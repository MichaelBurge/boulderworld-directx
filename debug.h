// debug.h: interface for the debug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUG_H__94EF589A_DF7E_49B3_8D50_68DE9A6A3A14__INCLUDED_)
#define AFX_DEBUG_H__94EF589A_DF7E_49B3_8D50_68DE9A6A3A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
class debug  
{
	char *nameoffile;
	FILE *file;
public:
	void SetFile(char *target);
	void logdata(char *);
	void logdata(int);
	debug();
	virtual ~debug();

};
#include "main.h"
#endif // !defined(AFX_DEBUG_H__94EF589A_DF7E_49B3_8D50_68DE9A6A3A14__INCLUDED_)
