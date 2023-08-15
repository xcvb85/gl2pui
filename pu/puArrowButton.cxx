/*
     PLIB - A Suite of Portable Game Libraries
     Copyright (C) 1998,2002  Steve Baker

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Library General Public
     License as published by the Free Software Foundation; either
     version 2 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Library General Public License for more details.

     You should have received a copy of the GNU Library General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

     For further information visit http://plib.sourceforge.net

     $Id: puArrowButton.cxx 1568 2002-09-02 06:05:49Z sjbaker $
*/


#include "puLocal.h"
#include <GLES2/gl2.h>

UL_RTTI_DEF1(puArrowButton,puButton)


void puDrawArrowButtonTriangle ( int pos_x, int pos_y, int size_x, int size_y,
                                 puColour colour, int arrow_type, int active )
{
    /*
    If greyed out then halve the opacity when drawing
    the widget
    */
    glUseProgram(puShaderProgramSingleColor);
    GLint posAttrib = glGetAttribLocation(puShaderProgramSingleColor, "vPosition");
    GLint colorUniform = glGetUniformLocation(puShaderProgramSingleColor, "vColor");
    GLint strippleUniform = glGetUniformLocation(puShaderProgramSingleColor, "vStripple");
    GLint screenSizeUniform = glGetUniformLocation(puShaderProgramSingleColor, "screenSize");
    GLint count = 3;

    switch ( arrow_type )
    {
        case PUARROW_UP :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y - size_y/4,
                pos_x           , pos_y + size_y/4,
                pos_x + size_x/4, pos_y - size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            break;
        }

        case PUARROW_DOWN :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y + size_y/4,
                pos_x           , pos_y - size_y/4,
                pos_x + size_x/4, pos_y + size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            break;
        }

        case PUARROW_FASTUP :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y - size_y/4,
                pos_x           , pos_y,
                pos_x + size_x/4, pos_y - size_y/4,
                pos_x - size_x/4, pos_y,
                pos_x           , pos_y + size_y/4,
                pos_x + size_x/4, pos_y
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            count = 6;
            break;
        }

        case PUARROW_FASTDOWN :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y + size_y/4,
                pos_x           , pos_y,
                pos_x + size_x/4, pos_y + size_y/4,
                pos_x - size_x/4, pos_y,
                pos_x           , pos_y - size_y/4,
                pos_x + size_x/4, pos_y
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            count = 6;
            break;
        }

        case PUARROW_LEFT :
        {
            GLint verticesArrow[] = {
                pos_x + size_x/4, pos_y - size_y/4,
                pos_x - size_x/4, pos_y,
                pos_x + size_x/4, pos_y + size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            break;
        }

        case PUARROW_RIGHT :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y - size_y/4,
                pos_x + size_x/4, pos_y,
                pos_x - size_x/4, pos_y + size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            break;
        }

        case PUARROW_FASTLEFT :
        {
            GLint verticesArrow[] = {
                pos_x + size_x/4, pos_y - size_y/4,
                pos_x           , pos_y,
                pos_x + size_x/4, pos_y + size_y/4,
                pos_x           , pos_y - size_y/4,
                pos_x - size_x/4, pos_y,
                pos_x           , pos_y + size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            count = 6;
            break;
        }

        case PUARROW_FASTRIGHT :
        {
            GLint verticesArrow[] = {
                pos_x - size_x/4, pos_y - size_y/4,
                pos_x           , pos_y,
                pos_x - size_x/4, pos_y + size_y/4,
                pos_x           , pos_y - size_y/4,
                pos_x + size_x/4, pos_y,
                pos_x           , pos_y + size_y/4
            };
            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesArrow);
            count = 6;
            break;
        }

        default :
            ulSetError ( UL_WARNING, "PUI: Unrecognised 'arrow_type' %d", arrow_type ) ;
            break;
    }
    glEnableVertexAttribArray(posAttrib);
    glUniform4f(colorUniform, colour [0], colour [1], colour [2], active?colour[3]:0.5*colour[3]);
    glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
    glUniform1f(strippleUniform, 0);
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void puArrowButton::draw ( int dx, int dy )
{
    if ( !visible || ( window != puGetWindow () ) ) return ;

    /*
    If arrow button is pushed or highlighted -
    use inverse style for button itself
    */

    if ( getIntegerValue() ^ highlighted )
    {
        if ( parent && ( ( parent->getType() & PUCLASS_POPUPMENU ) ||
                         ( parent->getType() & PUCLASS_MENUBAR   ) ) )
            abox.draw ( dx, dy, PUSTYLE_SMALL_SHADED, colour, isReturnDefault(), 2 ) ;
        else
            abox.draw ( dx, dy, -style, colour, isReturnDefault(), border_thickness ) ;
    }
    else
        abox.draw ( dx, dy, style, colour, isReturnDefault(), border_thickness ) ;

    if ( r_cb )
        r_cb ( this, dx, dy, render_data ) ;
    else
    {
        int size_x = abox.max[0] - abox.min[0] ;
        int size_y = abox.max[1] - abox.min[1] ;

        int pos_x = dx + ( abox.max[0] + abox.min[0] ) / 2 ;
        int pos_y = dy + ( abox.max[1] + abox.min[1] ) / 2 ;

        puDrawArrowButtonTriangle ( pos_x, pos_y, size_x, size_y, colour [ PUCOL_MISC ], arrow_type, active ) ;
    }

    draw_label ( dx, dy ) ;
}
