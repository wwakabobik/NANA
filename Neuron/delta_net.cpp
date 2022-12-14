//---------------------------------------------------------------------------


#pragma hdrstop

#include <stdlib.h>
#include "delta_net.h"
#include "NeuralNet.h"
#include <vcl.h>


bool is_contains(int c_array[],int n,int c_number)
{
for (int i=0;i<n;i++)
if(c_array[i]==c_number)
return true;
return false;
}

Delta_Net::Delta_Net()
{
        linear=false;
        delivery=0;
        inputs=0;
        outputs=0;
        compress_state=0;
        calc_state=0;
        layer_count=0;
        layer_regress=0;
        thetta=0;
        type=0;
        DNet=0;
        static_etta=0;
}

Delta_Net::~Delta_Net()
{
        delivery=0;
        inputs=0;
        outputs=0;
        compress_state=0;
        calc_state=0;
        layer_count=0;
        layer_regress=0;
        thetta=0;
        type=0;
        delete DNet;
        static_etta=0;
}

Delta_Net::Delta_Net(int new_inputs, int new_outputs, bool new_linear, int new_compress_state, int new_delivery, int new_calc_state, int new_layer_count, int new_layer_regress, double new_static_etta, double new_thetta, int new_type)
{
        linear=new_linear;
        delivery=new_delivery;
        inputs=new_inputs;
        outputs=new_outputs;
        compress_state=new_compress_state;
        calc_state=new_calc_state;
        layer_count=new_layer_count;
        layer_regress=new_layer_regress;
        thetta=new_thetta;
        type=new_type;
        static_etta=new_static_etta;
        N=5+layer_count;
        M=(inputs/compress_state)*calc_state;
        DNet=new NeuralNet(N,M,type,thetta);
        Set_Input_Layer();
        Set_Compress_Layer();
        Set_CalcNN();
        Set_Output_Layer();
}

void Delta_Net::Set_Input_Layer()
{
for (int i=0;i<inputs;i++)
        DNet->SetNeuron(0,i,type,thetta);
for (int j=inputs;j<M;j++)
        DNet->SetNeuron(0,j,0,0);
for (int k=0;k<M;k++)
        for (int l=0;l<M;l++)
                { DNet->SetConstEdge(0,k,l,1);  DNet->SetEdgeValue(0,k,l,1); }
}

void Delta_Net::Set_Compress_Layer()
{
        // Set compress layer
                // Set Neurons
for (int i=0;i<inputs/compress_state;i++)
        DNet->SetNeuron(1,i,type,thetta);
for (int j=inputs/compress_state;j<M;j++)
        DNet->SetNeuron(1,j,0,0);

                // Set Layers
if (!linear)
{
        for (int m=0;m<inputs/compress_state;m++)
        {
        for (int k0=0;k0<m*compress_state;k0++)
                { DNet->SetConstEdge(1,m,k0,0);  DNet->SetEdgeValue(1,m,k0,0); }
        for (int k=m*compress_state;k<m*compress_state+compress_state;k++)
                { DNet->SetConstEdge(1,m,k,static_etta);  DNet->SetEdgeValue(1,m,k,static_etta); }
        for (int k1=m*compress_state+compress_state;k1<M;k1++)
                { DNet->SetConstEdge(1,m,k1,0);        DNet->SetEdgeValue(1,m,k1,0); }
        }
}
else
{
        for (int m=0;m<M;m++)
        {
        for (int k0=0;k0<inputs/compress_state;k0++)
                { DNet->SetConstEdge(1,m,k0,static_etta);  DNet->SetEdgeValue(1,m,k0,static_etta); }
        for (int k0=inputs/compress_state;k0<M;k0++)
                { DNet->SetConstEdge(1,m,k0,0);  DNet->SetEdgeValue(1,m,k0,0); }
        }
}

        // Set second input layer
                // Set Neurons
for (int a=0;a<inputs/compress_state;a++)
        DNet->SetNeuron(2,a,type,thetta);
for (int b=inputs/compress_state;b<M;b++)
        DNet->SetNeuron(2,b,0,0);

               // Set Layers
for (int aa=0;aa<inputs/compress_state;aa++)
        for (int bb=0;bb<inputs/compress_state;bb++)
                if (aa==bb)
                        { DNet->SetConstEdge(2,aa,bb,static_etta);  DNet->SetEdgeValue(2,aa,bb,static_etta); }
                else
                        { DNet->SetConstEdge(2,aa,bb,0);  DNet->SetEdgeValue(2,aa,bb,0); }
for (int aa1=inputs/compress_state;aa1<M;aa1++)
        for (int bb1=inputs/compress_state;bb1<M;bb1++)
                { DNet->SetConstEdge(2,aa1,bb1,0);  DNet->SetEdgeValue(2,aa1,bb1,0); }
}

