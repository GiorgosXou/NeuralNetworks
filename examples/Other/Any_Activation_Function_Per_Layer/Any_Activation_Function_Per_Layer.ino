#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 4)

#define _1_OPTIMIZE B00010000 // REDUCING RAM By using the same pointer for every layer's weights.
#define ACTIVATION__PER_LAYER // DEFAULT KEYWORD for allowing the use of any Activation-Function per Layer-to-Layer .
//        #define Sigmoid // 0   UNCOMMENT LINES| Says to the compiler to compile ONLY Sigmoid (reduces ROM and RAM).
//        #define Tanh    // 1   UNCOMMENT LINES| Says to the compiler to compile ONLY Tanh    (reduces ROM and RAM).

#include <NeuralNetwork.h>

unsigned int layers[] = {3, 9, 9, 1}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
byte Actv_Functions[] = {  1, 1, 0 }; // 1 = Tanh and 0 = Sigmoid (in this case)  (just as a proof of consept)

float *outputs; // 4th layer's outputs (in this case output)

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

const float expectedOutput[8][1] = {{0}, {1}, {1}, {0}, {1}, {0}, {0}, {1}}; // values that we were expecting to get from the 4th/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.

void setup()
{

  Serial.begin(9600);
  NeuralNetwork NN(layers, NumberOf(layers), Actv_Functions); // Creating a NeuralNetwork with default learning-rates

  do{ 
    for (int j=0; j < NumberOf(inputs); j++) // loops through one Epoch
    {
      NN.FeedForward(inputs[j]);             // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
      NN.BackProp(expectedOutput[j]);        // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
    }

    // Prints the Error.
    Serial.print("MSE: "); 
    Serial.println(NN.MeanSqrdError,6);

    // loops through each epoch Until MSE goes < 0.003
  }while(NN.GetMeanSqrdError(NumberOf(inputs)) > 0.003);


  Serial.println("\n =-[OUTPUTS]-=");


  for (int i=0; i < NumberOf(inputs); i++) //Goes through all inputs/Training-Data
  {
    outputs = NN.FeedForward(inputs[i]);   // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output
    Serial.print(round(outputs[0]));       // Prints the output Rounded.
    Serial.print(" ≅ ");                   // Prints the symbol approximately equal. 
    Serial.println(outputs[0], 7);         // Prints the first 7 digits of the output after the comma.
  }

  //NN.print(); // prints the weights and biases of each layer
}

void loop() {}
