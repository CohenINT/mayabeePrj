
// OpenGLDlg.cpp : implementation file
//
#define NUL '\0';
#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLDlg.h"
#include "afxdialogex.h"

//for file input/ouput and music
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <Windows.h>
#include <playsoundapi.h>
#include <mmsystem.h>
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
END_MESSAGE_MAP()


// COpenGLDlg dialog



COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGL_DIALOG, pParent)
	, xLine(0)
	, playnow(false)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
//ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X, &COpenGLDlg::OnDeltaposMoveX)
ON_WM_TIMER()
ON_STN_CLICKED(IDC_PICTURE, &COpenGLDlg::OnStnClickedPicture)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X2, &COpenGLDlg::OnDeltaposMoveX2)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X3, &COpenGLDlg::OnDeltaposMoveX3)
ON_BN_CLICKED(IDC_BUTTON1, &COpenGLDlg::OnBnClickedButton1)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X4, &COpenGLDlg::OnDeltaposMoveX4)
ON_BN_CLICKED(IDC_BUTTON2, &COpenGLDlg::OnBnClickedButton2)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X5, &COpenGLDlg::OnDeltaposMoveX5)
ON_BN_CLICKED(IDC_BUTTON3, &COpenGLDlg::OnBnClickedButton3)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X6, &COpenGLDlg::OnDeltaposMoveX6)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X8, &COpenGLDlg::OnDeltaposMoveX8)
ON_BN_CLICKED(IDC_BUTTON4, &COpenGLDlg::OnBnClickedButton4)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X10, &COpenGLDlg::OnDeltaposMoveX10)
ON_BN_CLICKED(btnangle, &COpenGLDlg::OnBnClickedbtnangle)
ON_BN_CLICKED(IDC_BUTTON6, &COpenGLDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON7, &COpenGLDlg::OnBnClickedButton7)
ON_NOTIFY(UDN_DELTAPOS, RLMov, &COpenGLDlg::OnDeltaposRlmov)
ON_NOTIFY(UDN_DELTAPOS, btnLW, &COpenGLDlg::OnDeltaposbtnlw)
ON_NOTIFY(UDN_DELTAPOS, btnLW2, &COpenGLDlg::OnDeltaposbtnlw2)
END_MESSAGE_MAP()


// COpenGLDlg message handlers

BOOL COpenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//ptrView = new CGlView(this);
	CWnd* wnd = GetDlgItem(IDC_PICTURE);
	ptrView = new CGlView(wnd);

	SetTimer(1, 50, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COpenGLDlg::OnPaint()
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

		ptrView->vDrawGLScene();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenGLDlg::OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult)
{//move right or left 
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	ptrView->setMoveX(ptrView->getMoveX() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 1)
	{
		if (playnow == true)
		{
			//animation
			//spin around y axix V 
			//move the wings and arms

			ptrView->turnAngle -= 8;
			ptrView->setTurnY(ptrView->getTurnY() - 0.5f);//move around itself

			ptrView->RAangle += 24;//spin all right arm
			ptrView->RAx = (ptrView->RAx - 0.5);
			ptrView->RAy = (ptrView->RAy - 0.5);



			ptrView->LAangle += 24;//spin all left arm
			ptrView->LAx = (ptrView->LAx - 0.5);
			ptrView->LAy = (ptrView->LAy - 0.5);


			if (ptrView->LWflyvar == 45)
			{
				ptrView->LWflyvar = 0;
			}
			else
			ptrView->LWflyvar = 45;//flip wings
			
			if (ptrView->getMoveY() <= 2)
				ptrView->setMoveY(ptrView->getMoveY() + 0.1);



			//end of animation
			ptrView->vDrawGLScene();
		}

		else
		{
			playnow = false;
			PlaySound(NULL, 0, 0);//stop the music
		}
     
	}
}


void COpenGLDlg::OnStnClickedPicture()
{
	// TODO: Add your control notification handler code here
}


