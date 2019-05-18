# Simple [MLP - NeuralNetwork](https://en.wikipedia.org/wiki/Multilayer_perceptron) Library For Microcontrollers 
Nothing "Import ant", just a simple library for implementing Neural-Networks(NNs) easily and effectively on any Arduino board and other microcontrollers.

## ```Summary```
| NN Functions | Input Type (x)|Output Type (Y) | Action |
| ------ | ------ | ------ | ------ |
| ```*FeedForword(X) ```| 1D Float Array| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed.|
| ```*BackProp(x) ```| 1D Float Array|1D Float Array| Tells to the NN if the outputs-Y were right/the-expected-X-inputs and then, teaches it.|
<br>
Examples: Backpropagation_Single_Xor_Gate.ino<br>
Understanding the Basics of a Neural Network:<br>
[```1```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) [```2```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi) [```3```](https://www.youtube.com/watch?v=L_PByyJ9g-I) [```4```](https://www.youtube.com/watch?v=H-ybCx8gt-8) [```5```](https://www.youtube.com/watch?v=I74ymkoNTnw) [```6```](https://towardsdatascience.com/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464) [```7```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ) [```8```](https://www.youtube.com/watch?v=An5z8lR8asY) [```9```](http://neuralnetworksanddeeplearning.com/chap1.html) [```10```](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/) [```11```](https://en.m.wikipedia.org/wiki/Backpropagation) ```12``` ```13``` .<br> 
[An Image that Explains some basic things.](https://imgur.com/a/Owxak6w)

## ```Features```

- ##### ``` Current```
- - ```+``` Optimazed Algorithm For Less [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory) Usage.
- - ```+``` Only [Sigmoid Activation Function](https://en.wikipedia.org/wiki/Sigmoid_function).
- - ```+``` Use of [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/).
- - ```+``` Simplicity.
 

- ##### ```future```
- - ```-``` [More Activation Functions](https://towardsdatascience.com/activation-functions-neural-networks-1cbd9f8d91d6).
- - ```-``` Maybe Usage of External [EEPROM](https://en.wikipedia.org/wiki/EEPROM).
- - ```-``` Precisely made Constructors, for different needs.

## ```Important```

- ATtiny85 doesn't have [FPU](https://en.wikipedia.org/wiki/Floating-point_unit) that makes Maths on it, "difficult" for the [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory)
- If you want to Use "Serial" On An ATtiny85 Click [Here](https://www.youtube.com/watch?v=9CX4i6rMXS) (Be Careful SoftwareSerial Uses A lot of [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory))
- If you have Error with 'POINTER_REGS' Click [Here](https://forum.arduino.cc/index.php?topic=613857.0)
- BackPropagation maths on An ATtiny85 doesn't work properly for some reasons, though FeedForword maths Works! [...]

## ```Tested On```
- Arduino Uno
- ATtiny85

## ```Examples```

|*|Example Files (.ino)|Explenation|
| ------ | ------ | ------ |
|1|```Backpropagation_double_Xor```|NeuralNetwork  Training of a 3-input-xor circuit and the print of the output(s) of it|
|2|```Backpropagation_Single_Xor_Gate```|NeuralNetwork  Training of a xor gate and the print of the output(s) of it|
|3|```FeedForward_double_Xor```|print of the outputs of the pre-trained-NN|
|4|```FeedForward_double_Xor_PROGMEM```|print of the outputs of the pre-trained-NN using weights and biases from ROM|

## ```Functions & Variables [...]```
 NN = NeuralNetwork , LR = Learning Rate

| NN Functions | Input Type (x),(z)|Output Type (Y) | Action |
| ------ | ------ | ------ | ------ |
| *FeedForword(```*inputs```)| 1D Float Array| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed.|
| *FeedForword(```*inputs```, ```IS_PROGMEM```)| 1D Float Array, Boolean| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed. [Weights And Biases Saved in ROM] |
| BackProp(```*expected```)| 1D Float Array|1D Float Array| Tells to the NN if the outputs-Y were right/the-expected-X-inputs and then, teaches it.|
|print(```IS__PROGMEM```)|Boolean|String| Serial.Prints the weights and biases of NN. If print(true) prints from ROM|
|NN.Layer[ i ].Sigmoid(```&x```)|Constant Float|Float| Returns Sigmoid Activation Function's 1/(1+e^(-x)) value |

| NN -Constructors -Variables -Layer's Variables | Type| Explenation|
| ------ | ------ | ------ |
|NeuralNetwork(```*_layer```, ```&NumberOflayers```) |```const unsigned int```, ``` ```| ```Constructor``` |
|NeuralNetwork(```*_layer```, ```&NumberOflayers```, ```&LRw```, ```&LRb```)|```const unsigned int```, ``` ``` ,```const float```, ``` ```|```Constructor```|
|NeuralNetwork(```*_layer```, ```*default_Weights```, ```*default_Bias```, ```&NumberOflayers```)|```const unsigned int```,```float``` ,``` ``` ,```const unsigned int```|```Constructor```|
|NeuralNetwork(```*_layer```, ```*default_Weights```, ```*default_Bias```, ```&NumberOflayers```,```NO_OUTPUTS```)|```const unsigned int```,```float``` ,``` ``` ,```const unsigned int```,```bool```|```Constructor``` ```NO_OUTPUTS```  Clears Outputs from RAM|
|NN.```LearningRateOfWeights```|```float```|-|
|NN.```LearningRateOfBiases```|```float```|-|
|NN.```layers```[ i ]|```Layer*```|-|
|NN.Layer[ i ].```bias```|```float*```|-|
|NN.Layer[ i ].```outputs```[ j ]|```float*```|-|
|NN.Layer[ i ].```weights```[ j ][ l ]|```float**```|-|
|NN.Layer[ i ].```preLgamma```[ j ]|```float*```|-|
|NN.layers[ i ].```_numberOfInputs```|```unsigned int```|ReadOnly|
|NN.layers[ i ].```_numberOfOutputs```|```unsigned int```|ReadOnly|

## ```Searches Across Internet```
<br>| ``` ``` | Intresting   |```NN.```| Neural Network(s) |```A.```| Arduino etc.  |```-```| Mostly .NET & Other
|```*```| Maybe Intresting?
| About | NNs | PROGMEM | Define directive | Other & "Random" | HowTo - Arduino Library|
| ------ | ------ | ------ | ------ | ------ | ------ |
| asdasd | asdasda| asdasd | asdasda| asdasd | asdasdasdasdasdasdasdasdasdasdasdasd|


## ```Notes```
Forgive me for my mistakes and maybe poor knowledge in C/C++, but it is also my first time making a "normal" library [...]<br>
I am also sorry for my randomness in some parts of the ```Searches Across Internet``` Section. <br><br>
 Εικόνα που βλέπει το "εγώ", θυμίζει κουτί που δε βλέπεις, εικόνα που χάνεις• σκιά που 'τε φως και να βλέπεις, ακούει τα λόγια που λες: [...][ ‮#i📁👁](https://www.instagram.com/p/BwFAab3BvDYEOvtq08j57EcFjNd4UoAKsb_rJ40/)

I wish love and happiness to Everyone! <3
## ```Donation```
+ [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate/?token=uovyqeI3ewzYpkwK79qNpGrT5ei9GG5xchdP3eUZoFJsTTxrk55ja4BjXI7zrM3hSCzg8m)
 + Bitcoin Address: 1Cfn2zb2XC5JAqTNjDYAxwKYVwtjqcf5Pm

## ```Hastags```
#Arduino, #Microcontrollers, #Simple, #NeuralNetworks, #MLP
            
