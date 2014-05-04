//
//  HTower.h
//  towerDefense
//
//  Created by cloud on 13-4-17.
//
//

#ifndef __towerDefense__HTower__
#define __towerDefense__HTower__
//#include "HEnemy.h"
#include "HWorld.h"
#include "cocos2d.h"
#include "HEnemy.h"
class HTower:public cocos2d::CCNode
{
public:
    static HTower* initGame(HWorld *game,cocos2d::CCPoint loc);
    HEnemy *chosenEnemy;
    void targetKilled();
private:
    int attackRange;
    int damage;
    float fireRate;
    HWorld *theGame;
    cocos2d::CCSprite *mySprite;
    
    void initWithTheGame(HWorld * game,cocos2d::CCPoint location);
    void update(float time);
    virtual void draw();
    bool attacking;
    
    void attackEnemy();
    void shootWeapon();
    void chosenEnemyForAttack(HEnemy* enemy);
    void lastSightOfEnemy();
    void removeBullet(CCSprite *bullet);
    void damageEnemy();
};
#endif /* defined(__towerDefense__HTower__) */
