
// https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all
// https://www.arduino.cc/en/Hacking/libraryTutorial

/*
  NeuralNetwork.h - Library for MLP Neural Networks.
  Created by George Chousos, April 11, 2019. *0
  Released into the public domain.

  *0: Mainly Based On https://www.youtube.com/watch?v=L_PByyJ9g-I
*/

/*
[double on some Arduino boards like UNO for example is equal to float]

  and for a safety reason, i decided to use float instead of double,
  because of PROGMEM and the fact that pgm_read_float(&of_a_double),
  works on an arduino Uno and that makes me feel insecure ... So   ,
  i think it would be better like this, at least for now, as a float 
  and not a double. In case u want to use double, just replace every
  float with double and use pgm_read_dword instead of pgm_read_float
  if your microcontroller supports double precicion.
  Thanks for reading. (:

- https://www.arduino.cc/reference/en/language/variables/data-types/double/
- https://forum.arduino.cc/index.php?topic=613873.0
*/

/*
[Error #777]
    
 NeuralNetwork(const unsigned int *layer_, const float *default_Weights, const float *default_Bias, const unsigned int &NumberOflayers , bool isProgmem)   
 
 Because someone, might want to have default or pretrained weights and biases and not in the PROGMEM but in the SRAM.

- https://stackoverflow.com/questions/56024569/arduino-compiler-takes-into-account-const-progmem-type-as-equal-to-const-type
- https://forum.arduino.cc/index.php?topic=614438.0
*/

// i would love if there could be a list of microcontrollers or a way to determine with defined(..) the size of SRAM or etc.
// Defines a list of microcontroller Attiny series As__AVR_ATtinyXXX__
#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    #define As__AVR_ATtinyX__

    #if defined(__AVR_ATtiny85__)
        #pragma message "[⚠] Last Time i tried backpropagation on an ATtiny85 I had Issues [...]"
    #endif
#endif

// Defines a list of microcontroller series (as) As__No_Common_Serial_Support (in that moment)
#if defined(As__AVR_ATtinyX__) // or etc.
#define As__No_Common_Serial_Support
#endif


// - This prevents problems if someone accidently #include's your library twice.
#ifndef NeuralNetwork_h
#define NeuralNetwork_h


// - That gives you access to the standard types and constants of the Arduino language.
#include "Arduino.h"

// - And code goes here...

#if defined(_1_OPTIMIZE)
    #if ((_1_OPTIMIZE bitor B01111111) == B11111111)
        #define USE_PROGMEM
        #define NO_BACKPROP
        #pragma message "[⚠] [Reminder] Backpropagation is not Allowed with (USE_PROGMEM)."
    #endif
    #if ((_1_OPTIMIZE bitor B10111111) == B11111111)
        #define REDUCE_RAM_DELETE_OUTPUTS
        #define NO_BACKPROP
        #pragma message "[⚠] [Reminder] Backpropagation is not Allowed with (REDUCE_RAM_DELETE_OUTPUTS)."
    #endif  
    
    #if ((_1_OPTIMIZE bitor B11101111) == B11111111)
        #define REDUCE_RAM_WEIGHTS_COMMON
        #define REDUCE_RAM_WEIGHTS_LVL2
        //#warning [⚠] Backpropagating more than once after a FeedForward [...]
    #elif ((_1_OPTIMIZE bitor B11011111) == B11111111)
        #pragma message "[⚠] 00100000 is not implemented yet."
        //#define REDUCE_RAM_WEIGHTS_COMMON
        //#define REDUCE_RAM_WEIGHTS_LVL1
    #endif

    #if ((_1_OPTIMIZE bitor B11110111) == B11111111)
       #define REDUCE_RAM_DELETE_PREVIOUS_LAYER_GAMMA
       #pragma message "[⚠] 00001000 always Enabled not switchable yet."
    #endif

    #if ((_1_OPTIMIZE bitor B11111011) == B11111111)
       #define REDUCE_RAM_STATIC_REFERENCE
       #pragma message "[⚠] 00000100 Be carefull with multiple NN objects."
    #endif

    //if i'll make most of the things static/global, i can significantly reduce rom but with the "limitation" of "one" NN per skeatch
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

 #define ACT1 0
 #define ACT2 0
 #define ACT3 0
 #define ACT4 0
 #define ACT5 0
 #define ACT6 0

 #if !defined(ACTIVATION__PER_LAYER)
    //DEFAULT
    // i will also create a mechanism to show #error if more than one is defined with B opperations?
    #define ACTIVATION //Sigmoid default but for more than one you must declare it
    #define Sigmoid Sigmoid
    #define ACTIVATION_FUNCTION Sigmoid
    // ACTIVATION__PER_LAYER will have any per neuron [2D Array/Matrix] or per layer [1d Array/Vector]
