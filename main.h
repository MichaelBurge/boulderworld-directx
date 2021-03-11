#ifndef main
#define DIRECTINPUT_VERSION 0x0800
#include <vector>
#include <deque>
#include <ddraw.h>
#include <dinput.h>
#include <DMUSICC.H>
#include <DMUSICI.H>
#include <stdlib.h>
#include <windows.h>
#include <math.h>//Include C math header
#include <d3d9.h>
#include <d3dx9math.h>
//#include <stdlib.h>
using namespace std;

#include "ddutil.h"
#include "input.h"
#include "draw.h"
#include "debug.h"
#include "d3d.h"
#include "engine.h"
#include "music.h"
#include "math.h"//Include my math header
#include "strings.h"

#include "controls.h"
extern HWND hwnd;
extern int selectedkey,target,targetted;
extern int playerside;
extern int firstplanet;
extern int win,lose;
extern int state;
extern int redx;
extern int playercolors[];
extern int bottomgui;
bool dxtoascii(char character,bool shift,unsigned char *dest);
extern int WIDTH,HEIGHT;
#define main
#endif