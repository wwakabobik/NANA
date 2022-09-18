//---------------------------------------------------------------------------

#include "Neuron.h"
#include "NAFunctions.h"


//---------------------------------------------------------------------------

        void Neuron::SetAdditional( double s_additional)
        {
        additional = s_additional;
        }

        Neuron::Neuron()
        {
        result=0;
        input=0;
        additional=0;
        lasterror=0;
        }

        Neuron::Neuron(int i, int j, int s_type,  double s_thetta)
        {
        N=i;
        M=j;
        type=s_type;
        thetta=s_thetta;
        result=0;
        input=0;
        additional=0;
        lasterror=0;
        }

        Neuron::~Neuron()
        {
        N=0;
        M=0;
        type=0;
        result=0;
        input=0;
        }

         double Neuron::operator!(void)
        {
        result=0;
        if (N<1)
        GatherF();
        result=Activate();
        return result;
        }

        void Neuron::operator=( double data)
        {
        input=data;
        }

        Neuron Neuron::operator=(Neuron &src)
        {
        N=src.N;
        M=src.M;
        thetta=src.thetta;
        type=src.type;
        additional=src.additional;
        input=src.input;
        result=src.result;
        }

        void Neuron::ChangeType(int new_type)
        {
        type=new_type;
        }

        void Neuron::ChangeThetta( double new_thetta)
        {
        thetta=new_thetta;
        }

         double Neuron::Display()
        {
        return result;
        }

         double Neuron::Activate()
        {
        switch (type)
        {
        case 0:
        return FAZero();
        case 1:
        return FAStatic(thetta+additional);
        break;
        case 2:
        return FAEqual(input+additional, thetta);
        break;
        case 3:
        return FABarierS(input+additional, thetta);
        break;
        case 4:
        return FABarierH(input+additional, thetta);
        break;
        case 5:
        return FASigma(input+additional, thetta);
        break;
        case 6:
        return FATanh(input+additional, thetta);
        break;
        case 8:
        return FAAbs(input+additional);
        break;
        case 7:
        return FAExp(input+additional, thetta);
        break;
        }
        return 0.0;
        }

         double Neuron::GatherF()
        {
        return input;
        }


        // additional

         double Neuron::ShowInput(void)
        {
        return input;
        }
         double Neuron::ShowThetta(void)
        {
        return thetta;
        }
         double Neuron::ShowAdditional(void)
        {
        return additional;
        }
        int Neuron::ShowType(void)
        {
        return type;
        }

         double Neuron::ShowError(void)
        {
        return lasterror;
        }
        void Neuron::SetError( double new_error)
        {
        lasterror=new_error;
        }



