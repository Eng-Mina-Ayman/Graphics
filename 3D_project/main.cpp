#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/freeglut.h>

float screenx=1.8;
float lespeed=0,lescore=0;
int stop =0;
int level=1;
int ii=0,lview=600;
float dronx = 0,drony = -0.7,dronv=0,defbomb=0.02;
int bomb=0;
int rot=0;
int crush = 0;
int score = 0 ;
int ret=0;

typedef struct star{
double x;
double y;
double sizee;
}star;

#define LEN 8192
#define STARS_NUM 600

star a[STARS_NUM];


float xball=0,yball=1;
float aball = 1;

typedef struct rings{
double x;
double y;
float outrad;
float inrad;
double speed;
float angel;
}rings;

typedef struct bombs{
double x;
double y;
float bombrad;
}bombs;
bombs b[40];

#define RINGS_NUM 30
rings r[RINGS_NUM];

double RandomNumber(double Min, double Max){
	return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

void star_info(){
for(int i=0;i<STARS_NUM;i++){
  a[i].x = RandomNumber(-screenx, screenx);
  a[i].y = RandomNumber(-1, 1);
  a[i].sizee=RandomNumber(0, 2);
}
}

float definrad=0.01,defoutrad=0.04;

void ring_info(){
for(int i=0;i<RINGS_NUM;i++){
  r[i].x = RandomNumber(-screenx, screenx);
  r[i].y = RandomNumber(2,3);
  r[i].speed = RandomNumber(0.00010,0.00070);
  r[i].inrad = definrad;
  r[i].outrad = defoutrad;
  r[i].angel = 1;
}
}

void OnMouseClick(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    crush=0;
    score=0;
    level=1;
    lescore=0;
    lespeed=0;
    ii=0;
    ring_info();

  }

}

void windowSpecial(int key,int x,int y){
    if (key == GLUT_KEY_RIGHT){
       if(dronx < 1.7)
       dronx += 0.03;
       rot+=1;
    }

  else if (key == GLUT_KEY_LEFT){
        if(dronx > -1.7)
        dronx -= 0.03;
  rot-=1;
  }

  else if (key == GLUT_KEY_UP && drony < 0.98)
        drony += 0.03;

  else if (key == GLUT_KEY_DOWN && drony > -0.98)
        drony -= 0.03;

  glutPostRedisplay();
}

void windowKey(unsigned char key,int x,int y){

  if (key == 27) exit(0);

  else if (key == 32){drony-= 0.13;
    ret=1;bomb++;}

  glutPostRedisplay();
}

void windowMenu(int value){
  windowKey((unsigned char)value, 0, 0);
}

void timer(int x){
glutSpecialFunc(windowSpecial);
glutKeyboardFunc(windowKey);
glutPostRedisplay();
glutTimerFunc(1000/500, timer, 0);
}

double screen=1.0;

