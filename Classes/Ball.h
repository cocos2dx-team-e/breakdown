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

    ///
    virtual void contactWith(CCNode* target);

private:
    int         mState;
    
    ///
    CCNode* mpAttachingTarget;
    CCPoint mAttachingTargetOffset;

    ///
    CCPhysicsSprite*    mpPhysicsSprite;
    CCParticleSystem*   mpParticle;
};

#endif /* defined(__breakdown__Ball__) */
