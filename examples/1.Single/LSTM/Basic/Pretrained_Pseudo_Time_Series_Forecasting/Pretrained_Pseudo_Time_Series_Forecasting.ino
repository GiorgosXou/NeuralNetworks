#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0]))) // calculates the number of layers (in this case 3)
#define _3_OPTIMIZE 0B00000001 // ENABLES REDUCE_RAM_DELETE__GATED_OUTPUTS (Comment\Disable it to increase CPU performance)
#define _2_OPTIMIZE 0B00100000 // ENABLES MULTIPLE_BIASES_PER_LAYER
#define _1_OPTIMIZE 0B01011010 // https://github.com/GiorgosXou/NeuralNetworks#define-macro-properties
#define USE_LSTM__NB           // Makes LSTM the core-architecture of your NeuralNetwork. (NB = NO_BACKPROP support)
#define ReLU                   // Defines core activation-function of your NeuralNetwork. 
#define LSTM_ACT Sigmoid       // Defines the core recurrent-activation-function of your NeuralNetwork. (Sigmoid is the default, not necessary to define)
#include "PseudoSensors.h"     // A fake/pseudo temperature-sensor on which the NN was trained on.
#include <NeuralNetwork.h>


const unsigned int layers[] = {3, 6, 1}; // 3 input-neurons/features > 6 hidden-neurons > 1 output
float *output; // 3rd layer's output(s)

// Test/Input data, gathered from our pseudo-temperature-sensor  
// [timestep][feature] = 3 temperature points, each with 3 features
float inputs[3][3]; 

// Thanks to #define _2_OPTIMIZE B00100000 you have:
// [Pretrained Biases] 1 for each neuron of layer-to-layer
float biases[] = {
  // LSTM Layer 0 -> 1
  //
  // forget gate
  1.00000000e+00, 1.00000000e+00,  1.25248528e+00,  1.00001001e+00,  1.00000000e+00,  1.00000000e+00,
  // input/update gate
  0.00000000e+00, 0.00000000e+00,  0.00000000e+00,  1.40355319e-01,  0.00000000e+00,  1.21451449e-03,
  // cell state
  0.00000000e+00, 0.00000000e+00,  2.62340695e-01,  1.87162459e-01,  0.00000000e+00,  1.29580998e-03,
  // output gate
  0.00000000e+00, 0.00000000e+00, -1.09048694e-01, -1.02207225e-04,  0.00000000e+00,  6.78539655e-11,


  // LSTM Layer 1 -> 2
  //
  // forget gate
   1.1003171, 
  // input/update gate
   0.1894697, 
  // cell state
   0.22329234, 
  // output gate
  -0.07524981
};

