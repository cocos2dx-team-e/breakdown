#ifndef __breakdown__Ball__
#define __breakdown__Ball__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <Box2D/Box2D.h>
#include "Config.h"

class Slider;

/**
 * @author Y.Ishii
 * 移動しながらステージの壁＆ブロックと反射する
 */
class Ball
: public CCNode
{
public:
    Ball();
    virtual ~Ball();
    CREATE_FUNC(Ball);
    
    ///
    enum {
        kState_Unknown,
        kState_Attach,
        kState_Move,
    };
    
    /// 初期化
    virtual bool init();
    /// 移動中の処理等。毎フレーム行う処理
    virtual void update(float delta);
    ///
    virtual void onEnter();
    virtual void onExit();
    
    /// 指定のオブジェクトのアタッチする
    virtual void attach(CCNode* targetObject, const CCPoint& offset);
    
    /// 指定の場所へ向かって発射する
    virtual void fire(const CCPoint& power);

    /// 衝突検知時の処理
    virtual void contactWith(CCNode* target);

    /// 状態を取得します
    virtual int getState() const { return mState; }

private:
    int         mState;
    b2Vec2      mNextForce;
    
    CCNode* mpAttachingTarget;
    CCPoint mAttachingTargetOffset;

    CCPhysicsSprite*    mpPhysicsSprite;
    CCParticleSystem*   mpParticle;

    //
    void reattach();

    /*
     @Author shun-tak
     */
    int life;
    int getLife() { return life; }
    void decrLife() { life--; }
    bool isDead() { return life<=0 ? true : false; }
};

#endif /* defined(__breakdown__Ball__) */
