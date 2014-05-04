//
//  HMenu.cpp
//  planeDemo
//
//  Created by cloud on 13-4-12.
//
//
#include "HMenu.h"
#include "HAbout.h"
#include "HScore.h"
#include "HWin.h"
#include "HLose.h"
#include "HWorld.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
CCScene* HMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HMenu *layer = HMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    //创建menu背景
    CCSprite *menuBg=CCSprite::create("menu_bg.png");
    menuBg->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(menuBg);
    
    //播放背景音乐
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menuMusic.mp3", true);
    
    //创建菜单项
    CCMenuItem *itemPlay=CCMenuItemImage::create("play_nor.png", "play_pre.png", this, menu_selector(HMenu::playIsPressed));
    itemPlay->setPosition(ccp(0, 60));
    CCMenuItem *itemScore=CCMenuItemImage::create("score_nor.png", "score_pre.png", this, menu_selector(HMenu::scoreIsPressed));
    itemScore->setPosition(ccp(0, -itemScore->getContentSize().height+40));
    
    CCMenuItem *itemAbout=CCMenuItemImage::create("about_nor.png", "about_pre.png", this, menu_selector(HMenu::aboutIsPressed));
    itemAbout->setPosition(ccp(0, -itemScore->getContentSize().height*2+20));
    
    
    CCMenu *menu=CCMenu::create(itemPlay,itemScore,itemAbout,NULL);
    addChild(menu);
    return true;
}

void HMenu::playIsPressed()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, HWorld::scene()));
}
void HMenu::scoreIsPressed()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.5,HScore::scene()));
}
void HMenu::aboutIsPressed()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(1.5,HAbout::scene()));
}
