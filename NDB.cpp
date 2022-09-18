//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include <fstream.h>
#include "Neuron\\Delta_Net.h" // header oh DN
#include "A_func\\Date_conv.h" // date-hour converter header
#include "NDB.h" // this form
#include "NChart.h" // zoomed chart form
#include "LogWindow.h" // login window
#include "Delta_Net_Test.h" // demo of dummy DN
#include "NANA_test.h" // demo of dummy\param perceptron
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "daADCompClient"
#pragma link "daADCompDataSet"
#pragma link "daADDAptIntf"
#pragma link "daADDatSManager"
#pragma link "daADGUIxFormsControls"
#pragma link "daADGUIxFormsfAsync"
#pragma link "daADGUIxFormsfError"
#pragma link "daADGUIxFormsfLogin"
#pragma link "daADGUIxFormsfQBldr"
#pragma link "daADGUIxFormsQBldr"
#pragma link "daADGUIxFormsWait"
#pragma link "daADPhysIntf"
#pragma link "daADPhysManager"
#pragma link "daADPhysMySQL"
#pragma link "daADStanDef"
#pragma link "daADStanIntf"
#pragma link "daADStanOption"
#pragma link "daADStanParam"
#pragma link "CGAUGES"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm4 *Form4;

// control values

int clearn=100;
double* learn_error=new double[10000];

// NN DEFINITION

Delta_Net* DN;
Delta_Net* DNY;
Delta_Net* DNM;
Delta_Net* DND;
Delta_Net* DNH;

// converter

DH_Converter* DHC;

int in_p=16;
int out_p=3;

double* inp = new double[in_p+out_p];
double* inp2 = new double[in_p];
double* outp = new double[out_p];
double* outp2 = new double[out_p];
double* canonic_output_real=new double[in_p+out_p];
double* outp2v = new double[out_p];
double* canonic_output_realv=new double[in_p+out_p];


// special

double ND=1;

// pre-func

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

