//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#define PVersion "1.12 BETA"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Registry.hpp>
#include <mysql.h>
#include "Unit5.h"
#include <CustomizeDlg.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>



//---------------------------------------------------------------------------
class TMySQL_work
{
   public:
   MYSQL *dbCnt;
   bool Connected;
   int port;
   AnsiString host, user, pass, dbnm;
   AnsiString query;
   MYSQL_RES *result;
   MYSQL_ROW row;
   bool __fastcall TryConnect();
   bool __fastcall GetInspectors();
   void __fastcall AddUser(AnsiString a1, AnsiString a2, AnsiString a3, AnsiString a4);
   void __fastcall GetReportYears();
   void __fastcall GetRefbooks();
   void __fastcall Close();
   bool __fastcall TMySQL_work::Query(char *query);
};


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TButton *ConnectBtn;
        TMainMenu *MainMenu1;
        TMenuItem *MMFile;
        TMenuItem *MMConnect;
        TMenuItem *MMOptions;
        TMenuItem *MMExit;
        TMenuItem *MMAbout;
        TComboBox *InspListBox;
        TButton *AddBtn;
        TLabel *LabelConnection;
        TButton *InputBtn;
        TButton *JournalBtn;
        TButton *ReportBtn;
        TButton *EnterBtn;
        TButton *DelBtn;
        TBevel *Bevel1;
        bool __fastcall TryGetOptions();
        void __fastcall GetPositions();
        void __fastcall SavePositions();
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MMExitClick(TObject *Sender);
        void __fastcall ConnectBtnClick(TObject *Sender);
        void __fastcall MMOptionsClick(TObject *Sender);
        void __fastcall OptionsOpen();
        void __fastcall PrintLabel();
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall AddBtnClick(TObject *Sender);
        void __fastcall InspListBoxSelect(TObject *Sender);
        void __fastcall InspListBoxChange(TObject *Sender);
        void __fastcall InputBtnClick(TObject *Sender);
        void __fastcall EnterBtnClick(TObject *Sender);
        void __fastcall InspListBoxKeyPress(TObject *Sender, char &Key);
        void __fastcall JournalBtnClick(TObject *Sender);
        void __fastcall ReportBtnClick(TObject *Sender);
        void __fastcall MMAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Clrrr();
        void ChngEnbl(bool x);
        TMySQL_work *DB;
        TRegistry *HKLMOpt;
        Tinsp *Insp;
        bool Entered;
        int IL, IT, JL, JT, RL, RT;

};


//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
