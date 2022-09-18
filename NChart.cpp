//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NChart.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm6::FormResize(TObject *Sender)
{
Chart1->Height=Form6->Height-10;
Chart1->Width=Form6->Width-10;
}
//---------------------------------------------------------------------------
