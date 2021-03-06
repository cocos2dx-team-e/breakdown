#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"
#include "OverScene.h"
#include "Config.h"
#include "Ball.h"
#include "Block.h"
#include "Slider.h"
#include "SimpleAudioEngine.h"
#include "GamePhysicsContactListener.h"
#include "GLES-Render.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

/**
 * @author Y.Ishii
 * ちょっと強引にシングルトン
 */
CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild( GameScene::sharedGameScene() );
    return scene;
}

GameScene* GameScene::sharedGameScene()
{
    if( mpSharedInstance == NULL ){
        mpSharedInstance = GameScene::create();
    }
    return mpSharedInstance;
}

GameScene* GameScene::mpSharedInstance;

GameScene::GameScene()
: mpB2World(NULL)
{
    CCLOG("[%s]", __FUNCTION__);
    CC_ASSERT(mpSharedInstance == NULL);
    mpSharedInstance = this;
}

GameScene::~GameScene()
{
    CCLOG("[%s]", __FUNCTION__);
    mpSharedInstance = NULL;

    delete mpB2World;
}

/**
 *
 */
bool GameScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    setTouchMode(kCCTouchesOneByOne);
	setTouchEnabled(true);
    blockCount = 0;

    // 背景表示
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pBG = CCSprite::create("background.jpg");
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
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &groundBox;
            fixtureDef.density = WALL_DENSITY;
            fixtureDef.friction = WALL_FRICTION;
            fixtureDef.restitution = WALL_RESTITUTION;
            // bottom
//            groundBox.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( size.width, 0.0f ) );
//            pGroundBody->CreateFixture( &groundBox, 0 );
            // top
            groundBox.Set( b2Vec2( 0.0f, size.height ), b2Vec2( size.width, size.height ) );
            pGroundBody->CreateFixture(&fixtureDef);
            // left
            groundBox.Set( b2Vec2( 0.0f, 0.0f ), b2Vec2( 0.0f, size.height ) );
            pGroundBody->CreateFixture(&fixtureDef);
            // right
            groundBox.Set( b2Vec2( size.width, 0.0f ), b2Vec2( size.width, size.height ) );
            pGroundBody->CreateFixture(&fixtureDef);
        }

        // 衝突イベントのリスナーを登録する
        mpB2World->SetContactListener( new GamePhysicsContactListener() );

        //
        b2Draw* pB2Draw = new GLESDebugDraw();
        pB2Draw->SetFlags( 0xffff );
        mpB2World->SetDebugDraw( pB2Draw );
    }

    //スライダー生成
    Slider* player = Slider::create();
    player->setPosition(ccp(size.width*0.5, size.height*SLIDER_POSITION_RATE_Y));
    addChild(player);

    // Ballクラスの初期化
    mpBall = Ball::create();
    addChild(mpBall);

    // ブロック生成
    generateBlocks();

    CCLog("%s","breakdown App initialized.");
    return true;
}

/*
 @Author shun-tak
 */
void GameScene::generateBlocks()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    for (float row = 0.5; row < BLOCK_ROW_AMOUNT; row += 1.0) {
        int life = BLOCK_DEFAULT_LIFE - static_cast<int>(row);
        for (float column = 0.5; column < BLOCK_COLUMN_AMOUNT; column += 1.0) {
            Block* pBlock = Block::create();
            CCSize blockSize = pBlock->getContentSize();
            pBlock->setLife(life);
            pBlock->setSpriteAndB2Position(ccp(blockSize.width * BLOCK_SCALE * column,
                                               size.height - blockSize.height * BLOCK_SCALE * row));
            addChild(pBlock);
            blockCount++;
        }
    }
}

void GameScene::update(float delta)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    mpB2World->Step( delta, velocityIterations, positionIterations );

    // 死んだブロックの削除
    sweepDeadBlocks();

    // ゲームクリア判定
    if (isGameClear()) {
        transitionScene(TRANSITON_CODE_CLEAR);
    }
}

void GameScene::draw()
{
    CCLayer::draw();

#if 0
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    mpB2World->DrawDebugData();
    kmGLPopMatrix();
#endif
}

void GameScene::onEnter()
{
    CCLayer::onEnter();

    // Y.Ishii 再配置処理
    CCSprite* player = (CCSprite *)this->getChildByTag(NODE_TAG_SLIDER);
    mpBall->attach( player, ccp(0, 32) );

    scheduleUpdate();
}

void GameScene::onExit()
{
    CCLayer::onExit();

    unscheduleUpdate();
}

float GameScene::getPTMRatio() const
{
    return PTM_RATIO;
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //const CCPoint location =pTouch->getLocation();

    return true;
}

/*
 @Author minegishi
 BGM再生
 */
void GameScene::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent){

    //タップポイント取得
    CCDirector * pDirector = pDirector->CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

    //高さだけ固定
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    touchPoint.y = winSize.height*SLIDER_POSITION_RATE_Y;

    CCSprite* player = (CCSprite *)this->getChildByTag(NODE_TAG_SLIDER);

    player->setPosition(touchPoint);

}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    const CCPoint location =pTouch->getLocation();

    // スライダーの位置でタップを離したら、発射!!
    if( mpBall->getState() == Ball::kState_Attach ){
        mpBall->fire( ccp( (CCRANDOM_0_1()-0.5f)*3, 3.0f ) );
    }
}

/*
 @Author Takeda
 BGM再生
*/
void GameScene::playBGM()
{
    CCLOG("%s","PlayBGM");
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
}

/*
 @Author Takeda
 タイトル画面遷移用
*/
void GameScene::transitionScene(int transitionCode)
{
    //GameScene.h enumの定数により遷移
    if (transitionCode == TRANSITON_CODE_GAMEOVER)
    {

        CCLOG("%s","GAMEOVER");
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,OverScene::scene()));
    }
    else if(transitionCode == TRANSITON_CODE_CLEAR)
    {
        CCLOG("%s","GAME CLEAR");
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,EndScene::scene()));
    }
   
}

/*
 @Author shun-tak
 */
void GameScene::removeBlock(Block* pBlock)
{
    pBlock->getB2Body()->SetActive(false);
    pBlock->setVisible(false);
//    pBlock->removeFromParentAndCleanup(true);
//    getB2World()->DestroyBody( pBlock->getB2Body() );
    --blockCount;
}

/*
 @Author shun-tak
 */
void GameScene::sweepDeadBlocks()
{
}
