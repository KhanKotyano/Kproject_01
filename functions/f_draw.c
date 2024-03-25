#include "functions.h"
/*void GetCurrentFrame(Instance *_inst){
    _inst->frame_counter++;
    if(_inst->frame_counter >= (_TARGET_FPS/_inst->animation_speed)){
        _inst->frame_counter = 0;
        _inst->curretnt_frame++;
        if (_inst->curretnt_frame > _inst->max_frames) {_inst->curretnt_frame = 0;}
        _inst->frame_rectangle.x = (float)_inst->curretnt_frame*(float)_inst->sprite->width/(_inst->max_frames+1);
    }
};*/
Animation2D CreateAnimation2D(Texture2D *_sprite_sheet){
  static u32 id = 0;
  id++;
  return (Animation2D){
    //ANIMATION THING: TODO: MAYBE REMOVE TO A SEPARATE STRUCT
    .animation_speed = 8,
    .frame_counter = 0,
    .max_frames = 5,
    .curretnt_frame = 0,
    .frame_rectangle = {0.0f, 0.0f, (float)_sprite_sheet->width/6, (float)_sprite_sheet->height },
    .sprite_sheet = _sprite_sheet
  };

}

void DrawAndAnimate(Instance *_inst){
    GetFrameAnimation(&_inst->animation);
    //GetCurrentFrame(_inst);
    //Texture2D *_temp = _inst->sprite;
    DrawTextureRec(*_inst->animation.sprite_sheet,_inst->animation.frame_rectangle, _inst->pos, (Color){255,255,255,255});
};

void GetFrameAnimation(Animation2D *_animation){
    _animation->frame_counter++;
    if(_animation->frame_counter >= (_TARGET_FPS/_animation->animation_speed)){
        _animation->frame_counter = 0;
        _animation->curretnt_frame++;
        if (_animation->curretnt_frame > _animation->max_frames) {_animation->curretnt_frame = 0;}
        _animation->frame_rectangle.x = (float)_animation->curretnt_frame*(float)_animation->sprite_sheet->width/(_animation->max_frames+1);
    }
};

void DrawAnimation(Animation2D *_animation, Vector2 _pos){
    GetFrameAnimation(_animation);
    //Texture2D *_temp = _inst->sprite;
    DrawTextureRec(*_animation->sprite_sheet,_animation->frame_rectangle, _pos, (Color){255,255,255,255});
}