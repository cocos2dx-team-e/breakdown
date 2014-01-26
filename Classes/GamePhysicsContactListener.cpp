//
//  GamePhysicsContactListener.cpp
//  breakdown
//
//  Created by cocos2d-x on 14/01/26.
//
//

#include "GamePhysicsContactListener.h"
#include "Ball.h"

void GamePhysicsContactListener::BeginContact(b2Contact* contact)
{
    // 衝突した双方の物体を取得
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    CCNode* nodeA = (CCNode*)bodyA->GetUserData();
    CCNode* nodeB = (CCNode*)bodyB->GetUserData();

    if( nodeA != NULL && nodeB != NULL ){
        //
        if( nodeA->getTag() == NODE_TAG_BALL ){
            Ball* pBall = (Ball*)nodeA;
            pBall->contactWith(nodeB);
        }
        else if( nodeB->getTag() == NODE_TAG_BALL ){
            Ball* pBall = (Ball*)nodeB;
            pBall->contactWith(nodeA);
        }
    }

#if 0
    // 物体にひもづくSpriteを取得
    PhysicsSprite* spriteA = (PhysicsSprite*)bodyA->GetUserData();
    PhysicsSprite* spriteB = (PhysicsSprite*)bodyB->GetUserData();

    // 地面との衝突は無視する
    if (spriteA->getTag() == Config::kTag_Ground ||
        spriteB->getTag() == Config::kTag_Ground)
    {
        return;
    }

    // 衝突時の加速度を取得
    b2Vec2 velocityA = bodyA->GetLinearVelocity();
    b2Vec2 velocityB = bodyB->GetLinearVelocity();
    CCLOG("[BeginContact] A(%f, %f) B(%f, %f)", velocityA.x, velocityA.y, velocityB.x, velocityB.y);

    // 加速度が一定上の大きさだったら、ぶつかられた方を削除する
    float threshold = 3;
    if (pow(velocityA.x, 2) + pow(velocityA.y, 2) > pow(threshold, 2)) {
        spriteB->setDeleteFlag(true);
    }
    if (pow(velocityB.x, 2) + pow(velocityB.y, 2) > pow(threshold, 2)) {
        spriteA->setDeleteFlag(true);
    }
#endif
}

void GamePhysicsContactListener::EndContact(b2Contact* contact)
{

}

