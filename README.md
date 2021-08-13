



# Simple [MLP - NeuralNetwork](https://en.wikipedia.org/wiki/Multilayer_perceptron) Library For Microcontrollers 
Nothing "Import ant", just a simple library for implementing Neural-Networks(NNs) easily and effectively on any Arduino board and other microcontrollers.

## ```Summary```
| NN Functions | Input Type (x)|Output Type (Y) | Action |
| ------ | ------ | ------ | ------ |
|```getMeanSqrdError(x)```| Unsigned Int| float| **Calculates** & Returns the MSE _(Mean Squared Error)_ = _[ SSE (Sum Squared Error) divided by the Product of number-οf-οutputs and inputs-per-epoch aka batch-size]_. |
| ```*FeedForward(x) ```| 1D Float Array| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed.|
| ```BackProp(x) ```| 1D Float Array| - | "Tells" to the NN if the outputs-Y were correct/the-expected/X-inputs and then, "teaches" it.|
  
Examples: Backpropagation_Single_Xor_Gate.ino  
Understanding the Basics of a Neural Network:  
[```0```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) [```1```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi) [```2```](https://www.youtube.com/watch?v=L_PByyJ9g-I) [```3```](https://www.youtube.com/watch?v=H-ybCx8gt-8) [```4```](https://www.youtube.com/watch?v=I74ymkoNTnw) [```5```](https://towardsdatascience.com/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464) [```6```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ) [```7```](https://www.youtube.com/watch?v=An5z8lR8asY) [```8```](http://neuralnetworksanddeeplearning.com/chap1.html) [```9```](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/) [```10```](https://en.m.wikipedia.org/wiki/Backpropagation) [```11```](https://en.wikipedia.org/wiki/Activation_function) ```12``` .  


## ```Examples```

|*|Example Files (.ino)| About |
| ------ | ------ | ------ |
|1|```Backpropagation_Single_Xor_Gate```|Training a NN to behave as a xor-gate|
|2|```Backpropagation_double_Xor```|Training a NN to behave as a 3-input-xor circuit |
|3|```FeedForward_double_Xor```|Pre-trained NN behaving as a 3-input-xor circuit|
|4|```Run_In_Loop```|Example of using a NN inside the loop
|5|```FeedForward_double_Xor_PROGMEM```| Weights & biases are stored in the programmable memmory|
|6|```FeedForward_Individual_MNIST_PROGMEM```| Recognizing handwritten digits *[proof of concept]*|
|7|```Any_Activation_Function_Per_Layer```|Example of using multiple Activation Functions per Layer.|

## ```Important```
- If you have an error with 'POINTER_REGS' Click [Here](https://forum.arduino.cc/index.php?topic=613857.0)
-  I am **NOT a professional** in any of all those fields [...] I'm an idiot in some cases too.
- [**Make sure** that you have used *(4-byte)(32-bit)*-precision variables when Training, Because Floats](https://www.arduino.cc/en/pmwiki.php?n=Reference/Float):*"...are stored as 32 bits (4 bytes) of information...get more precision by using a double (e.g. up to 15 digits), on the Arduino, double is the same size as float."*

## ```Features```

- ##### ``` Current```
- - ```+``` Use of activation-functions per layer-to-layer.
- - ```+``` Optimizations based on [user's preference](#define-macro-properties). 
- - ```+```  MSE/BCE/CCE [loss-functions](#float-loss-functions).
- - ```+``` Many [activation-functions](#float-activation-functions).
- - ```+``` Use of [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/).
- - ```+``` Simplicity!
 

- ##### ```In the future, i want```
- - ```-``` Better code.
- - ```-``` Use of custom functions.
- - ```-``` More Activation Functions.
- - ```-``` Different weight initialization methods.
- - ```-``` Probably support for external/[internal](https://www.arduino.cc/en/Reference/EEPROM) [EEPROM](https://en.wikipedia.org/wiki/EEPROM).
- - ```-``` Even more properties, for many different needs.

## ```Tested On```
- Arduino Uno
- ATtiny85
- - doesn't have [FPU](https://en.wikipedia.org/wiki/Floating-point_unit) that makes Maths on it, "difficult" for the [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory) (i think..?)
- - If you want to Use "Serial" On An ATtiny85 Click [Here](https://www.youtube.com/watch?v=9CX4i6rMXS) (Be Careful SoftwareSerial Uses A lot of [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory))
- - [Backprop](https://en.m.wikipedia.org/wiki/Backpropagation) maths on An ATtiny85 doesn't work properly for some reasons, though [Feed](https://en.wikipedia.org/wiki/Feed_forward_(control)) [Forword](https://en.wikipedia.org/wiki/Feedforward_neural_network) maths Work! [...]
- - <sup><sub>(since the first release I haven't tested it again on the ATtiny85 at least yet, so I am not sure)</sub></sup>

## ```Functions, Variables &  [...]```
| (NN) Neural-Network's Constructors | 
| ------ |
|<sub>NeuralNetwork()</sub>|
|<sub>NeuralNetwork(```const unsigned int *_layer```, ```const unsigned int &NumberOflayers```, ```byte* _ActFunctionPerLayer=nullptr```)</sub> |
|<sub>NeuralNetwork(```const  unsigned  int  *layer_```, ```const  unsigned  int  &NumberOflayers```, ```const  float  &LRw```, ```const  float  &LRb```, ```byte *_ActFunctionPerLayer=nullptr```)</sub>|
|<sub>NeuralNetwork(```const  unsigned  int  *layer_```, ```float  *default_Weights```, ```float  *default_Bias```, ```const  unsigned  int  &NumberOflayers```, ```byte *_ActFunctionPerLayer=nullptr```);</sub>|

<br>

###  ```Type``` [Main Functions]
| NN Functions | Input Type (x)|Output Type (Y) | Action |
| ------ | ------ | ------ | ------ |
|FeedForward_Individual(```x```)|Float| 1D Float Array|"Feeds" the NN with each one X-input Individually until it returns Y-Output Values, If needed. <sup>(Way Less RAM too)</sup>|
| *FeedForword(```x```)| 1D Float Array| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed.|
| BackProp(```x```)| 1D Float Array | - | Tells to the NN if the outputs-Y were right/the-expected-X-inputs and then, teaches it.|
|print()| - |String| Serial.Prints the weights and biases of NN. _(If [B10000000](#macro-properties) prints from PROGMEM)_|

<br>

### ```float``` [Loss Functions]  
No need for ```#define MEAN_SQUARED_ERROR```, MSE is the default loss and it is always enabled.  The only case in which you will also need to define the MSE in your sketch, is only if you want to use it in relation with another loss-function. To use any other loss-function except from MSE just define it as seen below. 
| Loss Functions | Enabling MACRO |
| ------ | ------ | 
|NN.```getMeanSqrdError```(```unsigned int batch_size```)| ```#define MEAN_SQUARED_ERROR``` |
|NN.```getBinaryCrossEntropy```(```unsigned int batch_size```)| ```#define BINARY_CROSS_ENTROPY```|
|NN.```getCategoricalCrossEntropy```(```unsigned int batch_size```)| ```#define CATEGORICAL_CROSS_ENTROPY```|

<br>

### ```float``` [Loss Variables]  
To use any of the variables below,  you first need to ```#define```  a loss function as said above too.
| Loss variables | Sum variables |
| ------ | ------ | 
|NN.MeanSqrdError| NN.sumSquaredError|
|NN.BinaryCrossEntropy| NN.sumOfBinaryCrossEntropy
|NN.CategoricalCrossEntropy| NN.sumOfCategoricalCrossEntropy|

<br>

###  ```float``` [Activation Functions] 
Because of *(my uncertainty and)* the strict RAM optimization that allows the library to use one array that stores only the values after the activation instead of two arrays storing values before and after the activation, the use of some derivative functions in backpropagation are not supported by this library at this moment, as also seen by the MACRO ```NO_BACKPROP``` below. This means that if you want to use and  ```#define ``` any function from 8-13 under the section *"```NO_BACKPROP``` support"* , you won't be able to use backpropagation.

|| Enabling MACRO | Activation Functions | Action |
| ------ | ------ | ------ | ------ |
|0|```#define Sigmoid```   |NN.layers->```Sigmoid```(```&x```)  | Returns ```1/(1+e^(-x))``` |
|1|```#define Tanh```      |NN.layers->```Tanh```(```&x```)     | Returns ```(e^(2*x)-1)/(e^(2*x)+1)``` |
|2|```#define ReLU```      |NN.layers->```ReLU```(```&x```)     | Returns ```(x>0)?x:0``` |
|3|```#define LeakyELU```  |NN.layers->```LeakyELU```(```&x```) | Returns ```(x>0)?x:AlphaLeaky*x``` |
|4|```#define ELU```       |NN.layers->```ELU```(```&x```)      | Returns ```(x>0)?x:AlphaELU*(e^(x)-1)``` |
|5|```#define SELU```      |NN.layers->```SELU```(```&x```)     | Returns ```(x>0)?x:AlphaSELU*(e^(x)-1)``` |
|6|```#define Softmax```   |NN.layers->```Softmax```(```&x```)| ```void``` "complicated implementation" |
|7|```#define Identity```  |NN.layers->```Identity```(```&x```)| Returns ```x``` |
||| <center>**```NO_BACKPROP``` support**</center> | |
|8|```#define BinaryStep```|NN.layers->```BinaryStep```(```&x```)| Returns ```(x <  0) ?  0  :  1``` |
|9|```#define Softplus```  |NN.layers->```Softplus```(```&x```)| Returns ```log(1  +  exp(x))``` |
|10|```#define SiLU```     |NN.layers->```SiLU```(```&x```)| Returns ```x / (1  +  exp(-x))``` |
|11|```#define GELU```     |NN.layers->```GELU```(```&x```)| Returns ```(1/2) * x * (1  +  erf(x /  sqrt(x)))``` |
|12|```#define Mish```     |NN.layers->```Mish```(```&x```)| Returns ```x *  Tanh(log(1  +  exp(x)))``` |
|13|```#define Gaussian``` |NN.layers->```Gaussian```(```&x```)| Returns ```exp(-(x*x))``` |
||| <center>**Derivative Functions**</center> | |
|0|```#define Sigmoid```   |NN.layers->```SigmoidDer```(```&fx```) | Returns ```fx-fx*fx``` |
|1|```#define Tanh```      |NN.layers->```TanhDer```(```&fx```)| Returns ```1-fx*fx``` |
|2|```#define ReLU```      |NN.layers->```ReLUDer```(```&fx```)| Returns ```(fx>0)?1:0``` |
|3|```#define LeakyELU```  |NN.layers->```LeakyELUDer```(```&fx```)| Returns ```(fx>0)?1:AlphaLeaky``` |
|4|```#define ELU```       |NN.layers->```ELUDer```(```&fx```)| Returns ```(fx>0)?1:fx+AlphaELU``` |
|5|```#define SELU```      |NN.layers->```SELUDer```(```&fx```)| Returns ```(fx>0)?LamdaSELU:fx+AlphaSELU*LamdaSELU``` |
|6|```#define Softmax```   |NN.layers->```SoftmaxDer```(```&fx```)| Returns ```fx * (1  - fx)``` |
|7|```#define Identity```  |NN.layers->```IdentityDer```(```&x```)| Returns ```x``` |

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

###  ```float``` [Variables Of Activation Functions] 
| Enabling MACRO | Activation Variables| Default | Explenation|
|    ------   | ------ | ------ | ------ |
|```#define LeakyELU```|NN.AlphaLeaky| 0.01   | the α of Leaky |
|```#define ELU```     |NN.AlphaELU  | 1      | the α of ELU   |
|```#define SELU```    |NN.AlphaSELU | 1.6733 | the α of SELU  |
|```#define SELU```    |NN.LamdaSELU | 1.0507 | the λ of SELU  |

<br>

### ```Type``` [Other Variables]
| Type | NN's Variables | Explenation|
| ------ | ------ | ------ |
|```byte*```      |NN.```ActFunctionPerLayer``` |if [```ACTIVATION__PER_LAYER```](#macro-properties) defined|
|```float```       |NN.```LearningRateOfWeights```|The Learning-Rate-Of-Weights |
|```float```       |NN.```LearningRateOfBiases```| The Learning-Rate-Of-Biases|
|```float*```      |NN.```weights```|If [B00010000](#macro-properties) defined|
|```Layer*```      |NN.```layers``` | Layers of NN|
||<center>**Layer's Variables**</center>||
|```float*```      |NN.layers[i].```bias```| The bias of an individual layer[i] |
|```float*```      |NN.layers[i].```outputs```[]| The Output array of an individual layer[i]|
|```float**```     |NN.layers[i].```weights```[][]|if not [B00010000](#macro-properties) defined|
|```float*```      |NN.layers[i].```preLgamma```[]| The γ-error of previous layer[i-1] |
|```unsigned int```|NN.layers[i].```_numberOfInputs```| The number-Of-Inputs for an individual layer[i]|
|```unsigned int```|NN.layers[i].```_numberOfOutputs```| The number-Of-Outputs for an individual layer[i]|

<br>

### ```#define``` [MACRO Properties]

```c++
#define _1_OPTIMIZE B00000000
```
|  _1_OPTIMIZE |  Action |
| ------ | ------ | 
| ```B00000000``` |  Nothing | 
| ```B10000000``` | ⚠️ Enables the use of PROGMEM" instead of RAM|
| ```B01000000``` | ⚠️ Deletes previous layer's Outputs: Reduces RAM by a factor of ((the_sum_of_each_layer'_s **\_numberOfOutputs**) - (**\_numberOfOutputs** of_biggest_layer) *4 )  <sub><sup>approximately i think ?</sub></sup>|  
| ```B00100000``` | 🔴 Partialy Reduces RAM for Weights, level 1| 
| ```B00010000``` | Reduces RAM for Weights, level 2 by a factor of number_of_layers*[2]((%28https://forum.arduino.cc/index.php?topic=40837.0#:~:text=A%20pointer%20on%20the%20Arduino,the%20array%20it%20points%20to.%29)) - 2 bytes |  
| ```B00001000``` | 🟢 Deletes previous layer's Gamma | 
| ```B00000100``` |  Reduce RAM by a factor of [2](%28https://forum.arduino.cc/index.php?topic=40837.0#:~:text=A%20pointer%20on%20the%20Arduino,the%20array%20it%20points%20to.%29)*(number_of_layers - 1 or 2)bytes <sub><sup>slightly different usage with multiple NNs</sub></sup>| 
|```B00000010```|**Recomended** \| Disables default MSE loss function \| Reduces ROM, RAM & CPU consumption  |
  
<br>⚠️ = Backpropagation is not allowed<br>🔴 = Not yet implimented<br>🟢 = Always enabled **<sub><sup>(not switchable yet.)</sup><sub>**

<br>

## ```Searches Across Internet```  
Here most of the resources I came across the internet, I recomend you to have a look if you want to _(but please stay aware of the fact that for some of those sites, I had only opened them checked something and then closed them in a matter of seconds [so, please don't get them all siriously])_
#
### THANK YOU!
I also want **especially to thanks** [Underpower Jet](https://www.youtube.com/channel/UCWbkocGpP_8R5ZS1VpuusRA) for his amazing [tutorial](https://www.youtube.com/watch?v=L_PByyJ9g-I), by bringing it more to the surface. Because after all the videos and links I came across, he was the one that made the most significant difference to my understanding of neural networks. Plus, I would like to thanks: [giant_neural_network](https://www.youtube.com/channel/UCrBzGHKmGDcwLFnQGHJ3XYg) for [this](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) and [this](https://www.youtube.com/watch?v=vF0zqCkbsEU&t=12s), [ 3Blue1Brown](https://www.youtube.com/channel/UCYO_jab_esuFRV4b17AJtAw) for [this](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi), the Arduino community and everyone else who gave me the oportunity to learn and make this library possible to exist [...] 
#
### New Searches:
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


## ```Outro```
Forgive me if I have made any mistakes and please don't take me seriously with every claim i made, I am mainly "self taught" in this field of NeuralNetworks, I am not a professional programmer nor do I have a good knowledge in many of the fields used to create this library [...] 

I need help, I need to learn,<br>I want to learn, I want to help [...]<br>I wish love and happiness to Everyone! 🤍<br>Σημασία έχει, ότι ως αποτέλεσμα έχει την αγάπη.<br>

**if** you want to help me and others to educate ourselves better **and if** you have a love and passion for sharing and helping others, **then** I highly suggest you to **[join our discord server ](https://discord.gg/R2RVeD3gY8)** 🤍

My Instagram account is: [giorgos.xou](https://www.instagram.com/giorgos.xou/) [;)](http://prntscr.com/xtz4s6) feel free to ask me anything

## ```Donation```
if you want me to continue support this library, learn and bring more functionality to it, it would be really helpfull if you would consider donating, even the least amount of 0.01$ would be really appreciated!

***Bitcoin Address:***
<p align="left">
<img src="https://media.discordapp.net/attachments/803671967973900310/803680678000066610/Screenshot_3317.jpg" width="305" alt="image">
</p>

**1N8niMND7SqE8B7rsE7Mx7gPctkx2rUMTf**

[![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) [![Donate](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url) 

<sub>(I need money, else I might gonna kill myself for real). [stackedit.io](https://stackedit.io/app) have been used for the edditing of this MD file</sub> 

            
