//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogWindow.h"
#include "NDB.h"
#include "Delta_Net_Test.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Image2Click(TObject *Sender)
{
   if (CheckBox1->Checked)
 {Form3->ShowModal(); Form4->Close(); Form5->Close(); }
 else
 {
 Form4->ADConnection1->Connected=false;
 Form4->ADConnection1->Params->BeginUpdate();
 Form4->ADConnection1->Params->Clear();
 Form4->ADConnection1->Params->Add("User_Name="+Edit1->Text);
 Form4->ADConnection1->Params->Add("Password="+Edit2->Text);
 Form4->ADConnection1->Params->Add("Database=NANA_sealevel");
 Form4->ADConnection1->Params->Add("DriverID=MySQL");  //
 Form4->ADConnection1->DriverName="MySQL";
 Form4->ADConnection1->Params->EndUpdate();
 try {
 Form4->ADConnection1->Connected=true;
 }
 catch (...)
 {
 ShowMessage("Wrong login\\password combination!\nError: 3");
 Application->Terminate();
 }
 Form4->Visible=true; Form5->Close();
 }

}
//---------------------------------------------------------------------------

