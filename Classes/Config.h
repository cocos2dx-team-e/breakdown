/*
 @Author shun-tak
 */
#ifndef breakdown_Config_h
#define breakdown_Config_h

#include "cocos-ext.h"

// Pixel To Meter : nピクセルが1メートルという意味
#define PTM_RATIO 200

#define BLOCK_COLUMN_AMOUNT 4 // 横方向に並ぶブロックの数
#define BLOCK_ROW_AMOUNT 3 // 縦方向に並ぶブロックの数

#define BLOCK_SCALE 4.0f
#define SLIDER_SCALE 0.75f

#define BALL_DEFAULT_LIFE 2
#define BLOCK_DEFAULT_LIFE 3

// Sliderの高さ
#define SLIDER_POSITION_RATE_Y 0.1f 

// ボールの物理定数
#define BALL_DENSITY 0.1f
#define BALL_FRICTION 0.1f
#define BALL_RESTITUTION 1.0f

#define BLOCK_DENSITY 1.0f
#define BLOCK_FRICTION 0.0f
#define BLOCK_RESTITUTION 1.0f

#define SLIDER_DENSITY 1.0f
#define SLIDER_FRICTION 0.1f
#define SLIDER_RESTITUTION 1.01f

#define WALL_DENSITY 1.0f
#define WALL_FRICTION 0.0f
#define WALL_RESTITUTION 1.0f

#define MAX_BALL_VELOCITY 7.8f
#define MIN_BALL_VELOCITY 4.5f
#define ADDITIONAL_BALL_POWER 1.025f

// タグ
enum {
    NODE_TAG = 1000,

    NODE_TAG_BALL,
    NODE_TAG_BLOCK,
    NODE_TAG_SLIDER,
    NODE_TAG_DEAD_BLOCK,
    // ゲームオーバー
    TRANSITON_CODE_GAMEOVER,
    // クリア
    TRANSITON_CODE_CLEAR,
    // 現在のEnd結果
    TRANSITON_CODE
};

#endif
