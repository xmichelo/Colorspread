/// \file
/// \date 2013-12-31
/// \author Xavier Michelon
///
/// \brief Declaration of game board class


#ifndef COLORSPREAD_GAME_BOARD_H
#define COLORSPREAD_GAME_BOARD_H


#include <vector>
#include <memory>


//**********************************************************************************************************************
// \brief enumeration for colors
//**********************************************************************************************************************
enum class EColor {
   Color0 = 0,
   Color1 = 1,
   Color2 = 2,
   Color3 = 3,
   Color4 = 4,
   Color5 = 5,
   ColorCount = 6,
};


//**********************************************************************************************************************
/// \brief Class for game boards
//**********************************************************************************************************************
class GameBoard
{
public: // member functions
   explicit GameBoard(quint32 seed); ///< Constructor with specific seed
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

typedef std::shared_ptr<GameBoard> SpGameBoard; ///< Type definition for shared pointer to GameBoard
typedef std::vector<SpGameBoard> VecSpGameBoard; ///< type definition for vector of shared pointers to GameBoard


#endif // #ifndef COLORSPREAD__GAME__BOARD__H