// checkbox.h: interface for the checkbox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKBOX_H__73807191_9E04_464A_8141_EA362B8F121A__INCLUDED_)
#define AFX_CHECKBOX_H__73807191_9E04_464A_8141_EA362B8F121A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const int CCHECKBOX_SETPICTURE =0;
const int CCHECKBOX_SETCALLBACK=1;
class checkbox:public control {
	int onpicture,offpicture;
	bool fine;
	bool selected;
	void (*callback)(bool);
public:
	unsigned char IsStandard(void) {return STANDARDID_CHECKBOX;};
	checkbox();
	void Process(void);
	virtual ~checkbox();

};

#endif // !defined(AFX_CHECKBOX_H__73807191_9E04_464A_8141_EA362B8F121A__INCLUDED_)
