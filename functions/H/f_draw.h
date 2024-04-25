#ifndef KDRAW
#define KDRAW
#include "functions.h"
Animation2D CreateAnimation2D(Texture2D *_sprite_sheet, u8 _number_of_sprites, u8 _animation_speed);
Animation2D InheritAnimation2D(Animation2D *_sourse, u8 _animation_speed);


void DrawAndAnimate(Instance *_inst);

void DrawAnimation(Animation2D *_animation, Vector2 _pos);
#include "f_draw.c"
#endif