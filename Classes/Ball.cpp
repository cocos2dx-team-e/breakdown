#include "Ball.h"
#include "GameScene.h"

Ball::Ball()
: mpParticle(NULL)
{
}

Ball::~Ball()
{
    CC_SAFE_RELEASE(mpParticle);
}

bool Ball::init()
{
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("dash.png");
    if( !CCPhysicsSprite::initWithTexture( pTexture ) )
        return false;

    //
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //    bodyDef.position.Set( 100, 100 );
    b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody( &bodyDef );
    {
        b2CircleShape shape;
        shape.m_radius = 24.0f / GameScene::sharedGameScene()->getPTMRatio();
        
        b2FixtureDef shapeDef;
        shapeDef.shape = &shape;
        shapeDef.density = 0.1f;
        shapeDef.friction = 0.1f;
        shapeDef.restitution = 0.95f;
        pBody->CreateFixture( &shapeDef );
    }
    
    //
    setB2Body( pBody );
    setPTMRatio( GameScene::sharedGameScene()->getPTMRatio() );
    setPosition( ccp( 1000 * CCRANDOM_0_1(), 600 * CCRANDOM_0_1() ) ); //KARI
    
    //
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

void Ball::attach(CCObject* targetObject, const CCPoint& offset)
{
}

/// 指定の場所へ向かって発射する
void Ball::fire(const CCPoint& targetPosition)
{
    
}

/// 移動中の処理等。毎フレーム行う処理
void Ball::update(float delta)
{
    mpParticle->setPosition( getPosition() );
}
