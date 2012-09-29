// recmp3.h : main header file for the RECMP3 application
//

#if !defined(AFX_RECMP3_H__9A75A705_1104_4D9A_8F52_38C9275ED228__INCLUDED_)
#define AFX_RECMP3_H__9A75A705_1104_4D9A_8F52_38C9275ED228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRecmp3App:
// See recmp3.cpp for the implementation of this class
//

class CRecmp3App : public CWinApp
{
public:
	CRecmp3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecmp3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRecmp3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECMP3_H__9A75A705_1104_4D9A_8F52_38C9275ED228__INCLUDED_)
