/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of OpenGL Widget


#ifndef COLORSPREAD__GL__WIDGET__H
#define COLORSPREAD__GL__WIDGET__H


//**********************************************************************************************************************
/// \brief Implementation of custom OpenGL widget
//**********************************************************************************************************************
class GlWidget: public QGLWidget
{
public: // member functions
   GlWidget(QWidget* parent); ///< Default constructor
   ~GlWidget(); ///< Destructor

private: // member functions
   GlWidget(GlWidget const&); ///< Disabled copy-constructor
   GlWidget& operator=(GlWidget const&); ///< Disabled assignment operator
   void initializeGL(); ///< Initialize the OpenGL system
   void paintGL();  ///< OpenGL redraw callback
   void resizeGL(int width, int height); /// OpenGL resize callback
};


#endif // #ifndef COLORSPREAD__GL__WIDGET__H
