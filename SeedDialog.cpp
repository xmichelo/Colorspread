/// \file
/// \date 2013-02-07
/// \author Xavier Michelon
///
/// \brief Declaration of the seed dialog class


#include "stdafx.h"
#include "SeedDialog.h"
#include "GameEngine.h"
#include "Utils.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the dialog
//**********************************************************************************************************************
SeedDialog::SeedDialog(QWidget* parent)
   : QDialog(parent)
{
   ui_.setupUi(this);
   ui_.seedEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9a-fA-F]{1,8}"), ui_.seedEdit));
   connect(ui_.seedEdit, &QLineEdit::textChanged, this, &SeedDialog::onTextChanged);
   tryReadSeedFromClipboard();
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
void SeedDialog::onTextChanged(QString const& text) const
{
   int pos(0);
   QString t(text);
   ui_.okButton->setEnabled((QValidator::Acceptable == ui_.seedEdit->validator()->validate(t, pos)));
}


//**********************************************************************************************************************
/// \return The seed entered in the text field
//**********************************************************************************************************************
quint32 SeedDialog::getSeed() const
{
   quint32 result;
   hexStringToUint32(ui_.seedEdit->text(), result);
   return result;
}


//**********************************************************************************************************************
/// if no valid seed is in the clipboard, the value of the seed text field will be the one of the current game
//**********************************************************************************************************************
void SeedDialog::tryReadSeedFromClipboard() const
{
   QClipboard const* clipboard(QApplication::clipboard());
   if (clipboard->mimeData()->hasText())
   {
      QString const str(clipboard->text());
      quint32 seed;
      if (hexStringToUint32(str, seed))
      {
         ui_.seedEdit->setText(str);
         return;
      }
   }
   ui_.seedEdit->setText(uint32ToHexString(GameEngine::instance().getSeed()));
}

