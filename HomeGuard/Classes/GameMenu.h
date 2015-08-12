//
//  GameMenu.h
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#ifndef __towadgame__GameMenu__
#define __towadgame__GameMenu__
#include "cocos2d.h"
using namespace cocos2d;

class GameMenu:public Layer
{
    public :
    static Scene * createScene();
    CREATE_FUNC(GameMenu);
    bool  init();
};


#endif /* defined(__towadgame__GameMenu__) */
