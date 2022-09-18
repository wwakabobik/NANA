//---------------------------------------------------------------------------

#include <Stdlib.h>
#include "Perceptron.h"
#include "NeuralNet.h"
#include <vcl.h>


bool is_contains(int c_array[],int n,int c_number)
{
for (int i=0;i<n;i++)
if(c_array[i]==c_number)
return true;
return false;
}

Perceptron::Perceptron()
{
        Inputs=0;
        Outputs=0;
        input=0;
        output=0;
        N=0;
        M=0;
        type=0;
        NullEdges=0;
        thetta=0;
}

void Perceptron::C_INPUT(int new_DID, int new_DLD)
{
// INPUT LAYER

for (int i=0;i<Inputs;i++) // real inputs
{
        NN->SetNeuron(0,i,2,1);
        for (int j=0;j<M;j++)
        {
                if (j<i+new_DID && j>i) // child
                {
                        NN->SetEdgeValue(0,i,j,1);
                        NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]=1;
                }
                else                    // not-child
                {
                        NN->SetEdgeValue(0,i,j,0);
                        NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]=0;
                }
        }
}

for (int i=Inputs;i<M;i++) // zero inputs
{
        NN->SetNeuron(0,i,0,0);
                for (int j=0;j<M;j++)
                        {
                                NN->SetEdgeValue(0,i,j,0);
                                NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]=0;
                        }
}
}

void Perceptron::C2_INPUT(int new_DID, int new_DLD)
{
// REAL INPUT

int* SettedEdges = new int[M];
int border=M/new_DLD;
for (int k=0;k<M;k++)
SettedEdges[k]=-1;
int norm=0;
//ShowMessage("3");
for (int i=0;i<Inputs*new_DID;i++)
{
if (norm>=M)
{
for (int k=0;k<M;k++)
        SettedEdges[k]=-1;
norm=0;
}

        NN->SetNeuron(1,i,2,1);
        randomize();
        //ShowMessage("i(M): "+AnsiString(i)+" /"+AnsiString(Inputs*new_DID));
        int j=0;
        if (norm<M)  // set relation edges
        {
                for (j=0;j<border;j++)
                {
                        //ShowMessage("j "+AnsiString(j)+"/ "+AnsiString(border)+"\n n "+AnsiString(norm) + "/" + AnsiString(M));

                        int relation=-1; bool state=true;
                        for(;;)
                        {
                                relation=random(M);
                                state=is_contains(SettedEdges,M,relation);
                                if (!state)
                                break;
                        }
                        SettedEdges[norm]=relation;
                        NN->SetEdgeValue(0,i,j,1);
                        NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]=1;
                        norm++;
                        if (norm>M)
                        break;
                }
        }
        else  // set zero edges
        {
                for (j;j<M;j++)
                {
                                if (NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]!=1)
                                {
                                        NN->SetEdgeValue(0,i,j,0);
                                        NullEdges[NN->ReturnEdgeRealNumber(0,i,j)]=0;
                                }
                }
        }
}

for (int i=Inputs*new_DID;i<M;i++) // zero inputs
{
        NN->SetNeuron(0,i,0,0);
                for (int j=0;j<M;j++)
                        {
                               NN->SetEdgeValue(1,i,j,0);
                               NullEdges[NN->ReturnEdgeRealNumber(1,i,j)]=0;
                        }
}
}

void Perceptron::C_OUTPUT(int new_DID, int new_DLD)
{
// OUTPUT

// here can be a fuzzy logic, but in fact only a zero outputs

for (int i=0;i<Outputs;i++) // set outputs
        {
        NN->SetNeuron(N-1,i,type,thetta);
        for (int j=0;j<Outputs;j++)
                {
                        NN->SetEdgeValue(N-1,i-1,j,thetta);
                        NullEdges[NN->ReturnEdgeRealNumber(N-1,i-1,j)]=thetta;
                }
        }
        for (int i=Outputs;i<M;i++) // set zero output
        {
                NN->SetNeuron(N-1,i,0,0);
                for (int j=Outputs;j<M;j++)
                {
                NN->SetEdgeValue(N-1,i-1,j,0);
                NullEdges[NN->ReturnEdgeRealNumber(N-1,i-1,j)]=0;
                }
        }
}


Perceptron::Perceptron(int inputs, int outputs, int new_DID, int new_DLD, int new_NDLD, int new_type, double new_thetta)
{
 // with 0!

Inputs=inputs;
Outputs=outputs;
input=new double[Inputs];
output=new double[Outputs];
type=new_type;
thetta=new_thetta;
N=3+new_NDLD;
M=inputs*new_DID*new_DLD;

NN = new NeuralNet(N,M,type,thetta);
NN->SetEdges(0.3); // it must be not-null!
NullEdges = new int[N*M*M];
for (int i=0;i<N*M*M;i++)
NullEdges[i]=-1;

//ShowMessage("1");
C_INPUT(new_DID,new_DLD);
//ShowMessage("2");
C2_INPUT(new_DID,new_DLD);
//ShowMessage("5");
C_OUTPUT(new_DID,new_DLD);


}


