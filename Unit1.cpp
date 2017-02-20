//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit6.h"
#include "Unit8.h"
#include "Unit9.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TMySQL_work::Close()
{
  mysql_close(dbCnt);
  Connected = false;
}

bool __fastcall TMySQL_work::Query(char *query)
{
  bool err = mysql_query(dbCnt,query);
  if (err) { MessageBox(0, mysql_error(dbCnt), "Ошибка MySQL. Пожалуйста, сообщите разработчику.", 0); }
  return !err;
}

void __fastcall TMySQL_work::GetReportYears()
{
  query = "SELECT year(dt_inspection) FROM inspection GROUP BY year(dt_inspection) DESC";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    ReportForm->YearBox->Clear();
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      ReportForm->YearBox->Items->Add(row[0]);
    }
  }
}

void __fastcall TMySQL_work::GetRefbooks()
{
  query = "SELECT level FROM budget_level";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      InputForm->SGrid->Cells[5-i][0] = row[0];
      ReportForm->SGrid->Cells[5-i][0] = row[0];
    }
  }
  InputForm->SGrid->Cells[5][0] = "Сумма";
  ReportForm->SGrid->Cells[5][0] = "Всего";

  query = "SELECT name FROM data_gr1";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      InputForm->RGroup1->Items->Add(row[0]);
    }
  }

  query = "SELECT name FROM data_gr2";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      InputForm->RGroup2->Items->Add(row[0]);
    }
  }

  query = "SELECT name FROM contraventions";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      ReportForm->SGrid->Cells[0][14-i] = row[0];
    }
  }

  query = "SELECT name FROM reasons";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    for (int i = mysql_num_rows(result); i > 0; i--) {
      row = mysql_fetch_row(result);
      InputForm->MotivBox->Items->Add(row[0]);
      ReportForm->SGrid2->Cells[0][4-i] = row[0];
    }
  }
}

//---------------------------------------------------------------------------

bool __fastcall TMySQL_work::GetInspectors()
{
  query = "SELECT * FROM inspector ORDER BY surname DESC, name DESC, patronymic DESC";
  if (Query(query.c_str())) {
    result = mysql_store_result(dbCnt);
    MainForm->Insp->free();
    for (int i = mysql_num_rows(result)-1; i >= 0; i--) {
      row = mysql_fetch_row(result);
      MainForm->Insp->data = new inspdata;
      MainForm->Insp->data->dbi = atoi(row[0]);
      MainForm->Insp->data->ind = i;
      MainForm->Insp->data->fio = AnsiString(row[1])+" "+AnsiString(row[2])+" "+AnsiString(row[3]);
      MainForm->Insp->data->pwd = row[4];
      MainForm->Insp->push();
    }
    return true;
  } else return false;
}

//---------------------------------------------------------------------------

void __fastcall TMySQL_work::AddUser(AnsiString a1, AnsiString a2, AnsiString a3, AnsiString a4)
{
  query = "INSERT INTO `inspector` (`surname`, `name`, `patronymic`, `pwd`) VALUES ('"+a1+"','"+a2+"','"+a3+"','"+a4+"')";
  if (Query(query.c_str())) GetInspectors();
}

//---------------------------------------------------------------------------

bool __fastcall TMySQL_work::TryConnect()
{
  dbCnt = mysql_init(NULL);
  return mysql_real_connect(dbCnt, host.c_str(), user.c_str(), pass.c_str(), dbnm.c_str(), port == 0 ? 3306 : port, NULL, 0);
}

//---------------------------------------------------------------------------

