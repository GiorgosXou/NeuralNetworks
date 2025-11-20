// This is a minimal example demonstrating the use of a Neural Network (NN) with EEPROM-based weights and biases,
// aiming to reduce RAM and flash-memmory (aka. PROGMEM) usage.
/*
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_internal_EEPROM.ino TO SAVE AN NN INTO EEPROM FIRST, BEFORE USE OF THIS SKETCH
*/

// Macro to calculate the number of elements in an array
#define NumberOf(arg) ((unsigned int)(sizeof(arg) / sizeof(arg[0])))

// Macros for optimization flags
#define _1_OPTIMIZE 0B01001110 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B10000000 // Enable the use of Internal EEPROM
#define FROM_EEPROM_ADDRESS 0  // The position at which the NN will be saved in the internal EEPROM

#include <EEPROM.h>
#include <NeuralNetwork.h>

float *output;

void setup()
{
  Serial.begin(9600);
  while (!Serial){ }; 

  // Initializing a NeuralNetwork that runs (partially) via the Internal EEPROM of the MCU
  // (Partially meaning: weights, biases, etc. NOT LOADED INTO RAM. Only the computation of 
  // outputs of each layer uses RAM, which can be reduced by B01000000 and FeedForward_Individual)
  NeuralNetwork NN(FROM_EEPROM_ADDRESS);

  // "Feeding" the NeuralNetwork with an input array and getting the output
  output = NN.FeedForward((const float[]){1, 0, 0});

  // Displaying the output of double-xor-NN-from-internal-EEPROM for the input value (1, 0, 0)
  Serial.println("Output of double-xor-NN-from-internal-EEPROM for the value (1,0,0) is: " +
                 String(round(output[0])) + " ≅ " + String(output[0], 7));
}

void loop() {}
