// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include <math.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
	: moveX(0)
	, moveY(0)
	, moveZ(0)
	, rotY(0)
	, turnX(0)
	, turnY(0)
	, turnZ(0)
	, turnAngle(0)
	
	, RAangle(0)
	, RAy(0)
	, RAz(0)
	, RAx(0)
	, RAangle2(0)
	, RAx2(0)
	, RAy2(0)
	, RAz2(0)
	, LAangle(0)
	, LAx(0)
	, LAy(0)
	, LAangle2(0)
	, LAx2(0)
	, LAy2(0)
	, RLangle(0)
	, RLx(0)
	, RLy(0)
	, LLangle(0)
	, LLx(0)
	, LLy(0)
	, LLz(0)
	, testing(false)
	, LLoZ(0)
	, RLz(0)
	, moveLLvar(0)
	, moveRLvar(0)
	, moveLWvar(0)
	, moveRWvar(0)
	, LWflyvar(45)
{
	m_pclWnd = pclWnd;
	m_hDC  = GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect; 
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);
}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -
CGlView::~CGlView()
{
	// make the rendering context not current
	if(wglGetCurrentContext()!=NULL) 
		wglMakeCurrent(NULL, NULL);
	
	// delete the Context
  if (m_hGLContext!=NULL)
  {
		wglDeleteContext(m_hGLContext);
    m_hGLContext = NULL;
  }
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -
void CGlView::vDrawGLScene()									
{//here is all scene 
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();								
	glTranslatef(0.0f, 1.99f, -18.0f);
	

	//Enable color and light effects

	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);


	//if you deleting this line i guess you didn't sucecced in adding test button



    GLUquadricObj* obj,* obj_head,*obj_body,*obj_leftarm,*obj_rightarm, *obj_leftleg,*obj_rightleg, *obj_wingsholder,*obj_lefthip,*obj_righthip,*obj_leftwing,*obj_rightwing;
	obj_leftleg = gluNewQuadric();
	obj_rightleg =gluNewQuadric();
	obj_leftarm = gluNewQuadric();
	obj_lefthip= gluNewQuadric();
	obj_leftwing = gluNewQuadric();
	obj_rightwing = gluNewQuadric();
	obj_wingsholder = gluNewQuadric();
		obj_righthip= gluNewQuadric();
        obj = gluNewQuadric();
		obj_rightarm= gluNewQuadric();
		obj_body = gluNewQuadric();
		obj_head = gluNewQuadric();
		gluQuadricTexture(obj_wingsholder, true);
		gluQuadricTexture(obj_leftwing, true);
		gluQuadricTexture(obj_rightwing, true);
		gluQuadricTexture(obj_lefthip, true);
		gluQuadricTexture(obj_righthip, true);
		gluQuadricTexture(obj_rightarm, true);
		gluQuadricTexture(obj_body, true);
		gluQuadricTexture(obj_head, false);
		gluQuadricTexture(obj, true);
		gluQuadricTexture(obj_leftarm, true);
		gluQuadricTexture(obj_leftleg, true);
		gluQuadricTexture(obj_rightleg, true);

		//gluQuadricTexture(obj, false);

		if (testing == false)
		{
		//background

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexture[0]);

		glPushMatrix();
		glTranslatef(0, 0, -5);
		glScalef(22, 22, 33);
		glBegin(GL_QUADS);
		glColor3f(4, 4, 4);
		glTexCoord2f(0, 0);
		glVertex3f(-4, -3, 0);

		glTexCoord2f(0, 3);
		glVertex3f(-4, 3, 0);
		glTexCoord2f(2, 3);
		glVertex3f(4, 3, 0);
		glTexCoord2f(2, 0);
		glVertex3f(4, -3, 0);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
		}
		


		//whole charactor
		glPushMatrix();
		glTranslatef(moveX, moveY, moveZ);
		glRotatef(turnAngle, turnX, turnY, turnZ);
		
		


		if (testing == true)
		{
			//axes
			glPushMatrix();
			glBegin(GL_LINES);
			//x  RED
			glColor3f(5.0f, 0.0f, 0.0f);
			glVertex3f(-7.0f, 0.0f, 0.0f);
			glVertex3f(7.0f, 0.0f, 0.0f);
			//y  GREEN 
			glColor3f(0.0f, 5.0f, 0.0f);
			glVertex3f(0.0f, -7.0f, 0.0f);
			glVertex3f(0.0f, 7.0f, 0.0f);

			//z  BLUE
			glColor3f(0.0f, 0.0f, 5.0f);
			glVertex3f(0.0f, 0.0f, -7.0f);
			glVertex3f(0.0f, 0.0f, 7.0f);
			glEnd();
			glPopMatrix();

			//mesurement units
			glPushMatrix();
			glTranslatef(0, 0, 4);

			glColor3f(4, 4, 1);
			/*glTranslatef(0, 0, 4)*/;
			//gluSphere(obj, 1.5, 32, 32);
			float glz = 0, gly = 7.0f, glx = 1.5f;
			int i;
			glBegin(GL_POINTS);

			for (i = 0, glx = 1.5f, glz = 0, gly = 7; i < 34; i++)
			{//show for Y axe 
				glVertex3f(glx, gly, glz);

				gly -= 0.5;
			}
			for (i = 0, glx = -7.0f, gly = 0.5f, glz = 0; i < 34; i++)
			{//show for X axe
				glVertex3f(glx, gly, glz);

				glx += 0.5;
			}

			glEnd();

			glPopMatrix();
		}


		////background

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, idTexture[0]);
		//
		//glPushMatrix();
		//glTranslatef(0, 0, -5);
		//glScalef(22, 22, 33);
		//glBegin(GL_QUADS);
		//glColor3f(4, 4, 4);
		//glTexCoord2f(0, 0);
		//glVertex3f(-4, -3, 0);
		//
		//glTexCoord2f(0, 3);
		//glVertex3f(-4, 3, 0);
		//glTexCoord2f(2, 3);
		//glVertex3f(4, 3, 0);
		//glTexCoord2f(2, 0);
		//glVertex3f(4, -3, 0);
		//glEnd();

		//glDisable(GL_TEXTURE_2D);

		//glPopMatrix();


		//head
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glRotatef(-90, 1, 0, 0);
		gluSphere(obj_head,0.79, 32, 32);
		glPopMatrix();

		
		//left eye
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0.5f, 0.0f, 0.5f);
		gluSphere(obj_head, 0.22, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glColor3f(4, 1, 1);
		glTranslatef(0.5f, 0.0f, 0.5f);
		gluSphere(obj_head, 0.22, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glTranslatef(0.5f, 0.0f, 0.66f);
		gluSphere(obj_head, 0.1, 32, 32);
		glPopMatrix();


		//right eye
		glPushMatrix();
		glScalef(-1, 1, 1);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0.5f, 0.0f, 0.5f);
		gluSphere(obj_head, 0.22, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glColor3f(4, 1, 1);
		glTranslatef(0.5f, 0.0f, 0.5f);
		gluSphere(obj_head, 0.22, 32, 32);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.5f, 0.0f, 0.66f);
		gluSphere(obj_head, 0.1, 32, 32);
		glPopMatrix();
		glPopMatrix();

		//nose
		glPushMatrix();
		glColor3f(0, 4, 0);
		glRotatef(-45, 0, 0, 1);

		gluCylinder(obj_leftleg, 0.2, 0.01, 1.6, 32, 32);

		glPopMatrix();

		

		




		//body
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexture[1]);
		glPushMatrix();
		glTranslatef(0, -5.0f, 0.0f);
		glRotatef(-90,355, 5.76, 1);
		glColor3f(1, 1, 1);
		gluCylinder(obj_body, 1, 1, 4, 32, 32);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);





		//left arm
		//shoulder
		glPushMatrix();//whole arm
		glRotatef(LAangle, 9, 45, 0);


		glPushMatrix();
		glTranslatef(-0.9855, -1.53, 0);
		gluSphere(obj_leftarm, 0.6325, 32, 32);
		glPopMatrix();


		//only arm no shoulder
		glPushMatrix();
		
		//elbow
		glPushMatrix();
		glColor3f(5.0f, 4.0f, 0.0f);
		glTranslatef(-2.40f, -1.00950f, 0.149646f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_leftarm, 0.2, 0.2, 0.4, 32, 32);
		glPopMatrix();

		//mifrak sheni
		glPushMatrix();

		glColor3f(0.0f, 0.0f, 3.0f);
		glTranslatef(-2.71f, -0.80f, 0.220f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_leftarm, 0.2, 0.2, 2, 32, 32);
		glPopMatrix();

		//mifran rishon
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 3.0f);
		glTranslatef(-1.0f, -2.0f, 0.0f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_leftarm, 0.2, 0.2, 2, 32, 32);
		glPopMatrix();

		//only arm no shoulder
		glPopMatrix();

		glPopMatrix();//whole arm




		 //right arm
		glPushMatrix();//whole arm
		glRotatef(RAangle, 9, 45, 0);

	    //shoulder

		glRotatef(-180, 0, 1, 0);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-0.9855, -1.53, 0);
		gluSphere(obj_rightarm, 0.6325, 32, 32);
		glPopMatrix();


		//only arm no shoulder
		glPushMatrix();
		
		
		
		//elbow
		glPushMatrix();

		glColor3f(5.0f, 4.0f, 0.0f);
		glTranslatef(-2.40f, -1.02f, 0.2116f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_rightarm, 0.2, 0.2, 0.4, 32, 32);

		glPopMatrix();

		//mifrak sheni
		glPushMatrix();
		
	
        glColor3f(0.0f, 0.0f, 3.0f);
		glTranslatef(-2.71f, -0.80f, 0.220f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_rightarm, 0.2, 0.2, 2, 32, 32);
		glPopMatrix();

		//mifran rishon
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 3.0f);
		glTranslatef(-1.0f, -2.0f, 0.0f);
		glRotatef(-90, 1, 3, 1);
		gluCylinder(obj_rightarm, 0.2, 0.2, 2, 32, 32);
		glPopMatrix();

		//only arm no shoulder
		glPopMatrix();
		glPopMatrix();//whole arm

		


		
		


		//left leg
		//whole leg
		glPushMatrix();
		glRotatef(moveLLvar,1, 0, 0);
		
		//hip
		glPushMatrix();
		glColor3f(0, 4, 0);
		glTranslatef(1.5, -5.2023,0.412404);
		glRotatef(180, 1, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glRotatef(45, 1, 1, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexture[2]);
		gluCylinder(obj_lefthip, 0.22, 0.71, 1.46, 32, 32);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//only leg
		glPushMatrix();
		//glTranslatef(0, 0, LLoZ);//LEFT LEG OPPSITE Z 

		//mifrak rishon
		glPushMatrix();
		glColor3f(5, 4, 0);
		glTranslatef(0, -4.50f, 0.5f);
		glRotatef(180, 1, 0, 1);
		glRotatef(-24, 1, 0, 0);
		gluCylinder(obj_leftleg, 0.15, 0.15, 4, 32, 32);
		glPopMatrix();
		//knee cap
		glPushMatrix();
		glTranslatef(3.6, -6.1, 0.5);
		glColor3f(3, 0, 0);
		gluSphere(obj_leftleg, 0.3, 32, 32);
		glPopMatrix();
		//mifrak sheni
		glPushMatrix();
		glColor3f(5, 4, 0);
		glTranslatef(3.68, -6.210f, 0.5f);
		glRotatef(120, 1, 1, 0);
		gluCylinder(obj_leftleg, 0.15, 0.15, 4, 32, 32);
		glPopMatrix();
		glPopMatrix();//only leg

		glPopMatrix();
		//
		//whole leg





		//right leg
		//whole leg
		glPushMatrix();
		glRotatef(moveRLvar, 1, 0, 0);

		glScalef(-1, 1, 1);
		//hip
		glPushMatrix();
		glColor3f(0, 4, 0);
		glTranslatef(1.5, -5.2023, 0.412404);
		glRotatef(180, 1, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glRotatef(45, 1, 1, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idTexture[2]);
		gluCylinder(obj_righthip, 0.22, 0.71, 1.46, 32, 32);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//only leg
		glPushMatrix();
		//glRotatef(RLangle, RLx, RLy, 0);

		//mifrak rishon
		glPushMatrix();
		glColor3f(5, 4, 0);
		glTranslatef(0, -4.50f, 0.5f);
		glRotatef(180, 1, 0, 1);
		glRotatef(-24, 1, 0, 0);
		gluCylinder(obj_rightleg, 0.15, 0.15, 4, 32, 32);
		glPopMatrix();
		//knee cap
		glPushMatrix();
		glTranslatef(3.6, -6.1, 0.5);
		glColor3f(3, 0, 0);
		gluSphere(obj_rightleg, 0.3, 32, 32);
		glPopMatrix();
		//mifrak sheni
		glPushMatrix();
		glColor3f(5, 4, 0);
		glTranslatef(3.68, -6.210f, 0.5f);
		glRotatef(120, 1, 1, 0);
		gluCylinder(obj_rightleg, 0.15, 0.15, 4, 32, 32);
		glPopMatrix();


		glPopMatrix();//ONLY LEG
		
		glPopMatrix();
		//
		//whole leg


		GLfloat glz=0;
		int i=0,amount=144;//amount of triangles to create
	    



		//left wing 
		glPushMatrix();//whole wing
		glRotatef(LWflyvar, 0, 1, 0);//for animation

		// wing - upper
		glPushMatrix();
		glRotatef(moveLWvar, 0, 1, 0);
		glTranslatef(0, 0, -1);
		glColor3f(4, 0, 0);


		//multiplaying the triangle with 0.001 gap of Z axis
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		for ( i = 0,glz=0; i < amount; i++)
		{//multiplay the triangle
			glVertex3f(1, -1, 0+glz);
			glVertex3f(2, 1.5, 0+glz);
			glVertex3f(3.5, 1.5, 0+glz);
			glVertex3f(3.5, 0, 0+glz);
			glVertex3f(1, -2.5, 0+glz);
			glz += 0.001;//the gap between every triangle
		}
		glEnd();
		glPopMatrix();
		glPopMatrix();
		// left wing upper
		

		
		//left wing - bottom wing
		glPushMatrix();
		glRotatef(moveLWvar, 0, 1, 0);

		glTranslatef(0, -4.5, -1);
		glRotatef(180, 1, 0, 0);
		glColor3f(4, 0, 0);
		//multiplaying the triangle with 0.001 gap of Z axis
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);
		 amount = 144;//amount of triangles to create 
		for (i = 0, glz = 0; i < amount; i++)
		{//multiplay the triangle
			glVertex3f(1, -1, 0 + glz);
			glVertex3f(2, 1.5, 0 + glz);
			glVertex3f(3.5, 1.5, 0 + glz);
			glVertex3f(3.5, 0, 0 + glz);
			glVertex3f(1, -2.5, 0 + glz);
			glz += 0.001;//the gap between every triangle
		}
		glEnd();
		glPopMatrix();


		glPopMatrix();
		// left wing bottom
		glPopMatrix();









		//right wing 

		glPushMatrix();//whole right wing
		glRotatef(-LWflyvar,0,1,0);
		// wing upper
		glPushMatrix();
		glRotatef(moveRWvar, 0, 1, 0);
		glScalef(-1, 1, 1);
		glTranslatef(0, 0, -1);
		glColor3f(4, 0, 0);
		//multiplaying the triangle with 0.001 gap of Z axis
		glBegin(GL_TRIANGLE_FAN);
		for (i = 0, glz = 0; i < amount; i++)
		{//multiplay the triangle
			glVertex3f(1, -1, 0 + glz);
			glVertex3f(2, 1.5, 0 + glz);
			glVertex3f(3.5, 1.5, 0 + glz);
			glVertex3f(3.5, 0, 0 + glz);
			glVertex3f(1, -2.5, 0 + glz);
			glz += 0.001;//the gap between every triangle
		}
		glEnd();
		glPopMatrix();

		// bottom right wing
	glPushMatrix();
		glRotatef(moveRWvar, 0, 1, 0);
		glTranslatef(0, -4.5, -1);
		glRotatef(180, 1, 0, 0);
		glScalef(-1, 1, 1);

		glColor3f(4, 0, 0);
		//multiplaying the triangle with 0.001 gap of Z axis
		glBegin(GL_TRIANGLE_FAN);
		amount = 144;//amount of triangles to create
		for (i = 0, glz = 0; i < amount; i++)
		{//multiplay the triangle
			glVertex3f(1, -1, 0 + glz);
			glVertex3f(2, 1.5, 0 + glz);
			glVertex3f(3.5, 1.5, 0 + glz);
			glVertex3f(3.5, 0, 0 + glz);
			glVertex3f(1, -2.5, 0 + glz);
			glz += 0.001;//the gap between every triangle
		}
		glEnd();
	glPopMatrix();

	
	
	glPopMatrix();//whole right wing









		//wings holder
		//whole wings holder
		glPushMatrix();
		glColor3f(2, 2, 3);
		glTranslatef(0, -2, -1.4);

		glBegin(GL_TRIANGLE_FAN);
	
		 amount = 444;//amount of triangles to create

		for (i = 0, glz = 0; i < amount; i++)
		{//multiplay the triangle

			glVertex3f(-1.5, -2.5, 0 + glz);
			glVertex3f(1.5, -2.5, 0 + glz);
			glVertex3f(1, 1, 0 + glz);
			glVertex3f(-1, 1, 0 + glz);

			glz += 0.001;//the gap between every triangle
		}
		glEnd();

		  glPopMatrix();
		//
		  //whole wings holder


		
	
	
		glPopMatrix();
		
		//
		//
		//whole charactor
		




		//Disable color and light effects
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		

			

		gluDeleteQuadric(obj);
	gluDeleteQuadric(obj_head);//add here all the obj variables
	gluDeleteQuadric(obj_body);
	gluDeleteQuadric(obj_leftarm);
	gluDeleteQuadric(obj_rightarm);
	gluDeleteQuadric(obj_lefthip);
	gluDeleteQuadric(obj_leftleg);
	gluDeleteQuadric(obj_righthip);
	gluDeleteQuadric(obj_rightleg);
	gluDeleteQuadric(obj_wingsholder);







	// swap the buffer
	SwapBuffers(m_hDC);
	
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

    pixelDesc.nSize     = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDesc.nVersion	= 1;

    pixelDesc.dwFlags   =    
	
		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

    int iGLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
		ASSERT(&iGLPixelIndex);

    if (SetPixelFormat( hDC, iGLPixelIndex, &pixelDesc))
			return false;

    return TRUE;
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
		m_hGLContext = wglCreateContext(hDC);
    if (m_hGLContext == NULL)
      return FALSE;

    if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)
			return FALSE;

    return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{
	glShadeModel(GL_SMOOTH);								
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);		
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	glViewport(0,0,iWidth,iHeigth);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();								

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)iWidth/(GLfloat)iHeigth,0.45f,100.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();	

	generateTextureFromImageFile();
}

