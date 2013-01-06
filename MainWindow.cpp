/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "MainWindow.h"
#include "GameBoard.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window creation flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui_.setupUi(this);
   this->setupColorButtons();
   GameBoard* board(&GameBoard::instance());
   connect(board, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
   connect(board, SIGNAL(turnPlayed()), this, SLOT(onTurnPlayed()));
   connect(board, SIGNAL(gameWon()), this, SLOT(onGameWon()));
   connect(board, SIGNAL(gameLost()), this, SLOT(onGameLost()));
   board->newGame();
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
void MainWindow::onColorButton()
{
   QPushButton* button(static_cast<QPushButton*>(this->sender()));
   if (!button) return;
   QPushButton* buttons[eColorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < eColorCount; ++i)
      if (button == buttons[i]) 
      { 
         GameBoard::instance().playColor(EColor(i)); 
         break; 
      }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStarted()
{
   qDebug("onGameStarted()");
   ui_.gameStatusLabel->setText("");
   ui_.turnsLeftCounterLabel->setText(QString::number(GameBoard::instance().getTurnsLeft()));
   ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onTurnPlayed()
{
   ui_.turnsLeftCounterLabel->setText(QString::number(GameBoard::instance().getTurnsLeft()));
   ui_.glWidget->updateGL();
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
void MainWindow::onNewGame()
{
   GameBoard::instance().newGame();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onRestartGame()
{
   GameBoard::instance().restartGame();
}

