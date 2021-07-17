/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Declaration of main window class


#ifndef COLORSPREAD_MAINWINDOW_H
#define COLORSPREAD_MAINWINDOW_H


#include "ui_MainWindow.h"


//**********************************************************************************************************************
/// \brief The main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT
public: // member functions
   explicit MainWindow(QWidget *parent = nullptr); ///< Default constructor
   ~MainWindow() override = default; ///< Destructor

private: // member functions
   void setupColorButtons() const; ///< Setup the color buttons
   void setupStatusBar(); /// Setup the status bar

private slots:
   void onColorButton() const; ///< Slot for the color buttons
   void onGameStarted() const; ///< Slot for the game started signal
   void onGameStateChanged() const; ///< Slot for the turn played signal
   void onGameWon() const; ///< Slot for the game won signal
   void onGameLost() const; ///< Slot for the game lost signal
    static void onNewRandomGame(); ///< Slot for the new random game action
    static void onNewGameWithSeed(); ///< Slot for the 'New Game With Seed' action
    static void onRestartGame(); ///< Slot for the restart game action
    static void onActionCopyGameSeed(); ///< Slot for the 'Copy Game Seed' action
    static void onActionUndo(); ///< Slot for the 'Undo' action
    static void onActionRedo(); ///< Slot for the 'Redo' action
   void updateGuiState() const; ///< Slot for the GUI state update

private: // data members
   Ui::MainWindowClass ui_; ///< The GUI for the window
   QLabel* statusLabel_ { nullptr }; ///< The permanent label in the status bar
};


#endif // COLORSPREAD_MAINWINDOW_H