void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);

	const char* imageFileName[SIZE] = { "images\\background.bmp", "images\\body.bmp", "images\\flower.bmp" };

	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoadA(imageFileName[i]);//loads the width, height, colors from the image file (*.bmp) into opengl structure (AUX_RGBImageRec).

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//working on idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if the target is smaller than the source then minimize it using LINEAR algorithm.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if the target is bigger than the source then maximize it using LINEAR algorithm.
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save texture in memory.
			free(texture);
			texture = NULL;
		}
	}
}


float CGlView::getMoveX()
{
	return moveX;
}

void CGlView::setMoveX(float moveX)
{
	this->moveX = moveX;
}

float CGlView::getRotY()
{
	return rotY;
}

void CGlView::setRotY(float rotY)
{
	this->rotY = rotY;
}



void CGlView::setTurnY(float y)
{
	this->turnY = y;
}


float CGlView::getTurnY()
{
	return turnY;
}


void CGlView::setturnAngle(int angle)
{
	this->turnAngle = angle;
}


float CGlView::getMoveZ()
{
	return moveZ;
}


void CGlView::setMoveZ(float z)
{
	this->moveZ = z;
}


void CGlView::setTurnZ(float z)
{
	this->turnZ = z;
}


float CGlView::getTurnZ()
{
	return turnZ;
}



