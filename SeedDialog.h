/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Declaration of the seed dialog class


#ifndef COLORSPREAD__SEED__DIALOG__H
#define COLORSPREAD__SEED__DIALOG__H


#include "ui_SeedDialog.h"


//**********************************************************************************************************************
/// \brief Seed dialog class
//**********************************************************************************************************************
class SeedDialog: public QDialog
{
   Q_OBJECT

public: // member functions
   SeedDialog(QWidget* parent = nullptr); ///< Default constructor
   ~SeedDialog(); ///< Destructor
   quint32 getSeed() const; ///< retrieve the current value of the seed

private: // member functions
   SeedDialog(SeedDialog const&); ///< Disabled copy-constructor
   SeedDialog& operator=(SeedDialog const&); ///< Disabled assignment operator

private slots:
   void onTextChanged(QString const& text); ///< Call back for the text changed signal

private: // data members
   Ui::SeedDialog ui_; ///< The GUI for the dialog
   QRegExpValidator* validator; ///< The validator for the seed text field
};


#endif // #ifndef COLORSPREAD__SEED__DIALOG__H
