/// \file
/// \date 2013-01-05
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
/// \brief Game board class
//**********************************************************************************************************************
class GameBoard: public QObject
{
   Q_OBJECT
public: // member functions
   static GameBoard& instance();
   ~GameBoard(); ///< Destructor
   void reset(); ///< Reset the game board
   EColor getColorAt(qint32 row, qint32 column) const; ///< Retrieve the color at the given index
   void playColor(EColor color); /// Play the next turn with the given color
   qint32 getTurnsLeft() const; ///< Return the number of turns left in the game

private: // member functions
   GameBoard(GameBoard const&); ///< Disabled copy-constructor
   GameBoard& operator=(GameBoard const&); ///< Disabled assignment operator
   void setColorAt(qint32 row, qint32 column, EColor color); ///< Set the color of a cell
   void checkForGameEnd(); ///< Check if the game has ended and emit the appropriate signal (gameWon() or gameLost())

private: // data members
   GameBoard();
   std::vector<EColor> cells_; ///< The game board cells
   qint32 turnsLeft_; ///< The number of turns left in the game
   bool isGameFinished_; ///< Is the game finished

signals:
   void gameStarted();
   void turnPlayed();
   void gameWon();
   void gameLost();
};


#endif // #ifndef COLORSPREAD__GAME__BOARD__H
