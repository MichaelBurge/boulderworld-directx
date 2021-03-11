// input.cpp: implementation of the input class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern draw drawing;
input::input() {
	mousex=320;
	mousey=240;
	leftclicked=false;
	rightclicked=false;
}
void input::initialize(HWND hWnd,int x2,int y2,int screenwidth2,int screenheight2)
{
	x=x2;
	y=y2;
	screenwidth=screenwidth2;
	screenheight=screenheight2;
	hwnd = hWnd;
	if (FAILED(DirectInput8Create(GetModuleHandle(0),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&directinput,NULL))) MessageBox(NULL,"Couldn't set up DirectInput",NULL,NULL);
	else {
		if (FAILED(directinput->CreateDevice(GUID_SysKeyboard,&keyboard,NULL))) MessageBox(NULL,"Couldn't make keyboard",NULL,NULL);
		else if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard)))MessageBox(NULL,"Couldn't set keyboard format",NULL,NULL);
		else if (FAILED(keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))MessageBox(NULL,"Couldn't set keyboard cooperative level",NULL,NULL);
		else keyboard->Acquire();
		if (FAILED(directinput->CreateDevice(GUID_SysMouse,&mouse,NULL)))MessageBox(NULL,"Couldn't make mouse",NULL,NULL);
		else if (FAILED(mouse->SetDataFormat(&c_dfDIMouse2)))MessageBox(NULL,"Couldn't set mouse format",NULL,NULL);
		else if (FAILED(mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))MessageBox(NULL,"Couldn't set mouse cooperative level",NULL,NULL);
		else mouse->Acquire();

	}
}

input::~input()
{
	keyboard->Unacquire();
	keyboard->Release();
	keyboard=NULL;
	mouse->Unacquire();
	mouse->Release();
	mouse=NULL;
	directinput->Release();
	directinput=NULL;
}
bool input::Update(void) {
	HRESULT h;
	if (keyboard) {
		h=keyboard->GetDeviceState(sizeof(keyboardbuffer),(void*)&keyboardbuffer);
	if (h==DIERR_INPUTLOST) {
		keyboard->Acquire();
		h=keyboard->GetDeviceState(sizeof(keyboardbuffer),(void*)&keyboardbuffer);
	}
	if (FAILED(h)) return false;

		for (int temp=0;temp<256;temp++)//Loop through, calling the callback function if the key is pressed
			if (callback&&keyboardbuffer[temp]&0x80)callback(temp);
	}
	if (mouse) {
		DIMOUSESTATE2	mousebuffer;
		h=mouse->GetDeviceState(sizeof(mousebuffer),&mousebuffer);
		if (h==DIERR_INPUTLOST) {
			mouse->Acquire();
			h=mouse->GetDeviceState(sizeof(mousebuffer),&mousebuffer);
		}
		if (FAILED(h)) return false;\
		mousex+=mousebuffer.lX;
		mousey+=mousebuffer.lY;
		xdiff=  mousebuffer.lX;
		ydiff=  mousebuffer.lY;
		if (mousex<x) mousex=x;
		if (mousex > screenwidth) mousex=screenwidth;
		if (mousey<y) mousey=y;
		if (mousey > screenheight) mousey=screenheight;
		leftclicked=mousebuffer.rgbButtons[0]&0x80;
		rightclicked=mousebuffer.rgbButtons[1]&0x80;
		
	}
	return true;
}

int input::KeyPressed(int key) {
	return keyboardbuffer[key]&0x80;
}

void input::SetCallback(void (*target)(char)) {
	callback=target;
}

void input::SetKey(int key,int value) {
	keyboardbuffer[key]=value;
}