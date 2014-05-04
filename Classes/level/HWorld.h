#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <sstream>
#include "cocos2d.h"
//#define TESTDebug 1
using namespace cocos2d;
using namespace std;
enum
{
    tag_wave,
    tag_HP,
    tag_gold,
};
template<typename T>
string Conver2String(const T &value)
{
    stringstream ss;
    ss<<value;
    return ss.str();
}
class HWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();    
   
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HWorld);
    
    void loadTowerPositions();
    cocos2d::CCArray *towerBases;  //塔基座
    cocos2d::CCArray *towers;      //塔
    cocos2d::CCArray *wayPoints;   //路径点
    cocos2d::CCArray *enemies;     //敌怪
    cocos2d::CCArray *waveData;    //每波怪
    
    cocos2d::CCArray * returnWayPoints();
    cocos2d::CCArray * returnEnemies();
    virtual ~HWorld();
    void addWayPoints();
    bool collisionWithCircle(CCPoint pt1,float radius1,CCPoint pt2,float radius2);
    
    bool loadWaves();
    void enmeyGotKilled();
    void getHpDamage();
    void addGold(int golden);
private:
    bool isCanBuy();
    int gold;
    int wave;
    int hp;
    //生命周期相关函数
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
};

#endif // __HELLOWORLD_SCENE_H__
