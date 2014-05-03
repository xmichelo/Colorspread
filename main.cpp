/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point


#include "stdafx.h"
#include "MainWindow.h"


//**********************************************************************************************************************
/// \brief program entry-point
///
/// \param[in] argc The number of arguments passed on the command line
/// \param[in] argv The list of arguments passed on the command line
//**********************************************************************************************************************
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
