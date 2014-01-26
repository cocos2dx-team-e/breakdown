#ifndef __breakdown__Block__
#define __breakdown__Block__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <Box2D/Box2D.h>

USING_NS_CC;
USING_NS_CC_EXT;

class Block
: public CCPhysicsSprite
{
    CCPoint point; // ブロックの座標
    int life; // ブロックの体力
    b2BodyDef bodyDef; // 物理エンジン上の物質の定義
public:
    Block();
    virtual ~Block();
    CREATE_FUNC(Block);

    /*
     位置と体力を指定してBlockのインスタンスを生成するstaticメソッド
     */
    static Block create(CCPoint p, int l);

    int getLife(); // 残り体力
    void hit(); // ダメージを受けたときに呼ぶ
    bool isDead(); // 生死判定
    void explode(); // 爆発エフェクト
};

#endif /* defined(__breakdown__Block__) */
