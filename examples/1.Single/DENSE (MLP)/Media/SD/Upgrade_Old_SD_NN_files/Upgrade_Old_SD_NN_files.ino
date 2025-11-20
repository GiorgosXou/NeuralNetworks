// -----------------------------------------------------------------------------------------------
// This sketch is specifically designed for migrating/upgrading older Neural Network (NN) files
// from version 2.x.x to version 3.x.x. It is not intended for any other purpose or general use.
// ===============================================================================================

// MAKE SURE YOU DEFINED AND ENABLED THE SAME PROPERTIES YOUR ORIGINAL/OLD NN WAS TRAINED WITH

#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#include <SD.h>                // https://www.arduino.cc/reference/en/libraries/sd/
#define CS_SDPIN 4             // !!! MAKE SURE to change CS-pin to the one you use eg. for Arduino UNO is ...begin(4)
#define OLD_NN "/OLD"          // * The old filename where the NN is stored/exists
#define NEW_NN "/NEW"          // * The new filename .... make sure the name is SMALL, simple and starts with /
#define _1_OPTIMIZE 0B01011000 // (0B01 doesn't effect anything) Make sure to enable the same optimizations your original/old NN was trained with
#define ACTIVATION__PER_LAYER  // Make sure you defined the same Activation-Functions you defined during training of the old-NN
        #define Sigmoid // 0      Says to the compiler to compile the Sigmoid Activation-Function
        #define Tanh    // 1      Says to the compiler to compile the Tanh    Activation-Function

#include <NeuralNetwork.h>
          NeuralNetwork NN;


void initialize()
{
  Serial.begin(9600);
  while (!Serial){ }; 
  Serial.print(F("Initializing SD"));
  if (!SD.begin(CS_SDPIN)) { // !!! MAKE SURE to change CS-pin to the one you use eg. for Arduino UNO is ...begin(4)
    Serial.println(F(", failed!"));
    exit(0);
  }
  Serial.println(F(", done."));
  delay(2000); // wait to prevent potential reset-interupt during saving
}


void setup()
{
  initialize();
  if (SD.exists(NEW_NN)){ // Checks if NEW_NN exists in SD-card
    // if already exists, load it and ...
    Serial.println(F(NEW_NN " already exists"));
    NN.load(NEW_NN);
  }else if (SD.exists(OLD_NN)){ // Else checks if OLD_NN exists in SD-card
    // if exists, convert/save it with new [V.3.X.X] algorithm and ...
    NN.load_old(OLD_NN);
    NN.save(NEW_NN);
    Serial.println(F("Saved."));
  }else{
    Serial.println(F(OLD_NN " does not exist"));
    exit(0);
  }
  // ... print it's parameters
  NN.print();
}


void loop() {}
