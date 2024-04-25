#ifndef KINST_STEP_IVENT
#define KINST_STEP_IVENT
#include "functions.h"
void SolderMain(Instance *self, custom_pointer *global_pointer_array);
void SolderCreate(Instance *self, custom_pointer *global_pointer_array);
void EnemyMainIvent(Instance *self, custom_pointer*);
void DumpFunction(Instance *self, custom_pointer*);

void AssignFunction(void(**function)(Instance*, custom_pointer*), u16 _type);
void AssignCreateFunction(void(**function)(Instance*, custom_pointer*), u16 _type);
#include "f_inst_step_ivent.c"
#endif
