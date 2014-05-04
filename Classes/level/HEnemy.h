//
//  HEnemy.h
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//

#ifndef __towerDefense__HEnemy__
#define __towerDefense__HEnemy__
#include "HWayPoint.h"
#include "cocos2d.h"
extern class HTower;
using namespace cocos2d;
class HEnemy:public CCNode
{
    
    CCPoint myPostion;
    int maxHp;
    int currentHp;
    float walkingSpeed;
    HWayPoint *destnationWaypoint;
    bool active;
    HWorld* theGame;
    
    void initWithGame(HWorld *game);
    void update(float time);
    void removeSelf();
    virtual void draw();
    void getRemoved();
    CCArray *actby;
    virtual ~HEnemy();
public:
    void removeActby(HTower* tower);
    void addActby(HTower* tower);
    static HEnemy*initGame(HWorld* game);
    void doActive();
    CCSprite *mySprite;
    void getDamage(int damage);
};

#endif /* defined(__towerDefense__HEnemy__) */
