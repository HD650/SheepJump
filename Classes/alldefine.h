#include "cocos2d.h"

#ifndef adlldefineH
#define adlldefineH


//字体
#define TitleFont "MATURASC.TTF"
#define EnglishFont "SHOWG.TTF"
#define ChineseFont "msyhbd.ttf"

//层内Z轴管理
#define GameObject 10
#define GameObjectForward 11
#define GameObjectEffEct 12
#define Land 2
#define BackGround 1
#define GameUI 100

//已经失效
#define LightRange 10

//碰撞体关系管理
#define Collision_Sheep 0x00000001
#define Collision_Wolf 0x00000010
#define Collision_Monster 0x00000100
#define Collision_DeadSheep 0x00000000
#define Collision_Bar 0x00000000
#define Collision_Land 0x10000111


//风，重力管理
#define WorldGravity Vec2(0,-500)
#define WorldWindGravity Vec2(0,250)

//生物物理引擎参数管理
#define JumpImpulse Vec2(0, 520000)
#define DeadJumpImpulse Vec2(100000, 450000)
#define MonsterDeadJumpImpulse Vec2(100000, 500000)
#define DeadTorque -5
#define BrideSpeed 70

//关卡波数管理
#define Wave1 5
#define Wave2 12
#define Wave3 21
#define Wave4 32
#define Wave5 42

//label大小
#define Tech_Waring_Label_Font_Size 25

//动画开始结束管理
#define Walk_Animate 1
#define Jump_Animate 2
#define Dead_Aninate 3
#endif
