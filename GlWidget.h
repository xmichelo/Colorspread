/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of OpenGL Widget


#ifndef COLORSPREAD_GL_WIDGET_H
#define COLORSPREAD_GL_WIDGET_H


#include <QOpenGLWidget>


//**********************************************************************************************************************
/// \brief Implementation of custom OpenGL widget
//**********************************************************************************************************************
class GlWidget: public QOpenGLWidget
{
public: // member functions
   explicit GlWidget(QWidget* parent); ///< Default constructor
   ~GlWidget() override = default; ///< Destructor

private: // member functions
   GlWidget(GlWidget const&) = delete; ///< Disabled copy-constructor
   GlWidget& operator=(GlWidget const&) = delete; ///< Disabled assignment operator
   void initializeGL() override; ///< Initialize the OpenGL system
   void paintGL() override;  ///< OpenGL redraw callback
   void resizeGL(int width, int height) override; /// OpenGL resize callback
};


#endif // #ifndef COLORSPREAD__GL__WIDGET__H
