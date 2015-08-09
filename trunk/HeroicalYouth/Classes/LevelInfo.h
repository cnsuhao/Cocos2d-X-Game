//
//  LevelInfo.h
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#ifndef __towadgame__LevelInfo__
#define __towadgame__LevelInfo__
#include "cocos2d.h"
using namespace cocos2d;
class LevelInfo:public Layer
{
public :
    static Scene * createScene();
    CREATE_FUNC(LevelInfo);
    bool  init();
};
#endif /* defined(__towadgame__LevelInfo__) */
