//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
#define Excell_97_2003 56
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComObj.hpp>
#include <utilcls.h>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TReportForm : public TForm
{
__published:	// IDE-managed Components
        TComboBox *YearBox;
        TButton *ReportBtn;
        TLabel *Label1;
        TStringGrid *SGrid;
        TStringGrid *SGrid2;
        TButton *PrintBtn;
        TButton *SaveBtn;
        TSaveDialog *SaveDlg;
        TProgressBar *ProgressBar;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ReportBtnClick(TObject *Sender);
        void __fastcall YearBoxSelect(TObject *Sender);
        void __fastcall YearBoxChange(TObject *Sender);
        void __fastcall PrintBtnClick(TObject *Sender);
        void __fastcall SaveBtnClick(TObject *Sender);
        void __fastcall SaveDlgTypeChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TReportForm(TComponent* Owner);
        double proto1data[4][16], proto2data[4][7], proto3data[4][13];
        AnsiString YEAR;
        Variant vApp, vBook, vSheet, vCells, vCell, vSaveAs;

};
//---------------------------------------------------------------------------
extern PACKAGE TReportForm *ReportForm;
//---------------------------------------------------------------------------
#endif
