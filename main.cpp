#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
GLfloat alpha = 0.0, theta = 0.0, gamma = 0.0, axis_x=0.0, axis_y=0.0;
bool fan4=false;

GLdouble eyex=30, eyey=6,eyez=-20,centerx=2,centery=0,centerz=0, upx=0,upy=1,upz=0;
// original -> 20,6,-20, 2,0,0, 0,1,0
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;

GLboolean bRotate = false, uRotate = false, light0 = false,light1=false,light2=false;

static GLfloat v_cube[8][3] =
{
    {0, 0, 0}, //0
    {0, 0, 1}, //1
    {1, 0, 1}, //2
    {1, 0, 0}, //3
    {0, 1, 0}, //4
    {0, 1, 1}, //5
    {1, 1, 1}, //6
    {1, 1, 0}  //7
};

static GLubyte cubeIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};




static GLfloat v_floor[8][3] =
{
    {-4,10,10}, //0
    {-4,10,0}, //1
    {-4,0,0}, //2
    {-4,0,10}, //3

    {20,10,0}, //4
    {20,0,0}, //5
    {20,10,10}, //6
    {20,0,10}, //7


};



static GLubyte florindices[4][4] =
{
    {0,1,2,3},
    {1,4,5,2},
    {4,6,7,5},
    {5,7,3,2}
};



static GLfloat colors[10][3] =
{
    //polygon colors
    {1.0, 1.0, 1.0},
    {0.5, 0.5, 0.5},
    //quad er shuru ekhan theke
    {0.5f, 0.0f, 1.0f}, //purple
    {1.0f, 0.0f, 0.0f}, //red
    {0.0f, 1.0f, 0.0f}, //green
    {1.0f, 1.0f, 0.0f}, //yellow
    {0.0, 0.0, 1.0}, //blue
    {1.0, 0.5, 0.0}, //idk what color
    {0.002, 0.6, 0.98}, // bluish hue
    {0.4, 0.2, 0.0} //brown
};



void drawWall(GLfloat r=0.4,GLfloat g=0,GLfloat b=.8,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    for (GLint i = 0; i <4; i++)
    {
        glBegin(GL_QUADS);

        //if(i!=3 && i!=1) glColor3f(colors[8][0],colors[8][1],colors[8][2]);
        //else if(i==3) glColor3f(colors[1][0],colors[1][1],colors[1][2]);
        //else glColor3f(colors[2][0],colors[2][1],colors[2][2]);

        glVertex3fv(&v_floor[florindices[i][0]][0]);
        glVertex3fv(&v_floor[florindices[i][1]][0]);
        glVertex3fv(&v_floor[florindices[i][2]][0]);
        glVertex3fv(&v_floor[florindices[i][3]][0]);

        glEnd();
    }
}


void drawCube(GLfloat r=1,GLfloat g=1,GLfloat b=1,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glVertex3fv(&v_cube[cubeIndices[i][0]][0]);
        glVertex3fv(&v_cube[cubeIndices[i][1]][0]);
        glVertex3fv(&v_cube[cubeIndices[i][2]][0]);
        glVertex3fv(&v_cube[cubeIndices[i][3]][0]);
        glEnd();
    }
}



void drawtable()
{
    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(-10,0,-10);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(10,0,-10);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(-10,0,10);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(10,0,10);
    drawCube();
    glPopMatrix();

//    glPushMatrix();
//    glScaled(4,0.1,2);
//    glTranslatef(-1,0,1);
//    drawcube(1,1,1);
//    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glScalef(1,0,1);
    glutSolidSphere( 5.0, 10.0, 15.0);
    glPopMatrix();

}


void chair(int r=0) {
    //legs left top
    glPushMatrix();
    //(1,1,1);
    glTranslatef(0,0,0);
    glScaled(0.2,1,0.2);
    drawCube(0.3,0.1,0);
    glPopMatrix();


    //legs left bottom
    glPushMatrix();
    //(1,1,1);
    glTranslatef(0,0,1);
    glScaled(0.2,1,0.2);
    drawCube(0.3,0.1,0);
    glPopMatrix();


    glPushMatrix();
    //(1,1,1);
    glTranslatef(1,0,0);
    glScaled(0.2,1,0.2);
    drawCube(0.3,0.1,0);
    glPopMatrix();


    glPushMatrix();
    //(1,1,1);
    glTranslatef(1,0,1);
    glScaled(0.2,1,0.2);
    drawCube(0.3,0.1,0);
    glPopMatrix();

    // seat
    glPushMatrix();
    //(1,1,1);
    if(!r) glTranslatef(0,1,0);
    else   glTranslatef(-.5,1,0);
    glScaled(1.8,0.02,1.2);
    drawCube(0.3,0.1,0);
    glPopMatrix();

    // backrest
    glPushMatrix();
    //(1,1,1);
    if(!r) glTranslatef(0,1,0);
    else   glTranslatef(1.2,1,0);
    glScaled(0.02,1.5,1.2);
    drawCube(0,0,0);
    glPopMatrix();

}



