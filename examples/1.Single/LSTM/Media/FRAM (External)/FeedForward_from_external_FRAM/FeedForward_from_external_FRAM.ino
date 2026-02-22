// This is a minimal example demonstrating the use of a Neural Network (NN) with FRAM-based weights and biases,
// aiming to reduce RAM and flash-memmory (aka. PROGMEM) usage.
/*
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
*/

#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _3_OPTIMIZE 0B10000001 // Enables the use of external FRAM + REDUCE_RAM_DELETE__GATED_OUTPUTS (Comment\Disable it to increase CPU performance)
#define _2_OPTIMIZE 0B00100000 // Enables MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define USE_LSTM__NB           // Makes LSTM the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork. 
#define LSTM_ACT Sigmoid       // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#define FROM_FRAM_ADDRESS 0    // The position at which the NN is stored in the external FRAM

// From LIBRARY-MANAGER Install: FRAM_I2C (https://github.com/RobTillaart/FRAM_I2C)
#include <FRAM.h>
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on. (OVER-trained, for the sake of Visualization in plotter)
#include <NeuralNetwork.h>


// Pointer to a NeuralNetwork object
NeuralNetwork *NN;
// Input data, gathered from our pseudo-temperature-sensor | 3 temperature-points for each timestep
float input[3];
// 4th layer's output(s)
float *output;


void setupTempSensor() {
  initTempSensor();                   // Initialization of fake/pseudo-temperature-sensor
  for (int i = 0; i < 3; i++) {
    input[i] = getTemp(); delay(250); // gets the 3 initial (timestep-0) temperatures + wait for each next one
  }
}


void setup(){
  FRAM fram;
  Wire.begin();
  Serial.begin(9600);
  while (!Serial){ };

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  // Setup the psudo-sensor
  setupTempSensor();

  // Initializing a NeuralNetwork that runs (partially) via the external FRAM of the MCU
  // (Partially meaning: weights, biases, etc. NOT LOADED INTO RAM. Only the computation of
  // outputs of each layer uses RAM, which can be reduced by B01000000 & FeedForward_Individual)
  NN = new NeuralNetwork(fram, FROM_FRAM_ADDRESS);

  // Print NN's structure
  NN->print();
}


void loop(){
  for (unsigned int i = 0; i < 3; i++)    // Each timestep consist of 3 temperature-samples
      output = NN->FeedForward(&input[i]); // FeedForward each temperature-value & return the (next)-predicted (output)

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

