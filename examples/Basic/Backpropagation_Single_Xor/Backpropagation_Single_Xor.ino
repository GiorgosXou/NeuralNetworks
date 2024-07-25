#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)

#define _1_OPTIMIZE 0B00010000 //  https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define SELU                   // Comment   this line and ...
//#define ELU                  // Uncomment this line to use ELU Activation Function

#include <NeuralNetwork.h>

const unsigned int layers[] = {2, 3, 1}; //3 layers (1st)layer with 2 input neurons (2nd)layer with 3 hidden neurons and (3rd)layer with 1 output neuron
float *output; // 3rd layer's output(s)

//Default Inputs/Training-Data
const float inputs[4][2] = {
  {0, 0}, // = 0
  {0, 1}, // = 1
  {1, 0}, // = 1
  {1, 1}  // = 0
};

const float expectedOutput[4][1] = {{0},{1},{1},{0}}; // values that we are expecting to get from the 3rd/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.

void setup()
{
  Serial.begin(9600);
  NeuralNetwork NN(layers,NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates
  
  do{ 
    for (unsigned int j = 0; j < NumberOf(inputs); j++) // Epoch
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


  //Goes through all the input arrays
  for (unsigned int i = 0; i < NumberOf(inputs); i++)
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN | returns the predicted output(s)
    Serial.println(output[0], 7);       // Prints the first 7 digits after the comma.
  }
   NN.print();                          // Prints the weights and biases of each layer
}
void loop() {}
