#include "TitleScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* TitleScene::scene()
{
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);

    return scene;
}

bool TitleScene::init(){
    if (!CCLayer::init()) {
        return false;
    }

    // 画面サイズを取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    /* ラベルを作成 */
    CCString* numberString1 = CCString::createWithFormat("%s", "BREAKDOWN");
    CCLabelTTF* label1 = CCLabelTTF::create(numberString1->getCString(), "HelveticaNeue-Bold", 50.0);
    label1->setHorizontalAlignment(kCCTextAlignmentCenter);
    label1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
    
    CCString* numberString2 = CCString::createWithFormat("%s", "COCOS2D-X TEAM E");
    CCLabelTTF* label2 = CCLabelTTF::create(numberString2->getCString(), "HelveticaNeue-Bold", 32.0);
    label2->setHorizontalAlignment(kCCTextAlignmentCenter);
    label2->setColor(ccc3(255,0,0));
    label2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));

    /* ラベルの表示 */
    this->addChild(label1);
    this->addChild(label2);


    // Startボタンの作成
    CCMenuItemImage* btnStart = CCMenuItemImage::create("btnStart_OFF.png",
                                                        "btnStart_ON.png",
                                                        this,
                                                        menu_selector(TitleScene::startTapped));

    CCMenu* topMenu = CCMenu::create(btnStart, NULL);
    topMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.4));
    this->addChild(topMenu);

    this->playBGM();

    return true;
};

void TitleScene::startTapped()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,GameScene::scene()));
};

void TitleScene::playBGM()
{
    CCLOG("%s","PlayBGM");
    //BGMあれば実装
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
};
