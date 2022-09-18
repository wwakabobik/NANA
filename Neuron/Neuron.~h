
#ifndef NeuronH
#define NeuronH
#include "NAFunctions.h"

class Neuron {
private:
        /* Neuron variables */
        int N;                                  // layer
        int M;                                  // number
         double result;                     // last result
         double input;                      // last input
         double GatherF(void);              // Agregate Function
         double Activate(void);             // activate neuron
         double thetta;                     // thetta internal value
         double additional;                 // hide layer (fuzzy) emulation
        int type;                               // typeof function
        /* Learning variables */
         double lasterror;
        Neuron();                               // default constructor
public:
        Neuron(int i, int j, int s_type,  double s_thetta);       // classified constructor
        ~Neuron();                                      // destructor
         double operator!(void);                    // calculate!
        void operator=( double data);               // set input
        Neuron operator=(Neuron &src);                  // set input
        void ChangeType(int new_type);                  // change calc function
        void ChangeThetta( double new_thetta);      // change thetta;
        void SetAdditional( double s_additional);   // set additional
         double Display(void);                      // display result
         double ShowInput(void);                    // display input
         double ShowThetta(void);                   // display thetta
         double ShowAdditional(void);               // display additional
        int ShowType(void);                             // display type
         double ShowError(void);                    // display error
        void SetError( double new_error);            // set error
};

//---------------------------------------------------------------------------
#endif
