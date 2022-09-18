//---------------------------------------------------------------------------

#ifndef NANA_testH
#define NANA_testH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Grids.hpp>
#include "CGAUGES.h"
#include "CSPIN.h"
#include <Mask.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TLineSeries *Series1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TLineSeries *Series2;
        TStringGrid *StringGrid1;
        TCGauge *CGauge1;
        TButton *Button8;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TComboBox *ComboBox1;
        TMaskEdit *MaskEdit1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TEdit *Edit2;
        TComboBox *Function_E;
        TLabel *Label5;
        TLabel *Label6;
        TButton *Button10;
        TEdit *NullFrom;
        TEdit *NullTo;
        TLabel *Label7;
        TLabel *Label8;
        TButton *Button9;
        TLabel *Label9;
        TLabel *Label10;
        TCSpinEdit *LearningSteps_E;
        TMaskEdit *Alpha_E;
        TLabel *Label11;
        TMaskEdit *W_E;
        TLabel *Label13;
        TMaskEdit *Betta_E;
        TLabel *Label12;
        TMaskEdit *Step_E;
        TLabel *Label14;
        TButton *Button11;
        TMaskEdit *Etta_E;
        TLabel *Label15;
        TMaskEdit *Edge_N;
        TLabel *Label16;
        TMaskEdit *Inertial_E;
        TLabel *Label17;
        TMaskEdit *Epsilon_E;
        TLabel *Label18;
        TButton *Button12;
        TButton *Learn;
        TMaskEdit *Start_X_E;
        TLabel *Label19;
        TMaskEdit *MaskEdit3;
        TLabel *Label20;
        TButton *Button13;
        TButton *Button14;
        TTrackBar *W_D;
        TTrackBar *Betta_D;
        TTrackBar *Error_D;
        TTrackBar *Start_X_D;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label21;
        TLabel *Label24;
        TButton *Button15;
        TButton *Button16;
        TButton *Button17;
        TButton *Button18;
        TButton *Button19;
        TButton *Button20;
        TButton *Button21;
        TChart *Chart2;
        TLineSeries *Series3;
        TChart *Chart3;
        TLineSeries *Series4;
        TLineSeries *Series5;
        TButton *Button22;
        TButton *Button23;
        TButton *Button24;
        TButton *Button25;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall CSpinEdit1Change(TObject *Sender);
        void __fastcall CSpinEdit2Change(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall MaskEdit1Change(TObject *Sender);
        void __fastcall Step_EChange(TObject *Sender);
        void __fastcall W_EChange(TObject *Sender);
        void __fastcall Alpha_EChange(TObject *Sender);
        void __fastcall Betta_EChange(TObject *Sender);
        void __fastcall LearningSteps_EChange(TObject *Sender);
        void __fastcall Function_EChange(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Etta_EChange(TObject *Sender);
        void __fastcall Edge_NChange(TObject *Sender);
        void __fastcall Inertial_EChange(TObject *Sender);
        void __fastcall Epsilon_EChange(TObject *Sender);
        void __fastcall LearnClick(TObject *Sender);
        void __fastcall Start_X_EChange(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Start_X_DChange(TObject *Sender);
        void __fastcall W_DChange(TObject *Sender);
        void __fastcall Betta_DChange(TObject *Sender);
        void __fastcall Error_DChange(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button23Click(TObject *Sender);
        void __fastcall Button24Click(TObject *Sender);
        void __fastcall Button25Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
