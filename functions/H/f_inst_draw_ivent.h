#ifndef KDRAW_IVENT
#define KDRAW_IVENT
#include "functions.h"
void SolderMainDraw(Instance *self, custom_pointer *global_pointer_array);
void SolderMainDrawGui(Instance *self, custom_pointer *global_pointer_array);
void AssignDrawGUIFunction(void(**function)(Instance*, custom_pointer*), u16 _type);
void AssignDrawFunction(void(**function)(Instance*, custom_pointer*), u16 _type);
#include "f_instance.c"
#endif