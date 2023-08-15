#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <math.h>
#include <GL/glut.h>
#include <pu.h>

void motionfn ( int x, int y )
{
    puMouse ( x, y ) ;
    glutPostRedisplay () ;
}

void mousefn ( int button, int updown, int x, int y )
{
    puMouse ( button, updown, x, y ) ;
    glutPostRedisplay () ;
}

void displayfn ()
{
    glClearColor ( 0.1, 0.4, 0.1, 1.0 ) ;
    glClear      ( GL_COLOR_BUFFER_BIT ) ;

    puDisplay () ;

    glutSwapBuffers   () ;
    glutPostRedisplay () ;
}

void button_cb ( puObject * )
{
    fprintf ( stderr, "Hello World.\n" ) ;
}

int main ( int argc, char **argv )
{
    glutInitWindowSize  ( 240, 120 ) ;
    glutInit            ( &argc, argv ) ;
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;
    glutCreateWindow    ( "PUI Application"  ) ;
    glutDisplayFunc     ( displayfn ) ;
    glutMouseFunc       ( mousefn   ) ;
    glutMotionFunc      ( motionfn  ) ;

    puInit () ;

    puOneShot *b = new puOneShot ( 50, 50, 200, 80 ) ;

    b -> setLegend   ( "Say Hello" ) ;
    b -> setCallback ( button_cb ) ;

    glutMainLoop () ;

    return 0 ;
}

