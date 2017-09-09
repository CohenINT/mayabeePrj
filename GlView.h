// GlView.h: interface for the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_)
#define AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GLAUX.H> // Header File For The glaux Library

#define SIZE 3

class CGlView  
{
public:
	CGlView(CWnd *pclWnd);
	~CGlView();

	void vDrawGLScene();

	protected:
	private:
		void vInitGl(int iWidth, int iHeigth);
		BOOL bSetWindowPixelFormat(HDC hDC);
		BOOL bCreateViewGLContext(HDC hDC);

	// members //////////////////////////////////////////////////////////
	public:
	protected:
	private:			
		HGLRC	m_hGLContext;	// required GLContext
		CWnd *m_pclWnd;			// window inwhich opengl will be drawn
		HDC		m_hDC;			// handle to m_pclWnds device context
		float moveX, moveY, moveZ;
		float rotY;
public:
	float getMoveX();
	void setMoveX(float moveX);
	float getRotY();
	void setRotY(float rotY);
	void generateTextureFromImageFile();
private:
	GLuint idTexture[SIZE];
	AUX_RGBImageRec* texture;
public:
	float turnX;
	float turnY;
	float turnZ;
	void setTurnY(float y);
	float getTurnY();
	int turnAngle;
	void setturnAngle(int angle);
	float getMoveZ();
	void setMoveZ(float);
	// this x axe from txt file
	float xLine;
	void setTurnZ(float z);
	float getTurnZ();

	void setMoveY(float y);
	float getMoveY();
	float RAangle;
	float RAy;
	float RAz;
	float RAx;
	float RAangle2;
	float RAx2;
	float RAy2;
	float RAz2;
	float LAangle;
	float LAx;
	float LAy;
	float LAangle2;
	float LAx2;
	float LAy2;
	float RLangle;
	float RLx;
	float RLy;
	float LLangle;
	float LLx;
	float LLy;
	float LLz;
	// for testing measures
	bool testing;
	// every change of angle the z axis goes oppsite way 
	float LLoZ;
	float RLz;
	// this is the angle parameter of the left leg 
	float moveLLvar;
	// get the LLmovevar 
	float getLLmove();
	void setMoveLL(float angle);
	// right left movement angle
	float moveRLvar;
	float getRLmove();
	// seetting the angle for the right leg rotation
	void setMoveRL(float angle);
	// setting the left arm move angle
	void setLAmove(float angle);
	// setting right arm move angle
	void setRAmove(float angle);
	// move left wing variable 
	float moveLWvar;
	// setting the Left wing move angle
	void setMoveLW(float angle);
	// right wing angle variable
	float moveRWvar;
	// setting the Right wing angle
	void setMoveRW(float angle);
	// angle 45 or 0 for flipping the wings used for animaton
	int LWflyvar;
};

#endif

