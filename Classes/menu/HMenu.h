//
//  HMenu.h
//  planeDemo
//
//  Created by cloud on 13-4-12.
//
//

#ifndef __planeDemo__HMenu__
#define __planeDemo__HMenu__

#include "cocos2d.h"
class HMenu:public cocos2d::CCLayer
{
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
public:
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();    
       
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HMenu);
    void playIsPressed();
    void scoreIsPressed();
    void aboutIsPressed();
};

#endif /* defined(__planeDemo__HMenu__) */
