//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
#include "Unit1.h"
#include "Unit6.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReportForm *ReportForm;
//---------------------------------------------------------------------------
__fastcall TReportForm::TReportForm(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TReportForm::FormShow(TObject *Sender)
{
  MainForm->DB->GetReportYears();
}

//---------------------------------------------------------------------------
void __fastcall TReportForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  for (int i = 1; i < 6; i++)
   for (int j = 1; j < 14; j++) SGrid->Cells[i][j] = "";
  for (int i = 0; i < 4; i++) SGrid2->Cells[1][i] = "";
  ReportBtn->Enabled = false;
  PrintBtn->Enabled = false;
  SaveBtn->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TReportForm::ReportBtnClick(TObject *Sender)
{
  byte i, j;
  for (i = 0; i < 4; i++)
   for (j = 0; j < 13; j++) proto3data[i][j] = 0;
  YEAR = YearBox->Items->Strings[YearBox->ItemIndex];
  AnsiString query1 = "SELECT SUM(d1), SUM(d2), SUM(d3), SUM(d4), SUM(d5), SUM(d6), SUM(d7), SUM(d8), SUM(d9), SUM(d10), SUM(d11), SUM(d12), SUM(d13), SUM(d14), SUM(d15), SUM(d16) FROM inspection_budget_year";
  AnsiString query2 = "SELECT SUM(d1), SUM(d2), SUM(d3), SUM(d4), SUM(d5), SUM(d6), SUM(d7) FROM inspection_budget";
  AnsiString queryx = " WHERE id_inspection IN (SELECT id_inspection FROM inspection WHERE YEAR(dt_inspection)="+YEAR+") GROUP BY id_budget_lvl";

  AnsiString query3 = "SELECT motivation, COUNT(id_inspection) FROM inspection WHERE YEAR(dt_inspection)="+YEAR+" GROUP BY motivation";
  query1 += queryx;
  query2 += queryx;
  MYSQL_RES *result;
  MYSQL_ROW row;
  if (MainForm->DB->Query(query3.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    for (i = 0; i < 4; i++) SGrid2->Cells[1][i] = "0";
    for (i = 0; i < mysql_num_rows(result); i++) {
      row = mysql_fetch_row(result);
      if (atoi(row[0])) SGrid2->Cells[1][atoi(row[0])-1] = row[1];
    }
  }
  if (MainForm->DB->Query(query1.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    for (i = 0; i < mysql_num_rows(result); i++) {
      row = mysql_fetch_row(result);
      for (j = 0; j < 16; j++) proto1data[i][j] = atof(row[j]);
    }
  }
  if (MainForm->DB->Query(query2.c_str())) {
    result = mysql_store_result(MainForm->DB->dbCnt);
    for (i = 0; i < mysql_num_rows(result); i++) {
      row = mysql_fetch_row(result);
      for (j = 0; j < 7; j++) proto2data[i][j] = atof(row[j]);
    }
  }
  for (i = 0; i < 4; i++) proto3data[i][0] = proto1data[i][15];
  for (i = 0; i < 4; i++) {
    double tmp = 0;
    for (j = 0; j < 13; j++) tmp += proto1data[i][j];
    proto3data[i][3] = tmp;
  }
  for (i = 0; i < 4; i++) proto3data[i][4] = proto1data[i][13];
  for (i = 0; i < 4; i++) proto3data[i][5] = proto1data[i][14];
  for (i = 0; i < 4; i++) for (j = 3; j < 6; j++) proto3data[i][1] += proto3data[i][j];
  for (i = 0; i < 4; i++) proto3data[i][2] = proto1data[i][4];

  for (i = 0; i < 4; i++) proto3data[i][6] = proto2data[i][0] + proto2data[i][1];
  for (i = 0; i < 4; i++) proto3data[i][7] = proto2data[i][3];
  for (i = 0; i < 4; i++) proto3data[i][8] = proto2data[i][4];
  for (i = 0; i < 4; i++) proto3data[i][9] = proto2data[i][0];
  for (i = 0; i < 4; i++) proto3data[i][10] = proto2data[i][1];
  for (i = 0; i < 4; i++) proto3data[i][11] = proto2data[i][5];
  for (i = 0; i < 4; i++) proto3data[i][12] = proto2data[i][6];

  for (j = 0; j < 13; j++) {
    double tmp = 0;
    for (i = 0; i < 4; i++) {
      SGrid->Cells[i+1][j+1] = proto3data[i][j];
      tmp += proto3data[i][j];
    }
    SGrid->Cells[5][j+1] = tmp;
  }
  PrintBtn->Enabled = true;
  SaveBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::YearBoxSelect(TObject *Sender)
{
  ReportBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::YearBoxChange(TObject *Sender)
{
  ReportBtn->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::PrintBtnClick(TObject *Sender)
{
  Printer()->BeginDoc();
  Printer()->Canvas->Pen->Width=5;
  Printer()->Canvas->Font->Size=20;
  Printer()->Canvas->TextOutA(100, 100, "Отчет за "+YEAR+" год.");
  Printer()->Canvas->Font->Size=8;
  int i, j, x1, x2, y1, y2 = 480;
  for (i = 0; i < SGrid->RowCount; i++)
  {
    y1 = y2;
    y2 += SGrid->RowHeights[i]*6;
    x1 = x2 = 100;
    for (j = 0; j < 6; j++)
    {
       x2 += SGrid->ColWidths[j]*6+20;
       if (i != 0 || j != 0) Printer()->Canvas->Rectangle(x1, y1, x2, y2);
       Printer()->Canvas->TextOutA(x1+28, y1+38, SGrid->Cells[j][i]);
       x1 = x2;
    }
  }
  y2 += 300;
  x1 -= SGrid->ColWidths[5]*6+20;
  for (i = 0; i < SGrid2->RowCount; i++)
  {
    y1 = y2;
    y2 += SGrid2->RowHeights[i]*6;
    Printer()->Canvas->Rectangle(100, y1, x1, y2);
    Printer()->Canvas->Rectangle(x1, y1, x2, y2);
    Printer()->Canvas->TextOutA(128, y1+38, SGrid2->Cells[0][i]);
    Printer()->Canvas->TextOutA(x1+28, y1+38, SGrid2->Cells[1][i]);
  }
  Printer()->EndDoc();
}
//---------------------------------------------------------------------------

AnsiString GetLetter(int x)
{
  char c1 = x % 26 + 65;
  char c2 = x / 26 + 64;
  if (c2 == 64)  return c1;
  else return AnsiString(c2) + AnsiString(c1);
}

void __fastcall TReportForm::SaveBtnClick(TObject *Sender)
{
  SaveDlg->FileName = "Отчет"+YEAR;
  int i, j, k, NY, xx, YInd[100];
  bool allGood = true;
  if (SaveDlg->Execute()) {
    if (GetFileAttributes(SaveDlg->FileName.c_str()) != (DWORD)-1) {
      int ur = MessageBox(0, "Такой файл уже существует. Заменить существующий файл?", "Сохранить отчет", 4);
      if (ur == mrYes) {
        if (!DeleteFile(SaveDlg->FileName.c_str())) {
          MessageBox(0, "Не удается получить доступ к файлу. Возможно, он занят другим процессом. Так, например, он может быть открыт в Excel.\nПожалуйста, удалите файл самостоятельно, или выберите другое имя файла.", "Ошибка удаления", 0);
          allGood = false;
        }
      } else allGood = false;
    }
  } else allGood = false;
  if (allGood) {
    vApp=CreateOleObject("Excel.Application");
    vApp.OlePropertySet("Visible", false);
    vApp.OlePropertySet("SheetsInNewWorkbook", 3);
    vApp.OlePropertyGet("Workbooks").OleProcedure("Add");
    vBook=vApp.OlePropertyGet("Workbooks").OlePropertyGet("Item", 1);
// -------!!!------- Лист1 -------!!!------- //
    vSheet=vBook.OlePropertyGet("Worksheets").OlePropertyGet("Item", 1);
    vCells=vSheet.OlePropertyGet("Cells");
    vSheet.OlePropertySet("Name", ("Протоколы"+YEAR).c_str());
    vSheet.OleProcedure("Activate");

//Cells default
    vCells.OlePropertyGet("Font").OlePropertySet("Size", 8);
    vCells.OlePropertyGet("Font").OlePropertySet("Name", "Times New Roman");
    vCells.OlePropertySet("VerticalAlignment", -4108);
    vCells.OlePropertySet("RowHeight", 16);
    vCells.OlePropertySet("WrapText", true);
    vCells.OlePropertySet("ColumnWidth", 10.2);
    vCells.OlePropertySet("NumberFormat", "# ##0,00;[красный]-# ##0,00; ");

//--- Шапка

    MYSQL_RES *result, *result2;
    MYSQL_ROW row1, row2;
    AnsiString query = "SELECT year FROM inspection_budget_year WHERE id_inspection IN (SELECT id_inspection FROM inspection WHERE YEAR(dt_inspection)="+YEAR+") GROUP BY year ORDER BY year ASC";
    if (MainForm->DB->Query(query.c_str())) {
      result = mysql_store_result(MainForm->DB->dbCnt);
      NY = mysql_num_rows(result)+1;
      for (j = 0; j < 19; j++) {
        vCell=vCells.OlePropertyGet("Item", 3, 8+j*NY);
        vCell.OlePropertySet("Value", "Всего");
      }
      for (i = 0; i < NY-1; i++) {
        row1 = mysql_fetch_row(result);
        YInd[atoi(row1[0])-1990] = i;
        for (j = 0; j < 19; j++) {
          vCell=vCells.OlePropertyGet("Item", 3, 9+j*NY+i);
          vCell.OlePropertySet("Value", row1[0]);
          vCell.OlePropertySet("NumberFormat", "####");
        }
      }
    }

    vCell=vCells.OlePropertyGet("Item", 2, 1);
    vCell.OlePropertySet("RowHeight", 24);

    for (i = 0; i < 7; i++) {
      vCell=vSheet.OlePropertyGet("Range", (GetLetter(i)+"1:"+GetLetter(i)+"2").c_str());
      vCell.OleProcedure("Merge");
    }

    vCell=vCells.OlePropertyGet("Item", 1, 1);
    vCell.OlePropertySet("Value", "№ п/п");
    vCell.OlePropertySet("ColumnWidth", 7);

    vCell=vCells.OlePropertyGet("Item", 1, 2);
    vCell.OlePropertySet("Value", "№ дела");

    vCell=vCells.OlePropertyGet("Item", 1, 3);
    vCell.OlePropertySet("Value", "Наименование проверки");
    vCell.OlePropertySet("ColumnWidth", 20);

    vCell=vCells.OlePropertyGet("Item", 1, 4);
    vCell.OlePropertySet("Value", "Основание проверки");
    vCell.OlePropertySet("ColumnWidth", 20);

    vCell=vCells.OlePropertyGet("Item", 1, 5);
    vCell.OlePropertySet("Value", "Руководитель ревизорской группы");
    vCell.OlePropertySet("ColumnWidth", 20);

    vCell=vCells.OlePropertyGet("Item", 1, 6);
    vCell.OlePropertySet("Value", "Проверяемый период");
    vCell.OlePropertySet("ColumnWidth", 20);

    vCell=vCells.OlePropertyGet("Item", 1, 7);
    vCell.OlePropertySet("Value", "Уровни бюджетов");

    vCell=vCells.OlePropertyGet("Item", 1, 8);
    vCell.OlePropertySet("Value", "Общий объем проверенных средств");

    vCell=vCells.OlePropertyGet("Item", 1, 8+NY);
    vCell.OlePropertySet("Value", "Общая сумма нарушений");

    for (i = 2; i < 17; i++) {
      vCell=vCells.OlePropertyGet("Item", 1, 8+i*NY);
      vCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex", 20);
      vCell.OlePropertySet("Value", InputForm->RGroup1->Items[0][i-2].c_str());
    }

    for (i = 0; i < 19; i++) {
      vCell=vSheet.OlePropertyGet("Range", (GetLetter(i*NY+7)+"1:"+GetLetter(i*NY+6+NY)+"2").c_str());
      vCell.OleProcedure("Merge");
    }

    vCell=vCells.OlePropertyGet("Item", 1, 17*NY+8);
    vCell.OlePropertySet("Value", "Всего финансовых нарушений");
    vCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex", 36);
    vCell=vCells.OlePropertyGet("Item", 1, 18*NY+8);
    vCell.OlePropertySet("Value", "Всего нефинансовых нарушений");
    vCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex", 36);

    vCell=vSheet.OlePropertyGet("Range", (GetLetter(19*NY+7)+"1:"+GetLetter(19*NY+9)+"1").c_str());
    vCell.OleProcedure("Merge");
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+8);
    vCell.OlePropertySet("Value", "Устранено нарушений");
    vCell=vCells.OlePropertyGet("Item", 2, 19*NY+8);
    vCell.OlePropertySet("Value", "Всего");
    vCell=vCells.OlePropertyGet("Item", 2, 19*NY+9);
    vCell.OlePropertySet("Value", "Зачет нецелевых");
    vCell=vCells.OlePropertyGet("Item", 2, 19*NY+10);
    vCell.OlePropertySet("Value", "Возмещено в бюджеты");

    for (j = 0; j < 6; j++) {
      vCell=vSheet.OlePropertyGet("Range", (GetLetter(19*NY+10+j)+"1:"+GetLetter(19*NY+10+j)+"2").c_str());
      vCell.OleProcedure("Merge");
    }

    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+11);
    vCell.OlePropertySet("Value", "Внесены изменения в РЦП");
    vCell.OlePropertySet("ColumnWidth", 12);
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+12);
    vCell.OlePropertySet("Value", "Неустранимые");
    vCell.OlePropertySet("ColumnWidth", 12);
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+13);
    vCell.OlePropertySet("Value", "Не устранено");
    vCell.OlePropertySet("ColumnWidth", 12);
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+14);
    vCell.OlePropertySet("Value", "Наложены штрафы");
    vCell.OlePropertySet("ColumnWidth", 12);
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+15);
    vCell.OlePropertySet("Value", "Уплачены штрафы");
    vCell.OlePropertySet("ColumnWidth", 12);
    vCell=vCells.OlePropertyGet("Item", 1, 19*NY+16);
    vCell.OlePropertySet("Value", "Примечание");
    vCell.OlePropertySet("ColumnWidth", 56);

//Объединение пустот
    vCell=vSheet.OlePropertyGet("Range", "A3:G3");
    vCell.OleProcedure("Merge");
    vCell=vSheet.OlePropertyGet("Range", (GetLetter(19*NY+7)+"3:"+GetLetter(19*NY+15)+"3").c_str());
    vCell.OleProcedure("Merge");

//Форматирование всей шапки
    vCell=vSheet.OlePropertyGet("Range", ("A1:"+GetLetter(19*NY+15)+"3").c_str());
    vCell.OlePropertyGet("Font").OlePropertySet("Bold", true);
    vCell.OlePropertySet("HorizontalAlignment", -4108);
    vCell.OlePropertyGet("Borders", 10).OlePropertySet("Weight", 3);
    vCell.OlePropertyGet("Borders", 12).OlePropertySet("Weight", 3);
    vCell.OlePropertyGet("Borders", 11).OlePropertySet("Weight", 2);
//--- Конец щапки

    query = "SELECT inspection.id_inspection, inspection.name, reasons.name, CONCAT_WS(' ', inspector.surname, inspector.name, inspector.patronymic), inspection.dt_pbegin, inspection.dt_pend, inspection.comment FROM inspection, reasons, inspector WHERE inspection.motivation=reasons.id AND inspection.id_director=inspector.id_inspector AND YEAR(inspection.dt_inspection)="+YEAR+" ORDER BY inspection.id_inspection";
    if (MainForm->DB->Query(query.c_str())) {
      result = mysql_store_result(MainForm->DB->dbCnt);
      int xxl = mysql_num_rows(result);
      ProgressBar->Min = 0;
      ProgressBar->Max = xxl+1;
      for (xx = 0; xx <= xxl; xx++) {
        if (xx != xxl) {
          row1 = mysql_fetch_row(result);
          for (j = 0; j < 6; j++) {
            vCell=vSheet.OlePropertyGet("Range", (GetLetter(j)+AnsiString(xx*5+4)+":"+GetLetter(j)+AnsiString(xx*5+8)).c_str());
            vCell.OleProcedure("Merge");
            vCell.OlePropertySet("NumberFormat", "####");
          }
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 1);
          vCell.OlePropertySet("Value", row1[0]);
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 3);
          vCell.OlePropertySet("Value", row1[1]);
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 4);
          vCell.OlePropertySet("Value", row1[2]);
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 5);
          vCell.OlePropertySet("Value", row1[3]);
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 6);
          vCell.OlePropertySet("Value", ("c "+AnsiString(row1[4])+" по "+AnsiString(row1[5])).c_str());
          vCell=vSheet.OlePropertyGet("Range", (GetLetter(19*NY+15)+AnsiString(xx*5+4)+":"+GetLetter(19*NY+15)+AnsiString(xx*5+8)).c_str());
          vCell.OleProcedure("Merge");
          AnsiString comment = row1[6];
          for (j = 1; j <= comment.Length(); j++)
            if (comment[j] == '#') comment[j] = ' ', comment[++j] = '\n';
          vCell.OlePropertySet("Value", comment.c_str());

          query = "SELECT * FROM inspection_budget_year WHERE id_inspection="+AnsiString(row1[0])+" ";
          if (MainForm->DB->Query(query.c_str())) {
            result2 = mysql_store_result(MainForm->DB->dbCnt);
            for (i = 0; i < mysql_num_rows(result2); i++) {
              row2 = mysql_fetch_row(result2);
              vCell=vCells.OlePropertyGet("Item", xx*5+4+atoi(row2[1]), 9+NY+YInd[atoi(row2[2])-1990]);
              vCell.OlePropertySet("Value", atof(row2[18]));
              for (j = 3; j < 18; j++) {
                vCell=vCells.OlePropertyGet("Item", xx*5+4+atoi(row2[1]), 9+j*NY+YInd[atoi(row2[2])-1990]);
                vCell.OlePropertySet("Value", atof(row2[j]));
              }
            }
          }
          query = "SELECT * FROM inspection_budget WHERE id_inspection="+AnsiString(row1[0])+" ";
          if (MainForm->DB->Query(query.c_str())) {
            result2 = mysql_store_result(MainForm->DB->dbCnt);
            for (i = 0; i < mysql_num_rows(result2); i++) {
              row2 = mysql_fetch_row(result2);
              for (j = 2; j < 9; j++) {
                vCell=vCells.OlePropertyGet("Item", xx*5+4+atoi(row2[1]), 7+NY*19+j);
                vCell.OlePropertySet("Value", atof(row2[j]));
              }
            }
          }
        } else {
          vCell=vSheet.OlePropertyGet("Range", ("A"+AnsiString(xx*5+4)+":"+"F"+AnsiString(xx*5+8)).c_str());
          vCell.OleProcedure("Merge");
          vCell.OlePropertyGet("Font").OlePropertySet("Bold", true);
          vCell.OlePropertySet("HorizontalAlignment", -4108);
          vCell.OlePropertySet("Value", ("Итого за "+YEAR+" год").c_str());
          vCell=vSheet.OlePropertyGet("Range", (GetLetter(NY*19+15)+AnsiString(xx*5+4)+":"+GetLetter(NY*19+15)+AnsiString(xx*5+8)).c_str());
          vCell.OleProcedure("Merge");
          query = "SELECT id_budget_lvl, year, SUM(d1), SUM(d2), SUM(d3), SUM(d4), SUM(d5), SUM(d6), SUM(d7), SUM(d8), SUM(d9), SUM(d10), SUM(d11), SUM(d12), SUM(d13), SUM(d14), SUM(d15), SUM(d16) FROM inspection_budget_year WHERE id_inspection IN (SELECT id_inspection FROM inspection WHERE YEAR(dt_inspection)="+YEAR+") GROUP BY id_budget_lvl, year";
          if (MainForm->DB->Query(query.c_str())) {
            result2 = mysql_store_result(MainForm->DB->dbCnt);
            for (i = 0; i < mysql_num_rows(result2); i++) {
              row2 = mysql_fetch_row(result2);
              vCell=vCells.OlePropertyGet("Item", xx*5+4+atoi(row2[0]), 9+NY+YInd[atoi(row2[1])-1990]);
              vCell.OlePropertySet("Value", atof(row2[17]));
              for (j = 2; j < 17; j++) {
                vCell=vCells.OlePropertyGet("Item", xx*5+4+atoi(row2[0]), 9+j*NY+NY+YInd[atoi(row2[1])-1990]);
                vCell.OlePropertySet("Value", atof(row2[j]));
              }
            }
          }
          query = "SELECT SUM(d1), SUM(d2), SUM(d3), SUM(d4), SUM(d5), SUM(d6), SUM(d7) FROM inspection_budget WHERE id_inspection IN (SELECT id_inspection FROM inspection WHERE YEAR(dt_inspection)="+YEAR+") GROUP BY id_budget_lvl ORDER BY id_budget_lvl";
          if (MainForm->DB->Query(query.c_str())) {
            result2 = mysql_store_result(MainForm->DB->dbCnt);
            for (i = 0; i < mysql_num_rows(result2); i++) {
              row2 = mysql_fetch_row(result2);
              for (j = 0; j < 7; j++) {
                vCell=vCells.OlePropertyGet("Item", xx*5+5+i, 9+NY*19+j);
                vCell.OlePropertySet("Value", atof(row2[j]));
              }
            }
          }
        } //end else
