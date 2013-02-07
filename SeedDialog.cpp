/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Declaration of the seed dialog class


#include "stdafx.h"
#include "SeedDialog.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the dialog
//**********************************************************************************************************************
SeedDialog::SeedDialog(QWidget* parent)
   : QDialog(parent)
{
   ui_.setupUi(this);
   validator = new QRegExpValidator(QRegExp("[0-9a-fA-F]{1,8}"), this);
   ui_.seedEdit->setValidator(validator);
   connect(ui_.seedEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(QString const &)));
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
SeedDialog::~SeedDialog()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void SeedDialog::onTextChanged(QString const& text)
{
   int pos(0);
   QString t(text);
   ui_.okButton->setEnabled((QValidator::Acceptable == validator->validate(t, pos)));
}


//**********************************************************************************************************************
/// \return The seed entered in the text field
//**********************************************************************************************************************
quint32 SeedDialog::getSeed() const
{
   QString input(ui_.seedEdit->text());
   int pos(0);
   if (QValidator::Acceptable != validator->validate(input, pos))
      return 0;
   return input.toUInt(nullptr, 16);
}

