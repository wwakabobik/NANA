//---------------------------------------------------------------------------

#include "NAFunctions.h"
#include <Math.h>
#include <vcl.h>

//---------------------------------------------------------------------------


double FAEqual(double net, double thetta)
{
return net*thetta;
}

double FABarierS(double net, double thetta)
{
if (net>=thetta)
return 1;
else return 0;
}

double FABarierH(double net, double thetta)
{
net+=1;
if (net>=0)
return 1;
else return 0;
}

double FASigma(double net, double thetta)
{
double solve;
if (net<-5)
return 0.0;
if (net>5)
return 1.0;
solve=1.000/(1.000+exp((-net*thetta)));
// this is not correct, but what?
//solve=solve*10.0-5.0;
return solve;
}

  double FATanh(  double net,   double thetta)
{
  double solve;
solve= (exp(net*thetta)-exp(-net*thetta)) / (exp(net*thetta)+exp(-net*thetta));
return solve;
}

  double FAAbs(  double net)
{
return abs(net);
}

  double FAExp(  double net,   double thetta)
{
  double solve;
solve=exp(-net*thetta);
return solve;
}

  double FAStatic(  double thetta)
{
return thetta;
}

  double FAZero()
{
return 0;
}

/*ONLY FOR TESTING*/

double* CompressInput(double input[],int n,int type,int etta)
{
double betta=5.0;

double* new_input = new double[n];
double max,min;
max=input[0];
min=input[0];
for (int i=0;i<n;i++)
{ if (max<input[i]) max=input[i]; if (min>input[i]) min=input[i]; }
for (int j=0;j<n;j++)
new_input[j]=input[j]-min;
switch (type)
{
        case 5:
        {
        for (int k=0;k<n;k++)
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

double* CompressOutput(double output[],int n,int type,int etta)
{
double betta=1;

double* new_output = new double[n];
double max,min;
max=output[0];
min=output[0];
for (int i=0;i<n;i++)
{ if (max<output[i]) max=output[i]; if (min>output[i]) min=output[i]; }
for (int j=0;j<n;j++)
new_output[j]=output[j]-min;
switch (type)
{
        case 5:
        {
        for (int k=0;k<n;k++)
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

