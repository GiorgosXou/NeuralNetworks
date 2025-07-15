#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _1_OPTIMIZE 0B01010010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define USE_LSTM__NB           // Makes LSTM the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork. 
#define LSTM_ACT Sigmoid       // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on.
#include <NeuralNetwork.h>


const unsigned int layers[] = {1, 6, 1}; // 1 input-neuron/feature > 6 hidden-neurons > 1 output
float *output; // 3rd layer's output(s)

// Input data, gathered from our pseudo-temperature-sensor | 3 temperature-points for each timestep
float input[3]; 

// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  // LSTM Layer 0 -> 1

  // forget gate
   1.0005640e+00, 1.0000000e+00, 1.0009421e+00, 1.0000000e+00, 1.0000000e+00, 1.0000000e+00,
  // input/update gate
   2.6461852e-01, 4.1273775e-06, 0.0000000e+00, 1.5077704e-01, 0.0000000e+00, 1.6193975e-05, 
  // cell state
   0.0000000e+00,-2.1291467e-12, 1.9136046e-01, 1.5075621e-01,-1.0493273e-01,-3.2228940e-07, 
  // output gate
   3.7514053e-02, 0.0000000e+00, 0.0000000e+00, 0.0000000e+00,-2.1309011e-01, 0.0000000e+00,

  // LSTM Layer 1 -> 2

  // forget gate
   1.1662949 ,
  // input/update gate
   0.14027178,
  // cell state
   0.17858411,
  // output gate
  -0.06330408
};

