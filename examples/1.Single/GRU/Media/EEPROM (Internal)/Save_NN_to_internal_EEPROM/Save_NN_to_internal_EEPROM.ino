/*
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
- CAUTION SAVING AND LOADING IS OPTIMIZED TO WORK BASED ON WHAT ACTIVATION-FUNCTIONS OR BIAS-MODE YOU HAVE DEFINED (OR NOT DEFINED AT ALL)
*/
#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01001010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define IN_EEPROM_ADDRESS 0    // The position at which the NN will be saved at the internal EEPROM
#define USE_GRU__NB            // Makes GRU the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define SELU                   // Defines core activation-function of your NeuralNetwork.
#define GRU_ACT Sigmoid        // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#include <EEPROM.h>
#include <NeuralNetwork.h>


const unsigned int layers[] = {1, 7, 1}; // 1 input-neuron/feature > 7 hidden-neurons > 1 output
float *output; // 3rd layer's output(s)


// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  // GRU LAYER 0 -> 1:
  -0.00000310f,  0.00000000f, -0.05434279f,  0.00637730f, -0.01681493f,  0.04459214f,  0.00338214f, // Reset gate
  -0.02532095f,  0.00000000f,  0.01936465f,  0.09296568f,  0.00000000f,  0.00000000f,  0.00000000f, // Hidden gate
  -0.13306241f,  0.00000000f, -0.04568334f,  0.14990036f,  0.13635142f, -0.13429713f,  0.00461378f, // Update gate
  // GRU LAYER 1 -> 2:
   0.04531341f, // Reset gate
   0.00713156f, // Hidden gate
   0.00000000f, // Update gate
};


// [Pretrained weights]
float weights[] = {
  // GRU LAYER 0 -> 1

  // Reset gate
  -1.33938479f,
  -0.03783005f, -0.14616261f,  0.01099165f,  0.40420756f, -0.12413868f, -0.21799204f,  0.31425563f,
  -2.12496352f,
   0.06030353f, -0.07232196f,  0.43727815f,  0.40129974f,  0.02670722f,  0.18915460f,  0.12371439f,
   0.26889446f,
   0.14978135f,  0.22753280f, -0.13011231f,  0.10110772f,  0.21872441f, -0.02229667f,  0.04458100f,
   0.32001629f,
  -0.00991401f,  0.13759744f,  0.02628658f, -0.00065196f, -0.03384386f,  0.04847182f,  0.33032614f,
  -0.59701645f,
   0.37172565f, -0.18358657f,  0.22922859f,  0.26779452f, -0.11374487f, -0.43449578f, -0.15515219f,
  -0.80770296f,
  -0.09403186f,  0.20660332f,  0.31708854f, -0.07228278f, -0.30018604f, -0.31566471f, -0.26422542f,
  -0.59932673f,
   0.14523080f, -0.02035773f, -0.07518782f, -0.27156660f, -0.10930426f, -0.08516754f, -0.25376886f,

  // Hidden gate
   0.80545270f,
   0.04182721f,  0.22506578f,  0.13529494f,  0.02523871f,  0.34147483f,  0.00007684f,  0.18379337f,
   0.17928584f,
  -0.07628329f, -0.24674916f, -0.33486295f, -0.05998139f, -0.14045849f,  0.02334694f,  0.31924951f,
   1.58848512f,
  -0.08529426f,  0.22714475f,  0.36438805f,  0.06593151f, -0.03847703f,  0.09640963f, -0.01700393f,
  -0.80774242f,
   0.12107311f, -0.24729356f,  0.29799354f, -0.59541887f, -0.47949639f, -0.14173110f,  0.15994872f,
  -2.83003259f,
  -0.13538416f, -0.29974309f, -0.01340835f,  0.08567008f, -0.13786557f, -0.10791776f, -0.39019507f,
  -1.51681042f,
  -0.03578674f,  0.18220270f, -0.17817183f, -0.13040924f, -0.24237464f, -0.31402147f,  0.24421115f,
  -1.09934521f,
   0.12677267f,  0.46648529f, -0.27537617f,  0.34182426f, -0.24830298f, -0.07060461f, -0.11617935f,

  // Update gate
   0.09171966f,
  -0.21972935f,  0.21892552f, -0.43703485f,  0.09061531f,  0.12531221f, -0.20679158f,  0.25482392f,
   0.94072521f,
   0.34856668f,  0.22258312f,  0.00621994f,  0.03413750f, -0.54711282f,  0.47959560f, -0.03990110f,
  -0.08311337f,
   0.34289336f, -0.24712130f, -0.49784896f,  0.28348824f,  0.34726626f,  0.26315150f,  0.04620047f,
  -0.51507634f,
  -0.06561361f, -0.01395036f,  0.16819426f, -0.02510674f, -0.35303560f,  0.03835104f,  0.11195970f,
  -0.18408334f,
  -0.17809591f,  0.30075219f,  0.05793172f, -0.31061724f,  0.16515681f,  0.09561569f, -0.24164955f,
  -0.17061810f,
  -0.62046289f, -0.10634065f, -0.29189479f,  0.20095712f, -0.08498804f,  0.31337199f, -0.15199114f,
  -0.55862677f,
   0.01213941f, -0.02149793f,  0.11186281f, -0.05457438f,  0.13265166f, -0.09191123f,  0.27656209f,

  // GRU LAYER 1 -> 2

  // Reset gate
   0.94509280f,  0.78388548f, -0.48134166f,  0.21569856f, -1.12215674f,  0.16905373f, -0.62353814f,
  -0.78050637f,

  // Hidden gate
  -0.16573721f,  0.71401811f,  0.40147561f, -0.60980886f, -0.40043074f, -0.98667961f,  0.11554884f,
   0.58911568f,

  // Update gate
  -0.29945144f, -0.07561081f, -0.77024752f, -0.22322531f, -0.33787566f,  0.24360655f,  0.25347349f,
  -0.02108407f,
};


void setup()
{
  Serial.begin(9600);
  while (!Serial){ }; // Wait for the Serial connection to be established 
  NeuralNetwork NN(layers, weights, biases, NumberOf(layers)); // Creating a NeuralNetwork with pretrained Weights and Biases
  unsigned int endAddress = NN.save(IN_EEPROM_ADDRESS); // Saves the NN IN_EEPROM_ADDRESS and (optionally)returns where it ended
  Serial.println("Saved GRU of " + String(endAddress - IN_EEPROM_ADDRESS) + "-Bytes into the internal EEPROM of the MCU");
}
void loop(){}

