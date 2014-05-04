//
//  HScore.cpp
//  planeDemo
//
//  Created by cloud on 13-4-12.
//
//

#include "HScore.h"
#include "HAbout.h"
#include "HMenu.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
CCScene* HScore::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HScore *layer = HScore::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HScore::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //创建menu背景
    CCSprite *menuBg=CCSprite::create("score_bg.png");
    menuBg->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(menuBg);
   
    //添加一个文本获取存储的积分
    std::string scoreStr="";
    std::string score=CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str();
    if (atoi(score.c_str())!=-1) {
        scoreStr+=score;
    }
    else
    {
        scoreStr="0";
    }
    //显示分数
    CCLabelTTF *ttScore=CCLabelTTF::create(scoreStr.c_str(), "Helvetica", 23);
    ttScore->setPosition(ccp(size.width*0.5-50,size.height*0.5+70));
    ttScore->setColor(ccc3(255, 0, 0));
    addChild(ttScore);
    
    
    
    //创建菜单项
    CCLabelTTF *ttback=CCLabelTTF::create("返回主主菜单", "Helvetica-Bold", 23);
    ttback->setColor(ccc3(255, 255, 0));
    
    CCMenuItemLabel *itemReturn=CCMenuItemLabel::create(ttback, this, menu_selector(HScore::returnToMainMenu));
    itemReturn->setPosition(ccp(0, -120));
    
    
    CCMenu *menu=CCMenu::create(itemReturn,NULL);
    addChild(menu);
    return true;
}

void HScore::returnToMainMenu()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.5, HMenu::scene()));
}