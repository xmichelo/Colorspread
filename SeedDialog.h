/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Declaration of the seed dialog class


#ifndef COLORSPREAD_SEED_DIALOG_H
#define COLORSPREAD_SEED_DIALOG_H


#include "ui_SeedDialog.h"


//**********************************************************************************************************************
/// \brief Seed dialog class
//**********************************************************************************************************************
class SeedDialog: public QDialog
{
   Q_OBJECT

public: // member functions
   explicit SeedDialog(QWidget* parent = nullptr); ///< Default constructor
   ~SeedDialog() override; ///< Destructor
   quint32 getSeed() const; ///< retrieve the current value of the seed

private: // member functions
   SeedDialog(SeedDialog const&) = delete; ///< Disabled copy-constructor
   SeedDialog(SeedDialog&&) = delete; ///< Disabled move copy-constructor
   SeedDialog& operator=(SeedDialog const&) = delete; ///< Disabled assignment operator
   SeedDialog& operator=(SeedDialog&&) = delete; ///< Disabled move assignment operator
   void tryReadSeedFromClipboard() const; ///< check if the clipboard contains a valid seed value, and if so, set the value of the seed edit to it.

private slots:
   void onTextChanged(QString const& text) const; ///< Call back for the text changed signal

private: // data members
   Ui::SeedDialog ui_; ///< The GUI for the dialog
};


#endif // #ifndef COLORSPREAD_SEED_DIALOG_H
