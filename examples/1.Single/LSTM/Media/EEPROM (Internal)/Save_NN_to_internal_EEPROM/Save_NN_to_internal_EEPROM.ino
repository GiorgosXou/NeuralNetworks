/*
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
*/
#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _3_OPTIMIZE 0B00000001 // ENABLES REDUCE_RAM_DELETE__GATED_OUTPUTS (Comment\Disable it to increase CPU performance)
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01001010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define IN_EEPROM_ADDRESS 0    // The position at which the NN will be saved at the internal EEPROM
#define USE_LSTM__NB           // Makes LSTM the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork. 
#define LSTM_ACT Sigmoid       // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#include <EEPROM.h>
#include <NeuralNetwork.h>


const unsigned int layers[] = {1, 6, 1}; // 1 input-neuron/feature > 6 hidden-neurons > 1 output
float *output; // 3rd layer's output(s)


// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  // LSTM Layer 0 -> 1
   1.00026536e+00,  1.00000000e+00, 1.00250888e+00, 1.00000000e+00,  1.00000000e+00,  1.00000000e+00, // forget gate
   2.20722690e-01,  1.30023473e-05, 0.00000000e+00, 1.64558411e-01,  0.00000000e+00,  1.36244589e-05, // input/update gate
   0.00000000e+00, -1.02434615e-11, 1.70869172e-01, 1.76502556e-01, -1.66924641e-01, -2.71643700e-07, // cell state
   1.20677855e-02,  0.00000000e+00, 0.00000000e+00, 0.00000000e+00, -1.84525296e-01 , 0.00000000e+00, // output gate

  // LSTM Layer 1 -> 2
   1.0829587 , // forget gate
   0.22360934, // input/update gate
   0.19277474, // cell state
  -0.10411564, // output gate
};


// [Pretrained weights]
float weights[] = {
  // LSTM LAYER 0 -> 1

  // forget gate
   0.39946321f,
   0.53314412f,  0.09876864f,  0.22394429f, -0.27697107f, -0.05453104f,  0.02055343f,
   0.49116489f,
  -0.05811211f, -0.12102585f, -0.02828634f, -0.23783672f, -0.06744099f,  0.01464431f,
  -0.84522927f,
   0.13233167f,  0.07849675f, -0.28679976f,  0.13661782f,  0.25697032f,  0.14189914f,
  -1.98829794f,
  -0.22866368f, -0.05625797f, -0.07811587f, -0.14586532f,  0.21605399f, -0.05777653f,
   1.35827482f,
   0.04210760f, -0.04560905f, -0.07495481f,  0.04048335f, -0.03357042f,  0.01903087f,
   2.11748910f,
  -0.22739749f, -0.23216945f,  0.05206724f, -0.34240514f, -0.00683814f,  0.20005216f,

  // input/update gate
  -0.63885266f,
   0.09072137f,  0.13439897f,  0.19967178f,  0.07825780f, -0.50407028f,  0.16791597f,
  -1.20202208f,
  -0.23675047f,  0.18664469f, -0.10452457f,  0.04584002f,  0.06057936f,  0.08155300f,
   1.53077149f,
   0.33688763f,  0.04156153f,  0.13740146f,  0.04792240f,  0.42817014f, -0.30913496f,
  -0.00562429f,
  -0.09148461f,  0.08719451f, -0.08566646f, -0.04492739f, -0.03158337f, -0.09981491f,
   1.84771264f,
  -0.14497064f,  0.38956881f, -0.03813103f,  0.15693441f, -0.08313482f,  0.17130798f,
  -1.07441890f,
   0.25944307f, -0.16822861f, -0.30672848f, -0.01085385f, -0.10693069f, -0.07391746f,

  // cell state
  -1.89399695f,
  -0.18853290f,  0.01446671f, -0.22261819f, -0.07121444f,  0.26616684f, -0.28798938f,
  -0.70225108f,
  -0.14144464f,  0.41245258f, -0.04522229f, -0.07499889f, -0.03899441f, -0.40139183f,
   0.67716485f,
  -0.46234080f, -0.31204486f,  0.60017902f,  0.50611836f, -0.75077480f, -0.38313484f,
   1.20777011f,
  -0.27582711f,  0.23949769f,  0.52289891f,  0.14735718f,  0.05129264f,  0.16497529f,
  -0.38947642f,
  -0.18640739f, -0.08145908f, -0.47170866f,  0.23763219f, -0.05976659f,  0.21137117f,
  -0.19206747f,
  -0.18054433f,  0.22913840f,  0.02256774f, -0.18946812f, -0.18600573f, -0.24026936f,

  // output gate
   0.34145498f,
   0.02569296f, -0.30740348f,  0.24673417f,  0.24740385f,  0.33139467f,  0.19350685f,
   1.63929808f,
  -0.05157050f,  0.19543171f,  0.00214885f, -0.05228107f, -0.05185254f,  0.23357248f,
   1.97462213f,
   0.08355921f, -0.07277633f, -0.20185670f, -0.05923201f, -0.38782489f, -0.06065622f,
   1.51536334f,
   0.10402673f,  0.33111405f,  0.01598506f,  0.35688692f, -0.06611998f,  0.06747419f,
   1.42332029f,
   0.04066662f, -0.15109207f, -0.55749226f, -0.01752009f,  0.11390731f, -0.25611225f,
   1.68252611f,
   0.17969765f,  0.11551546f, -0.06713309f,  0.32499579f, -0.02790840f, -0.27207723f,

  // LSTM LAYER 1 -> 2

  // forget gate
  -0.05610929f,  0.03407475f,  0.07835432f,  0.10527384f, -0.48232764f,  0.07626471f,
  -0.16950469f,

  // input/update gate
  -0.32330844f, -0.01399989f,  0.13636349f,  0.13546516f, -0.25338826f, -0.00583024f,
   0.55364102f,

  // cell state
  -0.24874432f, -0.05229580f,  0.27790213f,  0.09800874f, -0.64907628f,  0.01098746f,
  -0.66030931f,

  // output gate
   0.58283663f,  0.06725086f,  0.00907905f, -0.15209980f,  0.14015821f,  0.00571866f,
   0.18503276f
};


void setup()
{
  Serial.begin(9600);
  while (!Serial){ }; // Wait for the Serial connection to be established 
  NeuralNetwork NN(layers, weights, biases, NumberOf(layers)); // Creating a NeuralNetwork with pretrained Weights and Biases
  unsigned int endAddress = NN.save(IN_EEPROM_ADDRESS); // Saves the NN IN_EEPROM_ADDRESS and (optionally)returns where it ended
  Serial.println("Saved neural-network of " + String(endAddress - IN_EEPROM_ADDRESS) + "-Bytes into the internal EEPROM of the MCU");
}
void loop(){}

