//
//  GameScene.cpp
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#include "GameScene.h"
#include "ui/cocosGUI.h"
using namespace ui;

 GameScene * GameScene::GS=nullptr;
Vector<Enemy*> GameScene::allEnemy;
Vector<Bullet*> GameScene::allBullet;

Scene * GameScene::createScene(){
    auto scene=Scene::create();
    auto layer=GameScene::getInstance();
    scene->addChild(layer);
    return scene;
}

 GameScene * GameScene::getInstance()
{
    if(GS!=nullptr)
    {
        return GS;
    }else
    {
        GS=GameScene::create();
        return GS;
    }
}

bool GameScene::init(){
    if(!Layer::init())
    {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PlayResource.plist");
    this->levelNumber=1;
    this->initLevel();
//    initToolBar();
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    tdState=0;
    this->scheduleUpdate();
    return true;
}

void GameScene::initLevel(){
    levelinf.clear();
    allPoint.clear();
    allEnemy.clear();
    allTD.clear();
    GameScene::allBullet.clear();
    for (int i=0; i<9; i++) {
        for(int j=0;j<16;j++)
        {mapinfo[i][j]=0;
        }
    }
    this->removeAllChildrenWithCleanup(true);

// 读取关卡信息配置文件
    ValueMap levelinfo=FileUtils::getInstance()->getValueMapFromFile(
                StringUtils::format("level_00%d.plist",this->levelNumber));

    this->levelinf=levelinfo["levelinfo"].asValueMap();
    ValueMap levelmap=levelinfo["levelmap"].asValueMap();

// 关卡背景
    auto bk=Sprite::create(levelmap["bgimg"].asString());
    this->addChild(bk);
    bk->setTag(999);
    bk->setPosition(Director::getInstance()->getVisibleSize()/2);

	//关卡瓦片地图信息
	auto levelMap = TMXTiledMap::create(levelmap["mapfile"].asString());
	levelMap->setTag(1000);
	levelMap->setAnchorPoint(Vec2(0.5,0.5));
	levelMap->setPosition(Director::getInstance()->getWinSize().width/2,
                     Director::getInstance()->getWinSize().height/2);
	
    this->addChild(levelMap);
    
    initAllPoint(levelMap);

	//关卡初始金钱
    this->money=levelinf["money"].asInt();
    this->npcNumber=1;
    this->npcNumberCount=levelinf["npcgroup"].asValueVector().size();
    this->hp=100;
    
    this->npcNumber_index=0;
    ValueVector allenemy=levelinf["npcgroup"].asValueVector();
    this->npcNumber_index_count=allenemy.at(0).asValueVector().size();

    this->schedule(schedule_selector(GameScene::newEnemy), 3);
   
    initToolBar();

}

void GameScene::initAllPoint(TMXTiledMap * map){
    auto objs=map->getObjectGroup("obj");
    for (int i=0; i<objs->getObjects().size(); i++) {
        MyPoint * tmp=MyPoint::create();
        tmp->x=objs->getObject(StringUtils::format("%d",i))["x"].asFloat();
        tmp->y=objs->getObject(StringUtils::format("%d",i))["y"].asFloat();
        this->allPoint.pushBack(tmp);
    }
}

void GameScene::newEnemy(float t){
	int type=0;
    if (this->npcNumber_index<this->npcNumber_index_count) {
       ValueVector allenemy=levelinf["npcgroup"].asValueVector();
        type=allenemy.at(npcNumber-1).asValueVector().at(npcNumber_index).asValueMap()["npc_Type"].asInt();
        npcNumber_index++;
    }else{
        npcNumber_index=0;
        npcNumber++;
        if(npcNumber>npcNumberCount)
        {
            npcNumber=npcNumberCount;
            this->unschedule(schedule_selector(GameScene::newEnemy));
            return;
        }
		else
        {
			auto labgroup=(Label *)this->getChildByTag(2000)->getChildByTag(2003);
			labgroup->setString(StringUtils::format("%d",this->npcNumber));
        }
        return;
    }
    
    auto newEnemy=Enemy::createEnemy(type, allPoint);
    this->addChild(newEnemy,1);
    allEnemy.pushBack(newEnemy);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){

	CCLOG("getLocation %f,%f", touch->getLocation().x, touch->getLocation().y);
	CCLOG("getLocationInView %f,%f", touch->getLocationInView().x, touch->getLocationInView().y);
	//得到用户点击这个点所在地图的行列
	int r=touch->getLocation().y/71;
    int c=touch->getLocation().x/71;
    auto map=(TMXTiledMap *)this->getChildByTag(1000);
    int gid=map->getLayer("bg")->getTileGIDAt(Vec2(c,r));
    bool canTouch=false;
    if(gid>0)
    {
        if(!map->getPropertiesForGID(gid).isNull())
        {
        auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
        if(!tileTemp.empty())
         {
             canTouch=true;
         }
        }
    }
    nowRow=((int)(touch->getLocation().y/71));
    nowCol=((int)(touch->getLocation().x/71));
    if(mapinfo[nowRow][nowCol]==0)
    {
		if (canTouch) {
			if(this->getChildByTag(1001)!=nullptr)
			{
				this->getChildByTag(1001)->removeFromParentAndCleanup(true);
			}
			addTDselect(nowRow, nowCol);
		}
		else{
			auto tips = Sprite::createWithSpriteFrameName("no.png");
			tips->setAnchorPoint(Vec2(0,0));
			tips->setPosition(((int)(touch->getLocation().x/71))*71,((int)(touch->getLocation().y/71))*71);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.8f),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),NULL));
		}
    }
	else
    {
		//TODO 出现塔升级或者卖掉的图层 
    }
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
}

