//CSC 470 Project 2
//Ryan, Ali, Alleny

#include <stdio.h> 
#include <windows.h>
#include <stdlib.h>  
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;
#define W 600
#define H 600

//globals
int boxbig = 3;
int boxdown = -84;
int big = 1;
float xmove = .011, ymove = 1, zmove = -0.1;
int angle = 0;
int linescalex = 0, linescaley = 0, linescale = 0;

//lookat values
float eye1 = 10, eye2 = 6, eye3 = 10;
float at1 = 0, at2 = 0, at3 = 0;
float up1 = 0, up2 = 1, up3 = 0;
float zoom = 4;

//light values
float lightx = 10, lighty = 10, lightz = 10;

//car movement
float carRotateY = 90;
float carTransX, carTransZ;

void setup(void)
{
    //Turning on the lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //Iintensity of the lights
    GLfloat lightIntensity[] = { 1.5f, 1.5f, 1.5f, 1.5f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    //View port
    glViewport(0, 0, W, H);
}

void displaySolid(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W / zoom, W / zoom, -H / zoom, H / zoom, -W, W);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye1, eye2, eye3, at1, at2, at3, up1, up2, up3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.6f, 1.0f };
    GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 90.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Direction of the lights
    GLfloat lightPosition[] = { lightx,lighty, lightz, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //make the stuff under here
    float theta, X, Y;

    //-------------moon---------------
    /*glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        //glTranslatef(-300, -30, -200);
        theta = i * 3.142 / 180;
        glVertex2f(-200 + 60 * cos(theta), 200 + 60 * sin(theta));
    }
    glEnd();*/


    //racetrack
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 360; i++)
        {
            int move = 0;
            if (j == 1)
                move = 20;
            theta = i * 3.142 / 180;
            X = 150 * cos(theta);
            Y = 150 * sin(theta);
            if (i % 40 == 0 && j < 2)
            {
                mat_ambient[0] = 0;
                mat_ambient[1] = 0;
                mat_ambient[2] = 0;
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glPushMatrix();
                glRotatef(move, 0, 1, 0);
                glPushMatrix();
                glTranslatef(X, -80, Y);
                glRotatef(-i, 0, 1, 0);
                glutSolidCube(75);
                glPopMatrix();
                glPopMatrix();
            }
            else if (i % 40 == 0 && j == 2)
            {
                mat_ambient[0] = 1; //R
                mat_ambient[1] = 1; //G
                mat_ambient[2] = 0; //B
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

                glPushMatrix();
                glTranslatef(X, -79, Y);
                glRotatef(-i, 0, 1, 0);
                glScalef(-0.089, 1, -0.6);
                glutSolidCube(75);
                glPopMatrix();

            }
        }
    }



    //grass
    glPushMatrix();
    glTranslatef(0, -84, 0);
    glScalef(27, 3, 27);
    mat_ambient[0] = 0;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //sky
    /*glPushMatrix();
    glTranslatef(-300, -50, -300);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRecti(600, 0, 0, 600);
    glPopMatrix();


    //sky
    glPushMatrix();
    glTranslatef(-300, -50, -300);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRecti(600, 0, 0, 600);
    glPopMatrix();*/


    // flowers

    glPushMatrix();
    glTranslatef(-160, -40, 310);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, -40, 315);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-90, -40, 250);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100, -40, 340);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, -40, 310);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, -40, 310);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-200, -40, -10);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -40, -90);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -40, -190);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250, -40, -180);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-230, -40, -210);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -40, -250);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-250, -40, -50);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-260, -40, -10);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, -40, 60);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(260, -40, 60);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, -40, 10);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -40, -10);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -40, -90);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -40, -190);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, -40, -180);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(230, -40, -210);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -40, -250);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();


    glPushMatrix();//snow clump too
    glTranslatef(250, -40, -50);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();//snow clump too
    glTranslatef(260, -40, -10);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();

    glPushMatrix();//snow clump too
    glTranslatef(190, -40, 60);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 5.1;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 2, 8, 9);
    glPopMatrix();




    //------------trees---------------\\

    glPushMatrix();
    glTranslatef(-40, -30, -290);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 0.1;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40, -10, -290);
    glRotatef(120, -360, 360, 390);
    mat_ambient[0] = 0.1;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(50, 100, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-40, -50, -290);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.8;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //----------pine tree-----------\\

    glPushMatrix();
    glTranslatef(-300, -30, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -10, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-300, 20, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-300, -50, -290);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    //---------------------------------------
    glPushMatrix();
    glTranslatef(-200, -30, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, -10, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-200, 20, -290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-200, -50, -290);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //ornaments
    glPushMatrix();
    glTranslatef(-200, 0, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, -10, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-180, -20, -250);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200, 10, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 20, -245);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 5.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-180, 30, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, 40, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, 50, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.5;
    mat_ambient[2] = 5.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, 60, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, 70, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, 70, -245);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 2.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();
    //=========================================

    glPushMatrix();
    glTranslatef(-300, -30, -40);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -10, -40);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-300, 20, -40);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-300, -50, -40);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //------------ornaments-----------\\

    glPushMatrix();
    glTranslatef(-300, 0, 15);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-280, -20, 15);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-260, 20, 10);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-240, 70, 15);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-240, -10, 15);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5, 10, 10);
    glPopMatrix();


    //---------------------------------------


    //=========================================

    glPushMatrix();
    glTranslatef(-300, -30, 90);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -10, 90);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-300, 20, 90);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-300, -50, 90);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-300, -30, 290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -10, 290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-300, 20, 290);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-300, -50, 290);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(100, -30, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, -10, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(100, 20, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(100, -50, 400);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-50, -30, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, -10, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(-50, 20, 400);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(-50, -50, 400);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //---------------------------------------------------------------------------

    //bench
    glPushMatrix();
    glTranslatef(300, -42, -55);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -50);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -45);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -40);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -35);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -30);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -25);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -20);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -15);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -42, -10);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -55);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -50);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -45);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -40);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -35);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -30);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -25);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -20);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -15);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -42, -10);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.2;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //-------------------------------------------------------------bench here------

    glPushMatrix();
    glTranslatef(300, -30, -260);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, -10, 260);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(40, 100, 9, 8);
    glPopMatrix();

    //snow cap
    glPushMatrix();
    glTranslatef(300, 20, 260);
    glRotatef(120, -360, 360, 390);
    //glRotatef(-90, 190, 0, -180);
    mat_ambient[0] = 3.0;
    mat_ambient[1] = 3.0;
    mat_ambient[2] = 3.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(35, 50, 9, 8);
    glPopMatrix();

    //trunk
    glPushMatrix();
    glTranslatef(300, -30, 260);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 0.7;
    mat_ambient[1] = 0.164706;
    mat_ambient[2] = 0.164706;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //------------------------------bush--------------------------------------

    glPushMatrix();
    glTranslatef(160, -40, -320);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(160, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(170, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(150, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120, -40, -320);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(110, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(115, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(120, -40, 320);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(110, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(115, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(210, -40, 320);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(225, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(215, -40, 328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();
    //--------------------------------------------\\

    glPushMatrix();
    glTranslatef(260, -40, -200);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(260, -40, -200);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(270, -40, -208);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, -40, -200);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();



    //-----------moon-----------\\

    glPushMatrix();
    glTranslatef(-500, 10, -100);
    mat_ambient[0] = 2.0;
    mat_ambient[1] = 2.0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(30, 30, 50);
    glPopMatrix();



    //---------ball------------\\

    glPushMatrix();
    glTranslatef(-200, -40, -170);
    mat_ambient[0] = 1.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(7, 30, 50);
    glPopMatrix();

    //---------snowman-------\\

    glPushMatrix();
    glTranslatef(-170, -40, -260);
    mat_ambient[0] = 2.0;
    mat_ambient[1] = 2.0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(17, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -20, -260);
    mat_ambient[0] = 2.0;
    mat_ambient[1] = 2.0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(15, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -0, -260);
    mat_ambient[0] = 2.0;
    mat_ambient[1] = 2.0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(12, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -0, -250);
    mat_ambient[0] = 5.5;
    mat_ambient[1] = 2.5;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCone(4, 10, 8, 9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -10, -240);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 5.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(3, 5, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -20, -240);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 5.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(3, 5, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -30, -240);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 0.0;
    mat_ambient[2] = 5.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(3, 5, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0.7; //R
    mat_ambient[1] = 0.2; //G
    mat_ambient[2] = 0.2; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-160, -20, -250);
    glRotatef(90, 90, 90, 180);
    glScalef(1.0, .2, .5);
    glutSolidCube(15);
    glPopMatrix();



    //----------bush----------\\

    glPushMatrix();
    glTranslatef(-160, -40, -320);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.5;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150, -40, -328);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();
    //--------------------------------------------\\

    glPushMatrix();
    glTranslatef(-300, -40, -128);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-310, -40, -118);
    mat_ambient[0] = 0.1;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -40, -118);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, -40, -128);
    mat_ambient[0] = 0.0;
    mat_ambient[1] = 1.0;
    mat_ambient[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 50, 50);
    glPopMatrix();




    //----------------people--------------------\\
    //torso
    glPushMatrix();
    glTranslatef(-300, -30, -200);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(5, 10, 10, 5);
    glPopMatrix();
    //torso
    glPushMatrix();
    glTranslatef(-300, -30, -200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(19);
    glPopMatrix();
    //head
    glPushMatrix();
    glTranslatef(-300, -10, -200);
    mat_ambient[0] = 2;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();
    //body
    glPushMatrix();
    glTranslatef(-285, -42, -200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(15);
    glPopMatrix();
    //legs
    glPushMatrix();
    glTranslatef(-270, -42, -200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();
    //foot
    glPushMatrix();
    glTranslatef(-300, -42, -190);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();

    //foot
    glPushMatrix();
    glTranslatef(-270, -42, -190);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();


    //torso
    glPushMatrix();
    glTranslatef(-300, -30, -170);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(5, 10, 10, 5);
    glPopMatrix();
    //torso
    glPushMatrix();
    glTranslatef(-300, -30, -170);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(19);
    glPopMatrix();
    //head
    glPushMatrix();
    glTranslatef(-300, -10, -170);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();
    //body
    glPushMatrix();
    glTranslatef(-290, -42, -170);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(15);
    glPopMatrix();
    //legs

    glPushMatrix();
    glTranslatef(-275, -42, -160);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();


    //foot
    glPushMatrix();
    glTranslatef(-270, -42, -170);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-270, -42, -190);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();

    //--------------------------------------------------------------------------

    //torso
    glPushMatrix();
    glTranslatef(-50, -20, 200);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 1.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(5, 10, 10, 5);
    glPopMatrix();
    //torso
    glPushMatrix();
    glTranslatef(-50, -20, 200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 1.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(15);
    glPopMatrix();
    //head
    glPushMatrix();
    glTranslatef(-50, -0, 200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();
    //body
    glPushMatrix();
    glTranslatef(-52, -35, 200);
    mat_ambient[0] = 0.5;
    mat_ambient[1] = 0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(14);
    glPopMatrix();
    //legs
    glPushMatrix();
    glTranslatef(-45, -42, 210);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();
    //foot
    glPushMatrix();
    glTranslatef(-40, -42, 200);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();

    //foot
    glPushMatrix();
    glTranslatef(-270, -42, -190);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();

    //-----------------------------------------------------------------
    //torso
    glPushMatrix();
    glTranslatef(150, -20, -200);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(5, 10, 10, 5);
    glPopMatrix();
    //torso
    glPushMatrix();
    glTranslatef(150, -20, -200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1.5;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(15);
    glPopMatrix();
    //head
    glPushMatrix();
    glTranslatef(150, -0, -200);
    mat_ambient[0] = 1.5;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();
    //body
    glPushMatrix();
    glTranslatef(152, -35, -200);
    mat_ambient[0] = 0.5;
    mat_ambient[1] = 0;
    mat_ambient[2] = 2.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(14);
    glPopMatrix();
    //legs
    glPushMatrix();
    glTranslatef(145, -42, -210);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();
    //foot
    glPushMatrix();
    glTranslatef(140, -42, -200);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0.2;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();

    //foot
    glPushMatrix();
    glTranslatef(-270, -42, -190);
    mat_ambient[0] = 1;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(5);
    glPopMatrix();
    //----------------bench--------------------\\

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -195);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -190);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -180);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();


    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -170);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();


    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -160);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -150);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -140);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();

    //bench
    glPushMatrix();
    glTranslatef(-300, -42, -130);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glScalef(1.0, 1.1, 1.1);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(8);
    glPopMatrix();


    //----------------child--------------------\\

        // body
    glPushMatrix();
    glTranslatef(-200, -30, -200);
    mat_ambient[0] = 0;
    mat_ambient[1] = 0;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();

    // head
    glPushMatrix();
    glTranslatef(-200, -20, -200);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(10, 5, 10);
    glPopMatrix();

    //arms
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-200, -30, -215);
    glScalef(.9, .2, .5);
    glutSolidCube(15);

    glPopMatrix();//wings
    /*glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-190, -30, -200);
    glRotatef(-90, 0, 0, -180);
    glScalef(.9, .2, .5);
    glutSolidCube(15);
    glPopMatrix();*/

    //arms
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0.5; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-215, -25, -200);
    glScalef(.9, .2, .5);
    glutSolidCone(10, 20, 20, 3);
    glPopMatrix();


    //leg1
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-200, -40, -200);
    glRotatef(90, 90, 90, 180);
    glScalef(.9, .2, .5);
    glutSolidCube(15);
    glPopMatrix();


    //leg2
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-200, -35, -200);
    glRotatef(90, 90, 90, 180);
    glScalef(.9, .2, .5);
    glutSolidCube(15);
    glPopMatrix();


    //wireplanet
    glPushMatrix();
    glTranslatef(-6, 10, -6);
    glRotatef(-carRotateY, 1, 1, 1);
    mat_ambient[0] = 1;
    mat_ambient[1] = 1;
    mat_ambient[2] = 1;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutWireTorus(50, 50, 8, 9);
    glutWireSphere(60, 100, 30);
    glutSolidCube(15);
    glPopMatrix();

    //pole
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-6, -30, -6);
    glRotatef(90, 90, 90, 180);
    glScalef(.9, .2, .5);
    glutSolidCube(30);
    glPopMatrix();


    //----------------snow--------------------\\
    
    for (int i = 0; i < 500; i++) {
        glPushMatrix();
        glTranslatef(rand() % 1000, rand() % 300, rand() % 1000);
        glRotatef(-carRotateY, 1, 1, 1);
        mat_ambient[0] = 2.5;
        mat_ambient[1] = 2.5;
        mat_ambient[2] = 2.5;
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glutSolidSphere(2, 2, 2);

        glPopMatrix();
    }
    //--------------------------------------------------------------------------------------------cars--------------------------------------------------------------------------------\\
    //car1 normal race car
    glPushMatrix();
    glTranslatef(carTransX, -32, carTransZ);
    glRotatef(-carRotateY, 0, 1, 0); // rotate is - so rotation follows clockwise motion
    glScalef(.9, .9, .9); //use this to scale the whole car
    glPushMatrix();
    glScalef(2.5, .4, .9);//use this to scale body of car
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //side skirts
    glPushMatrix();
    glTranslatef(2, -5, 0);
    glScalef(1.5, .1, 1);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();


    //front grill
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(22, 0, 0);
    glScalef(.9, .2, .5);
    glutSolidCube(25);
    glPopMatrix();

    //yellow part of seats
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-5, -5.5, 3.5);
    glScalef(1.8, .29, 3.5);
    glutSolidCone(20, 2.5, 6, 10);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-5, 5.5, 3.5);
    glScalef(1.8, .29, 3.5);
    glutSolidCone(20, 2.5, 6, 10);
    glPopMatrix();


    //back bumper
    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-32, 0, 4);
    glScalef(.25, .9, .2);
    glutSolidCube(25);
    glPopMatrix();

    //yellow spoiler part
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-33, -5, 8);
    glScalef(.1, .1, .5);
    glutSolidCube(25);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-32, 5, 8);
    glScalef(.1, .1, .5);
    glutSolidCube(25);
    glPopMatrix();


    //blue spoiler
    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(-32, 0, 15);
    glScalef(.15, 1, .1);
    glutSolidCube(25);
    glPopMatrix();

    //blue seat parts
    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-8, 10, -5);
    glScalef(1, 1, 1);
    glutSolidCube(5);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-8, 10, 5);
    glScalef(1, 1, 1);
    glutSolidCube(5);
    glPopMatrix();

    //wheels
    glPushMatrix();
    glTranslatef(-22, -4, 12);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(2, 6, 8, 8);//2
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-22, -4, 12);
    glutSolidTorus(2, 3, 8, 8);//2
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(25, -4, 12);
    glutSolidTorus(2, 5, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(25, -4, 12);
    glutSolidTorus(2, 2.5, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-22, -4, -12);
    glutSolidTorus(2, 6, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-22, -4, -12);
    glutSolidTorus(2, 3, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(25, -4, -12);
    glutSolidTorus(2, 5, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(25, -4, -12);
    glutSolidTorus(2, 2.5, 8, 8);
    glPopMatrix();

    glPopMatrix();

    //car2 crazy ufo
    glPushMatrix();
    glRotatef(120, 0, 1, 0); //rotate 2nd car 120 degrees from the first car
    glPushMatrix();
    glTranslatef(carTransX, -32, carTransZ); // rotate is + so rotation is counter clockwise
    glRotatef(carRotateY * 4, 0, 1, 0);
    glScalef(1, 1, 1); //use this to scale the whole car
    glPushMatrix();
    glScalef(5, 1, 5); //use this to scale body of car
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidSphere(5.2, 10, 5);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(0, 0, 3.0);
    glScalef(3.0, 3.0, 1.0);
    glutSolidSphere(5.2, 10, 7);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glRotatef(270, 0, 0, 0);
    glTranslatef(0, 0, 5.5);
    glScalef(1.5, 1.5, 1.15);
    glutSolidSphere(5.2, 10, 7);
    glPopMatrix();


    //bottom thingies
    glPushMatrix();
    glTranslatef(-15, -1, 12);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(2, 2, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, -1, 12);
    glutSolidTorus(2, 2, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -1, -12);
    glutSolidTorus(2, 2, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, -1, -12);
    glutSolidTorus(2, 2, 8, 8);
    glPushMatrix();
    glTranslatef(5, -1, 12);
    glutSolidTorus(2, 1, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-35, -1, 12);
    glutSolidTorus(2, 1, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -1, 32);
    glutSolidTorus(2, 1.5, 8, 8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -1, -8);
    glutSolidTorus(2, 1.5, 8, 8);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    //car3 tilted car
    glPushMatrix();
    glRotatef(240, 0, 1, 0); //rotate 3rd car 240 degrees from the first car
    glPushMatrix();
    glTranslatef(carTransX, -25, carTransZ);
    glRotatef(-carRotateY, 0, 1, 0);
    glRotatef(-45, 1, 0, 0); // car is tilted 45 degrees on x axis so its driving on 2 left wheels
    glScalef(1, 1, 1); //use this to scale the whole car
    glPushMatrix();
    glScalef(2, .5, .9); //use this to scale body of car
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10, 0);
    glScalef(1.2, .3, .9);
    glutSolidCube(25);
    glPopMatrix();

    //wings
    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glScalef(.5, .1, 1);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(.45, .1, 1.1);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glScalef(.4, .1, 1.2);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2, 0, 0);
    glScalef(.35, .1, 1.3);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, 0, 0);
    glScalef(.3, .1, 1.4);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4, 0, 0);
    glScalef(.25, .1, 1.5);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glScalef(.2, .1, 1.5);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6, 0, 0);
    glScalef(.15, .1, 1.5);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //front grill
    glPushMatrix();
    glTranslatef(2, -1, 0);
    glScalef(2.1, .1, .7);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //exhausts
    glPushMatrix();
    glTranslatef(-4, -6, 2);
    glScalef(2.1, .1, .1);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5, -6, 2);
    glScalef(2.1, .1, .1);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, -6, -2);
    glScalef(2.1, .1, .1);
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5, -6, -2);
    glScalef(2.1, .1, .1);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //trim
    glPushMatrix();
    glTranslatef(0, -6, 0);
    glScalef(2.1, .1, 1);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //lights
    glPushMatrix();
    glTranslatef(0, 3, 8);
    glScalef(2.1, .15, .2);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 3, 8);
    glScalef(2.15, .075, .2);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 3, -8);
    glScalef(2.1, .15, .2);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 3, -8);
    glScalef(2.15, .075, .2);
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidCube(25);
    glPopMatrix();

    //windows
    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(0, 10, 0);
    glScalef(1.21, .18, .7);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    mat_ambient[0] = 0; //R
    mat_ambient[1] = 0; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(0, 10, 0);
    glScalef(1.0, .18, .91);
    glutSolidCube(25);
    glPopMatrix();

    //window splitter
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(0, 10, 0);
    glScalef(.1, .2, .92);
    glutSolidCube(25);
    glPopMatrix();

    //wheels
    glPushMatrix();
    glTranslatef(-22, -4, 12); //-22 -4 12
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(1, 6, 8, 8);//2
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22, -4, 12); //-22 -4 12
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glutSolidTorus(2, 3, 16, 16);//2
    glPopMatrix();


    //wheels
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(22, -4, 12);//22 -4 12
    glutSolidTorus(1, 6, 8, 8);
    glPopMatrix();
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(22, -4, 12);//22 -4 12
    glutSolidTorus(2, 3, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-22, -4, -12); //-22 -4 -12
    glutSolidTorus(1, 6, 8, 8);
    glPopMatrix();
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(-22, -4, -12); //-22 -4 -12
    glutSolidTorus(2, 3, 8, 8);
    glPopMatrix();

    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = 1; //G
    mat_ambient[2] = 1; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(22, -4, -12);//22 -4 -12
    glutSolidTorus(1, 6, 8, 8);
    glPopMatrix();
    glPushMatrix();
    mat_ambient[0] = 1; //R
    mat_ambient[1] = .5; //G
    mat_ambient[2] = 0; //B
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glTranslatef(22, -4, -12);//22 -4 -12
    glutSolidTorus(2, 3, 8, 8);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
    //make stuff above this

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
    system("cls");
    cout << "lightx = " << lightx << " lighty = " << lighty << " lightz = " << lightz << endl;
    cout << "eye1 = " << eye1 << " eye2 = " << eye2 << " zoom = " << zoom << endl;
    cout << "carRotateY = " << carRotateY << " carTransX = " << carTransX << " carTransZ = " << carTransZ << endl;
    cout << "xmove = " << xmove << " ymove = " << ymove << " zmove = " << zmove << endl;

}
//-------------------------------------------------------------------------------------------------------car end-------------------------------------------------------------------------------------------//
void timer(int iUnused)
{
    //do animation here
    //carRotateY = 90;
    //carTransX = -153, carTransZ = 0;
    carTransX = 0;
    carTransZ = 0;
    carRotateY = 90;
    angle++;
    float theta, X, Y;
    theta = angle * 3.142 / 180;
    X = 150 * cos(theta);
    Y = 150 * sin(theta);
    carRotateY += angle;
    carTransX += X;
    carTransZ += Y;
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);//calls itself every 30ms
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'a':
        eye1 += 1;
        glutPostRedisplay();
        break;
    case 'd':
        eye1 -= 1;
        glutPostRedisplay();
        break;
    case 'w':
        eye2 += 1;
        glutPostRedisplay();
        break;
    case 's':
        eye2 -= 1;
        glutPostRedisplay();
        break;
    case 'q':
        zoom -= 1;
        glutPostRedisplay();
        break;
    case 'e':
        zoom += 1;
        glutPostRedisplay();
        break;
        /*case 'i':
            lighty -= 1;
            glutPostRedisplay();
            break;
        case 'j':
            lightx += 1;
            glutPostRedisplay();
            break;
        case 'k':
            lighty += 1;
            glutPostRedisplay();
            break;
        case 'l':
            lightx -= 1;
            glutPostRedisplay();
            break;
        case 'u':
            lightz += 1;
            glutPostRedisplay();
            break;
        case 'o':
            lightz -= 1;
            glutPostRedisplay();
            break;*/
    case 'm':
        big += 1;
        glutPostRedisplay();
        break;
    case ',':
        big -= 1;
        glutPostRedisplay();
        break;
        //scale, move things
    case 'z':
        xmove += .1;
        glutPostRedisplay();
        break;
    case 'x':
        xmove -= .1;
        glutPostRedisplay();
        break;
    case 'c':
        ymove += .1;
        glutPostRedisplay();
        break;
    case 'v':
        ymove -= .1;
        glutPostRedisplay();
        break;
    case 'b':
        zmove += .1;
        glutPostRedisplay();
        break;
    case 'n':
        zmove -= .1;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Project 2");
    glutKeyboardFunc(keyInput);
    setup();
    glutDisplayFunc(displaySolid);
    timer(0);
    glutMainLoop();
    return 0;
}