void COpenGLDlg::OnDeltaposMoveX2(NMHDR *pNMHDR, LRESULT *pResult)
{//turn around function
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	//ptrView->setMoveX(ptrView->getMoveX() - 0.5*pNMUpDown->iDelta);
	/*if (ptrView->turnAngle == 180 && ptrView->turnAngle == -180)
	{
		ptrView->turnAngle = 0;
	}*/

	if(pNMUpDown->iDelta==-1)
	ptrView->turnAngle += 35;
	else
		ptrView->turnAngle -= 35;

	ptrView->setTurnY(ptrView->getTurnY() - 0.5f*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();
	

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveX3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->setMoveZ(ptrView->getMoveZ() - 0.5f*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();
	*pResult = 0;
}


void COpenGLDlg::OnBnClickedButton1()
{//saves state of axes//NOT WORKING
	// TODO: Add your control notification handler code here
	ofstream write;//set text into file
	ifstream read("saves.txt");//get the text from file
	char c = 'a';
	double i = 1, counter = 0;
	int j = 1,k=10, flag = 0;
	//read.close();//remove line to continue

	//seperate values x ,y,z,angle
	
		while (read.get(c) && c != 46 && c != '#') 
		{
			counter++;
		};//counts for the numbers before period
		j = counter;
		read.close();

		read.open("saves.txt", ios::in);
		c = 'a';//just reset
		//for(i=pow(10.0,counter);i>0;i/=10){}
		while (read.get(c)&&c != '#')
		{
		
		if (c != 46)//check for not being period
		{
			if (flag == 0)
			{
				if (j >= 0)//true means counter did not end yet
				{

					j--;
					i *= pow(10, j - 1);//מיקום הספרה באחדות עשרות מאות וכן הלאה
					
					xLine += ((int)c - 48)*i;
				}
			}
			else
			{//flag=1 all numbers are now after period

				xLine += ((int)c - 48) / k;
				k *= 10;
			}

		}
		else
		{
			flag = 1;//there is a period X.12345

		}

	}

	read.close();
	
	

}


void COpenGLDlg::OnDeltaposMoveX4(NMHDR *pNMHDR, LRESULT *pResult)
{//turn upside down
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	

	if (pNMUpDown->iDelta == -1)
		ptrView->turnAngle += 25;
	else
		ptrView->turnAngle -= 25;
	if (ptrView->turnAngle == 360 || ptrView->turnAngle == -360)
		ptrView->turnAngle = 0;

	ptrView->turnX=ptrView->turnX -( 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	

	*pResult = 0;
}


void COpenGLDlg::OnBnClickedButton2()
{//reset button
	// TODO: Add your control notification handler code here



	ptrView->setMoveX(0);
	ptrView->setMoveZ(0);
	ptrView->setRotY(0);
	ptrView->setturnAngle(0);
	ptrView->setTurnY(0);
	ptrView->setTurnZ(0);
	ptrView->turnX = 0;
	ptrView->setMoveY(0);
	ptrView->RAangle = 0;
    ptrView->RAx = 0;
	ptrView->RAy = 0;
	ptrView->RAz = 0;
	ptrView->RAangle2 = 0;
	ptrView->RAx2 = 0;
	ptrView->RAy2 = 0;
	ptrView->RAz2 = 0;
	ptrView->LAangle = 0;
		ptrView->LAx = 0;
	ptrView->LAy = 0;
	ptrView->LAangle2 = 0;
	ptrView->LAx2 = 0;
	ptrView->LAy2 = 0;
	ptrView->LLangle = 0;
	ptrView->LLx = 0;
	ptrView->LLy = 0;
	ptrView->LLz = 0;
	ptrView->RLangle = 0;
	ptrView->RLx = 0;
	ptrView->RLy = 0;
  ptrView->RLz = 0;
  ptrView->moveLLvar=0;
  ptrView->moveRLvar = 0;
  ptrView->moveLWvar = 0;
  ptrView->moveRWvar = 0;

	CString str;
	str.Format(L"Angle: %d", 0);
	GetDlgItem(btnangle)->SetWindowText(str);
	str.Format(L"Axes");
	GetDlgItem(IDC_BUTTON7)->SetWindowText(str);



	ptrView->vDrawGLScene();

}


void COpenGLDlg::OnDeltaposMoveX5(NMHDR *pNMHDR, LRESULT *pResult)
{//updown
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	ptrView->setMoveY(ptrView->getMoveY() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnBnClickedButton3()
{//play 
	// TODO: Add your control notification handler code here
	
	playnow = true;

		PlaySound(TEXT("mayabee.wav"), NULL, SND_ASYNC);


		ptrView->LWflyvar == 0;
	SetTimer(1, 135, NULL);//start the animation every 100 ms 

	ptrView->vDrawGLScene();

}


void COpenGLDlg::OnDeltaposMoveX6(NMHDR *pNMHDR, LRESULT *pResult)
{//all right arm move rotate
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	ptrView->setRAmove(ptrView->RAangle - 0.5*pNMUpDown->iDelta);


	showAngle(ptrView->RAangle);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveX7(NMHDR *pNMHDR, LRESULT *pResult)
{//upper part right hand-- NOT USED
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->vDrawGLScene();
	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveX8(NMHDR *pNMHDR, LRESULT *pResult)
{//left arm
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->setLAmove(ptrView->LAangle - 0.5*pNMUpDown->iDelta);
	showAngle(ptrView->LAangle);


	showAngle(ptrView->LAangle);

	ptrView->vDrawGLScene();
	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveX9(NMHDR *pNMHDR, LRESULT *pResult)
{//left hand upper part NOT USED
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	ptrView->vDrawGLScene();


	*pResult = 0;
}


void COpenGLDlg::OnBnClickedButton4()
{//stop button
	// TODO: Add your control notification handler code here
	playnow = false;

}


void COpenGLDlg::OnDeltaposMoveX10(NMHDR *pNMHDR, LRESULT *pResult)
{//left leg all move

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);


	ptrView->setMoveLL(ptrView->getLLmove() - 0.5*pNMUpDown->iDelta);
	showAngle(ptrView->getLLmove());


		ptrView->vDrawGLScene();

	
	*pResult = 0;






}










void COpenGLDlg::OnBnClickedbtnangle()
{
	// TODO: Add your control notification handler code 
	ptrView->vDrawGLScene();


}


// showing the angle of the current movement
void COpenGLDlg::showAngle(float angle)
{
	CString str;
	str.Format(L"Angle: %f", angle);
	GetDlgItem(btnangle)->SetWindowText(str);

}


void COpenGLDlg::OnBnClickedButton6()
{
	if (ptrView->testing == true)
	{
		ptrView->testing = false;
	}
	else
	{//if false
		ptrView->testing = true;
	}
	// TODO: Add your control notification handler code here
	ptrView->vDrawGLScene();

}


void COpenGLDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
}

using namespace std;
void COpenGLDlg::showAxes(float x, float y, float z)
{// showing the axes

	CString str;
	str.Format(L"X: %.3f Y: %.3f, Z: %.3f ", x,y,z);
	GetDlgItem(IDC_BUTTON7)->SetWindowText(str);
	
}



void COpenGLDlg::OnDeltaposRlmov(NMHDR *pNMHDR, LRESULT *pResult)
{//right leg all move
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	ptrView->setMoveRL(ptrView->moveRLvar - 0.5*pNMUpDown->iDelta);
	showAngle(ptrView->getRLmove());


	ptrView->vDrawGLScene();


	*pResult = 0;



	
}


void COpenGLDlg::OnDeltaposbtnlw(NMHDR *pNMHDR, LRESULT *pResult)
{//left wing move
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->setMoveLW(ptrView->moveLWvar - 0.5*pNMUpDown->iDelta);
	showAngle(ptrView->moveLWvar);


	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposbtnlw2(NMHDR *pNMHDR, LRESULT *pResult)
{//right wing move
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	ptrView->setMoveRW(ptrView->moveRWvar - 0.5*pNMUpDown->iDelta);
	showAngle(ptrView->moveRWvar);


	ptrView->vDrawGLScene();

	*pResult = 0;
}
