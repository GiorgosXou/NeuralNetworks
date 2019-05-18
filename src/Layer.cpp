#include "Arduino.h"
#include "NeuralNetwork.h"

NeuralNetwork::Layer::Layer() {}

NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias, const bool NO_OUTPUTS)
{
    _numberOfInputs = NumberOfInputs;   // (this) layer's  Number of Inputs .
    _numberOfOutputs = NumberOfOutputs; //       ##1       Number of Outputs.

    //outputs = new float[_numberOfOutputs]; //  ##1    New Array of Outputs.
    weights = new float *[_numberOfOutputs]; //  ##1    New Array of Pointers to (float) weights.
    bias = default_Bias;                     //  ##1    Bias as Default Bias.

    for (int i = 0; i < _numberOfOutputs; i++)              // [matrix] (_numberOfOutputs * _numberOfInputs)
        weights[i] = &default_Weights[i * _numberOfInputs]; // Passing Default weights to ##1 weights by reference.
}


NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, float *default_Weights, float *default_Bias)
{
    _numberOfInputs = NumberOfInputs;   // (this) layer's  Number of Inputs .
    _numberOfOutputs = NumberOfOutputs; //       ##1       Number of Outputs.

    outputs = new float[_numberOfOutputs];   //  ##1    New Array of Outputs.
    weights = new float *[_numberOfOutputs]; //  ##1    New Array of Pointers to (float) weights.
    bias = default_Bias;                     //  ##1    Bias as Default Bias.

    for (int i = 0; i < _numberOfOutputs; i++)              // [matrix] (_numberOfOutputs * _numberOfInputs)
        weights[i] = &default_Weights[i * _numberOfInputs]; // Passing Default weights to ##1 weights by reference.
}

//- [ numberOfInputs in into this layer , NumberOfOutputs of this layer ]
NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs)
{

    _numberOfInputs = NumberOfInputs;   //       ##1       Number of Inputs .
    _numberOfOutputs = NumberOfOutputs; //       ##1       Number of Outputs.

    outputs = new float[_numberOfOutputs];   //  ##1    New Array of Outputs.
    weights = new float *[_numberOfOutputs]; //  ##1    New Array of Pointers to (float) weights.
    bias = new float;                        //  ##1    New          Bias   .
    *bias = 1.0;

    float _random;

    for (int i = 0; i < _numberOfOutputs; i++)
    {
        weights[i] = new float[_numberOfInputs];

        for (int j = 0; j < _numberOfInputs; j++)
        {
            _random = (random(-90000, 90000)); // Pseudo-Random Number between -90000 and 90000
            weights[i][j] = _random / 100000;  // Divided by 100000 = a Number between -0.90000 and 0.90000
        }
    }
}

void NeuralNetwork::Layer::FdF_PROGMEM(const float *inputs) //*
{
    outputs = new float[_numberOfOutputs];
    //feed forwards
    for (int i = 0; i < _numberOfOutputs; i++)
    {
        outputs[i] = 0;
        for (int j = 0; j < _numberOfInputs; j++)
        {
            outputs[i] += inputs[j] * pgm_read_float(&weights[i][j]); // if double pgm_read_dword 
        }
        outputs[i] = Sigmoid(outputs[i] + pgm_read_float(bias)); // if double pgm_read_dword
    }

}

void NeuralNetwork::Layer::FeedForward(const float *inputs) //*
{
    //feed forwards
    for (int i = 0; i < _numberOfOutputs; i++)
    {
        outputs[i] = 0;
        for (int j = 0; j < _numberOfInputs; j++)
        {
            outputs[i] += inputs[j] * weights[i][j]; // (neuron[i]'s 1D array/matrix of inputs) * (neuron[i]'s 2D array/matrix weights) = neuron[i]'s output
        }
        outputs[i] = Sigmoid(outputs[i] + (*bias)); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output) + (bias of current layer))
    }

    // return outputs;
}

float NeuralNetwork::Layer::Sigmoid(const float &x)
{
    return 1 / (1 + exp(-x));
}

void NeuralNetwork::Layer::BackPropOutput(const float *_expected_, const float *inputs, const NeuralNetwork *NN)
{

    preLgamma = new float[_numberOfInputs]{}; // create gamma of previous layer and initialize{} values to 0

    float bias_Delta = 1.0;
    float gamma;

    for (int i = 0; i < _numberOfOutputs; i++)
    {

        //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
        gamma = ((2 / _numberOfOutputs) * (outputs[i] - _expected_[i])) * SigmDer(outputs[i]);
        bias_Delta *= gamma;

        for (int j = 0; j < _numberOfInputs; j++)
        {
            preLgamma[j] += gamma * weights[i][j];
            weights[i][j] -= (gamma * inputs[j]) * NN->LearningRateOfWeights;
        }
    }

    *bias -= bias_Delta * NN->LearningRateOfBiases;
}

void NeuralNetwork::Layer::BackPropHidden(const Layer *frontLayer, const float *inputs, const NeuralNetwork *NN)
{
    preLgamma = new float[_numberOfInputs]{};

    float bias_Delta = 1.0;
    float gamma;

    for (int i = 0; i < _numberOfOutputs; i++)
    {

        gamma = frontLayer->preLgamma[i] * SigmDer(outputs[i]);

        bias_Delta *= gamma;

        for (int j = 0; j < _numberOfInputs; j++)
        {
            preLgamma[j] += gamma * weights[i][j];
            weights[i][j] -= (gamma * inputs[j]) * NN->LearningRateOfWeights;
        }
    }

    *bias -= bias_Delta * NN->LearningRateOfBiases;
}

float NeuralNetwork::Layer::SigmDer(const float &x)
{
    return x - x * x;
}

//If Microcontroller isn't one of the Attiny Series then it compiles the code below.
#if !defined(As__No_Common_Serial_Support) // then Compile:
void NeuralNetwork::Layer::print()
{

    Serial.print(_numberOfInputs);
    Serial.print(" ");
    Serial.print(_numberOfOutputs);
    Serial.print("| bias:");
    Serial.print(*bias);
    Serial.println("");

    for (int i = 0; i < _numberOfOutputs; i++)
    {
        Serial.print(i + 1);
        Serial.print(" ");
        for (int j = 0; j < _numberOfInputs; j++)
        {
            //weights[i][j] = (float)j;
            Serial.print(" W:");
            Serial.print(weights[i][j], 7);
            Serial.print(" ");
        }
        Serial.println("");
    }
    Serial.println("----------------------");
}

void NeuralNetwork::Layer::print_PROGMEM()
{

    Serial.print(_numberOfInputs);
    Serial.print(" ");
    Serial.print(_numberOfOutputs);
    Serial.print("| bias:");
    Serial.print(pgm_read_float(bias));
    Serial.println("");

    for (int i = 0; i < _numberOfOutputs; i++)
    {
        Serial.print(i + 1);
        Serial.print(" ");
        for (int j = 0; j < _numberOfInputs; j++)
        {
            //weights[i][j] = (float)j;
            Serial.print(" W:");
            Serial.print(pgm_read_float(&weights[i][j]), 7);
            Serial.print(" ");
        }
        Serial.println("");
    }
    Serial.println("----------------------");
}

#endif