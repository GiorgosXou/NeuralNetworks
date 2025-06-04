#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the number of layers (in this case 4)

#define _1_OPTIMIZE 0B00010000 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define ACTIVATION__PER_LAYER  // DEFAULT KEYWORD for allowing the use of any Activation-Function per "Layer-to-Layer".
        #define Sigmoid // 0     Says to the compiler to compile the Sigmoid Activation-Function 
        #define Tanh    // 1     Says to the compiler to compile the Tanh    Activation-Function 

#include <NeuralNetwork.h>

unsigned int layers[] = {3, 9, 9, 1}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
byte Actv_Functions[] = {   1, 1, 0}; // 1 = Tanh and 0 = Sigmoid (just as a proof of consept)

float *output; // 4th layer's output

//Default Inputs/Training-Data
const float inputs[8][3] = {
  {0, 0, 0}, //0
  {0, 0, 1}, //1
  {0, 1, 0}, //1
  {0, 1, 1}, //0
  {1, 0, 0}, //1
  {1, 0, 1}, //0
  {1, 1, 0}, //0
  {1, 1, 1}  //1
};

const float expectedOutput[8][1] = {{0}, {1}, {1}, {0}, {1}, {0}, {0}, {1}}; // values that we are expecting to get from the 4th/(output)layer of the Neuralnetwork, in other words something like a feedback to the Neural-network.

void setup()
{
  Serial.begin(9600);
  NeuralNetwork NN(layers, NumberOf(layers), Actv_Functions); // Creating a Neural-Network with default learning-rates

  do{ 
    for (unsigned int j=0; j < NumberOf(inputs); j++) // Epoch
    {
      NN.FeedForward(inputs[j]);      // FeedForwards the input arrays through the NN | stores the output array internally
      NN.BackProp(expectedOutput[j]); // "Tells" to the NN if the output was the-expected-correct one | then, "teaches" it
    }

    // Prints the Error.
    Serial.print("MSE: "); 
    Serial.println(NN.MeanSqrdError,6);

    // Loops through each epoch Until MSE goes < 0.003
  }while(NN.getMeanSqrdError(NumberOf(inputs)) > 0.003);


  Serial.println("\n =-[OUTPUTS]-=");


  for (unsigned int i=0; i < NumberOf(inputs); i++) //Goes through all input-arrays/Training-Data
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN | returns the predicted output(s)
    Serial.print(round(output[0]));     // Prints the output Rounded.
    Serial.print(" ≅ ");                // Prints the symbol approximately equal.
    Serial.println(output[0], 7);       // Prints the first 7 digits of the output after the comma.
  }

  NN.print(); // Prints the weights and biases of each layer
}
void loop() {}
