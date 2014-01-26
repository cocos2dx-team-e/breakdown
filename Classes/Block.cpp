#include "Config.h"
#include "Block.h"
#include "GameScene.h"

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
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("orange_48x16.png");
    if(!CCPhysicsSprite::initWithTexture(pTexture)) {
        return false;
    }

    // 物理エンジン上の物質の設定
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = this;

    b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody(&bodyDef);
    {
        b2PolygonShape shape;
        shape.SetAsBox(this->getContentSize().width / 2 / PTM_RATIO,
                       this->getContentSize().height / 2 / PTM_RATIO);

        b2FixtureDef shapeDef;
        shapeDef.shape = &shape;
        shapeDef.density = 1.0f;
        shapeDef.friction = 0.1f;
        shapeDef.restitution = 0.95f;
        pBody->CreateFixture(&shapeDef);
    }
    setB2Body(pBody);
    setPTMRatio(PTM_RATIO);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    setPosition(ccp(size.width * 0.5, size.width * 0.5));

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
    if (this->isDead()) {
        return;
    }
    this->life--;

    // Spriteの画像をlife残量に応じて変更する
}

bool Block::isDead()
{
    if (this->life <= 0) {
        return true;
    }
    return false;
}

void Block::explode()
{
    // 爆発エフェクトを表示する
    CCLog("爆発エフェクトを表示する");
    // 効果音を出す
    CCLog("効果音を出す");
}
