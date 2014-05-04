//
//  HLose.cpp
//  protraitGame
//
//  Created by cloud on 13-4-18.
//
//

#include "HLose.h"
#include "HMenu.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
CCScene* HLose::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HLose *layer = HLose::create();
    //layer->setColor(ccc3(255, 255, 255));
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HLose::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(128, 0, 0, 255)))
    {
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //创建menu背景
    CCSprite *menuBg=CCSprite::create("game_lost.png");
    menuBg->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(menuBg);
    
    
    //创建菜单项
    CCLabelTTF *ttback=CCLabelTTF::create("返回主主菜单", "Helvetica-Bold", 23);
    ttback->setColor(ccc3(255, 255, 0));
    
    CCMenuItemLabel *itemReturn=CCMenuItemLabel::create(ttback, this, menu_selector(HLose::returnToMainMenu));
    itemReturn->setPosition(ccp(0, -120));
    
    
    CCMenu *menu=CCMenu::create(itemReturn,NULL);
    addChild(menu);
    return true;
}

void HLose::returnToMainMenu()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.5, HMenu::scene(), true));
}