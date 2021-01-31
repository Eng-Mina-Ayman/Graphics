#include <stdlib.h>
#include <GL/glut.h>
float shift=-1.7,shift2=1.7;

void timer(int x){
if(shift>1.5)
    shift = -1.5;
    shift+=0.008;
    if(shift2>1.5)
    shift2 = 1.5;
    shift2-=0.004;

glutPostRedisplay();
glutTimerFunc(1000/60, timer, 0);
}

void display()
{ glClearColor(0.529, 0.788, 0.933,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  //------------mountains----------------------------

  glBegin(GL_TRIANGLES);
  glColor3f(0.235, 0.2, 0.043);
  glVertex2f(1.0 ,0.09);
  glVertex2f(0.0,0.09);
  glVertex2f(0.5,0.55);
  glColor3f(0.235, 0.2, 0.043);
  glVertex2f(1.5 ,0.09);
  glVertex2f(0.4,0.09);
  glColor3f(0.576, 0.494, 0.145);
  glVertex2f(0.8,0.9);
  glColor3f(0.235, 0.2, 0.043);
  glVertex2f(0.5 ,0.09);
  glVertex2f(-0.6,0.09);
  glColor3f(0.576, 0.494, 0.145);
  glVertex2f(0.0,0.8);
  glColor3f(0.235, 0.2, 0.043);
  glVertex2f(-0.4 ,0.09);
  glVertex2f(-1.3,0.09);
  glColor3f(0.749, 0.631, 0.133);
  glVertex2f(-0.9,1.0);
  glEnd();

//----------------- sun ----------------------------

  glBegin(GL_POLYGON);
  glColor3f(1, 0.988, 0.039);

  glVertex2f(-0.51 , 0.72);
  glVertex2f(-0.48,0.72);
  glVertex2f(-0.45,0.78);
  glVertex2f(-0.45,0.84);
  glVertex2f(-0.48,0.90);
  glVertex2f(-0.51,0.90);
  glVertex2f(-0.54,0.84);
  glVertex2f(-0.54,0.78);
  glEnd();

//------------------- plant ----------------------
  glBegin(GL_QUADS);

  glColor3f(0.368, 1, 0.101);
  glVertex2f(1.0 ,-0.6);
  glVertex2f(-1.0,-0.6);
  glColor3f(0.294, 0.478, 0.101);
  glVertex2f(-1.0,-1.0);
  glVertex2f(1.0,-1.0);

//----------------- track ----------------------

  glColor3f(1, 1, 1);
  glVertex2f(1.0 ,-0.51);
  glVertex2f(-1.0,-0.51);
  glVertex2f(-1.0,-0.6);
  glVertex2f(1.0,-0.6);

  float x[4]={-0.9,-1.0,-0.85,-0.95};
  for(int i=0;i<11;i++){
    glColor3f(0, 0, 0);
    glVertex2f(x[0],-0.6);
    glVertex2f(x[0],-0.54);
    glVertex2f(x[1],-0.54);
    glVertex2f(x[1],-0.6);
    glVertex2f(x[2] ,-0.51);
    glVertex2f(x[3],-0.51);
    glVertex2f(x[1],-0.54);
    glVertex2f(x[0],-0.54);
    x[0]+=0.2;
    x[1]+=0.2;
    x[2]+=0.2;
    x[3]+=0.2;
  }

  glColor3f(1, 1, 1);
  glVertex2f(1.0 ,0.09);
  glVertex2f(-1.0,0.09);
  glVertex2f(-1.0,0.0);
  glVertex2f(1.0,0.0);

  float  x2[4]={-0.9,-1.0,-0.85,-0.95};
  for(int i=0;i<11;i++){
    glColor3f(0, 0, 0);
    glVertex2f(x2[0],0.0);
    glVertex2f(x2[0],0.06);
    glVertex2f(x2[1],0.06);
    glVertex2f(x2[1],0.0);
    glVertex2f(x2[2] ,0.09);
    glVertex2f(x2[3],0.09);
    glVertex2f(x2[1],0.06);
    glVertex2f(x2[0],0.06);
    x2[0]+=0.2;
    x2[1]+=0.2;
    x2[2]+=0.2;
    x2[3]+=0.2;
  }
  //------------------- road ----------------------------

  glColor3f(0.266, 0.278, 0.262);
  glVertex2f(1.0 ,-0.51);
  glVertex2f(1.0,0.0);
  glColor3f(0.482, 0.505, 0.474);
  glVertex2f(-1.0,0.0);
  glVertex2f(-1.0,-0.51);



//---------------------- lines ---------------------------
 float l[4]={-0.9,-0.85,-0.45,-0.5};
for(int i=0;i<3;i++){
  glColor3f(1, 1, 1);
  glVertex2f(l[0] ,-0.28);
  glVertex2f(l[1],-0.23);
  glVertex2f(l[2],-0.23);
  glVertex2f(l[3],-0.28);
  l[0]+=0.7;
  l[1]+=0.7;
  l[2]+=0.7;
  l[3]+=0.7;
}
  glEnd();

  //---------------------- car 2------------------------------
  glColor3f(1.0f,0.0f,0.5f);

  glBegin(GL_QUADS);
  glVertex2f(-0.3 + shift2 ,0.15);
  glVertex2f(0.2 +shift2 ,0.15);
  glVertex2f(0.2 + shift2 ,-0.02);
  glVertex2f(-0.3 + shift2 ,-0.02);

  glVertex2f(-0.15 + shift2 ,0.15);
  glVertex2f(-0.06 + shift2 ,0.30);
  glVertex2f(0.06 +shift2 ,0.30);
  glVertex2f(0.2 +shift2 ,0.15);

//----------------------- car window --------------------------------
  glColor3f(1.0,1.0,1.0);
  glVertex2f(-0.135 + shift2  ,0.15);
  glVertex2f(-0.055 + shift2 ,0.28);
  glVertex2f(-0.01 + shift2 ,0.28);
  glVertex2f(-0.01 + shift2 ,0.15);

  glColor3f(1.0,1.0,1.0);
  glVertex2f(0.18 +shift2 ,0.15);
  glVertex2f(0.055 + shift2 ,0.28);
  glVertex2f(0.01 +shift2 ,0.28);
  glVertex2f(0.01 + shift2 ,0.15);

  glEnd();

//---------------------------- tires -----------------------------------

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);

  glVertex2f(-0.21 + shift2 ,0.03);
  glVertex2f(-0.18 + shift2 ,0.03);
  glVertex2f(-0.15 + shift2 ,-0.03);
  glVertex2f(-0.15 + shift2 ,-0.09);
  glVertex2f(-0.18 + shift2 ,-0.15);
  glVertex2f(-0.21 + shift2 ,-0.15);
  glVertex2f(-0.24 + shift2 ,-0.09);
  glVertex2f(-0.24 + shift2 ,-0.03);

  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);

  glVertex2f(0.14 + shift2 ,0.03);
  glVertex2f(0.11 + shift2 ,0.03);
  glVertex2f(0.08 + shift2 ,-0.03);
  glVertex2f(0.08 + shift2 ,-0.09);
  glVertex2f(0.11 + shift2 ,-0.15);
  glVertex2f(0.14 + shift2 ,-0.15);
  glVertex2f(0.17 + shift2 ,-0.09);
  glVertex2f(0.17 + shift2 ,-0.03);

  glEnd();