void drawFan(GLfloat r=0,GLfloat g=0,GLfloat b=0,GLboolean emission=false) {

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glPushMatrix();

    glTranslatef(0,0,0);
    glScalef(0.1,0.1,1);
    drawCube();


    glPopMatrix();



}




void ceiling_light_holder(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix();
    glTranslatef(3.48,8,4.48);
    //glRotatef(-90,1,0,0);
    glScalef(0.1,1,0.1);
    drawCube(1,1,1);
    glPopMatrix();
}





void ceiling_light(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);



    glPushMatrix();
    glTranslatef(3.5,8,4.5);
    glutSolidSphere(0.5,16,20);
    glPopMatrix();
}







void light(double x,double y,double z,bool lighton,GLenum Lights,bool spot,bool strip)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat strip_light_diffuse[]  = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat strip_light_specular[] = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(Lights);
    if(lighton)
    {
        if(strip)
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, strip_light_diffuse);
            glLightfv( Lights, GL_SPECULAR, strip_light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }

        else
        {
            glLightfv( Lights, GL_AMBIENT, light_ambient);
            glLightfv( Lights, GL_DIFFUSE, light_diffuse);
            glLightfv( Lights, GL_SPECULAR, light_specular);
            glLightfv( Lights, GL_POSITION, light_position);
        }



    }
    else
    {
        glLightfv( Lights, GL_AMBIENT, no_light);
        glLightfv( Lights, GL_DIFFUSE, no_light);
        glLightfv( Lights, GL_SPECULAR, no_light);
        glLightfv( Lights, GL_POSITION, no_light);
    }






    //to know the position of strip light
    /*glPushMatrix();
    glTranslatef(10,8.5,4.5);
    glutSolidCube(1);
    glPopMatrix();*/


    if(spot)
    {
        GLfloat spot_direction[] = { 0, -1, 0 };
        glLightfv(Lights, GL_SPOT_DIRECTION, spot_direction);
        glLightf(Lights, GL_SPOT_CUTOFF, 55.0);
    }


}










void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 4, 100);
     //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);
    glViewport(0, 0, windowHeight, windowWidth);

    //glRotatef(45, 0, 0, 1 );
    // triangle();

    glRotatef(120,0,1,0);