void Delta_Net::Set_Calc_Layer(int LayerNumber)
{
//int delivery = 2; // this is real input state
if (LayerNumber==3)
{
        int part_net=0;
        for (int i=0;i<M;i++)
        {
        //ShowMessage("Layer 3, i="+AnsiString(i));
                if (i==(part_net+1)*calc_state*delivery)
                        part_net++;
                for (int j=0;j<part_net*delivery;j++)
                        { DNet->SetEdgeValue(LayerNumber,i,j,0); DNet->SetConstEdge(LayerNumber,i,j,0); }
                for (int j=part_net*delivery;j<(part_net+1)*delivery;j++)
                        { DNet->SetEdgeValue(LayerNumber,i,j,static_etta); DNet->SetConstEdge(LayerNumber,i,j,static_etta); }
                for (int j=(part_net+1)*delivery;j<M;j++)
                        { DNet->SetEdgeValue(LayerNumber,i,j,0); DNet->SetConstEdge(LayerNumber,i,j,0); }
        }
}
else if (LayerNumber>3) // this is polylayer
{
        int* TEdgesArray = new int[M/(layer_regress*(LayerNumber-3))+1];
        randomize();
        for (int k=0;k<M/layer_regress*(LayerNumber-3)+1;k++)
                TEdgesArray[k]=random(M);
        for (int i=0;i<M;i++)
                if (is_contains(TEdgesArray,M/(layer_regress*(LayerNumber-3))+1,i))
                        for (int j=0;j<M;j++)
                                { DNet->SetEdgeValue(LayerNumber,i,j,static_etta); DNet->SetConstEdge(LayerNumber,i,j,static_etta); }

                else
                        for (int j=0;j<M;j++)
                                { DNet->SetEdgeValue(LayerNumber,i,j,0); DNet->SetConstEdge(LayerNumber,i,j,0); }
}
if (LayerNumber==2+layer_count) // this is last one, set outputs
{
                // Set neurons
        for (int k0=0;k0<outputs*((inputs/compress_state)/delivery);k0++)
                DNet->SetNeuron(LayerNumber+1,k0,type,thetta);
        for (int k0=outputs*((inputs/compress_state)/delivery);k0<M;k0++)
                DNet->SetNeuron(LayerNumber+1,k0,0,0);
                // Set edges
        int part_net=0;
        for (int i0=0;i0<M;i0++)
        {
        if (i0%outputs==0 && i0!=0)
//        if (i0%outputs==0)
        part_net++;
                for (int j0=0;j0<part_net*delivery*calc_state;j0++)
                                { DNet->SetEdgeValue(LayerNumber+1,i0,j0,0); DNet->SetConstEdge(LayerNumber+1,i0,j0,0); }
                for (int j0=part_net*delivery*calc_state;j0<(part_net+1)*delivery*calc_state;j0++)
                                { DNet->SetEdgeValue(LayerNumber+1,i0,j0,static_etta); DNet->SetConstEdge(LayerNumber+1,i0,j0,static_etta); }
                for (int j0=(part_net+1)*delivery*calc_state;j0<M;j0++)
                                { DNet->SetEdgeValue(LayerNumber+1,i0,j0,0); DNet->SetConstEdge(LayerNumber+1,i0,j0,0); }
//        ShowMessage("PS:"+AnsiString(part_net)+"\ni0:"+AnsiString(i0)+"\nDel:"+AnsiString(delivery)+"\nCS:"+AnsiString(calc_state));
        }
}
}

