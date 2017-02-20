//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TInputForm : public TForm
{
__published:	// IDE-managed Components
        TDateTimePicker *DatePicker;
        TLabel *Label3;
        TStringGrid *SGrid;
        TLabel *Label1;
        TComboBox *DirectorBox;
        TLabel *Label4;
        TRadioGroup *RGroup1;
        TRadioGroup *RGroup2;
        TButton *SendBtn;
        TButton *PeriodBtn;
        TMemo *Comment;
        TDateTimePicker *Period1;
        TDateTimePicker *Period2;
        TButton *GroupBtn;
        TComboBox *MotivBox;
        TLabel *Label2;
        TLabel *Label7;
        TLabel *Label5;
        TLabel *Label6;
        TButton *OkBtn;
        TLabel *LabelRequire1;
        TLabel *LabelRequire2;
        TLabel *LabelRequire3;
        TLabeledEdit *NameEdit;
        TLabeledEdit *NumEdit;
        void __fastcall RGroup1Click(TObject *Sender);
        void __fastcall RGroup2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PeriodBtnClick(TObject *Sender);
        void __fastcall SendBtnClick(TObject *Sender);
        void __fastcall DirectorBoxSelect(TObject *Sender);
        void __fastcall DirectorBoxChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Period1Change(TObject *Sender);
        void __fastcall SGridSetEditText(TObject *Sender, int ACol, int ARow, const AnsiString Value);
        void __fastcall GroupBtnClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall OkBtnClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall MotivBoxSelect(TObject *Sender);
        void __fastcall MotivBoxChange(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TInputForm(TComponent* Owner);
        double proto1data[16][4][20];
        double proto2data[7][4];
        bool FirstEdit, PFixed;
        struct Tdtrec {
          unsigned short year, month, day;
        } dtx1, dtx2;
        int cur1, cur2;
        bool proto1save();
        bool proto2save();
        void proto1get(int x);
        void proto2get(int x);
        void proto1draw();
        void proto2draw();

        bool Editx, EExit;
        AnsiString query;
        void InsertGroup();
        void InsertData1();
        void InsertData2();
        bool InsertProto();
        void UpdateProto();
        bool SelectProto();
        bool isFloat(AnsiString x);
        AnsiString Fpnt( AnsiString x );
        AnsiString inspection_name, dt_inspection, dt_pbegin, dt_pend, motivation, comment, id_inspector_m;
        int id_inspection, id_target, id_director;

        TDateTime DateTime;
        MYSQL_RES *result;
        MYSQL_ROW row;
};
//---------------------------------------------------------------------------
extern PACKAGE TInputForm *InputForm;
//---------------------------------------------------------------------------
#endif
