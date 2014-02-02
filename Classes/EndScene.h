/*
 @Author Takeda
 End画面
 */


#ifndef __breakdown__EndScene__
#define __breakdown__EndScene__

#include "cocos2d.h"

class EndScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    void transition();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(EndScene);

protected:
    void playBGM();
};
#endif /* defined(__breakdown__titleScene__) */