// [Pretrained weights] //  NOTE: ORDER CHANGES BASED ON: _1_OPTIMIZE 0B0001 !!
float weights[] = {
  // LSTM LAYER 0 -> 1

  // Interleaved gates per row
  /*forget      */  0.40602452f,
  /*forget      */  0.53320462f,  0.09876864f,  0.23104222f, -0.27553272f, -0.05549302f,  0.02055343f,
  /*input/update*/ -0.55732214f,
  /*input/update*/ -0.08723317f,  0.13439897f,  0.29725462f,  0.00222707f, -0.50323039f,  0.16791597f,
  /*cell state  */ -1.89399695f,
  /*cell state  */ -0.18853290f,  0.01446671f, -0.22261819f, -0.07121444f,  0.26616684f, -0.28798938f,
  /*output      */  0.38137770f,
  /*output      */ -0.00289428f, -0.30740348f,  0.27059665f,  0.26322401f,  0.29916510f,  0.19350685f,
  /*forget      */  0.49116489f,
  /*forget      */ -0.05811211f, -0.12102585f, -0.02828634f, -0.23783672f, -0.06744099f,  0.01464431f,
  /*input/update*/ -1.20202208f,
  /*input/update*/ -0.23675047f,  0.18664469f, -0.10481453f,  0.04584696f,  0.06057939f,  0.08155300f,
  /*cell state  */ -0.70225108f,
  /*cell state  */ -0.14144464f,  0.41245258f, -0.04522229f, -0.07499889f, -0.03899441f, -0.40139183f,
  /*output      */  1.63929808f,
  /*output      */ -0.05157050f,  0.19543171f,  0.00214885f, -0.05228107f, -0.05185254f,  0.23357248f,
  /*forget      */ -0.84864545f,
  /*forget      */  0.13233167f,  0.07849675f, -0.29214400f,  0.13163356f,  0.25924894f,  0.14189914f,
  /*input/update*/  1.53077149f,
  /*input/update*/  0.33688763f,  0.04156153f,  0.13740146f,  0.04792240f,  0.42817014f, -0.30913496f,
  /*cell state  */  0.64802331f,
  /*cell state  */ -0.46692628f, -0.31204486f,  0.61743683f,  0.47593847f, -0.48823240f, -0.38313484f,
  /*output      */  1.97462213f,
  /*output      */  0.08355921f, -0.07277633f, -0.20185670f, -0.05923201f, -0.38782489f, -0.06065622f,
  /*forget      */ -1.98829794f,
  /*forget      */ -0.22866368f, -0.05625797f, -0.07811587f, -0.14586532f,  0.21605399f, -0.05777653f,
  /*input/update*/ -0.01137813f,
  /*input/update*/ -0.09696338f,  0.08719451f, -0.07657244f, -0.05922301f,  0.03942738f, -0.09981491f,
  /*cell state  */  1.18741620f,
  /*cell state  */ -0.26233926f,  0.23949769f,  0.52209061f,  0.12427679f,  0.12011904f,  0.16497529f,
  /*output      */  1.51536334f,
  /*output      */  0.10402673f,  0.33111405f,  0.01598506f,  0.35688692f, -0.06611998f,  0.06747419f,
  /*forget      */  1.35827482f,
  /*forget      */  0.04210760f, -0.04560905f, -0.07495481f,  0.04048335f, -0.03357042f,  0.01903087f,
  /*input/update*/  1.84771264f,
  /*input/update*/ -0.14497064f,  0.38956881f, -0.03813103f,  0.15693441f, -0.08313482f,  0.17130798f,
  /*cell state  */ -0.32731199f,
  /*cell state  */ -0.18640849f, -0.08145908f, -0.43220502f,  0.23383947f, -0.06267200f,  0.21137117f,
  /*output      */  1.41429985f,
  /*output      */  0.10252248f, -0.15109207f, -0.55060846f, -0.26855201f,  0.31316608f, -0.25611225f,
  /*forget      */  2.11748910f,
  /*forget      */ -0.22739749f, -0.23216945f,  0.05206724f, -0.34240514f, -0.00683814f,  0.20005216f,
  /*input/update*/ -1.07413161f,
  /*input/update*/  0.25944307f, -0.16822861f, -0.30672848f, -0.01085271f, -0.10693069f, -0.07391746f,
  /*cell state  */ -0.19206713f,
  /*cell state  */ -0.18054433f,  0.22913840f,  0.02256774f, -0.18946812f, -0.18600573f, -0.24026936f,
  /*output      */  1.68252611f,
  /*output      */  0.17969765f,  0.11551546f, -0.06713309f,  0.32499579f, -0.02790840f, -0.27207723f,

  // LSTM LAYER 1 -> 2

  // Interleaved gates per row
  /*forget      */ -0.27918896f,  0.03407475f,  0.19329531f,  0.11894168f, -0.12955438f,  0.07626471f,
  /*forget      */ -0.00719230f,
  /*input/update*/ -0.29635695f, -0.01399989f,  0.05436753f,  0.10567266f, -0.16897857f, -0.00583024f,
  /*input/update*/  0.45316818f,
  /*cell state  */ -0.27048895f, -0.05229580f,  0.24894045f,  0.07455997f, -0.27619952f,  0.01098746f,
  /*cell state  */ -0.66966546f,
  /*output      */ -0.22296827f,  0.06725086f,  0.02361265f, -0.20074037f,  0.11946618f,  0.00571866f,
  /*output      */  0.40414405f,
};

// Creating NeuralNetwork with pretrained Weights and Biases;
NeuralNetwork NN(layers, weights, biases, NumberOf(layers));


void setupTempSensor() {
  initTempSensor();                   // Initialization of fake/pseudo-temperature-sensor 
  for (int i = 0; i < 3; i++) {
    input[i] = getTemp(); delay(250); // gets the 3 initial (timestep-0) temperatures + wait for each next one
  }
}


void setup(){
  Serial.begin(9600); // Initialization/begining of Serial at 9600 baud-rate
  setupTempSensor();  // Initialization + population of timestep-0 with temperatures
  NN.print();         // Prints the weights & biases of each layer
}


void loop(){
  for (unsigned int i = 0; i < 3; i++)    // Each timestep consist of 3 temperature-samples
      output = NN.FeedForward(&input[i]); // FeedForward each temperature-value & return the (next)-predicted (output)

  // Slide/shift/"memmove()" array temperature-values/samples to the left by one.
  input[0] = input[1];
  input[1] = input[2];

  // Gets the next/new temperature.
  input[2] = getTemp(); delay(250);

  // Prints the Predicted (next)-temperature (7 digits after the comma).
  Serial.print("Predicted:");
  Serial.println(*output, 7);

  // Prints the next-new temperature that was predicted.
  Serial.print("Temperature:");
  Serial.println(input[2], 7);       
}

