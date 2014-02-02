/*
 @Author shun-tak
 */
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
    int life; // ブロックの体力
    b2BodyDef bodyDef; // 物理エンジン上の物質の定義

public:
    Block();
    virtual ~Block();
    CREATE_FUNC(Block);
    virtual bool init();

    void setLife(int l);

    // SpriteとB2Bodyの位置を設定する
    void setSpriteAndB2Position(CCPoint p);

    int getLife(); // 残り体力
    void hit(); // ダメージを受けたときに呼ぶ
    bool isDead(); // 生死判定
    void explode(); // 爆発エフェクト
};

#endif /* defined(__breakdown__Block__) */
