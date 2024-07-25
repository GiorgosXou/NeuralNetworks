#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _1_OPTIMIZE 0B11010010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B00100100 // MULTIPLE_BIASES_PER_LAYER + int8_t quantization
#include <NeuralNetwork.h>

const unsigned int layers[] = {3, 3, 1};
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

// [Pretrained Biases ] 1 for each neuron of layer-to-layer
const PROGMEM int8_t biases[] = {
  -49, -23, 22,
   29,
};

// [Pretrained weights]
const PROGMEM int8_t weights[] = {
   25,  49,  26,
  -33,  32,  48,
  -48, -33,  35,

  -60,  61, -60,
};


void setup()
{
  Serial.begin(9600);
  NeuralNetwork NN(layers, weights, biases, NumberOf(layers)); // Creating a NeuralNetwork with pretrained Weights and Biases

  //Goes through all the input arrays
  for (unsigned int i = 0; i < NumberOf(inputs); i++)
  {
    output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN  |  returns the predicted output(s)
    Serial.println(output[0], 7);       // Prints the first 7 digits after the comma
  }
  NN.print();                           // Prints the weights & biases of each layer
}
void loop(){}
