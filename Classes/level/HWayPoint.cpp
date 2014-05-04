//
//  HWayPoint.cpp
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//

#include "HWayPoint.h"
HWayPoint * HWayPoint::initGame(HWorld *game,CCPoint location)
{
    HWayPoint *wayPoint=new HWayPoint();
    if (wayPoint) {
        wayPoint->autorelease();
        wayPoint->initWithGame(game, location);
        return wayPoint;
    }
    CC_SAFE_DELETE(wayPoint);
    return NULL;    
}
void HWayPoint::initWithGame(HWorld *game,CCPoint location)
{
    theGame=game;
    myPostion=location;
    theGame->addChild(this);
}
void HWayPoint::draw()
{
    #ifdef TESTDebug 
    ccDrawColor4F(0, 255, 0, 255);
    
    ccDrawCircle(myPostion, 6, 360, 30, false);
    ccDrawCircle(myPostion, 2, 360, 30, false);
    
    if (nextWayPoint) {
        ccDrawLine(myPostion, nextWayPoint->myPostion);
    }
    #endif
    
}