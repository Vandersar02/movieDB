// Devoir4Dlg.h : header file
//
#include <vector>
#pragma once


// CDevoir4Dlg dialog
class CDevoir4Dlg : public CDialogEx
{
// Construction
public:
	CDevoir4Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVOIR4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPrevious();
	afx_msg void OnBnClickedNext();
	afx_msg void AfficherFilmActuel();
	afx_msg void DownloadJson();
	CString ID_title;
	CString ID_Description;
	CStatic ID_Image;
};
