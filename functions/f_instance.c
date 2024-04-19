#include "functions.h"
//#include <stdlib.h>
Instance CreateInstanceType(Vector2 _position, Animation2D *_animation, u16 _type){
  static u32 id = _INSTANCE_ID;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  switch(_type){
    case NOTHING:{
      _new_instance.depth = 0;
    }break;
    case PLAYER:{
      _new_instance.depth = 45;
      //_new_instance.f_test_main = &OtherPlayerMain;
    }break;
    case ENEMY:{
      _new_instance.depth = GetRandomValue(1, 100) ;
    }break;
  }
  AssignFunction(&_new_instance.f_main, _type);
  AssignDrawFunction(&_new_instance.f_draw, _type);
  AssignDrawGUIFunction(&_new_instance.f_drawGUI, _type);
  id++;
  return _new_instance;
};

Instance CreateInstance(Vector2 _position, Animation2D *_animation){
  static u32 id = _INSTANCE_ID;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  id++;
  return _new_instance;
};

Instance CreateInstanceEXT(Vector2 _position, Animation2D *_animation
                          ,void (**_function_array)(Instance*), int _f_size){
  static u32 id = _INSTANCE_ID;
  Instance _new_instance = {
    .ID = id,
    .exist = true,
    .pos = _position,
    .scale = 1,
    .angle = 0,
    .animation = InheritAnimation2D(_animation, _animation->animation_speed ),
  };
  
  id++;
  return _new_instance;
};





Instance InheritInstance(Instance *_inst, Vector2 _new_pos){
  Instance _new_instance = CreateInstance(_inst->pos,  &_inst->animation);
  _new_instance.scale = _inst->scale;
  _new_instance.angle = _inst->angle;
  return _new_instance;
}
void AddInstance( Vector2 _position, InstanceArray *a, Animation2D *_animation){
  Instance _inst = CreateInstance(_position, _animation);
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
void AddInstanceType( Vector2 _position, InstanceArray *a, Animation2D *_animation, u16 _type){
  Instance _inst = CreateInstanceType(_position, _animation, _type);
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


void UpdateInstances(InstanceArray *_inst_a, custom_pointer *global_prt){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_main(_cur_inst, global_prt);
  };

};


int GetDrawingOrder(Instance *_inst_a, int *order_array, size_t _used_size){ 
  int _depth_array[_used_size];
  for(int i = 0;i < (int)_used_size;i++){
    order_array[i] = i;
  }
  for(int i = 0;i < (int)_used_size;i++){
    _depth_array[i] = _inst_a[i].depth;
  }
  TargetQsort(_depth_array, 0, (int)_used_size - 1, order_array);
  //TargetBubbleSort(_depth_array, order_array, (int)_used_size);
  /*
  for(int i = 0;i < (int)_used_size;i++){
    printf("Order: %d \n", order_array[i]);
  }
  for(int i = 0;i < (int)_used_size;i++){
    printf("Depth: %d \n", _depth_array[i]);
  }
  exit(0);
  */
  return 0;
};

void UpdateDrawInstances(InstanceArray *_inst_a, custom_pointer *global_prt){
  size_t _used_size = (size_t)_inst_a->used;
  int _order_array[_used_size];
  GetDrawingOrder(_inst_a->array, _order_array, _used_size);

  for(unsigned int i = 0;i<_used_size;i++){
    //printf("%d \n",_order_array[i]);
    Instance *_cur_inst = &_inst_a->array[_order_array[i]];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_draw(_cur_inst, global_prt);
  }
  //exit(0);
};
void UpdateDrawGUIInstances(InstanceArray *_inst_a, custom_pointer *global_prt){
  size_t _used_size = (size_t)_inst_a->used;
  for(unsigned int i = 0;i<_used_size;i++){
    Instance *_cur_inst = &_inst_a->array[i];
    if(!_cur_inst->exist){
      continue;
    }
    _cur_inst->f_drawGUI(_cur_inst, global_prt);
  };
};
void UpdateDrawCells(CellGrid2D *cell_grid){
  for(u32 h = 0;h<cell_grid->height;h++){
    for(u32 w = 0;w<cell_grid->width;w++){
      Cell *_cur_cell = &cell_grid->grid[h][w];
      if(!_cur_cell->exist){
      continue;
      }
      DrawTexture(*_cur_cell->static_sprite, PIXEL_SIZE * w,PIXEL_SIZE * h, WHITE);
    }
  }
}