#elif defined(Sigmoid)
    #define ACT1 1
    #define ACTIVATION //Sigmoid default but for more than one you must declare it
    #define Sigmoid Sigmoid
    #define ACTIVATION_FUNCTION Sigmoid
#endif

#if defined(Tanh)
    #define ACT2 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Tanh
    #define Tanh Tanh
#endif

#if defined(ReLU) 
    #define ACT3 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION ReLU
    #define ReLU ReLU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
#endif

#if defined(LeakyELU) 
    #define ACT4 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION LeakyELU
    #define LeakyELU LeakyELU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
#endif

#if defined(ELU)
    #define ACT5 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION ELU
    #define ELU ELU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
#endif

#if defined(SELU)
    #define ACT6 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION SELU
    #define SELU SELU
#endif

#define NUM_OF_USED_ACTIVATION_FUNCTIONS (ACT1 + ACT2 + ACT3 + ACT4 + ACT5 + ACT6)
//#pragma message "The content is : " STR(NUM_OF_USED_ACTIVATION_FUNCTIONS)

#if defined(ACTIVATION__PER_LAYER)
    #if !defined(ACTIVATION)
        #define USE_ALL_ACTIVATION_FUNCTIONS
        #define NUM_OF_USED_ACTIVATION_FUNCTIONS 6
    #endif
#endif


#define MAKE_FUN_NAME1(actname,value) actname(value)
#define ACTIVATE_WITH(actname,value) MAKE_FUN_NAME1(actname,value)

#define MAKE_FUN_NAME2(actname,value) actname ## Der(value)
#define DERIVATIVE_OF(actname,value) MAKE_FUN_NAME2(actname,value)


// i might change static variables to plain variables and just pass a pointer from outer class?
class NeuralNetwork
{
private:

    

    int Individual_Input = 0;
    bool FIRST_TIME_FDFp = false; // determines if there are trashes left in last outputs .
    const float *_inputs;         // Pointer to primary/first Inputs Array from Sketch    .
                                  // (Used for backpropagation)                           .
    
    class Layer
    {
    public:
        
        #if !defined(REDUCE_RAM_STATIC_REFERENCE)
            NeuralNetwork *me;
        #endif

        unsigned int _numberOfInputs;  // # of neurons in the previous layer.
        unsigned int _numberOfOutputs; // # of neurons in the current  layer.

        float *bias;         // bias    of this     layer
        float *outputs;      // outputs of this     layer  [1D Array] pointers.
        
        //#if defined(REDUCE_RAM_WEIGHTS_LVL1)
        //    float *weights;      // weights of this     layer  [1D Array] pointers.                           #(used if     #REDUCE_RAM_WEIGHTS_LVL1   defined)         
        //#endif
        #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
            float **weights;     // weights of this     layer  [2D Array] pointers.                             #(used if NOT #REDUCE_RAM_WEIGHTS_COMMON defined) 
        #endif
        float *preLgamma;    // gamma   of previous layer  [1D Array] pointers.

