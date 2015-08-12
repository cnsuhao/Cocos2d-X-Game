//
//  Enemy.h
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#ifndef __towadgame__Enemy__
#define __towadgame__Enemy__
#include "cocos2d.h"
#include "MyPoint.h"
using namespace cocos2d;
class Enemy:public Node{
private:
    Vector<MyPoint *> allP;//ÿ���������
public:
    int ex,ey;
    int hp;
    CREATE_FUNC(Enemy);
    int curPoint;//��ǰ�ĵ�
    int countPoint;//�ܹ��ĵ�
    static Enemy * createEnemy(int etype,Vector<MyPoint *> &ap);
    bool init();
    void moveTo();//��ʱ�����ƶ���Ŀ���
    void sHp();//����Ѫ
};

#endif /* defined(__towadgame__Enemy__) */
