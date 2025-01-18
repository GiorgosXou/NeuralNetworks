// This is a minimal example demonstrating the use of a Neural Network (NN) with FRAM-based weights and biases,
// aiming to reduce RAM and flash-memmory (aka. PROGMEM) usage.
/*
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
   CAUTION: Use Save_NN_to_external_FRAM.ino TO SAVE AN NN INTO FRAM FIRST, BEFORE USE OF THIS SKETCH
*/

// Macro to calculate the number of elements in an array
#define NumberOf(arg) ((unsigned int)(sizeof(arg) / sizeof(arg[0])))

// Macros for optimization flags
#define _1_OPTIMIZE 0B01000110 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _3_OPTIMIZE 0B10000000 // Enable the use of external FRAM
#define FROM_FRAM_ADDRESS 0  // The position at which the NN will be saved in the external FRAM

// From LIBRARY-MANAGER Install: FRAM_I2C (https://github.com/RobTillaart/FRAM_I2C)
#include <FRAM.h>
#include <NeuralNetwork.h>

float *output;

void setup()
{
  FRAM fram;
  Wire.begin();
  Serial.begin(9600);

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  // Initializing a NeuralNetwork that runs (partially) via the external FRAM of the MCU
  // (Partially meaning: weights, biases, etc. NOT LOADED INTO RAM. Only the computation of
  // outputs of each layer uses RAM, which can be reduced by B01000000 & FeedForward_Individual)
  NeuralNetwork NN(fram, FROM_FRAM_ADDRESS);

  // "Feeding" the NeuralNetwork with an input array and getting the output
  output = NN.FeedForward((const float[]){1, 0, 0});

  // Displaying the output of double-xor-NN-from-external-FRAM for the input value (1, 0, 0)
  Serial.println("Output of double-xor-NN-from-external-FRAM for the value (1,0,0) is: " +
                 String(round(output[0])) + " ≅ " + String(output[0], 7));

  // Print NN's structure
  NN.print();
}

void loop() {}