        // Default Constractor                                                         .
        //      #0 Constructor                                                         .
        //      #1 Constructor With default/("probably") preptained, weights and biases.
        Layer();
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, NeuralNetwork * const NN = nullptr);                                              // #0  
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Bias, NeuralNetwork * const NN = nullptr); //                             #(used if     #REDUCE_RAM_WEIGHTS_LVL2 defined)
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias, NeuralNetwork * const NN = nullptr); // #1  #(used if NOT #REDUCE_RAM_WEIGHTS_LVL2 defined)


        void FeedForward_Individual(const float &input, const int &j);
        void FdF_Individual_PROGMEM(const float &input, const int &j);
        
        void FeedForward(const float *inputs); // Calculates the outputs() of layer.
        void FdF_PROGMEM(const float *inputs);

        void BackPropOutput(const float *_expected_, const float *inputs);
        void BackPropHidden(const Layer *frontLayer, const float *inputs);


        //if i acctually consider using other complicated activation functions i might need to think again about the before_Activation_output Array [...]
        float Sigmoid   (const float &x ); // Sigmoid Activation Function 1/(1+e^(-x)) .
        float SigmoidDer(const float &fx); // Derivative of Sigmoid Activation Function.
        
        float Tanh   (const float &x ); 
        float TanhDer(const float &fx); 

        float ReLU   (const float &x ); 
        float ReLUDer(const float &fx); // x is also fx on ReLU

        float LeakyELU   (const float &x );
        float LeakyELUDer(const float &fx); 

        float ELU   (const float &x ); // α = 1 
        float ELUDer(const float &fx); 
        
        float SELU   (const float &x );
        float SELUDer(const float &fx); 
        // Maybe use https://stackoverflow.com/a/42264773/11465149

        void print_PROGMEM();
        void print();
    };  
    //just like "static float *wights" [...]  i might have a function to switch?
    #if defined(ACTIVATION__PER_LAYER)

        typedef float (Layer::*method_function) (const float &);
        inline static const method_function (activation_Function_ptrs)[NUM_OF_USED_ACTIVATION_FUNCTIONS] = {
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(Sigmoid)
                &Layer::Sigmoid,
            #endif
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(Tanh)
                &Layer::Tanh,
            #endif
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(ReLU)
                &Layer::ReLU, 
            #endif
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(LeakyELU)
                &Layer::LeakyELU, 
            #endif
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
                &Layer::ELU, 
            #endif
            #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
                &Layer::SELU, 
            #endif            
        };
        #if !defined(NO_BACKPROP)
            inline static const method_function (derivative_Function_ptrs)[NUM_OF_USED_ACTIVATION_FUNCTIONS] = {
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(Sigmoid)
                    &Layer::SigmoidDer,
                #endif
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(Tanh)
                    &Layer::TanhDer,
                #endif
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(ReLU)
                    &Layer::ReLUDer, 
                #endif
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(LeakyELU)
                    &Layer::LeakyELUDer, 
                #endif
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
                    &Layer::ELUDer, 
                #endif
                #if defined(USE_ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
                    &Layer::SELUDer, 
                #endif                
            };
        #endif  
        //https://stackoverflow.com/a/31708674/11465149
        //http://www.cs.technion.ac.il/users/yechiel/c++-faq/array-memfnptrs.html // ??? [x]
    #endif
    

public:
    #if defined(REDUCE_RAM_STATIC_REFERENCE)
        static NeuralNetwork *me;
    #endif

    // Guessing that BackProp wont be called more than once excactly after a feedforward call, IF REDUCE_RAM_WEIGHTS_LVL2  else i should have had a temp weights-size variable or something
    // need to add a function for those who want to switch/redirect the pointer to a deferent weight Array... maybe? ... Why not?!? lol.
    // issues with multiple NNs too ...
    #if defined(REDUCE_RAM_WEIGHTS_LVL2) 
        float *weights; //                              pointer to sketch's        Array of Weights.    #(used if     #REDUCE_RAM_WEIGHTS_LVL2 defined)
        int i_j; 
    #endif   

    #if defined(ACTIVATION__PER_LAYER)
        unsigned int AtlayerIndex; // who 's gonna make a network with more than 255 layers :P ?!?!? but anyways i will use int or i will add byte too, using a property definition with bunch of other things like this for max optimization ... lol
        byte *ActFunctionPerLayer; // lets be realistic... byte because. xD
    #endif

    // no negative values allowed, (just saying..)
    // Alphas and Lamdas of Activation Functions
    float AlphaLeaky = 0.01   ;
    float AlphaSELU  = 1.6733 ; 
    float LamdaSELU  = 1.0507 ;
    float AlphaELU   = 1      ;


    Layer *layers;               // layers in the network [1D Array].
    unsigned int numberOflayers; // Number of layers.

    // unsigned float doesn't exist..? lol
    float LearningRateOfWeights = 0.33 ; // Learning Rate of Weights.
    float LearningRateOfBiases  = 0.066; // Learning Rate of Biases .
    
    float sumSquaredError = 0; // #3
    float MeanSqrdError   = 0; // #3


    ~NeuralNetwork(); // Destractor.

    NeuralNetwork();
    NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer = nullptr);                                              // #0
    NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const float &LRw, const float &LRb, byte *_ActFunctionPerLayer = nullptr);          // #0
    NeuralNetwork(const unsigned int *layer_, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer = nullptr); // #1

   // NeuralNetwork(const unsigned int *layer_, const PROGMEM float *default_Weights, const PROGMEM float *default_Bias, const unsigned int &NumberOflayers , bool isProgmem); // isProgmem (because of the Error #777) ? i get it in a way but ..
    
    void  reset_Individual_Input_Counter();
    float *FeedForward_Individual(const float &input);
    float *FeedForward(const float *inputs); // Moves Calculated outputs as inputs to next layer.
    
    float GetMeanSqrdError(unsigned int inputsPerEpoch); //#3
    void BackProp(const float *expected);    // BackPropopagation - (error, delta-weights, etc.).
    void print();
    
    
};
#if defined(REDUCE_RAM_STATIC_REFERENCE)
    NeuralNetwork *NeuralNetwork::me;