//

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
CGauge1->MaxValue=Memo1->Lines->Count;
// PARSE!
for (int i=0;i<Memo1->Lines->Count;i++)
{
CGauge1->Progress=i+1;
        AnsiString S_T=Memo1->Lines->Strings[i];
        int length = S_T.Length();
        char s_year[5];
        char s_month[3];
        char s_day[3];
        char s_hour[3];
        char s_minute[3];
        char s_level[7];
        int state=0;
        int k=0;
        for (int j=1;j<=length;j++)
        {
                if (S_T[j]==' ' || S_T[j]==':')
                        { state++; k=0; j++; }
                if (state==1)
                        { s_year[k]=S_T[j]; s_year[k+1]='\0'; k++; if (k==4) { state=2; k=0; } }
                else if (state==2)
                        { s_month[k]=S_T[j]; s_month[k+1]='\0';  k++;  if (k==2) { state=3; k=0; } }
                else if (state==3)
                        { s_day[k]=S_T[j]; s_day[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==4)
                        { s_hour[k]=S_T[j]; s_hour[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==5)
                        { s_minute[k]=S_T[j]; s_minute[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==6)
                        { s_level[k]=S_T[j]; s_level[k+1]='\0';  k++;  }
        }
/*ListBox1->Items->Add(AnsiString(s_year));
ListBox2->Items->Add(AnsiString(s_month));
ListBox3->Items->Add(AnsiString(s_day));
ListBox4->Items->Add(AnsiString(s_hour));
ListBox5->Items->Add(AnsiString(s_minute));
ListBox6->Items->Add(AnsiString(s_level));*/
ADQuery2->SQL->Text="INSERT INTO H_DATA (id_station, s_year, s_month, s_day, s_hour, s_minute, s_level) VALUES ( 1, "+AnsiString(s_year)+", "+AnsiString(s_month)+", "+AnsiString(s_day)+", "+AnsiString(s_hour)+", "+AnsiString(s_minute)+", "+AnsiString(s_level)+");";
ADQuery2->ExecSQL();
}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button2Click(TObject *Sender)
{
ADQuery1->Close();
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button3Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->Open();
Series1->Clear();
int i=0;
while (!ADQuery1->Eof)
{ i++; Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat); ADQuery1->Next(); }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button4Click(TObject *Sender)
{
ifstream r;
bool state = false;
AnsiString TMP;
char buffer[1024];
if (OpenDialog1->Execute())
{
r.open((OpenDialog1->FileName).c_str(),ios::in);
for (;;)
{
r.getline(buffer,1024);
TMP=AnsiString(buffer);
if (TMP=="</pre>")
break;
else
{
        if (TMP=="Station Date     Time  Pred 6 Min.")
        state=true;
        else if (state)
        Memo1->Lines->Add(TMP);
}
}
r.close();
//if (OpenDialog1->Execute())
}
//        Memo2->Lines->LoadFromFile(OpenDialog1->FileName);//
//        for (int i=0;i<Memo2->Lines->Count;i++)
//                if (Memo2->Lines->Strings[i]!="Station Date     Time  Pred 6 Min.")
//                        Memo2->Lines->Delete(i);
//                else { Memo2->Lines->Delete(i); break; }
//        }
//Memo1->Text=Memo2->Text;
//Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Load_From_FileClick(TObject *Sender)
{
char buffer[1024];
if (OpenDialog1->Execute())
{
        ifstream r,f;
        bool state = false;
        AnsiString TMP;
        f.open((OpenDialog1->FileName).c_str(),ios::in);
        int numberof_m=0;
        int n=0;
        CGauge1->MinValue=0;
        CGauge1->MaxValue=2;
        randomize();
        while (!f.eof())
        {
        CGauge1->Progress=random(CGauge1->MaxValue);
        f.getline(buffer,1024);
        CGauge1->MaxValue++;
        }
        f.close();
        ShowMessage("Staring SQL process with "+AnsiString(CGauge1->MaxValue)+" rows!");
        r.open((OpenDialog1->FileName).c_str(),ios::in);
        for (int i=0;;i++)
        {
                r.getline(buffer,1024);
                CGauge1->Progress=i;
                TMP=AnsiString(buffer);
                if (TMP=="</pre>" || r.eof())
                break;
                else
                {
                        if (TMP=="Station Date     Time  Pred 6 Min.")
                                state=true;
                        else if (state)
                        {
                                AnsiString S_T=TMP;
                                int length = S_T.Length();
                                char s_year[5];
                                char s_month[3];
                                char s_day[3];
                                char s_hour[3];
                                char s_minute[3];
                                char s_level[7];
                                int state=0;
                                int k=0;
                                for (int j=1;j<=length;j++)
                                {
                                        if (S_T[j]==' ' || S_T[j]==':')
                                                { state++; k=0; j++; }
                                        if (state==1)
                                                { s_year[k]=S_T[j]; s_year[k+1]='\0'; k++; if (k==4) { state=2; k=0; } }
                                        else if (state==2)
                                                { s_month[k]=S_T[j]; s_month[k+1]='\0';  k++;  if (k==2) { state=3; k=0; } }
                                        else if (state==3)
                                                { s_day[k]=S_T[j]; s_day[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==4)
                                                { s_hour[k]=S_T[j]; s_hour[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==5)
                                                { s_minute[k]=S_T[j]; s_minute[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==6)
                                                { s_level[k]=S_T[j]; s_level[k+1]='\0';  k++;  }
                                }
                                ADQuery2->SQL->Text="INSERT INTO H_DATA (id_station, s_year, s_month, s_day, s_hour, s_minute, s_level) VALUES ("+ Edit1->Text + ", "+AnsiString(s_year)+", "+AnsiString(s_month)+", "+AnsiString(s_day)+", "+AnsiString(s_hour)+", "+AnsiString(s_minute)+", "+AnsiString(s_level)+");";
                                ADQuery2->ExecSQL();
                        }
                }
        }
r.close();
}

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button5Click(TObject *Sender)
{
ADQuery1->SQL->Text="SELECT id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level FROM H_DATA WHERE id_station="+AnsiString(Edit1->Text)+" and s_year="+AnsiString(CSpinEdit1->Value)+" and s_month="+AnsiString(CSpinEdit2->Value)+" and s_day="+AnsiString(CSpinEdit3->Value)+" GROUP BY s_hour ORDER BY s_year, s_month, s_day, s_hour DESC LIMIT 0,"+AnsiString(CSpinEdit4->Value);
Memo1->Text=ADQuery1->SQL->Text;
ADQuery1->Open();
Series1->Clear();
for (int i=0;i<CSpinEdit4->Value;i++)
{ Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat); ADQuery1->Next(); }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button6Click(TObject *Sender)
{
int intervals=CSpinEdit4->Value;
int a_years=CSpinEdit1->Value;
int a_months=CSpinEdit2->Value;
int a_days=CSpinEdit3->Value;
int a_hours=CSpinEdit6->Value;
int d_months, d_days, d_hours;
d_hours=a_hours-intervals;
if (d_hours>=0) // interval less than one day
        Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(a_days)+" "+AnsiString(d_hours);
else
{
        d_days=a_days-(1-int(d_hours/24));
        if (d_days>1)
                if (d_hours%24!=0)
                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                else
                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
        else
        {
                d_months=a_months-1;
                if (d_months>0)
                {
                        if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                        {
                                d_days=31+d_days;
                                if (d_hours%24!=0)
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                else
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                        }
                        else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                        {
                                d_days=30+d_days;
                                if (d_hours%24!=0)
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                else
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                        }
                        else if (d_months==2)
                        {
                                if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                        d_days=29+d_days;
                                else
                                        d_days=28+d_days;
                                if (d_hours%24!=0)
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                else
                                        Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                        }
                }
                else // month a more !!!!!!!!!!!! here!
                {
                        d_days=31+d_days;
                        d_months=12;
                        if (d_hours%24!=0)
                                Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                        else
                                Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                }

        }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button7Click(TObject *Sender)
{
CGauge1->MaxValue=2008;
CGauge1->MinValue=1900;
for (int s_years=1900;s_years<2009;s_years++)
{
CGauge1->Progress=s_years;
for (int s_months=1;s_months<13;s_months++)
{

ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_days("+AnsiString(Edit1->Text)+","+AnsiString(s_years)+","+AnsiString(s_months)+");";
ADQuery1->ExecSQL();
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button8Click(TObject *Sender)
{
CGauge1->MaxValue=2008;
CGauge1->MinValue=1900;
for (int s_years=1900;s_years<2009;s_years++)
{
CGauge1->Progress=s_years;
ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_months("+AnsiString(Edit1->Text)+","+AnsiString(s_years)+");";
ADQuery1->ExecSQL();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button9Click(TObject *Sender)
{
ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_years("+AnsiString(Edit1->Text)+");";
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button10Click(TObject *Sender)
{
DN = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button11Click(TObject *Sender)
{
for (int m=0;m<clearn;m++)
learn_error[m]=0;
CGauge1->MaxValue=clearn;
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
for (int k=0;k<clearn;k++)
{
CGauge1->Progress=k+1;
/*
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(out_p+in_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
} */
//ADQuery1->SQL->Text=Memo1->Text;
int ry,rm,rd,rs;
rs=random(5)+1;
ry=random(107)+1901;
rm=random(12)+1;
rd=random(12);
// INPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
ADQuery1->Open();
Series1->Clear();
int i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
//inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
ADQuery1->Close();
//Sleep(500);
/*// OUTPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(Edit1->Text)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd+in_p)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p);
ADQuery1->Open();
i=0;
while (!ADQuery1->Eof)
{
//ShowMessage("!!!");
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
outp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
outp2[i]=outp[i];
ADQuery1->Next();
}
ADQuery1->Close();*/
// FULL_OUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
ADQuery1->Open();
 i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
//ADQuery1->Close();
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
DN->Learn(inp2,outp);
//DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
Form6->Series1->AddXY(i0,canonic_output_real[i0]);
Form6->Series2->AddXY(i0,canonic_output_real[i0]);

}
for (int j0=1;j0<out_p;j0++)
{
//ShowMessage(AnsiString(k)+" "+AnsiString(clearn));
learn_error[k]+=canonic_output_real[j0+in_p]-outp2[j0];
//ShowMessage(learn_error[k]);
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
Form6->Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
Series2->AddXY(in_p+j0,outp2[j0]);
Form6->Series2->AddXY(in_p+j0,outp2[j0]);
}

}

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button12Click(TObject *Sender)
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
if (Form5->CheckBox1->Checked)
{//for (int k=0;k<10;k++)
//{
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(out_p+in_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
}
}
//ADQuery1->SQL->Text=Memo1->Text;
else
{
int ry,rm,rd,rs;
ry=random(108)+1901;
rm=random(12)+1;
rd=random(12);
rs=random(5)+1;
// INPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
ADQuery1->Open();
Series1->Clear();
int i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
//inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
ADQuery1->Close();
//Sleep(500);
/*// OUTPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(Edit1->Text)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd+in_p)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p);
ADQuery1->Open();
i=0;
while (!ADQuery1->Eof)
{
//ShowMessage("!!!");
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
outp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
outp2[i]=outp[i];
ADQuery1->Next();
}
ADQuery1->Close();*/
// FULL_OUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
ADQuery1->Open();
 i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
//ADQuery1->Close();
}
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
DN->Calculate(inp2);
//DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=1;j0<out_p;j0++)
{
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
//Series1->AddXY(12+j0,outp[j0]);
Series2->AddXY(in_p+j0,outp2[j0]);
}

//}

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button13Click(TObject *Sender)
{
// CASCADE!
int DN_loc_id=1;
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
const int dim=DN->ShowM()*DN->ShowN()*DN->ShowM();
double* cedg = new double[dim];
double* vedg = new double[dim];
AnsiString tmp_string;
cedg=DN->SaveCEdges();
vedg=DN->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(1)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button14Click(TObject *Sender)
{
int DN_loc_id=1;
const int dim=DN->ShowM()*DN->ShowN()*DN->ShowM();
double* cedg = new double[dim];
double* vedg = new double[dim];  //
int i;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.1 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 AND e_num>4999 AND e_num<10000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.2 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 AND e_num>9999 AND e_num<15000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.3 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 AND e_num>14999 AND e_num<20000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.4 done");


ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
//ShowMessage("2 done");

DN->LoadEdges(cedg,vedg);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button15Click(TObject *Sender)
{
Form5->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::CSpinEdit7Change(TObject *Sender)
{
try {
clearn=CSpinEdit7->Value;
}
catch (...)
{
clearn=100;
}
//delete learn_error;
//learn_error=new double[clearn+1];
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button16Click(TObject *Sender)
{
Series1->Clear();
Series2->Clear();
//int rep=0;
//if (clearn>500) rep=clearn%500;
for (int i=0;i<clearn;i++)
{
//if (!rep || !(i%rep))
//{
Series1->AddXY(i,0);
Series2->AddXY(i,learn_error[i]);
//}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel1Click(TObject *Sender)
{
CGauge1->MaxValue=Memo1->Lines->Count;
// PARSE!
for (int i=0;i<Memo1->Lines->Count;i++)
{
CGauge1->Progress=i+1;
        AnsiString S_T=Memo1->Lines->Strings[i];
        int length = S_T.Length();
        char s_year[5];
        char s_month[3];
        char s_day[3];
        char s_hour[3];
        char s_minute[3];
        char s_level[7];
        int state=0;
        int k=0;
        for (int j=1;j<=length;j++)
        {
                if (S_T[j]==' ' || S_T[j]==':')
                        { state++; k=0; j++; }
                if (state==1)
                        { s_year[k]=S_T[j]; s_year[k+1]='\0'; k++; if (k==4) { state=2; k=0; } }
                else if (state==2)
                        { s_month[k]=S_T[j]; s_month[k+1]='\0';  k++;  if (k==2) { state=3; k=0; } }
                else if (state==3)
                        { s_day[k]=S_T[j]; s_day[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==4)
                        { s_hour[k]=S_T[j]; s_hour[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==5)
                        { s_minute[k]=S_T[j]; s_minute[k+1]='\0';  k++; if (k==2) { k=0; } }
                else if (state==6)
                        { s_level[k]=S_T[j]; s_level[k+1]='\0';  k++;  }
        }
/*ListBox1->Items->Add(AnsiString(s_year));
ListBox2->Items->Add(AnsiString(s_month));
ListBox3->Items->Add(AnsiString(s_day));
ListBox4->Items->Add(AnsiString(s_hour));
ListBox5->Items->Add(AnsiString(s_minute));
ListBox6->Items->Add(AnsiString(s_level));*/
ADQuery2->SQL->Text="INSERT INTO H_DATA (id_station, s_year, s_month, s_day, s_hour, s_minute, s_level) VALUES ("+AnsiString(Edit1->Text)+", "+AnsiString(s_year)+", "+AnsiString(s_month)+", "+AnsiString(s_day)+", "+AnsiString(s_hour)+", "+AnsiString(s_minute)+", "+AnsiString(s_level)+");";
ADQuery2->ExecSQL();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel2Click(TObject *Sender)
{
ADQuery1->Close();
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->ExecSQL();
       
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Panel3Click(TObject *Sender)
{
ADQuery1->SQL->Text=Memo1->Text;
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel4Click(TObject *Sender)
{
// 1
// CASCADE!
int DN_loc_id=1;
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
const int dim=DN->ShowM()*DN->ShowN()*DN->ShowM();
double* cedg = new double[dim];
double* vedg = new double[dim];
AnsiString tmp_string;
cedg=DN->SaveCEdges();
vedg=DN->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(DN_loc_id)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}

//2
// CASCADE!
DN_loc_id=2;
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
//AnsiString tmp_string;
cedg=DNY->SaveCEdges();
vedg=DNY->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(DN_loc_id)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}

//3
// CASCADE!
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
cedg=DNM->SaveCEdges();
vedg=DNM->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(DN_loc_id)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}

//4
// CASCADE!
DN_loc_id=4;
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
cedg=DND->SaveCEdges();
vedg=DND->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(DN_loc_id)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}

//5

// CASCADE!
DN_loc_id=5;
ADQuery1->SQL->Text="DELETE FROM DN_EDGES WHERE DN_id="+AnsiString(DN_loc_id);
ADQuery1->ExecSQL();                                                                                                                 //
cedg=DNH->SaveCEdges();
vedg=DNH->SaveVEdges();
/*for (int j=0;j<dim;j++)
if (vedg[j]!=1)
{ ShowMessage(AnsiString(j)+":"+vedg[j]); }*/

CGauge1->MaxValue=dim;
for (int i=0;i<dim;i++)
{
CGauge1->Progress=i+1;
tmp_string=AnsiString(vedg[i]);
try
{
//if (vedg[i]!=1 && vedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES (+"+AnsiString(DN_loc_id)+", 0, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();                                                                                                                 //
}
catch (...)
{ ShowMessage("verr:"+AnsiString(i)+":"+tmp_string); }
//}
//for (int i=0;i<dim;i++)
//{   //
tmp_string=AnsiString(cedg[i]);
try {
//if (cedg[i]!=1 && cedg[i]!=0)
for(int j=1;j<tmp_string.Length();j++)
if (tmp_string[j]==',') { tmp_string[j]='.'; break; }
ADQuery1->SQL->Text="INSERT INTO DN_EDGES  (DN_id, e_type, e_num, e_value) VALUES ("+AnsiString(DN_loc_id)+", 1, "+AnsiString(i)+", "+tmp_string+");";
ADQuery1->ExecSQL();
}
catch (...)
{ ShowMessage("cerr:"+AnsiString(i)+":"+tmp_string); }
}



}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel5Click(TObject *Sender)
{
int DN_loc_id=1;
const int dim=DN->ShowM()*DN->ShowN()*DN->ShowM();
double* cedg = new double[dim];
double* vedg = new double[dim];  //
int i;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 ORDER BY e_num";// AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
/*//ShowMessage("1.1 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 AND e_num>4999 AND e_num<10000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.2 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 AND e_num>9999 AND e_num<15000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.3 done");
//
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(1)+" AND e_type=0 AND e_num>14999 AND e_num<20000 ORDER BY e_num";
ADQuery2->Open();
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
//if (!(i%1000))
//ShowMessage(AnsiString(i));
}
ADQuery2->Close();
//ShowMessage("1.4 done");

*/
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}//
ADQuery2->Close();
//ShowMessage("2 done");

DN->LoadEdges(cedg,vedg);
//2
DN_loc_id=2;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 ORDER BY e_num";// AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
DNY->LoadEdges(cedg,vedg);
//3
DN_loc_id=3;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 ORDER BY e_num";// AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
DNM->LoadEdges(cedg,vedg);
//4
DN_loc_id=4;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 ORDER BY e_num";// AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
DND->LoadEdges(cedg,vedg);
//5
DN_loc_id=5;
//this is not so correct, but whatta hell!
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=0 ORDER BY e_num";// AND e_num>0 AND e_num<5000 ORDER BY e_num";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
vedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
ADQuery2->SQL->Text="select * from DN_edges where DN_id="+AnsiString(DN_loc_id)+" AND e_type=1";
ADQuery2->Open();
i=0;
while (!ADQuery2->Eof)
{
i++;
cedg[i]=ADQuery2->FieldByName("e_value")->AsFloat;
ADQuery2->Next();
}
ADQuery2->Close();
DNH->LoadEdges(cedg,vedg);  //
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel6Click(TObject *Sender)
{
DN = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5); // canonic
DNY = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5); // year DN
DNM = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5); // month DN
DND = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5); // day DN
DNH = new Delta_Net(in_p,out_p,false,2,2,5,1,1,0.2,1,5); // hour DN
DHC = new DH_Converter();
DN->LearningState(true);
DN->Learning_SetAlpha(1);
DN->Learning_SetEpsilon(0.2);
DN->Learning_SetEtta(0.2);
DNM->LearningState(true);
DNM->Learning_SetAlpha(1);
DNM->Learning_SetEpsilon(0.2);
DNM->Learning_SetEtta(0.2);
DND->LearningState(true);
DND->Learning_SetAlpha(1);
DND->Learning_SetEpsilon(0.2);
DND->Learning_SetEtta(0.2);
DNH->LearningState(true);
DNH->Learning_SetAlpha(1);
DNH->Learning_SetEpsilon(0.2);
DNH->Learning_SetEtta(0.2);

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel10Click(TObject *Sender)
{
char buffer[1024];
if (OpenDialog1->Execute())
{
        ifstream r,f;
        bool state = false;
        AnsiString TMP;
        f.open((OpenDialog1->FileName).c_str(),ios::in);
        int numberof_m=0;
        int n=0;
        CGauge1->MinValue=0;
        CGauge1->MaxValue=2;
        randomize();
        while (!f.eof())
        {
        CGauge1->Progress=random(CGauge1->MaxValue);
        f.getline(buffer,1024);
        CGauge1->MaxValue++;
        }
        f.close();
        ShowMessage("Staring SQL process with "+AnsiString(CGauge1->MaxValue)+" rows!");
        r.open((OpenDialog1->FileName).c_str(),ios::in);
        for (int i=0;;i++)
        {
                r.getline(buffer,1024);
                CGauge1->Progress=i;
                TMP=AnsiString(buffer);
                if (TMP=="</pre>" || r.eof())
                break;
                else
                {
                        if (TMP=="Station Date     Time  Pred 6 Min.")
                                state=true;
                        else if (state)
                        {
                                AnsiString S_T=TMP;
                                int length = S_T.Length();
                                char s_year[5];
                                char s_month[3];
                                char s_day[3];
                                char s_hour[3];
                                char s_minute[3];
                                char s_level[7];
                                int state=0;
                                int k=0;
                                for (int j=1;j<=length;j++)
                                {
                                        if (S_T[j]==' ' || S_T[j]==':')
                                                { state++; k=0; j++; }
                                        if (state==1)
                                                { s_year[k]=S_T[j]; s_year[k+1]='\0'; k++; if (k==4) { state=2; k=0; } }
                                        else if (state==2)
                                                { s_month[k]=S_T[j]; s_month[k+1]='\0';  k++;  if (k==2) { state=3; k=0; } }
                                        else if (state==3)
                                                { s_day[k]=S_T[j]; s_day[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==4)
                                                { s_hour[k]=S_T[j]; s_hour[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==5)
                                                { s_minute[k]=S_T[j]; s_minute[k+1]='\0';  k++; if (k==2) { k=0; } }
                                        else if (state==6)
                                                { s_level[k]=S_T[j]; s_level[k+1]='\0';  k++;  }
                                }
                                ADQuery2->SQL->Text="INSERT INTO H_DATA (id_station, s_year, s_month, s_day, s_hour, s_minute, s_level) VALUES ("+ Edit1->Text + ", "+AnsiString(s_year)+", "+AnsiString(s_month)+", "+AnsiString(s_day)+", "+AnsiString(s_hour)+", "+AnsiString(s_minute)+", "+AnsiString(s_level)+");";
                                ADQuery2->ExecSQL();
                        }
                }
        }
r.close();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel11Click(TObject *Sender)
{
CGauge1->MaxValue=2008;
CGauge1->MinValue=1900;
for (int s_years=1900;s_years<2009;s_years++)
{
CGauge1->Progress=s_years;
for (int s_months=1;s_months<13;s_months++)
{

ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_days("+AnsiString(Edit1->Text)+","+AnsiString(s_years)+","+AnsiString(s_months)+");";
ADQuery1->ExecSQL();
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel12Click(TObject *Sender)
{
CGauge1->MaxValue=2008;
CGauge1->MinValue=1900;
for (int s_years=1900;s_years<2009;s_years++)
{
CGauge1->Progress=s_years;
ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_months("+AnsiString(Edit1->Text)+","+AnsiString(s_years)+");";
ADQuery1->ExecSQL();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel13Click(TObject *Sender)
{
ADQuery1->Close();
ADQuery1->SQL->Text="CALL insert_years("+AnsiString(Edit1->Text)+");";
ADQuery1->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel7Click(TObject *Sender)
{
// converters
int ry=0,rm,rd,rh,rs;
double dvalue=-100,mvalue=-100,yvalue=-100;
for (int m=0;m<clearn;m++)
learn_error[m]=0;
CGauge1->MaxValue=clearn;
randomize();
for (int k=0;k<clearn;k++)
{
CGauge1->Progress=k+1;
// randomize each learn
if (!LOSS->Checked)
rs=random(5)+1; // 1-5
else
rs=Edit1->Text.ToInt();
ry=random(106)+1902; // 1902-2007
rm=random(12)+1; // 1-12
rd=random(12)+1; //1-12
rh=random(6); // 0-6
        // INPUT

/////////////////////////////////////
/*        ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
        {
        i++;
        inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
        ADQuery1->Next();
        }
        ADQuery1->Close();

        // FULL_OUT
        ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
        {
        i++;
        inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
        ADQuery1->Next();
        }
        ADQuery1->Close();
*/
///////////////////////////////////////////
/*        DHC->ConvertDays(ry,rm,rd,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        Memo1->Lines->Add("O:"+DHC->ReturnDQuery());
        //ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++; //
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertDays(ry,rm,rd,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        Memo1->Lines->Add("F:"+DHC->ReturnDQuery());
        //ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox2->Checked)
                inp2[0]=mvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        DND->Learn(inp2,outp);
        //DN->Calculate(inp2);
        outp2=DND->Display();
        dvalue=outp2[1];
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
        outp[j]=canonic_output_real[j+in_p];
DN->Learn(inp2,outp);
outp2=DN->Display(); */

// YEARS
        if ((CheckBox1->Checked  && WOCR->Checked) || !WOCR->Checked)
        {
        }
// MONTHS //
        if ((CheckBox2->Checked  && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertMonths(ry,rm,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();;
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertMonths(ry,rm,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();;
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox1->Checked)
                inp2[0]=yvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        if (CheckBox2->Checked)
        {
        DNM->Learn(inp2,outp);
        outp2v=outp2;
        canonic_output_realv=canonic_output_real;
        }
        else
        DNM->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DNM->Display();
        mvalue=outp2[1];
        //ShowMessage(mvalue);
        }
// DAYS
        if ((CheckBox3->Checked && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertDays(ry,rm,rd,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertDays(ry,rm,rd,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox2->Checked)
                inp2[0]=mvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        if (CheckBox3->Checked)
        {
        DND->Learn(inp2,outp);
        outp2v=outp2;
        canonic_output_realv=canonic_output_real;
        }
        else
        DND->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DND->Display();
        dvalue=outp2[1];
        }
// HOURS
        if ((CheckBox4->Checked && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertHours(ry,rm,rd,rh,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnHQuery();
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertHours(ry,rm,rd,rh,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnHQuery();
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox3->Checked)
                inp2[0]=dvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        if (CheckBox4->Checked)
        {
        DNH->Learn(inp2,outp);
        outp2v=outp2;
        canonic_output_realv=canonic_output_real;
        }
        else DNH->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DNH->Display();
        }


  /*      canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        DN->Learn(inp2,outp);
    */
double buf1=0, buf2=0;
for (int n=0;n<(in_p+out_p);n++)
        {
        if (canonic_output_real[n]<buf1)
                buf1=canonic_output_realv[n];
        if (canonic_output_real[n]>buf2)
                buf2=canonic_output_realv[n];
        }
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
Form6->Series1->AddXY(i0,canonic_output_real[i0]);
Form6->Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=1;j0<out_p;j0++)
{
        if (abs(buf1-buf2))
                learn_error[k]+=(canonic_output_realv[j0+in_p]-outp2v[j0])/abs(buf1-buf2);
        else
                learn_error[k]+=canonic_output_realv[j0+in_p]-outp2v[j0];
        Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
        Series2->AddXY(in_p+j0,outp2[j0]);
        Form6->Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
        Form6->Series2->AddXY(in_p+j0,outp2[j0]);
}
Form6->Chart1->Title->Text->Clear();
if (ry)
{
        Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction on: "+AnsiString(rd+16)+"."+AnsiString(rm)+"."+AnsiString(ry)+" station id="+AnsiString(rs));
        if (rs==1)
                Form6->Chart1->Title->Text->Add("Port Allen, Hanapepe bay, Kauai Island");
        else if (rs==2)
                Form6->Chart1->Title->Text->Add("Chicago");
        else if (rs==3)
                Form6->Chart1->Title->Text->Add("Los-Angeles");
        else if (rs==4)
                Form6->Chart1->Title->Text->Add("Yakutat, Alaska");
        else if (rs==5)
                Form6->Chart1->Title->Text->Add("Unalaska, Alaska");
}
else Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction");
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel8Click(TObject *Sender)
{
/*double* inp = new double[in_p+out_p];
double* inp2 = new double[in_p];
double* inp_inrange = new double[in_p];
double* outp = new double[out_p];
double* outp2 = new double[out_p];
double* canonic_output_real=new double[in_p+out_p];
randomize();
if (Form5->CheckBox1->Checked)
{//for (int k=0;k<10;k++)
//{
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(out_p+in_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
}
}
//ADQuery1->SQL->Text=Memo1->Text;
else
{
int ry,rm,rd,rs,rh=0;
if (Rcalc->Checked) // random calculations
{
        ry=random(107)+1901;
        rm=random(12)+1;
        rd=random(10)+1;
        rs=random(5)+1;
}
else // selected calculations
{
        //int intervals=CSpinEdit4->Value;
        int intervals=16;
        int a_years=CSpinEdit1->Value;
        int a_months=CSpinEdit2->Value;
        int a_days=CSpinEdit3->Value;
        int a_hours=CSpinEdit6->Value;
        int d_months, d_days, d_hours;
        //int s_year; s_month; s_day; s_hour; // results
        d_hours=a_hours-intervals;
        if (d_hours>=0) // interval less than one day
                {
                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(a_days)+" "+AnsiString(d_hours);
                //{
                ry=a_years; rm=a_months; rd=a_days; rh=d_hours; rs=Edit1->Text.ToInt();
                }
        else
        {
                d_days=a_days-(1-int(d_hours/24));
                if (d_days>1)
                        if (d_hours%24!=0)
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                //{
                                ry=a_years; rm=a_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                }
                        else
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                //{
                                ry=a_years; rm=a_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                }
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                //Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                if (d_hours%24!=0)
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                        }
                                else
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                        }
                                }
                        }
                }
        }
// INPUT
ShowMessage("Binput done");
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year>="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year>="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT "+AnsiString(in_p);
ADQuery1->Open();
Series1->Clear();
int i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
//inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
ADQuery1->Close();
ShowMessage("input done");
//Sleep(500);
*//* OUTPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(Edit1->Text)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd+in_p)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p);
ADQuery1->Open();
i=0;
while (!ADQuery1->Eof)
{
//ShowMessage("!!!");
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
outp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
outp2[i]=outp[i];
ADQuery1->Next();
}
ADQuery1->Close();*//*
// FULL_OUT
ShowMessage("BFinput done");
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year>="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year>="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT "+AnsiString(out_p+in_p);
ADQuery1->Open();
ShowMessage("FOinput done");
 i=0;
ShowMessage("ry:"+AnsiString(ry)+"rm:"+AnsiString(rm)+"rd:"+AnsiString(rd)+"rh:"+AnsiString(rh));
while (!ADQuery1->Eof || i!=19)
{
//ShowMessage("whatta hell?"+AnsiString(i));
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
ShowMessage("FBCinput done");
ADQuery1->Close();
ShowMessage("Finput done");   //
}
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
DN->Calculate(inp2);
//DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=1;j0<out_p;j0++)
{
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
//Series1->AddXY(12+j0,outp[j0]);
Series2->AddXY(in_p+j0,outp2[j0]);
}

//}

*/
/*DN->Learning_SetAlpha(1);
DN->Learning_SetEpsilon(0.2);
DN->Learning_SetEtta(0.2);
DN->LearningState(true);  */
/*int ry=0,rm,rd,rs,rh;
randomize();
if (Form5->CheckBox1->Checked)
{//for (int k=0;k<10;k++)
//{
ND=100+(-50+random(1000)*0.1);
if (!ND)
ND=1;

for (int i=0;i<(out_p+in_p);i++)
{
inp[i]=sin((i*0.2)/(ND*0.01));
if (i<12)
inp2[i]=sin((i*0.2)/(ND*0.01));
}
}
//ADQuery1->SQL->Text=Memo1->Text;
else
{
if (Rcalc->Checked)
        {
        ry=random(107)+1901;
        rm=random(12)+1;
        rd=random(12)+1;
        rs=random(5)+1;
        }
else
        {
        ry=CSpinEdit1->Value;
        rm=CSpinEdit2->Value;
        rd=CSpinEdit3->Value;
        rh=CSpinEdit6->Value;
        // ONLY TESTING
        int a_years=CSpinEdit1->Value;
        int a_months=CSpinEdit2->Value;
        int a_days=CSpinEdit3->Value;
        int a_hours=CSpinEdit6->Value;
        int d_months, d_days, d_hours;
        //int s_year; s_month; s_day; s_hour; // results
        d_hours=a_hours-in_p;
        if (d_hours>=0) // interval less than one day
                {
                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(a_days)+" "+AnsiString(d_hours);
                //{
                ry=a_years; rm=a_months; rd=a_days; rh=d_hours; rs=Edit1->Text.ToInt();
                }
        else
        {
                d_days=a_days-(1-int(d_hours/24));
                if (d_days>1)
                        if (d_hours%24!=0)
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                //{
                                ry=a_years; rm=a_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                }
                        else
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                //{
                                ry=a_years; rm=a_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                }
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                //Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                if (d_hours%24!=0)
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                        }
                                else
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                        }
                                }
                        }
                }
        }
// INPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(in_p);
ADQuery1->Open();
Series1->Clear();
int i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
//inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
ADQuery1->Close();*/
//Sleep(500);
/*// OUTPUT
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(Edit1->Text)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd+in_p)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p);
ADQuery1->Open();
i=0;
while (!ADQuery1->Eof)
{
//ShowMessage("!!!");
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
outp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
outp2[i]=outp[i];
ADQuery1->Next();
}
ADQuery1->Close();*/
// FULL_OUT
/*ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>"+AnsiString(rd)+" AND s_day<"+AnsiString(rd+in_p+out_p)+" ORDER BY s_year, s_month, s_day ASC LIMIT 0,"+AnsiString(out_p+in_p);
ADQuery1->Open();
 i=0;
while (!ADQuery1->Eof)
{
i++;
//Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
ADQuery1->Next();
}
//ADQuery1->Close();
}
canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
for (int j=0;j<out_p;j++)
outp[j]=canonic_output_real[j+in_p];
//DN->Learn(inp,outp);
DN->Calculate(inp2);
//DN->Calculate(inp2);
outp2=DN->Display();

Series1->Clear();
Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=1;j0<out_p;j0++)
{
Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
//Series1->AddXY(12+j0,outp[j0]);
Series2->AddXY(in_p+j0,outp2[j0]);
Form6->Chart1->Title->Text->Clear();
if (ry)
{
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction on: "+AnsiString(rd+16)+"."+AnsiString(rm)+"."+AnsiString(ry)+" station id="+AnsiString(rs));
if (rs==1)
Form6->Chart1->Title->Text->Add("Port Allen, Hanapepe bay, Kauai Island");
else if (rs==2)
Form6->Chart1->Title->Text->Add("Chicago");
else if (rs==3)
Form6->Chart1->Title->Text->Add("Los-Angeles");
else if (rs==4)
Form6->Chart1->Title->Text->Add("Yakutat, Alaska");
else if (rs==5)
Form6->Chart1->Title->Text->Add("Unalaska, Alaska");
}
else Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction");
}

//}

*/

int ry=0,rm,rd,rh,rs;
double dvalue=-100,mvalue=-100,yvalue=-100;
//for (int m=0;m<clearn;m++)
//learn_error[m]=0;
//CGauge1->MaxValue=clearn;
randomize();
//CGauge1->Progress=k+1;
// randomize each learn
if (Rcalc->Checked)
{
if (!LOSS->Checked)
rs=random(5)+1; // 1-5
else
rs=Edit1->Text.ToInt();
ry=random(106)+1902; // 1902-2007
rm=random(12)+1; // 1-12
rd=random(12)+1; //1-12
rh=random(6); // 0-6
}
else
{
ry=CSpinEdit1->Value;
rm=CSpinEdit2->Value;
rd=CSpinEdit3->Value;
rh=CSpinEdit6->Value;
rs=Edit1->Text.ToInt();
}
        // INPUT

// YEARS
        if ((CheckBox1->Checked  && WOCR->Checked) || !WOCR->Checked)
        {
//        DHC->ConvertYears(ry,rm,in_p,rs);
/*        ADQuery1->SQL->Text=DHC->ReturnMQuery();;
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertMonths(ry,rm,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        DNY->Learn(inp2,outp);
        //DN->Calculate(inp2);
        outp2=DNY->Display();
        yvalue=outp2[1];
*/        }
// MONTHS //
        if ((CheckBox2->Checked  && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertMonths(ry,rm,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();;
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertMonths(ry,rm,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();;
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox1->Checked)
                inp2[0]=yvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        DNM->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DNM->Display();
        mvalue=outp2[1];
        //ShowMessage(mvalue);
        }
// DAYS
        if ((CheckBox3->Checked && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertDays(ry,rm,rd,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertDays(ry,rm,rd,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnDQuery();
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox2->Checked)
                inp2[0]=mvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        DND->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DND->Display();
        dvalue=outp2[1];
        }
// HOURS
        if ((CheckBox4->Checked && WOCR->Checked) || !WOCR->Checked)
        {
        DHC->ConvertHours(ry,rm,rd,rh,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnHQuery();
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp2[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        DHC->ConvertHours(ry,rm,rd,rh,in_p+out_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnHQuery();
        ADQuery1->Open();
        i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        if (CheckBox3->Checked)
                inp2[0]=dvalue;
        canonic_output_real=CompressOutput(inp,(out_p+in_p),5,1);
        for (int j=0;j<out_p;j++)
                outp[j]=canonic_output_real[j+in_p];
        //DN->Learn(inp,outp);
        DNH->Calculate(inp2);
        //DN->Calculate(inp2);
        outp2=DNH->Display();
        }


Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
for (int i0=1;i0<in_p;i0++)
{
Series1->AddXY(i0,canonic_output_real[i0]);
Series2->AddXY(i0,canonic_output_real[i0]);
Form6->Series1->AddXY(i0,canonic_output_real[i0]);
Form6->Series2->AddXY(i0,canonic_output_real[i0]);
}
for (int j0=1;j0<out_p;j0++)
{
        Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
        Series2->AddXY(in_p+j0,outp2[j0]);
        Form6->Series1->AddXY(in_p+j0,canonic_output_real[j0+in_p]);
        Form6->Series2->AddXY(in_p+j0,outp2[j0]);
}
Form6->Chart1->Title->Text->Clear();
if (ry)
{
        Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction on: "+AnsiString(rd+16)+"."+AnsiString(rm)+"."+AnsiString(ry)+" station id="+AnsiString(rs));
        if (rs==1)
                Form6->Chart1->Title->Text->Add("Port Allen, Hanapepe bay, Kauai Island");
        else if (rs==2)
                Form6->Chart1->Title->Text->Add("Chicago");
        else if (rs==3)
                Form6->Chart1->Title->Text->Add("Los-Angeles");
        else if (rs==4)
                Form6->Chart1->Title->Text->Add("Yakutat, Alaska");
        else if (rs==5)
                Form6->Chart1->Title->Text->Add("Unalaska, Alaska");
}
else Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel9Click(TObject *Sender)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();

//int rep=0;
//if (clearn>500) rep=clearn%500;
double buf1,buf2,min,max,sum1=0,sum2=0,dispersion=0;
buf1=buf2=min=max=learn_error[0];
for (int i=0;i<clearn;i++)
{
//if (!rep || !(i%rep))
//{
sum1+=(learn_error[i]/(out_p-1))*100;
//sum2+=abs((learn_error[i]/out_p)*10000)/100.00;
if (learn_error[i]>buf1)
buf1=learn_error[i]/(out_p-1);
if (learn_error[i]<buf2)
buf2=learn_error[i]/(out_p-1);
if (abs(learn_error[i])<min)
min=abs((learn_error[i]/(out_p-1))*10000)/100.000;
Series1->AddXY(i,0);
Series2->AddXY(i,learn_error[i]/(out_p-1));
Form6->Series1->AddXY(i,0);
Form6->Series2->AddXY(i,learn_error[i]/(out_p-1));
//}              //
}
if (abs(buf1*10000)>abs(buf2*10000))
max=(abs(buf1*10000)/100.000);
else max=(abs(buf2*10000)/100.000);
sum2=abs(sum1*10000)/10000.000;
dispersion=abs((buf1-buf2)*10000)/100.000;
//ShowMessage("ABS b1-b2: "+AnsiString(abs((buf1-buf2)*10000)/10000.000));
//ShowMessage("b1-b2: "+AnsiString(((buf1-buf2)*10000)/10000.000));
//ShowMessage("Abs float b1-b2: "+AnsiString(abs(float((buf1-buf2)*10000))/10000.000));
//ShowMessage(AnsiString(buf1)+" "+AnsiString(buf2)+" "+AnsiString(abs(buf1-buf2)/clearn));
ShowMessage("Average: "+AnsiString(sum1/clearn)+"\nAbs average: "+AnsiString(sum2/clearn)+"\nMinimum: "+AnsiString(min)+"\nMaximum: "+AnsiString(max)+"\nDispersion: "+AnsiString(dispersion)+"\nAverage dispersion: "+AnsiString(dispersion/clearn));
//Memo1->Lines->Clear();
//Memo1->Lines->Add("Average: "+AnsiString(sum1/clearn)+"\nAbs average: "+AnsiString(sum2/clearn)+"\nMinimum: "+AnsiString(min)+"\nMaximum: "+AnsiString(max)+"\nDispersion: "+AnsiString(dispersion)+"\nAverage dispersion: "+AnsiString(dispersion/clearn));
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction deviations");
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Panel14Click(TObject *Sender)
{
Form6->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel16Click(TObject *Sender)
{
Form3->Visible=true;
Form3->Close();
Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Panel15Click(TObject *Sender)
{
Form1->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button17Click(TObject *Sender)
{
int ry,rm,rd,rh,rs;   //
        ry=CSpinEdit1->Value;
        rm=CSpinEdit2->Value;
        rd=CSpinEdit3->Value;
        rh=CSpinEdit6->Value;
        /* ONLY TESTING*/
        int a_years=CSpinEdit1->Value;
        int a_months=CSpinEdit2->Value;
        int a_days=CSpinEdit3->Value;
        int a_hours=CSpinEdit6->Value;
        int d_months, d_days, d_hours;
        //int s_year; s_month; s_day; s_hour; // results
        d_hours=a_hours-in_p;
        if (d_hours>=0) // interval less than one day
                {
                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(a_days)+" "+AnsiString(d_hours);
                //{
                ry=a_years; rm=a_months; rd=a_days; rh=d_hours; rs=Edit1->Text.ToInt();
                }
        else
        {
                d_days=a_days-(1-int(d_hours/24));
                if (d_days>1)
                        if (d_hours%24!=0)
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                //{
                                ry=a_years; rm=a_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                }
                        else
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                //{
                                ry=a_years; rm=a_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                }
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                //Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                if (d_hours%24!=0)
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                        }
                                else
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                        }
                                }
                        }

                }
if ((a_hours-in_p)<0)
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day="+AnsiString(rd)+" AND s_hour>"+AnsiString(rh)+" GROUP BY id_station, s_year, s_month, s_day, s_hour UNION select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day="+AnsiString(a_days)+" AND s_hour<="+AnsiString(a_hours)+" GROUP BY id_station, s_year, s_month, s_day, s_hour";
else
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day="+AnsiString(rd)+" AND s_hour>"+AnsiString(rh)+" GROUP BY id_station, s_year, s_month, s_day, s_hour LIMIT "+AnsiString(in_p);
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day="+AnsiString(a_days)+" AND s_hour<="+AnsiString(a_hours)+" GROUP BY id_station, s_year, s_month, s_day, s_hour";
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button18Click(TObject *Sender)
{
int ry,rm,rd,rh,rs;
        ry=CSpinEdit1->Value;
        rm=CSpinEdit2->Value;
        rd=CSpinEdit3->Value;
        rh=0;
        /* ONLY TESTING*/
        int a_years=CSpinEdit1->Value;
        int a_months=CSpinEdit2->Value;
        int a_days=CSpinEdit3->Value;
        int a_hours=CSpinEdit6->Value;
        int d_months, d_days, d_hours;
        //int s_year; s_month; s_day; s_hour; // results
        d_hours=0;
                //d_days=a_days-(1-int(d_hours/24));
                d_days=a_days-in_p;
                if (d_days>0)
                        if (d_hours%24!=0)
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                //{
                                ry=a_years; rm=a_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                }
                        else
                                {
                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(a_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                //{
                                ry=a_years; rm=a_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                }
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        if (d_hours%24!=0)
                                                {
                                                Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                                }
                                        else
                                                {
                                                //Edit2->Text=AnsiString(a_years)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                                //{
                                                ry=a_years; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                                }
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                if (d_hours%24!=0)
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days)+" "+AnsiString(24*(1-int(d_hours/24))+d_hours);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours; rs=Edit1->Text.ToInt();
                                        }
                                else
                                        {
                                        Edit2->Text=AnsiString(a_years-1)+" "+AnsiString(d_months)+" "+AnsiString(d_days+1)+" "+AnsiString(0);
                                        //{
                                        ry=a_years-1; rm=d_months; rd=d_days+1; rh=0; rs=Edit1->Text.ToInt();
                                        }
                                }
                        }

//ShowMessage(AnsiString(rd)+" "+AnsiString(a_days));
if ((a_days-in_p)<=0)
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" UNION select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day<="+AnsiString(a_days);
else
ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" LIMIT "+AnsiString(in_p);
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button19Click(TObject *Sender)
{
int ry,rm,rd,rh,rs;
        ry=CSpinEdit1->Value;
        rm=CSpinEdit2->Value;
        rd=CSpinEdit3->Value;
        rh=0;
        /* ONLY TESTING*/
        int a_years=CSpinEdit1->Value;
        int a_months=CSpinEdit2->Value;
        int a_days=CSpinEdit3->Value;
        int a_hours=CSpinEdit6->Value;
        int d_months, d_days, d_hours;
        if (((a_months-in_p)<-11) || a_months<5)
        {
        ry=a_years-2;
        rm=24+a_months-in_p;
        ADQuery1->SQL->Text="select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry+1)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month<"+AnsiString(a_months);
        }
        else
        {
        ry=a_years-1;
        rm=12+a_months-in_p;
        ADQuery1->SQL->Text="select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month<"+AnsiString(a_months);
        }
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button20Click(TObject *Sender)
{
DHC->ConvertHours(CSpinEdit1->Value,CSpinEdit2->Value,CSpinEdit3->Value,CSpinEdit6->Value,in_p,Edit1->Text.ToInt());
ADQuery1->SQL->Text=DHC->ReturnHQuery();
//ADQuery1->SQL->Text="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+Edit1->Text+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day="+AnsiString(a_days)+" AND s_hour<="+AnsiString(a_hours)+" GROUP BY id_station, s_year, s_month, s_day, s_hour";
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button21Click(TObject *Sender)
{
DHC->ConvertDays(CSpinEdit1->Value,CSpinEdit2->Value,CSpinEdit3->Value,in_p,Edit1->Text.ToInt());
ADQuery1->SQL->Text=DHC->ReturnDQuery();
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button22Click(TObject *Sender)
{
DHC->ConvertMonths(CSpinEdit1->Value,CSpinEdit2->Value,in_p,Edit1->Text.ToInt());
ADQuery1->SQL->Text=DHC->ReturnMQuery();
ADQuery1->Open();
int i=0;
if (GFS_cb->Checked)
{
Series1->Clear();
Series2->Clear();
Form6->Series1->Clear();
Form6->Series2->Clear();
while (!ADQuery1->Eof)
{
i++;
Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
Form6->Series1->AddXY(i,ADQuery1->FieldByName("a_level")->AsFloat);
ADQuery1->Next();
}
}
Form6->Chart1->Title->Text->Clear();
Form6->Chart1->Title->Text->Add("Nana.Sealevel.Prediction user query select");
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button23Click(TObject *Sender)
{
double* inp = new double[in_p+out_p];
        int ry,rm,rd,rh,rs;
        randomize();
        for (int i=0;i<100;i++)
        {
        rs=random(5)+1;
        ry=random(105)+1902;
        rm=random(12)+1;
        rd=random(12)+1;
        rh=random(6);
        DHC->ConvertMonths(ry,rm,in_p,rs);
        ADQuery1->SQL->Text=DHC->ReturnMQuery();
        ADQuery1->Open();
        int i=0;
        while (!ADQuery1->Eof)
                {
                i++;
                inp[i]=ADQuery1->FieldByName("a_level")->AsFloat;
                ADQuery1->Next();
                }
        ADQuery1->Close();
        }
}                 //
//---------------------------------------------------------------------------


void __fastcall TForm4::CheckBox3Enter(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=true;
CheckBox4->Checked=false;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm4::CheckBox3Exit(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=true;
CheckBox4->Checked=false;
}        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::CheckBox4Enter(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=false;
CheckBox4->Checked=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::CheckBox4Exit(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=false;
CheckBox4->Checked=true;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm4::CheckBox2Exit(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=true;
CheckBox3->Checked=false;
CheckBox4->Checked=false;
}        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::CheckBox2Enter(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=true;
CheckBox3->Checked=false;
CheckBox4->Checked=false;
}        
}
//---------------------------------------------------------------------------


void __fastcall TForm4::CheckBox1Enter(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=true;
CheckBox2->Checked=false;
CheckBox3->Checked=false;
CheckBox4->Checked=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::CheckBox1Exit(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=true;
CheckBox2->Checked=false;
CheckBox3->Checked=false;
CheckBox4->Checked=false;
}        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::WOCREnter(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=true;
CheckBox4->Checked=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::WOCRExit(TObject *Sender)
{
if (WOCR->Checked)
{
CheckBox1->Checked=false;
CheckBox2->Checked=false;
CheckBox3->Checked=true;
CheckBox4->Checked=false;
} //
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
//Form3->Show(); //
Form5->ShowModal();
}
//---------------------------------------------------------------------------

