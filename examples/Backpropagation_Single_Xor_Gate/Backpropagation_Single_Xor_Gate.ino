#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 3)

#include <NeuralNetwork.h>

const unsigned int layers[] = {2,4,1}; //3 layers (1st)layer with 2 input neurons (2nd)layer with 4 hidden neurons and (3rd)layer with 1 output neuron
float *outputs; // 3rd layer's outputs (in this case output)

//Default Inputs
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

  //Trains the NeuralNetwork for 3000 epochs = Training loops
  for(int i=0; i < 3000; i++) // epochs = Training loops
  {
    for (int j = 0; j < NumberOf(inputs); j++)
    {
       NN.FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
       NN.BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
    }
  }

  //Goes through all inputs
  for (int i = 0; i < NumberOf(inputs); i++)
  {
    outputs = NN.FeedForward(inputs[i]); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output 
    Serial.println(outputs[0], 7); // prints the first 7 digits after the comma.
  }

   NN.print(); // prints the weights and biases of each layer

}

void loop() {

}
