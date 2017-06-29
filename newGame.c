#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
float bird_xc;
int bird_yc=375;
int eggs_caught=0,missed_eggs=0,level_count=1,points=0;
int p=0;
// for incrementing the points based on color
int d=0;
// for color selection
float egg_xc,egg_yc;
// for coordinates of egg
int basket_x,basket_y;
int flagforbird=1;
// for coordinates of basket
int a=500,b=500; // for default size of the screen
int s=0;
// for menu option
int dropped_eggs=0;

float speed_1=1.5,speed_2=2.0,speed_3=2.5,speed_4=3.0;

int red_egg=0,white_egg=0;

int w=48,h=48,t=10,e=9,g=12;

void myinit();
void start_screen();
void egg();
void basket(int,int);
void duck(int,int);
void print_score();
void egg_start();
void color();
void score();
void display(void);
void myReshape(int,int);
void keys(unsigned char,int,int);
void menu(int);

void myinit()
{
    glViewport(0,0,a,b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,(GLdouble)a,0,(GLdouble)b);
    glMatrixMode(GL_MODELVIEW);

}

void start_screen()
{
    int k;
    char cat[7]="-CATCH";
    char Or[3]="OR";
    char hatch[7]="HATCH-";

    glColor3f(0,1,0);
    glRasterPos2i(150,180);
    for(k=0; k<7; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,cat[k]);

    glColor3f(1,1,1);
    glRasterPos2i(260,180);
    for(k=0; k<3; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,Or[k]);

    glColor3f(1,0,0);
    glRasterPos2i(340,180);
    for(k=0; k<7; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,hatch[k]);

char text[9]="EGG GAME";
int p;

glRasterPos2i(200,250);
glColor3f(1,0,1);
for(p=0;p<8;p++){
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[p]);
}
    egg_xc=110;
    egg_yc=370;
    egg();
    duck(25,375);
    basket(330,10);
}

void egg()
{
    float x,y,z=0;
    int t;
    glBegin(GL_POLYGON);
    for(t=0; t<=360; t+=1)
    {
        x = egg_xc+10*(cos(t));
        y = egg_yc+16*(sin(t));

        glVertex2f(x,y);
    }
    glEnd();
}

void basket(int i,int j)
{
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i,30.0+j);
    glVertex2f(10.0+i,10.0+j);
    glVertex2f(70.0+i,10.0+j);
    glVertex2f(80.0+i,30.0+j);
    glEnd();
}

void duck(int i,int j)
{
int x,y;
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(10.0+i,20.0+j);
    glVertex2f(160.0+i,20.0+j);
    glVertex2f(160.0+i,40.0+j);
    glVertex2f(10.0+i,40.0+j);
    glEnd();
    glFlush();

    }

void print_score()
{
    printf("\nLevel reached: %d\n\n",level_count);
    printf("\nNo. of eggs dropped= %d \n",dropped_eggs+red_egg);
    printf("\nNo. of eggs caught = %d\n",eggs_caught+red_egg);
    printf("\nNo. of eggs missed = %d\n",missed_eggs);
    printf("\nwhite eggs = %d\tpoints gained = %d\n",white_egg,white_egg*20);
    printf("\nRed eggs= %d\tpoints deducted = %d\n",red_egg,red_egg*50);
    printf("\n\n\nyour score=%d\n\n",white_egg*20-red_egg*50);

}

void egg_start()
{
    egg_yc=375;
    if(missed_eggs>=10)
    {
        printf("\n\n\t\t\t\tGAME OVER\n\n");
        print_score();
        exit(0);
    }
    dropped_eggs++;
    if(d==1)//dont count grey eggs
        dropped_eggs--;
    egg_xc=bird_xc+80;
    d=rand()%2;

}

void color()
{
    switch(d)
    {
    case 0:
        glColor3f(1,1,1);
        p=20;
        break; //white
    case 1:
        glColor3f(1,0,0);
        p=-50;
        break; //red-don't catch
    }
}

void score()
{
    if(egg_yc<=50 && (egg_xc>=basket_x&&egg_xc<=basket_x+60))
    {
        printf("\a");
        eggs_caught++;
        switch(d)
        {
        case 0:
            white_egg++;
            break;
        case 1:
            red_egg++;
            eggs_caught--;
            break;

        }
        egg_yc=-10;
    }
    missed_eggs=dropped_eggs-eggs_caught;
}