//     glScalef(1,5,1);
    glTranslatef(0,-10,0);


    glScalef(scale_x,scale_y,scale_z);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawWall();


    // tiles outline
    //(.8,.7,.2);
    glPushMatrix();
    glTranslatef(-4,0,0);
    //glRotatef(22, 0,0,1);
    glScalef(13, 0.002, 10);
    drawCube(.8,.7,.2);
    glPopMatrix();
    //tiles
    int start_point=-1;
    for(int k=9;k<20;k++){

        start_point = (start_point+1)%2;

        for (int i=0;i<10;i+=2){
            //(.8,.7,.2);
            glPushMatrix();

            glTranslatef(k,0,i+start_point);
            //glRotatef(22, 0,0,1);
            glScalef(1, 0.002, 1);
            drawCube(.8,.7,.2);
            glPopMatrix();
        }

    }


    {
    // right sofa
    //(1,1,1);
    glPushMatrix();
    glTranslatef(6,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(2, 1, 5);
    drawCube(.6,.7,.7);
    glPopMatrix();

    // right top sofa
    //(0,0,0);
    glPushMatrix();
    glTranslatef(7.5,1,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 5);
    drawCube(.7,0,.3);
    glPopMatrix();



    // top sofa
    //(1,1,1);
    glPushMatrix();
    glTranslatef(2,0,1);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube(.6,.7,.7);
    glPopMatrix();

    // top top sofa
    //(0,0,0);
    glPushMatrix();
    glTranslatef(2,1,1);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 0.5);
    drawCube(.7,0,.3);
    glPopMatrix();

    // table
    //(0.4,0.2,0);
    glPushMatrix();
    glTranslatef(2,0,3.5);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube(0.4,0.2,0);
    glPopMatrix();

    // LEFT sofa
    //(1,1,1);
    glPushMatrix();
    glTranslatef(-1,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(2, 1, 5);
    drawCube(.6,.7,.7);
    glPopMatrix();

    // left top sofa
    //(0,0,0);
    glPushMatrix();
    glTranslatef(-1,1,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 5);
    drawCube(.7,0,.3);
    glPopMatrix();

    // bottom sofa
    //(1,1,1);
    glPushMatrix();
    glTranslatef(2,0,6);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube(.6,.7,.7);
    glPopMatrix();

    // bottom top sofa
    //(0,0,0);
    glPushMatrix();
    glTranslatef(2,1,7.5);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 0.5);
    drawCube(.7,0,.3);
    glPopMatrix();

    // door right
    //(0.6,0.3,0.0);
    glPushMatrix();
    glTranslatef(-4,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.25, 6, 2.95);
    drawCube(.3,0,.2);
    glPopMatrix();

    // door handle right
    //(1,1,1);
    glPushMatrix();
    glTranslatef(-4,2.5,4.70);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 0.2);
    drawCube();
    glPopMatrix();

    // door left
    //(0.6,0.3,0.0);
    glPushMatrix();
    glTranslatef(-4,0,5.05);
    //glRotatef(22, 0,0,1);
    glScalef(0.25, 6, 2.95);
    drawCube(.3,0,.2);
    glPopMatrix();

    // door handle left
    //(1,1,1);
    glPushMatrix();
    glTranslatef(-4,2.5,5.10);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 0.2);
    drawCube();
    glPopMatrix();

    }

    //-------------------------------------

    {

    // table
    //(1,1,1);
    glPushMatrix();
    glTranslatef(13.85,0,6);
    //glRotatef(22, 0,0,1);
    glScalef(0.50, 1.5, 0.50);
    drawCube();
    glPopMatrix();



    // table top
    //(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(12,1.5,4);
    //glRotatef(22, 0,0,1);
    glScalef(4,0.1,5);
    drawCube();
    glPopMatrix();


    // left top chair
    glPushMatrix();
    glTranslatef(11,0,4.5);
    chair();
    glPopMatrix();

    // left bottom chair
    glPushMatrix();
    glTranslatef(11,0,7.5);
    chair();
    glPopMatrix();


    /*
    // right top chair
    glPushMatrix();
    //glRotatef(180,0,1,0);
    glTranslatef(15.5,0,4.5);
    glRotatef(180,0,1,0);
    chair();

    glPopMatrix();
    */

    // right top chair
    glPushMatrix();
    glTranslatef(15.5,0,4.5);
    chair(1);
    glPopMatrix();


    // right bottom chair
    glPushMatrix();
    glTranslatef(15.5,0,7.5);
    //glTranslatef(-10,0,7.5);
    chair(1);
    glPopMatrix();





    // cupboards
    //(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(16,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(4,2,1);
    drawCube(0.6,0.2,0);
    glPopMatrix();

    // cupboards
    //(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(19,0,3);
    //glRotatef(22, 0,0,1);
    glScalef(1,2,5);
    drawCube(0.6,0.2,0);
    glPopMatrix();

    // cupboards DOOR TOP
    //(1.0, 0, 0);
    glPushMatrix();
    glTranslatef(18.95,0.2,3.2);
    //glRotatef(22, 0,0,1);
    glScalef(0.02,1.5,1);
    drawCube(.2,.1,.2);
    glPopMatrix();

    // cupboards DOOR MIDDLE
     //(1.0, 0, 0.0);
    glPushMatrix();
    glTranslatef(18.95,0.2,4.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.02,1.5,1);
    drawCube(.2,.1,.2);
    glPopMatrix();

    // cupboards DOOR BOTTOM
     //(1.0, 0, 0.0);
    glPushMatrix();
    glTranslatef(18.95,0.2,6.6);
    //glRotatef(22, 0,0,1);
    glScalef(0.02,1.5,1);
    drawCube(.2,.1,.2);
    glPopMatrix();

    }
    // =========================================
    // ceiling bar |
    glPushMatrix();
    glTranslatef(3.25,9,0);
    //glRotatef(22, 0,0,1);
    glScalef(.5,0.5,10);
    drawCube(0,0,0);
    glPopMatrix();


    // ceiling bar --
    glPushMatrix();
    glTranslatef(-4,9,4.25);
    //glRotatef(22, 0,0,1);
    glScalef(24,0.5,.5);
    drawCube(0,0,0);
    glPopMatrix();
     // =========================================


    // Fans ==================================
    glPushMatrix();

    // Fan holder
    glPushMatrix();
    glTranslatef(9.48,8,4.48);
    //glRotatef(-90,1,0,0);
    glScalef(0.1,1,0.1);
    drawCube(1,1,1);
    glPopMatrix();


    glTranslatef(9.5,7.80,4.4);
    glRotatef( gamma,0, 1, 0 );
    drawFan(1,1,1);
    glRotatef(90,0, 1, 0 );
    drawFan(1,1,1);
    glRotatef(90,0, 1, 0 );
    drawFan(1,1,1);
    glRotatef(90,0, 1, 0 );
    drawFan(1,1,1);




    glPopMatrix();


    // =======================================


    // lights =================================

    ceiling_light_holder(0.3,.3,.4);
    ceiling_light(0.85,0.85,0.85);


    glPushMatrix();
    glTranslatef(16,8.75,4.25);
    //glRotatef(22, 0,0,1);
    glScalef(3,0.25,.25);
    drawCube(1,1,1);
    glPopMatrix();

    // ========================================


    light(17.75,8.83,4.5,light0,GL_LIGHT0,false,false);
    light(3.5,8,4.5,light1,GL_LIGHT1,true,false);
    light(18,12,15,light2,GL_LIGHT2,false,true);

    glFlush();
    glutSwapBuffers();
}


