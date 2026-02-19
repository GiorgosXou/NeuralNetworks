/*
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
*/
#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 4)
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define IN_FRAM_ADDRESS 0      // The position at which the NN will be saved at the external FRAM
#define USE_RNN__NB            // Makes (vanilla)-RNN the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork.
#include <FRAM.h>              // From LIBRARY-MANAGER Install: FRAM_I2C (https://github.com/RobTillaart/FRAM_I2C)
#include <NeuralNetwork.h>


const unsigned int layers[] = {1, 8, 1}; // 1 input/feature -> 8 hidden-neurons -> 1 output
float *output; // 3rd layer's output(s)

// Input data, gathered from our pseudo-temperature-sensor | 3 temperature-points for each timestep
float input[3];

// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  // RNN Layer 0 -> 1
  0.01358685, -0.00514791, 0.00213663, 0, 0.00012937, 0, 0.01629594, 0.00138612,
  // RNN Layer 1 -> 2
  0.03628523
};

// [Pretrained weights]
float weights[] = {
  // RNN Layer 0 -> 1
   1.22961831f,
   0.09631307f, -0.49769780f, -0.52050328f,  0.14724196f,  0.14216658f,  0.31458798f,  0.34053445f,  0.42788458f,
   1.06252575f,
   0.26479334f,  0.33770260f,  0.36780581f,  0.28700602f,  0.06649943f,  0.37049711f,  0.01079199f,  0.24036717f,
   0.02880220f,
  -0.26020879f, -0.46077374f,  0.62794960f, -0.14259411f, -0.33157930f,  0.38858604f, -0.02152641f,  0.20956597f,
  -2.07335281f,
  -0.46790832f,  0.18415610f, -0.31656858f,  0.44898683f, -0.18732452f,  0.51421177f, -0.32222831f, -0.20495902f,
  -0.12038947f,
   0.47241697f, -0.26723957f,  0.10427390f,  0.60275561f, -0.33342332f, -0.27658278f, -0.37639344f,  0.04331696f,
  -2.07136917f,
   0.28059754f, -0.23191825f,  0.23295835f,  0.05440384f,  0.65276182f,  0.35014871f, -0.22016022f, -0.46160263f,
   1.66096437f,
   0.32154834f,  0.35375106f, -0.26415607f, -0.56341839f, -0.17914364f,  0.24136791f, -0.29237694f,  0.36419830f,
   1.21911037f,
   0.29247519f, -0.18353373f, -0.12029932f, -0.15544552f, -0.51464641f,  0.25716805f,  0.22204265f, -0.65589458f,
  // RNN Layer 1 -> 2
   0.19118384f,  0.03528649f, -0.76362145f,  0.42128202f, -0.12675120f, -0.65542620f,  0.29082689f,  0.03534147f,
  -0.41052172f
};


void setup()
{
  FRAM fram;
  Wire.begin();
  Serial.begin(9600);
  while (!Serial){ };

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  NeuralNetwork NN(layers, weights, biases, NumberOf(layers)); // Creating a NeuralNetwork with pretrained Weights and Biases
  unsigned int endAddress = NN.save(fram, IN_FRAM_ADDRESS); // Saves the NN IN_FRAM_ADDRESS and (optionally)returns where it ended
  Serial.println("Saved neural-network of " + String(endAddress - IN_FRAM_ADDRESS) + "-Bytes into the external FRAM of the MCU");
}
void loop(){}

