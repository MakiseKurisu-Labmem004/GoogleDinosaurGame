#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#undef main

void LOAD(); // 负责把图片加载出来
void LOAD_PAUSE();
void PAUSE_LOGO(); // 暂停
void LOAD_TUMBLEWEED();
void QUIT();       // 写一个退出函数，所有的退出都在这里进行
void PRINTSCORE(); // 负责显示分数
void PRINTSCORENUMBER();
void PRINTSTART(); // 开始界面的文字
void LOAD_PLAY();
void LOAD_LAND();
void LOAD_DINO_LEFT();
void LOAD_DINO_RIGHT();
void BIGJUMP();
void CREEP_LEFT();
void CREEP_RIGHT();
void CREATE_BARRIER();
void PRINT_BARRIER();
void OB1_F();
void OB1_S();
void OB2_F();
void OB2_S();
void OB3_F();
void OB3_S();
void OB4_F();
void OB4_S();
void OB5_F();
void OB5_S();
void OB6_F();
void OB6_S();
void OB7_F();
void OB7_S();
void JUDGE_CRASH();
void GAME_OVER();
void RE();
void Random_Poo(int a, int b);
void PrintPoo();

static SDL_Surface *MainBackGroundSurface = NULL; // 图片
static SDL_Rect MainBackGroundRect;               // Texture的信息

static SDL_Surface *LandSurface = NULL;
static SDL_Rect LandRect;
static SDL_Surface *WeedSurface = NULL;
static SDL_Rect WeedRect;
static SDL_Surface *PauseSurface = NULL;
static SDL_Rect Pause;
static SDL_Surface *PauseLogoSurface = NULL;
static SDL_Rect PauseLogoRect;
static SDL_Surface *OverLogoSurface = NULL;
static SDL_Rect OverLogoRect;

static SDL_Surface *DinosaurLeftSurface = NULL;
static SDL_Rect DinosaurLeftRect;
static SDL_Surface *DinosaurRightSurface = NULL;
static SDL_Rect DinosaurRightRect;
static SDL_Surface *DinosaurJumpSurface = NULL;
static SDL_Rect DinosaurJumpRect;
static SDL_Surface *DinosaurCreepLeftSurface = NULL;
static SDL_Rect DinosaurCreepLeftRect;
static SDL_Surface *DinosaurCreepRightSurface = NULL;
static SDL_Rect DinosaurCreepRightRect;

static SDL_Surface *BirdUpSurface_low_first = NULL;
static SDL_Rect BirdUpRect_low_first;
static SDL_Surface *BirdDownSurface_low_first = NULL;
static SDL_Rect BirdDownRect_low_first;
static SDL_Surface *BirdUpSurface_mid_first = NULL;
static SDL_Rect BirdUpRect_mid_first;
static SDL_Surface *BirdDownSurface_mid_first = NULL;
static SDL_Rect BirdDownRect_mid_first;
static SDL_Surface *BirdUpSurface_high_first = NULL;
static SDL_Rect BirdUpRect_high_first;
static SDL_Surface *BirdDownSurface_high_first = NULL;
static SDL_Rect BirdDownRect_high_first;
static SDL_Surface *Cactus_1Surface_first = NULL;
static SDL_Rect Cactus_1Rect_first;
static SDL_Surface *Cactus_2Surface_first = NULL;
static SDL_Rect Cactus_2Rect_first;
static SDL_Surface *Cactus_3Surface_first = NULL;
static SDL_Rect Cactus_3Rect_first;
static SDL_Surface *Cactus_4Surface_first = NULL;
static SDL_Rect Cactus_4Rect_first;

static SDL_Surface *BirdUpSurface_low_second = NULL;
static SDL_Rect BirdUpRect_low_second;
static SDL_Surface *BirdDownSurface_low_second = NULL;
static SDL_Rect BirdDownRect_low_second;
static SDL_Surface *BirdUpSurface_mid_second = NULL;
static SDL_Rect BirdUpRect_mid_second;
static SDL_Surface *BirdDownSurface_mid_second = NULL;
static SDL_Rect BirdDownRect_mid_second;
static SDL_Surface *BirdUpSurface_high_second = NULL;
static SDL_Rect BirdUpRect_high_second;
static SDL_Surface *BirdDownSurface_high_second = NULL;
static SDL_Rect BirdDownRect_high_second;
static SDL_Surface *Cactus_1Surface_second = NULL;
static SDL_Rect Cactus_1Rect_second;
static SDL_Surface *Cactus_2Surface_second = NULL;
static SDL_Rect Cactus_2Rect_second;
static SDL_Surface *Cactus_3Surface_second = NULL;
static SDL_Rect Cactus_3Rect_second;
static SDL_Surface *Cactus_4Surface_second = NULL;
static SDL_Rect Cactus_4Rect_second;
static SDL_Surface *PooSurface = NULL;
static SDL_Rect PooRect;

