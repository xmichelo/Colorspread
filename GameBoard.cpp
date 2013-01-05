/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of game board class


#include "stdafx.h"
#include "GameBoard.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \return The only allowed instance of the class
//**********************************************************************************************************************
GameBoard& GameBoard::instance()
{
   static GameBoard board;
   return board;
}

//**********************************************************************************************************************
/// \param[in] size The size of the game board
//**********************************************************************************************************************
GameBoard::GameBoard()
{
   this->reset();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameBoard::~GameBoard()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameBoard::reset()
{
   cells_.clear();
   cells_.reserve(kBoardSize * kBoardSize);
   for (qint32 i = 0; i < kBoardSize * kBoardSize; ++i)
      cells_.push_back(EColor(qrand() % eColorCount));
}


//**********************************************************************************************************************
/// \param[in] row The zero-based index of the column
/// \param[in] column The zero-based index of the row
/// \return The column of the cell at the given row and column
//**********************************************************************************************************************
EColor GameBoard::getColorAt(qint32 row, qint32 column)
{
   Q_ASSERT(row < kBoardSize);
   Q_ASSERT(column < kBoardSize);
   return cells_[kBoardSize * row + column];
}
