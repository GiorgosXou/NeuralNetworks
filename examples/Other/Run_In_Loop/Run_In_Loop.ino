
#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) //calculates the amount of layers (in this case 3)

//#define REDUCE_RAM_STATIC_REFERENCE
#define SELU 
#include <NeuralNetwork.h>
          NeuralNetwork *NN; // creates a pointer to -> an object of NeuralNetwork in the RAM


const unsigned int layers[] = {2,4,1}; //3 layers (1st)layer with 2 input neurons (2nd)layer with 4 hidden neurons and (3rd)layer with 1 output neuron
float *outputs; // 3rd layer's outputs (in this case output)

//Default Inputs [for Training only]
const float inputs[4][2] = {
  {0, 0}, //0
  {0, 1}, //1
  {1, 0}, //1
  {1, 1}  //0
};
const float expectedOutput[4][1] = {{0},{1},{1},{0}}; // values that we were expecting to get from the 3rd/(output)layer of Neural-network, in other words something like a feedback to the Neural-network.


void setup(){
 
  Serial.begin(9600);
  NN = new NeuralNetwork(layers,NumberOf(layers)); //Initialization of NeuralNetwork object
 
  do{
    for (int j = 0; j < NumberOf(inputs); j++)
    {
       NN->FeedForward(inputs[j]);      // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
       NN->BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
    }
    
    // Prints the Error.
    Serial.print("MSE: "); 
    Serial.println(NN->MeanSqrdError,6);

    // loops through each epoch Until MSE goes < 0.003
  }while(NN->GetMeanSqrdError(NumberOf(inputs)) > 0.003);
  
  NN->print(); // prints the weights and biases of each layer
}


float INPUT_[1][2]; // Dynamic/Changable Input variable
void loop() {

  //As a brief example, here you could have a live input from two buttons/switches (or a feed from a sensor if it where a different NN)
  INPUT_[0][0] = 1; // ... lets say input from a       button/Switch
  INPUT_[0][1] = 0; // ... lets say input from another button/Switch
 
  outputs = NN->FeedForward(INPUT_[0]); // Feeds-Forward the Dynamic INPUT_[] to the first layer of the NN and Gets the output
  Serial.print("Output: ");
  Serial.println(outputs[0], 7);        // prints the first 7 digits after the comma.

  delay(1000);
  
}
