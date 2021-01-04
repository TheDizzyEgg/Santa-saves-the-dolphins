//#ifndef _DECLS
#define _DECLS
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdarg.h>
#include "windows.h"
#include "allegro5/allegro_opengl.h"
#include "allegro5/allegro_windows.h"
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <irrKlang.h>

#include "_Santa.h"
#include "_System.h"
#include "_Map.h"
#include "_Snowflake.h"
#include "_Shader.h"
#include "_Penguin.h"
#include "_SoundMusic.h"

#define LOG_FILE_PATH "GameLog.txt"


void writeLog(const char *errorMessage, int exitCode);
void updateAll();
bool compareColors(ALLEGRO_COLOR colorA, ALLEGRO_COLOR colorB);
bool isBitSet(int x, int y) ;
void renderAll();
int runIntro();
int runStartScreen();
void drawHUD();
void drawInfo();


class _Santa;
class _Footstep;
class _Map;
class _System;
class _Snowflake;
class _SnowflakeSystem;
class _ShaderSystem;
class _Penguin;
class _PenguinSystem;
class _SoundMusic;



//#endif