//        int carr[4] = {15455409, 12303591, 12445144, 14731988};
        int carr[4] = {17, 38, 35, 39};
        for (i = 0; i < 4; i++) {
          vCell=vSheet.OlePropertyGet("Range", ("G"+AnsiString(xx*5+i+5)+":"+GetLetter(19*NY+14)+AnsiString(xx*5+i+5)).c_str());
          vCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex", carr[i]);
        }

        for (j = 1; j <= 5; j++) {
          vCell=vCells.OlePropertyGet("Item", xx*5+4+j%5, 7);
          vCell.OlePropertySet("Value", SGrid->Cells[j][0].c_str());
        }
/**/
        for (i = 0; i < 19; i++) {
          for (j = 0; j < 5; j++) {
            vCell=vCells.OlePropertyGet("Item", xx*5+4+j, 8+i*NY);
            vCell.OlePropertySet("Value", ("=СУММ("+GetLetter(8+i*NY)+AnsiString(xx*5+4+j)+":"+GetLetter(6+i*NY+NY)+AnsiString(xx*5+4+j)+")").c_str());
          }
          for (j = 1; j < NY; j++) {
            vCell=vCells.OlePropertyGet("Item", xx*5+4, 8+i*NY+j);
            vCell.OlePropertySet("Value", ("=СУММ("+GetLetter(7+i*NY+j)+AnsiString(xx*5+5)+":"+GetLetter(7+i*NY+j)+AnsiString(xx*5+8)+")").c_str());
          }
        }
        for (i = 1; i < NY; i++) for (j = 1; j < 5; j++) {
           vCell=vCells.OlePropertyGet("Item", xx*5+4+j, 8+NY+i);
           AnsiString tmp = "";
           for (k = 2; k < 17; k++) {
             tmp += "+"+GetLetter(7+NY*k+i)+AnsiString(xx*5+4+j);
           }
           tmp[1] = '=';
           vCell.OlePropertySet("Value", tmp.c_str());
           vCell=vCells.OlePropertyGet("Item", xx*5+4+j, 8+18*NY+i);
           vCell.OlePropertySet("Value", ("="+GetLetter(7+NY*15+i)+AnsiString(xx*5+4+j)+"+"+GetLetter(7+NY*16+i)+AnsiString(xx*5+4+j)).c_str());
           vCell=vCells.OlePropertyGet("Item", xx*5+4+j, 8+17*NY+i);
           vCell.OlePropertySet("Value", ("="+GetLetter(7+NY+i)+AnsiString(xx*5+4+j)+"-"+GetLetter(7+NY*18+i)+AnsiString(xx*5+4+j)).c_str());
        }
        for (i = 0; i < 8; i++) {
          vCell=vCells.OlePropertyGet("Item", xx*5+4, 8+19*NY+i);
          vCell.OlePropertySet("Value", ("=СУММ("+GetLetter(7+19*NY+i)+AnsiString(xx*5+5)+":"+GetLetter(7+19*NY+i)+AnsiString(xx*5+8)+")").c_str());
        }
        for (i = 0; i < 4; i++) {
          vCell=vCells.OlePropertyGet("Item", xx*5+5+i, 8+19*NY);
          vCell.OlePropertySet("Value", ("="+GetLetter(8+19*NY)+AnsiString(xx*5+5+i)+"+"+GetLetter(9+19*NY)+AnsiString(xx*5+5+i)).c_str());
        }
