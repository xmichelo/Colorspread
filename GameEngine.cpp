/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of game board class


#include "stdafx.h"
#include "GameEngine.h"
#include "Constants.h"


using namespace std;


//**********************************************************************************************************************
/// \return The only allowed instance of the class
//**********************************************************************************************************************
GameEngine& GameEngine::instance()
{
   static GameEngine board;
   return board;
}

//**********************************************************************************************************************
//
//**********************************************************************************************************************
GameEngine::GameEngine()
   : seed_(0)
{
   this->reset();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameEngine::~GameEngine()
{

}


//**********************************************************************************************************************
/// \param[in] seed The seed for the new game
//**********************************************************************************************************************
void GameEngine::newGame(quint32 seed)
{
   seed_ = seed;
   qsrand(seed_);
   this->reset();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::newGame()
{
   // we do not want seed to be sequential so we also randomize it. as qrand() return a 16 bit numbers we concatenate
   // two values to get a 32 bit pseudo random value.
   qsrand(quint32(QDateTime::currentMSecsSinceEpoch()));
   this->newGame(quint32(qrand()) | (quint32(qrand()) << 16));
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::restartGame()
{
   ///< We reinitialize the random generator to the same seed, so what have the same game as before
   qsrand(seed_); 
   this->reset();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::reset()
{
   turnsLeft_ = kTurnCount;
   gameBoard_.reset(seed_);
   undoStack_.clear();
   redoStack_.clear();
   emit gameStarted();
}


//**********************************************************************************************************************
/// \param[in] color The color to play
//**********************************************************************************************************************
void GameEngine::playColor(EColor color)
{
   if (this->isGameFinished()) return;
   SPGameBoard previousBoard(make_shared<GameBoard>(gameBoard_));
   gameBoard_.spreadColor(color);
   --turnsLeft_;
   undoStack_.push_back(previousBoard);
   redoStack_.clear();
   emit turnPlayed();
   this->checkForGameEnd();
}


//**********************************************************************************************************************
/// \return the number of turns left in the game
//**********************************************************************************************************************
qint32 GameEngine::getTurnsLeft() const
{
   return turnsLeft_;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::checkForGameEnd()
{
   if (gameBoard_.gameIsWon())
   {
      emit gameWon();
      return;
   }
   if (0 == turnsLeft_)
      emit gameLost();
}


//**********************************************************************************************************************
/// \return The seed of the game
//**********************************************************************************************************************
quint32 GameEngine::getSeed() const
{
   return seed_;
}


//**********************************************************************************************************************
/// \return A constant reference to the game board
//**********************************************************************************************************************
GameBoard const& GameEngine::getGameBoard() const
{
   return gameBoard_;
}


//**********************************************************************************************************************
/// \return true if and only if undoing is possible
//**********************************************************************************************************************
bool GameEngine::canUndo() const
{
   return undoStack_.size() > 0;
}


//**********************************************************************************************************************
/// \return true if and only if redoing is possible
//**********************************************************************************************************************
bool GameEngine::canRedo() const
{
   return redoStack_.size() > 0;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::undo()
{
   Q_ASSERT(undoStack_.size() > 0);
   if (undoStack_.size() < 1)
      return;
   redoStack_.push_back(make_shared<GameBoard>(gameBoard_));
   gameBoard_ = *(undoStack_.back());
   undoStack_.pop_back();
   ++turnsLeft_;
   emit didUndo();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::redo()
{
   Q_ASSERT(redoStack_.size() > 0);
   if (redoStack_.size() < 1)
      return;
   undoStack_.push_back(make_shared<GameBoard>(gameBoard_));
   gameBoard_ = *redoStack_.back();
   redoStack_.pop_back();
   --turnsLeft_;
   emit didRedo();
}


//**********************************************************************************************************************
/// \return true if and only if the game is finished (won or lost)
//**********************************************************************************************************************
bool GameEngine::isGameFinished() const
{
   return (gameBoard_.gameIsWon()) || (0 == turnsLeft_);
}

