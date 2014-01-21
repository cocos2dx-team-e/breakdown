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
    int life; // ブロックの体力
public:
    Block();
    virtual ~Block();
    CREATE_FUNC(Block);

    void setLife(int life);
    int getLife();
    void hit();
    bool isDead();
    void explode();
};

#endif /* defined(__breakdown__Block__) */