//-----------------------------------------------------
  glBegin(GL_QUADS);
  glColor3f(0.972, 0.898, 0.145);
  glVertex2f(-0.3 + shift2 ,0.13);
  glVertex2f(-0.26 + shift2 ,0.13);
  glVertex2f(-0.26 + shift2 ,0.08);
  glVertex2f(-0.3 +shift2 ,0.08);

  glColor3f(0.0,0.0,0.0);
  glVertex2f(-0.04 + shift2 ,0.12);
  glVertex2f(-0.04 + shift2 ,0.135);
  glVertex2f(-0.015 + shift2 ,0.135);
  glVertex2f(-0.015 + shift2 ,0.12);

  glVertex2f(0.16 +shift2 ,0.12);
  glVertex2f(0.16 + shift2 ,0.135);
  glVertex2f(0.135 + shift2 ,0.135);
  glVertex2f(0.135 + shift2 ,0.12);

  glEnd();

//---------------------- car ------------------------------
  glColor3f(1.0f,0.0f,0.0f);

  glBegin(GL_QUADS);
  glVertex2f(0.3 +shift,-0.1);
  glVertex2f(-0.2+shift,-0.1);
  glVertex2f(-0.2+shift,-0.27);
  glVertex2f(0.3+shift,-0.27);

  glVertex2f(0.15 +shift,-0.1);
  glVertex2f(0.06+shift,0.05);
  glVertex2f(-0.06+shift,0.05);
  glVertex2f(-0.2+shift,-0.1);

//----------------------- car window --------------------------------
  glColor3f(1.0,1.0,1.0);
  glVertex2f(0.135 +shift,-0.1);
  glVertex2f(0.055+shift,0.03);
  glVertex2f(0.01+shift,0.03);
  glVertex2f(0.01+shift,-0.1);

  glColor3f(1.0,1.0,1.0);
  glVertex2f(-0.18 +shift,-0.1);
  glVertex2f(-0.055+shift,0.03);
  glVertex2f(-0.01+shift,0.03);
  glVertex2f(-0.01+shift,-0.1);

  glEnd();

//---------------------------- tires -----------------------------------

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);

  glVertex2f(0.21 +shift,-0.22);
  glVertex2f(0.18+shift,-0.22);
  glVertex2f(0.15+shift,-0.28);
  glVertex2f(0.15+shift,-0.34);
  glVertex2f(0.18+shift,-0.40);
  glVertex2f(0.21+shift,-0.40);
  glVertex2f(0.24+shift,-0.34);
  glVertex2f(0.24+shift,-0.28);

  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.0,0.0,0.0);

  glVertex2f(-0.14+shift ,-0.22);
  glVertex2f(-0.11+shift,-0.22);
  glVertex2f(-0.08+shift,-0.28);
  glVertex2f(-0.08+shift,-0.34);
  glVertex2f(-0.11+shift,-0.40);
  glVertex2f(-0.14+shift,-0.40);
  glVertex2f(-0.17+shift,-0.34);
  glVertex2f(-0.17+shift,-0.28);

  glEnd();
//-----------------------------------------------------
  glBegin(GL_QUADS);
  glColor3f(0.972, 0.898, 0.145);
  glVertex2f(0.3 +shift,-0.12);
  glVertex2f(0.26+shift,-0.12);
  glVertex2f(0.26+shift,-0.17);
  glVertex2f(0.3+shift,-0.17);

  glColor3f(0.0,0.0,0.0);
  glVertex2f(0.04+shift ,-0.130);
  glVertex2f(0.04+shift,-0.115);
  glVertex2f(0.015+shift,-0.115);
  glVertex2f(0.015+shift,-0.130);

  glVertex2f(-0.16+shift ,-0.130);
  glVertex2f(-0.16+shift,-0.115);
  glVertex2f(-0.135+shift,-0.115);
  glVertex2f(-0.135+shift,-0.130);

  glEnd();


  glFlush();
  //glutPostRedisplay();
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(1200,600);
  glutCreateWindow("2d_project");
  glPointSize(0.5);
  glutDisplayFunc(&display);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return EXIT_SUCCESS;
}

