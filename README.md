[SECTION_TRAINING]: #%E2%80%8D-training
[SECTION_BARE_AND_NATIVE_SUPPORT]: #-bare--native-support

[BASIC_EXAMPLES_MLP]:  ./examples/1.Single/DENSE%20(MLP)/Basic
[BASIC_EXAMPLES_RNN]:  ./examples/1.Single/RNN%20(Vanilla)/Basic
[BASIC_EXAMPLES_GRU]:  ./examples/1.Single/GRU/Basic
[BASIC_EXAMPLES_LSTM]: ./examples/1.Single/LSTM/Basic

[MEDIA_EXAMPLES_MLP]:  ./examples/1.Single/DENSE%20(MLP)/Media
[MEDIA_EXAMPLES_RNN]:  ./examples/1.Single/RNN%20(Vanilla)/Media
[MEDIA_EXAMPLES_GRU]:  ./examples/1.Single/GRU/Media
[MEDIA_EXAMPLES_LSTM]: ./examples/1.Single/LSTM/Media

[OTHER_EXAMPLES_MLP]:  ./examples/1.Single/DENSE%20(MLP)/Other
[OTHER_EXAMPLES_RNN]:  ./examples/1.Single/RNN%20(Vanilla)/Other
[OTHER_EXAMPLES_GRU]:  ./examples/1.Single/GRU/Other
[OTHER_EXAMPLES_LSTM]: ./examples/1.Single/LSTM/Other

[EXAMPLE_MNIST_RNN]: ./examples/1.Single/RNN%20(Vanilla)/Other/mnist_progmem_quantized/mnist_progmem_quantized.ino

[EXAMPLE_CUSTOM_FUNCTIONS_INO]: ./examples/1.Single/DENSE%20(MLP)/Other/Custom_activation_function/Custom_activation_function.ino
[EXAMPLE_FEED_INDIVIDUAL_INO]: ./examples/1.Single/DENSE%20(MLP)/Other/FeedForward_Individual_MNIST_PROGMEM/FeedForward_Individual_MNIST_PROGMEM.ino
[EXAMPLE_IN_EEPROM_INO]: ./examples/1.Single/DENSE%20(MLP)/Media/FeedForward_from_internal_EEPROM/FeedForward_from_internal_EEPROM.ino
[EXAMPLE_EXTERNAL_FRAM_INO]: ./examples/1.Single/DENSE%20(MLP)/Media/FeedForward_from_external_FRAM/FeedForward_from_external_FRAM.ino
[EXAMPLE_SAVE_INTO_EXTERNAL_FRAM_INO]: ./examples/1.Single/DENSE%20(MLP)/Media/Save_NN_to_external_FRAM/Save_NN_to_external_FRAM.ino
[EXAMPLE_DOUBLE_XOR_BACKPROP_INO]: ./examples/1.Single/DENSE%20(MLP)/Basic/Backpropagation_double_Xor/Backpropagation_double_Xor.ino
[EXAMPLE_INT_QUANTIZED_XOR_INO]: ./examples/1.Single/DENSE%20(MLP)/Other/Int_quantized_double_Xor_PROGMEM/Int_quantized_double_Xor_PROGMEM.ino
[EXAMPLE_DOUBLE_PRECISION]: ./examples/1.Single/DENSE%20(MLP)/Other/Precision_for_8byte_double/Precision_for_8byte_double.ino
[EXAMPLE_HILL_CLIMB_RAM_EFFICIENT]: ./examples/1.Single/DENSE%20(MLP)/Other/RAM_Efficient_HillClimb_double_xor/RAM_Efficient_HillClimb_double_xor.ino