void GameScene::addTDselect(int r,int c){
    this->nowRow=r;
    this->nowCol=c;
	//添加图片
    auto Image= Sprite::createWithSpriteFrameName("towerPos.png");
    int height=Image->getContentSize().height;
    int width=Image->getContentSize().width;  

	//箭楼
    auto  bt01= Sprite::createWithSpriteFrameName("ArrowTower1.png");
    auto  bt01_select= Sprite::createWithSpriteFrameName("ArrowTower1.png");
    bt01_select->setScale(1.1);

	//第二种攻击塔
    auto  bt02= Sprite::createWithSpriteFrameName("AttackTower1.png");
    auto  bt02_select= Sprite::createWithSpriteFrameName("AttackTower1.png");
    bt02_select->setScale(1.1);

	//第三种攻击塔
    auto  bt03= Sprite::createWithSpriteFrameName ("MultiDirTower1.png");
    auto  bt03_select= Sprite::createWithSpriteFrameName ("MultiDirTower1.png");
    bt03_select->setScale(1.1);

    //将3个Sprite转为Menu接收用户事件
    auto mitem01=MenuItemSprite::create(bt01, bt01_select, CC_CALLBACK_1(GameScene::selectTD, this));
    auto mitem02=MenuItemSprite::create(bt02, bt02_select, CC_CALLBACK_1(GameScene::selectTD, this));
    auto mitem03=MenuItemSprite::create(bt03, bt03_select, CC_CALLBACK_1(GameScene::selectTD, this));

    mitem01->setTag(10);
    mitem02->setTag(11);
    mitem03->setTag(12);

    mitem01->setAnchorPoint(Vec2(1,0));
    mitem02->setAnchorPoint(Vec2(0.5,0));
    mitem03->setAnchorPoint(Vec2(0,0));

	mitem01->setPosition(Vec2(0, height));
	mitem02->setPosition(Vec2(width / 2, height));
	mitem03->setPosition(Vec2(width, height));

    auto menuTD=Menu::create(mitem01,mitem02,mitem03,nullptr);
    menuTD->setPosition(Vec2::ZERO);
    Image->addChild(menuTD);

    Image->setTag(1001);
    this->addChild(Image,2);
    Image->setAnchorPoint(Vec2(0,0));
    Image->setPosition(c*71,r*71);
//    Image->runAction(Sequence::create(DelayTime::create(5.0f),
//                                     CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, Image)),
//                                     NULL));
   }

void GameScene::selectTD(Ref * obj)
{
	auto item=(MenuItemSprite *)obj; 
    switch (item->getTag()) {
        case 10://塔1
          {
			TD * newTd=TD::createNewTD(1,nowRow,nowCol);
            if(this->money>=newTd->price) //如果钱够
             {  this->addChild(newTd);
                //设置地图记录
                 allTD.pushBack(newTd);
                 mapinfo[nowRow][nowCol]=allTD.getIndex(newTd)+1;
                 this->money-=newTd->price;
                  auto moneyLabel=(Label *)this->getChildByTag(2000)->getChildByTag(2002);
                 moneyLabel->setString(StringUtils::format("%d",money));
             }
			 else
             {
                 auto tips = Sprite::createWithSpriteFrameName(
                                                               "nomoney_mark.png");
                 tips->setAnchorPoint(Vec2(0,0));
                 //    CCLOG("tiled width%f tips width%f",map->getTileSize().width,tips->getContentSize().width);
                 tips->setPosition(nowCol*71,nowRow*71);
                 this->addChild(tips);
                 tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                                  CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                                  NULL));
             }
        
            }
            break;
        case 11://塔2
            
            break;
        case 12://塔3
            
            break;
        default:
            break;
    }
    CCLOG("您选中了%d",item->getTag());
    //移除旧的塔的选择
    if(this->getChildByTag(1001)!=nullptr)
    {
        this->getChildByTag(1001)->removeFromParentAndCleanup(true);
    }
