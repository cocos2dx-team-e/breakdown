/*
 @Author Takeda
 End画面
 */


#ifndef __breakdown__OverScene__
#define __breakdown__OverScene__

#include "cocos2d.h"
#include "TitleScene.h"
#include "GameScene.h"

class OverScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    void transition();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(OverScene);

protected:
    void playBGM();
};
#endif /* defined(__breakdown__titleScene__) */
