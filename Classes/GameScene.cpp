#include "GameScene.h"
#include "Config.h"
#include "Ball.h"
#include "Block.h"
#include "SimpleAudioEngine.h"
#include "GamePhysicsContactListener.h"
#include "GLES-Render.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild( GameScene::sharedGameScene() );
    return scene;
}

GameScene* GameScene::sharedGameScene()
{
    static GameScene* pInstance;
    if( pInstance == NULL ){
        pInstance = new GameScene();
        pInstance->init();
    }
    return pInstance;
}

bool GameScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    setTouchMode(kCCTouchesOneByOne);
	setTouchEnabled(true);

    // 背景表示
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pBG = CCSprite::create("background.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);

    {// Box2dの初期化
        
        b2Vec2 gravity;
        gravity.Set( 0.0f, -5.0f );
        mpB2World = new b2World(gravity);
        mpB2World->SetAllowSleeping( true );
        mpB2World->SetContinuousPhysics( true );
        
        // 外周の壁
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set( 0, 0 );
        b2Body* pGroundBody = mpB2World->CreateBody( &groundBodyDef );
        {
            CCSize size = CCDirector::sharedDirector()->getVisibleSize();
            size.width /= getPTMRatio();
            size.height /= getPTMRatio();
            
            b2EdgeShape groundBox;
            // bottom
            groundBox.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( size.width, 0.0f ) );
            pGroundBody->CreateFixture( &groundBox, 0 );
            // top
            groundBox.Set( b2Vec2( 0.0f, size.height ), b2Vec2( size.width, size.height ) );
            pGroundBody->CreateFixture( &groundBox, 0 );
            // left
            groundBox.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( 0.0f, size.height ) );
            pGroundBody->CreateFixture( &groundBox, 0 );
            // right
            groundBox.Set( b2Vec2( size.width, 0.0f ), b2Vec2( size.width, size.height ) );
            pGroundBody->CreateFixture( &groundBox, 0 );
        }

        // 衝突イベントのリスナーを登録する
        mpB2World->SetContactListener( new GamePhysicsContactListener() );

        //
        b2Draw* pB2Draw = new GLESDebugDraw();
        pB2Draw->SetFlags( 0xffff );
        mpB2World->SetDebugDraw( pB2Draw );
    }

    //スライダー生成
    createSlider();
    CCSprite* player = (CCSprite *)this->getChildByTag(1);

    // Ballクラスの初期化
    mpBall = Ball::create();
    mpBall->attach( player, ccp(0, 16) );
    addChild(mpBall);

    //
    Block* pBlock = Block::create();
    pBlock->setLife(3);
    pBlock->setSpriteAndB2Position(ccp(size.height * 0.5, size.width * 0.5));
    pBlock->setTag( NODE_TAG_BLOCK );
    addChild(pBlock);

#if 0 // テスト用にボールを沢山だせます
    for( int lp = 0; lp < 20; ++lp ){
        Ball* p = Ball::create();
        p->fire( ccp( (CCRANDOM_0_1()-0.5f)*3, CCRANDOM_0_1()*5 ) );
        addChild(p);
    }
#endif

    // TODO Startボタン押下でスタート

    CCLog("%s","breakdown App initialized.");
    scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    
    {// Box2dの更新
        
        //It is recommended that a fixed time step is used with Box2D for stability
        //of the simulation, however, we are using a variable time step here.
        //You need to make an informed choice, the following URL is useful
        //http://gafferongames.com/game-physics/fix-your-timestep/
        
        int velocityIterations = 8;
        int positionIterations = 1;
        
        // Instruct the world to perform a single step of simulation. It is
        // generally best to keep the time step and iterations fixed.
        mpB2World->Step( delta, velocityIterations, positionIterations );
    }
}

void GameScene::draw()
{
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    mpB2World->DrawDebugData();
    kmGLPopMatrix();
}

float GameScene::getPTMRatio() const
{
    return PTM_RATIO;
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    const CCPoint location =pTouch->getLocation();

    // 仮
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    if( player->boundingBox().containsPoint( location ) ){
        mpBall->attach( player, ccp(0, 16) );
    }

    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent){

    //タップポイント取得
    CCDirector * pDirector = pDirector->CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

    //高さだけ固定
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    touchPoint.y = winSize.height*0.2;

    CCSprite* player = (CCSprite *)this->getChildByTag(1);

    player->setPosition(touchPoint);

}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    const CCPoint location =pTouch->getLocation();

    // スライダーの位置でタップを離したら、発射!!
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    if( player->boundingBox().containsPoint( location ) ){
        mpBall->fire( ccp( (CCRANDOM_0_1()-0.5f)*3, CCRANDOM_0_1()*5 ) );
    }
}

void GameScene::createSlider(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* mainController = CCSprite::create("slider.png");
    mainController->setPosition(ccp(winSize.width*0.5, winSize.height*0.2));
    //画像縮小
    mainController->setScale(0.4);

    mainController->setTag(1);

    this->addChild(mainController);
}

void GameScene::playBGM()
{
    //BGMあれば実装
    //SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
}
