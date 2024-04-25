#ifndef KINSTANCE_F
#define KINSTANCE_F
#include "functions.h"
#include <stdlib.h>
Instance CreateInstanceType(Vector2 _position, Animation2D *_animation, u16 _type, PointerArray *global_pointer_array);

Instance CreateInstance(Vector2 _position, Animation2D *_animation);
Instance CreateInstanceEXT(Vector2 _position, Animation2D *_animation,void (**_function_array)(Instance*), int _f_size);



Instance InheritInstance(Instance *_inst, Vector2 _new_pos);

void AddInstance( Vector2 _position, InstanceArray *a, Animation2D *_animation);

int AddInstanceType( PointerArray *global_pointer_array,Vector2 _position, InstanceArray *a, Animation2D *_animation, u16 _type);
void NewInstance( PointerArray *global_pointer_array,Vector2 _position, InstanceArray *a, Animation2D *_animation, u16 _type);


void InstanceDestroy(Instance* _inst);


void UpdateInstances(InstanceArray *_inst_a, custom_pointer *global_ptr);


int GetDrawingOrder(Instance *_inst_a, int *order_array, size_t _used_size);

void UpdateDrawInstances(InstanceArray *_inst_a, custom_pointer *global_prt);
void UpdateDrawGUIInstances(InstanceArray *_inst_a, custom_pointer *global_prt);
void UpdateDrawCells(CellGrid2D *cell_grid);
#include "f_instance.c"
#endif