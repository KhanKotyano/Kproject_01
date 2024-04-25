#ifndef KCOMMON_F
#define KCOMMON_F
#include "functions.h"
custom_pointer SetCustomPointer(void *pointer, unsigned char _pointer_type);
void *GetCustomPointer(custom_pointer *_custom_ptr);
//Memory Unsafe???
char* FloatToString( float recast );
//Memory Unsafe???
char* IntToString( int recast );

typedef struct _target {
  int index;
  int value;

} _target;

void swap(int* arr, int i, int j);
void qswap(int *a, int *b) ;
int partition(int array[], int low, int high) ;
int TargetPartition(int array[], int target[], int low, int high) ;


void quickSort(int array[], int low, int high) ;
void TargetQsort(int array[], int low, int high, int _target_a[]) ;
void TargetBubbleSort(int arr[], int _target_a[], int n);

Grid2D CreateGrid2D(unsigned int _width, unsigned int _height);

CellGrid2D CreateCellGrid2D(unsigned int _width, unsigned int _height);
Cell GetGridOnHover(Vector2 _mouse_world_pos, GridVector2D *_grid_on_hover_pos, CellGrid2D *cell_grid, GridVector2D WorldGrid , Cell *cell_on_hover);
#include "f_common.c"
#endif