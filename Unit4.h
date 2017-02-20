//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TPwdForm : public TForm
{
__published:	// IDE-managed Components
        TMaskEdit *PwdEdit;
        TButton *OK;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall OKClick(TObject *Sender);
        void __fastcall PwdEditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        AnsiString correctpass;
        int count;
        __fastcall TPwdForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPwdForm *PwdForm;
//---------------------------------------------------------------------------
#endif
