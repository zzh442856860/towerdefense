//
//  HWin.cpp
//  protraitGame
//
//  Created by cloud on 13-4-18.
//
//
#include "HMenu.h"
#include "HWin.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
CCScene* HWin::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HWin *layer = HWin::create();
    //layer->setColor(ccc3(255, 255, 255));
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HWin::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(128, 0, 0, 255)) )
    {
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //创建menu背景
    CCSprite *menuBg=CCSprite::create("game_win.png");
    menuBg->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(menuBg);
    
    
    //创建菜单项
    CCLabelTTF *ttback=CCLabelTTF::create("返回主主菜单", "Helvetica-Bold", 23);
    ttback->setColor(ccc3(255, 255, 0));
    
    CCMenuItemLabel *itemReturn=CCMenuItemLabel::create(ttback, this, menu_selector(HWin::returnToMainMenu));
    itemReturn->setPosition(ccp(0, -120));
    
    
    CCMenu *menu=CCMenu::create(itemReturn,NULL);
    addChild(menu);
    return true;
}

void HWin::returnToMainMenu()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.5, HMenu::scene(), true));
}