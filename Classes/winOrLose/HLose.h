//
//  HLose.h
//  protraitGame
//
//  Created by cloud on 13-4-18.
//
//

#ifndef __protraitGame__HLose__
#define __protraitGame__HLose__
#include "cocos2d.h"
class HLose:public cocos2d::CCLayerColor
{
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
public:
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HLose);
    void returnToMainMenu();
    
};

#endif /* defined(__protraitGame__HLose__) */
