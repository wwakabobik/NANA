//---------------------------------------------------------------------------

#ifndef delta_netH
#define delta_netH
#include "NeuralNet.h"
//---------------------------------------------------------------------------

class Delta_Net {
private:
        int inputs;             // number of inputs
        int outputs;            // number of outputs
        int compress_state;     // compress dimension inputs/dimension=2layer
        int calc_state;         // calculate neurons (real M)=2layer*calc_state
        int layer_count;        // number of calc count
        int layer_regress;      // state of regress rate
        int M;
        int N;
        double static_etta;
        double thetta;          // thetta
        int type;               // type
        bool linear;            // input compress
        int delivery;           // this is calc input

        // CONSTRUCTOR
        Delta_Net();                            // default constructor
        void Set_Input_Layer(void);             // set param of input layer
        void Set_Compress_Layer(void);          // set param of compress layer
        void Set_Calc_Layer(int LayerNumber);   // set param of calc layer (num)
        void Set_CalcNN(void);                  // set calc neural net
        void Set_Output_Layer(void);            // set output layer
public:
        NeuralNet* DNet;        // neural_net
        Delta_Net(int new_inputs, int new_outputs, bool new_linear, int new_compress_state, int new_delivery, int new_calc_state, int new_layer_count, int new_layer_regress, double new_static_etta, double new_thetta, int new_type);
        ~Delta_Net();           // default destructor
        void Learn(double* s_input,double* s_learn_output);
        void Calculate(double* s_input);
        double* Display(void);

        // LEARNING
        void Learning_SetAlpha( double new_alpha);
        void Learning_SetEtta( double new_etta);
        void Learning_SetEpsilon( double new_epsilon);
        void LearningState(bool new_state);

        // LOAD\SAVE
        void LoadEdges(double* cedges, double* vedges);
        double* SaveCEdges(void);
        double* SaveVEdges(void);
        int ShowN(void);
        int ShowM(void);
};
#endif
