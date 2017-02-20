//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInputForm *InputForm;
//---------------------------------------------------------------------------
__fastcall TInputForm::TInputForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

AnsiString TInputForm::Fpnt( AnsiString x )
{
   for (int i = 1; i <= x.Length(); i++ ) if (x[i] == ',') x[i] = '.';
   return x;
}

void __fastcall TInputForm::FormCreate(TObject *Sender)
{
  SGrid->ColWidths[0] = 39;
  cur1 = cur2 = -1;
  Editx = false;
  Left = MainForm->IL;
  Top = MainForm->IT;
}


void __fastcall TInputForm::FormShow(TObject *Sender)
{
  DatePicker->Date = DateTime.CurrentDate();
  DatePicker->MaxDate = (int)DateTime.CurrentDate();

  Period1->MaxDate = (int)DateTime.CurrentDate();
  Period2->MaxDate = (int)DateTime.CurrentDate();

  Period1->Date = (int)DateTime.CurrentDate();
  Period2->Date = (int)DateTime.CurrentDate();
  Period2->MinDate = (int)Period1->Date;

  MainForm->AddBtn->Enabled = false;
  GroupBtn->Enabled = Editx;
  if (Editx) SelectProto();
  else MotivBox->ItemIndex = -1;
  GroupForm->CheckListBox->Clear();
  GroupForm->CheckAllBox->Checked = false;
  DirectorBox->Clear();
  DirectorBox->Text = "Выберите руководителя группы";
  rlist *tmp = MainForm->Insp->head;
  while (tmp) {
    DirectorBox->Items->Add(tmp->data->fio);
    if (Editx && tmp->data->dbi == id_director) DirectorBox->ItemIndex = tmp->data->ind;
    GroupForm->CheckListBox->Items->Add(tmp->data->fio);
    if (Editx) {
      query = "SELECT id_inspector FROM inspection_group WHERE id_inspection="+AnsiString(id_inspection)+" AND id_inspector="+AnsiString(tmp->data->dbi);
      if (MainForm->DB->Query(query.c_str())) {
        result = mysql_store_result(MainForm->DB->dbCnt);
        GroupForm->CheckListBox->Checked[tmp->data->ind] = mysql_num_rows(result) == 1;
      }
    }
    tmp = tmp->next;
  }
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 16; i++)
      for (int k = 0; k < 20; k++) proto1data[i][j][k] = 0;
    for (int i = 0; i < 7; i++) proto2data[i][j] = 0;
  }
  Editx = false;
  Period1->Enabled = true;
  Period2->Enabled = true;
  PeriodBtn->Enabled = true;
  PeriodBtn->Caption = "Зафиксировать";
  LabelRequire3->Caption = "(обязательно зафиксировать)";
  PFixed = false;
  RGroup1->Enabled = false;
  RGroup2->Enabled = false;
  SendBtn->Enabled = false;
  OkBtn->Enabled = false;
  LabelRequire1->Caption = "(обязательное поле)";
  LabelRequire2->Caption = "(обязательное поле)";
  RGroup1->ItemIndex = cur1 = -1;
  RGroup2->ItemIndex = cur2 = -1;
  SGrid->Height = 0;
  Label7->Top = 96;
  Comment->Top = 112;
  Comment->Height = 521;
  Comment->Clear();
  NameEdit->Clear();
  NumEdit->Clear();
  MainForm->AddBtn->Enabled = true;
}

//---------------------------------------------------------------------------

bool TInputForm::proto1save()
{
 if (cur1 != -1)
   for (int i = 0; i < 4; i++)
    for (int j = 0; j <= dtx2.year-dtx1.year; j++)
      if (isFloat(SGrid->Cells[i+1][j+1])) proto1data[cur1][i][j] = SGrid->Cells[i+1][j+1].ToDouble();
      else {
        SGrid->Col = i+1;
        SGrid->Row = j+1;
        return false;
      }
 return true;
}

