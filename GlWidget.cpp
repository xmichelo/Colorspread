/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of OpenGL Widget


#include "stdafx.h"
#include "GlWidget.h"
#include "GameEngine.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget
//**********************************************************************************************************************
GlWidget::GlWidget(QWidget* parent)
   : QOpenGLWidget(parent)
{
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::initializeGL()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::paintGL()
{
   GameBoard const& gameBoard(GameEngine::instance().getGameBoard());
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glBegin(GL_QUADS);
   for (int i = 0; i < constants::kBoardSize; ++i)
      for (int j = 0; j < constants::kBoardSize; ++j)
      {
         QColor const color(constants::kColors[qint32(gameBoard.getCellColor(i, j))]);
         glColor3f(color.redF(), color.greenF(), color.blueF());
         glVertex2i(i      , j      );
         glVertex2i((i + 1), j      );
         glVertex2i((i + 1), (j + 1));
         glVertex2i(i      , (j + 1));
      }
   glEnd();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::resizeGL(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, constants::kBoardSize, constants::kBoardSize, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}
