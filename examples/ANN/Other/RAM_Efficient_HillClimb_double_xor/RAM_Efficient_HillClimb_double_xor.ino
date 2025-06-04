
/*
* This sketch utilizes a computationally-expensive but memmory-efficient Hill-Climbing algorithm,
* It requires only a few constant-size bytes of extra RAM to train any neural network (NN).
* The algorithm is primarily designed for fine-tuning pre-trained NNs using _3_OPTIMIZE 0B00100000.
* However, in this specific example, the alternative _3_OPTIMIZE 0B01000000 is used to demonstrate full training.
* In case of need for dynamic-changes in learning-rates, see _3_OPTIMIZE 0B00010000 (HILL_CLIMB_DYNAMIC_LEARNING_RATES support).
*/

#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _3_OPTIMIZE 0B01000000 // Enabling a computationally expensive but memmory-efficient Hill-Climbing algorithm
#define _1_OPTIMIZE 0B00010000 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#include <NeuralNetwork.h>

const unsigned int layers[] = {3, 5, 1}; // 3 layers (1st)layer with 3-input-neurons (2nd)layer 5-hidden-neurons and (3rd)layer with 1-output
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
  NeuralNetwork NN(layers, NumberOf(layers), 0.14, 0.02); // Creating a Neural-Network with learning-rates of 0.14 & 0.02 for weights & bias(es)

  do{
    for (unsigned int j = 0; j < NumberOf(inputs); j++) // Epoch
    {
      NN.FeedForward(inputs[j]);                 // FeedForwards the input arrays through the NN | stores the output array internally
      NN.ComputeSummedErrors(expectedOutput[j]); // Computes the sum of errors.
    }
    
    // Prints the Error.
    Serial.print("MSE: "); 
    Serial.println(NN.MeanSqrdError,6);

    // Loops\HillClimbs through each epoch Until MSE goes < 0.003
  }while (NN.HillClimb(NN.getMeanSqrdError(NumberOf(inputs)), 0.003));


  Serial.println("\n =-[OUTPUTS]-=");


  //Goes through all the input arrays
  for (unsigned int i = 0; i < NumberOf(inputs); i++)
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN | returns the predicted output(s)
    Serial.println(output[0], 7);       // Prints the first 7 digits after the comma.
  }
  NN.print();                           // Prints the weights and biases of each layer
}
void loop() {}
