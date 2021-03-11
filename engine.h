// engine.h: interface for the engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_)
#define AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"

class engine  {
	char **field;
	char **backup;
	int width,height,start;
	bool changed;
	int diamondcount;
	int target;
	text	savetext;
	text	loadtext;
	edit	saveedit;
	edit	loadedit;
	window toolswindow;
	button blanktool;
	button fungustool;
	button runbutton;
	button bricktool;
	button playertool;
	button grasstool;
	button bouldertool;
	button diamondtool;
	button firetool;
public:
	window	save;
	window	load;
	int tool;
	friend void SaveMap(char *filename);
	friend void LoadMap(char *filename);
	void Fill(int x,int y);
	void SaveState(void);
	void LoadState(void);
	void ProcessField(void);
	void Plot(int newval,int x,int y);
	void initialize(int target2);
	engine(void);
	void Redraw(void);
	void Resize(int width2,int height2);
	void Load(void);
	void Process(void);
};

#endif // !defined(AFX_ENGINE_H__41D04E05_498F_41E0_843A_63640A3B5513__INCLUDED_)