void reshape(int width,int height){
  double w2h = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* orthogonal projection */
  glOrtho(-screen*w2h,+screen*w2h, -screen,+screen, -screen,+screen);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void printv(va_list args, const char* format){
  char buf[LEN];
  char* ch=buf;
  vsnprintf(buf,LEN,format,args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void print(const char* format, ...){
  va_list args;
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void printAt(int x, int y, const char* format, ...){
  va_list args;

  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void BackGround(){
 glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  glColor3f(0, 0, 0 );
  glVertex2f( screenx,1 );
  glVertex2f( -screenx,1 );
  glColor3f(0.370, 0.062, 0.415);
  glVertex2f( -screenx,-1 );
  glColor3f(0.074, 0.070, 0.290 );
  glVertex2f( screenx,-1 );
  glEnd();
}

void stars_paint_move(){
for(int i=0;i<STARS_NUM;i++){
   float cl=RandomNumber(0.5, 1);
   glPointSize(a[i].sizee);
   glBegin(GL_POINTS);
   glColor3f(cl,cl,cl );
   glVertex2f( a[i].x , a[i].y );

   a[i].y -= 0.0001;

   if (a[i].y < -1)
    a[i].y=1;

    glEnd();
}

}

void RingsPaint(int i){
   glColor3f(0,0.7,1 );
   glTranslatef(r[i].x,r[i].y,0);
   glRotated(r[i].angel,0,1,0);
   glutSolidTorus(r[i].inrad,r[i].outrad,6,6);
}

void bomb_VS_rings(int i){
if(bomb>=0){
          glLoadIdentity();
   for(int j=0;j<=bomb;j++){
    if((crush == 0)&&(b[j].y > drony+0.1)&&(b[j].y > r[i].y-0.05)&&(b[j].y < r[i].y+0.05)&&(b[j].x > r[i].x-0.05)&&(b[j].x < r[i].x+0.05)&&(r[i].y<1)){
    r[i].inrad = 0;
    r[i].y = RandomNumber(1.5,3);
    r[i].x = RandomNumber(-1,1);
    r[i].inrad =definrad;
    b[j].y=1.1;
    score++;
    lescore++;
    stop =0;

    }
   }
   }
}

void dron_VS_rings(int i){
if (((r[i].x < dronx+0.16) && (r[i].x > dronx-0.16) && (r[i].y < drony+0.05) && (r[i].y > drony-0.05))
     ||((r[i].x < dronx+0.09) && (r[i].x > dronx-0.09) && (r[i].y < drony+0.24) && (r[i].y > drony-0.24))){
        crush = 1;
   }
}

void Level_Speed(){
if ((lescore == 10) && (stop == 0)){
    lespeed+=0.0005;
    lescore=0;
    stop = 1;
    level++;
    lview=0;
   }
}

void Rings_Move(int i){
r[i].y-=r[i].speed+lespeed;
   if (r[i].y < -1.2)
    r[i].y = 3 ;
  r[i].angel+=1;
}

void RingsDetails(){

 for(int i=0;i<RINGS_NUM;i++){
    glPushMatrix();
    RingsPaint(i);
    bomb_VS_rings(i);
    dron_VS_rings(i);
    Level_Speed();
    Rings_Move(i);
    glPopMatrix();
    }

}

void bombsDetails(){
  if(bomb==38)
    bomb=1;
  b[bomb].x = dronx;
  b[bomb].y = drony;
  for(int i=0;i<=bomb;i++){
  glPushMatrix();
  glTranslatef(b[i].x,b[i].y,0);
  glColor3f(1,0,0);
  glutSolidSphere(0.02,16,16);
  if(b[i].y<1.1)
  b[i].y+=0.02;
  glPopMatrix();
  }
}

void RocketDetails(){
//---------------------fire------------------------

glBegin(GL_POLYGON);
glColor3f(1,1,0);
glVertex2f(dronx,(drony));
glVertex2f(dronx-(RandomNumber(0.04,0.06)),(drony-0.15));
glColor3f(1,0,0);
glVertex2f(dronx,(drony-(RandomNumber(0.2,0.3))));
glColor3f(1,1,0);
glVertex2f(dronx+(RandomNumber(0.04,0.06)),(drony-0.15));
glEnd();

//-------------------------------------------------

//---------------------left side-------------------
  glColor3f(1,0,0);
  glPushMatrix();
  glTranslatef(dronx-0.05,(drony-0.05),0);
  glRotated(-90,1,0,0);
  glutSolidCone(0.07,0.1,4,4);
  glPopMatrix();
//------------------------------------------------

//--------------------right side------------------
  glColor3f(1,0,0);
  glPushMatrix();
  glTranslatef(dronx+0.05,(drony-0.05),0);
  glRotated(-90,1,0,0);
  glutSolidCone(0.07,0.1,4,4);
  glPopMatrix();
//------------------------------------------------

//---------------------tail------------------------
  glColor3f(1,0,0);
  glPushMatrix();
  glTranslatef(dronx,(drony-0.1),0);
  glRotated(-90,1,0,0);
  glutSolidCone(0.05,0.1,4,4);
  glPopMatrix();
//-------------------------------------------------


//------------------body---------------------

  glLoadIdentity();
 // glRotated(-rot,0,1,0);
  glColor3f(1,1,1);
  glPushMatrix();
  glTranslatef(dronx,drony,0);
  glutSolidCube(0.1);
  glPopMatrix();
//-------------------------------------------------


//----------------------head-----------------------
  glColor3f(1,1,1);
  glPushMatrix();
  glTranslatef(dronx,(drony+0.05),0);
  glRotated(-90,1,0,0);
  glutSolidCone(0.05,0.15,40,40);
  glPopMatrix();
//-------------------------------------------------


//----------------------WINDOW-----------------------
  glColor3f(0,0,1);
  glPushMatrix();
  glTranslatef(dronx,(drony+0.1),0);
  glutSolidSphere(0.02,16,16);
  glPopMatrix();
//-------------------------------------------------


//----------------------lines-----------------------

  glColor3f(1,0,0);
  glPushMatrix();

  glBegin(GL_QUADS);
  glVertex2f(dronx+0.03,drony+0.025);
  glVertex2f(dronx-0.03,drony+0.025);
  glVertex2f(dronx-0.03,drony+0.01);
  glVertex2f(dronx+0.03,drony+0.01);

  glVertex2f(dronx+0.03,drony-0.025);
  glVertex2f(dronx-0.03,drony-0.025);
  glVertex2f(dronx-0.03,drony-0.01);
  glVertex2f(dronx+0.03,drony-0.01);
  glEnd();
  glPopMatrix();
//-------------------------------------------------
}

void ViewScoreAndLevel(){
glColor3f(1.0,1.0,1.0);
  glLoadIdentity();
  glRasterPos3d(-1.75,0.9,0);
  print("Score : %d",score);
  glRasterPos3d(-1.5,0.9,0);
  print("Level : %d",level);
}

void GameOver(){
if (crush ==1){
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(screenx,1);
    glVertex2f(-screenx,1);
    glVertex2f(-screenx,-1);
    glVertex2f(screenx,-1);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glRasterPos3d(-0.18,0.3,0);
    print("Game Over");
    glRasterPos3d(-0.36,0.2,0);
    print("*********************************");
    glRasterPos3d(-0.3,0.1,0);
    print("Level :                         %d",level);
    glRasterPos3d(-0.3,0,0);
    print("Score :                        %d",score);
    glRasterPos3d(-0.36,-0.1,0);
    print("*********************************");
    glRasterPos3d(-0.3,-0.2,0);
    print("Right click : for try again ");
    glRasterPos3d(-0.3,-0.3,0);
    print("Esc : for exit");
}
}

void StartCounter(){
if(ii<2000){
    if(ii<500){
    glColor3f(1.0,1.0,0);
    glRasterPos3d(0,0,0);
    print("3");
    }
    else if(ii<1000){
    glColor3f(1.0,1.0,0);
    glRasterPos3d(0,0,0);
    print("2");
    }
    else if(ii<1500){
    glColor3f(1.0,1.0,0);
    glRasterPos3d(0,0,0);
    print("1");
    }
    else {
    glColor3f(1.0,1.0,0);
    glRasterPos3d(0,0,0);
    print("GO");
    }
    ii++;

}
}

void display()
{glutSpecialFunc(windowSpecial);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if(ret<14){
    drony+= 0.01;
    ret++;
  }

  BackGround();
  stars_paint_move();
  RingsDetails();
  bombsDetails();
  glLoadIdentity();
  RocketDetails();
  ViewScoreAndLevel();
  StartCounter();

    if(lview<500){
    glColor3f(1.0,1.0,0);
    glRasterPos3d(-0.2,0,0);
    print("Level %d",level);
    }
    lview++;

  GameOver();
  glLoadIdentity();
  glutSwapBuffers();

}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  star_info();
  ring_info();
  glutInitWindowSize(700,700);
  glutCreateWindow("Space War  ");
  glutSpecialFunc(windowSpecial);
  glutKeyboardFunc(windowKey);
  glutDisplayFunc(&display);
  glutReshapeFunc(reshape);
  glutMouseFunc(OnMouseClick);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutTimerFunc(0, timer, 0);
  glutFullScreen();
  glutMainLoop();

  return EXIT_SUCCESS;
}


