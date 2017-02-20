//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>

const AnsiString titles[5] = { "№", "№ протокола", "Дата", "Руководитель", "Наименование проверки"};

//---------------------------------------------------------------------------
class TJournalForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *SGrid;
        TPopupMenu *PopupM;
        TMenuItem *N1;
        TMenuItem *N2;
        TPopupMenu *PopupD;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall SGridMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TJournalForm(TComponent* Owner);
        void __fastcall GetJ();
        int ACol, ARow;

};
//---------------------------------------------------------------------------
extern PACKAGE TJournalForm *JournalForm;
//---------------------------------------------------------------------------
#endif
