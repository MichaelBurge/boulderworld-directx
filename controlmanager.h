// controlmanager.h: interface for the controlmanager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLMANAGER_H__07C62231_AF1A_4ADA_8C33_521E2549112D__INCLUDED_)
#define AFX_CONTROLMANAGER_H__07C62231_AF1A_4ADA_8C33_521E2549112D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class controlmanager  
{
	deque<control*> controls;
public:
	void Load(char *file);
	void Process(void);
	void Add(control *thecontrol);
	controlmanager();
	virtual ~controlmanager();

};

#endif // !defined(AFX_CONTROLMANAGER_H__07C62231_AF1A_4ADA_8C33_521E2549112D__INCLUDED_)
