#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
} Resource;

static Resource smallResource  = { cocos2d::CCSizeMake( 384, 512), "S"};
static Resource mediumResource = { cocos2d::CCSizeMake(768, 1024), "M"};
static Resource largeResource  = { cocos2d::CCSizeMake(1536, 2048), "L"};

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(768, 1024);

#define LEVEL_FONT_SIZE (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / mediumResource.size.width * 48)

#endif // __APPMACROS_H__
