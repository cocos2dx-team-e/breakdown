#include "AppDelegate.h"
#include "GameScene.h"
#include "AppMacros.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    
    // デザインサイズの設定
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
    
    CCSize frameSize = pEGLView->getFrameSize();
    
    std::vector<std::string> searchPath;
    
    if (frameSize.height > mediumResource.size.height)
    {
        // 「L」ディレクトリのリソースを使用
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResource.size.height)
    {
        // 「M」ディレクトリのリソースを使用
        searchPath.push_back(mediumResource.directory);
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
    }
    else
    {
        // 「S」ディレクトリのリソースを使用
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width));
    }

    // 要マルチレゾリューション対応
    searchPath.push_back("block");
    searchPath.push_back("images");
    
    // リソースディレクトリを指定
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();
    // run
    pDirector->runWithScene( pScene );

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
