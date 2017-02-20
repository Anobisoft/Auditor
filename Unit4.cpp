//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPwdForm *PwdForm;
//---------------------------------------------------------------------------
__fastcall TPwdForm::TPwdForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPwdForm::FormActivate(TObject *Sender)
{
  PwdEdit->Clear();
  count = 4;
  MainForm->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TPwdForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  MainForm->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPwdForm::OKClick(TObject *Sender)
{
  if (correctpass == PwdEdit->Text) {
    MainForm->ChngEnbl(true);
    Close();
  } else {
    if (!--count) {
      Close();
      MainForm->Close();
    } else {
        char * ccc = "99";
        itoa(count, ccc, 10);
        MessageBox(0, ccc, "Неверно! Осталось попыток: ", 0);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TPwdForm::PwdEditKeyPress(TObject *Sender, char &Key)
{
  if (Key == char(13)) OKClick(Sender);
}
//---------------------------------------------------------------------------