# [NeuralNetwork](https://en.wikipedia.org/wiki/Neural_network_(machine_learning)) Library For Microcontrollers 
Nothing *"Import ant"*, just a simple library for implementing both [MLP](https://en.wikipedia.org/wiki/Multilayer_perceptron) & [Recurrent](https://en.wikipedia.org/wiki/Recurrent_neural_network) Neural-Networks easily and effectively on most Arduino compatible boards and microcontrollers, with partial [bare-metal & native-os support][SECTION_BARE_AND_NATIVE_SUPPORT].

# 📚 Summary
| NN<span>&nbsp;</span>Functions | Input<span>&nbsp;</span>Type<span>&nbsp;</span>(x)|Output<span>&nbsp;</span>Type<span>&nbsp;</span>(Y) |<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Action<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>|
| ------ | ------ | ------ | ------ |
| ```BackProp(x)```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| - | <details><summary>Trains the Neural-network</summary>"Tells" to the NN if the output was correct/the-expected/X-inputs and then, "teaches" it.</details>|
| ```*FeedForward(x)```| [Template](https://www.geeksforgeeks.org/cpp/templates-cpp/ 'Any type but, preferably use DFLOAT ("float" or "double" based on preference)') Array| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| <details><summary>Returns the output of it</summary>"Feeds" the NN with X-input values and returns Y-Output Values, If needed.</details>|
|```getMeanSqrdError(x)```| Unsigned Int| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference')| <details><summary> Returns the Mean Squared Error</summary> MSE, is SSE (Sum Squared Error) divided by the Product of number-οf-οutputs and inputs-per-epoch aka batch-size. </details>|

Understanding the Basics of a Neural Network:  
[```EXM```][EXAMPLE_DOUBLE_XOR_BACKPROP_INO] [```0```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) [```1```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi) [```2```](https://www.youtube.com/watch?v=L_PByyJ9g-I) [```3```](https://www.youtube.com/watch?v=H-ybCx8gt-8) [```4```](https://www.youtube.com/watch?v=I74ymkoNTnw) [```5```](https://medium.com/towards-data-science/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464) [```6```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ) [```7```](https://www.youtube.com/watch?v=An5z8lR8asY) [```8```](http://neuralnetworksanddeeplearning.com/chap1.html) [```9```](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/) [```10```](https://en.m.wikipedia.org/wiki/Backpropagation) [```11```](https://en.wikipedia.org/wiki/Activation_function)

# 📦 Features

- ##### ``` Current```
- - ```+``` Use of activation-functions per layer-to-layer.
- - ```+``` Optimizations based on [user's preference](#define-macro-properties). 
- - ```+``` Support for [custom activation functions](#define-custom-functions).
- - ```+``` [Basic ESP32-S3 SIMD acceleration.](https://github.com/GiorgosXou/NeuralNetworks/blob/3dceb2f195bd3341ad0af37d5f020093c8f29988/src/NeuralNetwork.h#L2337-L2340 'Improving speed from ~ O(n^3) to O(n^2) in Feedforward')
- - ```+``` Both 16 and 8 bit, [int quantization](#int-quantization).
- - ```+``` MSE/BCE/CCE [loss-functions](#dfloat-loss-functions).
- - ```+``` Support for [double precision](#define-macro-properties).
- - ```+``` Many [activation-functions](#dfloat-activation-functions).
- - ```+``` [Use of storage medias.](#%EF%B8%8F--examples 'Such as SD, PROGMEM, EEPROM, FRAM')
- - ```+``` [Exceptional solutions.][EXAMPLE_MNIST_RNN]
- - ```+``` RNN GRU LSTM.
- - ```+``` Simplicity!  
 

- ##### ```In the future, i want```
- - ```-``` [Your support.](#-donation 'yes, your support is a feature too xD')
- - ```-``` Better overall code.
- - ```-``` Other training methods.
- - ```-``` More Activation Functions.
- - ```-``` Training with int quantization.
- - ```-``` Support for external [EEPROM](https://en.wikipedia.org/wiki/EEPROM).
- - ```-``` [Support for convolutional layers.](https://github.com/GiorgosXou/NeuralNetworks/issues/33)
- - ```-``` [Support for fixed-point arithmetics](https://github.com/GiorgosXou/NeuralNetworks/discussions/15).
- - ```-``` Different weight initialization methods.
- - ```-``` Running NNs entirely off external memmory.
- - ```-``` Even more properties, for many different needs.

# ✏️  Examples
***✨ (See also: [training with Tensorflow][SECTION_TRAINING] section & [native examples](https://github.com/GiorgosXou/native-os-neuralnetworks-examples))***

- **`🔤 Basic:`** [MLP][BASIC_EXAMPLES_MLP] | [RNN][BASIC_EXAMPLES_RNN] | [GRU][BASIC_EXAMPLES_GRU] | [LSTM][BASIC_EXAMPLES_LSTM]  
- **`💾 Media:`** [MLP][MEDIA_EXAMPLES_MLP] | [RNN][MEDIA_EXAMPLES_RNN] | [GRU][MEDIA_EXAMPLES_GRU] | [LSTM][MEDIA_EXAMPLES_LSTM]
- **`🎲 Other:`** [MLP][OTHER_EXAMPLES_MLP] | [RNN][OTHER_EXAMPLES_RNN] | [GRU][OTHER_EXAMPLES_GRU] | [LSTM][OTHER_EXAMPLES_LSTM]


# 📌 Important
1. <details><summary><b>MOST IMPORTANT</b>, DESTRUCTOR WONT FREE LAST-LAYER'S OUTPUTS !!!!</summary><b>By design</b>, the destructor won't free\deallocate the last layer's outputs, allowing you to continue using <a href="https://github.com/GiorgosXou/NeuralNetworks/blob/9ffc36f6e897fe486e2d58ecf8d2cbb9848f71e9/examples/Basic/FeedForward_double_Xor/FeedForward_double_Xor.ino#L7">these outputs</a> through the pointer in your sketch. <b>To fully delete</b> the neural-network and free the associated resources, <b>it's your responsibility to:</b> either <code>delete[] outputs</code> <b>or</b> <code>delete[] NN.layers[NN.numberOflayers - 1].outputs;</code> <ins>at the end of the scope</ins>. <b>Additionally</b>, with <code>NN.load(file)</code>: ensure you deleted last-layer's <code>*outputs</code> in your sketch, in case you plan to re-use the same pointer for capturing the outputs of the newly-loaded-NN's feedforward.</details>
2. If you need back-propagation **without hidden-layers** see [`_3_OPTIMIZE 0B00001000`](#define-macro-properties)
3. Ensure to use *(32-bit)* float-precision during [training][SECTION_TRAINING] unless you [`USE_64_BIT_DOUBLE`](#define-macro-properties)
4. `bias` simply means biases when you enable [`MULTIPLE_BIASES_PER_LAYER`](#define-macro-properties)
5. In case you have an error realated to 'POINTER_REGS' [check this link here](https://forum.arduino.cc/index.php?topic=613857.0)
6. **Bare-metal and Native-OS** support are still on an experimental state!
7. Last but not least,I am **NOT a professional** in any of those fields.


# 🦾 Bare & Native support
- To disable `NN.print()`, simply `#define DISABLE_NN_SERIAL_SUPPORT`
- To use `NN.print()` with bare-metal, you should map `printf` to UART
- [`USE_PROGMEM`](#define-macro-properties) in native-os applications, simply allows the use of `const`
- To [`USE_INTERNAL_EEPROM`](#define-macro-properties) with bare-metal, an [`EEPROM.h`](https://github.com/SpenceKonde/ATTinyCore/blob/v2.0.0-devThis-is-the-head-submit-PRs-against-this/avr/libraries/EEPROM/EEPROM.h)-alike is needed
- [`FS`](#define-macro-properties 'file system (SUPPORTS_FS_FUNCTIONALITY)') supports objects that implement: `read()` `write()` `seek()` `seekp()`



# 🔬 Tested on

<details><summary><strong>Arduino UNO</strong></summary>

- Can't [`USE_64_BIT_DOUBLE`](#define-macro-properties):  [`double` is the same as `float` on the UNO](https://www.arduino.cc/reference/en/language/variables/data-types/double/)
</details>
<details><summary><strong>ESP32-S3-Zero</strong></summary>

- Don't forget for serial to: `USB CDC on Boot: "Enabled"`
- If having issues when flashing, [hold the *(left)*-boot-button while connecting to the computer, then release it, and flash again.](https://www.waveshare.com/wiki/ESP32-S3-Zero#accordion2:~:text=If%20programming%20fails%2C%20press%20and%20hold%20the%20boot%20button%20while%20connecting%20to%20the%20computer%2C%20then%20release%20it%2C%20and%20programming%20again.)
- Uses software-emulated EEPROM, so don't expect internal-EEPROM examples\functionalities to work on it
- `USE_PROGMEM` works via plain `const` logic, therfore don't worry about bloated-code when enabling it
</details> 
<details><summary><strong>ESP32-C3</strong></summary>

- You may need to increase serial baud-rate from `9600` to `115200`
- Uses software-emulated EEPROM, so don't expect internal-EEPROM examples\functionalities to work on it
- `USE_PROGMEM` works via plain `const` logic, therfore don't worry about bloated-code when enabling it
</details> 
<details><summary><strong>ATtiny85</strong></summary>

- `NN.print()` Function is disabled!
- See [MNIST example run via the internal 512-Byte EEPROM](https://github.com/GiorgosXou/ATTiny85-MNIST-RNN-EEPROM 'Running an RNN MNIST model (mostly) via the internal 512-Byte EEPROM').
- Doesn't have [FPU](https://en.wikipedia.org/wiki/Floating-point_unit 'Floating-Point Unit') this makes Maths on it, "difficult" for the [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory 'Static Random-Access Memory') (i think..?)
- If you want to use "Serial" on an ATtiny85 Click [Here](https://www.youtube.com/watch?v=9CX4i6rMXS) (Be Careful SoftwareSerial Uses A lot of [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory))
</details> 
<details><summary><strong>Pico 2</strong></summary>

- Uses software-emulated EEPROM, so don't expect internal-EEPROM examples\functionalities to work on it
- `USE_PROGMEM` works via plain `const` logic, therfore don't worry about bloated-code when enabling it
</details>


<br>

# ⚙️ Functions, Variables  ...
**NOTE:** `DFLOAT` means `float`, unless you [`USE_64_BIT_DOUBLE`](#define-macro-properties), then it means `double`. `IDFLOAT` equals `DFLOAT` unless you [`USE_INT_QUANTIZATION`](#define-macro-properties), then it either means `int16_t` or `int8_t`. `IS_CONST` means nothing, unless you [`USE_PROGMEM`](#define-macro-properties), then it means `const`.

| (NN) Neural-Network's Constructors |
| ------ | 
|<details><summary>`NeuralNetwork()`</summary>Default Constructors</details>|
|<details><summary>`NeuralNetwork(String file)`</summary>Available if `#include <SD.h>`, lets you load NN from SD. Usefull\\**Important note:** moving it bellow `#include <NeuralNetwork.h>` will disable the support.</details>|
|<details><summary>`NeuralNetwork(unsigned int address)`</summary>Available if defined `_3_OPTIMIZE 0B10000000`-*(`USE_EXTERNAL_FRAM`)* or<br>Available if defined `_1_OPTIMIZE 0B10000000`-*(`USE_INTERNAL_EEPROM`)*</details>|
|<details><summary>`NeuralNetwork(*layer_, &NumberOflayers, *_PropsPerLayer)`</summary>Available if backpropagation is available (`! NO_BACKPROP`)</details>|
|<details><summary>`NeuralNetwork(*layer_, &NumberOflayers, LRw, LRb, *_PropsPerLayer)`</summary>Available if backpropagation is available (`! NO_BACKPROP`)</details>|
|<details><summary>`NeuralNetwork(*layer_, *default_Weights, &NumberOflayers, *_PropsPerLayer)`</summary>Available if [`NO_BIAS`](#define-macro-properties) enabled</details>|
|<details><summary>`NeuralNetwork(*layer_, *default_Weights, *default_Bias, &NumberOflayers, *_PropsPerLayer)`</summary>(:</details>|

```c++
 IS_CONST IDFLOAT *default_Bias
 IS_CONST IDFLOAT *default_Weights
 LayerType *_PropsPerLayer = NULL
 const unsigned int *layer_
 const unsigned int &NumberOflayers
 const DFLOAT LRw
 const DFLOAT LRb
```

<br>


##  ```Type``` Main Functions
| NN Functions | Input<span>&nbsp;</span>Type<span>&nbsp;</span>(x)|Output<span>&nbsp;</span>Type<span>&nbsp;</span>(Y) |<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Action<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>| 
| ------ | ------ | ------ | ------ |
|`FeedForward_Individual(x)`|[DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference')| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array|<details><summary>RAM Optimized FeedForward</summary>"Feeds" the NN with each one X-input Individually until it returns Y-Output Values, If needed. **Important note:** You can't train with it. <br><sup>(Almost no RAM usage for input layer, see also: [example][EXAMPLE_FEED_INDIVIDUAL_INO])</sup></details>|
| ```*FeedForward(x) ```| [Template](https://www.geeksforgeeks.org/cpp/templates-cpp/ 'Any type but, preferably use DFLOAT ("float" or "double" based on preference)') Array| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| <details><summary>Returns the output of the NN</summary>"Feeds" the NN with X-input values and returns Y-Output Values, If needed.</details>|
| ```BackProp(x) ```| [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') Array| - | <details><summary>Trains the NN</summary>"Tells" to the NN if the output was correct/the-expected/X-inputs and then, "teaches" it.</details>|
|`load(x)`| String \ [T_File](## '[SD\FS] Template for any kind of Object that implements `read()`, `write()`, `seek()` & `seekp()`') |bool| <details><summary>Loads NN from SD or FS</summary>Available if [_3_OPTIMIZE 0B00000010](#define-macro-properties) or `#include <SD.h>`. Usefull\\**Important note:** moving `#include <SD.h>` bellow `#include <NeuralNetwork.h>` will disable the support.</details>|
|`save(x)`| String \ [T_File](## '[SD\FS] Template for any kind of Object that implements `read()`, `write()`, `seek()` & `seekp()`') \ u_int|bool \ u_int| <details><summary>Saves NN to storage media</summary> SD \ internal-EEPROM or external-FRAM</details>|
|`print()`| - |String| <details><summary>Prints the specs of the NN</summary> _(If [_1_OPTIMIZE 0B10000000](#define-macro-properties) prints from PROGMEM. The same is true for the rest of memmory-types)_</details>|

<br>

##  ```Type``` Other Functions
| NN Functions | Input(s)<span>&nbsp;&nbsp;</span>|Output(s)<span>&nbsp;</span>|<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Action<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>| 
| ------ | ------ | ------ | ------ |
| ```HillClimb(error, tolerance)``` | [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference'), [DFLOAT](#%EF%B8%8F-functions-variables-- '"float" or "double" based on preference') | bool | [See example][EXAMPLE_HILL_CLIMB_RAM_EFFICIENT]|

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
|NN.BinaryCrossEntropy| NN.sumOfBinaryCrossEntropy |
|NN.CategoricalCrossEntropy| NN.sumOfCategoricalCrossEntropy|


<br>

##  ```DFLOAT``` Activation Functions
Due to *(my uncertainty and)* the strict RAM optimization that allows the library to use one array that stores only the values after the activation instead of two arrays storing values before and after the activation, the use of some derivative functions in backpropagation are not supported by this library at this moment, as also seen by the MACRO ```NO_BACKPROP``` below. This means that if you want to use and  ```#define``` any function from 8-13 under the section *"```NO_BACKPROP``` support"* , you won't be able to use backpropagation.

| |  <span>&nbsp;&nbsp;</span>Enabling<span>&nbsp;</span>MACRO<span>&nbsp;&nbsp;&nbsp;&nbsp;</span>| <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Activation<span>&nbsp;</span>Functions<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>|  <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>Returns<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span> |
| :------: | ------ | ------ | ------ |
|**0**|```#define Sigmoid```   |<sup><sub>NN.layers-></sub></sup>```Sigmoid(&x)```  |  ```1/(1+e^(-x))``` |
|**1**|```#define Tanh```      |<sup><sub>NN.layers-></sub></sup>```Tanh(&x)```     |  ```(e^(2*x)-1)/(e^(2*x)+1)``` |
|**2**|```#define ReLU```      |<sup><sub>NN.layers-></sub></sup>```ReLU(&x)```     |  ```(x>0)?x:0``` |
|**3**|```#define LeakyReLU```  |<sup><sub>NN.layers-></sub></sup>```LeakyReLU(&x)``` |  ```(x>0)?x:AlphaLeaky*x``` |
|**4**|```#define ELU```       |<sup><sub>NN.layers-></sub></sup>```ELU(&x)```      |  ```(x>0)?x:AlphaELU*(e^(x)-1)``` |
|**5**|```#define SELU```      |<sup><sub>NN.layers-></sub></sup>```SELU(&x)```     |  ```(x>=0)?x*LamdaSELU:LamdaSELU*AlphaSELU*(e^(x)-1)``` |
|**6**|```#define Softmax```   |<sup><sub>NN.layers-></sub></sup>```Softmax(&x)```| ```void``` "complicated implementation" |
|**7**|```#define Identity```  |<sup><sub>NN.layers-></sub></sup>```Identity(&x)```|  ```x``` |
| | | <center>**```NO_BACKPROP``` SUPPORT**</center> | |
|**8**|```#define BinaryStep```|<sup><sub>NN.layers-></sub></sup>```BinaryStep(&x)```|  ```(x <  0) ?  0  :  1``` |
|**9**|```#define Softplus```  |<sup><sub>NN.layers-></sub></sup>```Softplus(&x)```|  ```log(1  +  exp(x))``` |
|**10**|```#define SiLU```     |<sup><sub>NN.layers-></sub></sup>```SiLU(&x)```|  ```x / (1  +  exp(-x))``` |
|**11**|```#define GELU```     |<sup><sub>NN.layers-></sub></sup>```GELU(&x)```|  ```(1/2) * x * (1  +  erf(x /  sqrt(x)))``` |
|**12**|```#define Mish```     |<sup><sub>NN.layers-></sub></sup>```Mish(&x)```|  ```x *  Tanh(log(1  +  exp(x)))``` |
|**13**|```#define Gaussian``` |<sup><sub>NN.layers-></sub></sup>```Gaussian(&x)```|  ```exp(-(x*x))``` |
| | | <center>**Derivative Functions**</center> | |
|**0**|```#define Sigmoid```   |<sup><sub>NN.layers-></sub></sup>```SigmoidDer(&fx)``` |  ```fx-fx*fx``` |
|**1**|```#define Tanh```      |<sup><sub>NN.layers-></sub></sup>```TanhDer(&fx)```|  ```1-fx*fx``` |
|**2**|```#define ReLU```      |<sup><sub>NN.layers-></sub></sup>```ReLUDer(&fx)```|  ```(fx>0)?1:0``` |
|**3**|```#define LeakyReLU```  |<sup><sub>NN.layers-></sub></sup>```LeakyReLUDer(&fx)```|  ```(fx>0)?1:AlphaLeaky``` |
|**4**|```#define ELU```       |<sup><sub>NN.layers-></sub></sup>```ELUDer(&fx)```|  ```(fx>0)?1:fx+AlphaELU``` |
|**5**|```#define SELU```      |<sup><sub>NN.layers-></sub></sup>```SELUDer(&fx)```|  ```(fx>=0)?LamdaSELU:fx+AlphaSELU*LamdaSELU``` |
|**6**|```#define Softmax```   |<sup><sub>NN.layers-></sub></sup>```SoftmaxDer(&fx)```|  ```fx * (1  - fx)``` |
|**7**|```#define Identity```  |<sup><sub>NN.layers-></sub></sup>```IdentityDer(&x)```|  ```x``` |

<br>

if you want to use other activation function from the default one, just define one other:
```c++
#define Sigmoid // Default one, no need definition for single activation across network
#define Tanh
#define ReLU
#define LeakyReLU
#define ELU
#define SELU
...
```

Use any activation function per layer-to-layer, like:
```c++
#define ACTIVATION__PER_LAYER
#include <NeuralNetwork.h>

unsigned int layers[] = {3, 4, 2, 1}; // layer units
byte ActivFunctions[] = {
  Idx_Tanh,   // Index 1 = Tanh    | Layers : 0 -> 1
  Idx_ReLU,   // Index 2 = ReLU    | Layers : 1 -> 2
  Idx_Sigmoid // Index 0 = Sigmoid | Layers : 2 -> 3
};

// Tanh > ReLU > Sigmoid
```
If you want to drastically reduce ROM & slightly RAM size you can Define which Functions to use/compile, like:
```c++
#define ACTIVATION__PER_LAYER
        #define Sigmoid // 0
        //#define Tanh
        //#define ReLU
        //#define LeakyReLU
        #define ELU     // 1
        #define SELU    // 2
        ...
#include <NeuralNetwork.h>

unsigned int layers[] = {3, 4, 2, 1}; // layer units
byte ActivFunctions[] = {
  Idx_ELU,    // Index 1 = ELU     | Layers : 0 -> 1
  Idx_SELU,   // Index 2 = SELU    | Layers : 1 -> 2
  Idx_Sigmoid // Index 0 = Sigmoid | Layers : 2 -> 3
};

// ELU > SELU > Sigmoid
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
        //#define LeakyReLU
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

// derivative function must end in "Der" | Limited to f(x), due to optimization reasons
float NeuralNetwork::Layer::my_sigmoidDer(const float &fx){ return fx - fx * fx;      } 
float NeuralNetwork::Layer::my_sigmoid   (const float &x ){ return 1 / (1 + exp(-x)); }


unsigned int layers[] = {3, 4, 2, 1}; // layer units
byte ActivFunctions[] = {
  Idx_Tanh,      // Index 0 = Tanh       | Layers : 0 -> 1
  Idx_Tanh,      // Index 0 = Tanh       | Layers : 1 -> 2
  Idx_my_sigmoid // Index 1 = my_sigmoid | Layers : 2 -> 3
};

// Tanh > Tanh > my_sigmoid
```
> [!CAUTION]
> Be careful commenting in front of `#define`, see issue [#29](https://github.com/GiorgosXou/NeuralNetworks/issues/29)



<br>

##  ```DFLOAT``` Variables Of Activation Functions 
| Enabling MACRO | Activation Variables| Default | Explanation|
|    ------   | ------ | ------ | ------ |
|```#define LeakyReLU```|NN.AlphaLeaky| 0.01   | the α of Leaky |
|```#define ELU```     |NN.AlphaELU  | 1      | the α of ELU   |
|```#define SELU```    |NN.AlphaSELU | 1.67326324 | the α of SELU  |
|```#define SELU```    |NN.LamdaSELU | 1.05070098 | the λ of SELU  |

<br>

## ```Type``` Other Variables
**NOTE:** When you [`USE_INTERNAL_EEPROM`](#define-macro-properties) or [`USE_EXTERNAL_FRAM`](#define-macro-properties), then only `_numberOfInputs`,`_numberOfOutputs` and `outputs` are available

| Type | NN's Variables | Explanation|
| ------ | ------ | ------ |
|```byte*```      |NN.```PropsPerLayer``` |if ```ACTIVATION__PER_LAYER``` defined|
|```DFLOAT```       |NN.```LearningRateOfWeights```|The Learning-Rate-Of-Weights |
|```DFLOAT```       |NN.```LearningRateOfBiases```| The Learning-Rate-Of-Biases|
|```IDFLOAT*```      |NN.```weights```|If [REDUCE_RAM_WEIGHTS_LVL2](#define-macro-properties)|
|```Layer*```      |NN.```layers``` | Layers of NN|
| |<center>**Layer's Variables**</center>| |
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
| ```0B10000000``` |<sup><sub>⚠️</sub></sup>|<details><summary>Use `const`\\`PROGMEM` instead of RAM</summary>Enables the use of programmable-memmory instead of RAM, to store and use weights & biases. For non AVR-mcus, the same effect is achieved without the old legacy-progmem-api, therefore you don't need to worry about compatibility when enabling it.</details>|<sub><sup>`USE_PROGMEM`</sup></sub>|
| ```0B01000000``` |<sup><sub>⚠️📌</sub></sup>| <details><summary>Deletes previous layer's Outputs</summary>**Highly-Recommended** because: for each layer-to-layer input-to-ouput operation of internal feedforward, it deletes the previous layer's outputs. **Important note:** in case you want to `delete[] NN->layers[NN->numberOflayers - 1].outputs;` make sure afterwards to `...outputs = NULL` *(if you plan to `feedforward` again later in your sketch)*. Reducing RAM by a factor of ((the_sum_of_each_layer'_s **\_numberOfOutputs**) - (**\_numberOfOutputs** of_biggest_layer) *(4[float] or 8[double])Bytes )  <sub><sup>approximately i think ?</sub></sup></details>|<sub><sup>`REDUCE_RAM_DELETE_OUTPUTS`</sup></sub>|
| ```0B00100000``` |<sup><sub>ⓘ</sub></sup>| <details><summary>Disables SIMD support when available</summary>You may disable SIMD-support to ensure the use of any type of input-data</details>| <sub><sup>`DISABLE_SIMD_SUPPORT`</sup></sub>|
| ```0B00010000``` |<sup><sub>📌</sub></sup>| <details><summary>Reduces RAM for Weights, level 2 </summary> by a factor of (number_of_layers-1)*[2](## 'Size of a pointer (two bytes in the arduino)') Bytes</details>|<sub><sup>`REDUCE_RAM_WEIGHTS_LVL2`</sup></sub>|  
| ```0B00001000``` |<sup><sub>📌</sub></sup>| <details><summary>Reduces sketch but may effect speed</summary>Optimizes `accumulatedDotProduct` to minimize sketch consumption. May slightly reduce the performance</details>|<sub><sup>`REDUCED_SKETCH_SIZE_DOT_PROD`</sup></sub>| 
| ```0B00000100``` |<sup><sub>ⓘ</sub></sup> |<details><summary>Reduces RAM using static reference</summary>... to the NN-object (for layers) \| by a factor of [2](## 'Size of a pointer (two bytes in the arduino)')*(number_of_layers - 1 or 2)bytes. _(With this optimization)_ Note that, when you are using multiple NN-**objects** interchangeably in your sketch, you should either update `NN.me` manually before using the next one like `NN.me = &NN2` or just use `_2_OPTIMIZE 0B00000010` instead</details>|<sub><sup>`REDUCE_RAM_STATIC_REFERENCE`</sup></sub>|
| ```0B00000010``` |<sup><sub>📌</sub></sup>|<details><summary>Disables MSE function</summary>Disables the default loss function \| Reduces ROM, RAM & CPU consumption, althought usually needed for backpropagation</details> |<sub><sup>`DISABLE_MSE`</sup></sub>|
| ```0B00000001``` |<sup><sub>ⓘ</sub></sup>|<details><summary>Use 8-Byte double instead of float</summary>This will work only if your MCU supports 8byte doubles eg. Arduino UNO DOESN'T *([see also example][EXAMPLE_DOUBLE_PRECISION])*</details>  |<sub><sup>`USE_64_BIT_DOUBLE`</sup></sub>|
|  **_2_OPTIMIZE** | | | |
| ```0B10000000```  |<sup><sub>⚠️</sub></sup>|<details><summary>Use<span>&nbsp;</span>internal<span>&nbsp;</span>EEPROM<span>&nbsp;</span>instead<span>&nbsp;</span>of<span>&nbsp;</span>RAM</summary>Weights, biases, and activation functions stored-into and used-from the internal EEPROM of the MCU. Additionally, this means `REDUCE_RAM_WEIGHTS_LVLX` has no effect. see also: [example][EXAMPLE_IN_EEPROM_INO]</details> |<sub><sup>`USE_INTERNAL_EEPROM`</sup></sub>|
| ```0B01000000```  |<sup><sub></sub></sup>|<details><summary>Use NN without biases</summary>It disables the use of biases in the entire NN</details> |<sub><sup>`NO_BIAS`</sup></sub>|
| ```0B00100000```  |<sup><sub></sub></sup>|<details><summary>Use more than 1 bias, layer-to-layer</summary>Enables the use of a unique bias for each unit\\neuron of each layer-to-layer</details> |<sub><sup>`MULTIPLE_BIASES_PER_LAYER`</sup></sub>|
| ```0B00010000```  |<sup><sub></sub></sup>|<details><summary>Use [F() macro](https://docs.arduino.cc/language-reference/en/variables/utilities/PROGMEM/#:~:text=about%20myself.%5Cn%22-,The,macro,-When%20an%20instruction) for print function</summary>`Serial.print(...)` strings, normally saved in RAM. This ensures strings are stored in PROGMEM *(At least for Arduino boards)*</details> |<sub><sup>`F_MACRO`</sup></sub>|
| ```0B00001000```  |<sup><sub>⚠️📌</sub></sup>|<details><summary>Use `int16_t` quantization</summary> Weights and biases are stored as `int16_t` *(2-bytes each)*. During the proccess of feedforward each individual weight or bias: temporarily converts back to it's equivalent float [...] Reduces memmory-footprint by a factor of half the size of the "equivalent" `float` weights and biases. Slightly CPU intensive. *(**See also:** [Training > int-quantization + details](#int-quantization))*</details> |<sub><sup>`USE_INT_QUANTIZATION`</sup></sub>|
| ```0B00000100```  |<sup><sub>⚠️</sub></sup>|<details><summary>Use `int8_t ` quantization</summary>Weights and biases are stored as `int8_t` *(1-byte each)*. During the proccess of feedforward each individual weight or bias: temporarily converts back to it's equivalent float [...] Reduces memmory-footprint by a factor of half the size of the "equivalent" `int16_t` weights and biases. Slightly CPU intensive. *(**See also:** [Training > int-quantization + details](#int-quantization))*</details> |<sub><sup>`USE_INT_QUANTIZATION`</sup></sub>|
| ```0B00000010```  |<sup><sub></sub></sup>|<details><summary><sub><sup>`REDUCE_RAM_STATIC_REFERENCE`</sup></sub> for multiple NN </summary>It does the same thing as `REDUCE_RAM_STATIC_REFERENCE` but for multiple NN objects *(instead for just one)*. If you use `FeedForward_Individual` It is recommended to fallback to the original `_1_OPTIMIZE 0B00000100` and manually change `NN.me`</details> |<sub><sup>`...FOR_MULTIPLE_NN_OBJECTS`</sup></sub>|
| ```0B00000001```  |<sup><sub>⚠️📌</sub></sup>|<details><summary>Disables backpropagation</summary>Disabling backpropagation when it's not automatically disabled, helps reduce the size of your sketch.</details> |<sub><sup>`NO_BACKPROP`<sup></sub>|
|  **_3_OPTIMIZE** | | | |
| ```0B10000000```  |<sup><sub>⚠️</sub></sup>|<details><summary>Use<span>&nbsp;</span>external<span>&nbsp;</span>FRAM<span>&nbsp;</span>instead<span>&nbsp;</span>of<span>&nbsp;</span>RAM</summary>Weights, biases, and activation functions stored-into and used-from an external FRAM. Additionally, this means `REDUCE_RAM_WEIGHTS_LVLX` has no effect. see also: [example][EXAMPLE_EXTERNAL_FRAM_INO]</details> |<sub><sup>`USE_EXTERNAL_FRAM`</sup></sub>|
| ```0B01000000``` | <sup><sub></sub></sup> | <details><summary>Enables RAM-efficient Hill-Climbing</summary> a computationally-expensive but memmory-efficient Hill-Climbing algorithm. Requires only a few constant-size bytes of extra RAM to train any neural network (NN). The algorithm is primarily designed for fine-tuning pre-trained NNs using `_3_OPTIMIZE 0B00100000` instead. see also: [example][EXAMPLE_EXTERNAL_FRAM_INO]</details> |<sub><sup>`RAM_EFFICIENT_HILL_CLIMB`</sup></sub>|
| ```0B00100000``` | <sup><sub>⚠️</sub></sup> | <details><summary>Same as above but for fine-tuning</summary>Enables RAM-efficient Hill-Climbing but only for pre-trained NNs, such that you only use it for fine-tuning. see also: [example][EXAMPLE_HILL_CLIMB_RAM_EFFICIENT]</details> |<sub><sup>`RAM_...CLIMB_WITHOUT_NEW`</sup></sub>|
| ```0B00010000``` | <sup><sub></sub></sup> | <details><summary>Dynamic learning-rates for Hill-Climb</summary>In case of need for dynamic-changes in learning-rates durin Hill Climbing. see also: [example][EXAMPLE_HILL_CLIMB_RAM_EFFICIENT]</details> |<sub><sup>`...DYNAMIC_LEARNING_RATES`</sup></sub>|
| ```0B00001000``` | <sup><sub></sub></sup> | <details><summary>Support BackProp without hidden-layers</summary></details> |<sub><sup>`SUPPORT_NO_HIDDEN_BACKPROP`</sup></sub>|
| ```0B00000100``` | <sup><sub></sub></sup> | <details><summary>Disables `static`-use for activation</summary>(Not recomended) usually auto-enabled when using `Softmax`</details> |<sub><sup>`DISABLE_STATIC_FOR_ACTS`</sup></sub>|
| ```0B00000010``` | <sup><sub></sub></sup> | <details><summary>Enables FS functionality support</summary>Any object that implements `read()` `write()` `seek()` `seekp()` is accepted.</details> |<sub><sup>`SUPPORTS_FS_FUNCTIONALITY`</sup></sub>| <!-- (commit fd20e89f00b73b58930f63912d0249f7f3512d1a)-->
| ```0B00000001``` | <sup><sub>🔄</sub></sup> | <details><summary>Reduce RAM usage for GRU & LSTM</summary>*(at least theoretically)* should reduce ram usage drasticly *(when using more that 2 layers)* by defining *(per layer)*-`gatedOutputs` locally&temporarily inside `Layer::{ARCH}_Only_FeedForward(...)`, in stack</details> |<sub><sup>`REDUCE_RAM...GATED_OUTPUTS`</sup></sub>|
|  **_4_OPTIMIZE** | | | |
| ```0B10000000```  |<sup><sub>🔄</sub></sup>|<details><summary>Reduces RAM, resets states by deletion</summary>`REDUCE_RAM_RESET_STATES_BY_DELETION` instead of reseting the `hiddenStates` of an RNN to `0`, now, when calling `resetStates()` it simply `delete[]`s them and re-initializes them at the next call of `FeedForward` ***(IMPORTANT: it definitely causes heap fragmentation)*** |<sub><sup>`...RESET_STATES_BY_DELETION`</sup></sub>|

<br>

Don't use keywords to define optimizations, it won't work, use _X_OPTIMIZE
- ⚠️ = Backpropagation is not allowed
- 🔄 = Only for RNN-type architectures
- 📌 = Recommended

<br>


# 👨‍💻 Training
To train a neural-network, you can use [TensorFlow](https://www.tensorflow.org/) to do so. Here's a few basic python *(mostly set-up)* examples for you to get started with:

### [🔹MLP](https://www.tensorflow.org/api_docs/python/tf/keras/layers/Dense)

```python
# 🔹 Create a simple MLP neural network
model = tf.keras.Sequential([
    Input(shape=(input_size,)), # Input layer
    Dense(3, activation='sigmoid', dtype=tf.float32), # Dense  3 units 
    Dense(1, activation='sigmoid', dtype=tf.float32)  # Output 1 unit 
])
```

<details><summary>Click here to see the full <b>training example</b></summary>

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

</details>


### [🔹RNN (Vanilla)](https://www.tensorflow.org/api_docs/python/tf/keras/layers/SimpleRNN)

```Python
# 🔹 Build Stateful Multi-Layer SimpleRNN Model
model = Sequential([ # Input shape is (timesteps, features) | You may want to use kernel_initializer="he_normal"
    Input(shape=(seq_length, 1), batch_size=batch_size, dtype=tf.float32),
    SimpleRNN(8, activation='selu', return_sequences=True , stateful=True, dtype=tf.float32),
    SimpleRNN(1, activation='selu', return_sequences=False, stateful=True, dtype=tf.float32)
])
```

<details><summary>See how weights and biases should be <b>printed</b></summary>

```python
# TensorFlow’s (default) `use_bias=True` is `_2_OPTIMIZE 0B00100000` while for use_bias=False is `_2_OPTIMIZE 0B01000000`
print("#define _2_OPTIMIZE 0B00100000 // Enables MULTIPLE_BIASES_PER_LAYER \n") 

weights_biases = model.get_weights()
rnn_layers = model.layers[0:] # Skipping 0-index Input/Feature-Layer

# Extract and print biases
print('float biases[] = {')
for layer in rnn_layers:
    print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in layer.get_weights()[-1])},")
print('};\n')

# Extract and print weights
print("float weights[] = {", end='')
for i, layer in enumerate(rnn_layers):
    weights = layer.get_weights() # layer weights
    k  = weights[0].T # Transposed weights of layer 
    rk = weights[1].T # Transposed recurrent-weights of layer
    rows = k.shape[0]
    print(f"\n  // RNN LAYER {i+1}")
    for row_idx in range(rows):
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in k[row_idx])},")
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in rk[row_idx])},")
print("};")
```

</details>

### [🔹GRU](https://www.tensorflow.org/api_docs/python/tf/keras/layers/GRU)
``` python
# 🔹 Build Stateful Multi-Layer GRU Model
model = Sequential([ # Input shape is (timesteps, features) | You many want to use kernel_initializer="he_normal"
    Input(shape=(seq_length, 1), batch_size=batch_size, dtype=tf.float32),
    GRU(7, activation='selu', return_sequences=True , stateful=True, reset_after=False, dtype=tf.float32),
    GRU(1, activation='selu', return_sequences=False, stateful=True, reset_after=False, dtype=tf.float32),
])
```

<details><summary>See how weights and biases should be <b>printed</b></summary>

```python
# TensorFlow’s (default) `use_bias=True` is `_2_OPTIMIZE 0B00100000` while for use_bias=False is `_2_OPTIMIZE 0B01000000`
print("#define _2_OPTIMIZE 0B00100000 // Enables MULTIPLE_BIASES_PER_LAYER \n") 

weights_biases = model.get_weights()
gru_layers = model.layers[0:] # Skipping 0-index Input/Feature-Layer


def print_row(k, gate_str):
    print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in k)}, // {gate_str} gate")

def print_interleaved_rows(k, rk):
    k__np =  k.numpy().T 
    rk_np = rk.numpy().T
    num_rows = k__np.shape[0]

    for row_idx in range(num_rows):
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in k__np[row_idx])},")
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in rk_np[row_idx])},")


print("float biases[] = {")
for i, layer in enumerate(gru_layers):
    print(f"  // GRU LAYER {i+1}") # type(layer).__name__
    weights = layer.get_weights()
    k_update, k_reset, k_hidden = tf.split(weights[-1], num_or_size_splits=3, axis=0)
    print_row(k_reset , "Reset" )
    print_row(k_hidden, "Hidden")
    print_row(k_update, "Update")
print("};\n\n")

print("float weights[] = {", end='')
for i, layer in enumerate(gru_layers):
    print(f"\n  // GRU LAYER {i+1}")
    weights = layer.get_weights()

    # Split into gates
    k__update, k__reset, k__hidden = tf.split(weights[0], num_or_size_splits=3, axis=1)
    rk_update, rk_reset, rk_hidden = tf.split(weights[1], num_or_size_splits=3, axis=1)

    print("\n  // Reset gate "); print_interleaved_rows(k__reset, rk_reset)
    print("\n  // Hidden gate"); print_interleaved_rows(k__hidden, rk_hidden)
    print("\n  // Update gate"); print_interleaved_rows(k__update, rk_update)
print("};")
```

</details>

### [🔹LSTM](https://www.tensorflow.org/api_docs/python/tf/keras/layers/LSTM)
```python
# 🔹 Build Stateful Multi-Layer LSTM Model
model = Sequential([ # Input shape is (timesteps, features) | You may want to use kernel_initializer="he_normal"
    Input(shape=(seq_length, 1), batch_size=batch_size, dtype=tf.float32),
    LSTM(6, activation='selu', return_sequences=True , stateful=True, dtype=tf.float32),
    LSTM(1, activation='selu', return_sequences=False, stateful=True, dtype=tf.float32)
])
```


<details><summary>See how weights and biases should be <b>printed</b></summary>

```python
# TensorFlow’s (default) `use_bias=True` is `_2_OPTIMIZE 0B00100000` while for use_bias=False is `_2_OPTIMIZE 0B01000000`
print("#define _2_OPTIMIZE 0B00100000 // Enables MULTIPLE_BIASES_PER_LAYER \n") 

weights_biases = model.get_weights()
lstm_layers = model.layers[0:]


def print_row(k, gate_str):
    print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in k)}, // {gate_str}")

def print_interleaved_rows(k, rk):
    k__np =  k.numpy().T 
    rk_np = rk.numpy().T
    num_rows = k__np.shape[0]

    for row_idx in range(num_rows):
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in k__np[row_idx])},")
        print(f"  {', '.join(f"{f"{val:.8f}" if val < 0 else f" {val:.8f}"}f" for val in rk_np[row_idx])},")


print("float biases[] = {")
for i, layer in enumerate(lstm_layers):
    weights = layer.get_weights()
    print(f"  // LSTM LAYER {i+1}") # type(layer).__name__
    k_input, k_forget, k_cell, k_output = tf.split(weights[-1], num_or_size_splits=4, axis=0)
    print_row(k_forget, "forget gate")
    print_row(k_input , "input gate" )
    print_row(k_cell  , "cell state" )
    print_row(k_output, "output gate")
print("};\n\n")


print("float weights[] = {", end='')
for i, layer in enumerate(lstm_layers):
    print(f"\n  // LSTM LAYER {i+1}")
    weights = layer.get_weights()

    # Split into gates
    k__input, k__forget, k__cell, k__output = tf.split(weights[0], num_or_size_splits=4, axis=1)
    rk_input, rk_forget, rk_cell, rk_output = tf.split(weights[1], num_or_size_splits=4, axis=1)

    print("\n  // forget gate"); print_interleaved_rows(k__forget, rk_forget)
    print("\n  // input gate" ); print_interleaved_rows(k__input , rk_input )
    print("\n  // cell state" ); print_interleaved_rows(k__cell  , rk_cell  )
    print("\n  // output gate"); print_interleaved_rows(k__output, rk_output)
print("};")
```

</details>


> [!TIP]
> The equivalent of TensorFlow's *(default)* `use_bias=True` is `_2_OPTIMIZE 0B00100000` while for `use_bias=False` is `_2_OPTIMIZE 0B01000000`

### Int quantization

 *([See also](EXAMPLE_INT_QUANTIZED_XOR_INO))* Assuming you already have either enabled [`int16_t`](#define-macro-properties '#define _2_OPTIMIZE 0B00001000') or [`int8_t`](#define-macro-properties '#define _2_OPTIMIZE 0B00000100')... before proceeding with the example, you should know that the default range of weights *(that maps floats to ints)* , are set to `200.0` for `int16_t` and `51.0` for `int8_t` via this simple formula:
```cpp
// FLOAT RANGE FOR INT16 = (100.0) - (-100.0) = 200.0 | MAX - MIN
// FLOAT RANGE FOR INT8  = ( 25.5) - (- 25.5) =  51.0 | MAX - MIN
```

You can change that by defining your own value in your sketch, like:
```cpp
#define Q_FLOAT_RANGE 4.0 // (2.0) - (-2.0) = 4.0
```

<details><summary>Now click here to see the full <b>int-quantization MLP training example</b></summary>

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


> [!IMPORTANT]
> Make sure you have *(on top of your sketch)* enabled\\defined `_2_OPTIMIZE 0B00100000 // MULTIPLE_BIASES_PER_LAYER` or `_2_OPTIMIZE 0B01000000 // NO_BIAS ` depending on your needs of use. Additionally, if you want to use just 1 bias per layer-to-layer don't use any of those 2 optimizations *(althought, it must be noted that... unless customly done, Tensorflow doesn't support 1 bias per layer-to-layer)*. **Finally**, make sure to use `float32` unless your MCU is compatible and you want to `USE_64_BIT_DOUBLE`-optimization
> *([see also examples](#✏️-examples) on how to train a NN directly on an MCU)*

<br>


## A HUGE THANK YOU!
I want to **really thanks** [Underpower Jet](https://www.youtube.com/channel/UCWbkocGpP_8R5ZS1VpuusRA) for his amazing [tutorial](https://www.youtube.com/watch?v=L_PByyJ9g-I), by bringing it more to the surface. Because after all the videos and links I came across, he was the one that made the most significant difference to my understanding of backpropagation in neural networks. Plus, I would like to thanks: [giant_neural_network](https://www.youtube.com/channel/UCrBzGHKmGDcwLFnQGHJ3XYg) for [this](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) and [this](https://www.youtube.com/watch?v=vF0zqCkbsEU&t=12s), [ 3Blue1Brown](https://www.youtube.com/channel/UCYO_jab_esuFRV4b17AJtAw) for [this](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi), the authors of **[✨ this](https://www.researchgate.net/publication/353753323_Evaluation_of_a_wireless_low-energy_mote_with_fuzzy_algorithms_and_neural_networks_for_remote_environmental_monitoring)** scientific article for referencing me, Ivo Ljubičić for using my library for his [✨ master thesis](https://repozitorij.fsb.unizg.hr/en/islandora/object/fsb%3A5928), Arduino community and everyone else who gave me the oportunity to learn and make this library possible to exist [...] 


# 🌐 Research
Here most of the resources I came across the internet, I recommend you to have a brief look if you want to _(but please be aware of the fact that for few of those sites, I had only opened them checked something and then closed them in a matter of seconds [so, please don't get them all seriously])_


**```17\11\2025```** 
- **```Interesting:```**
- - <sub><sup>⭐ </sup></sub>[Differentiable Logic Cellular Automata](https://google-research.github.io/self-organising-systems/difflogic-ca/?hn '2025-03-19 04:34:05 PM') [2](https://news.ycombinator.com/item?id=43286161)
- **```NeuralNetworks:```**
- - [The Essential Guide to Neural Network Architectures](https://www.v7labs.com/blog/neural-network-architectures-guide '2025-08-04 08:11:07 AM')
- - [What are kernel initializers and what is their significance?](https://datascience.stackexchange.com/questions/37378 '2025-08-03 04:17:08 AM')
- - [How LLMs survive in low precision | Quantization Fundamentals](https://www.youtube.com/watch?v=qoQJq5UwV1c '2025-08-04 05:36:52 AM')
- - [Compressing Neural Networks for Embedded AI: Pruning, Projection, and Quantization](https://www.youtube.com/watch?v=7uV3-eTB5es '2025-08-16 12:31:41 PM')
- - ***```Training:```***
- - - [Is it possible to train a neural network without backpropagation?](https://stats.stackexchange.com/questions/235862/is-it-possible-to-train-a-neural-network-without-backpropagation '2025-03-19 08:07:12 PM')
- - - [How to set adaptive learning rate for GradientDescentOptimizer?](https://stackoverflow.com/questions/33919948/ '2025-08-03 04:02:54 AM')
- - - [Simulated Annealing with C](https://minimatech.org/simulated-annealing-with-c/ '2025-08-04 06:06:33 AM')
- - ***```Seems Interesting:```***
- - - [Could you make a neural network in cellular automata?](https://www.reddit.com/r/cellular_automata/comments/qgbc8w/could_you_make_a_neural_network_in_cellular/ '2025-03-21 11:05:49 AM')
- - - [ Swarm-Based Nature-Inspired Metaheuristics for Neural Network Optimization](https://www.igi-global.com/chapter/swarm-based-nature-inspired-metaheuristics-for-neural-network-optimization/187679 '2025-03-19 08:10:12 PM')
- - - [Recurrent neural-network training by a learning automaton approach for trajectory learning and control system design](https://ieeexplore.ieee.org/document/668879/authors#authors '2025-03-21 11:04:43 AM')
- - ***```RNN:```***
- - - ***```(Mostly vanilla) RNN:```***
- - - - [Number of parameters in Simple RNNs](https://datascience.stackexchange.com/questions/88436/number-of-parameters-in-simple-rnns '2025-03-19 07:26:44 PM')
- - - - [RNN Theory and Math Clearly Explained](https://www.youtube.com/watch?v=jPPWc0y-08Q '2025-03-21 10:34:33 AM')
- - - - [Gesture Recognition and Recurrent Neural Networks on an Arduino](https://spinwearables.com/rnn/ '2025-03-19 07:35:09 PM Chris zaf')
- - - - [MIT 6.S094: Recurrent Neural Networks for Steering Through Time](https://www.youtube.com/watch?v=nFTQ7kHQWtc&t=2259s '2025-03-19 08:04:08 PM')
- - - - [What exactly is a hidden state in an LSTM and RNN?](https://ai.stackexchange.com/questions/16133/what-exactly-is-a-hidden-state-in-an-lstm-and-rnn '2025-03-20 11:53:34 AM')
- - - - ***```Training:```***
- - - - - [Backpropagation in RNN](https://medium.com/@abhishekjainindore24/backpropagation-in-rnn-abd87b940a7d)
- - - - - [BPTT - Derivatives for W,V and U](https://www.youtube.com/watch?v=XoxsM5c8H-E '2025-03-21 11:00:07 AM')
- - - - - [9.7. Backpropagation Through Time](https://d2l.ai/chapter_recurrent-neural-networks/bptt.html)
- - - - - [RNN Training: Welcome to your Tape - Side B](https://medium.com/learn-love-ai/step-by-step-walkthrough-of-rnn-training-part-ii-7141084d274b '2025-03-21 10:08:18 AM')
- - - - - [Backpropagation Through Time for Recurrent Neural Network](https://mmuratarat.github.io/2019-02-07/bptt-of-rnn '2025-03-21 10:07:20 AM')
- - - - - [Backpropagation of a vanilla RNN](https://lucyliu-ucsb.github.io/posts/Backpropagation-of-a-vanilla-RNN/ '2025-03-21 10:57:26 AM')
- - - - ***```Examples:```***
- - - - - [RNN From Scratch In Python](https://www.youtube.com/watch?v=4wuIOcD1LLI '2025-03-19 08:13:18 PM')
- - - - - [Implementing Recurrent Neural Network from Scratch](https://github.com/gy910210/rnn-from-scratch '2025-03-20 08:36:37 AM')
- - - - - [Building a Recurrent Neural Network From Scratch](https://medium.com/@thisislong/building-a-recurrent-neural-network-from-scratch-ba9b27a42856 '2025-03-20 08:40:23 AM')
- - - - - [Jordan net: a 3-layer recurrent neural network (neural net) for Arduino DUE](https://forum.arduino.cc/t/jordan-net-a-3-layer-recurrent-neural-network-neural-net-for-arduino-due/334678 '2025-03-21 09:54:02 AM')
- - - - ***```ChatGPT:```***
- - - - - [RNN](https://chatgpt.com/c/67bf05a3-d500-8000-ba9f-d3e39f69e55b '2025-03-19 07:46:23 PM')
- - - - ***```Tensorflow:```***
- - - - - [Number of parameters in Simple RNNs](https://datascience.stackexchange.com/questions/88436/number-of-parameters-in-simple-rnns '2025-03-19 04:45:19 PM')
- - - - - [Mathematical structure of SimpleRNN in keras](https://stats.stackexchange.com/questions/371877/mathematical-structure-of-simplernn-in-keras '2025-03-19 04:44:17 PM')
- - - - - [TensorFlow / Keras: What is stateful = True in LSTM layers?](https://datascience.stackexchange.com/questions/66031/tensorflow-keras-what-is-stateful-true-in-lstm-layers '2025-03-21 10:53:19 AM')
- - - - - [Can you train an RNN model (Keras) by giving only one input at a time and get output continuously as you feed data instead of feeding all data at once in batches?](https://www.quora.com/Can-you-train-an-RNN-model-Keras-by-giving-only-one-input-at-a-time-and-get-output-continuously-as-you-feed-data-instead-of-feeding-all-data-at-once-in-batches '2025-03-21 10:47:59 AM')
- - - - - <sub><sup>⭐ </sup></sub>[If float32 is only 6-7 digits, how do values where the first 6-7 digits are just 0s make sense?](https://www.reddit.com/r/learnpython/comments/x7boeq/if_float32_is_only_67_digits_how_do_values_where/ '2025-03-23 10:41:03 AM')
- - - ***```GRU:```***
- - - - <sub><sup>⭐ </sup></sub>[To understand the underlying math of GRU neural network in TensorFlow Keras](https://stats.stackexchange.com/a/613773/466641)
- - - - <sub><sup>⭐ </sup></sub>[\[GRU\] Applying and Understanding Gated Recurrent Unit in Python](https://www.youtube.com/watch?v=rdz0UqQz5Sw '2025-05-14 10:50:47 AM')
- - - - [Understanding the flow of information through GRU cell](https://ashish-cse16.medium.com/understanding-the-flow-of-information-through-gru-cell-198655bc7074 '2025-05-14 01:33:19 PM')
- - - - [Simple Explanation of GRU (Gated Recurrent Units)](https://www.youtube.com/watch?v=tOuXgORsXJ4 '2025-03-25 02:41:54 PM')
- - - - [Gated Recurrent Unit | GRU | Explained in detail](https://www.youtube.com/watch?v=IBs8D8PWMc8 '2025-03-25 12:04:21 PM')
- - - - ***```Tensorflow:```***
- - - - - [TensorFlow - tf.keras.layers.GRU](https://www.tensorflow.org/api_docs/python/tf/keras/layers/GRU '2025-05-14 11:24:51 AM')
- - - - - [TensorFlow - `reset_after` parameter](https://keras.io/api/layers/recurrent_layers/gru/#:~:text=reset_after%3A%20GRU%20convention%20(whether%20to%20apply%20reset%20gate%20after%20or%20before%20matrix%20multiplication).%20False%20is%20%22before%22%2C%20True%20is '2025-05-14 01:46:24 PM')
- - - - - [GRU resetAfter support](https://github.com/tensorflow/tfjs/pull/3620 '2025-08-04 06:04:00 AM')
- - - ***```LSTM:```***
- - - - <sub><sup>⭐ </sup></sub>[\[LSTM\] Applying and Understanding Long Short-term Memory in Python](https://www.youtube.com/watch?v=rmxogwIjOhE '2025-05-26 01:08:14 PM')
- - - - <sub><sup>⭐ </sup></sub>[/keras/src/layers/rnn/lstm.py](https://github.com/keras-team/keras/blob/f6c4ac55692c132cd16211f4877fac6dbeead749/keras/src/layers/rnn/lstm.py#L218-L274 '2025-05-26 01:11:21 PM')
- - - - [Understanding LSTM Networks](https://colah.github.io/posts/2015-08-Understanding-LSTMs/ '2025-05-14 01:38:19 PM')
- - ***```Projects:```***
- - - <sub><sup>⭐ </sup></sub>[Neural Networks (MNIST inference) on the “3-cent” Microcontroller](https://cpldcpu.com/2024/05/02/machine-learning-mnist-inference-on-the-3-cent-microcontroller/#more-1674 '2025-04-08 10:11:36 PM')
- - ***```Other:```***
- - - <sub><sup>⭐ </sup></sub>[A Fundamental Unit Of Intelligence](https://www.youtube.com/watch?v=Dykkubb-Qus '2025-08-02 06:23:09 PM')
- - ***```Watch Later:```***
- - - [Recurrent Neural Network implementation](https://stackoverflow.com/questions/39910695/recurrent-neural-network-implementation '2025-03-21 10:46:16 AM')
- - - [Banach Space Representer Theorems for Neural Networks](https://www.youtube.com/watch?v=nLlIUeOqIcs '2025-03-19 04:23:06 PM')
- - - [Next-generation recurrent network models for cognitive neuroscience](https://www.youtube.com/watch?v=Eq-chOIbOwM '2025-03-19 04:24:02 PM')
- - - [G-Email: AI Agents: Introduction (Part-1) | Vipra Singh](https://mail.google.com/mail/u/0/#inbox/FMfcgzQZTgRNxBtfNwhKMwswvmJqvCQc '2025-03-19 04:29:35 PM')
- - - [Gradient Based Learning Algorithms vs Global Optimization Learning Algorithms for Neural Networks](https://stats.stackexchange.com/questions/98983/gradient-based-learning-algorithms-vs-global-optimization-learning-algorithms-fo?newreg=3e4fe90446c3477fbb9e2dc52f04bcfa '2025-03-21 11:02:43 AM')
- - - [Mamba: Linear-Time Sequence Modeling with Selective State Spaces (COLM Oral 2024)](https://www.youtube.com/watch?v=X-7rgesJaGM '2025-08-02 06:26:24 PM')
- - - [MAMBA from Scratch: Neural Nets Better and Faster than Transformers](https://www.youtube.com/watch?v=N6Piou4oYx8 '2025-08-02 06:32:10 PM')
- - - [Why Different Neuron Parts Learn Differently?](https://www.youtube.com/watch?v=9StHNcGs-JM '2025-08-02 08:53:08 PM')
- - - [LSTM Time Series Forecasting with TensorFlow & Python – Step-by-Step Tutorial](https://www.youtube.com/watch?v=94PlBzgeq90 '2025-08-03 04:11:21 AM')
- - - [recurrent neural network from scratch using c#](https://www.youtube.com/watch?v=7lp6NY4wgeA '2025-08-04 06:01:25 AM')
- **```MCUs & Arduino:```**
- - ***```ESP32:```***
- - - <sub><sup>⭐ </sup></sub>[Use randomSeed() to fallback to PRNG](https://github.com/espressif/arduino-esp32/discussions/7399 '2025-02-17 05:32:41 PM')
- - ***```CH32V003:```***
- - - [CH32V arduino support issue](https://community.platformio.org/t/ch32v-arduino-support-issue/38128/9 '2025-07-24 10:34:12 PM')
- - ***```SIMD:```***
- - - ***```Pico 2 (RP2350):```***
- - - - [GPT - Is there a C-api?](https://chatgpt.com/share/67b32cae-0604-8000-b143-de94ac59f082 '2025-02-17 02:35:20 PM')
- - - - [Reddit post speaking about SIMD too](https://www.reddit.com/r/embedded/comments/1eqyp48/ '2025-02-17 02:26:06 PM')
- - - - ***```Random:```***
- - - - - [RP2350 dsp instructions](https://forums.raspberrypi.com/viewtopic.php?t=381317 '2025-02-17 02:20:49 PM')
- - ***```Random:```***
- - - [Guide to PROGMEM on ESP8266 and Arduino IDE](https://www.youtube.com/watch?v=mg7netw1JuM '2025-02-22 01:48:43 AM')
- - ***```AVR:```***
- - - ***```register Keyword:```***
- - - - <sub><sup>⭐ </sup></sub>[Register](https://forum.arduino.cc/t/register/682625 '2025-11-07 09:19:28 PM')
- - - ***```EEMEM keyword:```***
- - - - [Set EEPROM from PC before program](https://arduino.stackexchange.com/a/28261/77085 '2025-10-27 12:35:33 AM')
- - - - [ChatGPT -  Decode EEPROM file](https://chatgpt.com/share/68fea49c-be90-8000-b7db-da3420e66d56 '2025-10-27 12:46:32 AM | TODO like PROGMEM')
- - - - [IDE upload to EEPROM](https://forum.arduino.cc/t/ide-upload-to-eeprom/480090 '2025-10-27 12:44:53 AM')
- - - - [EEprom content declaration data directly from sketch](https://forum.arduino.cc/t/eeprom-content-declaration-data-directly-from-sketch/410404 '2025-10-27 12:45:36 AM')
- - - - [.eep file empty unless also read](https://community.platformio.org/t/eep-file-empty-unless-also-read/2648 '2025-10-27 12:49:41 AM')
- - - - [Something that looks interesting](https://www.fucik.name/Arduino/eemem.php) from [source](https://forum.arduino.cc/t/eemem/261238 '2025-10-27 12:50:56 AM')
- - - - <sub><sup>⭐⭐</sup></sub>[Same thing can be done with any memmory type?](https://www.avrfreaks.net/s/topic/a5C3l000000UaPYEA0/t153758 '2025-10-27 12:52:30 AM | #define FRAMEM __attribute__((section( ".fram ")))')
- - - ***```ATMega:```***
- - - - [Little Endian or Big Endian?](https://forum.arduino.cc/t/little-endian-or-big-endian/41382 '2025-07-23 12:14:58 PM')
- **```Programming:```**
- - [Are two for-loops slower than a bigger one?](https://stackoverflow.com/questions/61131725/are-two-for-loops-slower-than-a-bigger-one '2025-08-30 09:53:41 AM')
- - ***```C/C++:```***
- - - [Why is zero-length array allowed only if it's heap allocated?](https://stackoverflow.com/questions/6861776/why-is-zero-length-array-allowed-only-if-its-heap-allocated '2025-09-05 01:25:10 PM')
- - - [The difference of int8_t, int_least8_t and int_fast8_t?](https://stackoverflow.com/questions/5254051/the-difference-of-int8-t-int-least8-t-and-int-fast8-t '2025-07-23 12:24:58 PM')
- - - [Can you make a computed goto in C++?](https://stackoverflow.com/questions/45380073/can-you-make-a-computed-goto-in-c '2025-07-23 12:41:36 PM')
- - - [How to speed up dynamic dispatch by 20% using computed gotos in standard C++](https://stackoverflow.com/questions/58774170/how-to-speed-up-dynamic-dispatch-by-20-using-computed-gotos-in-standard-c '2025-07-23 12:42:57 PM')
- - - [What optimizations does __builtin_unreachable facilitate?](https://stackoverflow.com/questions/54764535/what-optimizations-does-builtin-unreachable-facilitate '2025-07-23 12:44:19 PM')
- - - [How do I force the compiler to evaluate a switch at compile time?](https://stackoverflow.com/questions/61652334/how-do-i-force-the-compiler-to-evaluate-a-switch-at-compile-time '2025-07-24 01:56:46 PM')
- - - [Difference between "if constexpr()" Vs "if()"](https://stackoverflow.com/questions/43434491/difference-between-if-constexpr-vs-if '2025-07-24 01:55:18 PM')
- - - [A hands-on showdown of compiler flags](https://medium.com/nerd-for-tech/compiler-optimizations-boosting-code-performance-without-doing-much-95f1182a5757 '2025-08-02 08:49:43 PM')
- - - [3.12 Options That Control Optimization](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html '2025-08-03 04:32:08 AM')
- - - ***```Bitfields:```***
- - - - [Why bit endianness is an issue in bitfields?](https://stackoverflow.com/questions/6043483/why-bit-endianness-is-an-issue-in-bitfields#comment6992041_6043483 '2025-07-23 10:47:15 AM | tl;dr Safe as long as you read and write the bits in the same system')
- - - - [Is Aggregate Initialization of Bit-Fields Allowed?](https://stackoverflow.com/questions/34856936/is-aggregate-initialization-of-bit-fields-allowed '2025-08-16 06:12:07 PM | tldr YES')
- - - - [Is it possible to use array of bit fields?](https://stackoverflow.com/questions/41918433/ '2025-08-02 05:14:25 AM | bitmask is better i think')
- - - - [Purpose of empty bit fields in a structure?](https://stackoverflow.com/questions/35075688/purpose-of-empty-bit-fields-in-a-structure '2025-08-28 01:56:52 AM')
- - - ***```Macros:```***
- - - - [Macro definition to determine big endian or little endian machine?](https://stackoverflow.com/questions/2100331/macro-definition-to-determine-big-endian-or-little-endian-machine '2025-07-23 12:28:50 PM')
- - - - [How to detect if long double is of extended precision or not at compile time?](https://stackoverflow.com/questions/8751109 '2025-07-29 01:45:58 AM | for floats is FLT_MANT_DIG')
- - - - [Do any C or C++ compilers optimize within define macros?](https://stackoverflow.com/questions/6796344/do-any-c-or-c-compilers-optimize-within-define-macros '2025-08-02 08:51:52 PM')
- - - - [Can I capture the underlying value of one macro when defining another?](https://stackoverflow.com/questions/42095942 '2025-08-04 02:09:45 AM')
- - - - [How to compare strings in C conditional preprocessor-directives](https://stackoverflow.com/questions/2335888/ '2025-08-04 08:05:26 AM')
- - - - [Is it possible to define macro inside macro?](https://stackoverflow.com/questions/48431325/ '2025-08-04 03:29:34 AM')
- - - - **?** [6.5.15 Push/Pop Macro Pragmas](https://gcc.gnu.org/onlinedocs/gcc/Push_002fPop-Macro-Pragmas.html '2025-08-04 03:50:46 AM')
- - - - ***```#undef:```***
- - - - - [When do we need #ifdef before #undef?](https://stackoverflow.com/a/9090656/11465149 '2025-08-19 05:39:19 PM')
- - - - - ["You can apply the #undef directive to an identifier that has no previous definition;..."](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-appendix-pre-undef '2025-08-19 05:38:27 PM')
- - - - - ["‘#undef’ has no effect if the name is not a macro."](https://gcc.gnu.org/onlinedocs/cpp/Undefining-and-Redefining-Macros.html#index-_0023undef '2025-08-19 05:37:12 PM')
- - ***```Python:```***
- - - [Better options to the basic Arduino Serial Plotter?](https://arduino.stackexchange.com/a/66715/77085 '2025-08-02 04:20:02 AM | you may need sudo')
- **```(ALU) Arithmetic Logic Unit```**
- - [Elite: "The game that couldn't be written"](https://youtu.be/lC4YLMLar5I?t=2924 '2025-03-21 11:08:05 AM | Random but really cool')

<br>

**```22\11\2023```** 
* **```Code Related:```**
* * [Handy C++ "cheat sheet"](https://en.cppreference.com/w/cpp/keyword '2024-03-13 04:08:32 PM reserved c++ keywords')
* * _**```Macros:```**_
* * * [Do not put comments in front of #define whatever](https://github.com/GiorgosXou/NeuralNetworks/issues/29)
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


<details><summary>click to expand older research</summary>

> | ``` ``` | Intresting   |```NN.```| Neural Network(s) |```A.```| Arduino etc.  |```-```| Mostly .NET & Other |```*```| Maybe Intresting?

| NNs | PROGMEM | Define directive | Other & "Random" | 
| ------ | ------ | ------ | ------ |  
|[```Playlist```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So)|[```Arduino```](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)|[```Tutorial```]( https://www.deviceplus.com/how-tos/arduino-guide/arduino-preprocessor-directives-tutorial/)|[A. Initialize Array Values](https://stackoverflow.com/questions/201101/how-to-initialize-all-members-of-an-array-to-the-same-value)|  
|[```Playlist```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi)|[```Manual```](https://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html)|[```Arduino Define```]( https://www.arduino.cc/reference/en/language/structure/further-syntax/define/)|[A. Inheritance,destructors?](https://stackoverflow.com/questions/15817941/virtual-destructors-and-deleting-objects-with-multiple-inheritance-how-does-i)|
|[```BackPropagation```](https://www.youtube.com/watch?v=L_PByyJ9g-I)|[```Examples```](http://busyducks.com/wp_4_1/2016/02/11/update-comprehensive-arduino-flash-memory-via-progmem/)|[```Determining board```](https://forum.arduino.cc/index.php?topic=113656.0)|[A. Identifying Arduino type?](https://web-engineering.info/node/28)|
|[```Math Chain Rule```]( https://www.youtube.com/watch?v=H-ybCx8gt-8 )|[+ Post](https://forum.arduino.cc/index.php?topic=613873.0)|[```define extern?```](https://forum.arduino.cc/index.php?topic=614659.0)|[A. Create compile error?](https://arduino.stackexchange.com/questions/49009/purposely-create-compile-error-to-fail-the-upload)|
|[```Getting Started```](https://www.youtube.com/watch?v=I74ymkoNTnw)|[+ Pointers](https://stackoverflow.com/questions/28645920/c-arduino-passing-pointer-to-2d-array-stored-in-progmem)|[.ino Determining Board](https://github.com/stanleyseow/attiny-nRF24L01/blob/master/hardware/tiny/cores/tiny/core_build_options.h)|[A. Measuring Memory Usage](https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory)|
|[+ BackProp Tutorial]( https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/)|[+ Double Info]( https://www.arduino.cc/reference/en/language/variables/data-types/double/)|[Understanding #if ?](https://forum.arduino.cc/index.php?topic=98155.0)|[A. External Memory](https://scienceprog.com/adding-external-memory-to-atmega128/)|
|[+ BackProp Tutorial](https://ml-cheatsheet.readthedocs.io/en/latest/nn_concepts.html)|[read-only?](https://arduino.stackexchange.com/questions/1260/can-i-write-to-flash-memory-using-progmem)|[Random Defined Site?](https://gcc.gnu.org/onlinedocs/cpp/Defined.html#Defined)|[A. ATtiny85 Math Issues?](https://www.avrfreaks.net/forum/math-issues-attiny)|
|[+ Complete NN chart !](https://medium.com/towards-data-science/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464)|[flash to RAM?](https://arduino.stackexchange.com/questions/4572/progmem-do-i-have-to-copy-data-from-flash-to-ram-for-reading)|[Loading local libraries?](https://arduino.stackexchange.com/questions/8651/loading-local-libraries)|[A. Attiny85 External Mem.?](https://arduino.stackexchange.com/questions/45870/external-flash-memory-for-attiny85)|
|[+ MIT Deep RL](https://www.youtube.com/watch?v=zR11FLZ-O9M)|[Info Near Far?](https://www.geeksforgeeks.org/what-are-near-far-and-huge-pointers/)| |[A. Splitting Array?](https://stackoverflow.com/questions/33682629/splitting-an-array-into-multiple-arrays-c)|
|[+ MIT Deep Learning]( https://www.youtube.com/watch?v=O5xeyoRL95U)|[Example](https://github.com/troystribling/arduino-examples/blob/master/progmem/progmem.ino)| |[A. Importing Loads Everything?]( https://stackoverflow.com/questions/15291750/does-importing-libraries-load-everything-in-arduino)|
|- [```.NET Framework```]( http://accord-framework.net/)|[What is PGM_P?](https://www.avrfreaks.net/forum/what-pgmp)| |[```NN. Backprop. For Dummies YT```](https://www.youtube.com/watch?v=8d6jf7s6_Qs)|
|- .NET ! [1]( https://msdn.microsoft.com/en-us/magazine/mt842505.aspx),[2]( https://msdn.microsoft.com/en-us/magazine/mt493293.aspx),[3]( https://msdn.microsoft.com/en-us/magazine/mt829273.aspx),[4]( https://msdn.microsoft.com/en-us/magazine/dn904675.aspx),[5]( https://msdn.microsoft.com/en-us/magazine/mt791798.aspx),[6]( https://msdn.microsoft.com/en-us/magazine/dn451445.aspx)|[Passing Array?](https://forum.arduino.cc/index.php?topic=302174.0)| |[```NN. Convolutional (Math- code)```](https://www.youtube.com/watch?v=FTr3n7uBIuE)|
|- [C# Implementation]( https://www.tech-quantum.com/implement-a-simple-neural-network-in-csharp-net-part-1/), [2]( https://www.tech-quantum.com/implement-a-simple-neural-network-in-c-net-part-2/)|[Passing Array?](https://forum.arduino.cc/index.php?topic=36761.0)| |[NN. In 4 minutes - Python](https://www.youtube.com/watch?v=h3l4qz76JhQ)|
| - [.NET Deep NN](https://www.codeguru.com/csharp/.net/deep-neural-networks-and-.net.html)|[Reading?](https://forum.arduino.cc/index.php?topic=435121.0)| |[NN. Quick Intro]( https://ujjwalkarn.me/2016/08/09/quick-intro-neural-networks/)|
|[* Predicting Languages](https://www.youtube.com/watch?v=evTx5BoKcc8)|[Easy data handling?](https://forum.arduino.cc/index.php?topic=37137.0)| |[NN. -]( https://natureofcode.com/book/chapter-10-neural-networks/)|
|[* MIT Recurrent NNs]( https://www.youtube.com/watch?v=nFTQ7kHQWtc)|[Reading Long?](https://forum.arduino.cc/index.php?topic=294397.0)| |[NN. PyConSG 2016](https://www.youtube.com/watch?v=U0ACP9J8vOU)|
|- [2007 .NET Img Recognition]( https://www.codeproject.com/Articles/19323/Image-Recognition-with-Neural-Networks)|[Multi-D Array?](https://forum.arduino.cc/index.php?topic=45681.0)| |[NN. Simple 9 lines of Py-code]()|
|- [C# Handwritten Recognition](https://www.codeproject.com/Articles/143059/%2FArticles%2F143059%2FNeural-Network-for-Recognition-of-Handwritten-Di-2)|[Attiny85 mem?](https://electronics.stackexchange.com/questions/74872/memory-management-problems-with-attiny85)| |[NN. MIT Press book](http://www.deeplearningbook.org/)|
|[```Youtube Chanel```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ)|[Prob Array use?](https://arduino.stackexchange.com/questions/623/why-can-i-not-use-pointers-instead-of-array-with-progmem)| |[NN. A Beginner's Guide](https://skymind.ai/wiki/neural-network)|
|[+ Recurrent Explained]( https://www.youtube.com/watch?v=yZv_yRgOvMg)|[Double or float?](https://arduino.stackexchange.com/questions/20582/since-double-and-float-represent-the-same-data-type-usually-which-is-preferab)| |[```NN. MIT courses?```](http://www.ai.mit.edu/courses/6.892/lecture8-html/sld017.htm)|
|- .NET [1](https://visualstudiomagazine.com/Articles/2014/06/01/Deep-Neural-Networks.aspx?Page=2),[2](https://visualstudiomagazine.com/articles/2014/06/01/~/media/ECG/visualstudiomagazine/Images/2014/06/0614vsm_mccaffreyFig2.ashx),[3](https://visualstudiomagazine.com/articles/2014/06/01/~/media/ECG/visualstudiomagazine/Images/2014/06/0614vsm_mccaffreyFig1.ashx)| | |[```NN.Back Propagation```]( https://becominghuman.ai/back-propagation-in-convolutional-neural-networks-intuition-and-code-714ef1c38199)|
|- [C# Handwritten Recognition]( https://www.codeproject.com/Articles/1273125/Handwritten-Digits-Reader-UI)| | |[NN. MLP Maths?](http://www.iro.umontreal.ca/~pift6266/H10/notes/mlp.html)|
|[+ Python NN From Scratch](https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6)| | |[NN. Math. Notations Into Code](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/)|
|[* How Backpropagation!](https://www.youtube.com/watch?v=An5z8lR8asY)| | |[NN. Maths Into Code](http://matt.might.net/articles/discrete-math-and-code/)|
|[linear Regression](https://towardsdatascience.com/coding-deep-learning-for-beginners-linear-regression-part-1-initialization-and-prediction-7a84070b01c8)| | |[NN. (TAA),(BDI) Architecture ](https://msdn.microsoft.com/en-us/magazine/mt848706)|
|[+ MLP](https://www.cse.unsw.edu.au/~cs9417ml/MLP2/)| | |[NN. fast.ai ?](https://www.fast.ai/)|
|[+ MLP](https://towardsdatascience.com/multi-layer-neural-networks-with-sigmoid-function-deep-learning-for-rookies-2-bf464f09eb7f)| | |[NN. deeplearning.net]( http://deeplearning.net/reading-list/tutorials/)|
|[```🇬🇷``` Νευρωνικά Δίκτυα](https://www.youtube.com/watch?v=x4mCfg14S28)| | |[NN. BackProp Python]( https://machinelearningmastery.com/implement-backpropagation-algorithm-scratch-python/)|
|[```🇬🇷``` Γενετικός Αλγόριθμος]( https://www.youtube.com/watch?v=FyglDUdCqCk)| | |[NN. C# Code]( https://github.com/deepakkumar1984/tech-quantum/blob/master/CSharpExamples/StandardExamples/SimpleNeuralNet.cs)|
|- [MS NN Classification](https://msdn.microsoft.com/en-US/magazine/jj190808.aspx)| | |[NN. Implement BackProp Python](https://medium.com/coinmonks/implement-back-propagation-in-neural-networks-ed09897593e7)|
|- [VB ML Q-Learning]( https://www.codeproject.com/Articles/1088282/VisualBasic-Machine-Learning-Step-The-Q-Learning)| | |[```NN. Java Tut Playlist```](https://www.youtube.com/watch?v=d3OtgsGcMLw&index=1&list=PLgomWLYGNl1dL1Qsmgumhcg4HOcWZMd3k) ?|
|[* handwritten Recognition ](http://neuralnetworksanddeeplearning.com/chap1.html)| | |[NN. BackProp for Dummies]( https://www.quora.com/What-is-the-best-back-propagation-deep-learning-presentation-for-dummies)|
|[* Deep Learning in 6 weeks?](https://www.youtube.com/watch?v=_qjNH1rDLm0)| | |[```NN. Wiki Backprop Math```](https://en.m.wikipedia.org/wiki/Backpropagation)|
|[* Playlist](https://www.youtube.com/watch?v=QJoa0JYaX1I&list=PLRqwX-V7Uu6Y7MdSCaIfsxc561QI0U0Tb)| | |[NN. Looking Inside](https://ml4a.github.io/ml4a/looking_inside_neural_nets/)| 
|[- ```SciBasic```](https://github.com/xieguigang/sciBASIC)| | | |


</details>

<br>

# 💗 Donation 

Be the first person who donates to this project *(as of 2025-11-17)* Any amount of donation, will be highly appreciated! 

[![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url)
| Or via Monero address: <sup>`87PVyQ8Vt768hnvVyR9Qw1NyGzDea4q9Zd6AuwHb8tQBU9VdRYjRoBL7Ya8yRPVQakW2pjt2UWEtzYoxiRd7xpuB4XSJVAW`</sup>


# 🕳️ Outro
Forgive me if I've made any mistakes and please don't take me seriously with every claim i make, I am mainly "self taught" in this field of NeuralNetworks, I am not a professional programmer nor do I have a good knowledge in many of the fields used to create this library, **I just make things because I love to** [...] 

Also looking for jobs, if you are interested let me know, I really like working with embeded systems, C\C++, python, CLIs and etc.


Life is suffering.

**if** you want to help me&others to educate ourselves better **and if** you have a love and passion for sharing and helping, **then** I suggest you to **[join our discord server ](https://discord.gg/R2RVeD3gY8)** 🤍

<sup><sub>[.](http://prntscr.com/xtz4s6)</sub></sup>

            
