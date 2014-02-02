/*
 @Author shun-tak
 */
#include "Config.h"
#include "Slider.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace std;

Slider::Slider()
{
}

Slider::~Slider()
{
}

bool Slider::init()
{
    // Spriteの設定
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("slider.png");
    if(!CCPhysicsSprite::initWithTexture(pTexture)) {
        return false;
    }

    // 物理エンジン上の物質の設定
    bodyDef.type = b2_staticBody;
    bodyDef.userData = this;

    b2Body* pBody = GameScene::sharedGameScene()->getB2World()->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(this->getContentSize().width / 2 / PTM_RATIO * SLIDER_SCALE,
                   this->getContentSize().height / 2 / PTM_RATIO * SLIDER_SCALE);

    b2FixtureDef shapeDef;
    shapeDef.shape = &shape;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.1f;
    shapeDef.restitution = 1.01f;
    pBody->CreateFixture(&shapeDef);

    setB2Body(pBody);
    setPTMRatio(PTM_RATIO);
    setScale(SLIDER_SCALE);
    setTag(NODE_TAG_SLIDER);

    return true;
}
