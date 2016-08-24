#include "monster.h"

Monster* Monster::createmonster(float speed)
{
	auto temp = new Monster;
	temp->autorelease();
	temp->initmonster(speed);
	return temp;
}

void Monster::initmonster(float speed)
{
	Sprite::initWithFile("monster1.png");
	this->setAnchorPoint(Vec2(0, 0));
	speed = speed*0.6;

	auto body = PhysicsBody::createBox(this->getContentSize());
	body->setRotationEnable(false);
	body->setCategoryBitmask(Collision_Monster);
	body->setCollisionBitmask(Collision_Monster);
	body->setGravityEnable(false);//为了防止嵌地抖动，只能无视重力，在起跳后，重新打开重力
	this->setPhysicsBody(body);

	this->g_vx = speed;
	this->g_ismove = true;
	this->g_jumped = false;
	this->g_isdead = false;
	this->scheduleUpdate();
	this->setScaleY(0.9);
	this->setScaleX(0.8);

	Vector<SpriteFrame*> animatedata;
	animatedata.pushBack(SpriteFrame::create("monster1.png", Rect(0, 0, 125, 139)));
	animatedata.pushBack(SpriteFrame::create("monster2.png", Rect(0, 0, 125, 139)));
	Animation* animation = Animation::createWithSpriteFrames(animatedata, 1);
	this->walk_animate = Animate::create(animation);
	walk_animate->retain();
	Vector<SpriteFrame*> animatedata2;
	animatedata2.pushBack(SpriteFrame::create("monster_dead1.png", Rect(0, 0, 125, 157)));
	animatedata2.pushBack(SpriteFrame::create("monster_dead2.png", Rect(0, 0, 125, 157)));
	Animation* animation2 = Animation::createWithSpriteFrames(animatedata2, 0.3);
	this->dead_animate = Animate::create(animation2);
	dead_animate->retain();

	this->walkanimate();

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("monster.mp3");
	}
}

void Monster::remove()
{
	auto one = (AppDelegate*)Application::getInstance();
	this->removeFromParent();
	one->g_gamescene->g_sheeplayer->g_monster->eraseObject(this);
	one->g_gamescene->g_sheeplayer->g_allcreater->eraseObject(this);
	this->dead_animate->release();
	this->walk_animate->release();
	this->release();
}

void Monster::checkpos()
{
	auto one = (AppDelegate*)Application::getInstance();
	auto bar = one->g_gamescene->g_sheeplayer->g_bar->getBoundingBox();
	if (!g_isdead)
	{
		if (isRightXout())
		{
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			this->remove();
			return;
		}
		if (isBarcontact(bar))
		{
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->changehp(false);
			one->g_gamescene->g_sheeplayer->barbreak();
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

void Monster::dead()
{
	this->deadanimate();

	this->getPhysicsBody()->setGravityEnable(true);
	this->getPhysicsBody()->setRotationEnable(true);
	this->getPhysicsBody()->setCollisionBitmask(Collision_DeadSheep);
	this->getPhysicsBody()->applyImpulse(MonsterDeadJumpImpulse);
	this->getPhysicsBody()->setAngularVelocity(DeadTorque);
	this->g_ismove = false;
	this->g_isdead = true;
}

void Monster::walkanimate()
{
	auto temp = RepeatForever::create(Spawn::create(this->walk_animate, Sequence::create(EaseExponentialOut::create(RotateBy::create(0.5, 1)),
		EaseExponentialInOut::create(RotateBy::create(1, -2)), EaseBackIn::create(RotateBy::create(0.5, 1)), nullptr), nullptr));
	temp->setTag(Walk_Animate);
	this->runAction(temp);
}

void Monster::jumpanimate()
{
	this->getActionManager()->removeActionByTag(Walk_Animate, this);

}

void Monster::deadanimate()
{
	this->getActionManager()->removeAllActionsFromTarget(this);
	auto temp = RepeatForever::create(this->dead_animate);
	temp->setTag(Dead_Aninate);
	this->runAction(temp);

	if (UserDefault::getInstance()->getBoolForKey("BGM", true))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("monster_dead.mp3");
	}
}