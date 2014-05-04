//
//  HWayPoint.h
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//

#ifndef __towerDefense__HWayPoint__
#define __towerDefense__HWayPoint__
#include "HWorld.h"
#include "cocos2d.h"
class HWayPoint:public CCNode
{
public:
    static HWayPoint * initGame(HWorld *game,CCPoint location);
    HWayPoint* nextWayPoint;
    CCPoint myPostion;

private:
    HWorld *theGame;
       
    virtual void draw();
    void initWithGame(HWorld *game,CCPoint location);
};

#endif /* defined(__towerDefense__HWayPoint__) */
