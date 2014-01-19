#ifndef __breakdown__Ball__
#define __breakdown__Ball__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <Box2D/Box2D.h>

/**
 * 移動しながらステージの壁＆ブロックと反射する
 */
class Ball
: public CCPhysicsSprite
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
    
    ///
    virtual bool init();
    
    /// 指定のオブジェクトのアタッチする
    virtual void attach(CCObject* targetObject, const CCPoint& offset);
    
    /// 指定の場所へ向かって発射する
    virtual void fire(const CCPoint& targetPosition);
    
    /// 移動中の処理等。毎フレーム行う処理
    virtual void update(float delta);
    
private:
    int         mState;
//    CCRect      mActionArea;        // 移動可能領域
    
    ///
    CCObject*   mpAttachingTarget;
    CCPoint     mAttachingTargetOffset;
    
    ///
    CCPoint     mMoveDirection;
    float       mMoveSpeed;
    
    ///
    CCParticleSystem*   mpParticle;
};

#endif /* defined(__breakdown__Ball__) */
