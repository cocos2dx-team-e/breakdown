#include "Ball.h"
#include "Block.h"
#include "GameScene.h"

Ball::Ball()
: mpParticle(NULL)
{
}

Ball::~Ball()
{
    CC_SAFE_RELEASE(mpParticle);


    //
    GameScene::sharedGameScene()->getB2World()->DestroyBody( mpPhysicsSprite->getB2Body() );
}

bool Ball::init()
{
    if( !CCNode::init() )
        return false;

    mState = kState_Unknown;

    // 物理スプライトを初期化
    mpPhysicsSprite = CCPhysicsSprite::createWithTexture( CCTextureCache::sharedTextureCache()->addImage("dash.png") );
    {
        // 物理情報を定義
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody( &bodyDef );
        {// 円の物理情報を登録する
            b2CircleShape shape;
            shape.m_radius = 16.0f / GameScene::sharedGameScene()->getPTMRatio();

            b2FixtureDef shapeDef;
            shapeDef.shape = &shape;
            shapeDef.density = 0.1f;
            shapeDef.friction = 0.1f;
            shapeDef.restitution = 0.95f;
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
    
    // ボールにまとわりつくエフェクトを作成
    mpParticle = CCParticleGalaxy::create(); //CCParticleSun
    mpParticle->retain();
    mpParticle->setTexture( CCTextureCache::sharedTextureCache()->addImage("ccbParticleFire.png") );
    mpParticle->setPosition( ccp(0, 0) );
    mpParticle->setAnchorPoint( ccp( 0.5f, 0.5f ) );
    mpParticle->setPosVar( ccp( 16.0f, 16.0f ) );
    mpParticle->setStartSize( 42.0f );
    mpParticle->setEndSize( 42.0f );
    mpParticle->setEmissionRate( 80.0f );
    mpParticle->setLife( 1.0f );
    mpParticle->setLifeVar( 0.1f );
    //    mpParticle->setTotalParticles( 300 );
//    addChild( mpParticle );

    scheduleUpdate();
    return true;
}

void Ball::update(float delta)
{
    if( mState == kState_Attach ){
        CC_ASSERT(mpAttachingTarget);
        mpPhysicsSprite->setPosition( mpAttachingTarget->getPosition() + mAttachingTargetOffset );
    }
    else if( mState == kState_Attach ){
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

void Ball::fire(const CCPoint& power)
{
    mState = kState_Move;

    // 力学を適用する
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
    }
}

