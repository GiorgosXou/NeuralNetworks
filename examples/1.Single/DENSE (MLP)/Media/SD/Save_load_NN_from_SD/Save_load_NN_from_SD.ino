/*
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS, FLOAT\DOUBLE\INT-MODE OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS, FLOAT\DOUBLE\INT-MODE OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS, FLOAT\DOUBLE\INT-MODE OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- ^^^^^^^ THE ABOVE STATEMENT IS ALSO TRUE WHETHER YOU USED REDUCE_RAM_WEIGHTS_LVL2 OR NOT DURING TRAINING !!!!
- CAUTION THIS EXAMPLE BARELY FITS THE RAM OF ARDUINO UNO. EXPIRIMENT WITH CAUTION ON IT* | THIS IS MAINLY THE RESULT OF NOT USING B01000000 RAM-OPTIMIZATION ...
*/
#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#include <SD.h>                // https://www.arduino.cc/reference/en/libraries/sd/
#define CS_SDPIN   4           // !!! MAKE SURE to change CS-pin to the one you use eg. for Arduino UNO is ...begin(4)
#define FILENAME   "/WEIGHTS"  // * make sure the name is SMALL, simple and starts with /
#define _1_OPTIMIZE 0B00011000 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define ACTIVATION__PER_LAYER  // DEFAULT KEYWORD for allowing the use of any Activation-Function per "Layer-to-Layer".
        #define Sigmoid // 0     Says to the compiler to compile the Sigmoid Activation-Function 
        #define Tanh    // 1     Says to the compiler to compile the Tanh    Activation-Function 

#include <NeuralNetwork.h>
          NeuralNetwork *NN;

unsigned int layers[] = {3, 7, 1}; // 3 layers: (1st)layer with 3-inputs/features (2nd)layer 7-hidden-neurons and (3rd)layer with 1-output-neuron
byte Actv_Functions[] = {   1, 0}; // 1 = Tanh and 0 = Sigmoid (just as a proof of consept)

float *output; // 3th layer's output

//Default Inputs/Training-Data
const float inputs[8][3] = {
  {0, 0, 0}, // = 0
  {0, 0, 1}, // = 1
  {0, 1, 0}, // = 1
  {0, 1, 1}, // = 0
  {1, 0, 0}, // = 1
  {1, 0, 1}, // = 0
  {1, 1, 0}, // = 0
  {1, 1, 1}  // = 1
};
const float expectedOutput[8][1] = {{0}, {1}, {1}, {0}, {1}, {0}, {0}, {1}}; // values that we are expecting to get from the 4th/(output)layer of the Neuralnetwork, in other words something like a feedback to the Neural-network.


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
  randomSeed(millis()); // Just for testing the NN later at loop()
}


void train_and_save_NN()
{
  NN = new NeuralNetwork(layers,NumberOf(layers),Actv_Functions); //Initialization of NeuralNetwork object
  Serial.println(F("Training the NN"));
  do{
    for (unsigned int j = 0; j < NumberOf(inputs); j++) // Epoch
    {
      NN->FeedForward(inputs[j]);      // FeedForwards the input arrays through the NN | stores the output array internally
      NN->BackProp(expectedOutput[j]); // "Tells" to the NN if the output was the-expected-correct one | then, "teaches" it
    }

    // Prints the MSError.
    Serial.print(F("MSE: "));
    Serial.println(NN->MeanSqrdError,6);

    // Loops through each epoch Until MSE goes  < 0.003
  }while(NN->getMeanSqrdError(NumberOf(inputs)) > 0.003);
  
  NN->save(FILENAME); // Saves the NN into the FILENAME
  Serial.println(F("Done"));
}


void setup()
{
  initialize();
  if (SD.exists(FILENAME))            // Checks if FILENAME exists in SD-card
    NN = new NeuralNetwork(FILENAME); // Loads NN | [ use NN->load("/my_file"); while running, to load a new one ]
  else
    train_and_save_NN();              // Else If it doesn't exist, trains it and saves it ...   
  NN->print();                        // Prints the weights and biases of each layer
}


float input[3]; // Input Array
void loop() // testing a hypotherical scenarion
{
  //For example: here you could have a live input from two buttons/switches (or a feed from a sensor if it was a different NN)
  input[0] = random(2); // ... lets say input from a       button/Switch | random(2) = 0 or 1
  input[1] = random(2); // ... lets say input from another button/Switch | random(2) = 0 or 1
  input[2] = random(2); // ... lets say input from another button/Switch | random(2) = 0 or 1
  output = NN->FeedForward(input); // FeedForwards the input-array through the NN | returns the predicted output(s)
  
  Serial.println((String)"Inputs: " + round( input[0]) + "," + round(input[1])+ "," + round(input[2])); // Although you can kind of use casting like...
  Serial.println((String)"Output: " + round(output[0])); // ... "(int)output[0]" instead of round to reduces ROM usage, be careful
  
  delay(1500);
}
