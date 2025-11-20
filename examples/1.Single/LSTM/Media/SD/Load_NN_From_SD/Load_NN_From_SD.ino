#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#include <SD.h>                // https://www.arduino.cc/reference/en/libraries/sd/
#define CS_SDPIN   4           // !!! MAKE SURE to change CS-pin to the one you use eg. for Arduino UNO is ...begin(4)
#define FROM_FILE  "/LSTM.BIN" // * make sure the name is SMALL, simple and starts with /
#define _3_OPTIMIZE 0B00000001 // ENABLES REDUCE_RAM_DELETE__GATED_OUTPUTS (Comment\Disable it to increase CPU performance)
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define USE_LSTM__NB           // Makes LSTM the core-architecture of your NeuralNetwork (NB = NO_BACKPROP support) & of all the ones you are allowed to `load()`
#define SELU                   // Defines core activation-function of your NeuralNetwork & of all the ones you are allowed to `load()`
#define LSTM_ACT Sigmoid       // Defines the core recurrent-activation-function of your NeuralNetwork & of all the ones you are allowed to `load()`. (Sigmoid is the default, not necessary to define)
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on. (OVER-trained, for the sake of Visualization in plotter)
#include <NeuralNetwork.h>


NeuralNetwork NN; // Creating NeuralNetwork Object
float input[3];   // Input data, gathered from our pseudo-temperature-sensor
float *output;    // Last layer's output(s)


void setupTempSensor() {
  initTempSensor();           // Initialization of fake/pseudo-temperature-sensor
  for (int i = 0; i < 3; i++) // gets the 3 initial (timestep-0) temperatures + wait for each next one
    input[i] = getTemp(); delay(250); 
}


void initializeSD(){
  Serial.print(F("Initializing SD"));
  if (!SD.begin(CS_SDPIN)) { Serial.println(F(", failed!")); exit(0); }  // !!! MAKE SURE to change CS-pin to the one you use eg. for Arduino UNO is ...begin(4)
  Serial.println(F(", done."));
}


void setup(){
  Serial.begin(9600); // Initialization/begining of Serial at 9600 baud-rate
  while (!Serial){ }; // Wait for the Serial connection to be established 
  initializeSD();     // Initialization the SD card
  setupTempSensor();  // Initialization + population of timestep-0 with temperatures
  NN.load(FROM_FILE)  // Loading our NN after the Initialization of the SD
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

