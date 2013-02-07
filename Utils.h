/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Declaration of utility functions


#ifndef COLORSPREAD__UTILS__H
#define COLORSPREAD__UTILS__H


QString uint32ToHexString(quint32 value); // Return the hexadecimal representation of an 32-bit unsigned number
bool hexStringToUint32(QString const& str, quint32& outValue); ///< read an unsigned 32-bit integer from its hexadecimal representation

#endif // #ifndef COLORSPREAD__UTILS__H
