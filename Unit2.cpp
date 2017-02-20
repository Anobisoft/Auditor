//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::FormActivate(TObject *Sender)
{
  MainForm->Enabled = false;
  MainForm->HKLMOpt->OpenKey("software\\InspectorClient", true);
  Opt1Edit->Text = MainForm->HKLMOpt->ReadString("DBHost");
  if (MainForm->HKLMOpt->ValueExists("DBPort")) {
    Opt2Edit->Text = MainForm->HKLMOpt->ReadInteger("DBPort");
  } else Opt2Edit->Text = "3306";
  Opt3Edit->Text = MainForm->HKLMOpt->ReadString("DBUser");
  Opt4MaskEdit->Text = MainForm->HKLMOpt->ReadString("DBPass");
  if (MainForm->HKLMOpt->ValueExists("DBName")) {
    Opt5Edit->Text = MainForm->HKLMOpt->ReadString("DBName");
  } else Opt5Edit->Text = "inspectordb";
  MainForm->HKLMOpt->CloseKey();
  ApplyBtn->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  MainForm->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::ApplyBtnClick(TObject *Sender)
{
  MainForm->HKLMOpt->OpenKey("software\\InspectorClient", true);
  MainForm->HKLMOpt->WriteString("DBHost", Opt1Edit->Text);
  MainForm->HKLMOpt->WriteInteger("DBPort", atoi(Opt2Edit->Text.c_str()));
  MainForm->HKLMOpt->WriteString("DBUser", Opt3Edit->Text);
  MainForm->HKLMOpt->WriteString("DBPass", Opt4MaskEdit->Text);
  MainForm->HKLMOpt->WriteString("DBName", Opt5Edit->Text);
  MainForm->HKLMOpt->CloseKey();
  ApplyBtn->Enabled = false;
  MainForm->TryGetOptions();
  MainForm->PrintLabel();
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::CancelBtnClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::OptEditChange(TObject *Sender)
{
  ApplyBtn->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TOptionsForm::OKBtnClick(TObject *Sender)
{
  if (ApplyBtn->Enabled) ApplyBtnClick(Sender);
  Close();
}

//---------------------------------------------------------------------------

