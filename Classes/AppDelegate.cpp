#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("SheepMagicka", Rect(0, 0, 360, 640));
        director->setOpenGLView(glview);
    }

	director->getOpenGLView()->setDesignResolutionSize(360, 640, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
	FileUtils::getInstance()->addSearchPath("back");
	FileUtils::getInstance()->addSearchPath("else");
	FileUtils::getInstance()->addSearchPath("menu");
	FileUtils::getInstance()->addSearchPath("sprite");
	FileUtils::getInstance()->addSearchPath("text");
	FileUtils::getInstance()->addSearchPath("sound");
	FileUtils::getInstance()->addSearchPath("font");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Horns.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Dark Rock.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Thin.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("beat.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("birde.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("birde_fly.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("monster.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("monster_dead.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sheep.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sheep_dead.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wolf.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wolf_dead.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("lighting.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("wind.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("change.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jump.mp3");

    // create a scene. it's an autorelease object
    //auto scene = GameScene::creategamescene();
	auto scene = MainMenu::createmainmenu();
	 g_mainmenu = scene;

    // run
    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
