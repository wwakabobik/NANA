//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Perceptron_Test.h"
#include "NANA_test.h"
#include "Neuron\\NAFunctions.h"
#include "Neuron\\Neuron.h"
#include "Neuron\\NeuralNet.h"
#include "Neuron\\Perceptron.h"
#include "Perceptron_test.h"
#include "Neuron\\Neuro_Constants.h"
#include <Math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

int MAX_IN,MAX_OUT,DIV1,DIV2;

Perceptron* PT;

/*ONLY FOR TESTING*/

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
        else
        new_input=0;
        }
        }
        break;
}
return new_input;
}

double* CompressOutput(double output[],int N,int type,int etta)
{
// THIS IS WRONG!!!
double betta=0.5;
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
        new_output[k]=new_output[k]*(betta/(max-min))+0.5;
        else {
        if (new_output[k]<1 && new_output[k]>-1)
        new_output[k]=abs(new_output[k])+0.5;
        else
        new_output[k]=betta/new_output[k]+1;
        }
        }
        }
        break;
}
return new_output;
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
MAX_IN=4;
MAX_OUT=1;
DIV1=5;
DIV2=2;
PT = new Perceptron(MAX_IN,MAX_OUT,DIV1,DIV2,1,5,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
double x=Edit1->Text.ToDouble();
double w=Edit2->Text.ToDouble();
double b=Edit3->Text.ToDouble();
double* input = new double[MAX_IN];
double* output_l = new double[MAX_OUT];
double* output = new double [MAX_OUT];
double* input_r = new double[MAX_IN];
double* output_r =new double[MAX_OUT];

PT->Learning_SetAlpha(1);
PT->Learning_SetEpsilon(0.02);
PT->Learning_SetEtta(1);
int j=0;
/*for (int ii=0;ii<100;ii++)
{
double x=Edit1->Text.ToDouble();
double w=Edit2->Text.ToDouble();
double b=Edit3->Text.ToDouble();
randomize();
/*for (int ij=0;ij<10;ij++)
{
w+=0.5-random(10)/100.0;
x+=0.5-random(10)/100.0;
b+=0.5-random(10)/100.0;
        for (j=0;j<MAX_IN;j++)
                input[j]=(cos((x+j/2.0)*w+b));
        int n=0;
        for (n=0;n<MAX_OUT;n++)
        {
                output_l[n]=(cos((x+j/2.0)*w+b));
                //ShowMessage(output_l[n]);
                j++;
        }
        input_r=CompressInput(input,MAX_IN,5,1);
        output_r=CompressOutput(output_l,MAX_OUT,5,1);
        double l_state=(input_r[MAX_IN-1]+input_r[MAX_IN-2])/2;
        //ShowMessage(output_r[0]);
        output_l[0]=l_state;
        PT->Learn(input_r,output_l);
}
for (int k=0;k<MAX_OUT;k++)
{
        Memo1->Lines->Add(AnsiString(output[k]));
        Memo2->Lines->Add(AnsiString(output_l[k]));
}
}
output=PT->GetResult();
int i=0;
Series1->Clear();
Series2->Clear();
/*for (i=0;i<MAX_IN;i++)
{
//ShowMessage(input_r[i]);
        Series1->AddXY(i,input_r[i]);
        Series2->AddXY(i,input_r[i]);
        Memo1->Lines->Add(AnsiString(input_r[i]));
        Memo2->Lines->Add(AnsiString(input_r[i]));
} */
for (int i=0;i<1000;i++)
{
input_r[0]=0.75-0.25+random(50)/100.0;
input_r[1]=0.75-0.25+random(50)/100.0;
input_r[2]=0.75-0.25+random(50)/100.0;
input_r[3]=0.75-0.25+random(50)/100.0;
output_l[0]=(input_r[0]+input_r[1]+input_r[2]+input_r[3])/4;
PT->Learn(input_r,output_l);
}
output=PT->GetResult();
for (int k=0;k<MAX_OUT;k++)
{
//ShowMessage(output[k]);
        Series1->AddXY(k,output_l[k]);
        Series2->AddXY(k,output[k]);
        Memo1->Lines->Add(AnsiString(output[k]));
        Memo2->Lines->Add(AnsiString(output_l[k]));
//}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
double x=Edit1->Text.ToDouble();
double w=Edit2->Text.ToDouble();
double b=Edit3->Text.ToDouble();
double* input = new double[MAX_IN];
double* output = new double[MAX_OUT];
input[0]=0.75-0.25+random(50)/100.0;
input[1]=0.75-0.25+random(50)/100.0;
input[2]=0.75-0.25+random(50)/100.0;
input[3]=0.75-0.25+random(50)/100.0;
output[0]=(input[0]+input[1]+input[2]+input[3])/4;
Memo1->Lines->Clear();
Memo2->Lines->Clear();
Memo2->Lines->Add(AnsiString(output[0]));
output=PT->GetResult(input);
Memo1->Lines->Add(AnsiString(output[0]));
}
//---------------------------------------------------------------------------