#endif
    


//=======================================================================================================================================================================
//NeuralNetwork.cpp
//=======================================================================================================================================================================
#pragma region NeuralNetwork.cpp
    NeuralNetwork::~NeuralNetwork() // i might have messed up here some things but nvm for now
    {

        for (int i = 0; i < numberOflayers; i++)
        {
            #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
                for (int j = 0; j < layers[i]._numberOfOutputs; j++) // because of this i wont make _numberOfOutputs/inputs private :/ or maybe.. i ll see... or i will change them to const* ... what? i've just read it again lol
                {
                    delete[] layers[i].weights[j];
                    layers[i].weights[j] = NULL;    
                }
            #endif

            delete layers[i].bias;
            layers[i].bias = NULL;

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                delete[] layers[i].outputs;
                layers[i].outputs = NULL;
            #endif

            /*
            #if defined(REDUCE_RAM_WEIGHTS_LVL1)
                delete[] layers[i].weights;
                layers[i].weights = NULL;
            #endif
            */
        }

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            delete weights;
            weights = NULL;
        #endif

        delete[] layers;
        layers = NULL; // 18/5/2019
    }

    NeuralNetwork::NeuralNetwork() {}

    NeuralNetwork::NeuralNetwork(const unsigned int *layer_, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer )
    {
        numberOflayers = NumberOflayers - 1;

        layers = new Layer[numberOflayers]; // there has to be a faster way by alocating memory for example...

        #if defined(ACTIVATION__PER_LAYER)
            ActFunctionPerLayer = _ActFunctionPerLayer;
        #endif  
        
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            weights = default_Weights;
        #else
            unsigned int weightsFromPoint = 0;
        #endif

        for (int i = 0; i < numberOflayers; i++)
        {
            #if defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                layers[i] = Layer(layer_[i], layer_[i + 1], &default_Bias[i],this);
            #else
                layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], &default_Bias[i],this);
                weightsFromPoint += layer_[i] * layer_[i + 1];
            #endif
            
        }
    }

    NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const float &LRw, const float &LRb,  byte *_ActFunctionPerLayer )
    {
        LearningRateOfWeights = LRw; // Initializing the Learning Rate of Weights
        LearningRateOfBiases = LRb;  // Initializing the Learning Rate of Biases

        numberOflayers = NumberOflayers - 1;

        layers = new Layer[numberOflayers];

        #if defined(ACTIVATION__PER_LAYER)
            ActFunctionPerLayer = _ActFunctionPerLayer;
        #endif 

        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif

        #if defined(REDUCE_RAM_WEIGHTS_LVL2) //footprint episis san leksi
            for (int i = 0; i < numberOflayers; i++)
                i_j += layer_[i] * layer_[i + 1];
            
            weights = new float[i_j];
            i_j=0;
        #endif

        for (int i = 0; i < numberOflayers; i++)
        {
            layers[i] =  Layer(layer_[i], layer_[i + 1],this);
        }

    }

    //maybe i will  add one more constructor so i can release memory from feedforward outputs in case i dont want backprop?

    NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers,  byte *_ActFunctionPerLayer )
    {

        numberOflayers = NumberOflayers - 1;

        layers = new Layer[numberOflayers];

        #if defined(ACTIVATION__PER_LAYER)
            ActFunctionPerLayer = _ActFunctionPerLayer;
        #endif 

        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif

        #if defined(REDUCE_RAM_WEIGHTS_LVL2) //footprint episis san leksi
            for (int i = 0; i < numberOflayers; i++)
                i_j += layer_[i] * layer_[i + 1];
            
            weights = new float[i_j];
            i_j=0;
        #endif

        for (int i = 0; i < numberOflayers; i++)
        {
            layers[i] =  Layer(layer_[i], layer_[i + 1],this);
        }

    }

    void NeuralNetwork::reset_Individual_Input_Counter()
    {
        Individual_Input = 0;
    }

    float *NeuralNetwork::FeedForward_Individual(const float &input)
    {
        #if defined(USE_PROGMEM)
            layers[0].FdF_Individual_PROGMEM(input, Individual_Input);
        #else
            layers[0].FeedForward_Individual(input, Individual_Input);
        #endif
        Individual_Input++;

        if (Individual_Input == layers[0]._numberOfInputs)
        {
            Individual_Input=0;
        
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                if (FIRST_TIME_FDFp == true) // is it the first time ? if not, then delete trashes
                {
                    delete[] layers[numberOflayers - 1].outputs;
                    layers[numberOflayers - 1].outputs = NULL;
                }else{
                    FIRST_TIME_FDFp = true;
                }
            #endif

            for (int i = 1; i < numberOflayers; i++)
            {
                #if defined(ACTIVATION__PER_LAYER)
                    AtlayerIndex = i;
                #endif  
                #if defined(USE_PROGMEM)
                    layers[i].FdF_PROGMEM(layers[i - 1].outputs);
                #else
                    layers[i].FeedForward(layers[i - 1].outputs);
                #endif
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    delete[] layers[i - 1].outputs;
                    layers[i - 1].outputs = NULL;
                #endif
            }

            return layers[numberOflayers - 1].outputs;
        }

        return nullptr;
    }

    float *NeuralNetwork::FeedForward(const float *inputs)
    {
        _inputs = inputs;
        
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            if (FIRST_TIME_FDFp == true) // is it the first time ? if not, then delete trashes
            {
                delete[] layers[numberOflayers - 1].outputs;
                layers[numberOflayers - 1].outputs = NULL;
            }else{
                FIRST_TIME_FDFp = true;
            }
        #endif

        // Reseting the index to which layer we are back to 0, the 1st layer
        #if defined(ACTIVATION__PER_LAYER)
            AtlayerIndex = 0;
        #endif  
        // resets starting point (could have had a function returning it insted of initializing it on constructor too?)
        #if defined(REDUCE_RAM_WEIGHTS_LVL2) 
            i_j=0;
        #endif
        
        #if defined(USE_PROGMEM)
            layers[0].FdF_PROGMEM(_inputs);
        #else
            layers[0].FeedForward(_inputs);
        #endif

        for (int i = 1; i < numberOflayers; i++)
        {
            #if defined(ACTIVATION__PER_LAYER)
                AtlayerIndex = i;
            #endif  
            #if defined(USE_PROGMEM)
                layers[i].FdF_PROGMEM(layers[i - 1].outputs);
            #else
                layers[i].FeedForward(layers[i - 1].outputs);
            #endif
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                delete[] layers[i - 1].outputs;
                layers[i - 1].outputs = NULL;
            #endif
        }

        return layers[numberOflayers - 1].outputs;
    }



    void NeuralNetwork::BackProp(const float *expected)
    {
        /* i dont find any reason of having this if Backprop will never be used more than once imidiatly after once [...] but just in case ... commented .... The same goes for i_j too
        #if defined(ACTIVATION__PER_LAYER)
            AtlayerIndex = numberOflayers - 1;
        #endif  
        */

        layers[numberOflayers - 1].BackPropOutput(expected, layers[numberOflayers - 2].outputs); // issue because backprop einai anapoda ta weights [Fixed]

        for (int i = numberOflayers - 2; i > 0; i--)
        {
            layers[i].BackPropHidden(&layers[i + 1], layers[i - 1].outputs);
            delete[] layers[i + 1].preLgamma;
            layers[i + 1].preLgamma = NULL; // 18/5/2019
        }

        layers[0].BackPropHidden(&layers[1], _inputs);

        delete[] layers[1].preLgamma;
        delete[] layers[0].preLgamma;

        layers[0].preLgamma = NULL;
        layers[1].preLgamma = NULL;
    }

     //#3
     
    float NeuralNetwork::GetMeanSqrdError(unsigned int inputsPerEpoch)
    {
        MeanSqrdError = (sumSquaredError/ (layers[numberOflayers - 1]._numberOfOutputs * inputsPerEpoch));
        sumSquaredError = 0;
        return MeanSqrdError;
    }
    

    //If Microcontroller isn't one of the .._No_Common_Serial_Support Series then it compiles the code below.
    #if !defined(As__No_Common_Serial_Support) // then Compile:
    void NeuralNetwork::print()
    {
        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            i_j=0; 
        #endif

        Serial.println();
        Serial.println("----------------------");

        for (int i = 0; i < numberOflayers; i++)
        {
            #if defined(USE_PROGMEM)
                layers[i].print_PROGMEM();
            #else
                layers[i].print();
            #endif
        }
    }
    #endif
