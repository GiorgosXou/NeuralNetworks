
[EXAMPLE_CUSTOM_FUNCTIONS_INO]: ./examples/Other/Custom_activation_function/Custom_activation_function.ino
[EXAMPLE_FEED_INDIVIDUAL_INO]: ./examples/Other/FeedForward_Individual_MNIST_PROGMEM/FeedForward_Individual_MNIST_PROGMEM.ino
[EXAMPLE_IN_EEPROM_INO]: ./examples/Media/FeedForward_from_internal_EEPROM/FeedForward_from_internal_EEPROM.ino
[EXAMPLE_DOUBLE_XOR_BACKPROP_INO]: ./examples/Basic/Backpropagation_double_Xor/Backpropagation_double_Xor.ino
[EXAMPLE_INT_QUANTIZED_XOR_INO]: ./examples/Other/Int_quantized_double_Xor_PROGMEM/Int_quantized_double_Xor_PROGMEM.ino
[EXAMPLE_DOUBLE_PRECISION]: ./examples/Other/Precision_for_8byte_double/Precision_for_8byte_double.ino


# Simple [MLP - NeuralNetwork](https://en.wikipedia.org/wiki/Multilayer_perceptron) Library For Microcontrollers 
Nothing "Import ant", just a simple library for implementing Neural-Networks(NNs) easily and effectively on any Arduino board and other microcontrollers.

# 📚 Summary
| NN<span>&nbsp;</span>Functions | Input<span>&nbsp;</span>Type<span>&nbsp;</span>(x)|Output<span>&nbsp;</span>Type<span>&nbsp;</span>(Y) |<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Action<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>|
| ------ | ------ | ------ | ------ |
| ```BackProp(x)```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| - | <details><summary>Trains the Neural-network</summary>"Tells" to the NN if the output was correct/the-expected/X-inputs and then, "teaches" it.</details>|
| ```*FeedForward(x)```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| <details><summary>Returns the output of it</summary>"Feeds" the NN with X-input values and returns Y-Output Values, If needed.</details>|
|```getMeanSqrdError(x)```| Unsigned Int| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference')| <details><summary> Returns the Mean Squared Error</summary> MSE, is SSE (Sum Squared Error) divided by the Product of number-οf-οutputs and inputs-per-epoch aka batch-size. </details>|

