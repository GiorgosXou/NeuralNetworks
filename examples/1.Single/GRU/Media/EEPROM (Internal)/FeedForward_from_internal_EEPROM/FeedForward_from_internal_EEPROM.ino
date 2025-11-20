// This is an example demonstrating the use of a Neural-Network (NN) with EEPROM-based weights & biases,
// aiming to reduce RAM and flash-memmory (aka. sketch size) usage.
/*
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
*/
//#define DISABLE_SINGLE_TIMESTEP_THRESHOLD // You may completely disable the single-threshold-logic to reduce sketch-size (if unnecessary)

#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _3_OPTIMIZE 0B00000001 // ENABLES REDUCE_RAM_DELETE__GATED_OUTPUTS (Comment\Disable it to increase CPU performance)
#define _2_OPTIMIZE 0B10100000 // ENABLES USE_INTERNAL_EEPROM + MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define FROM_EEPROM_ADDRESS 0  // The position at which the NN will be saved in the internal EEPROM
#define USE_GRU__NB            // Makes GRU the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork. 
#define GRU_ACT Sigmoid        // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#include <EEPROM.h>
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on. (OVER-trained, for the sake of Visualization in plotter)
#include <NeuralNetwork.h>


// Input data, gathered from our pseudo-temperature-sensor | 3 temperature-points for each timestep
float input[3];
// 4th layer's output(s)
float *output;
// Creating NeuralNetwork with pretrained Weights and Biases;
NeuralNetwork NN(FROM_EEPROM_ADDRESS);


void setupTempSensor() {
  initTempSensor();                   // Initialization of fake/pseudo-temperature-sensor
  for (int i = 0; i < 3; i++) {
    input[i] = getTemp(); delay(250); // gets the 3 initial (timestep-0) temperatures + wait for each next one
  }
}


void setup(){
  Serial.begin(9600); // Initialization/begining of Serial at 9600 baud-rate
  while (!Serial){ }; // Wait for the Serial connection to be established 
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

