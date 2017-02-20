//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
#include "Unit6.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------

__fastcall TAddUserForm::TAddUserForm(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::FormActivate(TObject *Sender)
{
  MainForm->Enabled = false;
  InputForm->Enabled = false;
  OKBtn->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  MainForm->Enabled = true;
  InputForm->Enabled = true;
  Edit1->Clear();
  Edit2->Clear();
  Edit3->Clear();
  Edit4->Clear();
  Edit5->Clear();
  Edit1->SetFocus();
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::OKBtnClick(TObject *Sender)
{
  MainForm->DB->AddUser(Edit1->Text,Edit2->Text,Edit3->Text,Edit4->Text);
  Close();
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::CancelBtnClick(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::EditChange(TObject *Sender)
{
   if (Edit1->Text != "" && Edit2->Text != "" && Edit3->Text != "" && Edit4->Text != "" && Edit5->Text != "")
   {
     if (Edit4->Text == Edit5->Text) {
       Label6->Caption = "";
       OKBtn->Enabled = true;
     } else {
       OKBtn->Enabled = false;
       Label6->Caption = "Пароли должны совпадать!";
     }
   } else {
     OKBtn->Enabled = false;
     Label6->Caption = "Все поля обязательны для заполнения!";
   }
}

//---------------------------------------------------------------------------

void __fastcall TAddUserForm::EditKeyPress(TObject *Sender, char &Key)
{
   if (Key == char(13)) {
     if (Edit1->Text != "" && Edit2->Text != "" && Edit3->Text != "")
       if (Edit4->Text == Edit5->Text) OKBtnClick(Sender);
       else MessageBox(0, "Пароли не совпадают", "Ошибка", 0);
     else MessageBox(0, "Все поля обязательны для заполнения", "Ошибка", 0);
   }
}

//---------------------------------------------------------------------------

