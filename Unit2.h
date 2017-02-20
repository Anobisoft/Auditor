//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TEdit *Opt1Edit;
        TLabel *Opt1Label;
        TLabel *Opt2Label;
        TEdit *Opt2Edit;
        TLabel *Opt3Label;
        TEdit *Opt3Edit;
        TLabel *Opt4Label;
        TMaskEdit *Opt4MaskEdit;
        TEdit *Opt5Edit;
        TLabel *Opt5Label;
        TButton *ApplyBtn;
        TButton *CancelBtn;
        TButton *OKBtn;
        TGroupBox *GroupBox2;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ApplyBtnClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
        void __fastcall OptEditChange(TObject *Sender);
        void __fastcall OKBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