void display(void)
{
    int i;

    char level1[12]="LEVEL 1";
    char level2[12]="LEVEL 2";
    char level3[12]="LEVEL 3";
    char level4[12]="LEVEL 4";
    glClear(GL_COLOR_BUFFER_BIT);
    if(s>=1)
    {

        if(level_count==1)
        {
            glColor3f(1,1,1);
            glRasterPos2i(400,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level1[i]);
        }
        else if(level_count==2)
        {
            glColor3f(1,1,1);
            glRasterPos2i(400,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level2[i]);
        }
        else if(level_count==3)
        {
            glColor3f(1,1,1);
            glRasterPos2i(400,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level3[i]);
        }
        if(level_count==4)
        {
            glColor3f(1,1,1);
            glRasterPos2i(400,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level4[i]);
        }

        glutPostRedisplay();
        if(eggs_caught>=15)
        {
            if(flagforbird==1)
            {
                if(bird_xc>=300)
                {
                    flagforbird=-1;
                }
                bird_xc+=speed_4;

            }

            if(flagforbird==-1)
            {
                if(bird_xc<=20)
                {
                    flagforbird=1;
                }
                bird_xc-=speed_4;
            }


            duck(bird_xc,bird_yc);
        }

        else if(eggs_caught>=10)
        {
            if(flagforbird==1)
            {
                if(bird_xc>=300)
                {
                    flagforbird=-1;
                }
                bird_xc+=speed_3;

            }

            if(flagforbird==-1)
            {
                if(bird_xc<=20)
                {
                    flagforbird=1;
                }
                bird_xc-=speed_3;
            }

            duck(bird_xc,bird_yc);
        }


        else if(eggs_caught>=5)
        {
            if(flagforbird==1)
            {
                if(bird_xc>=300)
                {
                    flagforbird=-1;
                }
                bird_xc+=speed_2;

            }

            if(flagforbird==-1)
            {
                if(bird_xc<=20)
                {
                    flagforbird=1;
                }
                bird_xc-=speed_2;
            }


            duck(bird_xc,bird_yc);
        }

        else
        {
            if(flagforbird==1)
            {
                if(bird_xc>=300)
                {
                    flagforbird=-1;
                }
                bird_xc+=speed_1;

            }

            if(flagforbird==-1)
            {
                if(bird_xc<=20)
                {
                    flagforbird=1;
                }
                bird_xc-=speed_1;

            }


            duck(bird_xc,bird_yc);
        }
        if(egg_yc<=10)
            egg_start();
        color();
        egg();
        basket(basket_x,basket_y);
        if(eggs_caught>=15)
        {
            egg_yc-=speed_4;
            level_count=4;
        }
        else if(eggs_caught>=10)
        {
            egg_yc-=speed_3;
            level_count=3;
        }
        else if(eggs_caught>=5)
        {
            egg_yc-=speed_2;
            level_count=2;
        }
        else
            egg_yc-=speed_1;
        score();
    }
    else
        start_screen();
    glFlush();
    glutSwapBuffers();
}

void myReshape(int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
    a=w;
    b=h;
}

void keys(unsigned char key,int x,int y)
{
    if(key=='q'||key=='Q')
    {
        printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
        print_score();
        exit(0);
    }
    if(key=='s'||key=='S')
        s+=1;
    glutPostRedisplay();
}


void keys1(int key,int x,int y)
{
    char c=(char)key;

    if(c==GLUT_KEY_LEFT)
    {
        if(basket_x<=10)
        {
        }
        else
        {
            basket_x-=20;
        }
    }
    if(c==GLUT_KEY_RIGHT)
    {
        if(basket_x>=420)
        {

        }
        else
        {
            basket_x+=20;
        }
    }
	
    glutPostRedisplay();
}

void menu(int id)
{
    switch(id)
    {
    case 1:
        s+=1;
        break;
    case 2:
        print_score();
        break;
    case 3:
        printf("\n\n\n\t\tQUIT BY PLAYER\n");
        break;
    default:
        exit(0);
    }

}

int main(int argc,char **argv)
{
	
    printf("******************************************************************");
    printf("\n\t\t\t\t EGG GAME\n\n");
    printf("******************************************************************");
    printf("\n\tHow to Play..?\n\n <1>The objective of the game is to catch the eggs in the basket.\n\t To move Basket using keyboard\n");
    printf("\n <2> To Start, press key 's' or 'S' or \n\tClick Right mouse button then click 'Start Game'.\n");
    printf("\n <3> To Quit manually, press key 'q' or 'Q' or\n\t Click Right mouse button then click 'Quit'.\n");
    printf("\n\n RULES : If the player misses 10 eggs,then 'Game Over'.\n");
    printf("\n\n\n SCORE : ->White Egg = 20 point\n->Red Egg = -50 points\n");

    printf("\nFor each level, speed is increased\n\n");

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(a,b);
    glutCreateWindow("EGG GAME");
    myinit();
    glutCreateMenu(menu);
    glutAddMenuEntry("Start game",1);
    glutAddMenuEntry("Score",2);
    glutAddMenuEntry("Quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutSpecialFunc(keys1);
    glutIdleFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();
}
