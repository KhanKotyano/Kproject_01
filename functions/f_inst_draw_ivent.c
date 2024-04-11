#include "functions.h"
void PlayerMainDraw(Instance *self){
    DrawText(TextFormat("%g",self->pos.y), self->pos.x, self->pos.y - 8, 8, BLACK);
    DrawText(TextFormat("%g",self->pos.x), self->pos.x , self->pos.y- 16, 8, BLACK);
};
void PlayerMainDrawGui(Instance *self){
    DrawText(TextFormat("%i", self->animation.curretnt_frame), 40,4,24,RED);
};