bool TInputForm::proto2save()
{
 if (cur2 != -1)
  for (int i = 0; i < 4; i++)
   if (isFloat(SGrid->Cells[i+1][1])) proto2data[cur2][i] = SGrid->Cells[i+1][1].ToDouble();
   else return false;
 return true;
}

void TInputForm::proto1get(int x)
{
  double sum, sm[5] = {0, 0, 0, 0, 0};
  int j, i;
  for (i = 0; i <= dtx2.year-dtx1.year; i++) {
    sum = 0;
    for (j = 0; j < 4; j++){
      SGrid->Cells[j+1][i+1] = AnsiString(proto1data[x][j][i]);
      sum += proto1data[x][j][i];
      sm[j] += proto1data[x][j][i];
    }
    sm[4] += sum;
    SGrid->Cells[5][i+1] = sum;
  }
  for (j = 0; j < 5; j++) SGrid->Cells[j+1][i+1] = sm[j]; 
}

void TInputForm::proto2get(int x)
{
  double sum = 0;
  for (int i = 0; i < 4; i++) {
    SGrid->Cells[i+1][1] = AnsiString(proto2data[x][i]);
    sum += proto2data[x][i];
  }
  SGrid->Cells[5][1] = sum;
}

void TInputForm::proto1draw()
{
  SGrid->RowCount = dtx2.year-dtx1.year+3;
  SGrid->Height = (dtx2.year-dtx1.year+3)*20+4;
  Comment->Height = 521-SGrid->Height;
  Comment->Top = 112+SGrid->Height;
  Label7->Top = 96+SGrid->Height;
  int i;
  for (i = 0; i <= dtx2.year-dtx1.year; i++) {
    SGrid->Cells[0][i+1] = dtx1.year + i;
  }
  SGrid->Cells[0][i+1] = "Сумма";
}

