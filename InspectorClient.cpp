//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#define __LCC__
#include <mysql.h>
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", MainForm);
USEFORM("Unit2.cpp", OptionsForm);
USEFORM("Unit3.cpp", AddUserForm);
USEFORM("Unit4.cpp", PwdForm);
USEFORM("Unit6.cpp", InputForm);
USEFORM("Unit7.cpp", GroupForm);
USEFORM("Unit8.cpp", JournalForm);
USEFORM("Unit9.cpp", ReportForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TOptionsForm), &OptionsForm);
                 Application->CreateForm(__classid(TAddUserForm), &AddUserForm);
                 Application->CreateForm(__classid(TPwdForm), &PwdForm);
                 Application->CreateForm(__classid(TInputForm), &InputForm);
                 Application->CreateForm(__classid(TGroupForm), &GroupForm);
                 Application->CreateForm(__classid(TJournalForm), &JournalForm);
                 Application->CreateForm(__classid(TReportForm), &ReportForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