/**/
        vCell=vSheet.OlePropertyGet("Range", ("A"+AnsiString(xx*5+4)+":"+GetLetter(19*NY+15)+AnsiString(xx*5+8)).c_str());
        vCell.OlePropertyGet("Borders", 8).OlePropertySet("Weight", 3);
        vCell.OlePropertyGet("Borders", 10).OlePropertySet("Weight", 3);
        vCell.OlePropertyGet("Borders", 11).OlePropertySet("Weight", 2);
        vCell.OlePropertyGet("Borders", 12).OlePropertySet("Weight", 2);
        ProgressBar->Position = xx+1;
      }
      vCell.OlePropertyGet("Borders", 9).OlePropertySet("Weight", 3);
    }

    vSheet=vBook.OlePropertyGet("Worksheets").OlePropertyGet("Item", 3);
    vSheet.OlePropertySet("Name", "Цвета");
    vSheet.OleProcedure("Activate");
    for (i = 1; i < 57; i++) {
      vCell=vSheet.OlePropertyGet("Range", ("A"+AnsiString(i)+":"+"A"+AnsiString(i)).c_str());
      vCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex", i);
      vCell.OlePropertySet("Value", AnsiString(i).c_str());
    }
/**/

// -------!!!------- Лист2 -------!!!------- //
    vSheet=vBook.OlePropertyGet("Worksheets").OlePropertyGet("Item", 2);
    vCells=vSheet.OlePropertyGet("Cells");
    vSheet.OlePropertySet("Name", ("Отчет"+YEAR).c_str());
    vSheet.OleProcedure("Activate");

