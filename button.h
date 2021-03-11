// button.h: interface for the button class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUTTON_H__945D8A57_01D4_47CA_BC00_C5AE4865DCE1__INCLUDED_)
#define AFX_BUTTON_H__945D8A57_01D4_47CA_BC00_C5AE4865DCE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int CBUTTON_SETUP =0;
const int CBUTTON_SETDOWN =1;
const int CBUTTON_SETCALLBACK=2;
const int CBUTTON_GETDOWN=3;
const int CBUTTON_SETEXTRA=4;
const int CBUTTON_SOLID=5;
class button:public control {
	int uppicture,downpicture;
	void (*callback)(bool pressed,void *);
	void *extra;
	char *callbackname;
	bool pressed;
	bool solidity;
public:
	unsigned char IsStandard(void) {return STANDARDID_BUTTON;};
	button();
	char *Save(void);
	char *Load(void);
	void virtual Process();
	virtual ~button();

};

#endif // !defined(AFX_BUTTON_H__945D8A57_01D4_47CA_BC00_C5AE4865DCE1__INCLUDED_)