bool __fastcall TMainForm::TryGetOptions()
{
  HKLMOpt->OpenKey("software\\InspectorClient", true);
  if(HKLMOpt->ValueExists("DBHost")
  && HKLMOpt->ValueExists("DBUser")
  && HKLMOpt->ValueExists("DBPass")
  && HKLMOpt->ValueExists("DBName")) {
    DB->port = HKLMOpt->ReadInteger("DBPort");
    DB->host = HKLMOpt->ReadString("DBHost");
    DB->user = HKLMOpt->ReadString("DBUser");
    DB->pass = HKLMOpt->ReadString("DBPass");
    DB->dbnm = HKLMOpt->ReadString("DBName");
    HKLMOpt->CloseKey();
    return true;
  } else {
    HKLMOpt->CloseKey();
    return false;
  }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GetPositions()
{
  HKLMOpt->OpenKey("software\\InspectorClient", true);
  if (HKLMOpt->ValueExists("ML") && HKLMOpt->ValueExists("MT")) {
    Left = HKLMOpt->ReadInteger("ML");
    Top = HKLMOpt->ReadInteger("MT");
  }
  if (HKLMOpt->ValueExists("IL") && HKLMOpt->ValueExists("IT")) {
    IL = HKLMOpt->ReadInteger("IL");
    IT = HKLMOpt->ReadInteger("IT");
  }
  if (HKLMOpt->ValueExists("JL") && HKLMOpt->ValueExists("JT")) {
    JL = HKLMOpt->ReadInteger("JL");
    JT = HKLMOpt->ReadInteger("JT");
  }
  if (HKLMOpt->ValueExists("RL") && HKLMOpt->ValueExists("RT")) {
    RL = HKLMOpt->ReadInteger("RL");
    RT = HKLMOpt->ReadInteger("RT");
  }
  HKLMOpt->CloseKey();
}

void __fastcall TMainForm::SavePositions()
{
  HKLMOpt->OpenKey("software\\InspectorClient", true);
  HKLMOpt->WriteInteger("ML", Left);
  HKLMOpt->WriteInteger("MT", Top);
  HKLMOpt->WriteInteger("IL", IL);
  HKLMOpt->WriteInteger("IT", IT);
  HKLMOpt->WriteInteger("JL", JL);
  HKLMOpt->WriteInteger("JT", JT);
  HKLMOpt->WriteInteger("RL", RL);
  HKLMOpt->WriteInteger("RT", RT);
  HKLMOpt->CloseKey();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::PrintLabel()
{
  LabelConnection->Caption = DB->user + "@" + DB->host + ":" + (DB->port == 0 ? 3306 : DB->port);
  LabelConnection->Canvas;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   Insp = new Tinsp;
   Insp->head = NULL;
   EnterBtn->Enabled = false;
   HKLMOpt = new TRegistry();
   HKLMOpt->RootKey = HKEY_CURRENT_USER;
   GetPositions();
   DB = new TMySQL_work();
   DB->Connected = false;
   Entered = false;
   if (TryGetOptions()) PrintLabel();
   Caption = (AnsiString)"Ревизор " + PVersion;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::MMExitClick(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------

void TMainForm::ChngEnbl(bool x) {
  AddBtn->Enabled = x;
//  DelBtn->Enabled = x;
  InputBtn->Enabled = x;
  JournalBtn->Enabled = x;
  ReportBtn->Enabled = x;
  Entered = x;
  if (x) {
    InspListBox->Enabled = false;
    EnterBtn->Caption = "Сменить пользователя";
  } else {
    EnterBtn->Enabled = false;
    EnterBtn->Caption = "Авторизация";
  }
}

void TMainForm::Clrrr()
{
  JournalForm->Close();
  InputForm->Close();
  ReportForm->Close();
  InspListBox->Clear();
  PrintLabel();
  ChngEnbl(false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ConnectBtnClick(TObject *Sender)
{
  if (DB->Connected) {
    DB->Close();
    MMConnect->Caption = "Подключиться";
    ConnectBtn->Caption = "Подключиться";
    InputForm->RGroup1->Items->Clear();
    InputForm->RGroup2->Items->Clear();
    InspListBox->Enabled = false;
    Clrrr();
  } else if (!TryGetOptions()) OptionsOpen();
         else if ( DB->TryConnect() )
  {
    DB->Connected = true;
    MMConnect->Caption = "Отключиться";
    ConnectBtn->Caption = "Отключиться";
    LabelConnection->Caption = (AnsiString)LabelConnection->Caption + "   MySQL v" + mysql_get_server_info(DB->dbCnt);
    DB->Query("SET NAMES 'cp1251'");
    DB->GetRefbooks();
    if (DB->GetInspectors()) {
      InspListBox->Enabled = true;
      InspListBox->Text = "Выберите пользователя из списка";
      rlist *tmp = MainForm->Insp->head;
      while (tmp) {
        InspListBox->Items->Add(tmp->data->fio);
        tmp = tmp->next;
      }
    }
  } else MessageBox(0, mysql_error(DB->dbCnt), "Ошибка: подключение невозможно", 0);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::OptionsOpen()
{
  OptionsForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::MMOptionsClick(TObject *Sender)
{
  OptionsOpen();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
  SavePositions();
  if (DB->Connected) mysql_close(DB->dbCnt);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AddBtnClick(TObject *Sender)
{
  AddUserForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InspListBoxSelect(TObject *Sender)
{
  EnterBtn->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InspListBoxChange(TObject *Sender)
{
  EnterBtn->Enabled = false;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::InputBtnClick(TObject *Sender)
{
  if (InputForm->Visible) InputForm->SetFocus();
  else InputForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EnterBtnClick(TObject *Sender)
{

  if (Entered) {
    Clrrr();
    if (DB->GetInspectors()) {
      InspListBox->Enabled = true;
      InspListBox->Text = "Выберите пользователя из списка";
      rlist *tmp = MainForm->Insp->head;
      while (tmp) {
        InspListBox->Items->Add(tmp->data->fio);
        tmp = tmp->next;
      }
    }
  } else {
    rlist *tmp = Insp->head;
    while (tmp->data->ind != InspListBox->ItemIndex) tmp = tmp->next;
    InputForm->id_inspector_m = tmp->data->dbi;
    PwdForm->correctpass = tmp->data->pwd;
    PwdForm->Show();
  }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InspListBoxKeyPress(TObject *Sender, char &Key)
{
  if (Key == char(13) && EnterBtn->Enabled) EnterBtnClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::JournalBtnClick(TObject *Sender)
{
  if (JournalForm->Visible) JournalForm->SetFocus();
  else JournalForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ReportBtnClick(TObject *Sender)
{
  if (ReportForm->Visible) ReportForm->SetFocus();
  else ReportForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::MMAboutClick(TObject *Sender)
{
  AnsiString s = (AnsiString)"Ревизор - клиент\nверсия " + PVersion + "\n\nПо всем вопросам: st.pletnev@gmail.com";
  MessageBox(0, s.c_str(), "О программе", 0);
}

//---------------------------------------------------------------------------
// int ur;
//  MainForm->Visible = false;
//  do {
//    do { } while (MessageBox(0, "Вы с этим смиритесь?                          ", "Функция в разработке", 4) != mrYes);
//  } while (MessageBox(0, "Повторить вопрос?                             ", "Функция в разработке", 5) == mrRetry);
//  MainForm->Visible = true;


//  do {
//    ur = MessageBox(0, "Удалить все файлы на компьютере?", "Внимание!", 4);
//  } while (ur != mrYes);


//MessageBox(0, "ОК", "0", 0);
//MessageBox(0, "ОК Отмена", "1", 1);
//MessageBox(0, "Прервать Повтор Пропустить Х", "2", 2);
//MessageBox(0, "Да Нет Отмена", "3", 3);
//MessageBox(0, "Да Нет Х", "4", 4);
//MessageBox(0, "Повтор Отмена", "5", 5);
//MessageBox(0, "Отмена Повторить Продолжить", "6", 6);


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

