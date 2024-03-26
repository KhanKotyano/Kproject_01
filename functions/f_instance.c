#include "functions.h"

Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Animation2D *_animation){
  //static u32 id = 0;
  //id++;
  
  Instance _new_instance = {
    //.ID = id,
    .active = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0,
    .animation = *_animation,
  };
  //Instance *_new_ptr = &_new_instance;
  //_new_instance.ID = _new_ptr;
  return _new_instance;
};
Instance InheritInstance(Instance *_inst, Vector2 _new_pos){
  Instance _new_instance = {
    //.ID = _inst->ID << 24,
    .active = _inst->active,
    .pos = _new_pos,
    .sprite = _inst->sprite,
    .scale = _inst->scale,
    .angle = _inst->angle,
    .animation = _inst->animation,
  };
  //Instance *_new_ptr = &_new_instance;
  //_new_instance.ID = _new_ptr;
  return _new_instance;
}
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
    DrawText(IntToString(_inst_array[i].animation.curretnt_frame), _inst_array[i].pos.x, _inst_array[i].pos.y, 8, RED);
  };
}

/*void TestUpdateAnimateInstances(Instance **_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(_inst_array[i] == nullptr){
    
      continue;
    }
    DrawAndAnimate(_inst_array[i]);
  };
}
void AddInstancePointer( Instance *_inst, Instance **_inst_array, Vector2 _new_pos){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(_inst_array[i] != nullptr){
      continue;
    }
    static Instance* _instance = (Instance*)malloc(sizeof(Instance));
    _instance = &CreateInstance(_new_pos, _inst->sprite, &_inst->animation);
    _inst_array[i] = _instance;
    return;
  };
}*/
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