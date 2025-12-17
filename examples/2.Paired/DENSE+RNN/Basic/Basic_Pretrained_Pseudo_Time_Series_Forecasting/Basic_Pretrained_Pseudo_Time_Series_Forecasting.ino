#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
//#define DISABLE_SINGLE_TIMESTEP_THRESHOLD // You may completely disable the single-threshold-logic to reduce sketch-size (if unnecessary)
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B00100000 // Enables MULTIPLE_BIASES_PER_LAYER
#define USE_DENSE_RNN_PAIR__NB // Defines both RNN & DENSE architectures for your NeuralNetwork. (NB = NO_BACKPROP support)
#define THRESHOLD 3            // Timestep threshold for ...
#define AT_HIDDEN 1            // ... 2nd hidden-layer (index 1), before it outputs
#define SELU                   // Defines core activation-function of your NeuralNetwork.
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on. (OVER-trained, for the sake of Visualization in plotter)
#include <NeuralNetwork.h>


// First Layer is always an input/feature-layer, therefore we don't have to specify any architecture for it
LayerType architectures[] = {
  RNN(),
  RNN(),
  DENSE(),
};
const unsigned int layers[] = {1, 5, 3, 1}; // 1 input/feature layer -> 5 & 3 RNN hidden-neurons -> 1 DENSE output
float *output; // 4th layer's output(s)

// Input data, gathered from our pseudo-temperature-sensor | 3 temperature-points for each timestep
float input[3];

// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  0.032366186,  0.009003694, -0.015172903  , 0.0, -0.006930798, // RNN   Layer 0 -> 1
  0.013656618, -0.013992845, -0.00013149012, // RNN   Layer 1 -> 2
  0.06328548 // DENSE Layer 2 -> 3
};

// [Pretrained weights]
float weights[] = {
  // RNN Layer 0 -> 1
   1.30399001f,
   0.14601776f,  0.25613067f, -0.55393171f, -0.69367051f, -0.06464627f,
   1.18315744f,
   0.36774260f,  0.03865614f,  0.24619871f,  0.21447489f,  0.59151757f,
  -0.02828937f,
   0.07648949f,  0.32602647f, -0.54867667f,  0.75738585f, -0.20915025f,
  -2.07335281f,
  -0.72064269f, -0.04980764f, -0.32614806f,  0.05776641f,  0.60702848f,
  -0.11433228f,
  -0.43350682f,  0.67583454f,  0.49443546f,  0.04716558f, -0.19171867f,

  // RNN Layer 1 -> 2
   0.69408470f,  0.71752638f, -0.06637309f,  1.00600314f, -0.56027120f,
  -0.11874792f, -0.77567267f, -0.20694412f,
  -0.28963336f, -0.02655280f, -0.04302825f, -0.30166563f,  0.98483843f,
   0.67279196f,  0.11816070f, -0.47508934f,
   0.47242293f, -0.96838081f,  0.10515124f, -0.66345203f, -0.62638056f,
   0.48355943f, -0.21138959f,  0.84680498f,

  // DENSE Layer 2 -> 3
  0.43826136,   0.14729896,   -0.43494859,

};

// Creating NeuralNetwork with pretrained Weights and Biases;
NeuralNetwork NN(layers, weights, biases, NumberOf(layers) OPTIONAL_TIME(THRESHOLD, AT_HIDDEN), architectures);


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
