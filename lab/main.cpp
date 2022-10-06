#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

static GLfloat v_pyramid[12][3] =
{
    {0.0, 2.0, 0.0}, //0
    {-2.0, 1.0, 0.0}, //1
    {-2.0, -1.0, 0.0}, //2
    {0.0, -2.0, 0.0}, //3
    {2.0, -1.0, 0.0}, //4
    {2.0, 1.0, 0.0}, //5

    {0.0, 2.0, -5.0}, //6
    {-2.0, 1.0, -5.0}, //7
    {-2.0, -1.0, -5.0}, //8
    {0.0, -2.0, -5.0}, //9
    {2.0, -1.0, -5.0}, //10
    {2.0, 1.0, -5.0} //11
};

static GLubyte poly_Indices[2][6] =
{
    {0,1,2,3,4,5},
    {6,7,8,9,10,11}
};

static GLubyte quadIndices[6][4] =
{
    {0,6,7,1},
    {0,5,11,6},
    {1,7,8,2},

    {5,4,10,11},
    {2,3,9,8},
    {4,3,9,10}
};

static GLfloat colors[8][3] =
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
    {1.0, 0.5, 0.0} //idk what color
};

void drawpyramid()
{
    //glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for (GLint i = 0; i <2; i++)
    {
        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&v_pyramid[poly_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][2]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][3]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][4]][0]);
        glVertex3fv(&v_pyramid[poly_Indices[i][5]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glColor3f(colors[i+2][0],colors[i+2][1],colors[i+2][2]);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);

    }
    glEnd();


}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 4, 50);
     //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(2,3,10, 2,0,0, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);

    // glRotatef(45, 0, 0, 1 );
    // triangle();

    glRotatef(45,0,2,0);
    //glScalef(1,5,1);
    glTranslatef(5,10,0);

     drawpyramid();
//     glTranslatef(5,0,0);
//
//     drawpyramid();
//     glTranslatef(2,2,2);
     //drawpyramid();
 /*
    glPushMatrix();
    glTranslatef(0,0,Tzval);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    drawpyramid();
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

    case 27:	// Escape key
        exit(1);
    }
}



void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
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

