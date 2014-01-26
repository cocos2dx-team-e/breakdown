#ifndef __breakdown__Block__
#define __breakdown__Block__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <Box2D/Box2D.h>

USING_NS_CC;
USING_NS_CC_EXT;

class Block
: public CCPhysicsSprite
{
    CCPoint point; // ブロックの座標
    int life; // ブロックの体力
    b2BodyDef spriteBodyDef; // 物理エンジン上の物質の定義
public:
    Block();
    virtual ~Block();
    CREATE_FUNC(Block);
    static Block create(CCPoint p);


    int getLife();
    void hit();
    bool isDead();
    void explode();
};

#endif /* defined(__breakdown__Block__) */
