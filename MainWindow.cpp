/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "MainWindow.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window creation flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui_.setupUi(this);
}


//**********************************************************************************************************************
///
//**********************************************************************************************************************
MainWindow::~MainWindow()
{

}

