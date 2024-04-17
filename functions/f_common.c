#include "functions.h"
custom_pointer SetCustomPointer(void *pointer, unsigned char _pointer_type){
  custom_pointer _custom_ptr ;
  switch (_pointer_type){
  case PT_VOID:{
    _custom_ptr.p_void = (void*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_INT:{
    _custom_ptr.p_int =(int*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_UINT:{
    _custom_ptr.p_uint = (unsigned int*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_UCHAR:{
    _custom_ptr.p_uchar = (unsigned char*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_CHAR:{
    _custom_ptr.p_char =(char*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_FLOAT:{
    _custom_ptr.p_float =(float*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_DOUBLE:{
    _custom_ptr.p_double = (double*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_CAMERA:{
    _custom_ptr.p_camera = (CameraInstance2D*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_INST_ARRAY:{
    _custom_ptr.p_inst_array = (InstanceArray*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_CELL:{
    _custom_ptr.p_cell = (Cell*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  case PT_VECTOR2:{
    _custom_ptr.p_vector2D = (Vector2*)pointer;
    _custom_ptr.pointer_type = _pointer_type;
  }break;
  default:{
  
  }break;
  }
  return _custom_ptr;
}
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
  for(unsigned int i = 0; i < _height;i++){
    unsigned int *a = (unsigned int*)malloc(sizeof(unsigned int) * _width);
    temp_gridgrid[i] = a;
  }
  //printf("Assign TempGrid \n");
  _temp_grid2d.grid = temp_gridgrid;
  //printf("Assign TempGrid to Grid\n");
  //_temp_grid2d.grid[1][1] = 15;
  //printf("expected val:%d | test val:%d\n", 15,temp_gridgrid[1][1]);
  unsigned int j = 0;
  for(unsigned int i = 0; i < _height;i++){
    for(unsigned int ii = 0; ii < _width;ii++){
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
  for(unsigned int h = 0; h < _height;h++){
    Cell *a = (Cell*)malloc(sizeof(Cell) * _width);
    temp_gridgrid[h] = a;
  }
  _temp_grid2d.grid = temp_gridgrid;
  
  //_temp_grid2d.grid[1][1].grid_pos = (GridVector2D){15,15};
  //printf("expected val:%d | test val:%d\n", 15,temp_gridgrid[1][1].grid_pos.x);
  unsigned int j = 0;
  for(unsigned int h = 0; h < _height;h++){
    for(unsigned int w = 0; w < _width;w++){
      j++;
      _temp_grid2d.grid[h][w].grid_pos = (GridVector2D){w, h};
      _temp_grid2d.grid[h][w].exist = 1;
      #if DEBUG_MODE
        printf("x:%d y:%d pos:%d,%d \n", w , h, _temp_grid2d.grid[h][w].grid_pos.x,_temp_grid2d.grid[h][w].grid_pos.y);
      #endif
    }
  }  
  printf("Grid Created Successfully\n");
  return _temp_grid2d;
}
void GetGridOnHover(Vector2 _mouse_world_pos, GridVector2D *_grid_on_hover_pos, Cell **cell_on_hover , CellGrid2D *cell_grid, GridVector2D WorldGrid ){
  _grid_on_hover_pos->x = 0;
  _grid_on_hover_pos->y = 0;
  if(_mouse_world_pos.x > 0) {
    _grid_on_hover_pos->x = (unsigned int)_mouse_world_pos.x / PIXEL_SIZE;
  } 
  if(_mouse_world_pos.y > 0) {
    _grid_on_hover_pos->y = (unsigned int)_mouse_world_pos.y / PIXEL_SIZE;
  }
  if(_grid_on_hover_pos->x >= WorldGrid.x) _grid_on_hover_pos->x = WorldGrid.x-1;
  if(_grid_on_hover_pos->y >= WorldGrid.y) _grid_on_hover_pos->y = WorldGrid.y-1;
  if(_mouse_world_pos.x < 0) _grid_on_hover_pos->x = 0;
  if(_mouse_world_pos.y < 0) _grid_on_hover_pos->y = 0;
  *cell_on_hover = &(cell_grid->grid[_grid_on_hover_pos->y][_grid_on_hover_pos->x]);
}