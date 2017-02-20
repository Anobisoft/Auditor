//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit6.h"
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TJournalForm *JournalForm;
//---------------------------------------------------------------------------

__fastcall TJournalForm::TJournalForm(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::GetJ()
{
  MYSQL_RES *result;
  MYSQL_ROW row;
  AnsiString query = "SELECT inspection.id_inspection, inspection.n_inspection, inspection.dt_inspection, CONCAT_WS(' ', inspector.surname, inspector.name, inspector.patronymic), inspection.name FROM inspection, inspector WHERE inspection.id_director = inspector.id_inspector ORDER BY inspection.id_inspection DESC";
  if (MainForm->DB->Query(query.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    SGrid->RowCount = mysql_num_rows(result) == 0 ? 2 : mysql_num_rows(result)+1;
    Height = SGrid->RowCount <= 30 ? 37+20*SGrid->RowCount : 637;
    for (int i = 1; i <= mysql_num_rows(result); i++) {
      row = mysql_fetch_row(result);
      for (int j = 0; j < 5; j++) SGrid->Cells[j][i] = row[j];
    }
  }
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::FormShow(TObject *Sender)
{
  GetJ();
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::FormCreate(TObject *Sender)
{
  for (int i = 0; i < 5; i++) SGrid->Cells[i][0] = titles[i];
  SGrid->ColWidths[0] = 40;
  SGrid->ColWidths[1] = 72;
  SGrid->ColWidths[2] = 60;
  SGrid->ColWidths[3] = 200;
  SGrid->ColWidths[4] = 300;
  Width = 737;
  Left = MainForm->JL;
  Top = MainForm->JT;
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::FormResize(TObject *Sender)
{
  SGrid->ColWidths[3] = (ClientWidth - 198) * 2 /5;
  SGrid->ColWidths[4] = (ClientWidth - 198) * 3 /5;
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::SGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (Button == 1) {
    SGrid->MouseToCell(X, Y, ACol, ARow);
    if (ARow > 0 && SGrid->Cells[0][ARow] != "") SGrid->PopupMenu = PopupM;
    else SGrid->PopupMenu = PopupD;
  }
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::N1Click(TObject *Sender)
{
  int ur = MessageBox(0, "Вы уверенны, что хотите удалить этот протокол безвозвратно?", "Подтвердите удаление", 4);
  if (ur == mrYes) {
    if (InputForm->id_inspection == SGrid->Cells[0][ARow].ToInt()) InputForm->Close();
    AnsiString query = "DELETE FROM inspection WHERE id_inspection="+SGrid->Cells[0][ARow];
    if (MainForm->DB->Query(query.c_str())) {
      GetJ();
      MessageBox(0, AnsiString("Протокол №"+SGrid->Cells[0][ARow]+" удален").c_str(), "Внимание!", 0);
    }
  }
}

//---------------------------------------------------------------------------

void __fastcall TJournalForm::N2Click(TObject *Sender)
{
  if (InputForm->Visible) {
    int ur = MessageBox(0, "Окно редактирования протокола открыто.\nЕсли открыть этот протокол, несохраненные данные будут утеряны.\nВы уверенны, что хотите продолжить?", "Внимание!", 4);
    if (ur != mrYes) return;
    InputForm->Close();
  }
  InputForm->id_inspection = atoi(SGrid->Cells[0][ARow].c_str());
  InputForm->Editx = true;
  InputForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TJournalForm::FormDestroy(TObject *Sender)
{
  MainForm->JL = Left;
  MainForm->JT = Top;
}
//---------------------------------------------------------------------------


