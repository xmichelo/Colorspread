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
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   ui_.setupUi(this);
   this->setupColorButtons();
   this->setupStatusBar();
   GameEngine* board(&GameEngine::instance());
   connect(board, &GameEngine::gameStarted, this, &MainWindow::onGameStarted);
   connect(board, &GameEngine::turnPlayed, this, &MainWindow::onGameStateChanged);
   connect(board, &GameEngine::gameWon, this, &MainWindow::onGameWon);
   connect(board, &GameEngine::gameLost, this, &MainWindow::onGameLost);
   connect(board, &GameEngine::didUndo, this, &MainWindow::updateGuiState);
   connect(board, &GameEngine::didUndo, this, &MainWindow::onGameStateChanged);
   connect(board, &GameEngine::didRedo, this, &MainWindow::updateGuiState);
   connect(board, &GameEngine::didRedo, this, &MainWindow::onGameStateChanged);
   this->onNewRandomGame();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::setupColorButtons() const
{
   qint32 const colorCount = qint32(EColor::ColorCount);
   QPushButton* buttons[colorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < colorCount; ++i)
   {
      QColor const color(constants::kColors[i]);
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
void MainWindow::onColorButton() const
{
   QPushButton* button(static_cast<QPushButton*>(this->sender()));
   if (!button) return;
   qint32 const colorCount = qint32(EColor::ColorCount);
   QPushButton* buttons[colorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button,
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < colorCount; ++i)
      if (button == buttons[i]) 
      { 
         GameEngine::instance().playColor(EColor(i)); 
         break; 
      }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStarted() const
{
   ui_.gameStatusLabel->setText("");
   statusLabel_->setText(QString("Game Seed: %1").arg(uint32ToHexString(GameEngine::instance().getSeed())));
   ui_.turnsLeftCounterLabel->setText(QString::number(GameEngine::instance().getTurnsLeft()));
   ui_.glWidget->update();
   this->updateGuiState();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStateChanged() const
{
   ui_.turnsLeftCounterLabel->setText(QString::number(GameEngine::instance().getTurnsLeft()));
   ui_.glWidget->update();
   this->updateGuiState();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameWon() const
{
   ui_.gameStatusLabel->setStyleSheet("color: #61bc46;");
   ui_.gameStatusLabel->setText("You Win!");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameLost() const
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
void MainWindow::updateGuiState() const
{
   GameEngine& gameEngine(GameEngine::instance());
   ui_.actionUndo->setEnabled(gameEngine.canUndo());
   ui_.actionRedo->setEnabled(gameEngine.canRedo());
   ui_.gameStatusLabel->setVisible(gameEngine.isGameFinished());
}

