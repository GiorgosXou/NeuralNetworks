#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _2_OPTIMIZE 0B00000000 // Enable 0B01.. for NO_BIAS or 0B001.. for MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B00011000 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define Tanh                   // Comment this line to use Sigmoid (the default) activation function

#include <NeuralNetwork.h>

const unsigned int layers[] = {3, 5, 1}; // 3 layers (1st)layer with 3-inputs/features (2nd)layer 5 hidden neurons each and (3rd)layer with 1 output neuron
float *output; // 3rd layer's output(s)

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

const float expectedOutput[8][1] = {{0}, {1}, {1}, {0}, {1}, {0}, {0}, {1}}; // values that we are expecting to get from the 3rd/(output)layer of Neural-Network, in other words something like a feedback to the Neural-network.

void setup()
{
  Serial.begin(9600);
  while (!Serial){ }; 

  // Creating a Neural-Network with default learning-rates
  NeuralNetwork NN(layers, NumberOf(layers));

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


  Serial.println("\n=-[OUTPUTS]-=");


  //Goes through all the input arrays
  for (unsigned int i = 0; i < NumberOf(inputs); i++)
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN | returns the predicted output(s)
    Serial.println(output[0], 7);       // Prints the first 7 digits after the comma.
  }
  NN.print();                           // Prints the weights and biases of each layer
}
void loop() {}
