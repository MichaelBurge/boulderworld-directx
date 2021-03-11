#include "main.h"
bool running=true;
HWND hwnd;
int selectedkey,target,targetted;
TCHAR szWindowClass[] = "Window";
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
long _stdcall WndProc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam);

draw drawing;
input gameinput;
engine gameengine;
music gamemusic;
window tehwindow;
button exitbutton;
button mapeditor;
edit editbox;
debug debugger;
int screenx=0,screeny=0;
int x=0,y=0;
int state=0;
int win,lose;
bool initialized=false;
int title=0,editor=0,exit2=0,premade=0,arrow=0;
int WIDTH=800,HEIGHT=600;
int arrowlocation=0;
bool keyokay=true;
void inputprocess(char key) {
	static bool window=true;
	switch(key) {
	case DIK_F2:
		window=!window;
		//tehwindow.GiveMessage(CONTROL_ACTIVATE,window,0);
	}
}
void exitcall(bool pressed) {
	if (pressed) 
		running=false;
}
void mapcall(bool pressed) {
	if (pressed)
		state=1;
}
void Process(void) {
    RECT rect = {0,0,32,32};
	RECT rect2= {0,0,639,200};
	RECT rect3= {0,0,320,100};
	RECT rect4= {0,0,32,64};
	HDC hdc;
   gameinput.Update();
   x = gameinput.mousex;
   y = gameinput.mousey;
   if (x < 16) x=16;
   if (x >= drawing.width-16) x=drawing.width-17;
   if (y < 16) y=16;
   if (y >= drawing.height-16) y=drawing.height-17;
   
   
   if (gameinput.KeyPressed(DIK_ESCAPE)) {running=false;return;}
   int UP = DIK_UP;
   int DOWN=DIK_DOWN;
   int LEFT=DIK_LEFT;
   int RIGHT=DIK_RIGHT;
   //  SetCursorPos(x,y);
   drawing.Clear();
   switch(state) {
   case 0:
	   drawing.DrawPicture(0,0,title,&rect2);
	   drawing.DrawPicture(0,300,editor,&rect3);
	   drawing.DrawPicture(480,300,exit2,&rect3);
	   drawing.DrawPicture(160,500,premade,&rect3);
	   exitbutton.Process();
	   mapeditor.Process();
	   break;
   case 1:
   case 2:gameengine.Process();break;
   case 3:state=0;return;
   }
   drawing.DrawPicture(x-16,y-16,target,&rect);
   drawing.Flip();

}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}


void cheese(void) {
	state=1;
}
int _stdcall WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int nshowcmd) {
	MSG msg;
	MyRegisterClass(hinstance);
	hwnd=CreateWindowEx(WS_EX_APPWINDOW|WS_EX_TOPMOST	,
		szWindowClass, "DirectX RTS", WS_POPUP,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		NULL, NULL, hinstance, NULL);
	ShowWindow(hwnd,1);
	if (hwnd) {
		//drawing.SetBackground(CLR_INVALID);
		gamemusic.LoadMusic(L"music.mid",DMUS_SEG_REPEAT_INFINITE,GUID_StandardMIDIFile);
		gamemusic.PlayMusic(0);
		gameinput.initialize(hwnd,0,0,WIDTH,HEIGHT);
		gameinput.SetCallback(inputprocess);
		ShowCursor(NULL);
		debugger.SetFile("log.txt");
		debugger.logdata("testing");
		drawing.initialize(hwnd);
		target=drawing.LoadSurface("target.bmp");
		title=drawing.LoadSurface("title.bmp");
		editor=drawing.LoadSurface("editor.bmp");
		exit2=drawing.LoadSurface("exit.bmp");
		premade=drawing.LoadSurface("premade.bmp");
		arrow=drawing.LoadSurface("arrow.bmp");
		tehwindow.GiveMessage(CONTROL_SETPOS,0,0);
		tehwindow.GiveMessage(CONTROL_SETSIZE,200,200);
		tehwindow.GiveMessage(CONTROL_ACTIVATE,1,0);
		tehwindow.GiveMessage(CWINDOW_SETCLOSEPICTURES,drawing.LoadSurface("close.bmp"),drawing.LoadSurface("closedown.bmp"));
		tehwindow.GiveMessage(CWINDOW_SETCLOSECALLBACK,(int)cheese,0);
		tehwindow.GiveMessage(CWINDOW_TOGGLECLOSEBUTTON,1,0);
		editbox.GiveMessage(CONTROL_SETPOS,0,0);
		editbox.GiveMessage(CONTROL_SETSIZE,100,100);
		editbox.GiveMessage(CONTROL_ACTIVATE,1,0);
		editbox.GiveMessage(CEDIT_SETBGCOLOR,RGB(0,0,0),0);
		editbox.GiveMessage(CEDIT_SETTOPLEFTCOLOR,RGB(192,192,192),0);
		editbox.GiveMessage(CEDIT_SETBOTTOMRIGHTCOLOR,RGB(92,92,92),0);
		editbox.GiveMessage(CEDIT_SETCARETCOLOR,RGB(128,128,128),0);
		editbox.GiveMessage(CEDIT_SETTEXTCOLOR,RGB(192,192,192),0);
		editbox.SetParent(&tehwindow);
		exitbutton.GiveMessage(CONTROL_SETPOS,480,300);
		exitbutton.GiveMessage(CONTROL_SETSIZE,320,240);
		exitbutton.GiveMessage(CONTROL_ACTIVATE,1,0);
		exitbutton.GiveMessage(CBUTTON_SETUP,drawing.LoadSurface("exit.bmp"),0);
		exitbutton.GiveMessage(CBUTTON_SETCALLBACK,(int)exitcall,0);
		mapeditor.GiveMessage(CONTROL_SETPOS,0,300);
		mapeditor.GiveMessage(CONTROL_SETSIZE,320,240);
		mapeditor.GiveMessage(CONTROL_ACTIVATE,1,0);
		mapeditor.GiveMessage(CBUTTON_SETUP,drawing.LoadSurface("editor.bmp"),0);
		mapeditor.GiveMessage(CBUTTON_SETCALLBACK,(int)mapcall,0);
		gameengine.Load();
		gameengine.initialize(target);
		while (running) {
			if (PeekMessage(&msg,0,0,0,PM_NOREMOVE)) {
				if (!GetMessage(&msg,0,0,0)) running = false;
				else DispatchMessage(&msg);
			} else Process();
		}
	} else MessageBox(NULL,NULL,NULL,NULL);
	return 0;
}

long _stdcall WndProc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_DESTROY:
		DestroyWindow(hwnd);
		running=false;
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		running=false;
		break;
	default:
		return DefWindowProc(hwnd,message,wparam,lparam);
	
	}
	return TRUE;
}



