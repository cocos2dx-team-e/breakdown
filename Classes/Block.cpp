/*
 @Author shun-tak
 */
#include "Config.h"
#include "Block.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Block::Block()
{
    this->life = 0;
}

Block::~Block()
{
}

bool Block::init()
{
    // Spriteの設定
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("orange.png");
    if(!CCPhysicsSprite::initWithTexture(pTexture)) {
        return false;
    }

    // 物理エンジン上の物質の設定
    bodyDef.type = b2_staticBody;

    b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(this->getContentSize().width / 2 / PTM_RATIO * BLOCK_SCALE,
                   this->getContentSize().height / 2 / PTM_RATIO * BLOCK_SCALE);

    b2FixtureDef shapeDef;
    shapeDef.shape = &shape;
    shapeDef.density = BLOCK_DENSITY;
    shapeDef.friction = BLOCK_FRICTION;
    shapeDef.restitution = BLOCK_RESTITUTION;
    pBody->CreateFixture(&shapeDef);

    // 自信にタグをセットして、衝突リスナーから判別できるようにする
    this->setTag(NODE_TAG_BLOCK);
    pBody->SetUserData( this );

    setB2Body(pBody);
    setPTMRatio(PTM_RATIO);
    setScale(BLOCK_SCALE);

    return true;
}

void Block::setLife(int l)
{
    this->life = l;
}

void Block::setSpriteAndB2Position(CCPoint p)
{
    this->setPosition(p);
}

int Block::getLife()
{
    return this->life;
}

void Block::hit()
{
    this->life--;

    if (this->isDead()) {
        CCLog("ブロックの体力が0");
        //this->setTag(NODE_TAG_DEAD_BLOCK);
        scheduleOnce(schedule_selector(Block::explode), 0.0f);
        //explode();
        return;
    }

    /*{
        CCParticleExplosion* m_emitter = CCParticleExplosion::create();
        m_emitter->retain();
        m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("Icon-57.png") );
        m_emitter->setAutoRemoveOnFinish(true);
        m_emitter->setPosition( getPosition() );
        addChild(m_emitter, 10);
    }*/

    playDamageSound();

    // Spriteの画像をlife残量に応じて変更する
    CCTexture2D* pTexture;
    if(life == 1) {
        pTexture = CCTextureCache::sharedTextureCache()->addImage("dark_broken.png");
    } else if (life == 2) {
        pTexture = CCTextureCache::sharedTextureCache()->addImage("orange_broken.png");
    } else {
        pTexture = CCTextureCache::sharedTextureCache()->addImage("orange.png");
    }
    this->setTexture(pTexture);
}

bool Block::isDead()
{
    if (this->life <= 0) {
        return true;
    }
    return false;
}

/*
 @Author Minegishi
 */
void Block::playDamageSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
}

/*
 @Author Minegishi
 */
void Block::playDeadSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("destroy.wav");
}

void Block::explode()
{
    GameScene::sharedGameScene()->removeBlock(this);

    // 爆発エフェクトを表示する
    CCLog("爆発エフェクトを表示する");
    
    // 効果音を出す
    playDeadSound();
}
