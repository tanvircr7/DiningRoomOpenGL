#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1200, windowWidth=1400;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
GLdouble eyex=20, eyey=6,eyez=-20,centerx=2,centery=0,centerz=0, upx=0,upy=1,upz=0;
// original -> 20,6,-20, 2,0,0, 0,1,0
double scale_x = 1;
double scale_y = 1;
double scale_z = 1;

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



void drawWall()
{
    for (GLint i = 0; i <4; i++)
    {
        glBegin(GL_QUADS);

        if(i!=3 && i!=1) glColor3f(colors[8][0],colors[8][1],colors[8][2]);
        else if(i==3) glColor3f(colors[1][0],colors[1][1],colors[1][2]);
        else glColor3f(colors[2][0],colors[2][1],colors[2][2]);

        glVertex3fv(&v_floor[florindices[i][0]][0]);
        glVertex3fv(&v_floor[florindices[i][1]][0]);
        glVertex3fv(&v_floor[florindices[i][2]][0]);
        glVertex3fv(&v_floor[florindices[i][3]][0]);

        glEnd();
    }
}


void drawCube()
{
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




    // right sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(6,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(2, 1, 5);
    drawCube();
    glPopMatrix();

    // right top sofa
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(7.5,1,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 5);
    drawCube();
    glPopMatrix();



    // top sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(2,0,1);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube();
    glPopMatrix();

    // top top sofa
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(2,1,1);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 0.5);
    drawCube();
    glPopMatrix();

    // table
    glColor3f(0.4,0.2,0);
    glPushMatrix();
    glTranslatef(2,0,3.5);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube();
    glPopMatrix();

    // LEFT sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-1,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(2, 1, 5);
    drawCube();
    glPopMatrix();

    // left top sofa
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(-1,1,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 5);
    drawCube();
    glPopMatrix();

    // bottom sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(2,0,6);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 2);
    drawCube();
    glPopMatrix();

    // bottom top sofa
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(2,1,7.5);
    //glRotatef(22, 0,0,1);
    glScalef(3, 1, 0.5);
    drawCube();
    glPopMatrix();

    // door right
    glColor3f(0.6,0.3,0.0);
    glPushMatrix();
    glTranslatef(-4,0,2);
    //glRotatef(22, 0,0,1);
    glScalef(0.25, 6, 2.95);
    drawCube();
    glPopMatrix();

    // door handle right
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-4,2.5,4.70);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 0.2);
    drawCube();
    glPopMatrix();

    // door left
    glColor3f(0.6,0.3,0.0);
    glPushMatrix();
    glTranslatef(-4,0,5.05);
    //glRotatef(22, 0,0,1);
    glScalef(0.25, 6, 2.95);
    drawCube();
    glPopMatrix();

    // door handle left
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-4,2.5,5.10);
    //glRotatef(22, 0,0,1);
    glScalef(0.5, 1, 0.2);
    drawCube();
    glPopMatrix();

/*

    // table
    glPushMatrix();
    glTranslatef(11,2.5,2);
    glRotatef(180,1,0,0);
    drawtable();
    glPopMatrix();

*/
    // LEFT sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(10.95,0,4.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.10, 1, 0.10);
    drawCube();
    glPopMatrix();


    // LEFT sofa TOP
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(10.5,1,4);
    //glRotatef(22, 0,0,1);
    glScalef(1, 0.1, 1);
    drawCube();
    glPopMatrix();


    // left below sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(10.95,0,8.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.10, 1, 0.10);
    drawCube();
    glPopMatrix();


    // left below sofa TOP
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(10.5,1,8);
    //glRotatef(22, 0,0,1);
    glScalef(1, 0.1, 1);
    drawCube();
    glPopMatrix();

    //------------------------------------

    // RIght sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(16.95,0,4.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.10, 1, 0.10);
    drawCube();
    glPopMatrix();


    // right sofa TOP
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(16.5,1,4);
    //glRotatef(22, 0,0,1);
    glScalef(1, 0.1, 1);
    drawCube();
    glPopMatrix();


    // right below sofa
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(16.95,0,8.5);
    //glRotatef(22, 0,0,1);
    glScalef(0.10, 1, 0.10);
    drawCube();
    glPopMatrix();


    // right below sofa TOP
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(16.5,1,8);
    //glRotatef(22, 0,0,1);
    glScalef(1, 0.1, 1);
    drawCube();
    glPopMatrix();


    // table
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(13.85,0,6);
    //glRotatef(22, 0,0,1);
    glScalef(0.50, 1, 0.50);
    drawCube();
    glPopMatrix();



    // table top
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(12,1,4);
    //glRotatef(22, 0,0,1);
    glScalef(4,0.1,5);
    drawCube();
    glPopMatrix();


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
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
