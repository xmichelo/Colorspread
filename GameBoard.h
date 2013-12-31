/// \file
/// \date 2013-12-31
/// \author Xavier Michelon
///
/// \brief Declaration of game board class


#ifndef COLORSPREAD__GAME__BOARD__H
#define COLORSPREAD__GAME__BOARD__H


#include <vector>


//**********************************************************************************************************************
// \brief enumeration for colors
//**********************************************************************************************************************
enum EColor {
   eColor0 = 0,
   eColor1 = 1,
   eColor2 = 2,
   eColor3 = 3,
   eColor4 = 4,
   eColor5 = 5,
   eColorCount = 6,
};


//**********************************************************************************************************************
/// \brief Class for game boards
//**********************************************************************************************************************
class GameBoard
{
public: // member functions
   GameBoard(); ///< Default constructor
   GameBoard(quint32 seed); ///< Constructor with specific seed
   GameBoard(GameBoard const&); ///< Disabled copy-constructor
   ~GameBoard(); ///< Destructor
   GameBoard& operator=(GameBoard ref); ///< Disabled assignment operator
   void swap(GameBoard& ref); ///< Swap the content of the board
   void reset(quint32 seed); ///< Reset the board using the given seed
   EColor getCellColor(qint32 row, qint32 column) const; ///< Retrieve the color at the given index
   void setCellColor(qint32 row, qint32 column, EColor color); ///< Set the color of a cell
   void spreadColor(EColor color); ///< Spread the specified color
   bool gameIsWon() const; ///< Is the board representing a won game?

private: // data members
   std::vector<EColor> cells_; ///< The board cells
};


#endif // #ifndef COLORSPREAD__GAME__BOARD__H