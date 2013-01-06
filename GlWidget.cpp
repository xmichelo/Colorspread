/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of OpenGL Widget


#include "stdafx.h"
#include "GlWidget.h"
#include "GameBoard.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget
//**********************************************************************************************************************
GlWidget::GlWidget(QWidget* parent)
   : QGLWidget(QGLFormat(QGL::AlphaChannel | QGL::DoubleBuffer | QGL::Rgba), parent)
{
   this->setAutoBufferSwap(false);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GlWidget::~GlWidget()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::initializeGL()
{
   qDebug("InitializeGL()");
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::paintGL()
{
   GameBoard const& gameBoard(GameBoard::instance());
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glBegin(GL_QUADS);
   for (int i = 0; i < kBoardSize; ++i)
      for (int j = 0; j < kBoardSize; ++j)
      {
         QColor const color(kColors[gameBoard.getColorAt(i, j)]);
         glColor3f(color.redF(), color.greenF(), color.blueF());
         glVertex2i(i       * kCellRenderSize, j       * kCellRenderSize);
         glVertex2i((i + 1) * kCellRenderSize, j       * kCellRenderSize);
         glVertex2i((i + 1) * kCellRenderSize, (j + 1) * kCellRenderSize);
         glVertex2i(i       * kCellRenderSize, (j + 1) * kCellRenderSize);
      }
   glEnd();
   this->swapBuffers();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::resizeGL(int width, int height)
{
   qDebug("resizeGL()");
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, width, height, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}
