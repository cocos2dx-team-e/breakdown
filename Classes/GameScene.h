#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Ball;
class Slider;


class GameScene : public cocos2d::CCLayer
{
public:
    // 画面遷移時の分岐コード
    enum {
        // ゲームオーバー
        TRANSITON_CODE_GAMEOVER,
        // クリア
        TRANSITON_CODE_CLEAR
    };

    virtual bool init();
    virtual ~GameScene();

    // ゲーム終了
    void transitionScene(int transitionCode);

    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual void update(float delta);
    virtual void draw();
    virtual void onEnter();
    virtual void onExit();
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    //スライダー用
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    //
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    // Singleton
    static GameScene* sharedGameScene();
    
    // 物理世界へようこそ
    b2World* getB2World(){ return mpB2World; }
    const b2World* getB2World() const { return mpB2World; }
    
    // Pixel To Meter ?
    float getPTMRatio() const;

    void createSlider();
    
private:
    b2World* mpB2World;
    
    //
    Ball* mpBall;

protected:
    void playBGM();
};

#endif /* defined(__GAME_SCENE_H__) */
