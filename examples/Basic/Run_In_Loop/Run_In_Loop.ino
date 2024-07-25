#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)

#define SELU 
#include <NeuralNetwork.h>
          NeuralNetwork *NN;

const unsigned int layers[] = {2,3,1}; //3 layers (1st)layer with 2 input neurons (2nd)layer with 3 hidden neurons and (3rd)layer with 1 output neuron
float *output; // 3rd layer's output(s)

//Default Inputs [for Training only]
const float inputs[4][2] = {
  {0, 0}, // = 0
  {0, 1}, // = 1
  {1, 0}, // = 1
  {1, 1}  // = 0
};
const float expectedOutput[4][1] = {{0},{1},{1},{0}}; // Values that we are expecting to get from the 3rd/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.


void setup()
{   
  Serial.begin(9600);
  randomSeed(millis());
  
  NN = new NeuralNetwork(layers,NumberOf(layers)); //Initialization of NeuralNetwork object
 
  do{
    for (unsigned int j = 0; j < NumberOf(inputs); j++) // Epoch
    {
      NN->FeedForward(inputs[j]);      // FeedForwards the input arrays through the NN | stores the output array internally
      NN->BackProp(expectedOutput[j]); // "Tells" to the NN if the output was the-expected-correct one | then, "teaches" it
    }
    
    // Prints the MSError.
    Serial.print("MSE: "); 
    Serial.println(NN->MeanSqrdError,6);

    // Loops through each epoch Until MSE goes  < 0.003
  }while(NN->getMeanSqrdError(NumberOf(inputs)) > 0.003);
  
  NN->print(); // Prints the weights and biases of each layer
}


float input[2]; // Input Array
void loop() 
{
  //For example: here you could have a live input from two buttons/switches (or a feed from a sensor if it was a different NN)
  input[0] = random(2); // ... lets say input from a       button/Switch | random(2) = 0 or 1
  input[1] = random(2); // ... lets say input from another button/Switch | random(2) = 0 or 1
 
  output = NN->FeedForward(input); // FeedForwards the input-array through the NN | returns the predicted output(s)
  
  Serial.println((String)"Inputs: " + round( input[0]) + "," + round(input[1])); // Although you can kind of use casting like:
  Serial.println((String)"Output: " + round(output[0])); // "(int)output[0]" instead of round to reduces ROM usage, be careful
  
  delay(1500);
}
