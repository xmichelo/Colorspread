/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#ifndef COLORSPREAD__MAINWINDOW__H
#define COLORSPREAD__MAINWINDOW__H


#include <QtGui/QMainWindow>
#include "ui_MainWindow.h"


//**********************************************************************************************************************
/// \brief The main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
   MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0); ///< Default constructor
   ~MainWindow(); ///< Destructor

private:
   Ui::MainWindowClass ui_; ///< The GUI for the window
};


#endif // COLORSPREAD__MAINWINDOW__H
