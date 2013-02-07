/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Implementation of utility functions


#include "stdafx.h"
#include "Utils.h"


//**********************************************************************************************************************
/// The string representation use lower-case letter, and is padded with zeros, so the length of the string is always 8
///
/// \param[in] value The number
/// \return The hexadecimal representation of the number
//**********************************************************************************************************************
QString uint32ToHexString(quint32 value)
{
   return QString("%1").arg(value, 8, 16, QChar('0')).toLower();
}


//**********************************************************************************************************************
/// \param[in] str The hexadecimal string
/// \param[out] outValue The result of the conversion. if the function returns false, outValue is 0
/// \return true if an only if str contains a valid hexadecimal representation of a 32-bit unsigned integer
//**********************************************************************************************************************
bool hexStringToUint32(QString const& str, quint32& outValue)
{
   bool ok;
   outValue = str.toUInt(&ok, 16);
   return ok;
}
