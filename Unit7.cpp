//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit1.h"
#include "Unit6.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroupForm *GroupForm;
//---------------------------------------------------------------------------
__fastcall TGroupForm::TGroupForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TGroupForm::FormActivate(TObject *Sender)
{
  InputForm->Enabled = false;
  CheckListBox->ItemEnabled[InputForm->DirectorBox->ItemIndex] = false;
  CheckListBox->Checked[InputForm->DirectorBox->ItemIndex] = true;
}

//---------------------------------------------------------------------------

void __fastcall TGroupForm::OKBtnClick(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------

void __fastcall TGroupForm::CheckAllBoxClick(TObject *Sender)
{
  for (int i = 0; i < CheckListBox->Items->Count; i++)
  {
    if (InputForm->DirectorBox->ItemIndex != i) CheckListBox->Checked[i] = CheckAllBox->Checked;
  }
}

//---------------------------------------------------------------------------


void __fastcall TGroupForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  InputForm->Enabled = true;
  CheckListBox->ItemEnabled[InputForm->DirectorBox->ItemIndex] = true;
  CheckListBox->Checked[InputForm->DirectorBox->ItemIndex] = false;
}
//---------------------------------------------------------------------------


