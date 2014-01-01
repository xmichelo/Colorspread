/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Declaration of game board class


#ifndef COLORSPREAD__GAME__ENGINE__H
#define COLORSPREAD__GAME__ENGINE__H


#include "GameBoard.h"


//**********************************************************************************************************************
/// \brief Game engine class
//**********************************************************************************************************************
class GameEngine: public QObject
{
   Q_OBJECT
public: // member functions
   static GameEngine& instance(); ///< Return the only allowed instance of the class
   ~GameEngine(); ///< Destructor
   void newGame(quint32 seed); ///< Start a new game with the specified seed
   void newGame(); ///< Start a new (random) game
   void restartGame(); ///< Restart the current game
   void playColor(EColor color); /// Play the next turn with the given color
   qint32 getTurnsLeft() const; ///< Return the number of turns left in the game
   quint32 getSeed() const; ///< Return the seed of the game
   GameBoard const& getGameBoard() const; ///< Return a constant reference to the game board
   bool canUndo() const; ///< Test if undo is possible
   bool canRedo() const; ///< Test if redo is possible
   void undo();
   void redo();
   bool isGameFinished() const; ///< check if the game is finished

private: // member functions
   GameEngine(); ///< Default constructor
   GameEngine(GameEngine const&); ///< Disabled copy-constructor
   GameEngine& operator=(GameEngine const&); ///< Disabled assignment operator
   void reset(); ///< Reset the game
   void checkForGameEnd(); ///< Check if the game has ended and emit the appropriate signal (gameWon() or gameLost())

private: // data members
   GameBoard gameBoard_; ///< The game board
   qint32 turnsLeft_; ///< The number of turns left in the game
   quint32 seed_; ///< The seed used to get the random board
   VecSPGameBoard undoStack_; ///< The 'undo' stack
   VecSPGameBoard redoStack_; ///< The 'redo' stack

signals:
   void gameStarted();
   void turnPlayed();
   void gameWon();
   void gameLost();
   void didUndo();
   void didRedo();
};


#endif // #ifndef COLORSPREAD__GAME__ENGINE__H
