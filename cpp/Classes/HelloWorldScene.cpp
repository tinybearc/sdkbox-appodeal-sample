#include "HelloWorldScene.h"
#include "PluginAppodeal/PluginAppodeal.h"

USING_NS_CC;

class ADListener : public sdkbox::AppodealListener {
public:
    virtual void onBannerDidLoadAd();
    virtual void onBannerDidFailToLoadAd();
    virtual void onBannerDidClick();
    virtual void onBannerPresent();

    virtual void onInterstitialDidLoadAd();
    virtual void onInterstitialDidFailToLoadAd();
    virtual void onInterstitialWillPresent();
    virtual void onInterstitialDidDismiss();
    virtual void onInterstitialDidClick();

    virtual void onVideoDidLoadAd();
    virtual void onVideoDidFailToLoadAd();
    virtual void onVideoDidPresent();
    virtual void onVideoWillDismiss();
    virtual void onVideoDidFinish();

    virtual void onRewardVideoDidLoadAd();
    virtual void onRewardVideoDidFailToLoadAd();
    virtual void onRewardVideoDidPresent();
    virtual void onRewardVideoWillDismiss();
    virtual void onRewardVideoDidFinish(int amount, const std::string& name);
};

void ADListener::onBannerDidLoadAd() {
    CCLOG("Listener onBannerDidLoadAd");
}
void ADListener::onBannerDidFailToLoadAd() {
    CCLOG("Listener onBannerDidFailToLoadAd");
}
void ADListener::onBannerDidClick() {
    CCLOG("Listener onBannerDidClick");
}
void ADListener::onBannerPresent() {
    CCLOG("Listener onBannerPresent");
}

void ADListener::onInterstitialDidLoadAd() {
    CCLOG("Listener onInterstitialDidLoadAd");
}
void ADListener::onInterstitialDidFailToLoadAd() {
    CCLOG("Listener onInterstitialDidFailToLoadAd");
}
void ADListener::onInterstitialWillPresent() {
    CCLOG("Listener onInterstitialWillPresent");
}
void ADListener::onInterstitialDidDismiss() {
    CCLOG("Listener onInterstitialDidDismiss");
}
void ADListener::onInterstitialDidClick() {
    CCLOG("Listener onInterstitialDidClick");
}

void ADListener::onVideoDidLoadAd() {
    CCLOG("Listener onVideoDidLoadAd");
}
void ADListener::onVideoDidFailToLoadAd() {
    CCLOG("Listener onVideoDidFailToLoadAd");
}
void ADListener::onVideoDidPresent() {
    CCLOG("Listener onVideoDidPresent");
}
void ADListener::onVideoWillDismiss() {
    CCLOG("Listener onVideoWillDismiss");
}
void ADListener::onVideoDidFinish() {
    CCLOG("Listener onVideoDidFinish");
}

void ADListener::onRewardVideoDidLoadAd() {
    CCLOG("Listener onRewardVideoDidLoadAd");
}
void ADListener::onRewardVideoDidFailToLoadAd() {
    CCLOG("Listener onRewardVideoDidFailToLoadAd");
}
void ADListener::onRewardVideoDidPresent() {
    CCLOG("Listener onRewardVideoDidPresent");
}
void ADListener::onRewardVideoWillDismiss() {
    CCLOG("Listener onRewardVideoWillDismiss");
}
void ADListener::onRewardVideoDidFinish(int amount, const std::string& name) {
    CCLOG("Listener onRewardVideoDidFinish %d : %s", amount, name.c_str());
}


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Appodeal Sample", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    
    Menu* list = Menu::create(
                              MenuItemFont::create("Show Ad", CC_CALLBACK_1(HelloWorld::onButton1Click, this)),
                              NULL);
    list->alignItemsVerticallyWithPadding(5);
    list->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(list);
    
	sdkbox::PluginAppodeal::setListener(new ADListener());
    sdkbox::PluginAppodeal::init();

    sdkbox::PluginAppodeal::setDebugEnabled(true);
    sdkbox::PluginAppodeal::setUserVkId("user id");
    sdkbox::PluginAppodeal::setUserFacebookId("facebook id");
    sdkbox::PluginAppodeal::setUserEmail("test@sdkbox.com");
    sdkbox::PluginAppodeal::setUserBirthday("11/11/1999"); //DD/MM/YYYY
    sdkbox::PluginAppodeal::setUserAge(11);
    sdkbox::PluginAppodeal::setUserGender(sdkbox::PluginAppodeal::Gender::AppodealUserGenderMale);
    sdkbox::PluginAppodeal::setUserOccupation(sdkbox::PluginAppodeal::Occupation::AppodealUserOccupationSchool);
    sdkbox::PluginAppodeal::setUserRelationship(sdkbox::PluginAppodeal::Relationship::AppodealUserRelationshipSingle);
    sdkbox::PluginAppodeal::setUserSmokingAttitude(sdkbox::PluginAppodeal::SmokingAttitude::AppodealUserSmokingAttitudeNegative);
    sdkbox::PluginAppodeal::setUserAlcoholAttitude(sdkbox::PluginAppodeal::AlcoholAttitude::AppodealUserAlcoholAttitudeNegative);
    sdkbox::PluginAppodeal::setUserInterests("game");

    sdkbox::PluginAppodeal::cacheAd(sdkbox::PluginAppodeal::AdType::AppodealAdTypeAll);
	
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onButton1Click(Ref *sender) {
    CCLOG("Button1 Click");
    sdkbox::PluginAppodeal::showAd(sdkbox::PluginAppodeal::ShowStyle::AppodealShowStyleInterstitial);
//    if (sdkbox::PluginAppodeal::isReadyForShowWithStyle(sdkbox::PluginAppodeal::ShowStyle::AppodealShowStyleBannerBottom)) {
//        sdkbox::PluginAppodeal::showAd(sdkbox::PluginAppodeal::ShowStyle::AppodealShowStyleBannerBottom);
//    } else {
//        CCLOG("not ready for show");
//    }
}

void HelloWorld::onButton2Click(Ref *sender) {
    sdkbox::PluginAppodeal::hideBanner();
    CCLOG("Button2 Click");
}

