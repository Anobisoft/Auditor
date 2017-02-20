//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TAddUserForm : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label3;
        TLabel *Label4;
        TMaskEdit *Edit4;
        TButton *CancelBtn;
        TButton *OKBtn;
        TMaskEdit *Edit5;
        TLabel *Label5;
        TLabel *Label6;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
        void __fastcall EditChange(TObject *Sender);
        void __fastcall EditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TAddUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------
#endif
