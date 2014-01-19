#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "Slider.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Ball;

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual void update(float delta);
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    //スライダー用
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    // Singleton
    static GameScene* sharedGameScene();
    
    // 物理世界へようこそ
    b2World* getB2World(){ return mpB2World; }
    const b2World* getB2World() const { return mpB2World; }
    
    // Pixel To Meter ?
    float getPTMRatio() const;
    
private:
    b2World* mpB2World;
    
    //
    Ball* mpBall;

    //スライダー
    slider* piece;
};

#endif /* defined(__GAME_SCENE_H__) */
