#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Ball;
class Block;
class Slider;


class GameScene : public cocos2d::CCLayer
{
public:

    virtual bool init();
    virtual ~GameScene();
    GameScene();

    void generateBlocks();

    // ゲーム終了
    void transitionScene(int transitionCode);

    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);

    // Singleton
    static GameScene* sharedGameScene();
    
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

    // 物理世界へようこそ
    b2World* getB2World(){ return mpB2World; }
    const b2World* getB2World() const { return mpB2World; }
    
    // Pixel To Meter ?
    float getPTMRatio() const;

    // B2オブジェクトの削除
    void removeBlock(Block* pBlock);

    // 死んだブロックをまとめて削除
    void sweepDeadBlocks();

    /*
     @Author shun-tak
     */
    bool isGameClear() { return blockCount <= 0 ? true : false; }
    
private:
    b2World* mpB2World;
    Ball* mpBall;
    int blockCount;

    static GameScene* mpSharedInstance;

protected:
    void playBGM();
};

#endif /* defined(__GAME_SCENE_H__) */
