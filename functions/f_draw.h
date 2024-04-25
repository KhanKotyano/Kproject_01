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
Animation2D CreateAnimation2D(Texture2D *_sprite_sheet, u8 _number_of_sprites, u8 _animation_speed){
  //static u32 id = 0;
  //id++;
  if(_animation_speed > _MAX_ANIMATION_SPEED){
    _animation_speed = _MAX_ANIMATION_SPEED;
  }
  if(_animation_speed < _MIN_ANIMATION_SPEED){
    _animation_speed = _MIN_ANIMATION_SPEED;
  }
  return (Animation2D){
    .animation_speed = _animation_speed,
    .frame_counter = 0,
    .max_frames = (u8)(_number_of_sprites-1),
    .curretnt_frame = 0,
    .color = (Color){255,255,255,255},
    .frame_rectangle = {0.0f, 0.0f, (float)_sprite_sheet->width/_number_of_sprites, (float)_sprite_sheet->height },
    .sprite_sheet = _sprite_sheet
  };

}
Animation2D InheritAnimation2D(Animation2D *_sourse, u8 _animation_speed){
  if(_animation_speed > _MAX_ANIMATION_SPEED){
    _animation_speed = _MAX_ANIMATION_SPEED;
  }
  if(_animation_speed < _MIN_ANIMATION_SPEED){
    _animation_speed = _MIN_ANIMATION_SPEED;
  }
  Animation2D _new_animation = {
    .animation_speed = _animation_speed,
    .frame_counter = 0,
    .max_frames = _sourse->max_frames,
    .curretnt_frame = 0,
    .color = WHITE,
    .frame_rectangle = _sourse->frame_rectangle,
    .sprite_sheet = _sourse->sprite_sheet
  };
  _new_animation.frame_rectangle.x = 0.0f;
  _new_animation.frame_rectangle.y = 0.0f;
  return _new_animation;
}


void DrawAndAnimate(Instance *_inst){
    GetFrameAnimation(&_inst->animation);
    DrawTextureRec(*_inst->animation.sprite_sheet,_inst->animation.frame_rectangle, _inst->pos, _inst->animation.color);
};
void DrawSelf(Instance *self){
  DrawTextureRec(*self->animation.sprite_sheet,self->animation.frame_rectangle, self->pos, self->animation.color);
};
void GetFrameAnimation(Animation2D *_animation){
    _animation->frame_counter++;
    if(_animation->frame_counter >= ((_TARGET_FPS*_ANIMATION_FPS_OFFSET)/_animation->animation_speed)){
        _animation->frame_counter = 0;
        _animation->curretnt_frame++;
        if (_animation->curretnt_frame > _animation->max_frames) {_animation->curretnt_frame = 0;}
        _animation->frame_rectangle.x = (float)_animation->curretnt_frame*(float)_animation->sprite_sheet->width/(_animation->max_frames+1);
    }
};

void DrawAnimation(Animation2D *_animation, Vector2 _pos){
    GetFrameAnimation(_animation);
    //Color _temp_col = WHITE;
    DrawTextureRec(*_animation->sprite_sheet,_animation->frame_rectangle, _pos, _animation->color);
    #if true
      _animation->color = WHITE;
    #endif
}