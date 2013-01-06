/// \file
/// \date 2013-01-05
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "MainWindow.h"
#include "GameBoard.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window creation flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui_.setupUi(this);
   this->setupColorButtons();
}


//**********************************************************************************************************************
///
//**********************************************************************************************************************
MainWindow::~MainWindow()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::setupColorButtons()
{
   QPushButton* buttons[eColorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < eColorCount; ++i)
   {
      QColor const color(kColors[i]);
      buttons[i]->setStyleSheet(QString("background-color: rgb(%1, %2, %3);\nborder: 1px solid rgb(50, 50, 50);")
                                .arg(color.red()).arg(color.green()).arg(color.blue()));
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onColorButton()
{
   QPushButton* button(static_cast<QPushButton*>(this->sender()));
   if (!button) return;
   QPushButton* buttons[eColorCount] = { ui_.color0Button, ui_.color1Button, ui_.color2Button, ui_.color3Button, 
                                         ui_.color4Button, ui_.color5Button };
   for (int i = 0; i < eColorCount; ++i)
      if (button == buttons[i]) 
      { 
         GameBoard::instance().playColor(EColor(i)); 
         ui_.glWidget->updateGL();
         break; 
      }
}

