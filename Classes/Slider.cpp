#include "Slider.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace std;


bool Slider::init(){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* mainController = CCSprite::create("block.png");
    mainController->setPosition(ccp(winSize.width*0.5, winSize.height*0.2));
    //画像縮小
    mainController->setScale(0.2);
    
    mainController->setTag(1);

}

void Slider::move(CCPoint CCpoint){

    //高さだけ固定
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //touchPoint.y = winSize.height*0.2;

    //CCSprite* player = (CCSprite *)this->getChildByTag(1);

    //ここアニメーションさせる場合。ただtouchmoveだと変になった
    //float duration = 1.0f;
    //CCMoveTo* actionMove = CCMoveTo::create(duration, touchPoint);
    //player->runAction(actionMove);

    //player->setPosition(CCpoint);
}