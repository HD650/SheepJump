#include "wolf.h"
Wolf* Wolf::createwolf(float speed)
{
	auto temp = new Wolf;
	temp->autorelease();
	temp->initwolf(speed);
	return temp;
}

void Wolf::initwolf(float speed)
{
	Sprite::initWithFile("wolf1.png");
	this->setAnchorPoint(Vec2(0, 0));
	initsprite();
	inittarget();
	speed = speed*0.9;

	auto body = PhysicsBody::createBox(this->getContentSize());
	body->setRotationEnable(false);
	body->setCategoryBitmask(Collision_Wolf);
	body->setCollisionBitmask(Collision_Wolf);
	body->setGravityEnable(false);//为了防止嵌地抖动，只能无视重力，在起跳后，重新打开重力
	this->setPhysicsBody(body);

	this->g_vx = speed;
	this->g_ismove = true;
	this->g_jumped = false;
	this->g_isdead = false;
	this->scheduleUpdate();
	this->setScale(0.7);
	
	Vector<SpriteFrame*> animatedata;
	animatedata.pushBack(SpriteFrame::create("wolf1.png", Rect(0, 0, 125, 89)));
	animatedata.pushBack(SpriteFrame::create("wolf2.png", Rect(0, 0, 125, 89)));
	Animation* animation = Animation::createWithSpriteFrames(animatedata, 1);
	this->walk_animate = Animate::create(animation);
	walk_animate->retain();
	Vector<SpriteFrame*> animatedata2;
	animatedata2.pushBack(SpriteFrame::create("wolf_dead1.png", Rect(0, 0, 125, 89)));
	animatedata2.pushBack(SpriteFrame::create("wolf_dead2.png", Rect(0, 0, 125, 89)));
	Animation* animation2 = Animation::createWithSpriteFrames(animatedata2, 0.3);
	this->dead_animate = Animate::create(animation2);
	dead_animate->retain();

	this->walkanimate();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("wolf.mp3");
	}
}

void Wolf::initsprite()
{
	for (int i = 0; i < 3; i++)
	for (int ii = 0; ii < 3; ii++)
	{
		auto temp = Sprite::create("point.png");
		temp->setAnchorPoint(Vec2(0.5, 0.5));
		temp->setPosition((this->getBoundingBox().size.width / 2 + (ii - 1) * 1.5 * temp->getContentSize().width) - 10,
			(this->getBoundingBox().size.height / 2 + (1 - i) * 1.5 * temp->getContentSize().height));

		temp->retain();
		g_targetnode[i][ii] = temp;
		this->addChild(temp);
		temp->setColor(Color3B(80, 0, 0));

		g_target[i][ii] = false;
	}
}

void Wolf::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->removeFromParent();
	one->g_gamescene->g_sheeplayer->g_wolves->eraseObject(this);
	one->g_gamescene->g_sheeplayer->g_allcreater->eraseObject(this);
	this->dead_animate->release();
	this->walk_animate->release();
	this->release();
}

void Wolf::checkpos()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto bar = one->g_gamescene->g_sheeplayer->g_bar->getBoundingBox();
	if (!g_isdead)
	{
		if (isRightXout())
		{
			one->g_gamescene->changescores(false);
			one->g_gamescene->changescores(false);
			one->g_gamescene->changescores(false);
			one->g_gamescene->changescores(false);
			this->remove();
			return;
		}
		if (isBarcontact(bar))
		{
			one->g_gamescene->changehp(false);
			one->g_gamescene->g_sheeplayer->barshack();
			this->dead();
			return;
		}
	}
	else
	{
		if (isDownYout())
		{
			this->remove();
			return;
		}
	}
}

void Wolf::walkanimate()
{
	auto temp = RepeatForever::create(Spawn::create(this->walk_animate, Sequence::create(EaseExponentialOut::create(RotateBy::create(0.5, 1)),
		EaseExponentialInOut::create(RotateBy::create(1, -2)), EaseBackIn::create(RotateBy::create(0.5, 1)), nullptr), nullptr));
	temp->setTag(Walk_Animate);
	this->runAction(temp);
}

void Wolf::jumpanimate()
{
	this->getActionManager()->removeActionByTag(Walk_Animate, this);
	this->setSpriteFrame(SpriteFrame::create("wolf1.png", Rect(0, 0, 125, 89)));
	/*this->runAction(Sequence::create(EaseElasticOut::create(RotateBy::create(1, Vec3(-20, 0, 0))),
		EaseExponentialIn::create(RotateTo::create(0.5, Vec3(0, 0, 0))), nullptr));*/
	this->runAction(Sequence::create(EaseElasticOut::create(ScaleBy::create(0.3, 0.8, 1.2)), DelayTime::create(0.7),
		EaseExponentialIn::create(ScaleTo::create(0.3, 0.7, 0.7)), nullptr));

	auto pos = this->getPosition();
	pos.y -= this->getBoundingBox().size.height / 2;
	auto smokepart = TextureCache::getInstance()->addImage("jump_paticle.png");
	auto smoke = ParticleMeteor::create();
	smoke->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	smoke->setEndSize(0.5);
	smoke->setScale(2);
	smoke->setScaleY(0.5);
	smoke->setGravity(Vec2(-10, 10));
	smoke->setEmissionRate(50);
	smoke->setDuration(0.5);
	smoke->setLife(0.5);
	smoke->setAngle(270);
	smoke->setPosition(pos);
	this->getParent()->addChild(smoke, GameObjectEffEct);

	this->scheduleOnce([this](float in){if (!this->g_isdead){ this->walkanimate(); } }, 0.4, "returntowalk");

	this->hidetarget();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");
	}
}

void Wolf::deadanimate()
{
	this->getActionManager()->removeAllActionsFromTarget(this);

	auto temp = RepeatForever::create(this->dead_animate);
	temp->setTag(Dead_Aninate);
	this->runAction(temp);

	this->hidetarget();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("wolf_dead.mp3");
	}
}