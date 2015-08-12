//
//  LevelSelect.h
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#ifndef __towadgame__LevelSelect__
#define __towadgame__LevelSelect__
#include "cocos2d.h"
using namespace cocos2d;
class LevelSelect:public Layer
{
    public :
    static Scene * createScene();
    CREATE_FUNC(LevelSelect);
    bool  init();
};
#endif /* defined(__towadgame__LevelSelect__) */
