/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of game board class


#include "stdafx.h"
#include "GameEngine.h"
#include "Constants.h"
#include <deque>
#include <utility>


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
/// \param[in] size The size of the game board
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
   cells_.clear();
   cells_.reserve(kBoardSize * kBoardSize);
   for (qint32 i = 0; i < kBoardSize * kBoardSize; ++i)
      cells_.push_back(EColor(qrand() % eColorCount));
   isGameFinished_ = false;
   emit gameStarted();
}


//**********************************************************************************************************************
/// \param[in] row The zero-based index of the column
/// \param[in] column The zero-based index of the row
/// \return The column of the cell at the given row and column
//**********************************************************************************************************************
EColor GameEngine::getColorAt(qint32 row, qint32 column) const
{
   Q_ASSERT((row >= 0) && (row < kBoardSize));
   Q_ASSERT((column >= 0) && (column < kBoardSize));
   return cells_[kBoardSize * row + column];
}


//**********************************************************************************************************************
/// \param[in] color The color to play
//**********************************************************************************************************************
void GameEngine::playColor(EColor color)
{
   if (isGameFinished_) return;
   EColor const oldColor(this->getColorAt(0,0));
   if (oldColor == color) return;
   deque<pair<qint32, qint32>> queue;
   setColorAt(0, 0, color);
   queue.push_back(make_pair(0,0));
   while(!queue.empty())
   {
      pair<qint32, qint32> pair(queue.front());
      queue.pop_front();
      if ((pair.first > 0) && (oldColor == getColorAt(pair.first - 1, pair.second)))
      {
         setColorAt(pair.first - 1, pair.second, color);
         queue.push_back(make_pair(pair.first - 1, pair.second));
      }
      if ((pair.first < kBoardSize - 1) && (oldColor == getColorAt(pair.first + 1, pair.second)))
      {
         setColorAt(pair.first + 1, pair.second, color);
         queue.push_back(make_pair(pair.first + 1, pair.second));
      }
      if ((pair.second > 0) && (oldColor == getColorAt(pair.first, pair.second - 1)))
      {
         setColorAt(pair.first, pair.second - 1, color);
         queue.push_back(make_pair(pair.first, pair.second - 1));
      }
      if ((pair.second < kBoardSize - 1) && (oldColor == getColorAt(pair.first, pair.second + 1)))
      {
         setColorAt(pair.first, pair.second + 1, color);
         queue.push_back(make_pair(pair.first, pair.second + 1));
      }
   }
   --turnsLeft_;
   emit turnPlayed();
   this->checkForGameEnd();
}


//**********************************************************************************************************************
/// \param[in] row The row of the cell
/// \param[in] column The column of the cell
/// \param[in] color The new color of the cell
//**********************************************************************************************************************
void GameEngine::setColorAt(qint32 row, qint32 column, EColor color)
{
   Q_ASSERT((row >= 0) && (row < kBoardSize));
   Q_ASSERT((column >= 0) && (column < kBoardSize));
   cells_[kBoardSize * row + column] = color;
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
   EColor const color(cells_[0]);
   bool won(true);
   for (int i = 1; i < kBoardSize * kBoardSize; ++i)
      if (color != cells_[i])
      {
         won = false;
         break;
      }
   if (won)
   {
      isGameFinished_ = true;
      emit gameWon();
      return;
   }
   if (0 == turnsLeft_)
   {
      isGameFinished_ = true;
      emit gameLost();
   }
}


//**********************************************************************************************************************
/// \return The seed of the game
//**********************************************************************************************************************
quint32 GameEngine::getSeed() const
{
   return seed_;
}