void Delta_Net::Set_Output_Layer(void)
{
        // Set neurons
        for (int k=0;k<outputs;k++)
                DNet->SetNeuron(N-1,k,type,thetta);
        for (int k=outputs;k<M;k++)
                DNet->SetNeuron(N-1,k,0,0);
        // Set Edges
for (int i=0;i<M;i++)
        for (int j=0;j<M;j++)
                if ((i+j)%(outputs)==0)
                        { DNet->SetEdgeValue(N-1,i,j,static_etta); DNet->SetConstEdge(N-1,i,j,static_etta); }
                else
                        { DNet->SetEdgeValue(N-1,i,j,0); DNet->SetConstEdge(N-1,i,j,0); }
}

void Delta_Net::Set_CalcNN(void)
{
for (int i=3;i<3+layer_count;i++)
Set_Calc_Layer(i);
}


void Delta_Net::Learn(double* s_input,double* s_learn_output)
{
double* ns_output = new double[M];
double* ns_input = new double[M];

        // Learn Output
for (int i=0;i<outputs;i++)
        ns_output[i]=s_learn_output[i];
for (int i=outputs;i<M;i++)
        ns_output[i]=0;
        // Input
for (int j=0;j<inputs;j++)
        ns_input[j]=s_input[j];
for (int j=inputs;j<M;j++)
        ns_input[j]=0;
DNet->Learn(ns_input,ns_output);
}

void Delta_Net::Calculate(double* s_input)
{
double* ns_input = new double[M];
for (int j=0;j<inputs;j++)
        ns_input[j]=s_input[j];
for (int j=inputs;j<M;j++)
        ns_input[j]=0;DNet->GetResult(ns_input);
}

double* Delta_Net::Display(void)
{
double* n_output = new double[outputs];
double* ns_output = new double[M];
ns_output=DNet->GetResult();
for (int i=0;i<outputs;i++)
n_output[i]=ns_output[i];
return n_output;
}

void Delta_Net::Learning_SetAlpha( double new_alpha)
{
DNet->Learning_SetAlpha(new_alpha);
}
void Delta_Net::Learning_SetEtta( double new_etta)
{
DNet->Learning_SetEtta(new_etta);
}
void Delta_Net::Learning_SetEpsilon(double new_epsilon)
{
DNet->Learning_SetEpsilon(new_epsilon);
}
void Delta_Net::LearningState(bool new_state)
{
DNet->LearningState(new_state);
}

// LOAD\SAVE

void Delta_Net::LoadEdges(double* cedges, double* vedges)
{
DNet->SetConstEdges(cedges);
DNet->SetEdges(vedges);
}

double* Delta_Net::SaveCEdges(void)
{
double* tmp_a=new double[N*M*M];
tmp_a=DNet->ReturnSigma();
ShowMessage("AOE DN:"+AnsiString(tmp_a[50]));
return DNet->ReturnSigma();
}

double* Delta_Net::SaveVEdges(void)
{
double* tmp_a=new double[N*M*M];
tmp_a=DNet->ReturnEdges();
ShowMessage("AOE DN:"+AnsiString(tmp_a[50]));
return DNet->ReturnEdges();
}

int Delta_Net::ShowN(void)
{
DNet->ShowN();
}

int Delta_Net::ShowM(void)
{
DNet->ShowM();
}



//---------------------------------------------------------------------------

