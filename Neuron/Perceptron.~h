//---------------------------------------------------------------------------

#ifndef PerceptronH
#define PerceptronH
#include "NeuralNet.h"

        class Perceptron {
private:
        NeuralNet* NN;  // standart NN
        int Inputs;             // number of inputs
        int Outputs;            // number of outputs
        double* input;          // input
        double* output;         // output
        double* learn_output;   // learn_output
        int N;                  // total layers
        int M;                  // total neuron in layer
        int type;               // activation function
        double thetta;          // thetta
        int* NullEdges;         // static null edges
        Perceptron();           // default constructor
        void RefillEdges(void); // set null edges
        void SetLayerFunction(int LayerNumber, int new_type); // set layer function

                // ADD
        void C_INPUT(int new_DID, int new_DLD);
        void C2_INPUT(int new_DID, int new_DLD);
        void C_OUTPUT(int new_DID, int new_DLD);
public:
        Perceptron(int inputs, int outputs, int new_DID, int new_NDID, int new_DLD, int type, double new_thetta); // mono-layer perceptron constructor
        void ReInitialize(void); // Reset all edges

        // VIEW
        double operator()(int NeuronNumber); // get single neuron result
        double ShowNeuronInput(int NeuronNumber); // displays single neuron input
        double ShowNeuronThetta(int NeuronNumber); // displays single neuron thetta
        double ShowNeuronAdditional(int NeuronNumber); // displays single neuron additional
        int ShowNeuronType(int NeuronNumber); // displays neuron type
        double ShowEdge(int EdgeNumber); // displays edge weigth

        // LEARNING
        bool Learning_IsCorrect(void);
        void Learning_SetAlpha( double new_alpha);
        void Learning_SetEtta( double new_etta);
        void Learning_SetEpsilon( double new_epsilon);
        void LearningState(bool new_state);
        bool Learn( double* new_input,  double* new_output); // calculate&learn
        bool Learn( double* new_output); // calculate&learn

        // CALC
        double* GetResult(void);             // get array of output
        double* GetResult( double* new_input);     // calculate with data

};


//---------------------------------------------------------------------------
#endif