void CGlView::setMoveY(float y)
{
	this->moveY = y;
}


float CGlView::getMoveY()
{
	return moveY;
}


// get the LLmovevar 
float CGlView::getLLmove()
{
	return moveLLvar;
}


void CGlView::setMoveLL(float angle)//start with 0.5 degrees (use debug to see value)
{// setting the angle for the left leg rotation

	if (angle >= -2.5 && angle <= 10)
	{
		this->moveLLvar = angle;

	}
}


float CGlView::getRLmove()
{
	return moveRLvar;
}


void CGlView::setMoveRL(float angle)
{// setting the angle for the right leg rotation

	if (angle >= -2.5 && angle <= 10)
	{
		moveRLvar = angle;

	}

}


// setting the left arm move angle
void CGlView::setLAmove(float angle)
{
	if (angle >= -20 && angle <= 80)
	{
		LAangle = angle;
	}
	
}


// setting right arm move angle
void CGlView::setRAmove(float angle)
{
	if(angle >=-20 && angle<=80)
	{
		RAangle = angle;
	}
}


// setting the Left wing move angle
void CGlView::setMoveLW(float angle)
{
	if (angle >= -5.8 &&angle <= 21)
	{
		this->moveLWvar = angle;
	}

}


// setting the Right wing angle
void CGlView::setMoveRW(float angle)
{
	if (angle >= -15.8 &&angle <= 3)
	{
		this->moveRWvar = angle;
	}
}