static TTF_Font *ScoreFont = NULL;
static SDL_Surface *ScoreSurface = NULL;
static SDL_Rect ScoreRect;
static SDL_Color ScoreFontColor = {0, 0, 0, 0};
static TTF_Font *ScoreNumFont = NULL;
static SDL_Surface *ScoreNumSurface = NULL;
static SDL_Rect ScoreNumRect;
static SDL_Color ScoreNumFontColor = {0, 0, 0, 0};
static TTF_Font *StartFont = NULL;
static SDL_Surface *StartSurface = NULL;
static SDL_Rect StartRect;
static SDL_Color StartFontColor = {0, 0, 0, 0};

static SDL_Window *Window = NULL;     // 窗口
static SDL_Renderer *Renderer = NULL; // 渲染器，可理解为一个画笔
static SDL_Event MainEvent;
Mix_Chunk *music1;
Mix_Chunk *music2;
Mix_Chunk *music3;
Mix_Chunk *music4;
int Judge = 0;
int Judge_Creep = 0;
int Judge_Jump = 0;
int Score = 1;
int Land_X = 0;
int Jump_Hight = 0;
int Jump_Up = 1;
int Judge_On_Land = 1;
int Step = 40;
int Score_Delay = 0;
int Fly_Delay = 0;
int Judge_Pause = 0;
int OB1_first = 0;
int OB1_second = 0;
int OB2_first = 0;
int OB2_second = 0;
int OB3_first = 0;
int OB3_second = 0;
int OB4_first = 0;
int OB4_second = 0;
int OB5_first = 0;
int OB5_second = 0;
int OB6_first = 0;
int OB6_second = 0;
int OB7_first = 0;
int OB7_second = 0;
int limit = 60;
int DIE = 0;

int L_OR_R = 1;
int count_run = 0;
int L_OR_R_CREEP = 1;
int count_creep = 0;

int U_OR_D_F = 1;
int U_OR_D_S = 1;
int U_OR_D_F_M = 1;
int U_OR_D_S_M = 1;
int U_OR_D_F_H = 1;
int U_OR_D_S_H = 1;

int count_fly_F = 0;
int count_fly_S = 0;
int count_fly_F_M = 0;
int count_fly_S_M = 0;
int count_fly_F_H = 0;
int count_fly_S_H = 0;

int Bird_Init_X_F = 1100;
int Bird_Init_X_S = 1100;
int Bird_Init_X_F_M = 1100;
int Bird_Init_X_S_M = 1100;
int Bird_Init_X_F_H = 1100;
int Bird_Init_X_S_H = 1100;
int Cactus_Init_X_F_1 = 1100;
int Cactus_Init_X_S_1 = 1100;
int Cactus_Init_X_F_2 = 1100;
int Cactus_Init_X_S_2 = 1100;
int Cactus_Init_X_F_3 = 1100;
int Cactus_Init_X_S_3 = 1100;
int Cactus_Init_X_F_4 = 1100;
int Cactus_Init_X_S_4 = 1100;
int last = 0;
int fly_speed = 25;
int Bird_Final_X = -80;
int Cactus_Final_X = -180;
int JUDGE_11 = 0;
int JUDGE_12 = 0;
int JUDGE_21 = 0;
int JUDGE_22 = 0;
int JUDGE_31 = 0;
int JUDGE_32 = 0;
int Poo_X = -40;
int Weed_Y = -120;
int Weed_X = 1100;
static double angle = 0;
int Have_Weed = 0;
int Judge_Poo = 0;
int Poo_Delay = 0;
int Have_Wind=0;
int Have_Jump=0;
int Wind_Delay=50;
int Have_Halt=0;
int Have_Lost=0;
time_t t;