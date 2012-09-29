// recmp3Dlg.h : header file
//

#if !defined(AFX_RECMP3DLG_H__692619CD_EE54_4471_B598_1A114B57908B__INCLUDED_)
#define AFX_RECMP3DLG_H__692619CD_EE54_4471_B598_1A114B57908B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lame.h"

/////////////////////////////////////////////////////////////////////////////
// CRecmp3Dlg dialog

class CRecmp3Dlg : public CDialog
{
// Construction
public:
	unsigned long m_numsecsrecorded;
	WAVEFORMATEX m_wfe;
	BOOL m_isRecording;
	void stop_recording();
	BOOL start_recording();
	int log(LPCTSTR text);
	CRecmp3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRecmp3Dlg)
	enum { IDD = IDD_RECMP3_DIALOG };
	CStatic	m_textstatus;
	CButton	m_g3;
	CButton	m_g2;
	CButton	m_g1;
	CComboBox	m_inputdevices;
	CButton	m_recordbtn;
	CListBox	m_log;
	CString	m_outfilepath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecmp3Dlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	lame_global_flags * m_lgf;
	HWAVEIN m_hWaveIn;
	FILE * m_outFile;
	CFont m_boldFont;

	// Generated message map functions
	//{{AFX_MSG(CRecmp3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowsebtn();
	afx_msg void OnRecordbtn();
	afx_msg void OnAboutButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECMP3DLG_H__692619CD_EE54_4471_B598_1A114B57908B__INCLUDED_)
