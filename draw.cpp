// draw.cpp: implementation of the draw class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
draw::draw()
{
current=0;
clearcolor=RGB(256,256,256);
width=WIDTH;
height=HEIGHT;
background=0;
target=false;
}

draw::~draw()
{
	kill();
}

void draw::initialize(HWND hwnd) {
	HRESULT h;
	DirectDrawCreateEx(NULL, (void **)&directdraw, IID_IDirectDraw7, NULL);
	directdraw->SetCooperativeLevel(hwnd,DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT);
	directdraw->SetDisplayMode(width,height,32,0,0);
	DDSURFACEDESC2	ddsd;

	// Create the primary surface with two back buffers.
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			DDSCAPS_FLIP |
			DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 2;
	h = directdraw->CreateSurface(&ddsd, &primary, NULL);
	ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
	primary->GetAttachedSurface(&ddsd.ddsCaps, &backbuffer);
	directdraw->FlipToGDISurface();
}
void draw::kill(void) {
	for (int temp=current;temp>0;temp--) {
		pictures[temp-1]->Release();
		pictures.pop_back();
	}
	if (primary)primary->Release();
	primary=NULL;
	if (directdraw)directdraw->Release();
	directdraw = NULL;
}
int draw::LoadSurface(char * file) {
	picturesource.push_back(file);
	pictures.push_back(DDLoadBitmap(directdraw, file, 0, 0));
	return current++;
}

BOOL draw::DrawPicture(int x, int y, int picture, RECT *rect) {
	int originalx=rect->right,originaly=rect->bottom;
	bool xchanged=false,ychanged=false;
	DDSetColorKey(pictures[picture],background);
	if (x <0) {//Clip the left and top of the rectangle. The bottom and right are below.
		originalx=rect->left;
		rect->left-=x;
		x=0;
		xchanged=true;
		
	}
	if (y<0) {
		originaly=rect->top;
		rect->top-=y;
		y=0;
		ychanged=true;
		
	}
	
	
	if (rect->right>rect->left&&(x+(rect->right-rect->left))>width-1) {rect->right-=((rect->right-rect->left)+x)-width;xchanged=true;}//Clip the rectangle
	if ((y+(rect->bottom-rect->top))>height-1) {rect->bottom-=((rect->bottom-rect->top)+y)-height;ychanged=true;}
	HRESULT h = (target?primary:backbuffer)->BltFast(x,y,pictures[picture],rect,DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);//Draw the picture
	if (xchanged) if (x>0)rect->right=originalx;else rect->left=originalx;
	if (ychanged) if (y>0)rect->bottom=originaly;else rect->top=originaly;//If we altered the rectangle while clipping it, set it back to normal
	return h;
}
BOOL draw::DrawWithoutInvisible(int x, int y, int picture, RECT *rect) {
	int originalx=rect->right,originaly=rect->bottom;
	bool xchanged=false,ychanged=false;
	if (x <0) {//Clip the left and top of the rectangle. The bottom and right are below.
		originalx=rect->left;
		rect->left-=x;
		x=0;
		xchanged=true;
		
	}
	if (y<0) {
		originaly=rect->top;
		rect->top-=y;
		y=0;
		ychanged=true;
		
	}
	
	
	if (rect->right>rect->left&&(x+(rect->right-rect->left))>width-1) {rect->right-=((rect->right-rect->left)+x)-width;xchanged=true;}//Clip the rectangle
	if ((y+(rect->bottom-rect->top))>height-1) {rect->bottom-=((rect->bottom-rect->top)+y)-height;ychanged=true;}
	HRESULT h = (target?primary:backbuffer)->BltFast(x,y,pictures[picture],rect,DDBLTFAST_WAIT);//Draw the picture
	if (xchanged) if (x>0)rect->right=originalx;else rect->left=originalx;
	if (ychanged) if (y>0)rect->bottom=originaly;else rect->top=originaly;//If we altered the rectangle while clipping it, set it back to normal
	return h;
}
BOOL draw::DrawPictureSpecial(RECT *dest,int picture, RECT *src,int flags,DDBLTFX *fx) {
	DDSetColorKey(pictures[picture],background);
	return (target?primary:backbuffer)->Blt(dest,pictures[picture],src,flags,fx);
}
BOOL draw::DrawPictureRotation(int x, int y,int width,int height, int picture, RECT *rect,short rotation) {
	RECT temp = {x,y,width,height};
	DDBLTFX fx;
	ZeroMemory(&fx,sizeof(fx));
	fx.dwSize = sizeof(fx);
	fx.dwRotationAngle = rotation;
	DDSetColorKey(pictures[picture],background);
	return (target?primary:backbuffer)->Blt(&temp,pictures[picture],rect,DDBLT_ROTATIONANGLE|DDBLT_KEYDEST,&fx);
}

