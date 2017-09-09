
// OpenGLDlg.h : header file
//

#pragma once

#include "GlView.h"


// COpenGLDlg dialog
class COpenGLDlg : public CDialogEx
{
// Construction
public:
	COpenGLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_DIALOG };
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
private:
	CGlView* ptrView;
public:
//	afx_msg void OnDeltaposMovex(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDeltaposMovex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPicture();
	afx_msg void OnDeltaposMoveX2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	// tx file line x
	float xLine;
	afx_msg void OnDeltaposMoveX4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDeltaposMoveX5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDeltaposMoveX6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX9(NMHDR *pNMHDR, LRESULT *pResult);
	// define if the application is playing the animation
	bool playnow=false;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnDeltaposMoveX10(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnDeltaposMoveX11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedbtnangle();
	// showing the angle of the current movement
	void showAngle(float angle);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	// showing the axes
	void showAxes(float x, float y, float z);
	afx_msg void OnDeltaposRlmov(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposbtnlw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposbtnlw2(NMHDR *pNMHDR, LRESULT *pResult);
};
