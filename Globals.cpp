/// \file
/// \author 
///
/// \brief Implementation of global variables for the application.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "Globals.h"


namespace globals {


//**********************************************************************************************************************
/// \return A reference to the random number generator for the application.
//**********************************************************************************************************************
QRandomGenerator& rng()
{
   static QRandomGenerator instance;
   return instance;
}


} // namespace globals