void TInputForm::proto2draw()
{
  SGrid->RowCount = 2;
  Label7->Top = 140;
  SGrid->Height = 44;
  Comment->Height = 477;
  Comment->Top = 156;
  SGrid->Cells[0][1] = "Все";
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::RGroup1Click(TObject *Sender)
{
  if (FirstEdit && cur1 != -1) {
    if (!proto1save()) {
      RGroup1->ItemIndex = cur1;
      return ;
    } else ;
  } else {
    if (!proto2save()) {
      RGroup2->SetFocus();
      RGroup2->ItemIndex = cur2;
      return ;
    } else {
      FirstEdit = true;
      RGroup2->ItemIndex = -1;
      proto1draw();
    }
  }
  cur1 = RGroup1->ItemIndex;
  proto1get(cur1);
  SGrid->SetFocus(); SGrid->Col = 1; SGrid->Row = 1;
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::RGroup2Click(TObject *Sender)
{
  if (FirstEdit)
  {
    if (proto1save()) {
      FirstEdit = false;
      RGroup1->ItemIndex = -1;
      proto2draw();
    } else {
      RGroup1->SetFocus();
      RGroup1->ItemIndex = cur1;
      return ;
    }
  } else if (cur2 != -1) {
           if (!proto2save()) {
             RGroup2->ItemIndex = cur2;
             return ;
           } else ;
         } else proto2draw();
  cur2 = RGroup2->ItemIndex;
  proto2get(cur2);
  SGrid->SetFocus(); SGrid->Col = 1; SGrid->Row = 1;
}

//---------------------------------------------------------------------------


void __fastcall TInputForm::Period1Change(TObject *Sender)
{
  Period2->MaxDate = Period1->Date + 7300 > DateTime.CurrentDate() ? DateTime.CurrentDate() : Period1->Date + 7300;
  Period2->MinDate = Period1->Date;
}

void __fastcall TInputForm::PeriodBtnClick(TObject *Sender)
{
  if (PFixed)
  {
    PFixed = false;
    Period1->Enabled = true;
    Period2->Enabled = true;
    PeriodBtn->Caption = "Зафиксировать";
    LabelRequire3->Caption = "(фиксировать обязательно)";
    RGroup1->Enabled = false;
    RGroup2->Enabled = false;
    SendBtn->Enabled = false;
    OkBtn->Enabled = false;
    Label7->Top = 96;
    Comment->Top = 112;
    Comment->Height = 521;
    SGrid->Height = 0;
    RGroup1->ItemIndex = cur1 = -1;
    RGroup2->ItemIndex = cur2 = -1;
  } else {
    if ((DirectorBox->ItemIndex != -1) && (MotivBox->ItemIndex != -1)) {
      SendBtn->Enabled = true;
      OkBtn->Enabled = true;
    }
    Period1->Date.DecodeDate(&dtx1.year, &dtx1.month, &dtx1.day);
    Period2->Date.DecodeDate(&dtx2.year, &dtx2.month, &dtx2.day);
    PFixed = true;
    Period1->Enabled = false;
    Period2->Enabled = false;
    PeriodBtn->Caption = "Изменить период";
    LabelRequire3->Caption = "";
    RGroup1->Enabled = true;
    RGroup2->Enabled = true;
  }
}

//---------------------------------------------------------------------------

void TInputForm::InsertGroup()
{
  rlist *tmp = MainForm->Insp->head;
  while (tmp != NULL) {
    if (GroupForm->CheckListBox->Checked[tmp->data->ind]) {
      query = "INSERT INTO inspection_group VALUES ('"+AnsiString(id_inspection)+"', '"+AnsiString(tmp->data->dbi)+"')";
      MainForm->DB->Query(query.c_str());
    }
    tmp = tmp->next;
  }
}

void TInputForm::InsertData1()
{
  for (int k = 0; k <= dtx2.year-dtx1.year; k++)
    for (int i = 0; i < 4; i++)
    {
      query = "INSERT INTO inspection_budget_year VALUES ("+AnsiString(id_inspection)+", "+AnsiString(i+1)+", "+AnsiString(dtx1.year+k);
      for (int j = 0; j < 16; j++) query += ", " + Fpnt(AnsiString(proto1data[j][i][k]));
      query += ")";
      MainForm->DB->Query(query.c_str());
    }
}
void TInputForm::InsertData2()
{
  for (int i = 0; i < 4; i++) {
    query = "INSERT INTO inspection_budget VALUES ("+AnsiString(id_inspection)+", "+AnsiString(i+1);
    for (int j = 0; j < 7; j++) query += ", " + Fpnt(AnsiString(proto2data[j][i]));
    query += ")";
    MainForm->DB->Query(query.c_str());
  }
}

void TInputForm::UpdateProto()
{
  query = "UPDATE inspection SET dt_inspection='"+dt_inspection+"', "+
  "dt_pbegin='"+dt_pbegin+"', "+
  "dt_pend='"+dt_pend+"', "+
  "name='"+inspection_name+"', "+
  "motivation='"+motivation+"', "+
  "id_director='"+AnsiString(id_director)+"', "+
  "id_inspector_m='"+id_inspector_m+"', "+
  "comment='"+comment+"', dtm_modif=NOW(), "+
  "n_inspection='"+NumEdit->Text+"' WHERE id_inspection="+AnsiString(id_inspection);
  if (MainForm->DB->Query(query.c_str())) {
    query = "DELETE FROM inspection_group WHERE id_inspection="+AnsiString(id_inspection);
    if (MainForm->DB->Query(query.c_str())) InsertGroup();
    query = "DELETE FROM inspection_budget_year WHERE id_inspection="+AnsiString(id_inspection);
    if (MainForm->DB->Query(query.c_str())) InsertData1();
    query = "DELETE FROM inspection_budget WHERE id_inspection="+AnsiString(id_inspection);
    if (MainForm->DB->Query(query.c_str())) InsertData2();
  }
}


bool TInputForm::InsertProto()
{
  id_target = mysql_insert_id(MainForm->DB->dbCnt);
  query = "INSERT INTO inspection (dt_inspection, dt_pbegin, dt_pend, name, motivation, id_director, id_inspector_m, comment, dtm_modif, n_inspection) VALUES ('"+
    dt_inspection+"', '"+
    dt_pbegin+"', '"+
    dt_pend+"', '"+
    inspection_name+"', '"+
    motivation+"', '"+
    AnsiString(id_director)+"', '"+
    id_inspector_m+"', '"+
    comment+"', NOW(), '"+
    NumEdit->Text+"');";
  if (MainForm->DB->Query(query.c_str())) {
    id_inspection = mysql_insert_id(MainForm->DB->dbCnt);
    InsertGroup();
    InsertData1();
    InsertData2();
    return true;
  }
  return false;
}

TDateTime ConvDate(char * s)
{
  AnsiString x, xx;
  x = AnsiString(s);
  xx = AnsiString(x[9])+AnsiString(x[10])+"."+AnsiString(x[6])+AnsiString(x[7])+"."+AnsiString(x[1])+AnsiString(x[2])+AnsiString(x[3])+AnsiString(x[4]);
  return StrToDate(xx);
}

bool TInputForm::SelectProto()
{
  int i, j, y1, y2;
  AnsiString query = "SELECT * FROM inspection WHERE id_inspection="+AnsiString(id_inspection);
  if (MainForm->DB->Query(query.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    row = mysql_fetch_row(result);
    DatePicker->Date = ConvDate(row[1]);

    Period1->Date = ConvDate(row[2]);
    Period2->MinDate = (int)Period1->Date;
    Period2->Date = ConvDate(row[3]);
    Period1->Date.DecodeDate(&dtx1.year, &dtx1.month, &dtx1.day);
    Period2->Date.DecodeDate(&dtx2.year, &dtx2.month, &dtx2.day);
    PFixed = true;
    Period1->Enabled = false;
    Period2->Enabled = false;
    PeriodBtn->Caption = "Изменить период";
    RGroup1->Enabled = true;
    RGroup2->Enabled = true;
    SendBtn->Enabled = true;
    OkBtn->Enabled = true;
    LabelRequire1->Caption = "";
    LabelRequire2->Caption = "";
    LabelRequire3->Caption = "";

    NameEdit->Text = row[4];
    MotivBox->ItemIndex = atoi(row[5])-1;
    id_director = atoi(row[6]);
    comment = row[8];
    for (i = 1; i <= comment.Length(); i++)
      if (comment[i] == '#') comment[i] = '\r', comment[++i] = '\n';
    Comment->Text = comment;
    NumEdit->Text = row[10];
  }
  int k, m;
  query = "SELECT * FROM inspection_budget WHERE id_inspection="+AnsiString(id_inspection);
  if (MainForm->DB->Query(query.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    for (i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      k = atoi(row[1]);
      for (j = 0; j < 7; j++) proto2data[j][k-1] = atof(row[j+2]);
    }
  }
  query = "SELECT * FROM inspection_budget_year WHERE id_inspection="+AnsiString(id_inspection);
  if (MainForm->DB->Query(query.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    for (i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      k = atoi(row[1]), m = atoi(row[2])-dtx1.year;
      for (j = 0; j < 16; j++) proto1data[j][k-1][m] = atof(row[j+3]);
    }
  }
  return true;
}

void __fastcall TInputForm::SendBtnClick(TObject *Sender)
{
  if (FirstEdit) {
    if (proto1save()) EExit = true;
    else {
      EExit = false;
      return ;
    }
  } else if (proto2save()) EExit = true;
         else {
           EExit = false;
           return ;
         }

  inspection_name = NameEdit->Text;
  dt_inspection = DatePicker->Date.FormatString("YYYY-MM-DD");
  dt_pbegin = Period1->Date.FormatString("YYYY-MM-DD");
  dt_pend = Period2->Date.FormatString("YYYY-MM-DD");
  if (DirectorBox->ItemIndex != -1) {
    rlist *tmp = MainForm->Insp->head;
    while (tmp->data->ind != DirectorBox->ItemIndex) tmp = tmp->next;
    id_director = tmp->data->dbi;
  } else id_director = 0;
  comment = Comment->Text;
  for (int i = 1; i <= comment.Length(); i++)
    if (comment[i] == '\r' || comment[i] == '\n') comment[i] = '#';
  motivation = MotivBox->ItemIndex+1;

  if (Editx) UpdateProto();
  else if (InsertProto()) Editx = true;
  if (JournalForm->Visible) JournalForm->GetJ();
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::DirectorBoxSelect(TObject *Sender)
{
  GroupBtn->Enabled = true;
  LabelRequire1->Caption = "";
  if (PFixed && (MotivBox->ItemIndex > -1)) {
    SendBtn->Enabled = true;
    OkBtn->Enabled = true;
  }
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::DirectorBoxChange(TObject *Sender)
{
  GroupBtn->Enabled = false;
  SendBtn->Enabled = false;
  OkBtn->Enabled = false;
  LabelRequire1->Caption = "(обязательное поле)";
  GroupForm->CheckListBox->Checked[DirectorBox->ItemIndex] = false;
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::MotivBoxSelect(TObject *Sender)
{
  LabelRequire2->Caption = "";
  if (PFixed && (DirectorBox->ItemIndex > -1)) {
    SendBtn->Enabled = true;
    OkBtn->Enabled = true;
  }
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::MotivBoxChange(TObject *Sender)
{
  SendBtn->Enabled = false;
  OkBtn->Enabled = false;
  LabelRequire2->Caption = "(обязательное поле)";
}

//---------------------------------------------------------------------------

bool TInputForm::isFloat(AnsiString x) {
  int i;
  for (i = 1; i <= x.Length(); i++) {
    if (x[i] == ',')
      if (i == x.Length() || i == 1) return false;
      else for ( i++; i <= x.Length(); i++)
             if (x[i] >= '0' && x[i] <= '9') ;
             else return false;
    else if (x[i] >= '0' && x[i] <= '9') ;
         else return false;
  }
  if (i > 1) return true;
  else return false;
}

void __fastcall TInputForm::SGridSetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
  if (isFloat(SGrid->Cells[ACol][ARow])) {
    double sum = 0;
    int i;
    for (i = 1; i < 5; i++) if (isFloat(SGrid->Cells[i][ARow])) sum += SGrid->Cells[i][ARow].ToDouble();
    SGrid->Cells[5][ARow] = sum;
    if (FirstEdit)
    {
      sum = 0;
      for (i = 1; i < SGrid->RowCount-1; i++) if (isFloat(SGrid->Cells[ACol][i])) sum += SGrid->Cells[ACol][i].ToDouble();
      SGrid->Cells[ACol][SGrid->RowCount-1] = sum;
      sum = 0;
      for (i = 1; i < 5; i++) if (isFloat(SGrid->Cells[i][SGrid->RowCount-1])) sum += SGrid->Cells[i][SGrid->RowCount-1].ToDouble();
      SGrid->Cells[5][SGrid->RowCount-1] = sum;
    }
  }
}

//---------------------------------------------------------------------------

void __fastcall TInputForm::GroupBtnClick(TObject *Sender)
{
  GroupForm->Show();
}
//---------------------------------------------------------------------------


void __fastcall TInputForm::OkBtnClick(TObject *Sender)
{
  SendBtnClick(Sender);
  if (EExit) Close();
}
//---------------------------------------------------------------------------


void __fastcall TInputForm::FormDestroy(TObject *Sender)
{
  MainForm->IL = Left;
  MainForm->IT = Top;
}
//---------------------------------------------------------------------------


