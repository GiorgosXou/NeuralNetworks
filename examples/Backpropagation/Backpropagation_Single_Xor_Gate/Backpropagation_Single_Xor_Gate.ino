#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 3)

#define _1_OPTIMIZE B00010000 // REDUCING RAM By using the same pointer for every layer's weights.
#define SELU                  // Uncomment this line to use SELU Activation Function     (faster!)
//#define ELU                   // Uncomment this line to use  ELU Activation Function (way faster!)

#include <NeuralNetwork.h>

const unsigned int layers[] = {2,4,1}; //3 layers (1st)layer with 2 input neurons (2nd)layer with 4 hidden neurons and (3rd)layer with 1 output neuron
float *outputs; // 3rd layer's outputs (in this case output)

//Default Inputs/Training-Data
const float inputs[4][2] = {
  {0, 0}, //0
  {0, 1}, //1
  {1, 0}, //1
  {1, 1}  //0
};

const float expectedOutput[4][1] = {{0},{1},{1},{0}}; // values that we were expecting to get from the 3rd/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.

void setup()
{
  
  Serial.begin(9600);
  NeuralNetwork NN(layers,NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates
  
  do{ 
    for (int j = 0; j < NumberOf(inputs); j++) // 1 epoch
    {
       NN.FeedForward(inputs[j]);      // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
       NN.BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
    }
    
    // Prints the Error.
    Serial.print("MSE: "); 
    Serial.println(NN.MeanSqrdError,6);

    // loops through each epoch Until MSE goes < 0.003
  }while(NN.GetMeanSqrdError(NumberOf(inputs)) > 0.003);


  Serial.println("\n =-[OUTPUTS]-=");


  //Goes through all inputs
  for (int i = 0; i < NumberOf(inputs); i++)
  {
    outputs = NN.FeedForward(inputs[i]); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output 
    Serial.println(outputs[0], 7);       // prints the first 7 digits after the comma.
  }

   NN.print(); // prints the weights and biases of each layer
}

void loop() {}
