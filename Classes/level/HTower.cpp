//
//  HTower.cpp
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//
#include "SimpleAudioEngine.h"
#include "HTower.h"
using namespace cocos2d;
using namespace CocosDenshion;
HTower* HTower::initGame(HWorld *game,cocos2d::CCPoint loc)
{
    HTower *tower=new HTower();
    if (tower)
    {
        tower->autorelease();
        tower->initWithTheGame(game, loc);
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return NULL;
}
void HTower::initWithTheGame(HWorld * game,cocos2d::CCPoint location)
{
    theGame=game;
    attackRange=70;        //炮塔攻击范围
    damage=10;             //伤害
    fireRate=1;            //攻击速度
    mySprite = CCSprite::create("tower.png");
    mySprite->setPosition(location);
    addChild(mySprite);
    game->addChild(this);
    scheduleUpdate();    
}
//选择一个敌怪攻击
void HTower::chosenEnemyForAttack(HEnemy* enemy)
{
    chosenEnemy=NULL;
    chosenEnemy=enemy;
    chosenEnemy->addActby(this);
    attackEnemy();
    //敌人受伤害
}
//攻击敌怪
void HTower::attackEnemy()
{
    schedule(schedule_selector(HTower::shootWeapon),fireRate);
}
//敌怪离开攻击范围
void HTower::lastSightOfEnemy()
{
    
    if (chosenEnemy) {
        chosenEnemy->removeActby(this);
        chosenEnemy=NULL;
    }
    unschedule(schedule_selector(HTower::shootWeapon));
}
void HTower::update(float time)
{
    if (chosenEnemy)
    {
        //炮口转向敌怪
        CCPoint targetPostion=chosenEnemy->mySprite->getPosition();
        CCPoint myPt=mySprite->getPosition();
        CCPoint normalized=ccpNormalize(ccp(targetPostion.x-myPt.x,targetPostion.y-myPt.y));
        mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x))+90);
        if (!theGame->collisionWithCircle(targetPostion, attackRange, myPt, 1)) {
            lastSightOfEnemy();
        }
    }
    else
    {
        //找到一个敌怪来攻击
        CCArray *enemies=theGame->returnEnemies();
        for (int i=0; i<enemies->count(); i++) {
            HEnemy *enemy=(HEnemy*) enemies->objectAtIndex(i);
            if (theGame->collisionWithCircle(mySprite->getPosition(), attackRange, enemy->mySprite->getPosition(), 1))
            {
                chosenEnemyForAttack(enemy);
                break;
            }
        }
    }
}
//开炮
void HTower::shootWeapon()
{
    SimpleAudioEngine::sharedEngine()->playEffect("laser_shoot.wav");
    CCSprite *bullet=CCSprite::create("bullet.png");
    theGame->addChild(bullet);
    bullet->setPosition(mySprite->getPosition());
    CCCallFuncN *funCall=CCCallFuncN::create(this, callfuncN_selector(HTower::removeBullet));
    CCCallFunc *funAct=CCCallFunc::create(this, callfunc_selector(HTower::damageEnemy));
    bullet->runAction(CCSequence::create(CCMoveTo::create(0.1, chosenEnemy->mySprite->getPosition()),funAct,funCall,NULL));
}
//敌怪掉血
void HTower::damageEnemy()
{
    if (chosenEnemy) {
        chosenEnemy->getDamage(damage);
    }
}
//移除子弹
void HTower::removeBullet(CCSprite *bullet)
{
    theGame->removeChild(bullet, true);
}
void HTower::draw()
{
    #ifdef TESTDebug
    ccDrawColor4F(255, 255, 255, 255);
    ccDrawCircle(mySprite->getPosition(), attackRange, 360, 30, false);
    #endif
}
//目标被击毁后，不再开炮
void HTower::targetKilled()
{
    chosenEnemy=NULL;
    unschedule(schedule_selector(HTower::shootWeapon));
}