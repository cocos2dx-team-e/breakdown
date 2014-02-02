#include "Ball.h"
#include "Block.h"
#include "Slider.h"
#include "GameScene.h"

/*
 * @author Y.Ishii
 */
Ball::Ball()
: mpParticle(NULL)
, mpAttachingTarget(NULL)
, mState(kState_Unknown)
{
}

Ball::~Ball()
{
    CC_SAFE_RELEASE(mpParticle);


    //
    //GameScene::sharedGameScene()->getB2World()->DestroyBody( mpPhysicsSprite->getB2Body() );
}

bool Ball::init()
{
    if( !CCNode::init() )
        return false;

    mState = kState_Unknown;
    mNextForce.SetZero();

    // 物理スプライトを初期化
    mpPhysicsSprite = CCPhysicsSprite::createWithTexture( CCTextureCache::sharedTextureCache()->addImage("ball01.png") );
    mpPhysicsSprite->setScale(2.0f);
    {
        // 物理情報を定義
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody( &bodyDef );
        {// 円の物理情報を登録する
            b2CircleShape shape;
            shape.m_radius = mpPhysicsSprite->getContentSize().width * 0.5f / GameScene::sharedGameScene()->getPTMRatio() * mpPhysicsSprite->getScale();

            b2FixtureDef shapeDef;
            shapeDef.shape = &shape;
            shapeDef.density = BALL_DENSITY;
            shapeDef.friction = BALL_FRICTION;
            shapeDef.restitution = BALL_RESTITUTION;
            pBody->CreateFixture( &shapeDef );
        }
        // SpriteとPhysicaを関連付ける
        mpPhysicsSprite->setB2Body( pBody );

        // 自信にタグをセットして、衝突リスナーから判別できるようにする
        this->setTag(NODE_TAG_BALL);
        pBody->SetUserData( this );
    }
    mpPhysicsSprite->setPTMRatio( GameScene::sharedGameScene()->getPTMRatio() );
    addChild(mpPhysicsSprite);

    // ボールの初期ライフを設定
    this->life = BALL_DEFAULT_LIFE;

    return true;
}

void Ball::onEnter()
{
    CCNode::onEnter();

    // ボールにまとわりつくエフェクトを作成
    mpParticle = CCParticleGalaxy::create(); //CCParticleSun
    mpParticle->retain();
    mpParticle->setTexture( CCTextureCache::sharedTextureCache()->addImage("ccbParticleFire.png") );
    mpParticle->setPosition( ccp(0, 0) );
    mpParticle->setAnchorPoint( ccp( 0.5f, 0.5f ) );
    mpParticle->setPosVar( ccp( 16.0f, 16.0f ) );
    mpParticle->setStartSize( 42.0f );
    mpParticle->setEndSize( 48.0f );
    mpParticle->setEmissionRate( 120.0f );
    mpParticle->setLife( 1.0f );
    mpParticle->setLifeVar( 0.1f );
    //    mpParticle->setTotalParticles( 300 );
    addChild( mpParticle );

    //
    scheduleUpdate();
}

void Ball::onExit()
{
    CCNode::onExit();

    //
    unscheduleUpdate();

    //
    removeChild( mpParticle );
}

void Ball::update(float delta)
{
    if( mState == kState_Attach ){
        CC_ASSERT(mpAttachingTarget);
        mpPhysicsSprite->setPosition( mpAttachingTarget->getPosition() + mAttachingTargetOffset );
    }
    else if( mState == kState_Move ){
        //
        if( mpPhysicsSprite->getPosition().y < -100 ){
            mState = kState_Unknown;
            // 物理運動を停止する
            mpPhysicsSprite->getB2Body()->SetActive( false );

            if (this->isDead()) {
                GameScene::sharedGameScene()->transitionScene(TRANSITON_CODE_GAMEOVER );
            } else {
                this->decrLife();
                this->scheduleOnce(schedule_selector(Ball::reattach), 2);
            }
        }else{
        }
    }

    mpParticle->setPosition( mpPhysicsSprite->getPosition() );
}

///
void Ball::attach(CCNode* targetObject, const CCPoint& offset)
{
    mState = kState_Attach;

    // アタッチ情報を保存
    mpAttachingTarget = targetObject;
    mAttachingTargetOffset = offset;

    // 物理運動を停止する
    mpPhysicsSprite->getB2Body()->SetActive( false );
}

void Ball::reattach()
{
    CC_ASSERT(mpAttachingTarget);
    attach( mpAttachingTarget, mAttachingTargetOffset );
}

void Ball::fire(const CCPoint& power)
{
    mState = kState_Move;

    // 力学を適用する
    mpPhysicsSprite->getB2Body()->SetAwake( false );
    mpPhysicsSprite->getB2Body()->ApplyForceToCenter( b2Vec2( power.x, power.y ) );

    // 物理運動を開始する
    mpPhysicsSprite->getB2Body()->SetActive( true );
}

void Ball::contactWith(CCNode* target)
{
    if( target->getTag() == NODE_TAG_BLOCK ){
        Block* block = (Block*)target;
        block->hit();
    }
    else if( target->getTag() == NODE_TAG_SLIDER ){
        Slider* slider = (Slider*)target;
        b2Vec2 v0( mpPhysicsSprite->getPositionX(), mpPhysicsSprite->getPositionY() );
        b2Vec2 v1( slider->getPositionX(), slider->getPositionY() );
        // 力学を適用する
        float angular = mpPhysicsSprite->getB2Body()->GetAngularVelocity() + 0.85f;
        b2Vec2 power1( v0 - v1 );
        b2Vec2 power2( mpPhysicsSprite->getB2Body()->GetLinearVelocity() );
        const float velocity = std::max( MIN_BALL_VELOCITY, std::min( MAX_BALL_VELOCITY, power2.Length() * ADDITIONAL_BALL_POWER ) );
        power1.y = fabsf(power1.y);
        power2.y = fabsf(power2.y);
        power1.Normalize();
        power2.Normalize();
        b2Vec2 force( power1 + power2 );
        force.Normalize();
        force *= velocity;
        CCLOG("POWER %.1f", force.Length());
        mpPhysicsSprite->getB2Body()->SetLinearVelocity( force );
        mpPhysicsSprite->getB2Body()->SetAngularVelocity( angular );
    }
}

