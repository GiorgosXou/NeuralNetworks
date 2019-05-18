#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 4)

#include <NeuralNetwork.h>

unsigned int layers[] = {3, 9, 9, 1}; // 4 layers (1st)layer with 3 input neurons (2nd & 3rd)layer 9 hidden neurons each and (4th)layer with 1 output neuron
float *outputs; // 4th layer's outputs (in this case output)

//Default Inputs
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

  NeuralNetwork NN(layers, NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates

  //Trains the NeuralNetwork for 8000 epochs = Training loops
  for (int i = 0; i < 8000; i++)
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
