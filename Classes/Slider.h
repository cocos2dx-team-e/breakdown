#ifndef __breakdown__Slider__
#define __breakdown__Slider__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <Box2D/Box2D.h>

class Slider
: public CCPhysicsSprite
{
    b2BodyDef bodyDef; // 物理エンジン上の物質の定義
public:
    Slider();
    virtual ~Slider();
    CREATE_FUNC(Slider);
    virtual bool init();
};


#endif /* defined(__breakdown__Slider__) */
