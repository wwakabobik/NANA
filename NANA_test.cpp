//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NANA_test.h"
#include "Neuron\\NAFunctions.h"
#include "Neuron\\Neuron.h"
#include "Neuron\\NeuralNet.h"
#include "Perceptron_test.h"
#include "Delta_Net_Test.h"
#include "NDB.h"
#include "LogWindow.h"
#include <Math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;     //
// NN Param
int MAX_N=10;
int MAX_M=10;
int type_N=5;
double thetta_N=1.0;
// L&C Param
// global
double Etta=0.05;
double Edge=0.1;
double Inertial=1;
double Epsilon=0.02;
// test function
double Start_X=0;
int Learning_Steps=1000;
int NFunction=1;
double Alpha=1.0;
double Betta=10.0;
double W=10.0;
double Step=0.1;
// divergention
int StartX_DIV=10;
int Betta_DIV=10;
int W_DIV=10;
int Error_DIV=10;
int Alpha_DIV=1;
//NeuralNet* NN2(MAX_N,MAX_M,type_N,thetta_N);
NeuralNet* TN;

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
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Series1->Clear();
double net; double thetta=Edit1->Text.ToDouble();
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FAEqual(net,thetta));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FABarierS(net,Edit1->Text.ToDouble()));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FABarierH(net,Edit1->Text.ToDouble()));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FASigma(net,Edit1->Text.ToDouble()));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FATanh(net,Edit1->Text.ToDouble()));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-100; i<100; i++)
{
net=i/10.0;
Series1->AddXY(net,FAAbs(net));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
Series1->Clear();
 double net;
for (int i=-60; i<60; i++)
{
net=i/10.0;
Series1->AddXY(net,FAExp(net,Edit1->Text.ToDouble()));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
TN = new NeuralNet(MAX_N,MAX_M,type_N,thetta_N);
}
//---------------------------------------------------------------------------







void __fastcall TForm1::CSpinEdit1Change(TObject *Sender)
{
MAX_N=CSpinEdit1->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit2Change(TObject *Sender)
{
MAX_M=CSpinEdit2->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
type_N=ComboBox1->ItemIndex;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MaskEdit1Change(TObject *Sender)
{
try{
thetta_N=MaskEdit1->Text.ToDouble();
}
catch(...) { }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Step_EChange(TObject *Sender)
{
try {
Step=Step_E->Text.ToDouble();
}
catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::W_EChange(TObject *Sender)
{
try {
W=W_E->Text.ToDouble(); }
catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Alpha_EChange(TObject *Sender)
{
try {
Alpha=Alpha_E->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Betta_EChange(TObject *Sender)
{
try {
Betta=Betta_E->Text.ToDouble();
} catch (...) {}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LearningSteps_EChange(TObject *Sender)
{
try {
Learning_Steps=LearningSteps_E->Text.ToInt();
}
catch (...) {}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Function_EChange(TObject *Sender)
{
try {
NFunction=Function_E->ItemIndex;
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
for (int i=NullFrom->Text.ToInt();i<NullTo->Text.ToInt();i++)
TN->SetNeuron(MAX_N-1,i,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
for (int i=NullFrom->Text.ToInt();i<NullTo->Text.ToInt();i++)
TN->SetNeuron(0,i,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
for (int i=0;i<MAX_N;i++)
for (int j=0;j<MAX_M;j++)
TN->SetNeuron(i,j,type_N,thetta_N);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
TN->Learning_SetEpsilon(Epsilon);
TN->Learning_SetAlpha(Inertial);
TN->Learning_SetEtta(Etta);
TN->SetEdges(Edge);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Etta_EChange(TObject *Sender)
{
try {
Etta=Etta_E->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edge_NChange(TObject *Sender)
{
try {
Edge=Edge_N->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Inertial_EChange(TObject *Sender)
{
try {
Inertial=Inertial_E->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Epsilon_EChange(TObject *Sender)
{
try {
Epsilon=Epsilon_E->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LearnClick(TObject *Sender)
{
CGauge1->Progress=0;
CGauge1->MaxValue=Learning_Steps-1;
double* input = new double[MAX_M]; // function input
double* input_real = new double[MAX_M]; // neural input
double* output = new double[MAX_M]; // real output
double* canonic_output_real = new double[MAX_M]; // neural learning output
double* canonic_output = new double[MAX_M]; // learning_output
double* canonic_output_visual = new double[MAX_M]; // visual output
double* i_rru = new double[MAX_M];
randomize();
for (int g=0;g<Learning_Steps;g++)
{
Start_X=StartX_DIV*50/10000.0-random(StartX_DIV*50)/10000.0;
CGauge1->Progress=g;
for (int i=0;i<MAX_M;i++)
{
if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(0,i))!=0)
input[i]=Start_X+Step*i;
else input[i]=0;
switch (NFunction)  {
        case 0:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*cos(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 1:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*sin(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 2:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*tan(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 3:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*exp(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 4:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*log(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        }
}

/* for (int kk=0;kk<MAX_M;kk++)
if (kk>0)
i_rru[kk]=input[kk]-input[kk-1];
else i_rru[kk]=input[kk]; */
//input_real=CompressInput(input,MAX_M,type_N,thetta_N);
//input_real=CompressInput(i_rru,MAX_M,type_N,thetta_N);
canonic_output_real=CompressOutput(canonic_output,MAX_M,type_N,thetta_N);
//TN->Learn(input_real,canonic_output_real);
TN->Learn(input,canonic_output_real);
}
output=TN->GetResult();
Series1->Clear();
Series2->Clear();
Series3->Clear();
Series4->Clear();
Series5->Clear();
int mmax=TN->CountNotZeroNeuronsInLayer(MAX_N-1);
//        for (int j=0;j<MAX_M;j++)
        for (int j=0;j<mmax;j++)
        {
        Series1->AddXY(input[j],canonic_output_real[j]);
        Series2->AddXY(input[j],output[j]);
        Series3->AddXY(i_rru[j],output[j]);
        Series4->AddXY(input_real[j],canonic_output_real[j]);
        Series5->AddXY(input_real[j],output[j]);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Start_X_EChange(TObject *Sender)
{
try {
Start_X=Start_X_E->Text.ToDouble();
} catch (...) {}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button13Click(TObject *Sender)
{
CGauge1->Progress=0;
double* input = new double[MAX_M]; // function input
double* input_real = new double[MAX_M]; // neural input
double* output = new double[MAX_M]; // real output
double* canonic_output_real = new double[MAX_M]; // neural learning output
double* canonic_output = new double[MAX_M]; // learning_output
double* i_rru = new double[MAX_M];
//double* canonic_output_visual = new double[MAX_M]; // visual output
//for (int g=0;g<Learning_Steps;g++)
//{
CGauge1->Progress=CGauge1->MaxValue;
for (int i=0;i<MAX_M;i++)
{
input[i]=Start_X+Step*i;
switch (NFunction)  {
        case 0:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*cos(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 1:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*sin(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 2:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*tan(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 3:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*exp(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        case 4:
        if (TN->ShowNeuronType(TN->ReturnNeuronRealNumber(MAX_N-1,i))!=0)
        canonic_output[i]=(Alpha+Alpha_DIV*50/10000.0-Alpha*random(Alpha_DIV*100)/10000.0)*log(input[i]*(W+W_DIV*50/10000.0-W*random(W_DIV*100)/10000.0)+(Betta+Betta_DIV*50/10000.0-Betta*random(Betta_DIV*100)/10000.0))+Alpha*random(Error_DIV*100)/10000.0;
        else canonic_output[i]=0;
        break;
        }
}
/*for (int kk=0;kk<MAX_M;kk++)
if (kk>0)
i_rru[kk]=input[kk]-input[kk-1];
else i_rru[kk]=input[kk]; */
//input_real=CompressInput(input,MAX_M,type_N,thetta_N);
canonic_output_real=CompressOutput(canonic_output,MAX_M,type_N,thetta_N);
//output=(TN->GetResult(input_real));
output=(TN->GetResult(input));
//output=TN->GetResult();
Series1->Clear();
Series2->Clear();
Series3->Clear();
Series4->Clear();
Series5->Clear();
int mmax=TN->CountNotZeroNeuronsInLayer(MAX_N-1);
//        for (int j=0;j<MAX_M;j++)
        for (int j=0;j<mmax;j++)
        {
        Series1->AddXY(input[j],canonic_output_real[j]);
        Series2->AddXY(input[j],output[j]);
        Series4->AddXY(input_real[j],canonic_output_real[j]);
        Series5->AddXY(input_real[j],output[j]);
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
TN->SetCascadeNeuron(type_N,thetta_N);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Start_X_DChange(TObject *Sender)
{
StartX_DIV=Start_X_D->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::W_DChange(TObject *Sender)
{
W_DIV=W_D->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Betta_DChange(TObject *Sender)
{
Betta_DIV=Betta_D->Position;  //
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Error_DChange(TObject *Sender)
{
Error_DIV=Error_D->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
for (int i=0;i<MAX_N*MAX_M*MAX_M;i++)
TN->SetEdgeValue(i,(-0.3+random(600)/1000.0));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
Betta=((Betta_E->Text.ToDouble())*0.01*random(Betta_D->Position));
W=((W_E->Text.ToDouble())*0.01*random(W_D->Position));
Start_X=((Start_X_E->Text.ToDouble())*0.01*random(Start_X_D->Position));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
StringGrid1->ColCount=MAX_N;
StringGrid1->RowCount=MAX_M;
for (int i=0;i<MAX_N;i++)
for (int j=0;j<MAX_M;j++)
StringGrid1->Cells[i][j]=TN->ShowNeuronInput(TN->ReturnNeuronRealNumber(i,j));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
StringGrid1->ColCount=MAX_N;
StringGrid1->RowCount=MAX_M;
for (int i=0;i<MAX_N;i++)
for (int j=0;j<MAX_M;j++)
StringGrid1->Cells[i][j]=TN->ShowNeuronError(i,j);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{
StringGrid1->ColCount=MAX_M;
StringGrid1->RowCount=MAX_M;
int i=Edit1->Text.ToInt();
for (int j=0;j<=MAX_M;j++)
for (int k=0;k<MAX_M;k++)
{
StringGrid1->Cells[j][k]=TN->ShowEdge(TN->ReturnEdgeRealNumber(i,j,k));
//ShowMessage(AnsiString(j)+" "+AnsiString(k));
}
}
//---------------------------------------------------------------------------


bool is_contains(int c_array[],int n,int c_number)
{
for (int i=0;i<n;i++)
if(c_array[i]==c_number)
return true;
return false;
}

void __fastcall TForm1::Button22Click(TObject *Sender)
{
double* CE = new double[MAX_N*MAX_M*MAX_M];
int* ISC = new int[MAX_M];
int devider=MAX_M;
for (int i=0;i<MAX_N;i++)
for (int j=0;j<MAX_M;j++)
for (int k=0;k<MAX_M;k++)
CE[TN->ReturnEdgeRealNumber(i,j,k)]=-1;
for (int i=1;i<MAX_N;i++)
{
        if (devider>MAX_M)
        devider=MAX_M;
        for (int j=0;j<MAX_M;j++)
        {
/*                        for (int norm=0;norm<MAX_M/devider;norm++)
                        {
                        int relation=-1; bool state=true;
                        for(;;)
                        {
                                relation=random(MAX_M);
                                state=is_contains(ISC,MAX_M,relation);
                                if (!state)
                                break;
                        }
                        ISC[norm]=relation;
                        CE[TN->ReturnEdgeRealNumber(i,j,norm)]=Edge;
                        }
*/
                        for (int norm=0;norm<MAX_M;norm++)
                                CE[TN->ReturnEdgeRealNumber(i,j,norm)]=0;
CE[TN->ReturnEdgeRealNumber(i,j,j)]=0.1;
        }
        devider++;
}
TN->SetConstEdges(CE);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button21Click(TObject *Sender)
{
StringGrid1->ColCount=MAX_N;
StringGrid1->RowCount=MAX_M;
for (int i=0;i<MAX_N;i++)
for (int j=0;j<MAX_M;j++)
StringGrid1->Cells[i][j]=TN->operator ()((TN->ReturnNeuronRealNumber(i,j)));

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button23Click(TObject *Sender)
{
Form3->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button24Click(TObject *Sender)
{
Form4->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button25Click(TObject *Sender)
{
Form5->ShowModal();
}
//---------------------------------------------------------------------------

