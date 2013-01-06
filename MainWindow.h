/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Declaration of main window class


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
public: // member functions
   MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0); ///< Default constructor
   ~MainWindow(); ///< Destructor

private: // member functions
   void setupColorButtons(); ///< Setup the color buttons

private slots:
   void onColorButton(); ///< Callback for the color buttons
   void onGameStarted(); ///< Callback for the game started signal
   void onTurnPlayed(); ///< Callback for the turn played signal
   void onGameWon(); ///< Callback for the game won signal
   void onGameLost(); ///< Callback for the game lost signal
private: // data members
   Ui::MainWindowClass ui_; ///< The GUI for the window
};


#endif // COLORSPREAD__MAINWINDOW__H
