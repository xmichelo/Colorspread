/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Declaration of constants


#ifndef COLORSPREAD_CONSTANTS_H
#define COLORSPREAD_CONSTANTS_H


namespace constants {


extern qint32 const kBoardSize; ///< The size of the game board (number of cells on each row and column)
extern qint32 const kTurnCount; ///< The number of turns allowed in a game
extern std::vector<QColor> const kColors; ///< The list of colors
extern qint32 const kCellRenderSize; ///< The rendering size of cells


} // namespace constants


#endif // #ifndef COLORSPREAD_CONSTANTS_H
