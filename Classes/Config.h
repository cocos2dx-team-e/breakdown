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
#define SLIDER_SCALE 0.4f

#define BLOCK_DEFAULT_LIFE 3

enum {
    NODE_TAG = 1000,

    NODE_TAG_BALL,
    NODE_TAG_BLOCK,
    NODE_TAG_SLIDER,
    NODE_TAG_DEAD_BLOCK,
    // ゲームオーバー
    TRANSITON_CODE_GAMEOVER,
    // クリア
    TRANSITON_CODE_CLEAR
};

#endif