Understanding the Basics of a Neural Network:  
[```EXM```][EXAMPLE_DOUBLE_XOR_BACKPROP_INO] [```0```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) [```1```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi) [```2```](https://www.youtube.com/watch?v=L_PByyJ9g-I) [```3```](https://www.youtube.com/watch?v=H-ybCx8gt-8) [```4```](https://www.youtube.com/watch?v=I74ymkoNTnw) [```5```](https://towardsdatascience.com/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464) [```6```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ) [```7```](https://www.youtube.com/watch?v=An5z8lR8asY) [```8```](http://neuralnetworksanddeeplearning.com/chap1.html) [```9```](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/) [```10```](https://en.m.wikipedia.org/wiki/Backpropagation) [```11```](https://en.wikipedia.org/wiki/Activation_function)

# 📦 Features

- ##### ``` Current```
- - ```+``` Use of activation-functions per layer-to-layer.
- - ```+``` Optimizations based on [user's preference](#define-macro-properties). 
- - ```+``` Support for [custom activation functions](#define-custom-functions).
- - ```+``` [Basic ESP32-S3 SIMD acceleration.](https://github.com/GiorgosXou/NeuralNetworks/blob/5cd31c9a29853899c36b5ca7d0d8cf5e9cb3422e/src/NeuralNetwork.h#L1964-L1967 'Improving speed from ~ O(n^3) to O(n^2) in Feedforward')
- - ```+``` Both 16 and 8 bit, [int quantization](#int-quantization).
- - ```+``` MSE/BCE/CCE [loss-functions](#dfloat-loss-functions).
- - ```+``` Support for [double precision](#define-macro-properties).
- - ```+``` Many [activation-functions](#dfloat-activation-functions).
- - ```+``` [Use of storage medias.](## 'Such as SD, PROGMEM, EEPROM')
- - ```+``` [Exceptional solutions.](## 'eg. look at FeedForward_Individual')
- - ```+``` Simplicity!  
 

- ##### ```In the future, i want```
- - ```-``` [Your support.](#-donation 'yes, your support is a feature too xD')
- - ```-``` Better overall code.
- - ```-``` Other training methods.
- - ```-``` More Activation Functions.
- - ```-``` Training with int quantization.
- - ```-``` [Support for convolutional layers.](https://github.com/GiorgosXou/NeuralNetworks/issues/33)
- - ```-``` [Support for fixed-point arithmetics](https://github.com/GiorgosXou/NeuralNetworks/discussions/15).
- - ```-``` Different weight initialization methods.
- - ```-``` Support for external [EEPROM](https://en.wikipedia.org/wiki/EEPROM) and [FRAM](https://en.wikipedia.org/wiki/Ferroelectric_RAM).
- - ```-``` Even more properties, for many different needs.

# ✏️ Examples
***✨ ([See also](#-training)): training with Tensorflow section)***

- ***`🔤 Basic:`***
- - [Using a NN inside the loop](./examples/Basic/Run_In_Loop/Run_In_Loop.ino 'Run_In_Loop')
- - [Pre-trained NN behaving as a 3-input-xor circuit](./examples/Basic/FeedForward_double_Xor/FeedForward_double_Xor.ino 'FeedForward_double_Xor.ino')
- - [Training a NN to behave as a 3-input-xor circuit][EXAMPLE_DOUBLE_XOR_BACKPROP_INO]
- - [Training a NN to behave as a single xor-gate](./examples/Basic/Backpropagation_Single_Xor/Backpropagation_Single_Xor.ino 'Backpropagation_Single_Xor.ino')
- - [Using multiple Activ.-functions per layer-to-layer](./examples/Basic/Any_Activation_Function_Per_Layer/Any_Activation_Function_Per_Layer.ino 'Any_Activation_Function_Per_Layer.ino')
- - [Using multiple biases per layer-to-layer](./examples/Basic/Multiple_biases/Multiple_biases.ino 'Multiple_biases.ino')
- ***`💾 Media:`***
- - [Save NN into SD and load it into RAM after restart](./examples/Media/Save_load_NN_from_SD/Save_load_NN_from_SD.ino 'Save_load_NN_from_SD.ino')
- - [Saving a NN into the internal EEPROM for later use](./examples/Media/Save_NN_to_internal_EEPROM/Save_NN_to_internal_EEPROM.ino 'Save_NN_to_internal_EEPROM.ino')
- - [Running NN mostly via internal EEPROM (not RAM)][EXAMPLE_IN_EEPROM_INO]
- - [Running NN mostly via programmable memmory](./examples/Media/FeedForward_double_Xor_PROGMEM/FeedForward_double_Xor_PROGMEM.ino 'FeedForward_double_Xor_PROGMEM.ino')
- ***`🎲 Other:`***
- - [Pre-trained `int8_t`-quantized NN ✨][EXAMPLE_INT_QUANTIZED_XOR_INO]
- - [Using a custom function made by you][EXAMPLE_CUSTOM_FUNCTIONS_INO]
- - [Support for 8Byte "double" instead of "float"](./examples/Other/Precision_for_8byte_double/Precision_for_8byte_double.ino 'Precision_for_8byte_double ')
- - [Recognizing handwritten digits (MNIST) ✨][EXAMPLE_FEED_INDIVIDUAL_INO]


# ⚠️ Important
1. I am **NOT a professional** in any of those fields...
2. In case of error with 'POINTER_REGS' click [here](https://forum.arduino.cc/index.php?topic=613857.0)
3. `bias` means biases if [`MULTIPLE_BIASES_PER_LAYER`](#define-macro-properties) is enabled
4. Ensure you use (32-bit) floats during training unless you [`USE_64_BIT_DOUBLE`](#define-macro-properties).
5. <details><summary><b>And most important, destructor wont free last-layer's outputs!</b></summary><b>By design</b>, the destructor won't free\deallocate the last layer's outputs, allowing you to continue using <a href="https://github.com/GiorgosXou/NeuralNetworks/blob/9ffc36f6e897fe486e2d58ecf8d2cbb9848f71e9/examples/Basic/FeedForward_double_Xor/FeedForward_double_Xor.ino#L7">these outputs</a> through the pointer in your sketch. <b>To fully delete</b> the neural-network and free the associated resources, <b>it's your responsibility to:</b> either <code>delete[] outputs</code> <b>or</b> <code>delete[] NN.layers[NN.numberOflayers - 1].outputs;</code> <ins>at the end of the scope</ins>. <b>Additionally</b>, with <code>NN.load(file)</code>: ensure you deleted last-layer's <code>*outputs</code> in your sketch, in case you plan to re-use the same pointer for capturing the outputs of the newly-loaded-NN's feedforward.</details>


# 🔬 Tested on

<details><summary><strong>Arduino UNO</strong></summary>

- Don't [`USE_64_BIT_DOUBLE`](#define-macro-properties):  [`double` is the same as `float` on the UNO](https://www.arduino.cc/reference/en/language/variables/data-types/double/)</details>
<details><summary><strong>ESP32-C3</strong></summary>

- You may need to increase serial baud-rate from `9600` to `115200`
- Uses software-emulated EEPROM, so don't expect EEPROM-examples\functionalities to work on it </details>
<details><summary><strong>ATtiny85</strong></summary>

- `NN.print()` Function is disabled!
- Doesn't have [FPU](https://en.wikipedia.org/wiki/Floating-point_unit) that makes Maths on it, "difficult" for the [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory) (i think..?)
- If you want to use "Serial" on an ATtiny85 Click [Here](https://www.youtube.com/watch?v=9CX4i6rMXS) (Be Careful SoftwareSerial Uses A lot of [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory))
- [Backprop](https://en.m.wikipedia.org/wiki/Backpropagation) maths on an ATtiny85 won't work properly _(due to SRAM limitations, unless NN too small)_, though [Feed](https://en.wikipedia.org/wiki/Feed_forward_(control)) [Forword](https://en.wikipedia.org/wiki/Feedforward_neural_network) maths will Work! [...] <sup><sub>(since the first release I haven't tested it again on the ATtiny85 at least yet, so I am not 100% sure)</sub></sup>
</details>


<br>

# ⚙️ Functions, Variables  ...
Note that `DFLOAT` means `float`, unless you [`USE_64_BIT_DOUBLE`](#define-macro-properties), then it means `double`. `IDFLOAT` equals `DFLOAT` unless you [`USE_INT_QUANTIZATION`](#define-macro-properties), then it either means `int16_t` or `int8_t`. `IS_CONST` means nothing, unless you [`USE_PROGMEM`](#define-macro-properties), then it means `const`.

| (NN) Neural-Network's Constructors |
| ------ | 
|<details><summary>`NeuralNetwork()`</summary>Default Constructors</details>|
|<details><summary>`NeuralNetwork(String file)`</summary>Available if `#include <SD.h>`, lets you load NN from SD. Usefull\\**Important note:** moving it bellow `#include <NeuralNetwork.h>` will disable the support.</details>|
|<details><summary>`NeuralNetwork(unsigned int address)`</summary>Available if defined `_1_OPTIMIZE 0B10000000`-*(`USE_INTERNAL_EEPROM`)*</details>|
|<details><summary>`NeuralNetwork(*layer_, &NumberOflayers, *_ActFunctionPerLayer)`</summary>Available if backpropagation is available (`! NO_BACKPROP`)</details>|
|<details><summary>`NeuralNetwork(*layer_, &NumberOflayers, &LRw, &LRb, *_ActFunctionPerLayer)`</summary>Available if backpropagation is available (`! NO_BACKPROP`)</details>|
|<details><summary>`NeuralNetwork(*layer_, *default_Weights, &NumberOflayers, *_ActFunctionPerLayer)`</summary>Available if [`NO_BIAS`](#define-macro-properties) enabled</details>|
|<details><summary>`NeuralNetwork(*layer_, *default_Weights, *default_Bias, &NumberOflayers, *_ActFunctionPerLayer)`</summary>(:</details>|

```c++
 IS_CONST IDFLOAT *default_Bias
 IS_CONST IDFLOAT *default_Weights
 byte *_ActFunctionPerLayer = NULL
 const unsigned int *layer_
 const unsigned int &NumberOflayers
 const DFLOAT &LRw
 const DFLOAT &LRb
```

<br>


##  ```Type``` Main Functions
| NN Functions | Input<span>&nbsp;</span>Type<span>&nbsp;</span>(x)|Output<span>&nbsp;</span>Type<span>&nbsp;</span>(Y) |<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Action<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>| 
| ------ | ------ | ------ | ------ |
|`FeedForward_Individual(x)`|[DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference')| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array|<details><summary>RAM Optimized FeedForward</summary>"Feeds" the NN with each one X-input Individually until it returns Y-Output Values, If needed. **Important note:** You can't train with it. <br><sup>(Almost no RAM usage for input layer, see also: [example][EXAMPLE_FEED_INDIVIDUAL_INO])</sup></details>|
| ```*FeedForward(x) ```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| <details><summary>Returns the output of the NN</summary>"Feeds" the NN with X-input values and returns Y-Output Values, If needed.</details>|
| ```BackProp(x) ```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| - | <details><summary>Trains the NN</summary>"Tells" to the NN if the output was correct/the-expected/X-inputs and then, "teaches" it.</details>|
|`load(x)`| String|bool| <details><summary>Loads NN from SD</summary>Available if `#include <SD.h>`. Usefull\\**Important note:** moving it bellow `#include <NeuralNetwork.h>` will disable the support.</details>|
|`save(x)`| String \ int|bool \ int| <details><summary>Saves NN to storage media</summary> SD or internal-EEPROM</details>|
|`print()`| - |String| <details><summary>Prints the specs of the NN</summary> _(If [_1_OPTIMIZE 0B10000000](#define-macro-properties) prints from PROGMEM)_</details>|

<br>

## ```DFLOAT``` Loss Functions
No need for ```#define MEAN_SQUARED_ERROR```, MSE is the default loss and it is always enabled.  The only case in which you will also need to define the MSE in your sketch, is only if you want to use it in relation with another loss-function. To use any other loss-function except from MSE just define it as seen below. 
| Loss Functions | Enabling MACRO |
| ------ | ------ | 
|NN.```getMeanSqrdError```(```unsigned int batch_size```)| ```#define MEAN_SQUARED_ERROR``` |
|NN.```getBinaryCrossEntropy```(```unsigned int batch_size```)| ```#define BINARY_CROSS_ENTROPY```|
|NN.```getCategoricalCrossEntropy```(```unsigned int batch_size```)| ```#define CATEGORICAL_CROSS_ENTROPY```|


<br>

## ```DFLOAT``` Loss Variables
To use any of the variables below,  you first need to ```#define```  a loss function as said above too.
| Loss variables | Sum variables |
| ------ | ------ | 
|NN.MeanSqrdError| NN.sumSquaredError|
|NN.BinaryCrossEntropy| NN.sumOfBinaryCrossEntropy
|NN.CategoricalCrossEntropy| NN.sumOfCategoricalCrossEntropy|


<br>

##  ```DFLOAT``` Activation Functions
Due to *(my uncertainty and)* the strict RAM optimization that allows the library to use one array that stores only the values after the activation instead of two arrays storing values before and after the activation, the use of some derivative functions in backpropagation are not supported by this library at this moment, as also seen by the MACRO ```NO_BACKPROP``` below. This means that if you want to use and  ```#define``` any function from 8-13 under the section *"```NO_BACKPROP``` support"* , you won't be able to use backpropagation.

||  <span>&nbsp;&nbsp;</span>Enabling<span>&nbsp;</span>MACRO<span>&nbsp;&nbsp;&nbsp;&nbsp;</span>| <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Activation<span>&nbsp;</span>Functions<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>|  <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Returns<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span> |
| :------: | ------ | ------ | ------ |
|**0**|```#define Sigmoid```   |<sup><sub>NN.layers-></sub></sup>```Sigmoid(&x)```  |  ```1/(1+e^(-x))``` |
|**1**|```#define Tanh```      |<sup><sub>NN.layers-></sub></sup>```Tanh(&x)```     |  ```(e^(2*x)-1)/(e^(2*x)+1)``` |
|**2**|```#define ReLU```      |<sup><sub>NN.layers-></sub></sup>```ReLU(&x)```     |  ```(x>0)?x:0``` |
|**3**|```#define LeakyELU```  |<sup><sub>NN.layers-></sub></sup>```LeakyELU(&x)``` |  ```(x>0)?x:AlphaLeaky*x``` |
|**4**|```#define ELU```       |<sup><sub>NN.layers-></sub></sup>```ELU(&x)```      |  ```(x>0)?x:AlphaELU*(e^(x)-1)``` |
|**5**|```#define SELU```      |<sup><sub>NN.layers-></sub></sup>```SELU(&x)```     |  ```(x>0)?x:AlphaSELU*(e^(x)-1)``` |
|**6**|```#define Softmax```   |<sup><sub>NN.layers-></sub></sup>```Softmax(&x)```| ```void``` "complicated implementation" |
|**7**|```#define Identity```  |<sup><sub>NN.layers-></sub></sup>```Identity(&x)```|  ```x``` |
||| <center>**```NO_BACKPROP``` SUPPORT**</center> | |
|**8**|```#define BinaryStep```|<sup><sub>NN.layers-></sub></sup>```BinaryStep(&x)```|  ```(x <  0) ?  0  :  1``` |
|**9**|```#define Softplus```  |<sup><sub>NN.layers-></sub></sup>```Softplus(&x)```|  ```log(1  +  exp(x))``` |
|**10**|```#define SiLU```     |<sup><sub>NN.layers-></sub></sup>```SiLU(&x)```|  ```x / (1  +  exp(-x))``` |
|**11**|```#define GELU```     |<sup><sub>NN.layers-></sub></sup>```GELU(&x)```|  ```(1/2) * x * (1  +  erf(x /  sqrt(x)))``` |
|**12**|```#define Mish```     |<sup><sub>NN.layers-></sub></sup>```Mish(&x)```|  ```x *  Tanh(log(1  +  exp(x)))``` |
|**13**|```#define Gaussian``` |<sup><sub>NN.layers-></sub></sup>```Gaussian(&x)```|  ```exp(-(x*x))``` |
||| <center>**Derivative Functions**</center> | |
|**0**|```#define Sigmoid```   |<sup><sub>NN.layers-></sub></sup>```SigmoidDer(&fx)``` |  ```fx-fx*fx``` |
|**1**|```#define Tanh```      |<sup><sub>NN.layers-></sub></sup>```TanhDer(&fx)```|  ```1-fx*fx``` |
|**2**|```#define ReLU```      |<sup><sub>NN.layers-></sub></sup>```ReLUDer(&fx)```|  ```(fx>0)?1:0``` |
|**3**|```#define LeakyELU```  |<sup><sub>NN.layers-></sub></sup>```LeakyELUDer(&fx)```|  ```(fx>0)?1:AlphaLeaky``` |
|**4**|```#define ELU```       |<sup><sub>NN.layers-></sub></sup>```ELUDer(&fx)```|  ```(fx>0)?1:fx+AlphaELU``` |
|**5**|```#define SELU```      |<sup><sub>NN.layers-></sub></sup>```SELUDer(&fx)```|  ```(fx>0)?LamdaSELU:fx+AlphaSELU*LamdaSELU``` |
|**6**|```#define Softmax```   |<sup><sub>NN.layers-></sub></sup>```SoftmaxDer(&fx)```|  ```fx * (1  - fx)``` |
|**7**|```#define Identity```  |<sup><sub>NN.layers-></sub></sup>```IdentityDer(&x)```|  ```x``` |

<br>

if you want to use other activation function from the default one, just define one other:
```c++
#define Sigmoid //[default] No need definition, for single activation across network
#define Tanh
#define ReLU
#define LeakyELU
#define ELU
#define SELU
...
```

Use any activation function per layer-to-layer, like :
```c++
#define ACTIVATION__PER_LAYER
#include <NeuralNetwork.h>

unsigned int layers[] = {3, 4, ..., 2, 1};
byte Actv_Functions[] = {   1, ..., 2, 0};

// Tanh > ... > ReLU > Sigmoid
```
If you want to drastically reduce ROM & slightly RAM size you can Define which Functions to use/compile, like:
```c++
#define ACTIVATION__PER_LAYER
        #define Sigmoid // 0
        //#define Tanh
        //#define ReLU
        //#define LeakyELU
        #define ELU     // 1
        #define SELU    // 2
        ...
#include <NeuralNetwork.h>

unsigned int layers[] = {3, 4, ..., 2, 1};
byte Actv_Functions[] = {   1, ..., 2, 0};

// ELU > ... > SELU > Sigmoid
```
<sup>⚠️ have in mind that because I used f(x) for derivatives there might be chances of mistakes  (?)</sup>

<br>

##  `#define` Custom Functions
*([See also example][EXAMPLE_CUSTOM_FUNCTIONS_INO])* You can define up to 5. Every custom function, comes after every each non-custom one *(numerically)* eg:
```c++
#define ACTIVATION__PER_LAYER
        #define Sigmoid // 0
        //#define Tanh
        //#define ReLU
        //#define LeakyELU
        #define ELU  // 1
        #define SELU // 2
        #define CUSTOM_AF1 my_act_fun1 // 3
        #define CUSTOM_AF2 my_act_fun2 // 4
        ...
```
Define derivative-functions, by just definening `..._DFX`:
```c++
        #define CUSTOM_AF1 my_act_fun1 
        #define CUSTOM_DF1 
```
And then use them in your sketch like:
```c++
// CUSTOM_DF1 is optional ...
#define ACTIVATION__PER_LAYER
        #define Tanh
        #define CUSTOM_AF1 my_sigmoid 
        #define CUSTOM_DF1

#include <NeuralNetwork.h>

// derivative function must end in "Der" | Limited to f(x), for optimization reasons
float NeuralNetwork::Layer::my_sigmoidDer(const float &fx){ return fx - fx * fx;      } 
float NeuralNetwork::Layer::my_sigmoid   (const float &x ){ return 1 / (1 + exp(-x)); }


unsigned int layers[] = {3, 4, ..., 2, 1};
byte Actv_Functions[] = {   0, ..., 0, 1};

// Tanh > ... > Tanh > my_sigmoid
```
**IMPORTANT NOTE:** Be careful commenting in front of `#define`, see issue #29



<br>

##  ```DFLOAT``` Variables Of Activation Functions 
| Enabling MACRO | Activation Variables| Default | Explenation|
|    ------   | ------ | ------ | ------ |
|```#define LeakyELU```|NN.AlphaLeaky| 0.01   | the α of Leaky |
|```#define ELU```     |NN.AlphaELU  | 1      | the α of ELU   |
|```#define SELU```    |NN.AlphaSELU | 1.6733 | the α of SELU  |
|```#define SELU```    |NN.LamdaSELU | 1.0507 | the λ of SELU  |

<br>

## ```Type``` Other Variables
**Note** that except from `_numberOfInputs` and `_numberOfOutputs` everything else is not valid when you [`USE_INTERNAL_EEPROM`](#define-macro-properties)

| Type | NN's Variables | Explenation|
| ------ | ------ | ------ |
|```byte*```      |NN.```ActFunctionPerLayer``` |if ```ACTIVATION__PER_LAYER``` defined|
|```DFLOAT```       |NN.```LearningRateOfWeights```|The Learning-Rate-Of-Weights |
|```DFLOAT```       |NN.```LearningRateOfBiases```| The Learning-Rate-Of-Biases|
|```IDFLOAT*```      |NN.```weights```|If [REDUCE_RAM_WEIGHTS_LVL2](#define-macro-properties)|
|```Layer*```      |NN.```layers``` | Layers of NN|
||<center>**Layer's Variables**</center>||
|```IDFLOAT*```      |NN.layers[i].```bias```| <details><summary>The bias of an individual layer[i], unless...</summary>[`NO_BIAS` or `MULTIPLE_BIASES_PER_LAYER`](#define-macro-properties) is enabled.</details>|
|```DFLOAT*```      |NN.layers[i].```outputs```[]| The Output array of an individual layer[i]|
|```IDFLOAT**```     |NN.layers[i].```weights```[][]|if not [REDUCE_RAM_WEIGHTS_LVL2](#define-macro-properties)|
|```DFLOAT*```      |NN.layers[i].```preLgamma```[]| The γ-error of previous layer[i-1] |
|```unsigned int```|NN.layers[i].```_numberOfInputs```| The Layer[i]'s Number Of inputs\nodes|
|```unsigned int```|NN.layers[i].```_numberOfOutputs```| The number-Of-Outputs for an individual layer[i]|

<br>

## ```#define``` MACRO Properties

```c++
#define _1_OPTIMIZE 0B00000000
```

|  _1_OPTIMIZE | | Action |  Keyword |
| :------: | :------: | ------ | ------ | 
| ```0B00000000``` | |   Nothing | |
| ```0B10000000``` |<sup><sub>⚠️</sub></sup>|<details><summary>Use PROGMEM instead of RAM</summary>Enables the use of programmable-memmory instead of RAM, to store and use weights and biases</details>|<sub><sup>`USE_PROGMEM`</sup></sub>|
| ```0B01000000``` |<sup><sub>⚠️📌</sub></sup>| <details><summary>Deletes previous layer's Outputs</summary>**Highly-Recommended** because: for each layer-to-layer input-to-ouput operation of internal feedforward, it deletes the previous layer's outputs. **Important note:** in case you want to `delete[] NN->layers[NN->numberOflayers - 1].outputs;` make sure afterwards to `...outputs = NULL` *(if you plan to `feedforward` again later in your sketch)*. Reducing RAM by a factor of ((the_sum_of_each_layer'_s **\_numberOfOutputs**) - (**\_numberOfOutputs** of_biggest_layer) *(4[float] or 8[double])Bytes )  <sub><sup>approximately i think ?</sub></sup></details>|<sub><sup>`REDUCE_RAM_DELETE_OUTPUTS`</sup></sub>|
| ```0B00100000``` |<sup><sub>❌</sub></sup>| <details><summary>Reduces RAM for Weights, level 1</summary>*(Partially reduce)* Not yet implimented</details>| <sub><sup>`REDUCE_RAM_WEIGHTS_LVL1`</sup></sub>|
| ```0B00010000``` |<sup><sub>📌</sub></sup>| <details><summary>Reduces RAM for Weights, level 2 </summary> by a factor of (number_of_layers-1)*[2](## 'Size of a pointer (two bytes in the arduino)') Bytes</details>|<sub><sup>`REDUCE_RAM_WEIGHTS_LVL2`</sup></sub>|  
| ```0B00001000``` |<sup><sub>🟢</sub></sup>| <details><summary>Deletes previous layer's Gamma</summary>Always enabled **<sub><sup>(not switchable yet.)</sup></sub>**</details>|<sub><sup>`REDUCE_RAM_..._LAYER_GAMMA`</sup></sub>| 
| ```0B00000100``` |<sup><sub>ⓘ</sub></sup> |<details><summary>Reduces RAM using static reference</summary>... to the NN-object (for layers) \| by a factor of [2](## 'Size of a pointer (two bytes in the arduino)')*(number_of_layers - 1 or 2)bytes. _(With this optimization)_ Note that, when you are using multiple NN-**objects** interchangeably in your sketch, you should either update `NN.me` manually before using the next one like `NN.me = &NN2` or just use `_2_OPTIMIZE 0B00000010` instead</details>|<sub><sup>`REDUCE_RAM_STATIC_REFERENCE`</sup></sub>|
| ```0B00000010``` |<sup><sub>📌</sub></sup>|<details><summary>Disables MSE function</summary>Disables the default loss function \| Reduces ROM, RAM & CPU consumption, althought usually needed for backpropagation</details> |<sub><sup>`DISABLE_MSE`</sup></sub>|
| ```0B00000001``` |<sup><sub>ⓘ</sub></sup>|<details><summary>Use 8-Byte double instead of float</summary>This will work only if your MCU supports 8byte doubles eg. Arduino UNO DOESN'T *([see also example][EXAMPLE_DOUBLE_PRECISION])*</details>  |<sub><sup>`USE_64_BIT_DOUBLE`</sup></sub>|
|  **_2_OPTIMIZE** | |  ||
| ```0B10000000```  |<sup><sub>⚠️</sub></sup>|<details><summary>Use<span>&nbsp;</span>internal<span>&nbsp;</span>EEPROM<span>&nbsp;</span>instead<span>&nbsp;</span>of<span>&nbsp;</span>RAM</summary>Weights, biases, and activation functions stored-into and used-from the internal EEPROM of the MCU. Additionally, this means `REDUCE_RAM_WEIGHTS_LVLX` has no effect. see also: [example][EXAMPLE_IN_EEPROM_INO]</details> |<sub><sup>`USE_INTERNAL_EEPROM`</sup></sub>|
| ```0B01000000```  |<sup><sub></sub></sup>|<details><summary>Use NN without biases</summary>It disables the use of biases in the entire NN</details> |<sub><sup>`NO_BIAS`</sup></sub>|
| ```0B00100000```  |<sup><sub></sub></sup>|<details><summary>Use more than 1 bias, layer-to-layer</summary>Enables the use of a unique bias for each unit\\neuron of each layer-to-layer</details> |<sub><sup>`MULTIPLE_BIASES_PER_LAYER`</sup></sub>|
| ```0B00010000```  |<sup><sub></sub></sup>|<details><summary>Use [F() macro](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/#:~:text=about%20myself.%5Cn%22-,The%20F()%20macro,-When%20an%20instruction) for print function</summary>`Serial.print(...)` strings, normally saved in RAM. This ensures strings are stored in PROGMEM *(At least for Arduino boards)*</details> |<sub><sup>`MULTIPLE_BIASES_PER_LAYER`</sup></sub>|
| ```0B00001000```  |<sup><sub>📌</sub></sup>|<details><summary>Use `int16_t` quantization</summary> Weights and biases are stored as `int16_t` *(2-bytes each)*. During the proccess of feedforward each individual weight or bias: temporarily converts back to it's equivalent float [...] Reduces memmory-footprint by a factor of half the size of the "equivalent" `float` weights and biases. Slightly CPU intensive. *(**See also:** [Training > int-quantization + details](#int-quantization))*</details> |<sub><sup>`USE_INT_QUANTIZATION`</sup></sub>|
| ```0B00000100```  |<sup><sub></sub></sup>|<details><summary>Use `int8_t ` quantization</summary>Weights and biases are stored as `int8_t` *(1-byte each)*. During the proccess of feedforward each individual weight or bias: temporarily converts back to it's equivalent float [...] Reduces memmory-footprint by a factor of half the size of the "equivalent" `int16_t` weights and biases. Slightly CPU intensive. *(**See also:** [Training > int-quantization + details](#int-quantization))*</details> |<sub><sup>`USE_INT_QUANTIZATION`</sup></sub>|
| ```0B00000010```  |<sup><sub></sub></sup>|<details><summary><sub><sup>`REDUCE_RAM_STATIC_REFERENCE`</sup></sub> for multiple NN </summary>It does the same thing as `REDUCE_RAM_STATIC_REFERENCE` but for multiple NN objects *(instead for just one)*. If you use `FeedForward_Individual` It is recommended to fallback to the original `_1_OPTIMIZE 0B00000100` and manually change `NN.me`</details> |<sub><sup>`...FOR_MULTIPLE_NN_OBJECTS`</sup></sub>|
| ```0B00000001```  |<sup><sub>⚠️</sub></sup>|<details><summary>Disables backpropagation</summary>Disabling backpropagation when it's not automatically disabled, helps reduce the size of your sketch.</details> |<sub><sup>`NO_BACKPROP`<sup></sub>|
  

<br>

Don't use keywords to define optimizations, it won't work, use _X_OPTIMIZE
- ⚠️ = Backpropagation is not allowed
- 🟢 = Always enabled <sub><sup>(not switchable yet.)</sup></sub>
- ❌ = Not yet implimented
- 📌 = Recommended

<br>


# 👨‍💻 Training
To train a neural-network, you can use Tensorflow to do so. Here's a basic python example:

```python
# pip install tensorflow
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import LearningRateScheduler
import tensorflow as tf
import numpy as np


# Define if you want to use biases
IS_BIASED = True

# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')

# Define the XOR gate inputs and outputs
inputs  = np.array([
    [ 0, 0, 0 ], 
    [ 0, 0, 1 ], 
    [ 0, 1, 0 ], 
    [ 0, 1, 1 ], 
    [ 1, 0, 0 ], 
    [ 1, 0, 1 ], 
    [ 1, 1, 0 ], 
    [ 1, 1, 1 ]
], dtype = np.float32)
outputs = np.array([[0], [1], [1], [0], [1], [0], [0], [1]], dtype = np.float32)
input_size = 3

# Create a simple convolutional neural network
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(input_size,)), # Input layer (no bias) 
    tf.keras.layers.Dense(3, activation='sigmoid', use_bias=IS_BIASED), # Dense  3 units 
    tf.keras.layers.Dense(1, activation='sigmoid', use_bias=IS_BIASED)  # Output 1 unit 
])

# Compile the model
optimizer = Adam(learning_rate=0.031)
model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(inputs, outputs, epochs=900, verbose=0)

# Evaluate the model on the training data
loss, accuracy = model.evaluate(inputs, outputs)
print(f"Model accuracy: {accuracy * 100:.2f}%")

# Predict XOR gate outputs
predictions = model.predict(inputs)
print("Predictions:")
for i in range(len(inputs)):
    print(f"Input: {inputs[i]}, Predicted Output: {predictions[i][0]:.7f}")

# Print biases and weights
# (IMPORTANT NOTE! they are printed as w[i][j] not w[j][i] | outputs * inputs)
print()
weights_biases = model.get_weights()

print("#define _1_OPTIMIZE 0B01000000 // Highly-Recommended Optimization For RAM")
if IS_BIASED:
    print("#define _2_OPTIMIZE 0B00100000 // MULTIPLE_BIASES_PER_LAYER \n")
    print('float biases[] = {')
    for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
        print('  ', end='')
        for j in range(0, w.shape[1]):
            print(b[j], end=', ')
        print()
    print('};\n')
else:
    print("#define _2_OPTIMIZE 0B01000000 // NO_BIAS \n")

print('float weights[] = {', end="")
for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
    print()
    for j in range(0, w.shape[1]):
        print('  ', end='')
        for i in range(0, w.shape[0]):
            print(w[i][j], end=', ')
        print()
print('};\n')
```

### Int quantization

 Assuming you already have either enabled [`int16_t`](#define-macro-properties '#define _2_OPTIMIZE 0B00001000') or [`int8_t`](#define-macro-properties '#define _2_OPTIMIZE 0B00000100')... before proceeding with the example, you should know that the default range of weights *(that maps floats to ints)* , is set to `200.0` for `int16_t` and `51.0` for `int8_t` via this simple formula:
```cpp
// FLOAT RANGE FOR INT16 = (100.0) - (-100.0) = 200.0 | MAX - MIN
// FLOAT RANGE FOR INT8  = ( 25.5) - (- 25.5) =  51.0 | MAX - MIN
```

You can change that by defining your own value in your sketch, like:
```cpp
#define Q_FLOAT_RANGE 40.0 // (20.0) - (-20.0) = 40.0 | Ensure you used a dot!
```

<details><summary>Now click here to see the full <b>int-quantization training example</b></summary>

```python
# pip install tensorflow
from tensorflow.keras.optimizers import Adam
import tensorflow as tf
import numpy as np


IS_BIASED  = True      # Define if you want to use biases
IS_PROGMEM = True      # Use PROGMEM or not
INT_RANGE  = 65535     # Range of int16_t -32768 to 32767 | for int8_t use 255 
FP__RANGE  = 200.0     # Range of weights -100   to 100   | for int8_t use 51
TYPE_NAME  = 'int16_t' # or 'int8_t'


def quantize_float32_to_int(w):
    S = (FP__RANGE) / (INT_RANGE)
    return round(w / S) # + Z

def int_to_float32(q):
    return np.float32(np.float32(FP__RANGE) / (INT_RANGE)) * np.float32(q)


# Enable 32-bit floating-point precision
tf.keras.backend.set_floatx('float32')

# Define the XOR gate inputs and outputs
inputs = np.array([
    [0, 0, 0], 
    [0, 0, 1], 
    [0, 1, 0], 
    [0, 1, 1], 
    [1, 0, 0], 
    [1, 0, 1], 
    [1, 1, 0], 
    [1, 1, 1]
], dtype=np.float32)
outputs = np.array([[0], [1], [1], [0], [1], [0], [0], [1]], dtype=np.float32)
input_size = 3

# Create a simple convolutional neural network
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(input_size,)),  # Input layer (no bias)
    tf.keras.layers.Dense(3, activation='sigmoid', use_bias=IS_BIASED),  # Dense 3 units
    tf.keras.layers.Dense(1, activation='sigmoid', use_bias=IS_BIASED)  # Output 1 unit
])

# Compile the model
optimizer = Adam(learning_rate=0.031)
model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(inputs, outputs, epochs=1000, verbose=0)

# Evaluate the model on the training data
loss, accuracy = model.evaluate(inputs, outputs)
print(f"original Model accuracy: {accuracy * 100:.2f}%")

weights_biases = model.get_weights()

if IS_PROGMEM:
    print("\n#define _1_OPTIMIZE 0B11000000 // PROGMEM + Highly-Recommended Optimization For RAM")
else:
    print("\n#define _1_OPTIMIZE 0B01000000 // Highly-Recommended Optimization For RAM")

# Quantize float32 biases to intX_t, print and then back to float32
# (IMPORTANT NOTE! they are printed as w[i][j] not w[j][i] | outputs * inputs)
if IS_BIASED:
    if TYPE_NAME == 'int16_t':
        print("#define _2_OPTIMIZE 0B00101000 // MULTIPLE_BIASES_PER_LAYER + int16_t quantization \n")
    else:
        print("#define _2_OPTIMIZE 0B00100100 // MULTIPLE_BIASES_PER_LAYER + int8_t quantization \n")
    print(('const PROGMEM ' if IS_PROGMEM else '') + TYPE_NAME + ' biases[] = {')
    for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
        print('  ', end='')
        for j in range(0, w.shape[1]):
            print(quantize_float32_to_int(b[j]), end=', ')
            b[j] = int_to_float32(quantize_float32_to_int(b[j]))
        print()
    print('};\n')
else:
    if TYPE_NAME == 'int16_t':
        print("#define _2_OPTIMIZE 0B01001000 // NO_BIAS + int16_t quantization \n")
    else:
        print("#define _2_OPTIMIZE 0B01000100 // NO_BIAS + int8_t quantization \n")

# Quantize float32 weights to intX_t, print and then back to float32
print(('const PROGMEM ' if IS_PROGMEM else '') + TYPE_NAME + ' weights[] = {', end="")
for l, (w, b) in enumerate(zip(weights_biases[::2], weights_biases[1::2])):
    print()
    for j in range(0, w.shape[1]):
        print('  ', end='')
        for i in range(0, w.shape[0]):
            print(quantize_float32_to_int(w[i][j]), end=', ')
            w[i][j] = int_to_float32(quantize_float32_to_int(w[i][j]))
        print()
print('};\n')

# Load quantized weights for NN evaluation
model.set_weights(weights_biases)

# Evaluate the model on the training data
loss, accuracy = model.evaluate(inputs, outputs)
print(f"{TYPE_NAME} Model accuracy: {accuracy * 100:.2f}%")

# Print predictions
print(f"{TYPE_NAME} Predictions:")
predictions = model.predict(inputs)
for i in range(len(inputs)):
    print(f"Input: {inputs[i]}, Predicted Output: {predictions[i][0]:.7f}")
```

*([See also: pretrained-quantized-ino-example][EXAMPLE_INT_QUANTIZED_XOR_INO])*

</details>



<br>


**IMPORTANT NOTE:** See how weights and biases are printed at the end of the script and make sure you have *(on top of your sketch)* enabled\\defined `_2_OPTIMIZE 0B00100000 // MULTIPLE_BIASES_PER_LAYER` or `_2_OPTIMIZE 0B01000000 // NO_BIAS ` depending on your needs of use. Additionally, if you want to use just 1 bias per layer-to-layer don't use any of those 2 optimizations *(Althought, just so you know... Tensorflow doesn't seem to support 1 bias per layer-to-layer)*. **Finally** make sure to use `float32` unless your MCU is compatible and you want to `USE_64_BIT_DOUBLE`-optimization

*([see also examples](#✏️-examples) on how to train a NN directly on an MCU)* 

<br>


## A HUGE THANK YOU!
I want to **really thanks** [Underpower Jet](https://www.youtube.com/channel/UCWbkocGpP_8R5ZS1VpuusRA) for his amazing [tutorial](https://www.youtube.com/watch?v=L_PByyJ9g-I), by bringing it more to the surface. Because after all the videos and links I came across, he was the one that made the most significant difference to my understanding of backpropagation in neural networks. Plus, I would like to thanks: [giant_neural_network](https://www.youtube.com/channel/UCrBzGHKmGDcwLFnQGHJ3XYg) for [this](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) and [this](https://www.youtube.com/watch?v=vF0zqCkbsEU&t=12s), [ 3Blue1Brown](https://www.youtube.com/channel/UCYO_jab_esuFRV4b17AJtAw) for [this](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi), the authors of **[✨ this](https://www.researchgate.net/publication/353753323_Evaluation_of_a_wireless_low-energy_mote_with_fuzzy_algorithms_and_neural_networks_for_remote_environmental_monitoring)** scientific article for referencing me, Ivo Ljubičić for using my library for his [✨ master thesis](https://repozitorij.fsb.unizg.hr/en/islandora/object/fsb%3A5928), Arduino community and everyone else who gave me the oportunity to learn and make this library possible to exist [...] 


# 🌐 Research
Here most of the resources I came across the internet, I recomend you to have a look if you want to _(but please stay aware of the fact that for some of those sites, I had only opened them checked something and then closed them in a matter of seconds [so, please don't get them all seriously])_


**```22\11\2023```** 
* **```Code Related:```**
* * [Handy C++ "cheat sheet"](https://en.cppreference.com/w/cpp/keyword '2024-03-13 04:08:32 PM reserved c++ keywords')
* * _**```Macros:```**_
* * * Do not put comments in front of #define whatever
* * * [is #ifdef \_\_SD\_H\_\_ considered a bad practice?](https://arduino.stackexchange.com/questions/94743/is-ifdef-sd-h-considered-a-bad-practice '2023-11-22 12:32:04 AM')
* * * [C++11-style \[\[unused\]\] attribute in gcc?](https://stackoverflow.com/questions/31909631/c11-style-unused-attribute-in-gcc '2023-11-22 12:38:06 AM')
* * * [comments in c macro definition](https://stackoverflow.com/questions/30133528/comments-in-c-macro-definition '2023-11-22 12:41:41 AM')
* * * [Using #undef before #define](https://stackoverflow.com/questions/28136208/using-undef-before-define/28136246#28136246 '2023-11-22 12:39:22 AM')
* * _**```Arduino:```**_ 
* * * _**```StackOverflow:```**_
* * * * [PROGMEM : pgm_read_float_near() equivalent for double? (Arduino Due)](https://arduino.stackexchange.com/a/94783/77085 '2023-11-22 12:35:08 AM')
* * * * [warning: inline variables are only available with ‘-std=c++17’ or ‘-std=gnu++17’ how to suppress it? \[closed\]](https://stackoverflow.com/questions/72181312/warning-inline-variables-are-only-available-with-std-c17-or-std-gnu17 '2023-11-22 12:40:45 AM')
* **```Neural Network Related```**
* * _**```General:```**_
* * * [Large values of weights in neural network](https://stackoverflow.com/questions/43253009/large-values-of-weights-in-neural-network '2023-11-30 03:25:35 PM')

<br>

**```12\08\2021```** 
* **```Neural Network Related```**
* *  _**``` Videos:```**_
* * * [How convolutional neural networks work, in depth](https://www.youtube.com/watch?v=JB8T_zN7ZC0)
* * * [How to use the loss function categorical crossentropy](https://www.youtube.com/watch?v=VM6FDop_uOg)
* * * [Tutorial 4: How to train Neural Network with BackPropogation](https://www.youtube.com/watch?v=mH9GBJ6og5A)
* * * [Neural Networks Part 8: Image Classification with Convolutional Neural Networks](https://www.youtube.com/watch?v=HGwBXDKFk9I)	
* * _**```Softmax:```**_
* * * [The Softmax : Data Science Basics](https://www.youtube.com/watch?v=8ps_JEW42xs)
* * * [Softmax Function in Deep Learning](https://www.youtube.com/watch?v=EuZZ6plg2Tk)
* * * [The SoftMax Derivative, Step-by-Step!!!](https://www.youtube.com/watch?v=M59JElEPgIg)
* * * [Derivative of Sigmoid and Softmax Explained Visually](https://www.youtube.com/watch?v=gRr2Q97XS2g)
* * * [Softmax and Cross Entropy Gradients for Backpropagation](https://www.youtube.com/watch?v=5-rVLSc2XdE)
* * _**```StackOverflow\Exchange:```**_
* * * [What is batch size in neural network?](https://stats.stackexchange.com/questions/153531)
* * * [how to do weight clipping after gradient updates?](https://stackoverflow.com/questions/42264567)
* * * [Cost function turning into nan after a certain number of iterations](https://stats.stackexchange.com/questions/325451)
* * * [Why use softmax only in the output layer and not in hidden layers?](https://stackoverflow.com/questions/37588632)
* * * [Why is step function not used in activation functions in machine learning?](https://stats.stackexchange.com/questions/271701)
* * * [if softmax is used as an activation function for output layer, must the number of nodes in the last hidden layer equal the number of output nodes?](https://stats.stackexchange.com/questions/281887/if-softmax-is-used-as-an-activation-function-for-output-layer-must-the-number-o)
* * _**```General:```**_
* * * [Is Sigmoid the only activation function compatible with the binary crossentropy loss function](https://peltarion.com/knowledge-center/documentation/modeling-view/build-an-ai-model/loss-functions/binary-crossentropy#:~:text=Sigmoid%20is%20the%20only%20activation%20function%20compatible%20with%20the%20binary%20crossentropy%20loss%20function.%20You%20must%20use%20it%20on%20the%20last%20block%20before%20the%20target%20block.)
* * * [Understanding binary cross-entropy / log loss: a visual explanation](https://towardsdatascience.com/understanding-binary-cross-entropy-log-loss-a-visual-explanation-a3ac6025181a)
* * * [Understanding RMSprop](https://towardsdatascience.com/understanding-rmsprop-faster-neural-network-learning-62e116fcf29a)
* * * [MLP_C Arduino Library](https://github.com/benjamin-henry/MLP_C)
* **```Code Related:```**
* * _**```Tools:```**_
* * * [Compiler Explorer](https://godbolt.org/)
* * _**```Macros:```**_
* * * [3.7.1 Standard Predefined Macros](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros)
* * * [Diagnostic Pragmas](https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html)
* * * [PREPROCESSOR DIRECTIVES 2](https://www.tenouk.com/Module10a.html)
* * _**```Arduino:```**_ 
* * * _**```StackOverflow:```**_
* * * * [Why there's no erf() function in Arduino's math.h library?](https://stackoverflow.com/questions/68720871/)
* * * * [How to Serial.println text and variable's values in the same line](https://stackoverflow.com/a/52749055/11465149)
* * * * [Why AVR-GCC compiler throws an error when overloading with the same variables but as PROGMEM?](https://stackoverflow.com/questions/68604352)
* * * _**```General:```**_
* * * * [Natural Log of a Number](https://www.delftstack.com/howto/arduino/arduino-natural-log/)
* **```General:```**
* * _**```Math:```**_
* * * [What the cap over letters in math means](https://en.wikipedia.org/wiki/Hat_operator#:~:text=article%3A%20unit%20vector-,Estimated%20value,%CE%B5%20(the%20statistical%20errors).)
* * * [When log is written without a base, is the equation normally referring to log base 10 or natural log?](https://math.stackexchange.com/questions/293783)
* * _**```Grammar:```**_
* * * [Plural of feedforward](https://en.wiktionary.org/wiki/feedforwards)
* * _**```Just "Random":```**_
* * * [Delving Deep into Rectifiers](https://arxiv.org/pdf/1502.01852.pdf)
* * * [Linear & Identity Activation Functions](http://theurbanengine.com/blog/linear-identity-activation)
* * * [“softmax derivative c++” Code Answer](https://www.codegrepper.com/code-examples/cpp/softmax+derivative++c%2B%2B)
* * * [The Softmax function and its derivative](https://eli.thegreenplace.net/2016/the-softmax-function-and-its-derivative/)
* * * [-](https://arxiv.org/abs/2011.11538)

<br>

**```xx\xx\202x```** 
* **```Neural Network Related```**
* *  _**```kind of Intresting To me```**_
* * * [Training Deep Neural Nets](https://www.slideshare.net/CloudxLab/training-deep-neural-nets) 
* * * [Activation Functions - EXPLAINED!](https://www.youtube.com/watch?v=s-V7gKrsels)
* * * [(Of course wiki lol) Activation function](https://en.wikipedia.org/wiki/Activation_function)
* * * [MNIST functions Intresting Simple Paper](https://arxiv.org/pdf/1804.02763.pdf)
* * _**```General```**_
* * * [How many times is backprop used in epoch?](https://datascience.stackexchange.com/a/68666)
* * * [Back-propagation in Neural Nets with >2 hidden layers](https://stats.stackexchange.com/questions/70168/back-propagation-in-neural-nets-with-2-hidden-layers)
* * * [Normalized Function, Normalized Data and Normalization](https://www.calculushowto.com/types-of-functions/normalized-function-normalized-data-and-normalization/)
* * _**```Activation Function Related```**_
* * * [Why the 6 in relu6?](https://stackoverflow.com/questions/47220595/why-the-6-in-relu6)
* * * [Are relus incapable of solving certain problems](https://ai.stackexchange.com/questions/2349/are-relus-incapable-of-solving-certain-problems)
* * * [(Seems Intresting!) Modern Activations](https://lme.tf.fau.de/lecture-notes/lecture-notes-in-deep-learning-activations-convolutions-and-pooling-part-2/)
* * * [Machine learning using ReLu return NaN](https://stackoverflow.com/questions/45616191/machine-learning-using-relu-return-nan)
* * * [Machine learning using ReLu return NaN](https://stackoverflow.com/a/45616690/11465149)
* * * [NaN loss when training regression network](https://stackoverflow.com/questions/37232782/nan-loss-when-training-regression-network)
* * * [How to avoid NaN in using ReLU + Cross-Entropy? duplicate](https://stats.stackexchange.com/questions/108381/how-to-avoid-nan-in-using-relu-cross-entropy)
* * * [Activation Functions Explained - GELU, SELU, ELU, ReLU and more](https://mlfromscratch.com/activation-functions-explained/#/)
* * * [Compressing deep neural networks on FPGAs to binary and ternary precision with HLS4ML](https://cds.cern.ch/record/2715322/plots)
* * * [For deep learning, With activation relu the output becomes NAN during training while is normal with tanh](https://stackoverflow.com/questions/47685341/for-deep-learning-with-activation-relu-the-output-becomes-nan-during-training-w)
* * _**```Gradient Explosion and clipping Related```**_
* * * [A clipped ReLU](https://www.mathworks.com/help/deeplearning/ref/nnet.cnn.layer.clippedrelulayer.html)
* * * [(Seems Intersting) Paper](https://arxiv.org/pdf/1701.07875.pdf)
* * * [Complete Guide To Exploding Gradient Problem](https://analyticsindiamag.com/complete-guide-to-exploding-gradient-problem/)
* * * [Understanding Gradient Clipping (and How It Can Fix Exploding Gradients Problem)](https://neptune.ai/blog/understanding-gradient-clipping-and-how-it-can-fix-exploding-gradients-problem)
* * * [Can the vanishing gradient problem be solved by multiplying the input of tanh with a coefficient?](https://datascience.stackexchange.com/questions/51545/can-the-vanishing-gradient-problem-be-solved-by-multiplying-the-input-of-tanh-wi)
* * * [(Seems Intersting) Keras ML library: how to do weight clipping after gradient updates? TensorFlow backend](https://stackoverflow.com/questions/42264567/keras-ml-library-how-to-do-weight-clipping-after-gradient-updates-tensorflow-b)
* * _**```MNIST Related```**_
* * * [MNIST-Visualizer](https://github.com/jeffrey-xiao/mnist-visualizer)
* * * [THE MNIST DATABASE](http://yann.lecun.com/exdb/mnist/)
* * * [ReLU vs sigmoid in mnist example](https://datascience.stackexchange.com/questions/18667/relu-vs-sigmoid-in-mnist-example)
* * * [Why not use more than 3 hidden layers for MNIST classification?](https://datascience.stackexchange.com/questions/22173/why-not-use-more-than-3-hidden-layers-for-mnist-classification)
* * * [Neural network classificator stuck at 85% accuracy for mnist dataset](https://answers.unity.com/questions/1690591/neural-network-classificator-stuck-at-85-accuracy.html )
* * * [(Arduino Project) MNIST - (approach) downsampled to 9x9 - 170 neurons ](https://hackaday.io/project/41159-deep-neural-network-on-arduino-mnist-handwritten)
* * * [MNIST digit recognition: what is the best we can get with a fully connected NN only? (no CNN)](https://stats.stackexchange.com/questions/376312/mnist-digit-recognition-what-is-the-best-we-can-get-with-a-fully-connected-nn-o)
* * * [What is the smallest model in terms of number of parameters that can achieve results over 99% on MNIST dataset?](https://www.quora.com/What-is-the-smallest-model-in-terms-of-number-of-parameters-that-can-achieve-results-over-99-on-MNIST-dataset)

* **```Related to Programming```**
* * _**```to C-type Languages```**_
* * * [c++ making a function that always runs when any other function of a class is called](https://stackoverflow.com/questions/518028/in-c-making-a-function-that-always-runs-when-any-other-function-of-a-class-is)
* * * [int.. = {1,2,}; Weird comma allowed. Any particular reason?](https://stackoverflow.com/questions/7043372/int-a-1-2-weird-comma-allowed-any-particular-reason)
* * * [Declare an array of pointers to functions in Visual C++](https://docs.microsoft.com/en-us/troubleshoot/cpp/declare-pointers-to-functions)
* * * [Function Pointer Array to a Method within a Class](https://stackoverflow.com/a/31708674/11465149)
* * * [Inability to overload Dot '.' operator in c++](https://stackoverflow.com/questions/42183631/inability-to-overload-dot-operator-in-c)
* * * [How to get address of a pointer in c/c++?](https://stackoverflow.com/questions/22250067/how-to-get-address-of-a-pointer-in-c-c)
* * * [CSharp 16 bit float conversions](https://stackoverflow.com/questions/59728656/c-sharp-16-bit-float-conversions)
* * * [Understanding * oppperator](https://stackoverflow.com/a/31331389)
* * * [Array of function pointers](http://www.cplusplus.com/forum/beginner/27582/)
* * * [Issue I came across c++](https://stackoverflow.com/questions/65860934/undefined-reference-to-outterclassfunction-ptrs-variable-issue)
* * * [Issue I came across c++](https://stackoverflow.com/questions/65873987/error-when-iterating-through-an-array-of-pointers-to-functions)
* * * [c++ constexpr](http://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/language/constexpr.html)
* * * [c++](https://stackoverflow.com/a/1759575/11465149)
* * _**```to Python```**_
* * * [Python Floating Point Precision numpy](https://stackoverflow.com/a/56515598/11465149)
* * * [Python Floating Point Precision Tensorflow](https://www.tensorflow.org/api_docs/python/tf/keras/backend/set_floatx)
* * _**```Other```**_
* * * [Aspect-oriented programming](https://en.wikipedia.org/wiki/Aspect-oriented_programming)
* * * [Metaprogramming](https://en.wikipedia.org/wiki/Metaprogramming#:~:text=Metaprogramming%20is%20a%20programming%20technique,even%20modify%20itself%20while%20running.)

* **```Arduino Related```**
* * [Reading and Writing Data to External EEPROM Using Arduino](https://www.instructables.com/Reading-and-Writing-Data-to-External-EEPROM-Using-/)
* * [avrdude: verification error, first mismatch at byte 0x7800](https://forum.arduino.cc/index.php?topic=396457.0)
* * [avrdude: verification error, first mismatch at byte 0x7800](https://forum.arduino.cc/index.php?topic=135195.0)
* * [KEYWORDS.TXT](https://forum.arduino.cc/index.php?topic=149418.0)

* **```#MACROS / pre-processor directives```**
* * [Is it possible to define same macro more than once?](https://www.sololearn.com/Discuss/1912463/is-it-possible-to-define-same-macro-more-than-once)
* * [(Very Useful) Print Content of Defined Variable](https://stackoverflow.com/a/12638158/11465149)
* * [How to remove gcc warning on pragma region](https://stackoverflow.com/questions/12894454/how-to-remove-gcc-warning-on-pragma-region)
* * [(Very Useful) Generate Functions](https://stackoverflow.com/a/1254012/11465149	)
* * [(seems intresting) Add numbers](https://stackoverflow.com/questions/3539549/can-i-add-numbers-with-the-c-c-preprocessor)
* * [3.8 Undefining and Redefining Macros](https://gcc.gnu.org/onlinedocs/cpp/Undefining-and-Redefining-Macros.html)
* * [(Seems Intresting) Iterate through #defines](https://stackoverflow.com/questions/26501032/iterate-through-defines)
* * [(Seems Intresting) Checking type of a variable](https://stackoverflow.com/questions/7339619/checking-type-of-a-variable-by-preprocessor-directive)
* * [Macro functions](http://crasseux.com/books/ctutorial/Macro-functions.html#:~:text=Macros%20that%20do%20so%20are,absolute%20value%20of%20its%20parameter.)
* * [(Random)](http://www.cplusplus.com/doc/tutorial/preprocessor/)

#

### Old Searches:
| ``` ``` | Intresting   |```NN.```| Neural Network(s) |```A.```| Arduino etc.  |```-```| Mostly .NET & Other |```*```| Maybe Intresting?  

| NNs | PROGMEM | Define directive | Other & "Random" | 
| ------ | ------ | ------ | ------ |  
|[```Playlist```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So)|[```Arduino```](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)|[```Tutorial```]( https://www.deviceplus.com/how-tos/arduino-guide/arduino-preprocessor-directives-tutorial/)|[A. Initialize Array Values](https://stackoverflow.com/questions/201101/how-to-initialize-all-members-of-an-array-to-the-same-value)|  
|[```Playlist```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi)|[```Manual```](https://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html)|[```Arduino Define```]( https://www.arduino.cc/reference/en/language/structure/further-syntax/define/)|[A. Inheritance,destructors?](https://stackoverflow.com/questions/15817941/virtual-destructors-and-deleting-objects-with-multiple-inheritance-how-does-i)|
|[```BackPropagation```](https://www.youtube.com/watch?v=L_PByyJ9g-I)|[```Examples```](http://busyducks.com/wp_4_1/2016/02/11/update-comprehensive-arduino-flash-memory-via-progmem/)|[```Determining board```](https://forum.arduino.cc/index.php?topic=113656.0)|[A. Identifying Arduino type?](https://web-engineering.info/node/28)|
|[```Math Chain Rule```]( https://www.youtube.com/watch?v=H-ybCx8gt-8 )|[+ Post](https://forum.arduino.cc/index.php?topic=613873.0)|[```define extern?```](https://forum.arduino.cc/index.php?topic=614659.0)|[A. Create compile error?](https://arduino.stackexchange.com/questions/49009/purposely-create-compile-error-to-fail-the-upload)||
|[```Getting Started```](https://www.youtube.com/watch?v=I74ymkoNTnw)|[+ Pointers](https://stackoverflow.com/questions/28645920/c-arduino-passing-pointer-to-2d-array-stored-in-progmem)|[.ino Determining Board](https://github.com/stanleyseow/attiny-nRF24L01/blob/master/hardware/tiny/cores/tiny/core_build_options.h)|[A. Measuring Memory Usage](https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory)||
|[+ BackProp Tutorial]( https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/)|[+ Double Info]( https://www.arduino.cc/reference/en/language/variables/data-types/double/)|[Understanding #if ?](https://forum.arduino.cc/index.php?topic=98155.0)|[A. External Memory](https://scienceprog.com/adding-external-memory-to-atmega128/)||
|[+ BackProp Tutorial](https://ml-cheatsheet.readthedocs.io/en/latest/nn_concepts.html)|[read-only?](https://arduino.stackexchange.com/questions/1260/can-i-write-to-flash-memory-using-progmem)|[Random Defined Site?](https://gcc.gnu.org/onlinedocs/cpp/Defined.html#Defined)|[A. ATtiny85 Math Issues?](https://www.avrfreaks.net/forum/math-issues-attiny)||
|[+ Complete NN chart !]( https://towardsdatascience.com/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464)|[flash to RAM?](https://arduino.stackexchange.com/questions/4572/progmem-do-i-have-to-copy-data-from-flash-to-ram-for-reading)|[Loading local libraries?](https://arduino.stackexchange.com/questions/8651/loading-local-libraries)|[A. Attiny85 External Mem.?](https://arduino.stackexchange.com/questions/45870/external-flash-memory-for-attiny85)||
|[+ MIT Deep RL](https://www.youtube.com/watch?v=zR11FLZ-O9M)|[Info Near Far?](https://www.geeksforgeeks.org/what-are-near-far-and-huge-pointers/)||[A. Splitting Array?](https://stackoverflow.com/questions/33682629/splitting-an-array-into-multiple-arrays-c)||
|[+ MIT Deep Learning]( https://www.youtube.com/watch?v=O5xeyoRL95U)|[Example](https://github.com/troystribling/arduino-examples/blob/master/progmem/progmem.ino)||[A. Importing Loads Everything?]( https://stackoverflow.com/questions/15291750/does-importing-libraries-load-everything-in-arduino)||
|- [```.NET Framework```]( http://accord-framework.net/)|[What is PGM_P?](https://www.avrfreaks.net/forum/what-pgmp)||[```NN. Backprop. For Dummies YT```](https://www.youtube.com/watch?v=8d6jf7s6_Qs)||
|- .NET ! [1]( https://msdn.microsoft.com/en-us/magazine/mt842505.aspx),[2]( https://msdn.microsoft.com/en-us/magazine/mt493293.aspx),[3]( https://msdn.microsoft.com/en-us/magazine/mt829273.aspx),[4]( https://msdn.microsoft.com/en-us/magazine/dn904675.aspx),[5]( https://msdn.microsoft.com/en-us/magazine/mt791798.aspx),[6]( https://msdn.microsoft.com/en-us/magazine/dn451445.aspx)|[Passing Array?](https://forum.arduino.cc/index.php?topic=302174.0)||[```NN. Convolutional (Math- code)```](https://www.youtube.com/watch?v=FTr3n7uBIuE)||
|- [C# Implementation]( https://www.tech-quantum.com/implement-a-simple-neural-network-in-csharp-net-part-1/), [2]( https://www.tech-quantum.com/implement-a-simple-neural-network-in-c-net-part-2/)|[Passing Array?](https://forum.arduino.cc/index.php?topic=36761.0)||[NN. In 4 minutes - Python](https://www.youtube.com/watch?v=h3l4qz76JhQ)||
| - [.NET Deep NN](https://www.codeguru.com/csharp/.net/deep-neural-networks-and-.net.html)|[Reading?](https://forum.arduino.cc/index.php?topic=435121.0)||[NN. Quick Intro]( https://ujjwalkarn.me/2016/08/09/quick-intro-neural-networks/)||
|[* Predicting Languages](https://www.youtube.com/watch?v=evTx5BoKcc8)|[Easy data handling?](https://forum.arduino.cc/index.php?topic=37137.0)||[NN. -]( https://natureofcode.com/book/chapter-10-neural-networks/)||
|[* MIT Recurrent NNs]( https://www.youtube.com/watch?v=nFTQ7kHQWtc)|[Reading Long?](https://forum.arduino.cc/index.php?topic=294397.0)||[NN. PyConSG 2016](https://www.youtube.com/watch?v=U0ACP9J8vOU)||
|- [2007 .NET Img Recognition]( https://www.codeproject.com/Articles/19323/Image-Recognition-with-Neural-Networks)|[Multi-D Array?](https://forum.arduino.cc/index.php?topic=45681.0)||[NN. Simple 9 lines of Py-code]()||
|- [C# Handwritten Recognition](https://www.codeproject.com/Articles/143059/%2FArticles%2F143059%2FNeural-Network-for-Recognition-of-Handwritten-Di-2)|[Attiny85 mem?](https://electronics.stackexchange.com/questions/74872/memory-management-problems-with-attiny85)||[NN. MIT Press book](http://www.deeplearningbook.org/)||
|[```Youtube Chanel```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ)|[Prob Array use?](https://arduino.stackexchange.com/questions/623/why-can-i-not-use-pointers-instead-of-array-with-progmem)||[NN. A Beginner's Guide](https://skymind.ai/wiki/neural-network)||
|[+ Recurrent Explained]( https://www.youtube.com/watch?v=yZv_yRgOvMg)|[Double or float?](https://arduino.stackexchange.com/questions/20582/since-double-and-float-represent-the-same-data-type-usually-which-is-preferab)||[```NN. MIT courses?```](http://www.ai.mit.edu/courses/6.892/lecture8-html/sld017.htm)||
|- .NET [1](https://visualstudiomagazine.com/Articles/2014/06/01/Deep-Neural-Networks.aspx?Page=2),[2](https://visualstudiomagazine.com/articles/2014/06/01/~/media/ECG/visualstudiomagazine/Images/2014/06/0614vsm_mccaffreyFig2.ashx),[3](https://visualstudiomagazine.com/articles/2014/06/01/~/media/ECG/visualstudiomagazine/Images/2014/06/0614vsm_mccaffreyFig1.ashx)|||[```NN.Back Propagation```]( https://becominghuman.ai/back-propagation-in-convolutional-neural-networks-intuition-and-code-714ef1c38199)||
|- [C# Handwritten Recognition]( https://www.codeproject.com/Articles/1273125/Handwritten-Digits-Reader-UI)|||[NN. MLP Maths?](http://www.iro.umontreal.ca/~pift6266/H10/notes/mlp.html)||
|[+ Python NN From Scratch](https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6)|||[NN. Math. Notations Into Code](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/)||
|[* How Backpropagation!](https://www.youtube.com/watch?v=An5z8lR8asY)|||[NN. Maths Into Code](http://matt.might.net/articles/discrete-math-and-code/)||
|[linear Regression](https://towardsdatascience.com/coding-deep-learning-for-beginners-linear-regression-part-1-initialization-and-prediction-7a84070b01c8)|||[NN. (TAA),(BDI) Architecture ](https://msdn.microsoft.com/en-us/magazine/mt848706)||
|[+ MLP](https://www.cse.unsw.edu.au/~cs9417ml/MLP2/)|||[NN. fast.ai ?](https://www.fast.ai/)||
|[+ MLP](https://towardsdatascience.com/multi-layer-neural-networks-with-sigmoid-function-deep-learning-for-rookies-2-bf464f09eb7f)|||[NN. deeplearning.net]( http://deeplearning.net/reading-list/tutorials/)||
|[```🇬🇷``` Νευρωνικά Δίκτυα](https://www.youtube.com/watch?v=x4mCfg14S28)|||[NN. BackProp Python]( https://machinelearningmastery.com/implement-backpropagation-algorithm-scratch-python/)||
|[```🇬🇷``` Γενετικός Αλγόριθμος]( https://www.youtube.com/watch?v=FyglDUdCqCk)|||[NN. C# Code]( https://github.com/deepakkumar1984/tech-quantum/blob/master/CSharpExamples/StandardExamples/SimpleNeuralNet.cs)||
|- [MS NN Classification](https://msdn.microsoft.com/en-US/magazine/jj190808.aspx)|||[NN. Implement BackProp Python](https://medium.com/coinmonks/implement-back-propagation-in-neural-networks-ed09897593e7)||
|- [VB ML Q-Learning]( https://www.codeproject.com/Articles/1088282/VisualBasic-Machine-Learning-Step-The-Q-Learning)|||[```NN. Java Tut Playlist```](https://www.youtube.com/watch?v=d3OtgsGcMLw&index=1&list=PLgomWLYGNl1dL1Qsmgumhcg4HOcWZMd3k) ?||
|[* handwritten Recognition ](http://neuralnetworksanddeeplearning.com/chap1.html)|||[NN. BackProp for Dummies]( https://www.quora.com/What-is-the-best-back-propagation-deep-learning-presentation-for-dummies)||
|[* Deep Learning in 6 weeks?](https://www.youtube.com/watch?v=_qjNH1rDLm0)|||[```NN. Wiki Backprop Math```](https://en.m.wikipedia.org/wiki/Backpropagation)||
|[* Playlist](https://www.youtube.com/watch?v=QJoa0JYaX1I&list=PLRqwX-V7Uu6Y7MdSCaIfsxc561QI0U0Tb)|||[NN. Looking Inside](https://ml4a.github.io/ml4a/looking_inside_neural_nets/)||
|[- ```SciBasic```](https://github.com/xieguigang/sciBASIC)|||||

<br>

# 💗 Donation 
<p align="left" width="100%">
    <img width="31%" href="" src="https://raw.githubusercontent.com/GiorgosXou/Random-stuff/main/Images/img4.png">
</p>


**Please** consider donating something, even the least amount would be really appreciated. I need it.
| Monero address: <sup>`87PVyQ8Vt768hnvVyR9Qw1NyGzDea4q9Zd6AuwHb8tQBU9VdRYjRoBL7Ya8yRPVQakW2pjt2UWEtzYoxiRd7xpuB4XSJVAW`</sup>

[![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) 


# 🕳️ Outro
- Forgive me if I've made any mistakes and please don't take me seriously with every claim i make, I am mainly "self taught" in this field of NeuralNetworks, I am not a professional programmer nor do I have a good knowledge in many of the fields used to create this library, **I just make things because I love to** [...] 

- Also looking for jobs, if you are interested let me know, I really like working with embeded systems, C\C++, python, CLIs and etc.

**if** you want to help me&others to educate ourselves better **and if** you have a love and passion for sharing and helping, **then** I suggest you to **[join our discord server ](https://discord.gg/R2RVeD3gY8)** 🤍

My Instagram account is: [giorgos.xou](https://www.instagram.com/giorgos.xou/) [;)](http://prntscr.com/xtz4s6) feel free to ask me anything

            
