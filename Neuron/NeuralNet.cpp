
#include <alloc.h>
#include "NeuralNet.h"
#include "Neuron.h"
#include "NAFunctions.h"
#include <Math.h>
#include <vcl.h>

NeuralNet::NeuralNet()
{
        N=0;
        M=0;
        K=0;
}

NeuralNet::NeuralNet(int s_N, int s_M, int s_type,   double s_thetta)
{
        learning=false;
        N=s_N;
        M=s_M;
        K=s_M;
        Neuro =(Neuron*) malloc((s_N*s_M)*sizeof(Neuron));
        int k=0;
        for (int j=0;j<s_M;j++)
        Neuron N_temp(0,j,2,1);

        for (int i=1;i<s_N;i++)
        for (int j=0;j<s_M;j++)
        {
        //Neuron N_temp(i,j,s_type,s_thetta/(s_M*i));
        Neuron N_temp(i,j,s_type,s_thetta);
        Neuro[k]=N_temp;
        k++;
        }
        ArrayOfEdges = new   double[N*M*M];
        sigma = new   double[N*M*M];
        for (int i=0;i<N*M*M;i++)
        sigma[i]=-1;
        NeuroLearnOutput = new   double[M];
        NeuroOutput = new   double[M];
        NeuroInput = new   double[M];
}

NeuralNet::~NeuralNet()
{
        delete Neuro;
        delete ArrayOfEdges;
//        delete NeuroLearnOutput;
//        delete NeuroOutput;
//        delete NeuroInput;
// it's fail, buddy

}


void NeuralNet::SetConstEdges(double* stat_sigma)
{
sigma=stat_sigma;
for (int i=1;i<N*M*M;i++)
if (stat_sigma[i]==1 || stat_sigma[i]==0)
ArrayOfEdges[i]=stat_sigma[i];
}

void NeuralNet::SetConstEdge(int i, int j, int k, double new_sigma)
{
sigma[ReturnEdgeRealNumber(i,j,k)]=new_sigma;
}

void NeuralNet::SetConstEdges()
{
for (int i=1;i<N*M*M;i++)
if (sigma[i]==1 || sigma[i]==0)
ArrayOfEdges[i]=sigma[i];
}

void NeuralNet::SetCascadeNeuron(int new_type, double new_thetta)
{
double n_thetta=new_thetta;
if (new_type>4 && new_type<8)
        {
        for (int i=0;i<N;i++)
                {
                if(i>0)
                //n_thetta=new_thetta*exp(-i*(0.25));
                n_thetta=new_thetta/(i/exp(1));
                for (int j=0;j<M;j++)
                {
                        Neuro[ReturnNeuronRealNumber(i,j)].ChangeType(new_type);
                        Neuro[ReturnNeuronRealNumber(i,j)].ChangeThetta(n_thetta);
                }
                }
        }
}

void NeuralNet::SetNeuronAdd(int i, int j,  double s_additional)
{
        Neuro[ReturnNeuronRealNumber(i,j)].SetAdditional(s_additional);
}

void NeuralNet::SetNeuronAdd(int NeuronNumber,  double s_additional)
{
        Neuro[NeuronNumber].SetAdditional(s_additional);
}

int NeuralNet::ReturnNeuronRealNumber(int x,int y)
{
        int result=M*x+y;
        return result;
}

void NeuralNet::SetNeuronValue(int i, int j,  double s_input)
{
        Neuro[ReturnNeuronRealNumber(i,j)]=s_input;
}
void NeuralNet::SetNeuronValue(int NeuronNumber,  double s_input)
{
        Neuro[NeuronNumber]=s_input;
}

void NeuralNet::SetNeuron(int i, int j, int new_type,  double new_thetta)
{
        Neuro[ReturnNeuronRealNumber(i,j)].ChangeThetta(new_thetta);
        Neuro[ReturnNeuronRealNumber(i,j)].ChangeType(new_type);
}

void NeuralNet::SetNeuron(int NeuronNumber, int new_type,  double new_thetta)
{
        Neuro[NeuronNumber].ChangeThetta(new_thetta);
        Neuro[NeuronNumber].ChangeType(new_type);
}

 double NeuralNet::operator()(int NeuronNumber)
{
        return Neuro[NeuronNumber].Display();
}

void NeuralNet::CalcNeuron(int i, int j)
{
        !Neuro[ReturnNeuronRealNumber(i,j)];
}

