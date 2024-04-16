#include "functions.h"

//Memory Unsafe???
char* FloatToString( float recast ){
  int length = snprintf( NULL, 0, "%g", recast ); 
  char *str = (char*)malloc( length + 1 );
  snprintf( str, length + 1, "%g", recast );
  return str;
}
//Memory Unsafe???
char* IntToString( int recast ){
  int length = snprintf( NULL, 0, "%d", recast ); 
  char *str = (char*)malloc( length + 1 );
  snprintf( str, length + 1, "%d", recast );
  return str;
}

typedef struct _target {
  int index;
  int value;

} _target;

void swap(int* arr, int i, int j){
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
void qswap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      qswap(&array[i], &array[j]);
    }
  }
  qswap(&array[i + 1], &array[high]);
  return (i + 1);
}
int TargetPartition(int array[], int target[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      qswap(&target[i], &target[j]);
      qswap(&array[i], &array[j]);
    }
  }
  qswap(&target[i + 1], &target[high]);
  qswap(&array[i + 1], &array[high]);
  return (i + 1);
}


void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}
void TargetQsort(int array[], int low, int high, int _target_a[]) {
  if (low < high) {
    int pi = TargetPartition(array, _target_a, low, high);
    TargetQsort(array, low, pi - 1, _target_a);
    TargetQsort(array, pi + 1, high, _target_a);
  }
}
void TargetBubbleSort(int arr[], int _target_a[], int n){
  int i, j;
  for (i = 0; i < n - 1; i++){
    for (j = 0; j < n - i - 1; j++){
      if (arr[j] > arr[j + 1]){
        swap(arr, j, j + 1);
        swap(_target_a, j, j + 1);
      }
    }
  }
}

Grid2D CreateGrid2D(unsigned int _width, unsigned int _height){
  printf("Start Creation\n");
  Grid2D _temp_grid2d = {
    .width = _width,
    .height = _height,
  };
  //printf("Created Grid\n");
  unsigned int **temp_gridgrid = (unsigned int **)malloc(sizeof(unsigned int **) * _height);
  //printf("Allocated TempGrid\n");
  for(unsigned int i = 0; i < _width;i++){
    unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int) * _height);
    temp_gridgrid[i] = a;
  }
  //printf("Assign TempGrid \n");
  _temp_grid2d.grid = temp_gridgrid;
  //printf("Assign TempGrid to Grid\n");
  //_temp_grid2d.grid[1][1] = 15;
  //printf("expected val:%d | test val:%d\n", 15,temp_gridgrid[1][1]);
  unsigned int j = 0;
  for(unsigned int i = 0; i < _width;i++){
    for(unsigned int ii = 0; ii < _height;ii++){
      j++;
      _temp_grid2d.grid[i][ii] = j;
      #if DEBUG_MODE
        printf("x:%d y:%d value:%d \n", i , ii, _temp_grid2d.grid[i][ii]);
      #endif
    }
  }
  printf("Grid Created Successfully\n");
  return _temp_grid2d;
}

CellGrid2D CreateCellGrid2D(unsigned int _width, unsigned int _height){
  printf("Start Creation\n");
  CellGrid2D _temp_grid2d = {
    .width = _width,
    .height = _height,
  };
  Cell **temp_gridgrid = (Cell **)malloc(sizeof(Cell **) * _height);
  for(unsigned int i = 0; i < _width;i++){
    Cell *a = (Cell*)malloc(sizeof(Cell) * _height);
    temp_gridgrid[i] = a;
  }
  _temp_grid2d.grid = temp_gridgrid;
  
  //_temp_grid2d.grid[1][1].grid_pos = (GridVector2D){15,15};
  //printf("expected val:%d | test val:%d\n", 15,temp_gridgrid[1][1].grid_pos.x);
  unsigned int j = 0;
  for(unsigned int i = 0; i < _width;i++){
    for(unsigned int ii = 0; ii < _height;ii++){
      j++;
      _temp_grid2d.grid[i][ii].grid_pos = (GridVector2D){i, ii};
      #if DEBUG_MODE
        printf("x:%d y:%d pos:%d,%d \n", i , ii, _temp_grid2d.grid[i][ii].grid_pos.x,_temp_grid2d.grid[i][ii].grid_pos.y);
      #endif
    }
  }  
  printf("Grid Created Successfully\n");
  return _temp_grid2d;
}