BOOL draw::Clear(void) {
	RECT rectangle = {0,0,width,height};
	DDBLTFX fx;
	ZeroMemory(&fx,sizeof(fx));
	fx.dwFillColor = clearcolor;
	fx.dwSize = sizeof(fx);
	return (target?primary:backbuffer)->Blt(&rectangle,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT|DDBLT_ASYNC,&fx);
}
BOOL draw::Flip(void) {
	HRESULT h = primary->Flip(NULL,DDFLIP_WAIT);
	return h;
}

void draw::SetClearColor(int color) {
	clearcolor=color;
}
int draw::DrawColor(int x,int y,int x2,int y2,int color) {
	HRESULT h;
	HDC hdc;
	LOGBRUSH logbrush = {BS_SOLID,color,NULL};
	(target?primary:backbuffer)->GetDC(&hdc);
	HPEN hpen = (HPEN)SelectObject(hdc,CreateBrushIndirect(&logbrush));//Create brush, select it in, and delete the previous one
	h = Rectangle(hdc,x,y,x2+1,y2+1);
	DeleteObject(SelectObject(hdc,hpen));
	(target?primary:backbuffer)->ReleaseDC(hdc);
	return h;
}



void draw::SetBackground(COLORREF color) {
	background=color;
}

void draw::DrawLine(int x,int y,int x2,int y2, COLORREF color) {
	HDC hdc;
	(target?primary:backbuffer)->GetDC(&hdc);
	HPEN hpen = (HPEN)SelectObject(hdc,CreatePen(PS_SOLID,0,color));
	MoveToEx(hdc,x,y,NULL);
	LineTo(hdc,x2,y2);
	DeleteObject(SelectObject(hdc,hpen));
	(target?primary:backbuffer)->ReleaseDC(hdc);
}

IDirectDrawSurface7 *draw::ReturnPicture(int picture) {
	return pictures[picture];
}

void draw::DrawText(char *text,int x,int y,COLORREF color) {
	HDC hdc;
	RECT rect = {x,y,x+1,y+1};
	(target?primary:backbuffer)->GetDC(&hdc);
	SetTextColor(hdc,color);
	SetBkMode(hdc,TRANSPARENT);
	::DrawText(hdc,text,-1,&rect,DT_NOCLIP);
	(target?primary:backbuffer)->ReleaseDC(hdc);
}
void draw::DrawNumber(int number,int x,int y,COLORREF color) {
	char buffer[256];
	for (int temp=0;temp<256;temp++)
		buffer[temp]=0;
	itoa(number,buffer,10);
	DrawText(buffer,x,y,color);
}

void draw::DrawPictureRepeat(int picture,int picwidth,int picheight,int x,int y, int endx,int endy) {
	RECT rect = {0,0,picwidth,picheight};
	for (int temp=x;temp<endx;temp+=picwidth)
		for (int temp2=y;temp2<endy;temp2+=picheight) {
			int tempx=rect.right;
			int tempy=rect.bottom;
			if (temp+picwidth>endx) rect.right-=(temp+picwidth)-endx;
			if (temp2+picheight>endy)rect.bottom-=(temp2+picheight)-endy;
			
			DrawPicture(temp,temp2,picture,&rect);
			rect.right=tempx;
			rect.bottom=tempy;
		}
}

void draw::SetTarget(bool thetarget) {
	target=thetarget;
}

HDC draw::Lock(void) {

	backbuffer->GetDC(&lockdc);
	return lockdc;
}

void draw::Unlock(void) {
	backbuffer->ReleaseDC(lockdc);
}