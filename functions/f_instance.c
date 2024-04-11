#include "functions.h"
void AssignFunction(void(**function)(Instance*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &PlayerMain;
    }break;
    case ENEMY:{
      *function = &DumpFunction;
    }break;
    default:{
      *function = &DumpFunction;
    }break;
  }
  
};
void AssignDrawFunction(void(**function)(Instance*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &DrawAndAnimate;
      
    }break;
    case ENEMY:{
      *function = &DrawAndAnimate;
      
    }break;
    default:{
      *function = &DumpFunction;
    }
  }
};
Instance CreateInstanceType(Vector2 _position, Texture2D *_sprite, Animation2D *_animation, u16 _type){
  static u32 id = _INSTANCE_ID;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  AssignFunction(&_new_instance.f_main, _type);
  AssignDrawFunction(&_new_instance.f_draw, _type);
  id++;
  return _new_instance;
};

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
  
  id++;
  return _new_instance;
};
void DrawSelf(Instance *self){
  DrawTextureEx(*self->sprite, self->pos, self->angle,self->scale, WHITE);
};
Instance CreateInstanceEXT(Vector2 _position, Texture2D *_sprite, Animation2D *_animation
                          ,void (**_function_array)(Instance*), int _f_size){
  static u32 id = _INSTANCE_ID;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  
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
void AddInstanceType( Vector2 _position, InstanceArray *a, Texture2D *_sprite, Animation2D *_animation, u16 _type){
  Instance _inst = CreateInstanceType(_position, _sprite, _animation, _type);
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


void InstanceDestroy(Instance* _inst){
  //free(_inst->f_main);
  //free(_inst->f_draw);
  //free(_inst->f_drawGUI);
  _inst = {0};
}


void UpdateInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_main(_cur_inst);
  };

};
void UpdateDrawInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_draw(_cur_inst);
  };
}
void UpdateDrawGUIInstances(InstanceArray *_inst_a){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_drawGUI(_cur_inst);
  };
}
