#ifndef breakdown_Config_h
#define breakdown_Config_h

// Pixel To Meter : nピクセルが1メートルという意味
#define PTM_RATIO 100

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
