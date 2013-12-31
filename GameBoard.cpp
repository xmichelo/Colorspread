/// \file
/// \date 2013-12-31
/// \author Xavier Michelon
///
/// \brief Implementation of game board class


#include "stdafx.h"
#include "GameBoard.h"
#include "Constants.h"
#include <utility>
#include <deque>


using namespace std;


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameBoard::GameBoard()
   : cells_(kBoardSize * kBoardSize, eColor0)
{

}


//**********************************************************************************************************************
/// \param[in] seed The seed for the game board
//**********************************************************************************************************************
GameBoard::GameBoard(quint32 seed)
{
   this->reset(seed);
}


//**********************************************************************************************************************
/// \param[in] ref The board to copy from
//**********************************************************************************************************************
GameBoard::GameBoard(GameBoard const& ref)
   : cells_(ref.cells_)
{
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameBoard::~GameBoard()
{

}


//**********************************************************************************************************************
/// \param[in] ref The board to copy from
//**********************************************************************************************************************
GameBoard& GameBoard::operator=(GameBoard ref)
{
   this->swap(ref);
   return *this;
}


//**********************************************************************************************************************
/// \param[in] ref The board to swap content with
//**********************************************************************************************************************
void GameBoard::swap(GameBoard& ref)
{
   cells_.swap(ref.cells_);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameBoard::reset(quint32 seed)
{
   cells_.clear();
   cells_.reserve(kBoardSize * kBoardSize);
   qsrand(seed); 
   for (qint32 i = 0; i < kBoardSize * kBoardSize; ++i)
      cells_.push_back(EColor(qrand() % eColorCount));
}


//**********************************************************************************************************************
/// \param[in] row The zero-based index of the cell's row
/// \param[in] column The zero-based index of the cell's column
//**********************************************************************************************************************
EColor GameBoard::getCellColor(qint32 row, qint32 column) const
{
   Q_ASSERT((row >= 0) && (row < kBoardSize));
   Q_ASSERT((column >= 0) && (column < kBoardSize));
   return cells_[kBoardSize * row + column];
}


//**********************************************************************************************************************
/// \param[in] row The row of the cell
/// \param[in] column The column of the cell
/// \param[in] color The new color of the cell
//**********************************************************************************************************************
void GameBoard::setCellColor(qint32 row, qint32 column, EColor color)
{
   Q_ASSERT((row >= 0) && (row < kBoardSize));
   Q_ASSERT((column >= 0) && (column < kBoardSize));
   cells_[kBoardSize * row + column] = color;
}


//**********************************************************************************************************************
/// \param[in] color The color to spread
//**********************************************************************************************************************
void GameBoard::spreadColor(EColor color)
{
   EColor const oldColor(this->getCellColor(0,0));
   if (oldColor == color) return;
   deque<pair<qint32, qint32>> queue;
   this->setCellColor(0, 0, color);
   queue.push_back(make_pair(0,0));
   while(!queue.empty())
   {
      pair<qint32, qint32> pair(queue.front());
      queue.pop_front();
      if ((pair.first > 0) && (oldColor == this->getCellColor(pair.first - 1, pair.second)))
      {
         this->setCellColor(pair.first - 1, pair.second, color);
         queue.push_back(make_pair(pair.first - 1, pair.second));
      }
      if ((pair.first < kBoardSize - 1) && (oldColor == this->getCellColor(pair.first + 1, pair.second)))
      {
         this->setCellColor(pair.first + 1, pair.second, color);
         queue.push_back(make_pair(pair.first + 1, pair.second));
      }
      if ((pair.second > 0) && (oldColor == this->getCellColor(pair.first, pair.second - 1)))
      {
         this->setCellColor(pair.first, pair.second - 1, color);
         queue.push_back(make_pair(pair.first, pair.second - 1));
      }
      if ((pair.second < kBoardSize - 1) && (oldColor == this->getCellColor(pair.first, pair.second + 1)))
      {
         this->setCellColor(pair.first, pair.second + 1, color);
         queue.push_back(make_pair(pair.first, pair.second + 1));
      }
   }
}


//**********************************************************************************************************************
/// \return true if and only if the game board is representing a won game (all cell have the same colors)
//**********************************************************************************************************************
bool GameBoard::gameIsWon() const
{
   Q_ASSERT(cells_.size() == kBoardSize * kBoardSize);
   EColor const color(cells_.front());
   for (std::vector<EColor>::const_iterator it = cells_.begin() + 1; it != cells_.end(); ++it)
      if (color != *it)
         return false;
   return true;
}


