//---------------------------------------------------------------------------

#ifndef NeuralNetH
#define NeuralNetH

#include "Neuron.h"

class NeuralNet {
        private:

/*  NEURAL NET  */

int N;                          // layers
int M;                          // range
int K;                          // edge
Neuron* Neuro;                  // array of Neurons
 double* ArrayOfEdges;      // array of edges
int type;                       // type
 double* NeuroInput;        // array of input
 double* NeuroOutput;        // array of input

/*  LEARNING VARIABLES  */

 bool learning;                  // state
 double epsilon;            // data accuracy
 double alpha;              // inertial member
 double etta;               // learning measure
 double* NeuroLearnOutput;  // static output
 double* sigma;             // static edges


NeuralNet();                    // constructor

        public:
NeuralNet(int s_N,int s_M,int s_type, double s_thetta); // classified constructor
~NeuralNet();                                               // destructor

/* CONVERTERS */

int ReturnEdgeRealNumber(int x,int y,int z); // convert from x-y-z coordinates
int ReturnNeuronRealNumber(int x,int y); // convert from x-y coordinates

/* CALCULATIONS */
void SetAggregateInput(int i, int j); // set of w*x input
void CalcLayer(int LayerNumber); // calculate N-layer
void CalcNeuron(int i, int j); // calculate neuron
void CalcNeuron(int NeuronNumber); // calculate neuron
void Calculate(void);   // calculate! (NET
void operator!(void); // calculate! (NET)

/* SETTINGS */
void SetNeuronValue(int i, int j,  double s_input); // set input of Neuron
void SetNeuronValue(int NeuronNumber,  double s_input); // set input of Neuron
void SetNeuron(int i, int j, int new_type,  double new_thetta); // set neuron param
void SetNeuron(int NeuronNumber, int new_type,  double new_thetta); // set neuron param
void SetCascadeNeuron(int new_type, double new_thetta); // set cascade neuron
void SetAllThetta( double thetta); // set thetta in NET
void SetThetta( double thetta); // set thetta on non-static\null neurons
void SetNeuronAdd(int NeuronNumber,  double s_additional); // set additional
void SetNeuronAdd(int i, int j,  double s_additional); // set additional
void SetEdgeValue(int i, int j, int k,  double weight); // set edge value
void SetEdgeValue(int EdgeNumber,  double weight); // set edge value
void SetEdges( double weight); // set edges basic value
void SetEdges( double* new_sigma); // set edges value
void SetConstEdges(double* stat_sigma); // set const singma
void SetConstEdges(); // set const singma
void SetConstEdge(int i, int j, int k, double new_sigma); // set const singma

/* VIEW */
  double operator()(int NeuronNumber); // get single neuron result
  double* GetResult(void);             // get array of output
  double* GetResult( double* new_input);     // calculate with data
  double ShowNeuronInput(int NeuronNumber); // displays single neuron input
  double ShowNeuronThetta(int NeuronNumber); // displays single neuron thetta
  double ShowNeuronAdditional(int NeuronNumber); // displays single neuron additional
  int ShowNeuronType(int NeuronNumber); // displays neuron type
  double ShowEdge(int EdgeNumber); // displays edge weigth
  bool IsLearning();                     // is neural net learning?

/*  Back propagation algorithm */

 double ShowNeuronError(int i, int j); // show error of neuron
 double ShowNeuronError(int NeuronNumber); // show error of neuron

 double* DeltaEpsilon(void);
bool Learning_IsCorrect(void);
void Learning_SetAlpha( double new_alpha);
void Learning_SetEtta( double new_etta);
void Learning_SetEpsilon( double new_epsilon);
void LearningState(bool new_state);

int CountRealNeuronsInLayer(int LayerNumber); // returns number of not-hidden neurons in layer
int CountRealNeuronsInNet(void); // returns number of not-hidden neurons in net
int CountHiddenNeuronsInLayer(int LayerNumber); // returns number of hidden neurons in net
int CountHiddenNeuronsInNet(void); // returns number of hidden neurons in net
int CountZeroNeuronsInLayer(int LayerNumber); // returns number of zero neurons in net
int CountZeroNeuronsInNet(void); // returns number of zero neurons in net
int CountNotZeroNeuronsInLayer(int LayerNumber); // returns number of none-zero neurons in net
int CountNotZeroNeuronsInNet(void); // returns number of none-zero neurons in net

void CInput(int j); // convert to static input

void SetError(int i, int j,  double new_error); // set error of neuron
void SetError(int NeuronNumber,   double new_error); // set error of neuron

void CalcTailNeuronError(int i, int j); // calculates error on output neuron
void CalcTailError(void); // calculates error on output
void CalcNeuronError(int i, int j); // calculates error on Neuron
void CalcLayerError(int LayerNumber); // calculates error of layer
void CalcAllErrors(void); // calculates all errors

void ChangeEdgeWeight(int i, int j, int k); // changes weight of Wij
void ChangeAllEdgeWeight(void); // changes all weights in net

bool Learn( double* new_input,  double* new_output); // calculate&learn
bool Learn( double* new_output); // calculate&learn

/* SAVE */

double* ReturnEdges(void);
double* ReturnSigma(void);
int ShowN(void);
int ShowM(void);


};
//---------------------------------------------------------------------------
#endif
