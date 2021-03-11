// draw.h: interface for the draw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_H__55130969_BD47_4DA2_AC78_D50D08110527__INCLUDED_)
#define AFX_DRAW_H__55130969_BD47_4DA2_AC78_D50D08110527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"

const bool BACKBUFFER	=false;
const bool PRIMARY		=true;
class draw {
	vector<IDirectDrawSurface7 *> pictures;
	deque<char *> picturesource;
	int current;
	int clearcolor;
	bool target;
public:
	IDirectDraw7		*directdraw;
	IDirectDrawSurface7 *primary;
	IDirectDrawSurface7 *backbuffer;
	
	HDC lockdc;
	HDC Lock(void);
	void Unlock(void);

	int background;
	int width,height;

	BOOL Clear(void);
	BOOL Flip(void);

	void SetTarget(bool thetarget);
	void initialize(HWND hwnd);
	void kill(void);
	void SetClearColor(int color);
	void LoadFont(char *file,char *characters,int charwidth,int charheight,int width,int height);
	void ReloadSurfaces(void);
	void SetBackground(COLORREF color);
	void DrawLine(int x,int y,int x2,int y2, COLORREF color);
	void DrawText(char *text,int x,int y,COLORREF color);
	void DrawNumber(int number,int x,int y,COLORREF color);
	void DrawPictureRepeat(int picture,int picwidth,int picheight,int x,int y, int endx,int endy);

	int DrawColor(int x,int y,int width,int height,int color);
	int LoadSurface(char *file);
	int DrawPicture(int x, int y, int picture, RECT *rect);
	int DrawPictureSpecial(RECT *dest,int picture, RECT *src,int flags,DDBLTFX *fx);
	int DrawWithoutInvisible(int x, int y, int picture, RECT *rect);
	int DrawPictureRotation(int x, int y,int width,int height, int picture, RECT *rect,short rotation);

	IDirectDrawSurface7 *ReturnPicture(int picture);

	
	draw();
	~draw();

};

#endif // !defined(AFX_DRAW_H__55130969_BD47_4DA2_AC78_D50D08110527__INCLUDED_)