void NeuralNet::CalcNeuron(int NeuronNumber)
{
        !Neuro[NeuronNumber];
}

void NeuralNet::SetAggregateInput(int i, int j)
{
         double result=0;
        if (i>0)
        {
        for (int n=0;n<K;n++)
        {
                result+=(Neuro[ReturnNeuronRealNumber(i-1,n)].Display())*(ArrayOfEdges[ReturnEdgeRealNumber(i,j,n)]);
        }
        SetNeuronValue(i,j,result);
        }
}

int NeuralNet::ReturnEdgeRealNumber(int x,int y,int z)
{
        int result = (x*M+y)*K+z;
        return result;
}

void NeuralNet::CalcLayer(int LayerNumber)
{
        for (int i=0;i<M;i++)
                SetAggregateInput(LayerNumber, i);
        CInput(LayerNumber);
        for (int j=0;j<M;j++)
                CalcNeuron(LayerNumber, j);

}

void NeuralNet::operator!(void)
{
        //ShowMessage("I'm here at !");
        for (int i=0;i<N;i++)
                CalcLayer(i);
        for (int j=0;j<M;j++)
                NeuroOutput[j]=Neuro[ReturnNeuronRealNumber(N-1,j)].Display();
}

void NeuralNet::Calculate(void)
{
        //ShowMessage("I'm here at calc");
        for (int i=0;i<N;i++)
                CalcLayer(i);
        for (int j=0;j<M;j++)
                NeuroOutput[j]=Neuro[ReturnNeuronRealNumber(N-1,j)].Display();
}

 double* NeuralNet::GetResult(void)
{
        return NeuroOutput;
}

 double* NeuralNet::GetResult( double* new_input)
{
        NeuroInput=new_input;
        for (int i=0;i<M;i++)
                Neuro[ReturnNeuronRealNumber(0,i)]=NeuroInput[i];
        Calculate();
        return NeuroOutput;
}

void NeuralNet::SetEdges( double weight)
{
        for (int i=0;i<N*M*K;i++)
                ArrayOfEdges[i]=weight;
}

void NeuralNet::SetEdges( double* new_sigma)
{
        for (int i=0;i<N*M*K;i++)
                ArrayOfEdges[i]=new_sigma[i];
}

void NeuralNet::SetAllThetta( double new_thetta)
{
        for (int i=0;i<N*M;i++)
                Neuro[i].ChangeThetta(new_thetta);
}

void NeuralNet::SetThetta( double new_thetta)
{
        for (int i=0;i<N*M;i++)
                if (Neuro[i].ShowType()>1)
                        Neuro[i].ChangeThetta(new_thetta);
}


void NeuralNet::SetEdgeValue(int i, int j, int k,  double weight)
{
        ArrayOfEdges[ReturnEdgeRealNumber(i,j,k)]=weight;
}

void NeuralNet::SetEdgeValue(int EdgeNumber,  double weight)
{
        ArrayOfEdges[EdgeNumber]=weight;
}

  double NeuralNet::ShowNeuronInput(int NeuronNumber)
 {
        return Neuro[NeuronNumber].ShowInput();
 }

  double NeuralNet::ShowNeuronThetta(int NeuronNumber)
 {
        return Neuro[NeuronNumber].ShowThetta();
 }

  double NeuralNet::ShowNeuronAdditional(int NeuronNumber)
 {
        return Neuro[NeuronNumber].ShowAdditional();
 }

  double NeuralNet::ShowEdge(int EdgeNumber)
 {
        return ArrayOfEdges[EdgeNumber];
 }

 int NeuralNet::ShowNeuronType(int NeuronNumber)
 {
        return Neuro[NeuronNumber].ShowType();
 }

// -------- LEARNING FUNCTIONS ---------

// Count func

int NeuralNet::CountRealNeuronsInLayer(int LayerNumber)
{
        int RNofNeurons=0;
        for (int i=0;i<M;i++)
                if (Neuro[ReturnNeuronRealNumber(LayerNumber,i)].ShowType()>1) RNofNeurons++;
        return RNofNeurons;
}

int NeuralNet::CountRealNeuronsInNet(void)
{
        int RNofNeurons=0;
        for (int j=0;j<N;j++)
                for (int i=0;i<M;i++)
                        if (Neuro[ReturnNeuronRealNumber(j,i)].ShowType()>1) RNofNeurons++;
        return RNofNeurons;
}

