//
//  HEnemy.cpp
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//
#include "HTower.h"
#include "HEnemy.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
HEnemy *HEnemy::initGame(HWorld* game)
{
    HEnemy *enmey=new HEnemy();
    if (enmey)
    {
        enmey->autorelease();
        enmey->initWithGame(game);
        return enmey;
    }
    CC_SAFE_DELETE(enmey);
    return NULL;
}
void HEnemy::initWithGame(HWorld *game)
{
    actby=CCArray::create();
    CC_SAFE_RETAIN(actby);
    theGame=game;
    maxHp=40;
    currentHp=maxHp;
    active=false;
    walkingSpeed=0.5f;
    //walkingSpeed=2.0f;
    mySprite=CCSprite::create("enemy.png");
    addChild(mySprite);
    CCArray *wayPoints=theGame->returnWayPoints();
    int nIndex=wayPoints->count()-1;
    if (nIndex>=0) {
        HWayPoint* wayPoint=(HWayPoint*) wayPoints->objectAtIndex(nIndex);
        destnationWaypoint=wayPoint->nextWayPoint;
        myPostion=wayPoint->myPostion;
        mySprite->setPosition(myPostion);
    }
    theGame->addChild(this);
    scheduleUpdate();
    
}
//敌怪掉血
void HEnemy::getDamage(int damage)
{
    currentHp-=damage;
    if (currentHp<=0)
    {
        //敌怪被消灭了，告诉炮塔别开炮了
        for (int i=0;i<actby->count(); i++) {
            HTower *tower=(HTower*) actby->objectAtIndex(i);
            tower->targetKilled();
        }
        getRemoved();
        SimpleAudioEngine::sharedEngine()->playEffect("enemy_destroy.wav");
    }
}
//敌怪开始活动
void HEnemy::doActive()
{
    active=true;
}
//清空自己
void HEnemy::removeSelf()
{
    theGame->removeChild(this, true);
    CCArray *enemies=theGame->returnEnemies();
    enemies->removeObject(this);
    theGame->enmeyGotKilled();
}
void HEnemy::draw()
{
    //画血条
    CCPoint postion=mySprite->getPosition();
    CCPoint orgin;
    CCPoint endpt;
    orgin.x=postion.x-10;
    orgin.y=postion.y+16;
    endpt.x=postion.x+10;
    endpt.y=postion.y+14;
    ccDrawSolidRect(orgin, endpt, ccc4f(255, 0, 0, 255));
    float cuthp=currentHp;
    cuthp=cuthp/maxHp*20;  //血条总长20
    endpt.x=postion.x-10+cuthp;
    ccDrawSolidRect(orgin, endpt, ccc4f(0, 255, 0, 255));
    
}
//敌怪被消灭了
void HEnemy::getRemoved()
{
    //爆炸粒子效果
    CCParticleSystemQuad *particle=CCParticleSystemQuad::create("particle_boom.plist");
    particle->setPosition(mySprite->getPosition());
    particle->setAutoRemoveOnFinish(true);
    theGame->addChild(particle);
    
    theGame->addGold(200);
    removeSelf();
}
//被炮塔攻击
void HEnemy::addActby(HTower* tower)
{
    actby->addObject(tower);
}
//离开炮塔攻击
void HEnemy::removeActby(HTower* tower)
{
    actby->removeObject(tower);
}

void HEnemy::update(float time)
{
    if (!active) {
        return;
    }
    if (theGame->collisionWithCircle(myPostion, 1, destnationWaypoint->myPostion, 1))//到了一个路径点，就走下一个路径点
    {
        if (destnationWaypoint->nextWayPoint) {
            destnationWaypoint=destnationWaypoint->nextWayPoint;
        }
        else
        {
            //玩家掉血
            theGame->getHpDamage();
            removeSelf();
        }
    }
    CCPoint targetPoint=destnationWaypoint->myPostion;
    float movementSpeed=walkingSpeed;
    CCPoint normalized=ccpNormalize(ccp(targetPoint.x-myPostion.x,targetPoint.y-myPostion.y));
    double angle=atan2(normalized.y, -normalized.x);
    float rotation=CC_RADIANS_TO_DEGREES(angle);         //旋转方向
    mySprite->setRotation(rotation);
    
    myPostion=ccp(myPostion.x+normalized.x*movementSpeed,myPostion.y+normalized.y*movementSpeed);//移动距离
    mySprite->setPosition(myPostion);    
    
}
HEnemy::~HEnemy()
{
    CC_SAFE_RELEASE(actby);
}