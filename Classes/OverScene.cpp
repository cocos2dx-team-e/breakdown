/*
 @Author Takeda
 End画面
 */

#include "OverScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* OverScene::scene()
{
    CCScene* scene = CCScene::create();
    OverScene* layer = OverScene::create();
    scene->addChild(layer);

    return scene;
}

bool OverScene::init(){
    if (!CCLayer::init()) {
        return false;
    }


    // 背景表示
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pBG = CCSprite::create("background.jpg");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);

    // 画面サイズを取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();


    /* ラベルを作成 */
    CCString* numberString3 = CCString::createWithFormat("%s", "GAME OVER");
    CCLabelTTF* label3 = CCLabelTTF::create(numberString3->getCString(), "HelveticaNeue-Bold", 50.0);
    label3->setHorizontalAlignment(kCCTextAlignmentCenter);
    label3->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));

    /* ラベルの表示 */
    this->addChild(label3);


    // BGM表示
    //this->playBGM();

    this->schedule(schedule_selector(OverScene::transition), 2);

    return true;
};

void OverScene::playBGM()
{
    CCLOG("%s","PlayBGM");
    //BGMあれば実装
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
};

void OverScene::transition()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,TitleScene::scene()));
}