int NeuralNet::CountHiddenNeuronsInLayer(int LayerNumber)
{
        int HofNeurons=0;
        for (int i=0;i<M;i++)
        if (Neuro[ReturnNeuronRealNumber(LayerNumber,i)].ShowType()==1) HofNeurons++;
        return HofNeurons;
}

int NeuralNet::CountHiddenNeuronsInNet(void)
{
        int HofNeurons=0;
        for (int j=0;j<N;j++)
                for (int i=0;i<M;i++)
                        if (Neuro[ReturnNeuronRealNumber(j,i)].ShowType()==1) HofNeurons++;
        return HofNeurons;
}
int NeuralNet::CountZeroNeuronsInLayer(int LayerNumber)
{
        int ZofNeurons=0;
        for (int i=0;i<M;i++)
                if (Neuro[ReturnNeuronRealNumber(LayerNumber,i)].ShowType()==0) ZofNeurons++;
        return ZofNeurons;
}

int NeuralNet::CountZeroNeuronsInNet(void)
{
        int ZofNeurons=0;
        for (int j=0;j<N;j++)
                for (int i=0;i<M;i++)
                        if (Neuro[ReturnNeuronRealNumber(j,i)].ShowType()==0) ZofNeurons++;
        return ZofNeurons;
}

int NeuralNet::CountNotZeroNeuronsInLayer(int LayerNumber)
{
        int NZofNeurons=0;
        for (int i=0;i<M;i++)
                if (Neuro[ReturnNeuronRealNumber(LayerNumber,i)].ShowType()>0) NZofNeurons++;
        return NZofNeurons;
}

int NeuralNet::CountNotZeroNeuronsInNet(void)
{
        int NZofNeurons=0;
        for (int j=0;j<N;j++)
                for (int i=0;i<M;i++)
                        if (Neuro[ReturnNeuronRealNumber(j,i)].ShowType()>0) NZofNeurons++;
        return NZofNeurons;
}

// view func

bool NeuralNet::IsLearning()
{
        return learning;
}

 double NeuralNet::ShowNeuronError(int i, int j)
{
        return Neuro[ReturnNeuronRealNumber(i,j)].ShowError();
}

 double NeuralNet::ShowNeuronError(int NeuronNumber)
{
        return Neuro[NeuronNumber].ShowError();
}

// set

void NeuralNet::SetError(int i, int j,  double new_error)
{
        Neuro[ReturnNeuronRealNumber(i,j)].SetError(new_error);
}

void NeuralNet::SetError(int NeuronNumber,   double new_error)
{
        Neuro[NeuronNumber].SetError(new_error);
}

// calc

void NeuralNet::CalcTailNeuronError(int i, int j)
{
         if (Neuro[ReturnNeuronRealNumber(i,j)].ShowType()!=0)
         {
         double result=Neuro[ReturnNeuronRealNumber(i,j)].Display();
         double var_error=(NeuroLearnOutput[j]-result)*result*(1-result);
        SetError(i,j,var_error);
        }
}

void NeuralNet::CalcTailError(void)
{
        for (int i=0;i<M;i++)
                if (Neuro[ReturnNeuronRealNumber(N-1,i)].ShowType()>1)
                        CalcTailNeuronError(N-1,i);
}

void NeuralNet::CalcNeuronError(int i, int j)
{
         if (Neuro[ReturnNeuronRealNumber(i,j)].ShowType()!=0)
         {
         double result=Neuro[ReturnNeuronRealNumber(i,j)].Display();
         double aggregate_error=0;
        for (int n=0;n<M;n++)
                aggregate_error+=ArrayOfEdges[ReturnEdgeRealNumber(i+1,n,j)]*Neuro[ReturnNeuronRealNumber(i+1,n)].ShowError();
         double var_error=result*(1-result)*aggregate_error;
        SetError(i,j,var_error);
        }
}

void NeuralNet::CalcLayerError(int LayerNumber)
{
        for (int i=0;i<M;i++)
                if (Neuro[ReturnNeuronRealNumber(LayerNumber,i)].ShowType()>1)
                        CalcNeuronError(LayerNumber,i);
}

void NeuralNet::CalcAllErrors(void)
{
        CalcTailError();
                for (int i=N-2;i>0;i--)
                        CalcLayerError(i);
}

// ñhange sigma-matrix

