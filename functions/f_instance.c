#include "functions.h"

Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Animation2D *_animation){
  static u32 id = 0;
  id++;
  return (Instance){
    .ID = id,
    .active = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0,
    //ANIMATION THING: TODO: MAYBE REMOVE TO A SEPARATE STRUCT
    //.animation_speed = 8,
    //.frame_counter = 0,
    //.max_frames = 5,
    //.curretnt_frame = 0,
    //.frame_rectangle = {0.0f, 0.0f, (float)_sprite->width/6, (float)_sprite->height },
    .animation = *_animation,
  };
};
void AddInstance( Vector2 _position, Instance *_inst_array, Texture2D *_sprite, Animation2D *_animation){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(_inst_array[i].active){
      continue;
    }
    _inst_array[i] = CreateInstance(_position, _sprite, _animation);
    return;
  };
}
void UpdateInstances(Instance *_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(!_inst_array[i].active){
      continue;
    }
    //PlayerIvent(_inst_array[i]);
  };

};
void UpdateDrawInstances(Instance *_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(!_inst_array[i].active){
      
      continue;
    }
    DrawTextureEx(*_inst_array[i].sprite, _inst_array[i].pos, _inst_array[i].angle, _inst_array[i].scale, WHITE);
  };
}
void UpdateAnimateInstances(Instance *_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(!_inst_array[i].active){
      
      continue;
    }
    DrawAndAnimate(&_inst_array[i]);
  };
}

int PlayerIvent(Instance &self){
  if(IsKeyDown(KEY_UP)){
    self.pos.y -= 1;
    //self.scale -= 0.005f;
  }
  if(IsKeyDown(KEY_DOWN)){
    self.pos.y += 1;
   // self.scale += 0.005f;
  }
  if(IsKeyDown(KEY_LEFT)){
    self.pos.x -= 1;
  }
  if(IsKeyDown(KEY_RIGHT)){
    self.pos.x  += 1;
  }
  if (IsKeyDown(KEY_A)) self.angle--;
  else if (IsKeyDown(KEY_S)) self.angle++;
  return 1;
};