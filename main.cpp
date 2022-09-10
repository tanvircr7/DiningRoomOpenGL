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



static GLfloat colors[9][3] =
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
    {0.002, 0.6, 0.98} // bluish hue
};



void drawWall()
{
    for (GLint i = 0; i <4; i++)
    {
        glBegin(GL_QUADS);

        if(i!=3) glColor3f(colors[8][0],colors[8][1],colors[8][2]);
        else glColor3f(colors[1][0],colors[1][1],colors[1][2]);

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


/*

void drawwindow()
{
    //glColor3f(1,0,0);




    for (GLint i = 0; i <1; i++)
    {glBegin(GL_QUADS);
        glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_window[winindices[i][0]][0]);
        glVertex3fv(&v_window[winindices[i][1]][0]);
        glVertex3fv(&v_window[winindices[i][2]][0]);
        glVertex3fv(&v_window[winindices[i][3]][0]);

        glEnd();

    }


}
void drawcube(int i)
{
    //glColor3f(1,0,0);


    if(i==1)
    {
        for (GLint i = 0; i <6; i++)
        {glBegin(GL_QUADS);
            glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
            glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
            glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
            glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
            glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);

            glEnd();

        }
    }
    else if(i==2)
    {
        for (GLint i = 0; i <6; i++)
        {glBegin(GL_QUADS);
            glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
            glVertex3fv(&v_sink[sinkindices[i][0]][0]);
            glVertex3fv(&v_sink[sinkindices[i][1]][0]);
            glVertex3fv(&v_sink[sinkindices[i][2]][0]);
            glVertex3fv(&v_sink[sinkindices[i][3]][0]);

            glEnd();

        }
    }

}
*/

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 4, 100);
     //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(20,6,-20, 2,0,0, 0,1,0);
    glViewport(0, 0, windowHeight, windowWidth);

    //glRotatef(45, 0, 0, 1 );
    // triangle();

    glRotatef(120,0,1,0);
//     glScalef(1,5,1);
    glTranslatef(0,-10,0);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    drawWall();

    drawCube();

/*
    glPushMatrix();
    drawwindow();
    glRotatef(90,-1,0,0);
    glTranslatef(0,-16,0);
    drawwindow();
    glRotatef(90,-1,0,0);
    glTranslatef(0,-16,0);
    drawwindow();
    glRotatef(90,-1,0,0);
    glTranslatef(0,-16,0);
    drawwindow();
    glPopMatrix();


    glTranslatef(0,0,12);
    glPushMatrix();
    glScalef(1,1,.668);
    glTranslatef(0,10,2);
    drawcube(1);
    glTranslatef(4,0,0);
    drawcube(1);
    glTranslatef(4,0,0);
    drawcube(1);
    glPopMatrix();



    drawcube(1);
    glTranslatef(4,0,0);
    drawcube(1);
    //glScalef(.5,1,1);
    glTranslatef(4,0,0);
    drawcube(2);

    glPushMatrix();
    glTranslatef(0,0,3);
    drawcube(2);
    glPopMatrix();

    glTranslatef(4,0,0);
    drawcube(1);


    glTranslatef(-12,0,0);
    glRotatef(90,0,1,0);
    drawcube(1);
    glTranslatef(4,0,0);
    drawcube(1);
    glTranslatef(4,0,0);
    drawcube(1);
*/

//     glTranslatef(5,0,0);
//
//     drawWall();
//     glTranslatef(2,2,2);
     //drawWall();
 /*
    glPushMatrix();
    glTranslatef(0,0,Tzval);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    drawWall();
    glPopMatrix();
*/
   /*
     glPushMatrix();
        glTranslatef(0,0,Tzval);
        glScalef(3,3,3);
        glutSolidCube(1);
    glPopMatrix();
  */
    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:  // Escape key
        exit(1);
    }


}


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