//Cells default
    vCells.OlePropertyGet("Font").OlePropertySet("Size", 8);
    vCells.OlePropertyGet("Font").OlePropertySet("Name", "Times New Roman");
    vCells.OlePropertySet("RowHeight", 18); //16?
    vCells.OlePropertySet("ColumnWidth", 10.2);
    vCells.OlePropertySet("VerticalAlignment", -4108);
    vCells.OlePropertySet("NumberFormat", "# ##0,00;[красный]-# ##0,00; ");


// ------- Заголовок
    vCell=vSheet.OlePropertyGet("Range", "A1:N1");
    vCell.OleProcedure("Merge");
    vCell.OlePropertyGet("Borders", 9).OlePropertySet("Weight", 3);

    vCell=vCells.OlePropertyGet("Item", 1, 1);
    vCell.OlePropertySet("RowHeight", 30);
    vCell.OlePropertySet("HorizontalAlignment", -4108);
    vCell.OlePropertySet("VerticalAlignment", -4108);
    vCell.OlePropertyGet("Font").OlePropertySet("Size", 15);
    vCell.OlePropertyGet("Font").OlePropertySet("Bold", true);
    vCell.OlePropertySet("Value", ("ОТЧЕТ СЛУЖБЫ ПО ФИНАНСОВО-БЮДЖЕТНОМУ НАДЗОРУ РЕСПУБЛИКИ ТЫВА ЗА "+YEAR+" ГОД").c_str());

