# Simple [MLP - NeuralNetwork](https://en.wikipedia.org/wiki/Multilayer_perceptron) Library For Microcontrollers 
Nothing "Import ant", just a simple library for implementing Neural-Networks(NNs) easily and effectively on any Arduino board and other microcontrollers.

## ```Summary```
| NN Functions | Input Type (x)|Output Type (Y) | Action |
| ------ | ------ | ------ | ------ |
| ```*FeedForward(X) ```| 1D Float Array| 1D Float Array| "Feeds" the NN with X-input values and returns Y-Output Values, If needed.|
| ```*BackProp(x) ```| 1D Float Array|1D Float Array| Tells to the NN if the outputs-Y were right/the-expected-X-inputs and then, teaches it.|
  
Examples: Backpropagation_Single_Xor_Gate.ino  
Understanding the Basics of a Neural Network:  
[```0```](https://www.youtube.com/watch?v=ZzWaow1Rvho&list=PLxt59R_fWVzT9bDxA76AHm3ig0Gg9S3So) [```1```](https://www.youtube.com/watch?v=aircAruvnKk&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi) [```2```](https://www.youtube.com/watch?v=L_PByyJ9g-I) [```3```](https://www.youtube.com/watch?v=H-ybCx8gt-8) [```4```](https://www.youtube.com/watch?v=I74ymkoNTnw) [```5```](https://towardsdatascience.com/the-mostly-complete-chart-of-neural-networks-explained-3fb6f2367464) [```6```](https://www.youtube.com/channel/UCgBncpylJ1kiVaPyP-PZauQ) [```7```](https://www.youtube.com/watch?v=An5z8lR8asY) [```8```](http://neuralnetworksanddeeplearning.com/chap1.html) [```9```](https://www.lifehacker.com.au/2016/03/translating-mathematical-notations-into-code-you-can-use/) [```10```](https://en.m.wikipedia.org/wiki/Backpropagation) ```11``` ```12``` .  
[An Image that Explains some basic things.](https://imgur.com/a/Owxak6w)

## ```Features```

- ##### ``` Current```
- - ```+``` Optimized Algorithm For Less [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory) Usage.
- - ```+``` Only [Sigmoid Activation Function](https://en.wikipedia.org/wiki/Sigmoid_function).
- - ```+``` Use of [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/).
- - ```+``` Simplicity.
 

- ##### ```future```
- - ```-``` [More Activation Functions](https://towardsdatascience.com/activation-functions-neural-networks-1cbd9f8d91d6).
- - ```-``` Maybe Usage of External [EEPROM](https://en.wikipedia.org/wiki/EEPROM).
- - ```-``` Precise properties, for many different needs.

## ```Important```

- ATtiny85 doesn't have [FPU](https://en.wikipedia.org/wiki/Floating-point_unit) that makes Maths on it, "difficult" for the [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory)
- If you want to Use "Serial" On An ATtiny85 Click [Here](https://www.youtube.com/watch?v=9CX4i6rMXS) (Be Careful SoftwareSerial Uses A lot of [SRAM](https://en.wikipedia.org/wiki/Static_random-access_memory))
- If you have Error with 'POINTER_REGS' Click [Here](https://forum.arduino.cc/index.php?topic=613857.0)
- [Backprop](https://en.m.wikipedia.org/wiki/Backpropagation) maths on An ATtiny85 doesn't work properly for some reasons, though [Feed](https://en.wikipedia.org/wiki/Feed_forward_(control)) [Forword](https://en.wikipedia.org/wiki/Feedforward_neural_network) maths Work! [...]
- I am not yet a professional programmer [...]
- [**Make sure** that you have used *(4-byte)(32-bit)*-precision variables when Training, Because Floats](https://www.arduino.cc/en/pmwiki.php?n=Reference/Float):*"...are stored as 32 bits (4 bytes) of information...get more precision by using a double (e.g. up to 15 digits), on the Arduino, double is the same size as float."*

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


## ```Notes```
Forgive me for my mistakes and maybe poor knowledge in C/C++, but it is also my first time making a "normal" library [...]  
I am also sorry for my randomness in some parts of the ```Searches Across Internet``` Section.  

 Εικόνα που βλέπει το "εγώ", θυμίζει κουτί που δε βλέπεις, εικόνα που χάνεις• σκιά που 'τε φως και να βλέπεις, ακούει τα λόγια που λες: [...][ ‮#i📁👁](https://www.instagram.com/giorgos.xou/)
  
I wish love and happiness to Everyone! <3
## ```Donation```

+ [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XDMZ9RGLBWS8U&source=url)
+ Bitcoin Address: 1Cfn2zb2XC5JAqTNjDYAxwKYVwtjqcf5Pm
            
