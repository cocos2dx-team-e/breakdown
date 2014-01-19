#ifndef __breakdown__Slider__
#define __breakdown__Slider__

#include "cocos2D.h"
USING_NS_CC;

class Slider : public CCPhysicsSprite{
public:
    Slider();
    CREATE_FUNC(Ball);

    virtual bool init();

    void move(CCPoint CCpoint);

};


#endif /* defined(__breakdown__Slider__) */
