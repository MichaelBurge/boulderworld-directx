// ai.h: interface for the ai class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AI_H__D6D3BB07_4BEB_4DE3_8A25_BA7E132963A3__INCLUDED_)
#define AFX_AI_H__D6D3BB07_4BEB_4DE3_8A25_BA7E132963A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
struct unit;
struct planet;
class ai {
	vector<unit*> units;
	vector<planet*> untakenplanets;
	
	int planets;
public:
	int player;
	void CreateShip(void);
	void checkplanets(void);
	void regetunits(void);
	void process(void);
	void processunit(unit *theunit);
	bool safe(int x,int y,double distance);
	ai();
	~ai();

};

#endif // !defined(AFX_AI_H__D6D3BB07_4BEB_4DE3_8A25_BA7E132963A3__INCLUDED_)