void Perceptron::RefillEdges(void)
{
for (int i=0;i<N*M*M;i++)
if (NullEdges[i]==0 || NullEdges[i]==1)
NN->SetEdgeValue(i,NullEdges[i]);
}

void Perceptron::SetLayerFunction(int LayerNumber, int new_type)
{
for (int i=0;i<M;i++)
NN->SetNeuron(LayerNumber,i,new_type,thetta);
}

void Perceptron::ReInitialize(void)
{
for (int i=0;i<N*M*M;i++)
NN->SetEdgeValue(i,NullEdges[i]);
}

//CALC

double* Perceptron::GetResult(void)
{
        double* n_o = new double[M];
        n_o=NN->GetResult();                 // Output of Perceptron
        for (int i=0;i<Outputs;i++)       // input to NN
                output[i]=n_o[i];
        return output;
}

double* Perceptron::GetResult( double* new_input)
{
        input=new_input;
        double* n_i = new double[M];
        double* n_o = new double[M];

        for (int i=0;i<Inputs;i++)               // input to NN
                n_i[i]=input[i];
        for (int i=Inputs;i<M;i++)
                n_i[i]=0;
        n_o=NN->GetResult(n_i);                 // Output of Perceptron
                for (int i=0;i<Outputs;i++)
                output[i]=n_o[i];
        return output;
}


// VIEW

double Perceptron::operator()(int NeuronNumber)
{
        return NN->operator ()(NeuronNumber);
}


double Perceptron::ShowNeuronInput(int NeuronNumber)
{
        return NN->ShowNeuronInput(NeuronNumber);
}

double Perceptron::ShowNeuronThetta(int NeuronNumber)
{
        return NN->ShowNeuronThetta(NeuronNumber);
}

double Perceptron::ShowNeuronAdditional(int NeuronNumber)
{
        return NN->ShowNeuronAdditional(NeuronNumber);
}

int Perceptron::ShowNeuronType(int NeuronNumber)
{
        return NN->ShowNeuronType(NeuronNumber);
}

double Perceptron::ShowEdge(int EdgeNumber)
{
        return NN->ShowEdge(EdgeNumber);
}

// LEARNING

bool Perceptron::Learning_IsCorrect(void)
{
        return NN->Learning_IsCorrect();
}

void Perceptron::Learning_SetAlpha( double new_alpha)
{
        NN->Learning_SetAlpha(new_alpha);
}

void Perceptron::Learning_SetEtta( double new_etta)
{
        NN->Learning_SetEtta(new_etta);
}

void Perceptron::Learning_SetEpsilon( double new_epsilon)
{
        NN->Learning_SetEpsilon(new_epsilon);
}

void Perceptron::LearningState(bool new_state)
{
        NN->LearningState(new_state);
}

bool Perceptron::Learn( double* new_input,  double* new_output)
{
        input=new_input;
        learn_output=new_output;
        bool learniscorrect=false;
        double* n_i = new double[M];
        double* n_o = new double[M];
        double* n_o_l = new double[M];

        for (int i=0;i<Outputs;i++)               // learn output to NN
                n_o_l[i]=learn_output[i];
        for (int i=Outputs;i<M;i++)
                n_o_l[i]=0;

        for (int i=0;i<Inputs;i++)               // input to NN
                n_i[i]=input[i];
        for (int i=Inputs;i<M;i++)
                n_i[i]=0;

        learniscorrect=NN->Learn(n_i,n_o_l);   // Learn

        n_o=NN->GetResult();                   // Output of Perceptron
        for (int i=0;i<Outputs;i++)
                output[i]=n_o[i];

        return learniscorrect;
}

bool Perceptron::Learn( double* new_output)
{
        learn_output=new_output;

        bool learniscorrect=false;
        double* n_o = new double[M];
        double* n_o_l = new double[M];

        for (int i=0;i<Outputs;i++)               // learn output to NN
                n_o_l[i]=learn_output[i];
        for (int i=Outputs;i<M;i++)
                n_o_l[i]=0;

        learniscorrect=NN->Learn(n_o_l);   // Learn

        n_o=NN->GetResult();                   // Output of Perceptron
        for (int i=0;i<Outputs;i++)
                output[i]=n_o[i];

        RefillEdges();

        return learniscorrect;
}








//---------------------------------------------------------------------------

