#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER

#include <NeuralNetwork.h>

const unsigned int layers[] = {3, 4, 1};
float *output; // 3rd layer's output(s)

// Default Test/Input data
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

// Thanks to #define _2_OPTIMIZE B00100000 you can have:
// [Pretrained Biases ] 1 for each neuron of layer-to-layer
float biases[] = {
  -5.39513 , 11.9918585, -4.4244404, 5.0895796,
  -11.46223,
};

// [Pretrained weights] They are 3*4*1
float weights[] = {
  10.161275, 11.1635275, -10.984715,
  -8.504105, -7.931017 , -8.43375  ,
  -9.152142, 9.405975  ,  8.16624  ,
  -9.437108, 9.365779  , -9.652881 ,

  12.006584, 12.459393 , 12.126074 , -12.9152155,
};


void setup()
{
  Serial.begin(9600);
  while (!Serial){ }; 

  // Creating a NeuralNetwork with pretrained Weights and Biases
  NeuralNetwork NN(layers, weights, biases, NumberOf(layers));

  //Goes through all the input arrays
  for (unsigned int i = 0; i < NumberOf(inputs); i++)
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN  |  returns the predicted output(s)
    Serial.println(output[0], 7);       // Prints the first 7 digits after the comma
  }
  NN.print();                           // Prints the weights & biases of each layer
}
void loop(){}