// ------- Таблица1
    for (i = 3; i < 8; i++) {
      vCell=vSheet.OlePropertyGet("Range", ("A"+AnsiString(i)+":G"+AnsiString(i)).c_str());
      vCell.OleProcedure("Merge");
    }

//Данные
    for (i = 0; i < 4; i++)
      for (j = 0; j < 2; j++) {
        vCell=vCells.OlePropertyGet("Item", i+3, j*7+1);
        vCell.OlePropertySet("Value", SGrid2->Cells[j][i].c_str());
      }
    vCell=vCells.OlePropertyGet("Item", 7, 1);
    vCell.OlePropertySet("Value", ("ВСЕГО в "+YEAR+"г. проведено проверок:").c_str());
    vCell=vCells.OlePropertyGet("Item", 7, 8);
    vCell.OlePropertySet("Value", "=СУММ(H3:H6)");

//Рамка
    vCell=vSheet.OlePropertyGet("Range", "A3:H7");
    for (i = 7; i < 11; i++) vCell.OlePropertyGet("Borders", i).OlePropertySet("Weight", 3);
    vCell.OlePropertyGet("Borders", 11).OlePropertySet("Weight", 2);
    vCell.OlePropertyGet("Borders", 12).OlePropertySet("Weight", 2);

// ------- Таблица 2