void NeuralNet::ChangeEdgeWeight(int i, int j, int k)
{
/* Hey? It's true? */
        ArrayOfEdges[ReturnEdgeRealNumber(i,j,k)]=etta*Neuro[ReturnNeuronRealNumber(i,j)].Display()*Neuro[ReturnNeuronRealNumber(i,j)].ShowError()+alpha*ArrayOfEdges[ReturnEdgeRealNumber(i,j,k)];
}

void NeuralNet::ChangeAllEdgeWeight(void)
{
        for (int i=0;i<N;i++)
                for (int j=0;j<M;j++)
                        for (int k=0;k<K;k++)
                                ChangeEdgeWeight(i,j,k);
}

// learning settings

void NeuralNet::LearningState(bool new_state)
{
        learning=new_state;
}

 double* NeuralNet::DeltaEpsilon(void)
{
         double* EpsilonArray = new  double[M];
        for (int i=0;i<M;i++)
                EpsilonArray[i]=abs(NeuroLearnOutput[i]-Neuro[N-1,i].Display());
        return EpsilonArray;
}

bool NeuralNet::Learning_IsCorrect(void)
{
         double* EpsilonArray = new  double[M];
//       double temp_number;
        for (int i=0;i<M;i++)
                {
if(abs(NeuroLearnOutput[i]-Neuro[N-1,i].Display())>epsilon);
                {
//                ShowMessage(AnsiString(double(EpsilonArray[i]))+" "+AnsiString(double(Neuro[N-1,i].Display()))+" "+AnsiString(double(NeuroLearnOutput[i])));
//                }
//        for (int i=0;i<M;i++)
//                if (EpsilonArray[i]>epsilon)
//                        {
                        delete EpsilonArray; return false; }}
        delete EpsilonArray;
        return true;
}

void NeuralNet::Learning_SetAlpha( double new_alpha)
{
        alpha=new_alpha;
}

void NeuralNet::Learning_SetEtta( double new_etta)
{
        etta=new_etta;
}

void NeuralNet::Learning_SetEpsilon( double new_epsilon)
{
        epsilon=new_epsilon;
}

// learn!

bool NeuralNet::Learn( double* new_input,  double * new_output)
{
        NeuroLearnOutput=new_output;
        NeuroInput=new_input;
        for (int i=0;i<M;i++)
        Neuro[ReturnNeuronRealNumber(0,i)]=NeuroInput[i];
        Calculate();
        CalcAllErrors();
        ChangeAllEdgeWeight();
        SetConstEdges(sigma);
        return Learning_IsCorrect();
}

bool NeuralNet::Learn( double* new_output)
{
        NeuroLearnOutput=new_output;
        Calculate();
        CalcAllErrors();
        ChangeAllEdgeWeight();
        SetConstEdges(sigma);
        return Learning_IsCorrect();
}

void NeuralNet::CInput(int P)
{
double* new_input = new double[M];
//double* new_input2 = new double[M];
double betta=5.0;

double max,min;

max=Neuro[ReturnNeuronRealNumber(P,0)].ShowInput();
min=Neuro[ReturnNeuronRealNumber(P,0)].ShowInput();

for (int i=0;i<M;i++)
{ if (max<Neuro[ReturnNeuronRealNumber(P,i)].ShowInput()) max=Neuro[ReturnNeuronRealNumber(P,i)].ShowInput();
  if (min>Neuro[ReturnNeuronRealNumber(P,i)].ShowInput()) min=Neuro[ReturnNeuronRealNumber(P,i)].ShowInput(); }
for (int j=0;j<M;j++)
new_input[j]=Neuro[ReturnNeuronRealNumber(P,j)].ShowInput()-min;
for (int k=0;k<M;k++)
{
        if ((max-min)!=0)
        new_input[k]=new_input[k]*(2*betta/(max-min))-betta;
        else new_input[k]=0;
}
for (int m=0;m<M;m++)
Neuro[ReturnNeuronRealNumber(P,m)]=new_input[m];
}

// SAVE

double* NeuralNet::ReturnSigma(void)
{
ShowMessage("sigma NN:"+AnsiString(sigma[670]));
return sigma;
}

double* NeuralNet::ReturnEdges(void)
{
ShowMessage("AOE NN:"+AnsiString(ArrayOfEdges[670]));
return ArrayOfEdges;
}

int NeuralNet::ShowN(void)
{
return N;
}

int NeuralNet::ShowM(void)
{
return M;
}



//---------------------------------------------------------------------------



