//
//  GamePhysicsContactListener.h
//  breakdown
//
//  Created by cocos2d-x on 14/01/26.
//
//

#ifndef __breakdown__GamePhysicsContactListener__
#define __breakdown__GamePhysicsContactListener__

#include "Box2D/Box2D.h"

class GamePhysicsContactListener
: public b2ContactListener
{
public:
    // 衝突時の処理
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    
};

#endif /* defined(__breakdown__GamePhysicsContactListener__) */