// [Pretrained weights]
float weights[] = {
  // LSTM LAYER 0 -> 1

  // forget gate
   0.22821866, -0.65545577,  0.8145403 ,
   0.5334635 ,  0.09876864,  0.21247445, -0.276397  , -0.05444458,  0.02055343,
   0.2835742 ,  0.5198261 ,  0.66201866, 
  -0.05811211, -0.12102585, -0.02828634, -0.23783672, -0.06744099,  0.01464431,
  -0.25704363, -1.232965  ,  0.09125342, 
   0.13233167,  0.07849675, -0.13327086,  0.3750872 ,  0.2608953 ,  0.14171705,
  -1.1471213 , -0.3660638 , -0.4049711 , 
  -0.22866368, -0.05625797, -0.07825997, -0.14545113,  0.21605399, -0.05777653,
   0.7842004 ,  0.5854538 , -0.06951999, 
   0.0421076 , -0.04560905, -0.07495481,  0.04048335, -0.03357042,  0.01903087,
   1.2225329 ,  0.2463733 ,  0.5043682 , 
  -0.22739749, -0.23216945,  0.05206724, -0.34240514, -0.00683814,  0.20005216,

  // input/update gate
  -0.50028795, -0.26516846,  0.8629024 , 
   0.14603055,  0.13439897, -0.00588223, -0.26114377, -0.23144594,  0.16791597,
  -0.6939878 ,  1.8059947 ,  0.9616955 ,
  -0.23675047,  0.18664469, -0.10487165,  0.04584201,  0.06058063,  0.081553  ,
   0.8837913 ,  0.17976445, -0.6355908 ,
   0.33688763,  0.04156153,  0.13740146,  0.0479224 ,  0.42817014, -0.30913496,
   0.0559902 ,  0.32111633,  0.7361056 ,
  -0.06590211,  0.08719451, -0.07349604, -0.10887568,  0.18843777, -0.10087894,
   1.0667773 , -0.5632981 , -1.7046987 ,
  -0.14497064,  0.3895688 , -0.03813103,  0.15693441, -0.08313482,  0.17130798,
  -0.60648173, -0.3876489 ,  1.2823611 ,
   0.25944307, -0.16822861, -0.29515833, -0.0108159 , -0.10693069, -0.07391746,

  // cell state
  -1.0934997 , -0.14119755,  1.4659587 , 
  -0.1885329 ,  0.01446671, -0.22261819, -0.07121444,  0.26616684, -0.28798938,
  -0.40544483, -0.86637026,  1.0393487 ,
  -0.14144464,  0.41245258, -0.04522229, -0.07499889, -0.03899441, -0.40139183,
   0.52087843,  0.02402944, -0.4501974 ,
  -0.23849934, -0.31204486,  0.70047915,  0.49572223, -0.2957935 , -0.3072901 ,
   0.79136515, -1.8860978 ,  0.9280553 ,
  -0.24310245,  0.23949769,  0.49295202,  0.0866797 ,  0.27342808,  0.16484658,
  -0.12812336,  0.10214321, -0.06205229,
  -0.18640739, -0.08145908, -0.32224917,  0.35094884, -0.14742595,  0.21137117,
  -0.0968838 ,  1.4207103 ,  1.1103734 ,
  -0.18054433,  0.2291384 ,  0.03472814, -0.18937767, -0.18600573, -0.24026936,

  // output gate
   0.13292764, -0.4377505 , -0.6420141 , 
   0.00964168, -0.30740348,  0.10838639,  0.2445347 ,  0.3534783 ,  0.19350685,
   0.94644916, -1.5230649 , -0.38317043,
  -0.0515705 ,  0.19543171,  0.00214885, -0.05228107, -0.05185254,  0.23357248,
   1.0655411 , -0.80397695,  0.3047849 ,
   0.08355921, -0.07277633, -0.26777634, -0.1883128 , -0.3878249 , -0.06064489,
   0.87328166, -0.67618483,  0.1568314 ,
   0.10402673,  0.33111405,  0.01255681,  0.3564693 , -0.06611998,  0.06747419,
   0.93677527, -0.80159575,  1.1004612 ,
  -0.11617068, -0.15109207, -0.3440451 , -0.09478746,  0.08942974, -0.25611225,
   0.97140694,  0.67385834, -0.76053965,
   0.17969765,  0.11551546, -0.06713309,  0.3249958 , -0.0279084 , -0.27207723,

  // LSTM LAYER 1 -> 2

  // forget gate
   0.07373408,  0.03407475, 0.107731  , -0.0438153 ,  0.05283786, 0.13881046,
  -0.1300363 ,

  // input/update gate
   0.02917215, -0.01399989, 0.11676068,  0.18115118, -0.02986906, 0.03235602,
   0.5051812 ,

  // cell state
   0.00328769, -0.0522958 , 0.3078437 ,  0.0916268 ,  0.00086583, 0.09845624,
  -0.5947338,

  // output gate
  -0.03956752, 0.06725086 , 0.02940571, -0.22776443,  0.06124537, 0.02526124,
   0.47375518
};

// Creating NeuralNetwork with pretrained Weights and Biases;
NeuralNetwork NN(layers, weights, biases, NumberOf(layers));


void getFeatures(){
  float dT[3];
  // Shift older temperatures
  inputs[0][0] = inputs[1][0]; // timestep 0, Feature 0: set raw temperature (Old reading)
  inputs[1][0] = inputs[2][0]; // timestep 1, Feature 0: set raw temperature (Old reading)
  inputs[2][0] = getTemp();    // timestep 2, Feature 0: get raw temperature (New reading) & ...
  
  Serial.print("Present:");     // Prints the actual/Present temperature
  Serial.println(inputs[2][0], 7); 

  // Feature 1: first derivative (rate of change)
  dT[0] = inputs[0][1] =  inputs[1][0] - inputs[0][0];        // forward diff
  dT[1] = inputs[1][1] = (inputs[2][0] - inputs[0][0]) / 2.0; // central diff
  dT[2] = inputs[2][1] =  inputs[2][0] - inputs[1][0];        // backward diff

  // Feature 2: second derivative (acceleration)
  inputs[0][2] =  dT[1] - dT[0];
  inputs[1][2] = (dT[2] - dT[0]) / 2.0;
  inputs[2][2] =  dT[2] - dT[1];
}


void setupTempSensor() {
  initTempSensor(); // Initialization of fake/pseudo-temperature-sensor 
  inputs[1][0] = getTemp(); delay(250); // get the 1st temperature & wait for the next one
  inputs[2][0] = getTemp(); delay(250); // get the 2nd temperature & wait for the next one
}


void setup(){
  Serial.begin(9600);
  while (!Serial){ }; // Wait for the Serial connection to be established 
  setupTempSensor();
  NN.print(); // Prints the weights & biases of each layer
}


void loop(){
  getFeatures(); // populates inputs[3][3] with: raw-temperature, rate-of-change & acceleration values
  for (unsigned int i = 0; i < 3; i++) // for each timestep (in our case it happens we have 3 at `getFeatures()`)
      output = NN.FeedForward(inputs[i]); // FeedForwards the input[i]-array through the NN  ->  predicts the *NEXT* temperature (based on the Present-temperature + the other getFeatures above) -> returns the predicted one/output
  Serial.print("Predicted:"); // Prints the Predicted next-temperature (7 digits after the comma) (returned via the above line-of-code)
  Serial.println(output[0], 7);
  delay(250); // ... wait for the next reading
}
