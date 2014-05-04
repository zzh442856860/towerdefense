#include "HWorld.h"
#include "SimpleAudioEngine.h"
#include "HTower.h"
#include "HWayPoint.h"
#include "HEnemy.h"
#include "stdio.h"
#include "SimpleAudioEngine.h"
#include "HWin.h"
#include "HLose.h"
using namespace cocos2d;
using namespace CocosDenshion;
#define TOWERCAST 300
CCScene* HWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HWorld *layer = HWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCSprite *background=CCSprite::create("Bg.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    addChild(background);
    
    towerBases=CCArray::create();//用create的都要retain
    CC_SAFE_RETAIN(towerBases);
    towers=CCArray::create();
    CC_SAFE_RETAIN(towers);
    wayPoints=CCArray::create();
    CC_SAFE_RETAIN(wayPoints);
    loadTowerPositions();//加载炮塔位置
    addWayPoints();//添加敌人行进路径
    
    enemies=CCArray::create();
    CC_SAFE_RETAIN(enemies);
    waveData=CCArray::createWithContentsOfFile("Waves.plist");
    CC_SAFE_RETAIN(waveData);
      
    
    //当前波数
    CCString *strWave=CCString::create("");
    strWave->initWithFormat("waves: %d",wave);
    CCLabelBMFont *pFont=CCLabelBMFont::create(strWave->getCString(), "font_red_14.fnt");
    pFont->setPosition(400,winSize.height-12);
    addChild(pFont,0,tag_wave);
    loadWaves();
    
    //当前血量
    hp=5;
    CCString *strHP=CCString::create("");
    strHP->initWithFormat("HP: %d",hp);
    CCLabelBMFont *pHPFont=CCLabelBMFont::create(strHP->getCString(), "font_red_14.fnt");
    pHPFont->setPosition(300,winSize.height-12);
    addChild(pHPFont,0,tag_HP);
    
    //当前黄金    
    gold=1000;
    CCString *strGold=CCString::create("");
    strGold->initWithFormat("gold: %d",gold);
    CCLabelBMFont *pGoldFont=CCLabelBMFont::create(strGold->getCString(), "font_red_14.fnt");
    pGoldFont->setPosition(200,winSize.height-12);
    addChild(pGoldFont,0,tag_gold);
    
    //背景音乐
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("8bitDungeonLevel.mp3", true);
    return true;
}
//判断黄金储备
bool HWorld::isCanBuy()
{
    if (gold-TOWERCAST>0) {
        return true;
    }
    return false;
}
//敌怪顺利到达终点
void HWorld::getHpDamage()
{
    if (hp<=0) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, HLose::scene()));
    }
    hp-=1;
    CCString *strHP=CCString::create("");
    strHP->initWithFormat("HP: %d",hp);
    CCLabelBMFont *pHPFont=(CCLabelBMFont *) getChildByTag(tag_HP);
    pHPFont->setString(strHP->getCString());
    SimpleAudioEngine::sharedEngine()->playEffect("life_lose.wav");
}
//加载波数
bool HWorld::loadWaves()
{
       
    if (wave>=waveData->count()) {
        return false;
    }
    CCArray *currenWaveData=(CCArray *)waveData->objectAtIndex(wave);
    for (int i=0; i<currenWaveData->count(); i++) {
        CCDictionary *pDic=(CCDictionary*)currenWaveData->objectAtIndex(i);        
        CCString* delay=(CCString *)pDic->valueForKey("spawnTime");
        HEnemy *enmey=HEnemy::initGame(this);
        enemies->addObject(enmey);
        enmey->scheduleOnce(schedule_selector(HEnemy::doActive), delay->floatValue());
    }
    wave++;
    CCLabelBMFont *pFont=(CCLabelBMFont*) getChildByTag(tag_wave);
    CCString *strWave=CCString::create("");
    strWave->initWithFormat("waves: %d",wave);
    pFont->setString(strWave->getCString());
    return true;

}
//判断是不是一波敌怪都死了，如果都死了，放下波敌怪
void HWorld::enmeyGotKilled()
{
    if (enemies->count()<=0)
    {
        if (!loadWaves()) {
            CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.5,HWin::scene()));
        }
    }
}
//设置敌怪活动路径
void HWorld::addWayPoints()
{
    HWayPoint *wayPoint1=HWayPoint::initGame(this, ccp(420,35));
    wayPoints->addObject(wayPoint1);
    wayPoint1->nextWayPoint=NULL;

    HWayPoint *wayPoint2=HWayPoint::initGame(this, ccp(35,35));
    wayPoints->addObject(wayPoint2);
    wayPoint2->nextWayPoint=wayPoint1;
    
    HWayPoint *wayPoint3=HWayPoint::initGame(this, ccp(35,130));
    wayPoints->addObject(wayPoint3);
    wayPoint3->nextWayPoint=wayPoint2;
    
    HWayPoint *wayPoint4=HWayPoint::initGame(this, ccp(445,130));
    wayPoints->addObject(wayPoint4);
    wayPoint4->nextWayPoint=wayPoint3;
    
    HWayPoint *wayPoint5=HWayPoint::initGame(this, ccp(445,220));
    wayPoints->addObject(wayPoint5);
    wayPoint5->nextWayPoint=wayPoint4;
    
    HWayPoint *wayPoint6=HWayPoint::initGame(this, ccp(-40,220));
    wayPoints->addObject(wayPoint6);
    wayPoint6->nextWayPoint=wayPoint5;
}
//加载塔基座
void HWorld::loadTowerPositions()
{
    CCArray *towerPositions=CCArray::createWithContentsOfFile("TowersPosition.plist");   
    for (int i=0;i<towerPositions->count();i++)    
    {
        CCDictionary *pDic=(CCDictionary *) towerPositions->objectAtIndex(i);
        CCSprite *towerBase=CCSprite::create("open_spot.png");
        const CCString *strX=pDic->valueForKey("x");
        const CCString *strY=pDic->valueForKey("y");
        int x=strX->intValue();
        int y=strY->intValue();        
        towerBase->setPosition(ccp(x,y));
        addChild(towerBase);
        towerBases->addObject(towerBase);

    }
    
}
//杀了一个怪，玩家得到金钱
void HWorld::addGold(int golden)
{
    gold+=golden;
    CCLabelBMFont *pGoldFont=(CCLabelBMFont *)getChildByTag(tag_gold);
    CCString *strGold=CCString::create("");
    strGold->initWithFormat("gold: %d",gold);
    pGoldFont->setString(strGold->getCString());
    CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Conver2String(gold));
    CCUserDefault::sharedUserDefault()->flush();
    
}
//圆形碰撞
bool HWorld::collisionWithCircle(CCPoint pt1,float radius1,CCPoint pt2,float radius2)
{
    float xdif=pt1.x-pt2.x;
    float ydif=pt1.y-pt2.y;
    
    float distande=sqrt(xdif*xdif+ydif*ydif);
    if (distande<=radius1+radius2) {
        return true;
    }
    return false;
}
CCArray *HWorld::returnEnemies()
{
    return enemies;
}
CCArray * HWorld::returnWayPoints()
{
    return wayPoints;
}
HWorld::~HWorld()
{
    CC_SAFE_RELEASE(towerBases);
    CC_SAFE_RELEASE(towers);
    CC_SAFE_RELEASE(wayPoints);
    CC_SAFE_RELEASE(enemies);
    CC_SAFE_RELEASE(waveData);
}
//生命周期相关函数
void HWorld::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}
void HWorld::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}
bool HWorld::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
    CCPoint location=pTouch->getLocation();
    for (int i=0; i<towerBases->count(); i++) {
        CCSprite* towerBase=(CCSprite*) towerBases->objectAtIndex(i);
        CCRect rect=towerBase->boundingBox();
        if(rect.containsPoint(location) && (towerBase->getUserData()==NULL)&&(isCanBuy()))
        {
            gold-=TOWERCAST;
            CCLabelBMFont *pGoldFont=(CCLabelBMFont *)getChildByTag(tag_gold);
            CCString *strGold=CCString::create("");
            strGold->initWithFormat("gold: %d",gold);
            pGoldFont->setString(strGold->getCString());
            CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Conver2String(gold));
            CCUserDefault::sharedUserDefault()->flush();
            
            HTower *tower=HTower::initGame(this, towerBase->getPosition());
            towers->addObject(tower);
            towerBase->setUserData(tower);
            SimpleAudioEngine::sharedEngine()->playEffect("tower_place.wav");
        }
    }
}
void HWorld::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent)
{
}
void HWorld::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
    
}