#pragma endregion NeuralNetwork.cpp



//=======================================================================================================================================================================
// Layer.cpp
//=======================================================================================================================================================================

#pragma region Layer.cpp

    NeuralNetwork::Layer::Layer() {}


    #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias, NeuralNetwork * const NN )
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new float[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif
            
            bias = default_Bias; //                          ##1    Bias as Default Bias.
            weights = new float *[_numberOfOutputs]; //      ##1    New Array of Pointers to (float) weights.

            for (int i = 0; i < _numberOfOutputs; i++)              // [matrix] (_numberOfOutputs * _numberOfInputs)
                weights[i] = &default_Weights[i * _numberOfInputs]; // Passing Default weights to ##1 weights by reference.
            
        }

    #else
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Bias, NeuralNetwork * const NN )
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new float[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif
            
            bias = default_Bias; //                          ##1    Bias as Default Bias.
        }

    #endif

    //- [ numberOfInputs in into this layer , NumberOfOutputs of this layer ]
    NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, NeuralNetwork * const NN )
    {

        _numberOfInputs = NumberOfInputs;                             // ##1       Number of Inputs .
        _numberOfOutputs = NumberOfOutputs;                           // ##1       Number of Outputs.

        #if !defined(REDUCE_RAM_STATIC_REFERENCE)
            me = NN;
        #endif

        outputs = new float[_numberOfOutputs];                        // ##1    New Array of Outputs.
        #if !defined(REDUCE_RAM_WEIGHTS_COMMON)      
            weights = new float *[_numberOfOutputs];                  // ##1    New Array of Pointers to (float) weights.
        #endif
        bias = new float;                                             // ##1    New          Bias   .
        *bias = 1.0;

        float _random;

        for (int i = 0; i < _numberOfOutputs; i++)
        {
            #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
                weights[i] = new float[_numberOfInputs];
            #endif
            
            for (int j = 0; j < _numberOfInputs; j++)
            {
                _random = (random(-90000, 90000)); // Pseudo-Random Number between -90000 and 90000
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    me->weights[me->i_j] = _random / 100000;
                    me->i_j++;
                #else
                    weights[i][j] = _random / 100000;  // Divided by 100000 = a Number between -0.90000 and 0.90000
                #endif
            }
        }

    }

    void NeuralNetwork::Layer::FdF_Individual_PROGMEM(const float &input, const int &j)
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
            if (j == 0) // if it is the first input then create output array (for the output layer of this current layer)
                outputs = new float[_numberOfOutputs]; // ? speed ? or {} or memset .. it matters
        #endif
        //outputs[i] = 0; kai o midenismos se for

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            me->i_j = 0; // 1/2 only places that represents ony the i
        #endif

        //feed forwards
        int i;
        
        for (i = 0; i < _numberOfOutputs; i++)
        {
            if (j == 0)
                outputs[i] = 0; // ? speed ? safe one..

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                outputs[i] += input * pgm_read_float(&me->weights[me->i_j+j]);
            #else
                outputs[i] += input * pgm_read_float(&weights[i][j]); // if double pgm_read_dword 
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                me->i_j += _numberOfInputs;
            #endif
        }

        // when all individual inputs get summed and multiplied by their weights in their outputs, then pass them from the activation function
        if (j == _numberOfInputs -1)
            for (i = 0; i < _numberOfOutputs; i++)
            {
                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[0]])(outputs[i] + pgm_read_float(bias));  // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i] + pgm_read_float(bias)); // if double pgm_read_dword
                #endif
            }

    }

    void NeuralNetwork::Layer::FeedForward_Individual(const float &input, const int &j)
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
            if (j == 0) // if it is the first input then create output array (for the output layer of this current layer)
                outputs = new float[_numberOfOutputs];
        #endif
        //outputs[i] = 0; kai o midenismos se for

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            me->i_j = 0; // 1/2 only places that represents ony the i
        #endif

        //feed forwards
        int i;
        for (i = 0; i < _numberOfOutputs; i++)
        {
            if (j == 0)
                outputs[i] = 0;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                outputs[i] += input * me->weights[me->i_j+j];
            #else
                outputs[i] += input * weights[i][j]; // if double pgm_read_dword 
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                me->i_j += _numberOfInputs;
            #endif
        }

        // when all individual inputs get summed and multiplied by their weights in their outputs, then pass them from the activation function
        if (j == _numberOfInputs -1)
            for (i = 0; i < _numberOfOutputs; i++){
                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[0]])(outputs[i] + (*bias)); // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i] + (*bias)); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output) + (bias of current layer))
                #endif
            }

    }

    void NeuralNetwork::Layer::FdF_PROGMEM(const float *inputs) //*
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            outputs = new float[_numberOfOutputs];
        #endif
        
        //feed forwards
        for (int i = 0; i < _numberOfOutputs; i++)
        {
            outputs[i] = 0; // #2
            for (int j = 0; j < _numberOfInputs; j++) 
            {
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    outputs[i] += inputs[j] * pgm_read_float(&me->weights[me->i_j]);
                    me->i_j++;
                #else
                    outputs[i] += inputs[j] * pgm_read_float(&weights[i][j]); // if double pgm_read_dword 
                #endif
            }
            #if defined(ACTIVATION__PER_LAYER)
                outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i] + pgm_read_float(bias));
            #else
                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i] + pgm_read_float(bias)); // if double pgm_read_dword
            #endif

        }

    }

    void NeuralNetwork::Layer::FeedForward(const float *inputs) //*
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            outputs = new float[_numberOfOutputs];
        #endif
    
        //feed forwards
        for (int i = 0; i < _numberOfOutputs; i++)
        {
            outputs[i] = 0;
            for (int j = 0; j < _numberOfInputs; j++)
            {
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    outputs[i] += inputs[j] * me->weights[me->i_j];
                    me->i_j++;
                #else
                    outputs[i] += inputs[j] * weights[i][j]; // (neuron[i]'s 1D array/vector of inputs) * (neuron[i]'s 2D array/matrix weights) = neuron[i]'s output
                #endif
                
            }
            #if defined(ACTIVATION__PER_LAYER)
                outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i] + (*bias));
            #else
                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i] + (*bias)); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output) + (bias of current layer))
            #endif
        }

        // return outputs;
    } 
    /*
    αρα θα βγαλω τη sigmoid απο _numberOfOutputs loop ==> Sigmoid(ACTIVATION_FUNCTION, outputs[i] + (*bias))
    και θα τη βαλω στο _numberOfInputs loop ==> inputs[j] (για εξοικονομηση RAM, διαφορετικα BeforeActivationOutputs 1D Array [πριν το activation δλδ] με Property)
    ωστε να μπορω οταν θα κανω backprop να παρω τις παραγωγους και αλλων συναρτισεων ενεργοποιησης 
    που απετουν το Input πριν το activation.... αααχ issues τελικα it was too good to be true..

    https://stackoverflow.com/questions/1253934/c-pre-processor-defining-for-generated-function-names
    */


    float NeuralNetwork::Layer::Sigmoid  (const float &x) { return 1 / (1 + exp(-x))                          ;}
    float NeuralNetwork::Layer::Tanh     (const float &x) { return (exp(2*x) - 1) / (exp(2*x) + 1)            ;}
    float NeuralNetwork::Layer::ReLU     (const float &x) { return (x > 0) ? x : 0                            ;}
    float NeuralNetwork::Layer::LeakyELU (const float &x) { return (x > 0) ? x : me->AlphaLeaky * x           ;}
    float NeuralNetwork::Layer::ELU      (const float &x) { return (x > 0) ? x : me->AlphaELU  * (exp(x) - 1) ;}
    float NeuralNetwork::Layer::SELU     (const float &x) { return (x > 0) ? x : me->AlphaSELU * (exp(x) - 1) ;}

    #if !defined(NO_BACKPROP)

        float NeuralNetwork::Layer::SigmoidDer  (const float &fx) { return fx - fx * fx                                                  ;} 
        float NeuralNetwork::Layer::TanhDer     (const float &fx) { return 1 - fx * fx                                                   ;}
        float NeuralNetwork::Layer::ReLUDer     (const float &fx) { return (fx > 0) ? 1 : 0                                              ;} 
        float NeuralNetwork::Layer::LeakyELUDer (const float &fx) { return (fx > 0) ? 1 : me->AlphaLeaky                                 ;} 
        float NeuralNetwork::Layer::ELUDer      (const float &fx) { return (fx > 0) ? 1 : fx + me->AlphaELU                              ;} 
        float NeuralNetwork::Layer::SELUDer     (const float &fx) { return (fx > 0) ? me->LamdaSELU : fx + me->AlphaSELU * me->LamdaSELU ;} 


        void NeuralNetwork::Layer::BackPropOutput(const float *_expected_, const float *inputs)
        {

            preLgamma = new float[_numberOfInputs]{}; // create gamma of previous layer and initialize{} values to 0 .. meh
            

            float bias_Delta = 1.0;
            float gamma;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                for (int i = _numberOfOutputs -1; i >= 0; i--) // i want to believe that it is being optimized, lol
                {
                    //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                    gamma = (outputs[i] - _expected_[i]);
                    me->sumSquaredError += gamma * gamma;
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = gamma * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = gamma * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]);
                    #endif
                    bias_Delta *= gamma;

                    for (int j = _numberOfInputs -1; j >= 0; j--)
                    {
                        me->i_j--;
                        preLgamma[j] += gamma * me->weights[me->i_j];
                        me->weights[me->i_j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;   
                    }
                }

            #else
                for (int i = 0; i < _numberOfOutputs; i++)
                {
                    //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                    //gamma = (outputs[i] - _expected_[i]) * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // outputs[i] is f(x) not x in this case, because i wanted to delete the array of inputs before activation

                     //#3
                    gamma = (outputs[i] - _expected_[i]); 
                    me->sumSquaredError += gamma * gamma; // I want to believe that it is being optimised/removed when not used
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = gamma * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = gamma * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]);
                    #endif
                    bias_Delta *= gamma;

                    for (int j = 0; j < _numberOfInputs; j++)
                    {
                        preLgamma[j] += gamma * weights[i][j];
                        weights[i][j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }
                }
            #endif
            
            *bias -= bias_Delta * me->LearningRateOfBiases;
        }

        void NeuralNetwork::Layer::BackPropHidden(const Layer *frontLayer, const float *inputs)
        {
            #if defined(ACTIVATION__PER_LAYER)
                me->AtlayerIndex -= 1; 
            #endif
            preLgamma = new float[_numberOfInputs]{};

            float bias_Delta = 1.0;
            float gamma;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                for (int i = _numberOfOutputs -1; i >= 0; i--)
                {
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = frontLayer->preLgamma[i] * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = frontLayer->preLgamma[i] * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // if i remember well , frontLayer->preLgamma[i] means current layer gamma?
                    #endif
                    bias_Delta *= gamma;

                    for (int j = _numberOfInputs -1; j >= 0; j--)
                    {
                        me->i_j--;
                        preLgamma[j] += gamma * me->weights[me->i_j];
                        me->weights[me->i_j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }

                }

            #else
                for (int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = frontLayer->preLgamma[i] * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = frontLayer->preLgamma[i] * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // if i remember well , frontLayer->preLgamma[i] means current layer gamma?
                    #endif
                    bias_Delta *= gamma;

                    for (int j = 0; j < _numberOfInputs; j++)
                    {
                        preLgamma[j] += gamma * weights[i][j];
                        weights[i][j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }

                }
            #endif

            *bias -= bias_Delta * me->LearningRateOfBiases;
            
        }



    #endif


    //If Microcontroller isn't one of the Attiny Series then it compiles the code below.
    #if !defined(As__No_Common_Serial_Support) // then Compile:
    void NeuralNetwork::Layer::print()
    { 


        Serial.print(_numberOfInputs);
        Serial.print(" ");
        Serial.print(_numberOfOutputs);
        Serial.print("| bias:");
        Serial.print(*bias);
        Serial.println();

        for (int i = 0; i < _numberOfOutputs; i++)
        {
            Serial.print(i + 1);
            Serial.print(" ");
            for (int j = 0; j < _numberOfInputs; j++)
            {
                Serial.print(" W:");
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    if (me->weights[me->i_j] > 0) Serial.print(" "); // dont even bothered to opt. here lol
                    Serial.print(me->weights[me->i_j], 7);
                    me->i_j++;
                #else
                    if (weights[i][j] > 0) Serial.print(" ");
                    Serial.print(weights[i][j], 7);
                #endif
                Serial.print(" ");
            }
            Serial.println("");
        }
        Serial.println("----------------------");

    }

    void NeuralNetwork::Layer::print_PROGMEM()
    {

        Serial.print(_numberOfInputs);
        Serial.print(" ");
        Serial.print(_numberOfOutputs);
        Serial.print("| bias:");
        Serial.print(pgm_read_float(bias));
        Serial.println();

        for (int i = 0; i < _numberOfOutputs; i++)
        {
            Serial.print(i + 1);
            Serial.print(" ");
            for (int j = 0; j < _numberOfInputs; j++)
            {
                //weights[i][j] = (float)j;
                Serial.print(" W:");
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    if (pgm_read_float(&me->weights[me->i_j]) > 0) Serial.print(" "); // if gratter than 10 too or something would be nice
                    Serial.print(pgm_read_float(&me->weights[me->i_j]), 6);
                    me->i_j++;
                #else
                    if (pgm_read_float(&weights[i][j]) > 0 ) Serial.print(" ");
                    Serial.print(pgm_read_float(&weights[i][j]), 6);
                #endif
                Serial.print(" ");
            }
            Serial.println("");
        }
        Serial.println("----------------------");
    }

    #endif

#pragma endregion Layer.cpp

#endif


/*

#2 https://stackoverflow.com/questions/22318677/is-it-faster-to-have-the-compiler-initialize-an-array-or-to-manually-iterate-over  [I am slightly confused. Anyways...]
#4 https://stackoverflow.com/questions/65860934/undefined-reference-to-outterclassfunction-ptrs-variable-issue


*/
