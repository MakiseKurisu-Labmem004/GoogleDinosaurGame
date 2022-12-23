#include "DINOSAUR.h"
// 主体main
int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_StopTextInput();
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();
    Window = SDL_CreateWindow("DINOSAUR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1100, 700, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    LOAD();
    PRINTSTART();
    PRINTSCORE();
    while (1)
    {
        SDL_RenderPresent(Renderer);
        if (DIE == 0 && Judge_Pause == 0)
            SDL_RenderClear(Renderer);
        if (Judge == 0)
        {
            LOAD();
            PRINTSTART();
            PRINTSCORE();
        }
        if (Judge == 1 && DIE != 1)
        {
            if (Judge_Pause == 0)
            {
                JUDGE_CRASH();
                LOAD_PLAY();
                if (L_OR_R == 1 && Judge_Jump == 0 && Judge_Creep == 0)
                {
                    LOAD_DINO_LEFT();
                    count_run += 1;
                    if (count_run > 2)
                    {
                        L_OR_R = 0;
                        count_run = 0;
                    }
                }
                else if (L_OR_R == 0 && Judge_Jump == 0 && Judge_Creep == 0)
                {
                    LOAD_DINO_RIGHT();
                    count_run += 1;
                    if (count_run > 2)
                    {
                        L_OR_R = 1;
                        count_run = 0;
                    }
                }
                else if (Judge_Creep == 1 && Judge_On_Land == 1)
                {
                    if (L_OR_R_CREEP == 1)
                    {
                        CREEP_LEFT();
                        count_creep += 1;
                        if (count_creep > 2)
                        {
                            L_OR_R_CREEP = 0;
                            count_creep = 0;
                        }
                    }
                    else if (L_OR_R_CREEP == 0)
                    {
                        CREEP_RIGHT();
                        count_creep += 1;
                        if (count_creep > 2)
                        {
                            L_OR_R_CREEP = 1;
                            count_creep = 0;
                        }
                    }
                    Judge_Jump = 0;
                }
                else if (Judge_Jump == 1)
                {
                    BIGJUMP();
                }
                PRINTSCORENUMBER();
                SDL_Delay(15);
            }
        }
        if (DIE == 1)
        {
            if (Have_Halt == 0)
            {
                Mix_HaltChannel(-1);
                Have_Halt = 1;
            }
            else
            {
                if (Have_Lost == 0)
                {
                    music4 = Mix_LoadWAV("resources/LoseSound.mp3");
                    Mix_PlayChannel(4, music4, 0);
                    Have_Lost += 1;
                }
            }
            GAME_OVER();
            while (SDL_PollEvent(&MainEvent))
            {
                switch (MainEvent.type)
                {
                case SDL_QUIT: // 相当于按窗口的X键
                    QUIT();
                    break;
                case SDL_KEYDOWN:
                    switch (MainEvent.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        RE();
                        break;
                    default:
                        break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    if (MainEvent.button.x >= 400 && MainEvent.button.x <= 700 && MainEvent.button.y >= 250 && MainEvent.button.y <= 429)
                    {
                        RE();
                    }
                    break;
                default:
                    break;
                }
            }
        }
        if (Judge_Pause == 0 && DIE != 1)
        {
            while (SDL_PollEvent(&MainEvent))
            {
                switch (MainEvent.type)
                {
                case SDL_QUIT: // 相当于按窗口的X键
                    QUIT();
                    break;
                case SDL_KEYDOWN: // 相当于键盘交互键
                    switch (MainEvent.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        if (Judge == 0) // 按下空格启动游戏
                        {
                            LOAD_PLAY();
                            Judge = 1;
                            break;
                        }
                        else if (Judge == 1) // 按下空格开始JUMP()
                        {
                            if (Judge_Jump == 0)
                            {
                                Judge_Jump = 1;
                            }
                            break;
                        }
                    case SDLK_q:
                        if (Judge == 1)
                        {
                            Judge_Pause = 1;
                        }
                        break;
                    case SDLK_UP:
                        if (Judge == 1) // 按下上方向键开始JUMP()
                        {
                            if (Judge_Jump == 0)
                            {
                                Judge_Jump = 1;
                            }
                            break;
                        }
                        else
                            break;
                    case SDLK_DOWN:
                        if (Judge == 1) // 按下下方向键开始CREEP()
                        {
                            Judge_Creep = 1;
                            break;
                        }
                        else
                            break;
                    case SDLK_ESCAPE:
                        QUIT();
                        break;
                    default:
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (MainEvent.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if (Judge == 1)
                        {
                            Judge_Creep = 0;
                            break;
                        }
                    default:
                        break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    if (MainEvent.button.x >= 20 && MainEvent.button.x <= 120 && MainEvent.button.y >= 20 && MainEvent.button.y <= 74 && Judge == 1)
                    {
                        Judge_Pause = 1;
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        else if (Judge_Pause == 1 && DIE != 1)
        {
            Mix_Pause(-1);
            PAUSE_LOGO();
            while (SDL_PollEvent(&MainEvent))
            {
                switch (MainEvent.type)
                {
                case SDL_QUIT: // 相当于按窗口的X键
                    QUIT();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (MainEvent.button.x >= 400 && MainEvent.button.x <= 700 && MainEvent.button.y >= 200 && MainEvent.button.y <= 494 && Judge == 1)
                    {
                        Mix_Resume(-1);
                        Judge_Pause = 0;
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (MainEvent.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if (Judge == 1)
                        {
                            Judge_Creep = 0;
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
        }
    }
    QUIT();
    return 0;
}
// 负责加载背景和字
void LOAD() // 负责把图片加载出来
{
    SDL_Texture *MainBackGroundTexture = NULL;                                             // 纹理
    MainBackGroundSurface = IMG_Load("resources/BackGround.png");                          // xxx为加载图片的名字
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface); // 将图片转化为纹理绑定在画笔上
    MainBackGroundRect.x = 0;
    MainBackGroundRect.y = 0;
    MainBackGroundRect.w = MainBackGroundSurface->w; // 宽,可根据原图片缩放
    MainBackGroundRect.h = MainBackGroundSurface->h; // 高,可根据原图片缩放
    ScoreFont = TTF_OpenFont("resources/ITCBLKAD.TTF", 40);
    StartFont = TTF_OpenFont("resources/ITCBLKAD.TTF", 60);
    ScoreNumFont = TTF_OpenFont("resources/ITCBLKAD.TTF", 40);
    SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, &MainBackGroundRect);
    SDL_DestroyTexture(MainBackGroundTexture);
}
void LOAD_PAUSE()
{
    SDL_Texture *PauseTexture = NULL;                                    // 纹理
    PauseSurface = IMG_Load("resources/PAUSE.png");                      // xxx为加载图片的名字
    PauseTexture = SDL_CreateTextureFromSurface(Renderer, PauseSurface); // 将图片转化为纹理绑定在画笔上
    Pause.x = 20;
    Pause.y = 20;
    Pause.w = PauseSurface->w; // 宽,可根据原图片缩放
    Pause.h = PauseSurface->h; // 高,可根据原图片缩放
    SDL_RenderCopy(Renderer, PauseTexture, NULL, &Pause);
    SDL_DestroyTexture(PauseTexture);
}
void PAUSE_LOGO()
{
    SDL_Texture *PauseLogoTexture = NULL;                                        // 纹理
    PauseLogoSurface = IMG_Load("resources/PAUSE_LOGO.png");                     // xxx为加载图片的名字
    PauseLogoTexture = SDL_CreateTextureFromSurface(Renderer, PauseLogoSurface); // 将图片转化为纹理绑定在画笔上
    PauseLogoRect.x = 400;
    PauseLogoRect.y = 200;
    PauseLogoRect.w = PauseLogoSurface->w; // 宽,可根据原图片缩放
    PauseLogoRect.h = PauseLogoSurface->h; // 高,可根据原图片缩放
    SDL_RenderCopy(Renderer, PauseLogoTexture, NULL, &PauseLogoRect);
    SDL_DestroyTexture(PauseLogoTexture);
}
// 开始以后加载背景和字
void LOAD_PLAY()
{
    LOAD();
    LOAD_LAND();
    CREATE_BARRIER();
    LOAD_PAUSE();
    LOAD_TUMBLEWEED();
    PRINTSCORE();
}
// 打印地面
void LOAD_TUMBLEWEED()
{
    int which = -1;
    if (Have_Weed == 0)
    {
        which = rand() % 1000;
        switch (which)
        {
        case 1:
            Have_Weed = 1;
            Weed_Y = 500;
            break;
        case 2:
            Have_Weed = 1;
            Weed_Y = 450;
            break;
        case 3:
            Have_Weed = 1;
            Weed_Y = 550;
            break;
        default:
            break;
        }
    }
    else
    {
        if (Have_Wind == 0)
        {
            music1 = Mix_LoadWAV("resources/WindSound.mp3");
            Mix_PlayChannel(-1, music1, 0);
            Have_Wind = 1;
        }
        if (Wind_Delay == 0)
        {
            if (Weed_X > -120)
            {
                if (Score < 330)
                {
                    Weed_X -= 20;
                    angle -= 4;
                }
                else
                {
                    Weed_X -= 30;
                    angle -= 6;
                }
                SDL_Texture *WeedTexture = NULL;
                WeedSurface = IMG_Load("resources/TUMBLEWEED.png");                // xxx为加载图片的名字
                WeedTexture = SDL_CreateTextureFromSurface(Renderer, WeedSurface); // 将图片转化为纹理绑定在画笔上
                WeedRect.x = Weed_X;
                WeedRect.y = Weed_Y;
                WeedRect.w = WeedSurface->w; // 宽,可根据原图片缩放
                WeedRect.h = WeedSurface->h; // 高,可根据原图片缩放
                SDL_RenderCopyEx(Renderer, WeedTexture, NULL, &WeedRect, angle, NULL, SDL_FLIP_NONE);
                SDL_DestroyTexture(WeedTexture);
            }
            else
            {
                which = -1;
                Have_Weed = 0;
                Weed_X = 1100;
                angle = 0;
                Have_Wind = 0;
                Wind_Delay = 50;
            }
        }
        else
        {
            Wind_Delay -= 1;
        }
    }
}
void LOAD_LAND()
{
    SDL_Texture *LandTexture = NULL;
    LandSurface = IMG_Load("resources/Land.png");                      // xxx为加载图片的名字
    LandTexture = SDL_CreateTextureFromSurface(Renderer, LandSurface); // 将图片转化为纹理绑定在画笔上
    LandRect.x = Land_X;
    LandRect.y = 400;
    LandRect.w = LandSurface->w; // 宽,可根据原图片缩放
    LandRect.h = LandSurface->h; // 高,可根据原图片缩放
    if (Land_X <= -2200)
    {
        Land_X = 0;
    }
    if (Score <= 260)
    {
        Land_X -= 10;
    }
    if (Score > 260 && Score <= 410)
    {
        Land_X -= 12;
    }
    if (Score > 410 && Score <= 510)
    {
        Land_X -= 14;
    }
    if (Score > 510 && Score <= 560)
    {
        Land_X -= 16;
    }
    if (Score > 560 && Score <= 660)
    {
        Land_X -= 18;
    }
    if (Score > 660)
    {
        if (Poo_Delay == 0)
            Land_X -= 20;
        else
        {
            Poo_Delay -= 1;
            Land_X -= 40;
        }
    }
    SDL_RenderCopy(Renderer, LandTexture, NULL, &LandRect);
    SDL_DestroyTexture(LandTexture);
}
// 打印恐龙
void LOAD_DINO_LEFT()
{
    SDL_Texture *DinosaurLeftTexture = NULL;
    DinosaurLeftSurface = IMG_Load("resources/DINO_RUN_LEFT.png");                     // xxx为加载图片的名字
    DinosaurLeftTexture = SDL_CreateTextureFromSurface(Renderer, DinosaurLeftSurface); // 将图片转化为纹理绑定在画笔上
    DinosaurLeftRect.x = 0;
    DinosaurLeftRect.y = 350;
    DinosaurLeftRect.w = DinosaurLeftSurface->w; // 宽,可根据原图片缩放
    DinosaurLeftRect.h = DinosaurLeftSurface->h;
    SDL_RenderCopy(Renderer, DinosaurLeftTexture, NULL, &DinosaurLeftRect);
    SDL_DestroyTexture(DinosaurLeftTexture);
}
void LOAD_DINO_RIGHT()
{
    SDL_Texture *DinosaurRightTexture = NULL;
    DinosaurRightSurface = IMG_Load("resources/DINO_RUN_RIGHT.png");                     // xxx为加载图片的名字
    DinosaurRightTexture = SDL_CreateTextureFromSurface(Renderer, DinosaurRightSurface); // 将图片转化为纹理绑定在画笔上
    DinosaurRightRect.x = 0;
    DinosaurRightRect.y = 350;
    DinosaurRightRect.w = DinosaurRightSurface->w; // 宽,可根据原图片缩放
    DinosaurRightRect.h = DinosaurRightSurface->h;
    SDL_RenderCopy(Renderer, DinosaurRightTexture, NULL, &DinosaurRightRect);
    SDL_DestroyTexture(DinosaurRightTexture);
}
void BIGJUMP()
{
    if (Have_Jump == 0)
    {
        music2 = Mix_LoadWAV("resources/JumpSound.wav");
        Mix_PlayChannel(-1, music2, 0);
        Have_Jump = 1;
    }
    SDL_Texture *DinosaurJumpTexture = NULL;
    DinosaurJumpSurface = IMG_Load("resources/DINO_JUMP.png");                         // xxx为加载图片的名字
    DinosaurJumpTexture = SDL_CreateTextureFromSurface(Renderer, DinosaurJumpSurface); // 将图片转化为纹理绑定在画笔上
    DinosaurJumpRect.x = 0;
    DinosaurJumpRect.y = (350 - Jump_Hight);
    DinosaurJumpRect.w = DinosaurJumpSurface->w; // 宽,可根据原图片缩放
    DinosaurJumpRect.h = DinosaurJumpSurface->h;
    if (Judge_Creep == 0)
    {
        Judge_On_Land = 0;
        if (Jump_Hight < 220 && Jump_Up == 1)
        {
            Jump_Hight += Step;
            Step -= 4;
        }
        if (Jump_Hight == 220)
        {
            if (Fly_Delay > 1)
            {
                Jump_Up = 0;
                Fly_Delay = 0;
            }
            else
            {
                Fly_Delay += 1;
            }
        }
        if (Jump_Hight > 0 && Jump_Up == 0)
        {
            Jump_Hight -= Step;
            Step += 4;
        }
        if (Jump_Hight <= 0)
        {
            Jump_Up = 1;
            Jump_Hight = 0;
            Judge_Jump = 0;
            Step = 40;
            Judge_On_Land = 1;
            Have_Jump = 0;
        }
    }
    else
    {
        Jump_Up = 0;
        if (Jump_Hight > 0)
        {
            Jump_Hight -= 100;
            Judge_On_Land = 0;
            Step = 20;
        }
        if (Jump_Hight <= 0)
        {
            Jump_Hight = 0;
            Judge_On_Land = 1;
            Jump_Up = 1;
            Judge_Jump = 0;
            Step = 40;
            Have_Jump = 0;
        }
    }
    SDL_RenderCopy(Renderer, DinosaurJumpTexture, NULL, &DinosaurJumpRect);
    SDL_DestroyTexture(DinosaurJumpTexture);
}
void CREEP_LEFT()
{
    SDL_Texture *DinosaurCreepLeftTexture = NULL;
    DinosaurCreepLeftSurface = IMG_Load("resources/DINO_CREEP_LEFT.png");                        // xxx为加载图片的名字
    DinosaurCreepLeftTexture = SDL_CreateTextureFromSurface(Renderer, DinosaurCreepLeftSurface); // 将图片转化为纹理绑定在画笔上
    DinosaurCreepLeftRect.x = 0;
    DinosaurCreepLeftRect.y = 388;
    DinosaurCreepLeftRect.w = DinosaurCreepLeftSurface->w; // 宽,可根据原图片缩放
    DinosaurCreepLeftRect.h = DinosaurCreepLeftSurface->h;
    SDL_RenderCopy(Renderer, DinosaurCreepLeftTexture, NULL, &DinosaurCreepLeftRect);
    SDL_DestroyTexture(DinosaurCreepLeftTexture);
}
void CREEP_RIGHT()
{
    SDL_Texture *DinosaurCreepRightTexture = NULL;
    DinosaurCreepRightSurface = IMG_Load("resources/DINO_CREEP_RIGHT.png");                        // xxx为加载图片的名字
    DinosaurCreepRightTexture = SDL_CreateTextureFromSurface(Renderer, DinosaurCreepRightSurface); // 将图片转化为纹理绑定在画笔上
    DinosaurCreepRightRect.x = 0;
    DinosaurCreepRightRect.y = 388;
    DinosaurCreepRightRect.w = DinosaurCreepRightSurface->w; // 宽,可根据原图片缩放
    DinosaurCreepRightRect.h = DinosaurCreepRightSurface->h;
    SDL_RenderCopy(Renderer, DinosaurCreepRightTexture, NULL, &DinosaurCreepRightRect);
    SDL_DestroyTexture(DinosaurCreepRightTexture);
}
// 障碍物
void CREATE_BARRIER()
{
    if (Score >= 660)
    {
        if (Score > limit)
        {
            srand((unsigned)time(&t));
            int Which_One = rand() % 7 + 1;
            switch (Which_One)
            {
            case 1:
                if (OB1_first == 1)
                {
                    OB1_second = 1;
                }
                else
                    OB1_first = 1;
                break;
            case 2:
                if (OB2_first == 1)
                {
                    OB2_second = 1;
                }
                else
                    OB2_first = 1;
                break;
            case 3:
                if (OB3_first == 1)
                {
                    OB3_second = 1;
                }
                else
                    OB3_first = 1;
                break;
            case 4:
                if (OB4_first == 1)
                {
                    OB4_second = 1;
                }
                else
                    OB4_first = 1;
                break;
            case 5:
                if (OB5_first == 1)
                {
                    OB5_second = 1;
                }
                else
                    OB5_first = 1;
                break;
            case 6:
                if (OB6_first == 1)
                {
                    OB6_second = 1;
                }
                else
                    OB6_first = 1;
                break;
            case 7:
                if (OB7_first == 1)
                {
                    OB7_second = 1;
                }
                else
                    OB7_first = 1;
                break;
            default:
                break;
            }
            limit += rand() % 30 + 30;
        }
    }
    else if (Score < 660 && Score >= 500)
    {

        if (Score > limit)
        {
            srand((unsigned)time(&t));
            int Which_One = rand() % 4 + 4;
            switch (Which_One)
            {
            case 1:
                if (OB1_first == 1)
                {
                    OB1_second = 1;
                }
                else
                    OB1_first = 1;
                break;
            case 2:
                if (OB2_first == 1)
                {
                    OB2_second = 1;
                }
                else
                    OB2_first = 1;
                break;
            case 3:
                if (OB3_first == 1)
                {
                    OB3_second = 1;
                }
                else
                    OB3_first = 1;
                break;
            case 4:
                if (OB4_first == 1)
                {
                    OB4_second = 1;
                }
                else
                    OB4_first = 1;
                break;
            case 5:
                if (OB5_first == 1)
                {
                    OB5_second = 1;
                }
                else
                    OB5_first = 1;
                break;
            case 6:
                if (OB6_first == 1)
                {
                    OB6_second = 1;
                }
                else
                    OB6_first = 1;
                break;
            case 7:
                if (OB7_first == 1)
                {
                    OB7_second = 1;
                }
                else
                    OB7_first = 1;
                break;
            default:
                break;
            }
            limit += rand() % 30 + 40;
        }
    }
    else if (Score < 500 && Score >= 300)
    {

        if (Score > limit)
        {
            srand((unsigned)time(&t));
            int Which_One = rand() % 3 + 4;
            switch (Which_One)
            {
            case 1:
                if (OB1_first == 1)
                {
                    OB1_second = 1;
                }
                else
                    OB1_first = 1;
                break;
            case 2:
                if (OB2_first == 1)
                {
                    OB2_second = 1;
                }
                else
                    OB2_first = 1;
                break;
            case 3:
                if (OB3_first == 1)
                {
                    OB3_second = 1;
                }
                else
                    OB3_first = 1;
                break;
            case 4:
                if (OB4_first == 1)
                {
                    OB4_second = 1;
                }
                else
                    OB4_first = 1;
                break;
            case 5:
                if (OB5_first == 1)
                {
                    OB5_second = 1;
                }
                else
                    OB5_first = 1;
                break;
            case 6:
                if (OB6_first == 1)
                {
                    OB6_second = 1;
                }
                else
                    OB6_first = 1;
                break;
            case 7:
                if (OB7_first == 1)
                {
                    OB7_second = 1;
                }
                else
                    OB7_first = 1;
                break;
            default:
                break;
            }
            limit += rand() % 30 + 50;
        }
    }
    else if (Score < 300)
    {

        if (Score > limit)
        {
            srand((unsigned)time(&t));
            int Which_One = 4;
            switch (Which_One)
            {
            case 1:
                if (OB1_first == 1)
                {
                    OB1_second = 1;
                }
                else
                    OB1_first = 1;
                break;
            case 2:
                if (OB2_first == 1)
                {
                    OB2_second = 1;
                }
                else
                    OB2_first = 1;
                break;
            case 3:
                if (OB3_first == 1)
                {
                    OB3_second = 1;
                }
                else
                    OB3_first = 1;
                break;
            case 4:
                if (OB4_first == 1)
                {
                    OB4_second = 1;
                }
                else
                    OB4_first = 1;
                break;
            case 5:
                if (OB5_first == 1)
                {
                    OB5_second = 1;
                }
                else
                    OB5_first = 1;
                break;
            case 6:
                if (OB6_first == 1)
                {
                    OB6_second = 1;
                }
                else
                    OB6_first = 1;
                break;
            case 7:
                if (OB7_first == 1)
                {
                    OB7_second = 1;
                }
                else
                    OB7_first = 1;
                break;
            default:
                break;
            }
            limit += rand() % 30 + 60;
        }
    }
    PRINT_BARRIER();
}
void PRINT_BARRIER()
{
    OB1_F();
    OB1_S();
    OB2_F();
    OB2_S();
    OB3_F();
    OB3_S();
    OB4_F();
    OB4_S();
    OB5_F();
    OB5_S();
    OB6_F();
    OB6_S();
    OB7_F();
    OB7_S();
    if (OB1_first == 1)
        Random_Poo(1, 1);
    if (OB1_second == 1)
        Random_Poo(1, 2);
    if (OB2_first == 1)
        Random_Poo(2, 1);
    if (OB2_second == 1)
        Random_Poo(2, 2);
    if (OB3_first == 1)
        Random_Poo(3, 1);
    if (OB3_second == 1)
        Random_Poo(3, 2);
    PrintPoo();
}
void OB1_F()
{
    if (OB1_first == 1)
    {
        if (Bird_Init_X_F > Bird_Final_X)
        {
            if (U_OR_D_F == 1)
            {
                SDL_Texture *BirdDownTexture_low_first = NULL;
                BirdDownSurface_low_first = IMG_Load("resources/BIRD_DOWN.png");                               // xxx为加载图片的名字
                BirdDownTexture_low_first = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_low_first); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_low_first.x = Bird_Init_X_F;
                BirdDownRect_low_first.y = 388;
                BirdDownRect_low_first.w = BirdDownSurface_low_first->w; // 宽,可根据原图片缩放
                BirdDownRect_low_first.h = BirdDownSurface_low_first->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_low_first, NULL, &BirdDownRect_low_first);
                SDL_DestroyTexture(BirdDownTexture_low_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F -= (fly_speed + 20);
                }
                if (count_fly_F > 3)
                {
                    count_fly_F = 0;
                    U_OR_D_F = 0;
                    BirdUpRect_low_first.x = Bird_Init_X_F;
                }
                else
                {
                    count_fly_F += 1;
                }
            }
            else if (U_OR_D_F == 0)
            {
                SDL_Texture *BirdUpTexture_low_first = NULL;
                BirdUpSurface_low_first = IMG_Load("resources/BIRD_Up.png");                               // xxx为加载图片的名字
                BirdUpTexture_low_first = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_low_first); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_low_first.x = Bird_Init_X_F;
                BirdUpRect_low_first.y = 376;
                BirdUpRect_low_first.w = BirdUpSurface_low_first->w; // 宽,可根据原图片缩放
                BirdUpRect_low_first.h = BirdUpSurface_low_first->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_low_first, NULL, &BirdUpRect_low_first);
                SDL_DestroyTexture(BirdUpTexture_low_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F -= (fly_speed + 20);
                }
                if (count_fly_F > 3)
                {
                    count_fly_F = 0;
                    U_OR_D_F = 1;
                    BirdDownRect_low_first.x = Bird_Init_X_F;
                }
                else
                {
                    count_fly_F += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_F = 1100;
            U_OR_D_F = 1;
            BirdDownRect_low_first.x = Bird_Init_X_F;
            OB1_first = 0;
        }
    }
}
void OB1_S()
{
    if (OB1_second == 1)
    {
        if (Bird_Init_X_S > Bird_Final_X)
        {
            if (U_OR_D_S == 1)
            {
                SDL_Texture *BirdDownTexture_low_second = NULL;
                BirdDownSurface_low_second = IMG_Load("resources/BIRD_DOWN.png");                                // xxx为加载图片的名字
                BirdDownTexture_low_second = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_low_second); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_low_second.x = Bird_Init_X_S;
                BirdDownRect_low_second.y = 388;
                BirdDownRect_low_second.w = BirdDownSurface_low_second->w; // 宽,可根据原图片缩放
                BirdDownRect_low_second.h = BirdDownSurface_low_second->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_low_second, NULL, &BirdDownRect_low_second);
                SDL_DestroyTexture(BirdDownTexture_low_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S -= (fly_speed + 20);
                }
                if (count_fly_S > 3)
                {
                    count_fly_S = 0;
                    U_OR_D_S = 0;
                    BirdUpRect_low_second.x = Bird_Init_X_S;
                }
                else
                {
                    count_fly_S += 1;
                }
            }
            else if (U_OR_D_S == 0)
            {
                SDL_Texture *BirdUpTexture_low_second = NULL;
                BirdUpSurface_low_second = IMG_Load("resources/BIRD_Up.png");                                // xxx为加载图片的名字
                BirdUpTexture_low_second = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_low_second); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_low_second.x = Bird_Init_X_S;
                BirdUpRect_low_second.y = 376;
                BirdUpRect_low_second.w = BirdUpSurface_low_second->w; // 宽,可根据原图片缩放
                BirdUpRect_low_second.h = BirdUpSurface_low_second->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_low_second, NULL, &BirdUpRect_low_second);
                SDL_DestroyTexture(BirdUpTexture_low_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S -= (fly_speed + 20);
                }
                if (count_fly_S > 3)
                {
                    count_fly_S = 0;
                    U_OR_D_S = 1;
                    BirdDownRect_low_second.x = Bird_Init_X_S;
                }
                else
                {
                    count_fly_S += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_S = 1100;
            BirdDownRect_low_second.x = Bird_Init_X_S;
            U_OR_D_S = 1;
            OB1_second = 0;
        }
    }
}
void OB2_F()
{
    if (OB2_first == 1)
    {
        if (Bird_Init_X_F_M > Bird_Final_X)
        {
            if (U_OR_D_F_M == 1)
            {
                SDL_Texture *BirdDownTexture_mid_first = NULL;
                BirdDownSurface_mid_first = IMG_Load("resources/BIRD_DOWN.png");                               // xxx为加载图片的名字
                BirdDownTexture_mid_first = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_mid_first); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_mid_first.x = Bird_Init_X_F_M;
                BirdDownRect_mid_first.y = 328;
                BirdDownRect_mid_first.w = BirdDownSurface_mid_first->w; // 宽,可根据原图片缩放
                BirdDownRect_mid_first.h = BirdDownSurface_mid_first->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_mid_first, NULL, &BirdDownRect_mid_first);
                SDL_DestroyTexture(BirdDownTexture_mid_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F_M -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F_M -= (fly_speed + 20);
                }
                if (count_fly_F_M > 3)
                {
                    count_fly_F_M = 0;
                    U_OR_D_F_M = 0;
                    BirdUpRect_mid_first.x = Bird_Init_X_F_M;
                }
                else
                {
                    count_fly_F_M += 1;
                }
            }
            else if (U_OR_D_F_M == 0)
            {
                SDL_Texture *BirdUpTexture_mid_first = NULL;
                BirdUpSurface_mid_first = IMG_Load("resources/BIRD_Up.png");                               // xxx为加载图片的名字
                BirdUpTexture_mid_first = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_mid_first); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_mid_first.x = Bird_Init_X_F_M;
                BirdUpRect_mid_first.y = 316;
                BirdUpRect_mid_first.w = BirdUpSurface_mid_first->w; // 宽,可根据原图片缩放
                BirdUpRect_mid_first.h = BirdUpSurface_mid_first->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_mid_first, NULL, &BirdUpRect_mid_first);
                SDL_DestroyTexture(BirdUpTexture_mid_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F_M -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F_M -= (fly_speed + 20);
                }
                if (count_fly_F_M > 3)
                {
                    count_fly_F_M = 0;
                    U_OR_D_F_M = 1;
                    BirdDownRect_mid_first.x = Bird_Init_X_F_M;
                }
                else
                {
                    count_fly_F_M += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_F_M = 1100;
            OB2_first = 0;
            BirdDownRect_mid_first.x = Bird_Init_X_F_M;
            U_OR_D_F_M = 1;
        }
    }
}
void OB2_S()
{
    if (OB2_second == 1)
    {
        if (Bird_Init_X_S_M > Bird_Final_X)
        {
            if (U_OR_D_S_M == 1)
            {
                SDL_Texture *BirdDownTexture_mid_second = NULL;
                BirdDownSurface_mid_second = IMG_Load("resources/BIRD_DOWN.png");                                // xxx为加载图片的名字
                BirdDownTexture_mid_second = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_mid_second); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_mid_second.x = Bird_Init_X_S_M;
                BirdDownRect_mid_second.y = 328;
                BirdDownRect_mid_second.w = BirdDownSurface_mid_second->w; // 宽,可根据原图片缩放
                BirdDownRect_mid_second.h = BirdDownSurface_mid_second->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_mid_second, NULL, &BirdDownRect_mid_second);
                SDL_DestroyTexture(BirdDownTexture_mid_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S_M -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S_M -= (fly_speed + 20);
                }
                if (count_fly_S_M > 3)
                {
                    count_fly_S_M = 0;
                    U_OR_D_S_M = 0;
                    BirdUpRect_mid_second.x = Bird_Init_X_S_M;
                }
                else
                {
                    count_fly_S_M += 1;
                }
            }
            else if (U_OR_D_S_M == 0)
            {
                SDL_Texture *BirdUpTexture_mid_second = NULL;
                BirdUpSurface_mid_second = IMG_Load("resources/BIRD_Up.png");                                // xxx为加载图片的名字
                BirdUpTexture_mid_second = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_mid_second); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_mid_second.x = Bird_Init_X_S_M;
                BirdUpRect_mid_second.y = 316;
                BirdUpRect_mid_second.w = BirdUpSurface_mid_second->w; // 宽,可根据原图片缩放
                BirdUpRect_mid_second.h = BirdUpSurface_mid_second->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_mid_second, NULL, &BirdUpRect_mid_second);
                SDL_DestroyTexture(BirdUpTexture_mid_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S_M -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S_M -= (fly_speed + 20);
                }
                if (count_fly_S_M > 3)
                {
                    count_fly_S_M = 0;
                    U_OR_D_S_M = 1;
                    BirdDownRect_mid_second.x = Bird_Init_X_S_M;
                }
                else
                {
                    count_fly_S_M += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_S_M = 1100;
            OB2_second = 0;
            BirdDownRect_mid_second.x = Bird_Init_X_S_M;
            U_OR_D_S_M = 1;
        }
    }
}
void OB3_F()
{
    if (OB3_first == 1)
    {
        if (Bird_Init_X_F_H > Bird_Final_X)
        {
            if (U_OR_D_F_H == 1)
            {
                SDL_Texture *BirdDownTexture_high_first = NULL;
                BirdDownSurface_high_first = IMG_Load("resources/BIRD_DOWN.png");                                // xxx为加载图片的名字
                BirdDownTexture_high_first = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_high_first); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_high_first.x = Bird_Init_X_F_H;
                BirdDownRect_high_first.y = 285;
                BirdDownRect_high_first.w = BirdDownSurface_high_first->w; // 宽,可根据原图片缩放
                BirdDownRect_high_first.h = BirdDownSurface_high_first->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_high_first, NULL, &BirdDownRect_high_first);
                SDL_DestroyTexture(BirdDownTexture_high_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F_H -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F_H -= (fly_speed + 20);
                }
                if (count_fly_F_H > 3)
                {
                    count_fly_F_H = 0;
                    U_OR_D_F_H = 0;
                    BirdUpRect_high_first.x = Bird_Init_X_F_H;
                }
                else
                {
                    count_fly_F_H += 1;
                }
            }
            else if (U_OR_D_F_H == 0)
            {
                SDL_Texture *BirdUpTexture_high_first = NULL;
                BirdUpSurface_high_first = IMG_Load("resources/BIRD_Up.png");                                // xxx为加载图片的名字
                BirdUpTexture_high_first = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_high_first); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_high_first.x = Bird_Init_X_F_H;
                BirdUpRect_high_first.y = 273;
                BirdUpRect_high_first.w = BirdUpSurface_high_first->w; // 宽,可根据原图片缩放
                BirdUpRect_high_first.h = BirdUpSurface_high_first->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_high_first, NULL, &BirdUpRect_high_first);
                SDL_DestroyTexture(BirdUpTexture_high_first);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_F_H -= fly_speed;
                }
                else
                {
                    Bird_Init_X_F_H -= (fly_speed + 20);
                }
                if (count_fly_F_H > 3)
                {
                    count_fly_F_H = 0;
                    U_OR_D_F_H = 1;
                    BirdDownRect_high_first.x = Bird_Init_X_F_H;
                }
                else
                {
                    count_fly_F_H += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_F_H = 1100;
            OB3_first = 0;
            U_OR_D_F_H = 1;
            BirdDownRect_high_first.x = Bird_Init_X_F_H;
        }
    }
}
void OB3_S()
{
    if (OB3_second == 1)
    {
        if (Bird_Init_X_S_H > Bird_Final_X)
        {
            if (U_OR_D_S_H == 1)
            {
                SDL_Texture *BirdDownTexture_high_second = NULL;
                BirdDownSurface_high_second = IMG_Load("resources/BIRD_DOWN.png");                                 // xxx为加载图片的名字
                BirdDownTexture_high_second = SDL_CreateTextureFromSurface(Renderer, BirdDownSurface_high_second); // 将图片转化为纹理绑定在画笔上
                BirdDownRect_high_second.x = Bird_Init_X_S_H;
                BirdDownRect_high_second.y = 285;
                BirdDownRect_high_second.w = BirdDownSurface_high_second->w; // 宽,可根据原图片缩放
                BirdDownRect_high_second.h = BirdDownSurface_high_second->h;
                SDL_RenderCopy(Renderer, BirdDownTexture_high_second, NULL, &BirdDownRect_high_second);
                SDL_DestroyTexture(BirdDownTexture_high_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S_H -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S_H -= (fly_speed + 20);
                }
                if (count_fly_S_H > 3)
                {
                    count_fly_S_H = 0;
                    U_OR_D_S_H = 0;
                    BirdUpRect_high_second.x = Bird_Init_X_S_H;
                }
                else
                {
                    count_fly_S_H += 1;
                }
            }
            else if (U_OR_D_S_H == 0)
            {
                SDL_Texture *BirdUpTexture_high_second = NULL;
                BirdUpSurface_high_second = IMG_Load("resources/BIRD_Up.png");                                 // xxx为加载图片的名字
                BirdUpTexture_high_second = SDL_CreateTextureFromSurface(Renderer, BirdUpSurface_high_second); // 将图片转化为纹理绑定在画笔上
                BirdUpRect_high_second.x = Bird_Init_X_S_H;
                BirdUpRect_high_second.y = 273;
                BirdUpRect_high_second.w = BirdUpSurface_high_second->w; // 宽,可根据原图片缩放
                BirdUpRect_high_second.h = BirdUpSurface_high_second->h;
                SDL_RenderCopy(Renderer, BirdUpTexture_high_second, NULL, &BirdUpRect_high_second);
                SDL_DestroyTexture(BirdUpTexture_high_second);
                if (Poo_Delay == 0)
                {
                    Bird_Init_X_S_H -= fly_speed;
                }
                else
                {
                    Bird_Init_X_S_H -= (fly_speed + 20);
                }
                if (count_fly_S_H > 3)
                {
                    count_fly_S_H = 0;
                    U_OR_D_S_H = 1;
                    BirdDownRect_high_second.x = Bird_Init_X_S_H;
                }
                else
                {
                    count_fly_S_H += 1;
                }
            }
        }
        else
        {
            Bird_Init_X_S_H = 1100;
            OB3_second = 0;
            U_OR_D_S_H = 0;
            BirdDownRect_high_second.x = Bird_Init_X_S_H;
        }
    }
}
void OB4_F()
{
    if (OB4_first == 1)
    {
        if (Cactus_Init_X_F_1 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_1Texture_first = NULL;
            Cactus_1Surface_first = IMG_Load("resources/CACTUS_1.png");                            // xxx为加载图片的名字
            Cactus_1Texture_first = SDL_CreateTextureFromSurface(Renderer, Cactus_1Surface_first); // 将图片转化为纹理绑定在画笔上
            Cactus_1Rect_first.x = Cactus_Init_X_F_1;
            Cactus_1Rect_first.y = 380;
            Cactus_1Rect_first.w = Cactus_1Surface_first->w; // 宽,可根据原图片缩放
            Cactus_1Rect_first.h = Cactus_1Surface_first->h;
            SDL_RenderCopy(Renderer, Cactus_1Texture_first, NULL, &Cactus_1Rect_first);
            SDL_DestroyTexture(Cactus_1Texture_first);
            if (Score <= 260)
            {
                Cactus_Init_X_F_1 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_F_1 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_F_1 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_F_1 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_F_1 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_F_1 -= 20;
                else
                {
                    Cactus_Init_X_F_1 -= 40;
                }
            }
        }
        else
        {
            OB4_first = 0;
            Cactus_Init_X_F_1 = 1100;
            Cactus_1Rect_first.x = Cactus_Init_X_F_1;
        }
    }
}
void OB4_S()
{
    if (OB4_second == 1)
    {
        if (Cactus_Init_X_S_1 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_1Texture_second = NULL;
            Cactus_1Surface_second = IMG_Load("resources/CACTUS_1.png");                             // xxx为加载图片的名字
            Cactus_1Texture_second = SDL_CreateTextureFromSurface(Renderer, Cactus_1Surface_second); // 将图片转化为纹理绑定在画笔上
            Cactus_1Rect_second.x = Cactus_Init_X_S_1;
            Cactus_1Rect_second.y = 380;
            Cactus_1Rect_second.w = Cactus_1Surface_second->w; // 宽,可根据原图片缩放
            Cactus_1Rect_second.h = Cactus_1Surface_second->h;
            SDL_RenderCopy(Renderer, Cactus_1Texture_second, NULL, &Cactus_1Rect_second);
            SDL_DestroyTexture(Cactus_1Texture_second);
            if (Score <= 260)
            {
                Cactus_Init_X_S_1 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_S_1 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_S_1 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_S_1 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_S_1 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_S_1 -= 20;
                else
                {
                    Cactus_Init_X_S_1 -= 40;
                }
            }
        }
        else
        {
            OB4_second = 0;
            Cactus_Init_X_S_1 = 1100;
            Cactus_1Rect_second.x = Cactus_Init_X_S_1;
        }
    }
}
void OB5_F()
{
    if (OB5_first == 1)
    {
        if (Cactus_Init_X_F_2 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_2Texture_first = NULL;
            Cactus_2Surface_first = IMG_Load("resources/CACTUS_2.png");                            // xxx为加载图片的名字
            Cactus_2Texture_first = SDL_CreateTextureFromSurface(Renderer, Cactus_2Surface_first); // 将图片转化为纹理绑定在画笔上
            Cactus_2Rect_first.x = Cactus_Init_X_F_2;
            Cactus_2Rect_first.y = 360;
            Cactus_2Rect_first.w = Cactus_2Surface_first->w; // 宽,可根据原图片缩放
            Cactus_2Rect_first.h = Cactus_2Surface_first->h;
            SDL_RenderCopy(Renderer, Cactus_2Texture_first, NULL, &Cactus_2Rect_first);
            SDL_DestroyTexture(Cactus_2Texture_first);
            if (Score <= 260)
            {
                Cactus_Init_X_F_2 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_F_2 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_F_2 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_F_2 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_F_2 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_F_2 -= 20;
                else
                {
                    Cactus_Init_X_F_2 -= 40;
                }
            }
        }
        else
        {
            OB5_first = 0;
            Cactus_Init_X_F_2 = 1100;
            Cactus_2Rect_first.x = Cactus_Init_X_F_2;
        }
    }
}
void OB5_S()
{
    if (OB5_second == 1)
    {
        if (Cactus_Init_X_S_2 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_2Texture_second = NULL;
            Cactus_2Surface_second = IMG_Load("resources/CACTUS_2.png");                             // xxx为加载图片的名字
            Cactus_2Texture_second = SDL_CreateTextureFromSurface(Renderer, Cactus_2Surface_second); // 将图片转化为纹理绑定在画笔上
            Cactus_2Rect_second.x = Cactus_Init_X_S_2;
            Cactus_2Rect_second.y = 360;
            Cactus_2Rect_second.w = Cactus_2Surface_second->w; // 宽,可根据原图片缩放
            Cactus_2Rect_second.h = Cactus_2Surface_second->h;
            SDL_RenderCopy(Renderer, Cactus_2Texture_second, NULL, &Cactus_2Rect_second);
            SDL_DestroyTexture(Cactus_2Texture_second);
            if (Score <= 260)
            {
                Cactus_Init_X_S_2 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_S_2 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_S_2 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_S_2 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_S_2 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_S_2 -= 20;
                else
                {
                    Cactus_Init_X_S_2 -= 40;
                }
            }
        }
        else
        {
            OB5_second = 0;
            Cactus_Init_X_S_2 = 1100;
            Cactus_2Rect_second.x = Cactus_Init_X_S_2;
        }
    }
}
void OB6_F()
{
    if (OB6_first == 1)
    {
        if (Cactus_Init_X_F_3 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_3Texture_first = NULL;
            Cactus_3Surface_first = IMG_Load("resources/CACTUS_3.png");                            // xxx为加载图片的名字
            Cactus_3Texture_first = SDL_CreateTextureFromSurface(Renderer, Cactus_3Surface_first); // 将图片转化为纹理绑定在画笔上
            Cactus_3Rect_first.x = Cactus_Init_X_F_3;
            Cactus_3Rect_first.y = 350;
            Cactus_3Rect_first.w = Cactus_3Surface_first->w; // 宽,可根据原图片缩放
            Cactus_3Rect_first.h = Cactus_3Surface_first->h;
            SDL_RenderCopy(Renderer, Cactus_3Texture_first, NULL, &Cactus_3Rect_first);
            SDL_DestroyTexture(Cactus_3Texture_first);
            if (Score <= 260)
            {
                Cactus_Init_X_F_3 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_F_3 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_F_3 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_F_3 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_F_3 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_F_3 -= 20;
                else
                {
                    Cactus_Init_X_F_3 -= 40;
                }
            }
        }
        else
        {
            OB6_first = 0;
            Cactus_Init_X_F_3 = 1100;
            Cactus_3Rect_first.x = Cactus_Init_X_F_3;
            Cactus_3Rect_first.x = Cactus_Init_X_F_3;
        }
    }
}
void OB6_S()
{
    if (OB6_second == 1)
    {
        if (Cactus_Init_X_S_3 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_3Texture_second = NULL;
            Cactus_3Surface_second = IMG_Load("resources/CACTUS_3.png");                             // xxx为加载图片的名字
            Cactus_3Texture_second = SDL_CreateTextureFromSurface(Renderer, Cactus_3Surface_second); // 将图片转化为纹理绑定在画笔上
            Cactus_3Rect_second.x = Cactus_Init_X_S_3;
            Cactus_3Rect_second.y = 350;
            Cactus_3Rect_second.w = Cactus_3Surface_second->w; // 宽,可根据原图片缩放
            Cactus_3Rect_second.h = Cactus_3Surface_second->h;
            SDL_RenderCopy(Renderer, Cactus_3Texture_second, NULL, &Cactus_3Rect_second);
            SDL_DestroyTexture(Cactus_3Texture_second);
            if (Score <= 260)
            {
                Cactus_Init_X_S_3 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_S_3 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_S_3 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_S_3 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_S_3 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_S_3 -= 20;
                else
                {
                    Cactus_Init_X_S_3 -= 40;
                }
            }
        }
        else
        {
            OB6_second = 0;
            Cactus_Init_X_S_3 = 1100;
            Cactus_3Rect_second.x = Cactus_Init_X_S_3;
        }
    }
}
void OB7_F()
{
    if (OB7_first == 1)
    {
        if (Cactus_Init_X_F_4 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_4Texture_first = NULL;
            Cactus_4Surface_first = IMG_Load("resources/CACTUS_4.png");                            // xxx为加载图片的名字
            Cactus_4Texture_first = SDL_CreateTextureFromSurface(Renderer, Cactus_4Surface_first); // 将图片转化为纹理绑定在画笔上
            Cactus_4Rect_first.x = Cactus_Init_X_F_4;
            Cactus_4Rect_first.y = 350;
            Cactus_4Rect_first.w = Cactus_4Surface_first->h; // 宽,可根据原图片缩放
            Cactus_4Rect_first.h = Cactus_4Surface_first->h;
            SDL_RenderCopy(Renderer, Cactus_4Texture_first, NULL, &Cactus_4Rect_first);
            SDL_DestroyTexture(Cactus_4Texture_first);
            if (Score <= 260)
            {
                Cactus_Init_X_F_4 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_F_4 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_F_4 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_F_4 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_F_4 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_F_4 -= 20;
                else
                {
                    Cactus_Init_X_F_4 -= 40;
                }
            }
        }
        else
        {
            OB7_first = 0;
            Cactus_Init_X_F_4 = 1100;
            Cactus_4Rect_first.x = Cactus_Init_X_F_4;
        }
    }
}
void OB7_S()
{
    if (OB7_second == 1)
    {
        if (Cactus_Init_X_S_4 > Cactus_Final_X)
        {
            SDL_Texture *Cactus_4Texture_second = NULL;
            Cactus_4Surface_second = IMG_Load("resources/CACTUS_4.png");                             // xxx为加载图片的名字
            Cactus_4Texture_second = SDL_CreateTextureFromSurface(Renderer, Cactus_4Surface_second); // 将图片转化为纹理绑定在画笔上
            Cactus_4Rect_second.x = Cactus_Init_X_S_4;
            Cactus_4Rect_second.y = 350;
            Cactus_4Rect_second.w = Cactus_4Surface_second->w; // 宽,可根据原图片缩放
            Cactus_4Rect_second.h = Cactus_4Surface_second->h;
            SDL_RenderCopy(Renderer, Cactus_4Texture_second, NULL, &Cactus_4Rect_second);
            SDL_DestroyTexture(Cactus_4Texture_second);
            if (Score <= 260)
            {
                Cactus_Init_X_S_4 -= 10;
            }
            if (Score > 260 && Score <= 410)
            {
                Cactus_Init_X_S_4 -= 12;
            }
            if (Score > 410 && Score <= 510)
            {
                Cactus_Init_X_S_4 -= 14;
            }
            if (Score > 510 && Score <= 560)
            {
                Cactus_Init_X_S_4 -= 16;
            }
            if (Score > 560 && Score <= 660)
            {
                Cactus_Init_X_S_4 -= 18;
            }
            if (Score > 660)
            {
                if (Poo_Delay == 0)
                    Cactus_Init_X_S_4 -= 20;
                else
                {
                    Cactus_Init_X_S_4 -= 40;
                }
            }
        }
        else
        {
            OB7_second = 0;
            Cactus_Init_X_S_4 = 1100;
            Cactus_4Rect_second.x = Cactus_Init_X_S_4;
        }
    }
}
void JUDGE_CRASH()
{
    if (L_OR_R == 1 && Judge_Jump == 0 && Judge_Creep == 0)
    {
        // LOAD_DINO_LEFT();
        if (OB1_first == 1)
        {
            if (U_OR_D_F == 1)
            {
                if (DinosaurLeftRect.x + 50 < BirdDownRect_low_first.x + 30 && DinosaurLeftRect.x + 100 > BirdDownRect_low_first.x + 5)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurLeftRect.x + 50 < BirdUpRect_low_first.x + 30 && DinosaurLeftRect.x + 100 > BirdUpRect_low_first.x + 5)
                {
                    DIE = 1;
                }
            }
        }
        if (OB1_second == 1)
        {
            if (U_OR_D_S == 1)
            {
                if (DinosaurLeftRect.x + 50 < BirdDownRect_low_second.x + 30 && DinosaurLeftRect.x + 100 > BirdDownRect_low_second.x + 5)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurLeftRect.x + 50 < BirdUpRect_low_second.x + 30 && DinosaurLeftRect.x + 100 > BirdUpRect_low_second.x + 5)
                {
                    DIE = 1;
                }
            }
        }
        if (OB2_first == 1)
        {
            if (U_OR_D_F_M == 1)
            {
                if (DinosaurLeftRect.x + 35 < BirdDownRect_mid_first.x && DinosaurLeftRect.x + 100 > BirdDownRect_mid_first.x + 30)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurLeftRect.x + 35 < BirdUpRect_mid_first.x && DinosaurLeftRect.x + 100 > BirdUpRect_mid_first.x + 25)
                {
                    DIE = 1;
                }
            }
        }
        if (OB2_second == 1)
        {
            if (U_OR_D_F_M == 1)
            {
                if (DinosaurLeftRect.x + 35 < BirdDownRect_mid_second.x && DinosaurLeftRect.x + 100 > BirdDownRect_mid_second.x + 30)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurLeftRect.x + 35 < BirdDownRect_mid_second.x && DinosaurLeftRect.x + 100 > BirdDownRect_mid_second.x + 25)
                {
                    DIE = 1;
                }
            }
        }
        if (OB4_first == 1)
        {
            if (DinosaurLeftRect.x < Cactus_1Rect_first.x + 25 && DinosaurLeftRect.x + 85 > Cactus_1Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB4_second == 1)
        {
            if (DinosaurLeftRect.x < Cactus_1Rect_second.x + 25 && DinosaurLeftRect.x + 85 > Cactus_1Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB5_first == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_2Rect_first.x + 80 && DinosaurLeftRect.x + 85 > Cactus_2Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB5_second == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_2Rect_second.x + 80 && DinosaurLeftRect.x + 85 > Cactus_2Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB6_first == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_3Rect_first.x + 90 && DinosaurLeftRect.x + 100 > Cactus_3Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB6_second == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_3Rect_second.x + 90 && DinosaurLeftRect.x + 100 > Cactus_3Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB7_first == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_4Rect_first.x + 115 && DinosaurLeftRect.x + 100 > Cactus_4Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB7_second == 1)
        {
            if (DinosaurLeftRect.x + 20 < Cactus_4Rect_second.x + 115 && DinosaurLeftRect.x + 100 > Cactus_4Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (PooRect.x + 40 > DinosaurLeftRect.x + 50 && DinosaurLeftRect.x + 50 > PooRect.x)
        {
            Poo_Delay = 8;
        }
    }
    else if (L_OR_R == 0 && Judge_Jump == 0 && Judge_Creep == 0)
    {
        if (OB1_first == 1)
        {
            if (DinosaurRightRect.x + 50 < BirdDownRect_low_first.x + 30 && DinosaurRightRect.x + 100 > BirdDownRect_low_first.x + 5)
            {
                DIE = 1;
            }
        }
        if (OB1_second == 1)
        {
            if (DinosaurRightRect.x + 50 < BirdDownRect_low_second.x + 30 && DinosaurRightRect.x + 100 > BirdDownRect_low_second.x + 5)
            {
                DIE = 1;
            }
        }
        if (OB2_first == 1)
        {
            if (U_OR_D_F_M == 1)
            {
                if (DinosaurRightRect.x + 35 < BirdDownRect_mid_first.x && DinosaurRightRect.x + 100 > BirdDownRect_mid_first.x + 30)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurRightRect.x + 35 < BirdDownRect_mid_first.x && DinosaurRightRect.x + 100 > BirdDownRect_mid_first.x + 25)
                {
                    DIE = 1;
                }
            }
        }
        if (OB2_second == 1)
        {
            if (U_OR_D_F_M == 1)
            {
                if (DinosaurRightRect.x + 35 < BirdDownRect_mid_second.x && DinosaurRightRect.x + 100 > BirdDownRect_mid_second.x + 30)
                {
                    DIE = 1;
                }
            }
            else
            {
                if (DinosaurRightRect.x + 35 < BirdDownRect_mid_second.x && DinosaurRightRect.x + 100 > BirdDownRect_mid_second.x + 25)
                {
                    DIE = 1;
                }
            }
        }
        if (OB4_first == 1)
        {
            if (DinosaurRightRect.x < Cactus_1Rect_first.x + 25 && DinosaurRightRect.x + 85 > Cactus_1Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB4_second == 1)
        {
            if (DinosaurRightRect.x < Cactus_1Rect_second.x + 25 && DinosaurRightRect.x + 85 > Cactus_1Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB5_first == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_2Rect_first.x + 80 && DinosaurRightRect.x + 85 > Cactus_2Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB5_second == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_2Rect_second.x + 80 && DinosaurRightRect.x + 85 > Cactus_2Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB6_first == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_3Rect_first.x + 90 && DinosaurRightRect.x + 100 > Cactus_3Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB6_second == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_3Rect_second.x + 90 && DinosaurRightRect.x + 100 > Cactus_3Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (OB7_first == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_4Rect_first.x + 115 && DinosaurRightRect.x + 100 > Cactus_4Rect_first.x)
            {
                DIE = 1;
            }
        }
        if (OB7_second == 1)
        {
            if (DinosaurRightRect.x + 20 < Cactus_4Rect_second.x + 115 && DinosaurRightRect.x + 100 > Cactus_4Rect_second.x)
            {
                DIE = 1;
            }
        }
        if (PooRect.x + 40 > DinosaurRightRect.x + 50 && DinosaurRightRect.x + 50 > PooRect.x)
        {
            Poo_Delay = 8;
        }
    }
    else if (Judge_Creep == 1 && Judge_On_Land == 1)
    {
        if (L_OR_R_CREEP == 1)
        {
            // CREEP_LEFT();
            if (OB1_first == 1)
            {
                if (U_OR_D_F == 1)
                {
                    if (DinosaurCreepLeftRect.x < BirdDownRect_low_first.x + 60 && DinosaurCreepLeftRect.x + 150 > BirdDownRect_low_first.x)
                    {
                        DIE = 1;
                    }
                }
                else
                {
                    if (DinosaurCreepLeftRect.x < BirdUpRect_low_first.x + 60 && DinosaurCreepLeftRect.x + 150 > BirdUpRect_low_first.x)
                    {
                        DIE = 1;
                    }
                }
            }
            if (OB1_second == 1)
            {
                if (U_OR_D_S == 1)
                {
                    if (DinosaurCreepLeftRect.x < BirdDownRect_low_second.x + 60 && DinosaurCreepLeftRect.x + 150 > BirdDownRect_low_second.x)
                    {
                        Judge_Pause = 1;
                    }
                }
                else
                {
                    if (DinosaurCreepLeftRect.x < BirdUpRect_low_second.x + 60 && DinosaurCreepLeftRect.x + 150 > BirdUpRect_low_second.x)
                    {
                        Judge_Pause = 1;
                    }
                }
            }
            if (OB4_first == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_1Rect_first.x + 35 && DinosaurCreepLeftRect.x + 150 > Cactus_1Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB4_second == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_1Rect_second.x + 35 && DinosaurCreepLeftRect.x + 150 > Cactus_1Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB5_first == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_2Rect_first.x + 85 && DinosaurCreepLeftRect.x + 150 > Cactus_2Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB5_second == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_2Rect_second.x + 85 && DinosaurCreepLeftRect.x + 150 > Cactus_2Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB6_first == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_3Rect_first.x + 95 && DinosaurCreepLeftRect.x + 150 > Cactus_3Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB6_second == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_3Rect_second.x + 95 && DinosaurCreepLeftRect.x + 150 > Cactus_3Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB7_first == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_4Rect_first.x + 115 && DinosaurCreepLeftRect.x + 150 > Cactus_4Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB7_second == 1)
            {
                if (DinosaurCreepLeftRect.x < Cactus_4Rect_second.x + 115 && DinosaurCreepLeftRect.x + 150 > Cactus_4Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (PooRect.x + 40 > DinosaurCreepLeftRect.x + 100 && DinosaurCreepLeftRect.x + 100 > PooRect.x)
            {
                Poo_Delay = 8;
            }
        }
        else if (L_OR_R_CREEP == 0)
        {
            // CREEP_RIGHT();
            if (OB1_first == 1)
            {
                if (U_OR_D_F == 1)
                {
                    if (DinosaurCreepRightRect.x < BirdDownRect_low_first.x + 60 && DinosaurCreepRightRect.x + 150 > BirdDownRect_low_first.x)
                    {
                        DIE = 1;
                    }
                }
                else
                {
                    if (DinosaurCreepRightRect.x < BirdUpRect_low_first.x + 60 && DinosaurCreepRightRect.x + 150 > BirdUpRect_low_first.x)
                    {
                        DIE = 1;
                    }
                }
            }
            if (OB1_second == 1)
            {
                if (U_OR_D_S == 1)
                {
                    if (DinosaurCreepRightRect.x < BirdDownRect_low_second.x + 60 && DinosaurCreepRightRect.x + 150 > BirdDownRect_low_second.x)
                    {
                        Judge_Pause = 1;
                    }
                }
                else
                {
                    if (DinosaurCreepRightRect.x < BirdUpRect_low_second.x + 60 && DinosaurCreepRightRect.x + 150 > BirdUpRect_low_second.x)
                    {
                        Judge_Pause = 1;
                    }
                }
            }
            if (OB4_first == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_1Rect_first.x + 35 && DinosaurCreepRightRect.x + 150 > Cactus_1Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB4_second == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_1Rect_second.x + 35 && DinosaurCreepRightRect.x + 150 > Cactus_1Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB5_first == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_2Rect_first.x + 85 && DinosaurCreepRightRect.x + 150 > Cactus_2Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB5_second == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_2Rect_second.x + 85 && DinosaurCreepRightRect.x + 150 > Cactus_2Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB6_first == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_3Rect_first.x + 95 && DinosaurCreepRightRect.x + 150 > Cactus_3Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB6_second == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_3Rect_second.x + 95 && DinosaurCreepRightRect.x + 150 > Cactus_3Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (OB7_first == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_4Rect_first.x + 115 && DinosaurCreepRightRect.x + 150 > Cactus_4Rect_first.x)
                {
                    DIE = 1;
                }
            }
            if (OB7_second == 1)
            {
                if (DinosaurCreepRightRect.x < Cactus_4Rect_second.x + 115 && DinosaurCreepRightRect.x + 150 > Cactus_4Rect_second.x)
                {
                    DIE = 1;
                }
            }
            if (PooRect.x + 40 > DinosaurCreepRightRect.x + 100 && DinosaurCreepRightRect.x + 100 > PooRect.x)
            {
                Poo_Delay = 8;
            }
        }
    }
    else if (Judge_Jump == 1)
    {
        // BIGJUMP();
        if (OB1_first == 1)
        {
            if (U_OR_D_F == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y > BirdDownRect_low_first.y && DinosaurJumpRect.y < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 40 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 108 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_first.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_low_first.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_low_first.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_low_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y < BirdDownRect_low_first.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_low_first.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_low_first.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_low_first.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_first.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_low_first.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_low_first.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_low_first.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 30 && DinosaurJumpRect.y > BirdUpRect_low_first.y && DinosaurJumpRect.y < BirdUpRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_first.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_low_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_first.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_low_first.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_first.x + 5 && DinosaurJumpRect.x < BirdUpRect_low_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_low_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_low_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_low_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y > BirdUpRect_low_first.y && DinosaurJumpRect.y < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_low_first.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_low_first.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_low_first.y && DinosaurJumpRect.y + 50 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y > BirdUpRect_low_first.y && DinosaurJumpRect.y < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_low_first.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_low_first.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_low_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_low_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_low_first.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_low_first.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_low_first.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_low_first.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB1_second == 1)
        {
            if (U_OR_D_S_M == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y > BirdDownRect_low_second.y && DinosaurJumpRect.y < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 40 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 108 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_second.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_low_second.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_low_second.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_low_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y < BirdDownRect_low_second.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_low_second.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_low_second.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_low_second.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_second.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_low_second.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_low_second.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_low_second.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 30 && DinosaurJumpRect.y > BirdUpRect_low_second.y && DinosaurJumpRect.y < BirdUpRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_second.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_low_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_second.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_low_second.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_second.x + 5 && DinosaurJumpRect.x < BirdUpRect_low_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_low_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_low_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_low_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_low_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y > BirdUpRect_low_second.y && DinosaurJumpRect.y < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_low_second.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_low_second.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_low_second.y && DinosaurJumpRect.y + 50 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y > BirdUpRect_low_second.y && DinosaurJumpRect.y < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_low_second.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_low_second.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_low_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_low_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_low_second.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_low_second.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_low_second.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_low_second.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB2_first == 1)
        {
            if (U_OR_D_F_M == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y > BirdDownRect_mid_first.y && DinosaurJumpRect.y < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 40 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 108 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_first.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_mid_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y < BirdDownRect_mid_first.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_mid_first.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_mid_first.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_first.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_first.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_first.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_first.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_mid_first.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 30 && DinosaurJumpRect.y > BirdUpRect_mid_first.y && DinosaurJumpRect.y < BirdUpRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_first.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_first.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_first.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_first.x + 5 && DinosaurJumpRect.x < BirdUpRect_mid_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_mid_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y > BirdUpRect_mid_first.y && DinosaurJumpRect.y < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_mid_first.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_mid_first.y && DinosaurJumpRect.y + 50 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y > BirdUpRect_mid_first.y && DinosaurJumpRect.y < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_first.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_first.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_mid_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_mid_first.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_mid_first.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_mid_first.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_mid_first.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB2_second == 1)
        {
            if (U_OR_D_S_M == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y > BirdDownRect_mid_second.y && DinosaurJumpRect.y < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 40 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 108 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_second.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_mid_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y < BirdDownRect_mid_second.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_mid_second.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_mid_second.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_mid_second.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_second.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_second.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_second.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_mid_second.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 30 && DinosaurJumpRect.y > BirdUpRect_mid_second.y && DinosaurJumpRect.y < BirdUpRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_second.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_second.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_second.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_second.x + 5 && DinosaurJumpRect.x < BirdUpRect_mid_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_mid_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_mid_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_mid_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_mid_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y > BirdUpRect_mid_second.y && DinosaurJumpRect.y < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_mid_second.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_mid_second.y && DinosaurJumpRect.y + 50 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y > BirdUpRect_mid_second.y && DinosaurJumpRect.y < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_mid_second.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_mid_second.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_mid_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_mid_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_mid_second.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_mid_second.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_mid_second.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_mid_second.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB3_first == 1)
        {
            if (U_OR_D_F_H == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y > BirdDownRect_high_first.y && DinosaurJumpRect.y < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 40 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 108 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_first.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_high_first.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_high_first.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_high_first.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y < BirdDownRect_high_first.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_high_first.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_high_first.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_high_first.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_first.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_high_first.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_high_first.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_high_first.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 30 && DinosaurJumpRect.y > BirdUpRect_high_first.y && DinosaurJumpRect.y < BirdUpRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_first.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_high_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_first.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_high_first.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_first.x + 5 && DinosaurJumpRect.x < BirdUpRect_high_first.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_first.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_high_first.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_high_first.y && DinosaurJumpRect.y + 50 < BirdDownRect_high_first.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y > BirdUpRect_high_first.y && DinosaurJumpRect.y < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 40 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 108 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_high_first.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_high_first.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_high_first.y && DinosaurJumpRect.y + 50 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y > BirdUpRect_high_first.y && DinosaurJumpRect.y < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_high_first.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_high_first.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_high_first.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_high_first.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_high_first.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_high_first.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_high_first.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_high_first.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB3_second == 1)
        {
            if (U_OR_D_S_H == 1)
            {
                if ((DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y > BirdDownRect_high_second.y && DinosaurJumpRect.y < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 40 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 40 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 70 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 50 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 108 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 108 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y + 40 > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y + 40 < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x + 70 < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x + 50 < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y + 108 > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y + 108 < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_second.x + 30 && DinosaurJumpRect.x + 25 < BirdDownRect_high_second.x + 50 && DinosaurJumpRect.y + 50 > BirdDownRect_high_second.y + 15 && DinosaurJumpRect.y + 50 < BirdDownRect_high_second.y + 57) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y < BirdDownRect_high_second.y + 35) ||
                    (DinosaurJumpRect.x + 100 > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x + 100 < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y + 40 > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y + 40 < BirdDownRect_high_second.y + 35) ||
                    (DinosaurJumpRect.x + 70 > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x + 70 < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 35) ||
                    (DinosaurJumpRect.x + 50 > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x + 50 < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y + 108 > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y + 108 < BirdDownRect_high_second.y + 35) ||
                    (DinosaurJumpRect.x > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y + 70 > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y + 70 < BirdDownRect_high_second.y + 35) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_second.x + 50 && DinosaurJumpRect.x + 25 < BirdDownRect_high_second.x + 80 && DinosaurJumpRect.y + 50 > BirdDownRect_high_second.y + 20 && DinosaurJumpRect.y + 50 < BirdDownRect_high_second.y + 35))
                {
                    DIE = 1;
                }
            }
            else
            {
                if ((DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 30 && DinosaurJumpRect.y > BirdUpRect_high_second.y && DinosaurJumpRect.y < BirdUpRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 5 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 30 && DinosaurJumpRect.y + 40 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_second.x + 5 && DinosaurJumpRect.x + 70 < BirdUpRect_high_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_second.x + 5 && DinosaurJumpRect.x + 50 < BirdUpRect_high_second.x + 30 && DinosaurJumpRect.y + 108 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_second.x + 5 && DinosaurJumpRect.x < BirdUpRect_high_second.x + 30 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 25 > BirdDownRect_high_second.x + 5 && DinosaurJumpRect.x + 25 < BirdDownRect_high_second.x + 30 && DinosaurJumpRect.y + 50 > BirdDownRect_high_second.y && DinosaurJumpRect.y + 50 < BirdDownRect_high_second.y + 15) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y > BirdUpRect_high_second.y && DinosaurJumpRect.y < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y + 40 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 40 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x + 70 < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x + 50 < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y + 108 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 108 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_high_second.x + 25 && DinosaurJumpRect.x + 25 < BirdUpRect_high_second.x + 50 && DinosaurJumpRect.y + 50 > BirdUpRect_high_second.y && DinosaurJumpRect.y + 50 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y > BirdUpRect_high_second.y && DinosaurJumpRect.y < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 100 > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x + 100 < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y + 40 > BirdUpRect_high_second.y + 35 && DinosaurJumpRect.y + 40 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 70 > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x + 70 < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 50 > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x + 50 < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y + 108 > BirdUpRect_high_second.y + 35 && DinosaurJumpRect.y + 108 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y + 70 > BirdUpRect_high_second.y + 35 && DinosaurJumpRect.y + 70 < BirdUpRect_high_second.y + 50) ||
                    (DinosaurJumpRect.x + 25 > BirdUpRect_high_second.x + 50 && DinosaurJumpRect.x + 25 < BirdUpRect_high_second.x + 80 && DinosaurJumpRect.y + 50 > BirdUpRect_high_second.y + 35 && DinosaurJumpRect.y + 50 < BirdUpRect_high_second.y + 50))
                {
                    DIE = 1;
                }
            }
        }
        if (OB4_first == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_1Rect_first)) ||(SDL_PointInRect(&P2, &Cactus_1Rect_first)) || (SDL_PointInRect(&P3, &Cactus_1Rect_first)) || (SDL_PointInRect(&P4, &Cactus_1Rect_first)))
            {
                DIE = 1;
            }
        }
        if (OB4_second == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_1Rect_second)) ||(SDL_PointInRect(&P2, &Cactus_1Rect_second)) || (SDL_PointInRect(&P3, &Cactus_1Rect_second)) || (SDL_PointInRect(&P4, &Cactus_1Rect_second)))
            {
                DIE = 1;
            }
        }
        if (OB5_first == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_2Rect_first)) ||(SDL_PointInRect(&P2, &Cactus_2Rect_first)) || (SDL_PointInRect(&P3, &Cactus_2Rect_first)) || (SDL_PointInRect(&P4, &Cactus_2Rect_first)))
            {
                DIE = 1;
            }
        }
        if (OB5_second == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_2Rect_second)) ||(SDL_PointInRect(&P2, &Cactus_2Rect_second)) || (SDL_PointInRect(&P3, &Cactus_2Rect_second)) || (SDL_PointInRect(&P4, &Cactus_2Rect_second)))
            {
                DIE = 1;
            }
        }
        if (OB6_first == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_3Rect_first)) ||(SDL_PointInRect(&P2, &Cactus_3Rect_first)) || (SDL_PointInRect(&P3, &Cactus_3Rect_first)) || (SDL_PointInRect(&P4, &Cactus_3Rect_first)))
            {
                DIE = 1;
            }
        }
        if (OB6_second == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_3Rect_second)) ||(SDL_PointInRect(&P2, &Cactus_3Rect_second)) || (SDL_PointInRect(&P3, &Cactus_3Rect_second)) || (SDL_PointInRect(&P4, &Cactus_3Rect_second)))
            {
                DIE = 1;
            }
        }
        if (OB7_first == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_4Rect_first)) ||(SDL_PointInRect(&P2, &Cactus_4Rect_first)) || (SDL_PointInRect(&P3, &Cactus_4Rect_first)) || (SDL_PointInRect(&P4, &Cactus_4Rect_first)))
            {
                DIE = 1;
            }
        }
        if (OB7_second == 1)
        {
            SDL_Point P1,P2, P3, P4;
            P1.x = DinosaurJumpRect.x + 25;
            P1.y = DinosaurJumpRect.y + 108;
            P2.x = DinosaurJumpRect.x + 25;
            P2.y = DinosaurJumpRect.y + 50;
            P3.x = DinosaurJumpRect.x + 60;
            P3.y = DinosaurJumpRect.y + 60;
            P4.x = DinosaurJumpRect.x + 50;
            P4.y = DinosaurJumpRect.y + 98;
            if ((SDL_PointInRect(&P1, &Cactus_4Rect_second)) ||(SDL_PointInRect(&P2, &Cactus_4Rect_second)) || (SDL_PointInRect(&P3, &Cactus_4Rect_second)) || (SDL_PointInRect(&P4, &Cactus_4Rect_second)))
            {
                DIE = 1;
            }
        }
    }
}
// 打印字
void PRINTSTART()
{
    SDL_Texture *StartTexture = NULL;
    StartSurface = TTF_RenderUTF8_Blended(StartFont, "Dragon Slayer!Hit the Space Bar To Get Started!", StartFontColor);
    StartTexture = SDL_CreateTextureFromSurface(Renderer, StartSurface);
    StartRect.x = 10;
    StartRect.y = 500;
    StartRect.w = StartSurface->w;
    StartRect.h = StartSurface->h;
    SDL_RenderCopy(Renderer, StartTexture, NULL, &StartRect);
    SDL_DestroyTexture(StartTexture);
}
void PRINTSCORE()
{
    SDL_Texture *ScoreTexture = NULL;
    ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, "SCORE>>>", ScoreFontColor);
    ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    ScoreRect.x = 750;
    ScoreRect.y = 38;
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_DestroyTexture(ScoreTexture);
}
void PRINTSCORENUMBER()
{
    SDL_Texture *ScoreNumTexture = NULL;
    Score += 1;
    char ScoreNumChar[16];
    sprintf(ScoreNumChar, "%d", Score);
    ScoreNumSurface = TTF_RenderUTF8_Blended(ScoreNumFont, ScoreNumChar, ScoreNumFontColor);
    ScoreNumTexture = SDL_CreateTextureFromSurface(Renderer, ScoreNumSurface);
    ScoreNumRect.x = 1000;
    ScoreNumRect.y = 38;
    ScoreNumRect.w = ScoreNumSurface->w;
    ScoreNumRect.h = ScoreNumSurface->h;
    SDL_RenderCopy(Renderer, ScoreNumTexture, NULL, &ScoreNumRect);
    SDL_DestroyTexture(ScoreNumTexture);
}
// 附加
void Random_Poo(int a, int b)
{
    int Poo_Or_Not = 0;
    if (rand() % 150 == 1 && last == 0)
    {
        Poo_Or_Not = 1;
        last = 1;
        music1 = Mix_LoadWAV("resources/PooSound.mp3");
        Mix_PlayChannel(-1, music1, 0);
    }
    if (Poo_Or_Not == 1)
    {
        if (a == 1 && b == 1)
        {
            JUDGE_11 = 1;
            Poo_X = BirdDownRect_low_first.x;
        }
        if (a == 1 && b == 2)
        {
            JUDGE_12 = 1;
            Poo_X = BirdDownRect_low_second.x;
        }
        if (a == 2 && b == 1)
        {
            JUDGE_21 = 1;
            Poo_X = BirdDownRect_mid_first.x;
        }
        if (a == 2 && b == 2)
        {
            JUDGE_22 = 1;
            Poo_X = BirdDownRect_mid_second.x;
        }
        if (a == 3 && b == 1)
        {
            JUDGE_31 = 1;
            Poo_X = BirdDownRect_high_first.x;
        }
        if (a == 3 && b == 2)
        {
            JUDGE_32 = 1;
            Poo_X = BirdDownRect_high_second.x;
        }
        Poo_Or_Not = 0;
    }
}
void PrintPoo()
{
    if (Poo_X > -40)
    {
        SDL_Texture *PooTexture = NULL;
        PooSurface = IMG_Load("resources/POO.png");                      // xxx为加载图片的名字
        PooTexture = SDL_CreateTextureFromSurface(Renderer, PooSurface); // 将图片转化为纹理绑定在画笔上
        PooRect.x = Poo_X;
        PooRect.y = 450;
        PooRect.w = PooSurface->w; // 宽,可根据原图片缩放
        PooRect.h = PooSurface->h; // 高,可根据原图片缩放
        if (Score > 660)
        {
            Poo_X -= 20;
        }
        SDL_RenderCopy(Renderer, PooTexture, NULL, &PooRect);
        SDL_DestroyTexture(PooTexture);
    }
    else
    {
        last = 0;
        Poo_X = -40;
    }
}
// 结束
void GAME_OVER()
{
    SDL_Texture *OverLogoTexture = NULL;                                       // 纹理
    OverLogoSurface = IMG_Load("resources/OVER_LOGO.png");                     // xxx为加载图片的名字
    OverLogoTexture = SDL_CreateTextureFromSurface(Renderer, OverLogoSurface); // 将图片转化为纹理绑定在画笔上
    OverLogoRect.x = 400;
    OverLogoRect.y = 250;
    OverLogoRect.w = OverLogoSurface->w; // 宽,可根据原图片缩放
    OverLogoRect.h = OverLogoSurface->h; // 高,可根据原图片缩放
    SDL_RenderCopy(Renderer, OverLogoTexture, NULL, &OverLogoRect);
    SDL_DestroyTexture(OverLogoTexture);
}
void RE()
{
    Judge = 1;
    Judge_Creep = 0;
    Judge_Jump = 0;
    Score = 1;
    Land_X = 0;
    Jump_Hight = 0;
    Jump_Up = 1;
    Judge_On_Land = 1;
    Step = 40;
    Fly_Delay = 0;
    Judge_Pause = 0;
    OB1_first = 0;
    OB1_second = 0;
    OB2_first = 0;
    OB2_second = 0;
    OB3_first = 0;
    OB3_second = 0;
    OB4_first = 0;
    OB4_second = 0;
    OB5_first = 0;
    OB5_second = 0;
    OB6_first = 0;
    OB6_second = 0;
    OB7_first = 0;
    OB7_second = 0;
    limit = 60;
    DIE = 0;

    L_OR_R = 1;
    count_run = 0;
    L_OR_R_CREEP = 1;
    count_creep = 0;

    U_OR_D_F = 1;
    U_OR_D_S = 1;
    U_OR_D_F_M = 1;
    U_OR_D_S_M = 1;
    U_OR_D_F_H = 1;
    U_OR_D_S_H = 1;

    count_fly_F = 0;
    count_fly_S = 0;
    count_fly_F_M = 0;
    count_fly_S_M = 0;
    count_fly_F_H = 0;
    count_fly_S_H = 0;

    Bird_Init_X_F = 1100;
    Bird_Init_X_S = 1100;
    Bird_Init_X_F_M = 1100;
    Bird_Init_X_S_M = 1100;
    Bird_Init_X_F_H = 1100;
    Bird_Init_X_S_H = 1100;
    Cactus_Init_X_F_1 = 1100;
    Cactus_Init_X_S_1 = 1100;
    Cactus_Init_X_F_2 = 1100;
    Cactus_Init_X_S_2 = 1100;
    Cactus_Init_X_F_3 = 1100;
    Cactus_Init_X_S_3 = 1100;
    Cactus_Init_X_F_4 = 1100;
    Cactus_Init_X_S_4 = 1100;

    fly_speed = 25;
    Bird_Final_X = -80;
    Cactus_Final_X = -180;
    last = 0;
    JUDGE_11 = 0;
    JUDGE_12 = 0;
    JUDGE_21 = 0;
    JUDGE_22 = 0;
    JUDGE_31 = 0;
    JUDGE_32 = 0;
    Poo_X = -40;
    Weed_Y = -120;
    Weed_X = 1100;
    angle = 0;
    Have_Weed = 0;
    Have_Wind = 0;
    Have_Jump = 0;
    Wind_Delay = 50;
    Judge_Poo = 1;
    Poo_Delay = 0;
    Have_Halt = 0;
    Have_Lost = 0;
}
void QUIT() // 写一个退出函数，所有的退出都在这里进行
{
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(LandSurface);
    SDL_FreeSurface(WeedSurface);
    SDL_FreeSurface(DinosaurLeftSurface);
    SDL_FreeSurface(DinosaurRightSurface);
    SDL_FreeSurface(DinosaurCreepLeftSurface);
    SDL_FreeSurface(DinosaurCreepRightSurface);
    SDL_FreeSurface(DinosaurJumpSurface);
    SDL_FreeSurface(ScoreSurface);
    SDL_FreeSurface(BirdUpSurface_high_first);
    SDL_FreeSurface(BirdUpSurface_high_second);
    SDL_FreeSurface(BirdUpSurface_low_first);
    SDL_FreeSurface(BirdUpSurface_low_second);
    SDL_FreeSurface(BirdUpSurface_mid_first);
    SDL_FreeSurface(BirdUpSurface_mid_second);
    SDL_FreeSurface(BirdDownSurface_high_first);
    SDL_FreeSurface(BirdDownSurface_high_second);
    SDL_FreeSurface(BirdDownSurface_low_first);
    SDL_FreeSurface(BirdDownSurface_low_second);
    SDL_FreeSurface(BirdDownSurface_mid_first);
    SDL_FreeSurface(BirdDownSurface_mid_second);
    SDL_FreeSurface(Cactus_1Surface_first);
    SDL_FreeSurface(Cactus_2Surface_first);
    SDL_FreeSurface(Cactus_3Surface_first);
    SDL_FreeSurface(Cactus_4Surface_first);
    SDL_FreeSurface(Cactus_1Surface_second);
    SDL_FreeSurface(Cactus_2Surface_second);
    SDL_FreeSurface(Cactus_3Surface_second);
    SDL_FreeSurface(Cactus_4Surface_second);
    SDL_FreeSurface(PooSurface);
    SDL_FreeSurface(OverLogoSurface);
    TTF_CloseFont(ScoreFont);
    SDL_FreeSurface(ScoreNumSurface);
    TTF_CloseFont(ScoreNumFont);
    SDL_FreeSurface(StartSurface);
    TTF_CloseFont(StartFont);
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    Mix_FreeChunk(music1);
    Mix_FreeChunk(music2);
    Mix_FreeChunk(music3);
    Mix_FreeChunk(music4);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}