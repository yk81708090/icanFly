#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(HelloWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
//
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//
//    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
//
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
//
//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);


    CCArray *sps=GetSpritesWithFile("atlas.txt");
    CCSprite *bg= (CCSprite *)sps->objectAtIndex(0);
    bg->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(bg, 0);

    land = (CCSprite *)sps->objectAtIndex(34);
    land->setPosition( ccp(size.width/2, 0+land->boundingBox().size.height/2) );
    this->addChild(land);


    land2 = CCSprite::createWithSpriteFrame(land->displayFrame());
    land2->setScale(land->getScale());
    land2->setPosition( ccp(size.width/2+land2->boundingBox().size.width, 0+land2->boundingBox().size.height/2) );

    land2->setScale(land->getScale());
    this->addChild(land2);


    CCSprite *title = (CCSprite *)sps->objectAtIndex(68);
    title->setPosition( ccp(size.width/2, size.height*0.7) );
    this->addChild(title);


    CCSprite *button_play = (CCSprite *)sps->objectAtIndex(19);
    button_play->setPosition( ccp(size.width/2-button_play->boundingBox().size.width*0.6, 0+land2->boundingBox().size.height/2+land2->boundingBox().size.height*0.72) );
    this->addChild(button_play);

    CCSprite *button_score = (CCSprite *)sps->objectAtIndex(22);
    button_score->setPosition( ccp(size.width/2+button_score->boundingBox().size.width*0.6, 0+land2->boundingBox().size.height/2+land2->boundingBox().size.height*0.72) );
    this->addChild(button_score);



    CCSprite *brand_copyright = (CCSprite *)sps->objectAtIndex(15);
    brand_copyright->setPosition( ccp(size.width/2, 0+land2->boundingBox().size.height/2+land2->boundingBox().size.height*0.25) );
    this->addChild(brand_copyright);


    CCSprite *button_rate = (CCSprite *)sps->objectAtIndex(20);
    button_rate->setPosition( ccp(size.width/2, size.height*0.42) );
    this->addChild(button_rate);


    CCSprite *bird0_1 = (CCSprite *)sps->objectAtIndex(2);
    CCSprite *bird0_2 = (CCSprite *)sps->objectAtIndex(3);
    CCSprite *bird0_3 = (CCSprite *)sps->objectAtIndex(4);

    CCArray *array= CCArray::create();
    array->addObject(bird0_1->displayFrame());
    array->addObject(bird0_2->displayFrame());
    array->addObject(bird0_3->displayFrame());

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(array,0.08f);

    

    CCSprite* sprite = CCSprite::createWithSpriteFrame(bird0_1->displayFrame());
    sprite->setPosition( ccp( size.width/2, size.height*0.55) );
    sprite->setScale(land->getScale());
    addChild(sprite);
    
    CCAnimate *animate = CCAnimate::create(animation);//这里创建了动画的Action
    CCActionInterval* seq1 = (CCActionInterval*)(CCSequence::create(
                                                                    CCJumpBy::create(1, ccp( 0,20), 15, 1),
                                                                    animate,
                                                                    CCJumpBy::create(1, ccp( 0,-20), -15, 1),
                                                                      animate,
                                                                   NULL) );

    CCAction * play=CCRepeatForever::create(animate);
    CCAction * act = CCSpawn::createWithTwoActions(animate, seq1);

    sprite->runAction(act);

    //执行任务计划，实现背景滚动
    this->schedule(schedule_selector(HelloWorld::backgroundMove),0.008f);

    return true;
}//背景滚动
void HelloWorld::backgroundMove(float dt)
{
    float movePoint = 65;
    land->setPositionX(land->getPositionX()-movePoint);
    land2->setPositionX(land->getPositionX()+land->boundingBox().size.width-movePoint+movePoint);
    if (land2->getPositionX()<land2->boundingBox().size.width/2)
    {
        land->setPositionX(0);
    }
}
CCArray* HelloWorld::GetSpritesWithFile(char * filename){
    std::string fullpath =CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
    unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;

    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "r", &bufferSize);
    std::string pszFilename =CCFileUtils::sharedFileUtils()->fullPathForFilename("atlas.png");
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename.c_str());


    CCString* pRet = CCString::createWithData(pBuffer, bufferSize);
    const char* MyBuffer = pRet->getCString();
    if (pBuffer)
    {
        delete [] pBuffer;
        pBuffer = NULL;
    }

    char *buf = new char[strlen(MyBuffer)+1];
    strcpy(buf, MyBuffer);

    const char *d = "\r\t\n";
    char *p;
    p = strtok(buf,d);
    int count=0;
    std::string strs[71];
    while(p)
    {
        strs[count]=p;
        p=strtok(NULL,d);
        count++;
    }
    CCArray *sps=CCArray::create();
    for (int i=0; i<count; i++) {
        printf("\r=====%i====\r",i);
        sps->addObject(getSprite((char*)strs[i].c_str(),pTexture));
    }
    return sps;
}
CCSprite* HelloWorld::getSprite(char *buf,cocos2d::CCTexture2D *pTexture){


//    printf("bur===%s\r",buf);
    const char *d = " ";
    char *a;
    a = strtok(buf,d);
    int i=0;
    std::string name;
    float x,y,w,h,sw,sh=0;
    while(a)
    {
        i++;
        if ( i==1) {
            name=a;
            printf( "#####%i,%s\r",i,a);
        }
        if (i==2) {
            w=atof(a);
        }
        if (i==3) {
            h=atof(a);
        }
        if (i==4) {
            x=atof(a);
        }
        if (i==5) {
            y=atof(a);
        }
        if (i==6) {
            sw=atof(a);
        }
        if (i==7) {
            sh=atof(a);
        }

        a=strtok(NULL,d);
    }
    CCRect rect=CCRectMake(x*1024, y*1024, w, h);
    CCSprite *sprite=CCSprite::createWithTexture(pTexture, rect);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    sprite->setScale(size.height/512);
    return sprite;
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
