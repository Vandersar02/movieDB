// Devoir4Dlg.cpp : implementation file
// St Cyr Lee J Vandersar
//

#include "pch.h"
#include "framework.h"
#include "Devoir4.h"
#include "Devoir4Dlg.h"
#include "afxdialogex.h"
#include "Film.h"
#include "JsonFilm.h"
#include <vector>
#include <urlmon.h>
#include <atlstr.h>
#pragma comment(lib, "urlmon.lib")


using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NEXT, &CDevoir4Dlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREVIOUS, &CDevoir4Dlg::OnBnClickedPrevious)
END_MESSAGE_MAP()


// CDevoir4Dlg dialog


CDevoir4Dlg::CDevoir4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVOIR4_DIALOG, pParent)
	, ID_title(_T(""))
	, ID_Description(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDevoir4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TITRE, ID_title);
	DDX_Text(pDX, IDC_DESCRIPTION, ID_Description);
	DDX_Control(pDX, IDC_PICTURES, ID_Image);
}

BEGIN_MESSAGE_MAP(CDevoir4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PREVIOUS, &CDevoir4Dlg::OnBnClickedPrevious)
	ON_BN_CLICKED(IDC_NEXT, &CDevoir4Dlg::OnBnClickedNext)
END_MESSAGE_MAP()


// CDevoir4Dlg message handlers

BOOL CDevoir4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	GetWindowRect(&rect);
	rect.MoveToXY(0, 0);
	rect.right = rect.left + 800;
	rect.bottom = rect.top + 550;
	MoveWindow(&rect, TRUE);

	// Centrons la fenêtre au milieu de l'écran
	CenterWindow();

	AfficherFilmActuel();


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CDevoir4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDevoir4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDevoir4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString jsonData = _T("https://api.themoviedb.org/3/movie/popular?api_key=4f10e69267d5a1cc2165fe4f3a4ff4ee");
CStringA jsonDataA(jsonData);
vector<Film> films = DeserialiserFilms(jsonDataA);

int currentFilmIndex = 0;

void CDevoir4Dlg::OnBnClickedPrevious()
{
	if (currentFilmIndex > 0) {
		currentFilmIndex--;
	}
	else {
		currentFilmIndex = films.size() - 1;
	}

	AfficherFilmActuel();
}

void CDevoir4Dlg::OnBnClickedNext()
{
	if (currentFilmIndex < films.size() - 1) {
		currentFilmIndex++;
	}
	else {
		currentFilmIndex = 0;
	}

	AfficherFilmActuel();
}


void CDevoir4Dlg::AfficherFilmActuel()
{
	// Vérifier si l'index du film actuel est valide
	if (currentFilmIndex >= 0 && currentFilmIndex < films.size())
	{
		// Obtenir le film actuel à partir du vecteur de films
		Film& film = films[currentFilmIndex];
		ID_title = L"Mon nouveau titre";

		// Mettre à jour les contrôles de la boîte de dialogue avec les informations du film
		SetDlgItemText(IDC_TITRE, ID_title);
		SetDlgItemText(IDC_DESCRIPTION, film.overview);
	}
}
