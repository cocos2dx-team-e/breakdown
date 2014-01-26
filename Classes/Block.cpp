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

Block Block::create(CCPoint p, int l)
{
    Block block = *Block::create();

    block.point = p;
    block.life = l;

    return block;
}

bool Block::init()
{
    // Spriteの設定
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    // 物理エンジン上の物質の設定
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(getPositionX() / PTM_RATIO,
                         getPositionY() / PTM_RATIO);
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

    return true;
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
    if (this->life == 0) {
        return true;
    }
    return false;
}

void Block::explode()
{
    // 爆発エフェクトを表示する
    // 効果音を出す
}
