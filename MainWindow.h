/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Declaration of main window class


#ifndef COLORSPREAD__MAINWINDOW__H
#define COLORSPREAD__MAINWINDOW__H


#include "ui_MainWindow.h"


//**********************************************************************************************************************
/// \brief The main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT
public: // member functions
   MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0); ///< Default constructor
   ~MainWindow(); ///< Destructor

private: // member functions
   void setupColorButtons(); ///< Setup the color buttons
   void setupStatusBar(); /// Setup the status bar

private slots:
   void onColorButton(); ///< Slot for the color buttons
   void onGameStarted(); ///< Slot for the game started signal
   void onGameStateChanged(); ///< Slot for the turn played signal
   void onGameWon(); ///< Slot for the game won signal
   void onGameLost(); ///< Slot for the game lost signal
   void onNewRandomGame(); ///< Slot for the new random game action
   void onNewGameWithSeed(); ///< Slot for the 'New Game With Seed' action
   void onRestartGame(); ///< Slot for the restart game action
   void onActionCopyGameSeed(); ///< Slot for the 'Copy Game Seed' action
   void onActionUndo(); ///< Slot for the 'Undo' action
   void onActionRedo(); ///< Slot for the 'Redo' action
   void updateGuiState(); ///< Slot for the GUI state update

private: // data members
   Ui::MainWindowClass ui_; ///< The GUI for the window
   QLabel* statusLabel_; ///< The permanent label in the status bar
};


#endif // COLORSPREAD__MAINWINDOW__H
