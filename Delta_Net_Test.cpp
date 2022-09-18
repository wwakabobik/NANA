//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Math.h>
#include <stdlib.h>
#include "Delta_Net_Test.h"
#include "Neuron\\Delta_Net.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
Delta_Net* DN;
int in_p=16;
int out_p=3;

double ND=1;






double* CompressInput(double input[],int N,int type,int etta)
{
// THIS IS WRONG!!!
double betta=5.0;
// END OF WRONG!!!
double* new_input = new double[N];
double max,min,measure;
max=input[0];
min=input[0];
for (int i=0;i<N;i++)
{ if (max<input[i]) max=input[i]; if (min>input[i]) min=input[i]; }
//if (abs(max)>abs(min)) measure=max;
//else measure=min;
for (int j=0;j<N;j++)
new_input[j]=input[j]-min;
switch (type)
{
        case 5:
        {
        for (int k=0;k<N;k++)
        {
        if ((max-min)!=0)
        new_input[k]=new_input[k]*(2*betta/(max-min))-betta;
        else new_input[k]=0;
        }
        }
        break;
}
return new_input;
}

double* CompressOutput(double output[],int N,int type,int etta)
{
// THIS IS WRONG!!!
double betta=1;
// END OF WRONG!!!
double* new_output = new double[N];
double max,min,measure;
max=output[0];
min=output[0];
for (int i=0;i<N;i++)
{ if (max<output[i]) max=output[i]; if (min>output[i]) min=output[i]; }
//if (abs(max)>abs(min)) measure=max;
//else measure=min;
for (int j=0;j<N;j++)
new_output[j]=output[j]-min;
switch (type)
{
        case 5:
        {
        for (int k=0;k<N;k++)
        {
        if ((max-min)!=0)
        new_output[k]=new_output[k]*(betta/(max-min));
        else new_output[k]=0;
        }
        }
        break;
}
return new_output;
}






//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
//DN = new Delta_Net(12,2,2,5,1,1,0.02,1,5);
DN = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5);
//int new_delivery, int new_calc_state, int new_layer_count, int new_layer_regress, double new_static_etta, double new_thetta, int new_type);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
DN->Learning_SetAlpha(1);
DN->Learning_SetEpsilon(0.2);
DN->Learning_SetEtta(0.2);
DN->LearningState(true);
double* inp = new double[in_p+out_p];
double* inp2 = new double[in_p];
double* inp_inrange = new double[in_p];
double* outp = new double[out_p];
double* outp2 = new double[out_p];
double* canonic_output_real=new double[in_p+out_p];
randomize();
for (int k=0;k<1000;k++)
{
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(out_p+in_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
}
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
DN->Learn(inp2,outp);
//DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
for (int i0=0;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=0;j0<out_p;j0++)
{
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
//Series1->AddXY(12+j0,outp[j0]);
Series2->AddXY(in_p+j0,outp2[j0]);
}

}

}
//---------------------------------------------------------------------------

void __fastcall TForm3::TrackBar1Change(TObject *Sender)
{
ND=TrackBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
StringGrid1->ColCount=6;
StringGrid1->RowCount=20;
for (int i=0;i<6;i++)
for (int j=0;j<20;j++)
StringGrid1->Cells[i][j]=DN->DNet->ShowNeuronInput(DN->DNet->ReturnNeuronRealNumber(i,j));
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
StringGrid1->ColCount=20;
StringGrid1->RowCount=20;
int i=Edit1->Text.ToInt();
for (int j=0;j<=20;j++)
for (int k=0;k<20;k++)
{
StringGrid1->Cells[j][k]=DN->DNet->ShowEdge(DN->DNet->ReturnEdgeRealNumber(i,j,k));
//ShowMessage(AnsiString(j)+" "+AnsiString(k));
}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button5Click(TObject *Sender)
{
double* inp = new double[in_p+out_p];
double* inp2 = new double[in_p];
double* inp_inrange = new double[in_p];
double* outp = new double[out_p];
double* outp2 = new double[out_p];
double* canonic_output_real=new double[in_p+out_p];
randomize();
for (int k=0;k<1000;k++)
{
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(in_p+out_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
}
canonic_output_real=CompressOutput(inp,in_p+out_p,5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
//DN->Learn(inp2,outp);
DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
for (int i0=0;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=0;j0<out_p;j0++)
{
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
//Series1->AddXY(12+j0,outp[j0]);
Series2->AddXY(in_p+j0,outp2[j0]);
}

}

}
//---------------------------------------------------------------------------