double limit = 360;
double roll_value = 0.2;
GLfloat angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0, angleRollLimit2 = -90.0;
int f=0;

int bv = 0;



void b_swap()
{
    if(bv==1)
    {
        int tmp = eyey;
        eyey = eyez;
        eyez = tmp;

        tmp = upy;
        upy = upz;
        upz = tmp;

    }
}

void init(int d)
{
    if(d!=f)
    {
        angleYaw = 90.0;
        anglePitch = 90.0;
        angleRoll = 90.0;
        eyex = 20;
        eyey = 6;
        eyez = -20;
        centerx = 2;
        centery = 0;
        centerz = 0;
        upx = 0;
        upy = 1;
        upz = 0;
        f=d;
        scale_x=1.5;
        scale_y=1.5;
        scale_z=1.5;
    }
    b_swap();
}

void setCameraEye_Yaw() // y axis , y u
{
    init(1);
    f=1;
    centery = 200.0*(cos(angleYaw*3.1416/180.0));
}

void setCameraEye_Roll() // z axis ,i o
{
    init(2);
    f=2;
    upx = 200.0*(cos(angleRoll*3.1416/180.0));//-sin(angleYaw*3.1416/180.0));
    upy = 200.0*(sin(angleRoll*3.1416/180.0));//+cos(angleYaw*3.1416/180.0));
}

void setCameraEye_Pitch() // x axis , r t
{
    init(3);
    f=3;

    centerx = 400.0*(cos(anglePitch*3.1416/180.0));
}





void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'r':
        if(anglePitch>=anglePitchLimit1)
                break;
        anglePitch += roll_value;

        //printf("%lf  p\n ", anglePitch);
        //if(anglePitch > limit)
        //    anglePitch -= limit;
        setCameraEye_Pitch();
        glutPostRedisplay();

        // eyex = eyex;

        break;
    case 't':
        if(anglePitch==anglePitchLimit2)
                break;
        anglePitch -= roll_value;
        //if(anglePitch < 0)
         //   anglePitch += limit;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'y':
        if(angleYaw==angleYawLimit1)
            break;
        angleYaw += roll_value;
        //if(angleYaw > limit)
        //    angleYaw -= limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'u':
        if(angleYaw==angleYawLimit2)
            break;
        angleYaw -= roll_value;
        //if(angleYaw < 0)
         //   angleYaw += limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'i':
        //if(angleRoll>=angleRollLimit1)
         //   break;
        angleRoll += roll_value;
        //if(angleRoll >= limit)
        //    angleRoll -= limit;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        //if(angleRoll<=angleRollLimit2)
         //   break;
        angleRoll -= roll_value;
        //if(angleRoll < 0)
        //    angleRoll += limit;
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;


    case '@':
       bRotate = !bRotate;
              // uRotate = false;
        axis_x=0.0;
        axis_y=1.0;

        break;


   case '#':
        uRotate = !uRotate;/**<  */
        bRotate = false;
       axis_x=1.0;
        axis_y=0.0;

       break;

    case 'z':
        //eyez-=2;
        //init(4);
        f=4;
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
        //eyez-=2;
        //init(4);
        f=4;
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;

    //switch for light0
    case '0':
        light0 = !light0;
        glutPostRedisplay();
        break;
    case '1':
        light1 = !light1;
        glutPostRedisplay();
        break;
    case '2':
        light2 = !light2;
        glutPostRedisplay();
        break;

    case '4':
        fan4 = !fan4;
        glutPostRedisplay();
        break;

    case 27:	// Escape key
        exit(1);
    }
}

/*
r, t => pitch
y, u => Yaw
i, o => roll
c, z => scaling

*/



void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (fan4 == true )
    {
        gamma += 1;
        if(gamma > 360.0);
            gamma -= 360.0 * floor(gamma/360.0);
    }

    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glEnable( GL_LIGHTING );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
