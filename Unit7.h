//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "Unit5.h"
//---------------------------------------------------------------------------
class TGroupForm : public TForm
{
__published:	// IDE-managed Components
        TCheckListBox *CheckListBox;
        TButton *OKBtn;
        TCheckBox *CheckAllBox;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall CheckAllBoxClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TGroupForm(TComponent* Owner);
        rlist *Group;
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupForm *GroupForm;
//---------------------------------------------------------------------------
#endif
