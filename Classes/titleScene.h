#ifndef __breakdown__titleScene__
#define __breakdown__titleScene__

#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    virtual void startTapped();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(TitleScene);

};
#endif /* defined(__breakdown__titleScene__) */