//    tdState=0;
    
}

void GameScene::update(float t)
{
    for(int i=0;i<GameScene::allBullet.size();i++)
    { 
		Bullet * nowBullet=allBullet.at(i);
        for(int j=0;j<GameScene::allEnemy.size();j++)
        { 
			Enemy * nowEnemy=GameScene::allEnemy.at(j);
            Rect rb(nowBullet->px,
                    nowBullet->py,
                    30,
                    30);
            Rect re(nowEnemy->getPosition().x,
                    nowEnemy->getPosition().y,
                    100,
                   100);
            if (rb.intersectsRect(re)) {
                nowEnemy->hp--;
                nowEnemy->sHp();
                
                if(nowEnemy->hp<=0)
                {
                    this->money+=100;
                    auto moneyLabel=(Label *)this->getChildByTag(2000)->getChildByTag(2002);
                    moneyLabel->setString(StringUtils::format("%ld",this->money));

                    auto exp=Explode::newExplode(1, nowEnemy->getPositionX(),nowEnemy->getPositionY());
                    this->addChild(exp);

                    nowEnemy->unscheduleAllSelectors();
                    nowEnemy->stopAllActions();
                    nowEnemy->removeFromParentAndCleanup(true);
                    GameScene::allEnemy.erase(j);
                }

                nowBullet->unscheduleAllSelectors();
                nowBullet->stopAllActions();
                nowBullet->removeFromParentAndCleanup(true);
                GameScene::allBullet.erase(i);
                i--;
                break;
            }
            
        }
    }

    if(this->npcNumber==this->npcNumberCount)
    {
      if(allEnemy.size()==0)
      {      
          this->levelNumber++;
          initLevel();
      }
    }
}

void GameScene::initToolBar(){
  
    Size size=Director::getInstance()->getWinSize();
    auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
    spritetool->setAnchorPoint(Vec2(0.5f, 1));
    spritetool->setPosition (Vec2(size.width / 2, size.height));
    this->addChild(spritetool,1);
    spritetool->setTag(2000);
    //
    auto moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    moneyLabel->setPosition(Vec2(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2));
    moneyLabel->setTag(2002);
    moneyLabel->setAnchorPoint(Point(0, 0.5f));
    auto moneyText = std::to_string(money);
    moneyLabel->setString(moneyText);
    spritetool->addChild(moneyLabel);
    
    //
    auto playHpBar = LoadingBar::create();
    playHpBar->setScale(2);
    playHpBar->loadTexture("sliderProgress2.png");
    playHpBar->setPercent(this->hp);
    playHpBar->setPosition(Vec2(spritetool->getContentSize().width / 5 *4  , spritetool->getContentSize().height / 2));
    playHpBar->setTag(2001);
    spritetool->addChild(playHpBar);
    
    auto star = Sprite::createWithSpriteFrameName("playstar.png");
    star->setPosition(Point(spritetool->getContentSize().width / 5 *4 , spritetool->getContentSize().height / 2));
    spritetool->addChild(star);
    
    //
    auto groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupLabel->setPosition(Vec2(spritetool->getContentSize().width / 8 * 3, spritetool->getContentSize().height / 2 ));
    groupLabel->setAnchorPoint(Point(0.5f , 0.5f));
    groupLabel->setTag(2003);
    auto groupInfoText = std::to_string(this->npcNumber);
    groupLabel->setString(groupInfoText);
    spritetool->addChild(groupLabel);
    
    auto groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2 , spritetool->getContentSize().height / 2 ));
    groupTotalLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupTotalText = std::to_string(this->npcNumberCount);
    groupTotalLabel->setString(groupTotalText);
    spritetool->addChild(groupTotalLabel);
    
    // back
    Sprite *backItem1 = Sprite::createWithSpriteFrameName("playbutton1.png");
    Sprite *backItem2 = Sprite::createWithSpriteFrameName("playbutton2.png");
    MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, nullptr);
    pPauseItem->setPosition(Point(spritetool->getContentSize().width - backItem1->getContentSize().width/2, spritetool->getContentSize().height / 2));
    pPauseItem->setAnchorPoint(Point(0, 0.4f));
    Menu* pMenu = Menu::create(pPauseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    spritetool->addChild(pMenu);
}

void GameScene::changeHp(int h)
{
    this->hp=h;
    auto hpLoadingBar=(LoadingBar*)this->getChildByTag(2000)->getChildByTag(2001);
    hpLoadingBar->setPercent(this->hp);
    if(hp<=0)
    {
        this->unscheduleAllSelectors();
        this->stopAllActions();

        Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5, GameOver::createScene()));
        GameScene::GS=nullptr;
    }
}




