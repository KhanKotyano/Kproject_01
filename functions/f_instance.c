#include "functions.h"

Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Instance *_inst_array){
  static int id = 0;
  id++;
  Instance _instance = {
    .ID = id,
    .active = true,
    .pos = _position,
    .sprite = _sprite,
    .scale = 1,
    .angle = 0
  };
  Instance *inst_pointer = &_instance;
  AddInstance(inst_pointer, _inst_array);
  return _instance;
};
void AddInstance(Instance *_inst, Instance *_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(_inst_array[i].active){
      continue;
    }
    _inst_array[i] = *_inst;
    return;
  };
}
void UpdateInstances(Instance *_inst_array){
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(!_inst_array[i].active){
      continue;
    }
    PlayerIvent(_inst_array[i]);
  };

};
void UpdateDrawInstances(Instance *_inst_array){
  int number = 0;
  for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
    if(!_inst_array[i].active){
      
      continue;
    }
    number++;
    char *player_posx = FloatToString(_inst_array[i].pos.y);
    char *player_posy = FloatToString(_inst_array[i].pos.x);
    
    DrawTextureEx(*_inst_array[i].sprite, Vector2 {0,0}, 0, 1, GREEN);
    DrawTextureEx(*_inst_array[i].sprite, _inst_array[i].pos, _inst_array[i].angle, _inst_array[i].scale, WHITE);
    DrawText(player_posx, _inst_array[i].pos.x, _inst_array[i].pos.y, 8, BLACK);
    DrawText(player_posy, _inst_array[i].pos.x , _inst_array[i].pos.y+ 24, 8, BLACK);
    

    free(player_posx);
    free(player_posy);
  };
  char *num = IntToString(number);
  DrawText(num, 16, 16, 8, BLACK);
}

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