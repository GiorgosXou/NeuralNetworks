// https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all
// https://www.arduino.cc/en/Hacking/libraryTutorial
// *0: Based On https://www.youtube.com/watch?v=L_PByyJ9g-I

/*
  NeuralNetwork.h - Library for MLP Neural Networks.
  Created by George Chousos, April 11, 2019. *0
  Released into the public domain.
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
    
 NeuralNetwork(const unsigned int *_layer, const float *default_Weights, const float *default_Bias, const unsigned int &NumberOflayers , bool isProgmem)   
 
 Because someone, might want to have default or pretrained weights and biases and not in the PROGMEM but in the SRAM.

- https://stackoverflow.com/questions/56024569/arduino-compiler-takes-into-account-const-progmem-type-as-equal-to-const-type
- https://forum.arduino.cc/index.php?topic=614438.0
*/

// i would love if there could be a list of microcontrollers or a way to determine with defined(..) the size of SRAM or etc.
// Defines a list of microcontroller Attiny series As__AVR_ATtinyXXX__
#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define As__AVR_ATtinyX__
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
//#include <math.h>

// - And code goes here...
class NeuralNetwork
{
private:
    bool FIRST_TIME_FDFp = false; // determines if there are trashes left in last outputs .
    unsigned int _numberOflayers; // # of layers                                          .
    const float *_inputs;         // Pointer to primary/first Inputs Array from Sketch    .
                                  // (Used for backpropagation)                           .
    class Layer
    {

    public:
        unsigned int _numberOfInputs;  // # of neurons in the previous layer.
        unsigned int _numberOfOutputs; // # of neurons in the current  layer.

        float *bias;      // bias    of this     layer
        float *outputs;   // outputs of this     layer  [1D Array] pointers.
        float **weights;  // weights of this     layer  [2D Array] pointers.
        float *preLgamma; // gamma   of previous layer  [1D Array] pointers.

        // Default Constractor                                                         .
        //      #0 Constructor                                                         .
        //      #1 Constructor With default/("probably") preptained, weights and biases.
        Layer();
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs);                                              // #0
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias); // #1
        Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias, const bool NO_OUTPUTS); // #1

        void FeedForward(const float *inputs); // Calculates the outputs() of layer.
        void FdF_PROGMEM(const float *inputs); 

        void BackPropOutput(const float *_expected_, const float *inputs, const NeuralNetwork *NN);
        void BackPropHidden(const Layer *frontLayer, const float *inputs, const NeuralNetwork *NN);

        float Sigmoid(const float &x); // Sigmoid Activation Function 1/(1+e^(-x)) .
        float SigmDer(const float &x); // Derivative of Sigmoid Activation Function.

        void print_PROGMEM();
        void print();
        
    };

public:
    Layer *layers; // layers in the network [1D Array].

    //unsigned float doesn't exist..?
    float LearningRateOfWeights = 0.33; // Learning Rate of Weights.
    float LearningRateOfBiases = 0.066; // Learning Rate of Biases .

    ~NeuralNetwork(); // Destractor.

    NeuralNetwork(const unsigned int *_layer, const unsigned int &NumberOflayers);                                              // #0
    NeuralNetwork(const unsigned int *_layer, const unsigned int &NumberOflayers, const float &LRw, const float &LRb);          // #0
    NeuralNetwork(const unsigned int *_layer, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers); // #1
    NeuralNetwork(const unsigned int *_layer, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers, bool NO_OUTPUTS);
   // NeuralNetwork(const unsigned int *_layer, const PROGMEM float *default_Weights, const PROGMEM float *default_Bias, const unsigned int &NumberOflayers , bool isProgmem); // isProgmem (because of the Error #777) ? i get it in a way but ..

    float *FeedForward(const float *inputs); // Moves Calculated outputs as inputs to next layer.
    float *FeedForward(const float *inputs, const bool IS__PROGMEM);

    void BackProp(const float *expected);    // BackPropopagation - (error, delta-weights, etc.).
    void print(bool IS__PROGMEM = false);
};

#endif

