#ifndef __breakdown__Slider__
#define __breakdown__Slider__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include <Box2D/Box2D.h>

class Slider
: public CCSprite
{
public:

    CREATE_FUNC(Slider);

    virtual bool init();

    virtual void move(CCPoint CCpoint);

};


#endif /* defined(__breakdown__Slider__) */
