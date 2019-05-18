#include "Arduino.h"
#include "NeuralNetwork.h"

NeuralNetwork::~NeuralNetwork()
{

    for (int i = 0; i < _numberOflayers; i++)
    {
        for (int j = 0; j < layers[i]._numberOfOutputs; j++) // because of this i wont make _numberOfOutputs/inputs private :/ or maybe.. i ll see... or i will change them to const*
        {
            delete[] layers[i].weights[j];
            layers[i].weights[j] = NULL;
        }

        delete[] layers[i].weights;
        delete[] layers[i].outputs;
        delete layers[i].bias;

        layers[i].bias = NULL;
        layers[i].outputs = NULL;
        layers[i].weights = NULL;
    }

    delete[] layers;
	layers = NULL; // 18/5/2019
}

NeuralNetwork::NeuralNetwork(const unsigned int *_layer, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers, bool NO_OUTPUTS)
{
    _numberOflayers = NumberOflayers - 1;

    layers = new Layer[_numberOflayers]; // there has to be a faster way by alocating memory for example...

    unsigned int weightsplitFrom = 0;
    for (int i = 0; i < _numberOflayers; i++)
    {
        layers[i] = Layer(_layer[i], _layer[i + 1], &default_Weights[weightsplitFrom], &default_Bias[i], true);
        weightsplitFrom += _layer[i] * _layer[i + 1];
    }
}

NeuralNetwork::NeuralNetwork(const unsigned int *_layer, float *default_Weights, float *default_Bias, const unsigned int &NumberOflayers)
{
    _numberOflayers = NumberOflayers - 1;

    layers = new Layer[_numberOflayers]; // there has to be a faster way by alocating memory for example...

    unsigned int weightsplitFrom = 0;
    for (int i = 0; i < _numberOflayers; i++)
    {
        layers[i] = Layer(_layer[i], _layer[i + 1], &default_Weights[weightsplitFrom], &default_Bias[i]);
        weightsplitFrom += _layer[i] * _layer[i + 1];
    }
}

NeuralNetwork::NeuralNetwork(const unsigned int *_layer, const unsigned int &NumberOflayers, const float &LRw, const float &LRb)
{
    LearningRateOfWeights = LRw; // Initializing the Learning Rate of Weights
    LearningRateOfBiases = LRb;  // Initializing the Learning Rate of Biases

    _numberOflayers = NumberOflayers - 1;

    layers = new Layer[_numberOflayers];

    for (int i = 0; i < _numberOflayers; i++)
    {
        layers[i] = Layer(_layer[i], _layer[i + 1]);
    }
}

//maybe i will  add one more constructor so i can release memory from feedforward outputs in case i dont want backprop?

NeuralNetwork::NeuralNetwork(const unsigned int *_layer, const unsigned int &NumberOflayers)
{

    _numberOflayers = NumberOflayers - 1;

    layers = new Layer[_numberOflayers];

    for (int i = 0; i < _numberOflayers; i++)
    {
        layers[i] = Layer(_layer[i], _layer[i + 1]);
    }
}

float *NeuralNetwork::FeedForward(const float *inputs, const bool IS__PROGMEM)
{
    _inputs = inputs;

    if (FIRST_TIME_FDFp == true) // is it the first time ? if not, then delete trashes
    {
        delete[] layers[_numberOflayers - 1].outputs;
        layers[_numberOflayers - 1].outputs = NULL;
    }else{
        FIRST_TIME_FDFp = true;
    }

    layers[0].FdF_PROGMEM(_inputs);

    for (int i = 1; i < _numberOflayers; i++)
    {
        layers[i].FdF_PROGMEM(layers[i - 1].outputs);

        delete[] layers[i - 1].outputs;
        layers[i - 1].outputs = NULL;
    }

    return layers[_numberOflayers - 1].outputs;
}

float *NeuralNetwork::FeedForward(const float *inputs)
{
    _inputs = inputs;

    layers[0].FeedForward(_inputs);

    for (int i = 1; i < _numberOflayers; i++)
    {
        layers[i].FeedForward(layers[i - 1].outputs);
    }

    return layers[_numberOflayers - 1].outputs;
}

void NeuralNetwork::BackProp(const float *expected)
{

    layers[_numberOflayers - 1].BackPropOutput(expected, layers[_numberOflayers - 2].outputs, this);

    for (int i = _numberOflayers - 2; i > 0; i--)
    {
        layers[i].BackPropHidden(&layers[i + 1], layers[i - 1].outputs, this);
        delete[] layers[i + 1].preLgamma;
		layers[i + 1].preLgamma = NULL; // 18/5/2019
    }

    layers[0].BackPropHidden(&layers[1], _inputs, this);

    delete[] layers[1].preLgamma;
    delete[] layers[0].preLgamma;

    layers[0].preLgamma = NULL;
    layers[1].preLgamma = NULL;
}

//If Microcontroller isn't one of the .._No_Common_Serial_Support Series then it compiles the code below.
#if !defined(As__No_Common_Serial_Support) // then Compile:
void NeuralNetwork::print(bool IS__PROGMEM)
{
    Serial.println("");
    Serial.println("----------------------");

    for (int i = 0; i < _numberOflayers; i++)
    {
        if (IS__PROGMEM == false)
            layers[i].print();
        else
            layers[i].print_PROGMEM();
    }
}
#endif