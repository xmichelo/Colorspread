/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "SeedDialog.h"
#include "MainWindow.h"
#include "Utils.h"
#include "GameEngine.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window creation flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
    , statusLabel_(00)
{
   ui_.setupUi(this);
   this->setupColorButtons();
   this->setupStatusBar();
   GameEngine* board(&GameEngine::instance());
   connect(board, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
   connect(board, SIGNAL(turnPlayed()), this, SLOT(onGameStateChanged()));
   connect(board, SIGNAL(gameWon()), this, SLOT(onGameWon()));
   connect(board, SIGNAL(gameLost()), this, SLOT(onGameLost()));
   connect(board, SIGNAL(didUndo()), this, SLOT(updateGuiState()));
   connect(board, SIGNAL(didUndo()), this, SLOT(onGameStateChanged()));
   connect(board, SIGNAL(didRedo()), this, SLOT(updateGuiState()));
   connect(board, SIGNAL(didRedo()), this, SLOT(onGameStateChanged()));
   this->onNewRandomGame();
}


//**********************************************************************************************************************
///
//**********************************************************************************************************************
MainWindow::~MainWindow()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::setupColorButtons()
{
   QPushButton* buttons[eColorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < eColorCount; ++i)
   {
      QColor const color(kColors[i]);
      buttons[i]->setStyleSheet(QString("background-color: rgb(%1, %2, %3);\nborder: 1px solid rgb(50, 50, 50);")
                                .arg(color.red()).arg(color.green()).arg(color.blue()));
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::setupStatusBar()
{
   statusLabel_ = new QLabel("", ui_.statusBar);
   ui_.statusBar->addPermanentWidget(statusLabel_);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onColorButton()
{
   QPushButton* button(static_cast<QPushButton*>(this->sender()));
   if (!button) return;
   QPushButton* buttons[eColorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < eColorCount; ++i)
      if (button == buttons[i]) 
      { 
         GameEngine::instance().playColor(EColor(i)); 
         break; 
      }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStarted()
{
   ui_.gameStatusLabel->setText("");
   statusLabel_->setText(QString("Game Seed: %1").arg(uint32ToHexString(GameEngine::instance().getSeed())));
   ui_.turnsLeftCounterLabel->setText(QString::number(GameEngine::instance().getTurnsLeft()));
   ui_.glWidget->updateGL();
   this->updateGuiState();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStateChanged()
{
   ui_.turnsLeftCounterLabel->setText(QString::number(GameEngine::instance().getTurnsLeft()));
   ui_.glWidget->updateGL();
   this->updateGuiState();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameWon()
{
   ui_.gameStatusLabel->setStyleSheet("color: #61bc46;");
   ui_.gameStatusLabel->setText("You Win!");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameLost()
{
   ui_.gameStatusLabel->setStyleSheet("color: #cd2c24;");
   ui_.gameStatusLabel->setText("Game Over!");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onNewRandomGame()
{
   GameEngine::instance().newGame();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onRestartGame()
{
   GameEngine::instance().restartGame();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onNewGameWithSeed()
{
   SeedDialog dlg;
   if (QDialog::Accepted != dlg.exec())
      return;
   GameEngine::instance().newGame(dlg.getSeed());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionCopyGameSeed()
{
  QApplication::clipboard()->setText(uint32ToHexString(GameEngine::instance().getSeed()));
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionUndo()
{
   GameEngine::instance().undo();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionRedo()
{
   GameEngine::instance().redo();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::updateGuiState()
{
   GameEngine& gameEngine(GameEngine::instance());
   ui_.actionUndo->setEnabled(gameEngine.canUndo());
   ui_.actionRedo->setEnabled(gameEngine.canRedo());
   ui_.gameStatusLabel->setVisible(gameEngine.isGameFinished());
}

