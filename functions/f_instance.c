#include "functions.h"

Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Animation2D *_animation){
  static u32 id = _INSTANCE_ID;
  //id << 32;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  //Instance *_new_ptr = &_new_instance;
  //_new_instance.ID = _new_ptr;
  id++;
  return _new_instance;
};
Instance InheritInstance(Instance *_inst, Vector2 _new_pos){
  Instance _new_instance = CreateInstance(_inst->pos, _inst->sprite, &_inst->animation);
  _new_instance.scale = _inst->scale;
  _new_instance.angle = _inst->angle;
  //Instance *_new_ptr = &_new_instance;
  //_new_instance.ID = _new_ptr;
  return _new_instance;
}
void AddInstance( Vector2 _position, InstanceArray *a, Texture2D *_sprite, Animation2D *_animation){
  Instance _inst = CreateInstance(_position, _sprite, _animation);
  //ArrayPushInstance(_inst_array, _inst);
  if (a->used == a->size) {
    //TODO: Maybe do it as separate check/function. Rn, it not optimal solution
    if(a->size < _MAX_INSTANCES){
      a->size *= 2;
      a->array = (Instance*)realloc(a->array, a->size * sizeof(Instance));
      EmptyInstanceArray(a, a->used);
      printf("New memory allocated to the instance array\n");
    } else {
      int _free_index = FindEmptyInstance(a->array, 0, (s32)a->used);
      if(_free_index != -1){
          a->array[_free_index] = _inst;
          return;
      } else {
        a->size *= 2;
        a->array = (Instance*)realloc(a->array, a->size * sizeof(Instance));
        EmptyInstanceArray(a, a->used);
        printf("New memory allocated to the instance array\n");
      }
    }
  } 
  a->array[a->used++] = _inst;
  //a->array[a->used-1].ID = a->used;
  _inst = {NULL};
}

void UpdateInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    //PlayerIvent(_inst_array[i]);
  };

};
void UpdateDrawInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }

    DrawTextureEx(*_cur_inst->sprite, _cur_inst->pos, _cur_inst->angle, _cur_inst->scale, WHITE);

  };
}
void UpdateAnimateInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      
      continue;
    }
    DrawAndAnimate(_cur_inst);
    DrawText(TextFormat("%i", _cur_inst->animation.curretnt_frame), _cur_inst->pos.x, _cur_inst->pos.y, 8, RED);
    DrawText(TextFormat("%i",_cur_inst->ID - _INSTANCE_ID), _cur_inst->pos.x +16, _cur_inst->pos.y, 8, GREEN);
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