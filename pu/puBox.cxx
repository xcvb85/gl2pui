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

     $Id: puBox.cxx 1943 2004-08-05 01:05:48Z puggles $
*/

#include "puLocal.h"
#include <GLES2/gl2.h>

#define PU_DFLT_OFFSET        5

void puBox::extend ( puBox *bx )
{
    if ( bx -> isEmpty () ) return ;

    if ( min[0]>bx->min[0] ) min[0] = bx->min[0] ;
    if ( min[1]>bx->min[1] ) min[1] = bx->min[1] ;
    if ( max[0]<bx->max[0] ) max[0] = bx->max[0] ;
    if ( max[1]<bx->max[1] ) max[1] = bx->max[1] ;
}

void puBox::draw ( int dx, int dy, int style, puColour colour[], int am_default, int border )
{
    int mid = PUCOL_FOREGROUND ;
    int hi  = PUCOL_HIGHLIGHT  ;
    int lo  = PUCOL_BACKGROUND ;

    /* Colour assignments */

    switch ( style )
    {
        case  PUSTYLE_NONE       :
            return ;

        case  PUSTYLE_SMALL_SHADED :
        case  PUSTYLE_SHADED     :
        case  PUSTYLE_SMALL_BEVELLED :
        case  PUSTYLE_BEVELLED   :
        case  PUSTYLE_BOXED      :
            mid = PUCOL_FOREGROUND ;
            hi  = PUCOL_HIGHLIGHT  ;
            lo  = PUCOL_BACKGROUND ;
            break ;

        case -PUSTYLE_SMALL_BEVELLED :
        case -PUSTYLE_BEVELLED   :
        case -PUSTYLE_SMALL_SHADED :
        case -PUSTYLE_SHADED     :
        case -PUSTYLE_BOXED      :
            mid = PUCOL_FOREGROUND ;
            hi  = PUCOL_BACKGROUND ;
            lo  = PUCOL_HIGHLIGHT  ;
            break ;

        default :
            ulSetError ( UL_WARNING, "PUI: Unrecognised 'style' %d", style ) ;
            return ;
    }

    switch ( abs(style) )
    {
        case  PUSTYLE_SMALL_BEVELLED   :
        case  PUSTYLE_SMALL_SHADED     :
        case  PUSTYLE_BEVELLED         :
        case  PUSTYLE_SHADED           :
        {
            glUseProgram(puShaderProgramSingleColor);
            GLint posAttrib = glGetAttribLocation(puShaderProgramSingleColor, "vPosition");
            GLint colorUniform = glGetUniformLocation(puShaderProgramSingleColor, "vColor");
            GLint strippleUniform = glGetUniformLocation(puShaderProgramSingleColor, "vStripple");
            GLint screenSizeUniform = glGetUniformLocation(puShaderProgramSingleColor, "screenSize");

            GLint verticesBorder1[] = {
                dx + min[0] + border,  dy + min[1] + border,
                dx + min[0], dy + min[1],
                dx + min[0] + border,  dy + max[1] - border,
                dx + min[0], dy + max[1],
                dx + max[0] - border,  dy + max[1] - border,
                dx + max[0], dy + max[1],
            };

            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorder1);
            glEnableVertexAttribArray(posAttrib);
            glUniform4f(colorUniform, colour[hi][0], colour[hi][1], colour[hi][2], colour[hi][3]);
            glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
            glUniform1f(strippleUniform, 0);
            glDrawArrays(GL_QUAD_STRIP, 0, 6);

            GLint verticesBorder2[] = {
                dx + min[0], dy + min[1],
                dx + min[0] + border, dy + min[1] + border,
                dx + max[0], dy + min[1],
                dx + max[0] - border, dy + min[1] + border,
                dx + max[0], dy + max[1],
                dx + max[0] - border, dy + max[1] - border
            };

            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorder2);
            glEnableVertexAttribArray(posAttrib);
            glUniform4f(colorUniform, colour[lo][0], colour[lo][1], colour[lo][2], colour[lo][3]);
            glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
            glDrawArrays(GL_QUAD_STRIP, 0, 6);

            if ( ( style == -PUSTYLE_SMALL_SHADED ) ||
                 ( style == -PUSTYLE_SHADED ) )
            {
                GLint verticesBorderPressed1[] = {
                    dx + min[0] + border   , dy + min[1] + border,
                    dx + min[0] + border/2 , dy + min[1] + border/2,
                    dx + min[0] + border   , dy + max[1] - border,
                    dx + min[0] + border/2 , dy + max[1] - border/2,
                    dx + max[0] - border   , dy + max[1] - border,
                    dx + max[0] - border/2 , dy + max[1] - border/2
                };

                glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorderPressed1);
                glEnableVertexAttribArray(posAttrib);
                glUniform4f(colorUniform, colour[lo][0], colour[lo][1], colour[lo][2], colour[lo][3]);
                glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
                glDrawArrays(GL_QUAD_STRIP, 0, 6);

                GLint verticesBorderPressed2[] = {
                    dx + min[0] + border/2 , dy + min[1] + border/2,
                    dx + min[0] + border   , dy + min[1] + border,
                    dx + max[0] - border/2 , dy + min[1] + border/2,
                    dx + max[0] - border   , dy + min[1] + border,
                    dx + max[0] - border/2 , dy + max[1] - border/2,
                    dx + max[0] - border   , dy + max[1] - border
                };

                glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorderPressed2);
                glEnableVertexAttribArray(posAttrib);
                glUniform4f(colorUniform, colour[hi][0], colour[hi][1], colour[hi][2], colour[hi][3]);
                glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
                glDrawArrays(GL_QUAD_STRIP, 0, 6);
            }

            glUseProgram(puShaderProgramMultipleColors);
            posAttrib = glGetAttribLocation(puShaderProgramMultipleColors, "vPosition");
            GLint colorAttrib = glGetAttribLocation(puShaderProgramMultipleColors, "vColor");
            screenSizeUniform = glGetUniformLocation(puShaderProgramMultipleColors, "screenSize");

            GLfloat verticesBackground[] = {
                GLfloat(dx + min[0] + border), GLfloat(dy + min[1] + border),   colour [mid][0], colour [mid][1], colour [mid][2], colour [mid][3],
                GLfloat(dx + min[0] + border), GLfloat(dy + max[1] - border),   colour [mid][0] + (colour[lo][0] - colour[mid][0])/2.0f,
                                                                                colour [mid][1] + (colour[lo][1] - colour[mid][1])/2.0f,
                                                                                colour [mid][2] + (colour[lo][2] - colour[mid][2])/2.0f,
                                                                                colour [lo][3],
                GLfloat(dx + max[0] - border), GLfloat(dy + max[1] - border),   colour [mid][0], colour [mid][1], colour [mid][2], colour [mid][3],
                GLfloat(dx + max[0] - border), GLfloat(dy + min[1] + border),   colour [mid][0] + (colour[lo][0] - colour[mid][0])/2.0f,
                                                                                colour [mid][1] + (colour[lo][1] - colour[mid][1])/2.0f,
                                                                                colour [mid][2] + (colour[lo][2] - colour[mid][2])/2.0f,
                                                                                colour [lo][3]
            };

            glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), verticesBackground);
            glEnableVertexAttribArray(posAttrib);
            glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), &verticesBackground[2]);
            glEnableVertexAttribArray(colorAttrib);
            glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
            glDrawArrays(GL_POLYGON, 0, 4);
            glUseProgram(0);
            break ;
        }

        case  PUSTYLE_BOXED      :
        {
            glUseProgram(puShaderProgramSingleColor);
            GLint posAttrib = glGetAttribLocation(puShaderProgramSingleColor, "vPosition");
            GLint colorUniform = glGetUniformLocation(puShaderProgramSingleColor, "vColor");
            GLint strippleUniform = glGetUniformLocation(puShaderProgramSingleColor, "vStripple");
            GLint screenSizeUniform = glGetUniformLocation(puShaderProgramSingleColor, "screenSize");

            GLint verticesBorder1[] = {
                dx + min[0], dy + min[1],
                dx + min[0], dy + max[1],
                dx + max[0], dy + max[1],
                dx + max[0], dy + min[1]
            };

            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorder1);
            glEnableVertexAttribArray(posAttrib);
            glUniform4f(colorUniform, colour[hi][0], colour[hi][1], colour[hi][2], colour[hi][3]);
            glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
            glUniform1f(strippleUniform, 0);
            glDrawArrays(GL_QUADS, 0, 4);

            GLint verticesBorder2[] = {
                dx + min[0]+border, dy + min[1]+border,
                dx + min[0]+border, dy + max[1]-border,
                dx + max[0]-border, dy + max[1]-border,
                dx + max[0]-border, dy + min[1]+border
            };

            glVertexAttribPointer(posAttrib, 2, GL_INT, GL_FALSE, 0, verticesBorder2);
            glEnableVertexAttribArray(posAttrib);
            glUniform4f(colorUniform, colour[mid][0], colour[mid][1], colour[mid][2], colour[mid][3]);
            glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
            glUniform1f(strippleUniform, 0);
            glDrawArrays(GL_QUADS, 0, 4);
            glUseProgram(0);
            break ;
        }

        default:
            break;
    }

    if ( am_default )
    {
        glUseProgram(puShaderProgramSingleColor);
        GLint posAttrib = glGetAttribLocation(puShaderProgramSingleColor, "vPosition");
        GLint colorUniform = glGetUniformLocation(puShaderProgramSingleColor, "vColor");
        GLint strippleUniform = glGetUniformLocation(puShaderProgramSingleColor, "vStripple");
        GLint screenSizeUniform = glGetUniformLocation(puShaderProgramSingleColor, "screenSize");

        GLfloat verticesStripple[] = {
            dx + min[0] + PU_DFLT_OFFSET + 0.5f, dy + min[1] + PU_DFLT_OFFSET + 0.5f,
            dx + min[0] + PU_DFLT_OFFSET + 0.5f, dy + max[1] - PU_DFLT_OFFSET - 0.5f,
            dx + max[0] - PU_DFLT_OFFSET - 0.5f, dy + max[1] - PU_DFLT_OFFSET - 0.5f,
            dx + max[0] - PU_DFLT_OFFSET - 0.5f, dy + min[1] + PU_DFLT_OFFSET + 0.5f,
            dx + min[0] + PU_DFLT_OFFSET + 0.5f, dy + min[1] + PU_DFLT_OFFSET + 0.5f
        };

        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, verticesStripple);
        glEnableVertexAttribArray(posAttrib);
        glUniform4f(colorUniform, colour[PUCOL_BACKGROUND][0], colour[PUCOL_BACKGROUND][1], colour[PUCOL_BACKGROUND][2], colour[PUCOL_BACKGROUND][3]);
        glUniform2f(screenSizeUniform, puGetWindowWidth(), puGetWindowHeight());
        glUniform1f(strippleUniform, 10);
        glDrawArrays(GL_LINE_STRIP, 0, 5);
        glUseProgram(0);
    }
}
