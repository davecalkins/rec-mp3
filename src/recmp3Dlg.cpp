// recmp3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "recmp3.h"
#include "recmp3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecmp3Dlg dialog

CRecmp3Dlg::CRecmp3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecmp3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecmp3Dlg)
	m_outfilepath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_lgf = NULL;
	m_isRecording = FALSE;
	m_hWaveIn = 0;
	m_outFile = NULL;
}

void CRecmp3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecmp3Dlg)
	DDX_Control(pDX, IDC_TEXTSTATUS, m_textstatus);
	DDX_Control(pDX, IDC_G3, m_g3);
	DDX_Control(pDX, IDC_G2, m_g2);
	DDX_Control(pDX, IDC_G1, m_g1);
	DDX_Control(pDX, IDC_INPUTDEVICES, m_inputdevices);
	DDX_Control(pDX, IDC_RECORDBTN, m_recordbtn);
	DDX_Control(pDX, IDC_LOG, m_log);
	DDX_Text(pDX, IDC_OUTFILE, m_outfilepath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRecmp3Dlg, CDialog)
	//{{AFX_MSG_MAP(CRecmp3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSEBTN, OnBrowsebtn)
	ON_BN_CLICKED(IDC_RECORDBTN, OnRecordbtn)
	ON_BN_CLICKED(IDC_ABOUT_BUTTON, OnAboutButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecmp3Dlg message handlers

BOOL CRecmp3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	UINT numDevs = waveInGetNumDevs();
	for (UINT x = 0; x < numDevs; x++)
	{
		WAVEINCAPS wic;
		if (waveInGetDevCaps(x,&wic,sizeof(WAVEINCAPS)) == MMSYSERR_NOERROR)
		{
			m_inputdevices.AddString(wic.szPname);
		}
	}
	if (m_inputdevices.GetCount() > 0)
	{
		m_inputdevices.SetCurSel(0);
	}

	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	m_boldFont.CreateFontIndirect(&lf);
	m_g1.SetFont(&m_boldFont,TRUE);
	m_g2.SetFont(&m_boldFont,TRUE);
	m_g3.SetFont(&m_boldFont,TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CRecmp3Dlg::DestroyWindow() 
{
	stop_recording();

	return CDialog::DestroyWindow();
}

void CRecmp3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecmp3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRecmp3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CRecmp3Dlg::log(LPCTSTR text)
{
	CTime t(time(0));
	CString outf;
	outf.Format("%s - %s", t.Format("%H:%M:%S"), text);

	int idx = m_log.AddString(outf);
	m_log.SetCaretIndex(idx,TRUE);
	return idx;
}

BOOL CRecmp3Dlg::start_recording()
{
	CWaitCursor w;

	BOOL result = FALSE;

	log("START");

	if (UpdateData(TRUE))
	{
		int inputDevID = m_inputdevices.GetCurSel();
		if (inputDevID < 0)
		{
			log("ERROR: you must select an input device");
		}
		else
		{
			if (m_outfilepath.GetLength() == 0)
			{
				log("ERROR: you must specify an output file");
			}
			else
			{
				m_outFile = fopen(m_outfilepath,"wb+");
				if (m_outFile == NULL)
				{
					log("ERROR: unable to open output file");
				}
				else
				{
					log("opened output file");

					m_lgf = lame_init();
					if (m_lgf == NULL)
					{
						log("ERROR: unable to initialize LAME encoder (lame_init() failed)");
					}
					else
					{
						if (lame_init_params(m_lgf) < 0)
						{
							log("ERROR: unable to initialize the LAME encoder (lame_init_params() failed)");
						}
						else
						{
							CString s;
							s.Format("initialized LAME mp3 encoder %s", get_lame_version());
							log(s);

							ZeroMemory(&m_wfe,sizeof(WAVEFORMATEX));
							m_wfe.wFormatTag = WAVE_FORMAT_PCM;
							m_wfe.nChannels = 2;
							m_wfe.nSamplesPerSec = 44100;
							m_wfe.wBitsPerSample = 16;
							m_wfe.nBlockAlign = m_wfe.nChannels * (m_wfe.wBitsPerSample / 8);
							m_wfe.nAvgBytesPerSec = m_wfe.nSamplesPerSec * m_wfe.nBlockAlign;

							if (waveInOpen(&m_hWaveIn,WAVE_MAPPER,&m_wfe,(DWORD_PTR)GetSafeHwnd(),0,CALLBACK_WINDOW) != MMSYSERR_NOERROR)
							{
								log("ERROR: unable to initialize audio input device");
							}
							else
							{
								log("initialized audio input device");
								
								const long numBuffers = 10;
								const long bufferSizeSeconds = 1;
								const long bufferSize = m_wfe.nSamplesPerSec * (m_wfe.wBitsPerSample / 8) * m_wfe.nChannels * bufferSizeSeconds;

								result = TRUE;

								for (long x = 0; x < numBuffers; x++)
								{
									char * bufData = new char[bufferSize];
									if (bufData != 0)
									{
										ZeroMemory(bufData,bufferSize);

										WAVEHDR * bufHdr = new WAVEHDR;
										if (bufHdr != 0)
										{
											ZeroMemory(bufHdr,sizeof(WAVEHDR));
											bufHdr->lpData = bufData;
											bufHdr->dwBufferLength = bufferSize;

											if (waveInPrepareHeader(m_hWaveIn,bufHdr,sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
											{
												result = FALSE;
											}
											else
											{
												if (waveInAddBuffer(m_hWaveIn,bufHdr,sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
												{
													result = FALSE;
												}
											}
										}
									}
								}

								if (!result)
								{
									log("ERROR: unable to initialize memory buffers");
								}
								else
								{
									CString s;
									s.Format("initialized %d memory buffers (%d bytes each)",
										numBuffers,
										bufferSize);
									log(s);

									if (waveInStart(m_hWaveIn) != MMSYSERR_NOERROR)
									{
										log("ERROR: unable to start recording");
										result = FALSE;
									}
									else
									{
										log("started recording");
										result = TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (!result)
	{
		stop_recording();
	}
	else
	{
		m_recordbtn.SetWindowText("STOP");
		m_isRecording = TRUE;
		m_numsecsrecorded = 0;
		m_textstatus.SetWindowText("Recorded: 0 secs");
		m_textstatus.ShowWindow(SW_SHOW);
	}

	return result;
}

void CRecmp3Dlg::stop_recording()
{
	CWaitCursor w;

	if (m_hWaveIn != 0)
	{
		waveInStop(m_hWaveIn);
		waveInReset(m_hWaveIn);
		log("stopped recording");
		waveInClose(m_hWaveIn);
		log("shutdown input audio device");
		m_hWaveIn = 0;
	}

	if (m_lgf != NULL)
	{
		if (m_isRecording)
		{
			unsigned char mp3buffer[7200];
			int mp3bytes = lame_encode_flush(m_lgf,mp3buffer,7200);
			if (mp3bytes < 0)
			{
				log("ERROR: unable to flush the LAME mp3 encoder buffers");
			}
			else
			{
				fwrite(mp3buffer,1,mp3bytes,m_outFile);
				log("flushed the LAME mp3 encoder buffers");
			}
		}

		lame_close(m_lgf);
		m_lgf = NULL;
		log("shutdown LAME mp3 encoder");
	}

	if (m_outFile != NULL)
	{
		fflush(m_outFile);
		fclose(m_outFile);
		m_outFile = NULL;
		log("closed output file");
	}

	m_recordbtn.SetWindowText("START");
	m_isRecording = FALSE;
	m_textstatus.ShowWindow(SW_HIDE);

	log("STOP");
}

void CRecmp3Dlg::OnBrowsebtn() 
{
	CTime t(time(0));
	CString outf;
	outf.Format("recorded-%s.mp3",t.Format("%Y-%m-%d"));

	CFileDialog fd(FALSE,".mp3",outf,OFN_OVERWRITEPROMPT,"mp3 audio files (*.mp3)|*.mp3|All Files (*.*)|*.*||");
	if (fd.DoModal() == IDOK)
	{
		m_outfilepath = fd.GetPathName();
		UpdateData(FALSE);
	}
}

void CRecmp3Dlg::OnRecordbtn() 
{
	if (m_isRecording)
	{
		stop_recording();
	}
	else
	{
		start_recording();
	}
}

LRESULT CRecmp3Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == MM_WIM_DATA)
	{
		WAVEHDR * wh = (WAVEHDR *)lParam;

		if (m_isRecording)
		{
			unsigned long num_samples = wh->dwBytesRecorded / 4;
			unsigned long mp3buffer_size = (unsigned long)(1.25 * (double)num_samples) + 7200;
			
			unsigned char * mp3buffer = new unsigned char[mp3buffer_size];

			short int * pcmleft = new short int[num_samples];
			short int * pcmright = new short int[num_samples];

			short int * pcmdata = (short int *)wh->lpData;
			unsigned long x,y;
			for (x = 0, y = 0; x < (num_samples*2); x += 2, y++)
			{
				pcmleft[y] = pcmdata[x];
				pcmright[y] = pcmdata[x+1];
			}

			int mp3bytes = lame_encode_buffer(m_lgf,
				pcmleft, pcmright,
				num_samples,mp3buffer,mp3buffer_size);
			if (mp3bytes < 0)
			{
				log("ERROR: unable to encode audio buffer to mp3");
			}
			else
			{
				fwrite(mp3buffer,1,mp3bytes,m_outFile);
			}

			delete [] pcmright;
			delete [] pcmleft;

			delete [] mp3buffer;

			waveInAddBuffer(m_hWaveIn,wh,sizeof(WAVEHDR));

			m_numsecsrecorded += (unsigned long)(((double)1.0 / (double)m_wfe.nSamplesPerSec) * (double)num_samples);
			CString s;
			s.Format("Recorded: %d secs", m_numsecsrecorded);
			m_textstatus.SetWindowText(s);
		}
		else
		{
			delete [] wh->lpData;
			delete wh;
		}
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CRecmp3Dlg::OnAboutButton() 
{
	CAboutDlg d;
	d.DoModal();
}