//Данные
    for (i = 0; i < 14; i++)
      for (j = 0; j < 6; j++) {
        vCell=vCells.OlePropertyGet("Item", j+9, i+1);
        vCell.OlePropertySet("Value", SGrid->Cells[j][i].c_str());
      }
//Размеры столбцов и строк, перенос слов
    vCell=vSheet.OlePropertyGet("Range", "A9:N9");
    vCell.OlePropertySet("RowHeight", 40);
    vCell.OlePropertySet("WrapText", True);

//Рамка
    vCell=vSheet.OlePropertyGet("Range", "A9:N14");
    for (i = 7; i < 11; i++) vCell.OlePropertyGet("Borders", i).OlePropertySet("Weight", 3);
    vCell.OlePropertyGet("Borders", 11).OlePropertySet("Weight", 2);
    vCell.OlePropertyGet("Borders", 12).OlePropertySet("Weight", 2);

//Сохраняем
    try {
      vBook.OleProcedure("SaveAs", SaveDlg->FileName.c_str(), Excell_97_2003);
    } catch ( ... ) {
      MessageBox(0, "Не удается сохранить отчет в выбранный файл.\nВозможно, у Вас не хватает прав для создания файла в выбранной папке.\nЛибо, что менее вероятно, каким-то непостижимым образом во время формирования электронной таблицы другой процесс создал файл с тем же именем и все еще его использует.\nТак или иначе, Вы можете сохранить текущий отчет самостоятельно (например, с другим именем).\nОтчет сформирован в Excel, просто воспользуйтесь фунцией \"сохранить\" или \"сохранить как...\".", "Ошибка сохранения", 0 );
    }
//Показываем
    vApp.OlePropertySet("Visible", true);

//    vApp.OleProcedure("Quit");
  }

}
//---------------------------------------------------------------------------

void __fastcall TReportForm::SaveDlgTypeChange(TObject *Sender)
{
  SaveDlg->FileName += SaveDlg->Filter[SaveDlg->FilterIndex];
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::FormCreate(TObject *Sender)
{
  Left = MainForm->RL;
  Top = MainForm->RT;
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::FormDestroy(TObject *Sender)
{
  MainForm->RL = Left;
  MainForm->RT = Top;
}
//---------------------------------------------------------------------------




