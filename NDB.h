//---------------------------------------------------------------------------

#ifndef NDBH
#define NDBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "daADCompClient.hpp"
#include "daADCompDataSet.hpp"
#include "daADDAptIntf.hpp"
#include "daADDatSManager.hpp"
#include "daADGUIxFormsControls.hpp"
#include "daADGUIxFormsfAsync.hpp"
#include "daADGUIxFormsfError.hpp"
#include "daADGUIxFormsfLogin.hpp"
#include "daADGUIxFormsfQBldr.hpp"
#include "daADGUIxFormsQBldr.hpp"
#include "daADGUIxFormsWait.hpp"
#include "daADPhysIntf.hpp"
#include "daADPhysManager.hpp"
#include "daADPhysMySQL.hpp"
#include "daADStanDef.hpp"
#include "daADStanIntf.hpp"
#include "daADStanOption.hpp"
#include "daADStanParam.hpp"
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "CGAUGES.h"
#include <Dialogs.hpp>
#include "CSPIN.h"
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TADConnection *ADConnection1;
        TADPhysMySQLDriverLink *ADPhysMySQLDriverLink1;
        TADGUIxFormsErrorDialog *ADGUIxFormsErrorDialog1;
        TADGUIxFormsQBldrDialog *ADGUIxFormsQBldrDialog1;
        TADGUIxFormsQBldrEngine *ADGUIxFormsQBldrEngine1;
        TADGUIxFormsLoginDialog *ADGUIxFormsLoginDialog1;
        TADGUIxFormsAsyncExecuteDialog *ADGUIxFormsAsyncExecuteDialog1;
        TADGUIxWaitCursor *ADGUIxWaitCursor1;
        TADUpdateSQL *ADUpdateSQL1;
        TADQuery *ADQuery1;
        TADQuery *ADQuery2;
        TMemo *Memo1;
        TButton *Button1;
        TButton *Button2;
        TDBGrid *DBGrid1;
        TDataSource *DataSource1;
        TButton *Button3;
        TCGauge *CGauge1;
        TButton *Button4;
        TOpenDialog *OpenDialog1;
        TButton *Load_From_File;
        TEdit *Edit1;
        TButton *Button5;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TCSpinEdit *CSpinEdit5;
        TChart *Chart1;
        TLineSeries *Series1;
        TButton *Button6;
        TCSpinEdit *CSpinEdit6;
        TEdit *Edit2;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TButton *Button12;
        TLineSeries *Series2;
        TButton *Button13;
        TButton *Button14;
        TButton *Button15;
        TCSpinEdit *CSpinEdit7;
        TButton *Button16;
        TLabel *Label1;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TCheckBox *GFS_cb;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel8;
        TPanel *Panel9;
        TPanel *Panel10;
        TPanel *Panel11;
        TPanel *Panel12;
        TPanel *Panel13;
        TLabel *Label2;
        TLabel *Label3;
        TPanel *Panel14;
        TCheckBox *Rcalc;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TPanel *Panel15;
        TPanel *Panel16;
        TButton *Button17;
        TButton *Button18;
        TButton *Button19;
        TButton *Button20;
        TButton *Button21;
        TButton *Button22;
        TButton *Button23;
        TCheckBox *LOSS;
        TCheckBox *WOCR;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Load_From_FileClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall CSpinEdit7Change(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Panel1Click(TObject *Sender);
        void __fastcall Panel2Click(TObject *Sender);
        void __fastcall Panel3Click(TObject *Sender);
        void __fastcall Panel4Click(TObject *Sender);
        void __fastcall Panel5Click(TObject *Sender);
        void __fastcall Panel6Click(TObject *Sender);
        void __fastcall Panel10Click(TObject *Sender);
        void __fastcall Panel11Click(TObject *Sender);
        void __fastcall Panel12Click(TObject *Sender);
        void __fastcall Panel13Click(TObject *Sender);
        void __fastcall Panel7Click(TObject *Sender);
        void __fastcall Panel8Click(TObject *Sender);
        void __fastcall Panel9Click(TObject *Sender);
        void __fastcall Panel14Click(TObject *Sender);
        void __fastcall Panel16Click(TObject *Sender);
        void __fastcall Panel15Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
        void __fastcall Button23Click(TObject *Sender);
        void __fastcall CheckBox3Enter(TObject *Sender);
        void __fastcall CheckBox3Exit(TObject *Sender);
        void __fastcall CheckBox4Enter(TObject *Sender);
        void __fastcall CheckBox4Exit(TObject *Sender);
        void __fastcall CheckBox2Exit(TObject *Sender);
        void __fastcall CheckBox2Enter(TObject *Sender);
        void __fastcall CheckBox1Enter(TObject *Sender);
        void __fastcall CheckBox1Exit(TObject *Sender);
        void __fastcall WOCREnter(TObject *Sender);
        void __fastcall WOCRExit(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
