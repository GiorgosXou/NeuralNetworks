
// https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all
// https://www.arduino.cc/en/Hacking/libraryTutorial

/*
  NeuralNetwork.h - Library for MLP Neural Networks.
  Created by George Chousos, April 11, 2019. *0
  Released into the public domain.

  *0: Mainly Based On https://www.youtube.com/watch?v=L_PByyJ9g-I
*/

/*
[double on some Arduino boards like UNO for example is equal to float]

- https://www.arduino.cc/reference/en/language/variables/data-types/double/
- https://forum.arduino.cc/index.php?topic=613873.0
*/

/*
[Error #777]
    
 NeuralNetwork(const unsigned int *layer_, const float *default_Weights, const float *default_Bias, const unsigned int &NumberOflayers , bool isProgmem)   
 
 Because someone, might want to have default or pretrained weights and biases and not in the PROGMEM but in the SRAM.

- https://stackoverflow.com/questions/56024569/arduino-compiler-takes-into-account-const-progmem-type-as-equal-to-const-type
- https://forum.arduino.cc/index.php?topic=614438.0
*/

// STR(MSGX) | pragma message
#define MSG0
// i would love if there could be a list of microcontrollers or a way to determine with defined(..) the size of SRAM or etc.
// Defines a list of microcontroller Attiny series As__AVR_ATtinyXXX__
#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    #define As__AVR_ATtinyX__

    #if defined(__AVR_ATtiny85__)
        #undef MSG0
        #define MSG0 \n- "////////////// [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] `NN.print()` function is disabled for ATtiny85 [...]"
    #endif
#endif

// Defines a list of microcontroller series (as) As__No_Common_Serial_Support (in that moment)
#if defined(As__AVR_ATtinyX__) // or etc.
    #define As__No_Common_Serial_Support
#endif

#define SD_NN_WRITE_MODE O_WRITE | O_CREAT
#if defined(ESP32)
    #define AS_SOFTWARE_EMULATED_EEPROM
    #undef SD_NN_WRITE_MODE
    #define SD_NN_WRITE_MODE "w"
#endif


// - This prevents problems if someone accidently #include's your library twice.
#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#define __NN_VERSION__ "VERSION: 2.3.1"\n

// - That gives you access to the standard types and constants of the Arduino language.
#include "Arduino.h"

// https://arduino.stackexchange.com/questions/94743/is-ifdef-sd-h-considered-a-bad-practice/
#define SD_LIB_NAME <SD.h>
#if defined(__SD_H__) || defined(SD_h) 
    #define SUPPORTS_SD_FUNCTIONALITY
#elif defined __has_include
    #if __has_include(SD_LIB_NAME)
        #include SD_LIB_NAME
        #define SUPPORTS_SD_FUNCTIONALITY
    #endif
#endif

#define EEPROM_LIB_NAME <EEPROM.h>
#if defined(EEPROM_h) || defined(__EEPROM_H__) 
    #define INCLUDES_EEPROM_H
#elif defined __has_include
    #if __has_include(EEPROM_LIB_NAME)
        #include EEPROM_LIB_NAME 
        #define INCLUDES_EEPROM_H
    #endif
#endif

// STR(MSGX) | pragma message
#define MSG1
#define MSG2
#define MSG3
#define MSG4
#define MSG5
#define MSG6
#define MSG7
#define MSG8
#define MSG9
#define MSG10
#define MSG11
#define MSG12
#define MSG13
#define MSG14
#define MSG15
#define LOVE \n 𝖀𝖓𝖈𝖔𝖓𝖉𝖎𝖙𝖎𝖔𝖓𝖆𝖑 𝕷𝖔𝖛𝖊 

#define F_MACRO  

#define MULTIPLY_BY_INT_IF_QUANTIZATION

#define ATOL atol
#define LLONG long
#define DFLOAT float
#define DFLOAT_LEN 7
#define PGM_READ_IDFLOAT pgm_read_float
#define IS_CONST
#if defined(_1_OPTIMIZE)
    #if ((_1_OPTIMIZE bitor 0B01111111) == 0B11111111)
        #define USE_PROGMEM
        #define NO_BACKPROP
        #undef IS_CONST
        #define IS_CONST const
        #undef MSG1
        #define MSG1 \n- " [1] 0B10000000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (USE_PROGMEM)."
    #endif
    #if ((_1_OPTIMIZE bitor 0B10111111) == 0B11111111)
        #define REDUCE_RAM_DELETE_OUTPUTS
        #define NO_BACKPROP
        #undef MSG2
        #define MSG2 \n- " [1] 0B01000000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (REDUCE_RAM_DELETE_OUTPUTS)."
    #endif  
    
    #if ((_1_OPTIMIZE bitor 0B11101111) == 0B11111111)
        #define REDUCE_RAM_WEIGHTS_COMMON
        #define REDUCE_RAM_WEIGHTS_LVL2
        //#warning [⚠] Backpropagating more than once after a FeedForward [...]
        #undef MSG3
        #define MSG3 \n- " [1] 0B00010000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using (REDUCE_RAM_WEIGHTS_LVL2)."
    #elif ((_1_OPTIMIZE bitor 0B11011111) == 0B11111111)
        #undef MSG3
        #define MSG3 \n- " [1] 0B00100000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Is not implemented yet."
        //#define REDUCE_RAM_WEIGHTS_COMMON
        //#define REDUCE_RAM_WEIGHTS_LVL1
    #endif

    #if ((_1_OPTIMIZE bitor 0B11110111) == 0B11111111)
        #define REDUCE_RAM_DELETE_PREVIOUS_LAYER_GAMMA
        #undef MSG4
        #define MSG4 \n- " [1] 0B00001000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Always Enabled not switchable yet."
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111011) == 0B11111111)
        #define REDUCE_RAM_STATIC_REFERENCE
        #undef MSG5
        #define MSG5 \n- " [1] 0B00000100 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] If multiple NN objects, see: _2_OPTIMIZE 0B00000010!"
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111101) == 0B11111111)
        #define DISABLE_MSE
        #undef MSG6
        #define MSG6 \n- " [1] 0B00000010 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] MSE is disabled (DISABLE_MSE) (DEFAULT_LOSS)"
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111110) == 0B11111111)
        #undef ATOL 
        #undef LLONG 
        #undef DFLOAT_LEN 
        #undef DFLOAT 
        #undef PGM_READ_IDFLOAT 
        #define USE_64_BIT_DOUBLE
        #define ATOL atoll
        #define LLONG long long
        #define DFLOAT_LEN 15
        #define DFLOAT double
        #define PGM_READ_IDFLOAT pgm_read_double

        double pgm_read_double(const double* address) {
            double result;
            memcpy_P(&result, address, sizeof(double));
            return result;
        }

        #undef MSG7
        #define MSG7 \n- " [1] 0B00000001 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Not all MCUs support 64bit\8byte double (USE_64_BIT_DOUBLE)."
    #endif
    //if i'll make most of the things static/global, i can significantly reduce rom but with the "limitation" of "one" NN per skeatch
#endif

#define IDFLOAT DFLOAT

// If not USE_INT_QUANTIZATION then the line bellow is used for SD save
#define CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(value) *((LLONG*)(&value))

#if defined(_2_OPTIMIZE)
    #if ((_2_OPTIMIZE bitor 0B01111111) == 0B11111111)
        #if defined(REDUCE_RAM_WEIGHTS_COMMON)
            #undef MSG3
            #define MSG3 \n- " [_] 0B00110000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] There is no need for (REDUCE_RAM_WEIGHTS_LVLX)"
        #endif
        #define NO_BACKPROP
        #define USE_INTERNAL_EEPROM
        #if defined(ACTIVATION__PER_LAYER)
            #define SIZEOF_FX sizeof(byte)
        #else
            #define SIZEOF_FX 0
        #endif
        #if defined(AS_SOFTWARE_EMULATED_EEPROM)
            #undef MSG9
            #define MSG9 \n- " [2] 0B10000000 [⚠] [𝗪𝗔𝗥𝗡𝗜𝗡𝗚] ESP32 MCUs are defined (AS_SOFTWARE_EMULATED_EEPROM)."
        #endif
        #undef MSG8
        #define MSG8 \n- " [2] 0B10000000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (USE_INTERNAL_EEPROM)."
        #if !defined(EEPROM_h) || !defined(__EEPROM_H__) 
            // for some reason it says 'EEPROM' was not declared in this scope even though i #include it below. So it needs it at the sketch i guess too
            #include <EEPROM.h>
            #define INCLUDES_EEPROM_H
        #endif
    #endif

    #if ((_2_OPTIMIZE bitor 0B10111111) == 0B11111111)
        #undef MSG11
        #define MSG11 \n- " [2] 0B01000000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Biases are disabled (NO_BIAS)."
        #define HAS_NO_BIAS true
        #define NO_BIAS
    #endif

    #if ((_2_OPTIMIZE bitor 0B11011111) == 0B11111111)
        #if defined(NO_BIAS)
            #error "You can't have both NO_BIAS and MULTIPLE_BIASES_PER_LAYER."
        #endif
        #undef MSG12
        #define MSG12 \n- " [2] 0B00100000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You are using (MULTIPLE_BIASES_PER_LAYER)."
        #define MULTIPLE_BIASES_PER_LAYER
    #endif

    #if ((_2_OPTIMIZE bitor 0B11101111) == 0B11111111)
        #undef MSG13
        #define MSG13 \n- " [2] 0B00010000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You are using F() macro for NN.print()."
        #undef F_MACRO
        #define F_MACRO F
    #endif

    #if (((_2_OPTIMIZE bitor 0B11110111) == 0B11111111) or ((_2_OPTIMIZE bitor 0B11111011) == 0B11111111)) 
        #if (((_2_OPTIMIZE bitor 0B11110111) == 0B11111111) and ((_2_OPTIMIZE bitor 0B11111011) == 0B11111111)) 
            #error "You can't use both int16_t and int8_t! use either 16 or 8."
        #endif
        #if defined(USE_64_BIT_DOUBLE)
            #error "You can't USE_64_BIT_DOUBLE precision with USE_INT_QUANTIZATION."
        #endif
        #undef MSG14
        #undef IDFLOAT
        #undef PGM_READ_IDFLOAT 
        #undef MULTIPLY_BY_INT_IF_QUANTIZATION
        #undef CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION
        #if (_2_OPTIMIZE bitor 0B11110111) == 0B11111111
            #define MSG14 \n- " [2] 0B00001000 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using int16_t quantization (NO_BACKPROP yet)."
            #define IDFLOAT int16_t
        #else
            #define MSG14 \n- " [2] 0B00000100 [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using int8_t quantization (NO_BACKPROP yet)."
            #define IDFLOAT int8_t
        #endif
        #define NO_BACKPROP
        #define USE_INT_QUANTIZATION
        #define PGM_READ_IDFLOAT pgm_read_ ## IDFLOAT

        IDFLOAT PGM_READ_IDFLOAT(const IDFLOAT* address) {
            IDFLOAT result;
            memcpy_P(&result, address, sizeof(IDFLOAT));
            return result;
        }

        // FLOAT RANGE = (100.0) - (-100.0) | MAX - MIN
        // INT   RANGE = (32767) - (-32768) | MAX - MIN
        #if (_2_OPTIMIZE bitor 0B11110111) == 0B11111111
            #if !defined(Q_FLOAT_RANGE)
                #define Q_FLOAT_RANGE 200.0
            #endif
            #define Q_INT_RANGE 65535
        #else
            #if !defined(Q_FLOAT_RANGE)
                #define Q_FLOAT_RANGE 51.0
            #endif
            #define Q_INT_RANGE 255
        #endif
        #define MULTIPLY_BY_INT_IF_QUANTIZATION * (Q_FLOAT_RANGE/Q_INT_RANGE)

        #define CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(value) value
    #endif

    #if ((_2_OPTIMIZE bitor 0B11111101) == 0B11111111)
        #undef MSG15
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            #error "You don't have to define both _1_ 0B00000100 (REDUCE_RAM_STATIC_REFERENCE) and _2_ 0B00000010 (REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)."
        #endif
        #define MSG15 \n- " [2] 0B00000010 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] If single NN object, use: _1_OPTIMIZE 0B00000100 instead."
        #define REDUCE_RAM_STATIC_REFERENCE
        #define REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS
    #endif
#endif

// Disable SIMD parallel processing if double-precision or int-quntization is enabled
#if defined(CONFIG_IDF_TARGET_ESP32S3) || defined(USE_ESP_SIMD)
    #if defined(USE_64_BIT_DOUBLE)
        #undef MSG7
        #define MSG7 \n- " [1] 0B00000001 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] SIMD disabled, there is no support when double precision."
    #elif defined(USE_INT_QUANTIZATION)
        #undef MSG7
        #define MSG7 \n- " [2] 0B00001000 [ⓘ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] SIMD disabled, there is no support for USE_INT_QUANTIZATION."
    #else
        #define ESP_SUPPORTS_SIMD
        #include "esp_dsp.h"
    #endif
#endif

// REMINDER DO NOT UNCOMMENT THIS!!!!!! BECAUSE IT WILL RESULT ON ESP32-C3 NOT COMPILING WITH USE_PROGMEM or USE_INTERNAL_EEPROM AT ALL | i keep it here as a future reminder
// #if defined(ESP_SUPPORTS_SIMD) and (defined(USE_PROGMEM) or defined(USE_INTERNAL_EEPROM))
//     #error "There's no support for SIMD use with USE_PROGMEM or USE_INTERNAL_EEPROM yet."
// #endif

#define ACT1  0
#define ACT2  0
#define ACT3  0
#define ACT4  0
#define ACT5  0
#define ACT6  0
#define ACT7  0
#define ACT8  0
#define ACT9  0
#define ACT10 0
#define ACT11 0
#define ACT12 0
#define ACT13 0
#define ACT14 0
// Custom Activation Fuctions
#define CACT1 0
#define CACT2 0
#define CACT3 0
#define CACT4 0
#define CACT5 0

// Custom Activation Fuctions Definitions (eg. DFLOAT CUSTOM_AFX(...);)
#define CUSTOM_AF1_DEFINITION
#define CUSTOM_AF2_DEFINITION
#define CUSTOM_AF3_DEFINITION
#define CUSTOM_AF4_DEFINITION
#define CUSTOM_AF5_DEFINITION

#define CUSTOM_DF1_DEFINITION
#define CUSTOM_DF2_DEFINITION
#define CUSTOM_DF3_DEFINITION
#define CUSTOM_DF4_DEFINITION
#define CUSTOM_DF5_DEFINITION

// STR(AX) | pragma message | A = Activation | AL = All | CA = Custom Activation
#define A1 
#define A2 
#define A3 
#define A4 
#define A5 
#define A6 
#define A7
#define A8
#define A9 
#define A10 
#define A11
#define A12
#define A13
#define A14
#define AL

#define CA1
#define CA2
#define CA3
#define CA4
#define CA5

// NB = NO BACKPROP | CSTA = Custom Activation message | NB_CA5 = NB message for CAs
#define NB_CA1 
#define NB_CA2 
#define NB_CA3 
#define NB_CA4 
#define NB_CA5

#define CSTA
#define NB


#if defined(Sigmoid) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A1
    #undef ACT1
    #undef Sigmoid
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT1 1
    #define ACTIVATION 
    #define ACTIVATION_FUNCTION Sigmoid
    #define Sigmoid Sigmoid
    #define A1 |> Sigmoid 
#endif
#if defined(Tanh) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A2
    #undef ACT2
    #undef Tanh
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT2 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Tanh
    #define Tanh Tanh
    #define A2 |> Tanh
#endif
#if defined(ReLU) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A3
    #undef ACT3
    #undef ReLU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT3 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION ReLU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
    #define ReLU ReLU
    #define A3 |> ReLU 
#endif
#if defined(LeakyELU) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A4
    #undef ACT4
    #undef LeakyELU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT4 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION LeakyELU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
    #define LeakyELU LeakyELU
    #define A4 |> LeakyELU 
#endif
#if defined(ELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A5
    #undef ACT5
    #undef ELU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT5 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION ELU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
    #define ELU ELU
    #define A5 |> ELU 
#endif
#if defined(SELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A6
    #undef ACT6
    #undef SELU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT6 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION SELU
    #define SELU SELU
    #define A6 |> SELU
#endif
#if defined(Softmax)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A7
    #undef ACT7
    #undef Softmax
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT7 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Softmax
    #define Softmax Softmax
    #define A7 |> Softmax
#endif
#if defined(Identity)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef A8
    #undef ACT8
    #undef Identity
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT8 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Identity
    #define Identity Identity
    #define A8 |> Identity
#endif
#if defined(BinaryStep) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A9
    #undef ACT9
    #undef BinaryStep
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT9 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION BinaryStep
    #define BinaryStep BinaryStep
    #define A9 |> BinaryStep 
#endif
#if defined(Softplus)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A10
    #undef ACT10
    #undef Softplus
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT10 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Softplus
    #define Softplus Softplus
    #define A10 |> Softplus 
#endif
#if defined(SiLU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A11
    #undef ACT11
    #undef SiLU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT11 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION SiLU
    #define SiLU SiLU
    #define A11 |> SiLU 
#endif
#if defined(GELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A12
    #undef ACT12
    #undef GELU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT12 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION GELU
    #define GELU GELU
    #define A12 |> GELU 
#endif
#if defined(Mish)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A13
    #undef ACT13
    #undef Mish
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT13 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Mish
    #define Mish Mish
    #define A13 |> Mish 
#endif
#if defined(Gaussian)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef A14
    #undef ACT14
    #undef Gaussian
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define NO_BACKPROP
    #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
    #define ACT14 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Gaussian
    #define Gaussian Gaussian
    #define A14 |> Gaussian 
#endif

#define CONCATENATE_WITHOUT_SPACE(x, y) CONCATENATE_IMPL(x, y)
#define CONCATENATE_IMPL(x, y) x ## y

#if defined(CUSTOM_AF1)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef CA1
    #undef CSTA 
    #undef CACT1
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef CUSTOM_AF1_DEFINITION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACTIVATION
    #define CUSTOM_AF1_DEFINITION DFLOAT CUSTOM_AF1(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF1)
        #undef CUSTOM_DF1
        #undef CUSTOM_DF1_DEFINITION
        #define CUSTOM_DF1 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF1, Der)
        #define CUSTOM_DF1_DEFINITION DFLOAT CUSTOM_DF1(const float &fx);
    #else
        #define NO_BACKPROP
        #undef NB
        #undef NB_CA1
        #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
        #define NB_CA1 |> CUSTOM_AF1
    #endif
    #define CACT1 1
    #define ACTIVATION_FUNCTION CUSTOM_AF1
    #define CA1 |> CUSTOM_AF1
#endif
#if defined(CUSTOM_AF2)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef CA2
    #undef CSTA 
    #undef CACT2
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef CUSTOM_AF2_DEFINITION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACTIVATION
    #define CUSTOM_AF2_DEFINITION DFLOAT CUSTOM_AF2(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF2)
        #undef CUSTOM_DF2
        #undef CUSTOM_DF2_DEFINITION
        #define CUSTOM_DF2 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF2, Der)
        #define CUSTOM_DF2_DEFINITION DFLOAT CUSTOM_DF2(const DFLOAT &fx);
    #else
        #define NO_BACKPROP
        #undef NB
        #undef NB_CA2
        #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
        #define NB_CA2 |> CUSTOM_AF2
    #endif
    #define CACT2 1
    #define ACTIVATION_FUNCTION CUSTOM_AF2
    #define CA2 |> CUSTOM_AF2
#endif
#if defined(CUSTOM_AF3)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef CA3
    #undef CSTA 
    #undef CACT3
    #undef ACTIVATION
    #undef CUSTOM_AF3_DEFINITION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACTIVATION
    #define CUSTOM_AF3_DEFINITION DFLOAT CUSTOM_AF3(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF3)
        #undef CUSTOM_DF3
        #undef CUSTOM_DF3_DEFINITION
        #define CUSTOM_DF3 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF3, Der)
        #define CUSTOM_DF3_DEFINITION DFLOAT CUSTOM_DF3(const DFLOAT &fx);
    #else
        #define NO_BACKPROP
        #undef NB
        #undef NB_CA3
        #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
        #define NB_CA3 |> CUSTOM_AF3
    #endif
    #define CACT3 1
    #define ACTIVATION_FUNCTION CUSTOM_AF3
    #define CA3 |> CUSTOM_AF3
#endif
#if defined(CUSTOM_AF4)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef CA4
    #undef CSTA 
    #undef CACT4
    #undef ACTIVATION
    #undef CUSTOM_AF4_DEFINITION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACTIVATION
    #define CUSTOM_AF4_DEFINITION DFLOAT CUSTOM_AF4(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF4)
        #undef CUSTOM_DF4
        #undef CUSTOM_DF4_DEFINITION
        #define CUSTOM_DF4 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF4, Der)
        #define CUSTOM_DF4_DEFINITION DFLOAT CUSTOM_DF4(const DFLOAT &fx);
    #else
        #define NO_BACKPROP
        #undef NB
        #undef NB_CA4
        #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
        #define NB_CA4 |> CUSTOM_AF4
    #endif
    #define CACT4 1
    #define ACTIVATION_FUNCTION CUSTOM_AF4
    #define CA4 |> CUSTOM_AF4
#endif
#if defined(CUSTOM_AF5)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef CA5
    #undef CSTA 
    #undef CACT5
    #undef ACTIVATION
    #undef CUSTOM_AF5_DEFINITION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACTIVATION
    #define CUSTOM_AF5_DEFINITION DFLOAT CUSTOM_AF5(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF5)
        #undef CUSTOM_DF5
        #undef CUSTOM_DF5_DEFINITION
        #define CUSTOM_DF5 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF5, Der)
        #define CUSTOM_DF5_DEFINITION DFLOAT CUSTOM_DF5(const DFLOAT &fx);
    #else
        #define NO_BACKPROP
        #undef NB
        #undef NB_CA5
        #define NB | 𝗡𝗢_𝗕𝗔𝗖𝗞𝗣𝗥𝗢𝗣 SUPPORT FOR:
        #define NB_CA5 |> CUSTOM_AF5
    #endif
    #define CACT5 1
    #define ACTIVATION_FUNCTION CUSTOM_AF5
    #define CA5 |> CUSTOM_AF5
#endif


#define NUM_OF_USED_ACTIVATION_FUNCTIONS (ACT1 + ACT2 + ACT3 + ACT4 + ACT5 + ACT6 + ACT7 + ACT8 + ACT9 + ACT9 + ACT10 + ACT11 + ACT12 + ACT13 + ACT14 + CACT1 + CACT2 + CACT3 + CACT4 + CACT5)


#if !defined(ACTIVATION)
    #if defined(ACTIVATION__PER_LAYER)
        // ACTIVATE ALL FUNCTIONS
        #define NO_BACKPROP
        #define ALL_ACTIVATION_FUNCTIONS
        #define AL |> "(ALL_ACTIVATION_FUNCTIONS)"
        #undef NUM_OF_USED_ACTIVATION_FUNCTIONS
        #define NUM_OF_USED_ACTIVATION_FUNCTIONS (14 + CACT1 + CACT2 + CACT3 + CACT4 + CACT5)
        #undef MSG10
        #define MSG10 \n- "////////////// [⚠] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed With (ALL_ACTIVATION_FUNCTIONS)."
    #else
        //ENABLE DEFAULT ACTIVATION FUNCTION
        // i will also create a mechanism to show #error if more than one is defined with B opperations?
        #undef A1
        #undef Sigmoid
        #define DEFAULT_ACTIVATION_FUNCTION
        #define ACTIVATION //Sigmoid default but for more than one you must declare it
        #define ACTIVATION_FUNCTION Sigmoid
        #define Sigmoid Sigmoid
        #define A1 |> Sigmoid 
    #endif
#endif


#define MAKE_FUN_NAME1(actname,value) actname(value)
#define MAKE_FUN_NAME2(actname,value) actname ## Der(value)

#define ACTIVATE_WITH(actname,value) MAKE_FUN_NAME1(actname,value)
#define DERIVATIVE_OF(actname,value) MAKE_FUN_NAME2(actname,value)


//LOSS | If there's no Loss function definition and no DISABLE_MSE definition, define the Default  | MEAN_SQUARED_ERROR = Default
#if !defined(CATEGORICAL_CROSS_ENTROPY) and !defined(BINARY_CROSS_ENTROPY) and !defined(MEAN_SQUARED_ERROR) and !defined(DISABLE_MSE)
    #define  DEFAULT_LOSS
#endif


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define INFORMATION LOVE __NN_VERSION__ MSG0 MSG1 MSG2 MSG3 MSG4 MSG5 MSG6 MSG7 MSG8 MSG9 MSG10 MSG11 MSG12 MSG13 MSG14 MSG15 \n\n 𝗨𝗦𝗜𝗡𝗚 [ƒx] AL A1 A2 A3 A4 A5 A6 A7 A8 A9 A10 A11 A12 A13 A14 CSTA CA1 CA2 CA3 CA4 CA5 |~|\n\n NB A9 A10 A11 A12 A13 A14 NB_CA1 NB_CA2 NB_CA3 NB_CA4 NB_CA5
#pragma message( STR(INFORMATION) )

// i might change static variables to plain variables and just pass a pointer from outer class?
class NeuralNetwork
{
private:

    #if defined(USE_INTERNAL_EEPROM)
        unsigned int address = 0;
        #if defined(ACTIVATION__PER_LAYER)
            byte F1; // first activation function only for use in FdF_Individual_iEEPROM
        #endif
    #endif
    int Individual_Input = 0;
    bool isAllocdWithNew = true;  // If weights and biases are allocated with new, for the destractor later | TODO: #if !defined(USE_PROGMEM) and etc. in constructors
    bool FIRST_TIME_FDFp = false; // determines if there are trashes left in last outputs .
    const DFLOAT *_inputs;        // Pointer to primary/first Inputs Array from Sketch    .
                                  // (Used for backpropagation)                           .

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        bool isAlreadyLoadedOnce = false; // Determines if load() function has been called more than once, so the next time it will clean | I mean... if you use sd library then you have a spare byte right?
    #endif

    class Layer
    {
    public:
        
        #if !defined(REDUCE_RAM_STATIC_REFERENCE)
            NeuralNetwork *me;
        #endif

        unsigned int _numberOfInputs;  // # of neurons in the previous layer.
        unsigned int _numberOfOutputs; // # of neurons in the current  layer.

        #if !defined(NO_BIAS)
            IS_CONST IDFLOAT *bias;     // bias    of this     layer  | or biases if MULTIPLE_BIASES_PER_LAYER enabled | Please do not wrap it into #ifdef USE_INTERNAL_EEPROM because it is being used when FdF_Individual_iEEPROM
        #endif
        DFLOAT *outputs;               // outputs of this     layer  [1D Array] pointers.
        
        //#if defined(REDUCE_RAM_WEIGHTS_LVL1)
        //    IDFLOAT *weights;         // weights of this     layer  [1D Array] pointers.                             #(used if     #REDUCE_RAM_WEIGHTS_LVL1   defined)         
        //#endif
        #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
            IS_CONST IDFLOAT **weights; // weights of this     layer  [2D Array] pointers.                             #(used if NOT #REDUCE_RAM_WEIGHTS_COMMON defined) 
        #endif
        #if !defined(NO_BACKPROP)
            DFLOAT *preLgamma;         // gamma   of previous layer  [1D Array] pointers.
        #endif

        // Default Constractor                                                         .
        //      #0 Constructor                                                         .
        //      #1 Constructor With default/("probably") preptained, weights and biases.
        Layer() {};
        #if !defined(USE_PROGMEM) 
            // ^^^^^ I keep this USE_PROGMEM instead of NO_BACKPROP because that way if I add a NeuralNetwork::feedforward_PROGMEM, with -fpermisive someone will be able to use both RAM-NN and PROGMEM-NN at the same time
            Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, NeuralNetwork * const NN = NULL); // #0  | defined(NO_BIAS) is there 2024-03-02
        #endif

        #if defined(NO_BIAS)
            Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Weights, NeuralNetwork * const NN = NULL); // #1  #(used if NOT #REDUCE_RAM_WEIGHTS_LVL2 defined)
            Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, bool has_no_bias, NeuralNetwork * const NN = NULL); // has_no_bias is something the compiler 99% will optimize\remove | This is just a trick for distinguishing the constructors from the one who auto-generates the weights
        #else
            Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Bias, NeuralNetwork * const NN = NULL); //                                       #(used if     #REDUCE_RAM_WEIGHTS_LVL2 defined)
            Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Weights, IS_CONST IDFLOAT *default_Bias, NeuralNetwork * const NN = NULL); // #1  #(used if NOT #REDUCE_RAM_WEIGHTS_LVL2 defined)
        #endif


        void FeedForward_Individual(const DFLOAT &input, const int &j);
        void FdF_Individual_PROGMEM(const DFLOAT &input, const int &j);
        #if defined(USE_INTERNAL_EEPROM)
            void FdF_Individual_iEEPROM(const DFLOAT &input, const int &j);
        #endif

        void FeedForward(const DFLOAT *inputs); // Calculates the outputs() of layer.
        void FdF_PROGMEM(const DFLOAT *inputs);
        #if defined(USE_INTERNAL_EEPROM)
            void FdF_IN_EEPROM(const DFLOAT *inputs);
        #endif

        #if !defined (NO_BACKPROP)
            void BackPropOutput(const DFLOAT *_expected_, const DFLOAT *inputs);
            void BackPropHidden(const Layer *frontLayer, const DFLOAT *inputs);
        #endif


        // "Extra Math"
        DFLOAT erf(DFLOAT x);

        //if i acctually consider using other complicated activation functions i might need to think again about the before_Activation_output Array [...]
        DFLOAT Sigmoid    (const DFLOAT &x ); // Sigmoid Activation Function 1/(1+e^(-x)) .
        DFLOAT SigmoidDer (const DFLOAT &fx); // Derivative of Sigmoid Activation Function.
        
        DFLOAT Tanh       (const DFLOAT &x ); 
        DFLOAT TanhDer    (const DFLOAT &fx); 

        DFLOAT ReLU       (const DFLOAT &x ); 
        DFLOAT ReLUDer    (const DFLOAT &fx); // x is also fx on ReLU

        DFLOAT LeakyELU   (const DFLOAT &x );
        DFLOAT LeakyELUDer(const DFLOAT &fx); 

        DFLOAT ELU        (const DFLOAT &x ); // α = 1 
        DFLOAT ELUDer     (const DFLOAT &fx); 
        
        DFLOAT SELU       (const DFLOAT &x ); // Maybe use https://stackoverflow.com/a/42264773/11465149
        DFLOAT SELUDer    (const DFLOAT &fx); 

        void   Softmax    ();
        DFLOAT SoftmaxSum (const DFLOAT &x ); // returns exp(outputs[i] + (*bias)) to each output and then sums it into sumOfSoftmax 
        DFLOAT SoftmaxDer (const DFLOAT &fx);

        DFLOAT Identity   (const DFLOAT &x );
        DFLOAT IdentityDer(const DFLOAT &x );

        // Custom Activation Fuctions Definitions (eg. DFLOAT CUSTOM_AFX(...);)
        CUSTOM_AF1_DEFINITION
        CUSTOM_AF2_DEFINITION
        CUSTOM_AF3_DEFINITION
        CUSTOM_AF4_DEFINITION
        CUSTOM_AF5_DEFINITION

        CUSTOM_DF1_DEFINITION
        CUSTOM_DF2_DEFINITION
        CUSTOM_DF3_DEFINITION
        CUSTOM_DF4_DEFINITION
        CUSTOM_DF5_DEFINITION

        // NO_BACKPROP support
        DFLOAT BinaryStep (const DFLOAT &x );
        DFLOAT Softplus   (const DFLOAT &x );
        DFLOAT SiLU       (const DFLOAT &x );
        DFLOAT GELU       (const DFLOAT &x );
        DFLOAT Mish       (const DFLOAT &x );
        DFLOAT Gaussian   (const DFLOAT &x );
        

        #if defined(USE_INTERNAL_EEPROM)
            void print_INTERNAL_EEPROM();
        #endif
        void print_PROGMEM();
        void print();
    };  


public:
    //just like "static IDFLOAT *wights" [...]  i might have a function to switch? | 2024-05-28 07:21:09 PM UPDATE: not sure what I meant back then... comment was moved here since `inline` change (this date), see also issue #35
    // this is the part where we declare an array-of-pointers-to-(activation and derivative) functions 
    #if defined(ACTIVATION__PER_LAYER)
        typedef DFLOAT (Layer::*method_function) (const DFLOAT &);
        static const method_function activation_Function_ptrs[NUM_OF_USED_ACTIVATION_FUNCTIONS];
        #if !defined(NO_BACKPROP)
            static const method_function derivative_Function_ptrs[NUM_OF_USED_ACTIVATION_FUNCTIONS];
        #endif  
        //https://stackoverflow.com/a/31708674/11465149
        //http://www.cs.technion.ac.il/users/yechiel/c++-faq/array-memfnptrs.html // ??? [x]
    #endif


    #if defined(REDUCE_RAM_STATIC_REFERENCE)
        static NeuralNetwork *me;
    #endif

    // Guessing that BackProp wont be called more than once excactly after a feedforward call, IF REDUCE_RAM_WEIGHTS_LVL2  else i should have had a temp weights-size variable or something
    // need to add a function for those who want to switch/redirect the pointer to a deferent weight Array... maybe? ... Why not?!? lol.
    // issues with multiple NNs too ...
    #if defined(REDUCE_RAM_WEIGHTS_LVL2) 
        IS_CONST IDFLOAT *weights; //                              pointer to sketch's        Array of Weights.    #(used if     #REDUCE_RAM_WEIGHTS_LVL2 defined)
        int i_j = 0; 
    #endif   

    #if defined(ACTIVATION__PER_LAYER)
        unsigned int AtlayerIndex; // who 's gonna make a network with more than 255 layers :P ?!?!? but anyways i will use int or i will add byte too, using a property definition with bunch of other things like this for max optimization ... lol
        byte *ActFunctionPerLayer; // lets be realistic... byte because. xD
    #endif

    // #5 This is the sum of the exp(outputs) of the previous layer (for All and each layer)
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
        DFLOAT sumOfSoftmax = 0;
    #endif

    // no negative values allowed, (just saying..)
    // Alphas and Lamdas of Activation Functions | #6 MACROS.
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyELU)
        DFLOAT AlphaLeaky = 0.01   ;
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
        DFLOAT AlphaSELU  = 1.6733 ; 
        DFLOAT LamdaSELU  = 1.0507 ;
    #endif        
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
        DFLOAT AlphaELU   = 1      ;
    #endif


    Layer *layers;                   // layers in the network [1D Array].
    unsigned int numberOflayers = 0; // Number of layers.


    // unsigned float doesn't exist..? lol
    #if !defined (NO_BACKPROP)
        DFLOAT LearningRateOfWeights = 0.33 ; // Learning Rate of Weights.
        #if !defined(NO_BIAS)
            DFLOAT LearningRateOfBiases  = 0.066; // Learning Rate of Biases .
        #endif
    #endif
    

    // LOSS VARIABLES | V Because #6
    #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
        DFLOAT sumSquaredError              = 0;  
        DFLOAT MeanSqrdError                = 0; 
    #endif
    #if defined(CATEGORICAL_CROSS_ENTROPY)
        DFLOAT sumOfCategoricalCrossEntropy = 0;  
        DFLOAT CategoricalCrossEntropy      = 0; 
    #endif
    #if defined(BINARY_CROSS_ENTROPY)
        DFLOAT sumOfBinaryCrossEntropy      = 0;  
        DFLOAT BinaryCrossEntropy           = 0; 
    #endif


    void pdestract(); // partial destaction
    ~NeuralNetwork(); // Destructor.

    NeuralNetwork();
    #if defined(USE_INTERNAL_EEPROM)
        NeuralNetwork(unsigned int address);
    #endif
    #if !defined(NO_BACKPROP)
        NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer = NULL);                                              // #0
        #if defined(NO_BIAS)
            NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const DFLOAT &LRw, byte *_ActFunctionPerLayer = NULL);          // #0
        #else
            NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const DFLOAT &LRw, const DFLOAT &LRb, byte *_ActFunctionPerLayer = NULL);          // #0
        #endif
    #endif
    #if defined(NO_BIAS)
        NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer = NULL); // #1
    #else
        NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights, IS_CONST IDFLOAT *default_Bias, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer = NULL); // #1
    #endif
    // NeuralNetwork(const unsigned int *layer_, const PROGMEM DFLOAT *default_Weights, const PROGMEM DFLOAT *default_Bias, const unsigned int &NumberOflayers , bool isProgmem); // isProgmem (because of the Error #777) ? i get it in a way but ..
    
    void  reset_Individual_Input_Counter();
    DFLOAT *FeedForward_Individual(const DFLOAT &input);
    DFLOAT *FeedForward(const DFLOAT *inputs); // Moves Calculated outputs as inputs to next layer.
    
    //LOSS FUNCTIONS +common
    DFLOAT getMeanSqrdError           (unsigned int inputsPerEpoch); 
    DFLOAT getBinaryCrossEntropy      (unsigned int inputsPerEpoch); 
    DFLOAT getCategoricalCrossEntropy (unsigned int inputsPerEpoch); 
    DFLOAT loss  (DFLOAT &sum, DFLOAT &loss, unsigned int batch_size);        

    #if !defined (NO_BACKPROP)
        void BackProp(const DFLOAT *expected);    // BackPropopagation - (error, delta-weights, etc.).
    #endif

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        NeuralNetwork(String file);
        bool save(String file); // TODO: load\Save from RAM and PROGMEM, EEPROM, FRAM and other medias 
        bool load(String file);
    #endif
    #if defined(INCLUDES_EEPROM_H)
        unsigned int save(unsigned int atAddress); // EEPROM
    #endif
    // unsigned int save(FRAM fram, unsigned int atAddress); // FRAM https://www.arduino.cc/reference/en/libraries/fram_i2c/
    
    void print();
     
};
#if defined(REDUCE_RAM_STATIC_REFERENCE)
    NeuralNetwork *NeuralNetwork::me;
#endif
    


//=======================================================================================================================================================================
//NeuralNetwork.cpp
//=======================================================================================================================================================================
#pragma region NeuralNetwork.cpp
    NeuralNetwork::NeuralNetwork() {
        isAllocdWithNew = false;
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif
    }

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        NeuralNetwork::NeuralNetwork(String file){
            isAllocdWithNew = false;
            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif
            load(file);
        }
    #endif
    

    void NeuralNetwork::pdestract()
    {
        #if !defined(USE_PROGMEM) && !defined(USE_INTERNAL_EEPROM)
            if (isAllocdWithNew){ // Because of undefined behavior in some MCUs like ESP32-C3
                for (int i = 0; i < numberOflayers; i++)
                {
                    #if !defined(REDUCE_RAM_WEIGHTS_COMMON) // && !defined(USE_PROGMEM)
                        for (int j = 0; j < layers[i]._numberOfOutputs; j++) // because of this i wont make _numberOfOutputs/inputs private :/ or maybe.. i ll see... or i will change them to const* ... what? i've just read it again lol
                        {
                            delete[] layers[i].weights[j];
                            layers[i].weights[j] = NULL;    
                        }
                    #endif

                    // #if !defined(USE_PROGMEM)
                    #if !defined(NO_BIAS)
                        delete layers[i].bias;
                        layers[i].bias = NULL;
                    #endif
                    // #endif

                    #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                        delete[] layers[i].outputs;
                        layers[i].outputs = NULL;
                    #endif

                    /*
                    #if defined(REDUCE_RAM_WEIGHTS_LVL1) // && !defined(USE_PROGMEM) // no need for progmem condition because progmem is never going to be initialized with new
                        delete[] layers[i].weights;
                        layers[i].weights = NULL;
                    #endif
                    */
                }

                #if defined(REDUCE_RAM_WEIGHTS_LVL2) // && !defined(USE_PROGMEM) // no need for progmem condition because progmem is never going to be initialized with new
                    delete weights;
                    weights = NULL;
                #endif
            }else{
                #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                    for (int i = 0; i < numberOflayers; i++){
                        delete[] layers[i].outputs;
                        layers[i].outputs = NULL;
                    }
                #endif
            }
        #elif !defined(REDUCE_RAM_DELETE_OUTPUTS)
            for (int i = 0; i < numberOflayers; i++){
                delete[] layers[i].outputs;
                layers[i].outputs = NULL;
            }
        #endif

        #if defined(ACTIVATION__PER_LAYER) && defined(SUPPORTS_SD_FUNCTIONALITY) 
            if (isAlreadyLoadedOnce){
                delete[] ActFunctionPerLayer;
                ActFunctionPerLayer = NULL;
            }
        #endif  

        if (numberOflayers !=0){
            delete[] layers;
            layers = NULL; // 18/5/2019
        }
    }
    NeuralNetwork::~NeuralNetwork() { pdestract(); } 



    #if defined(NO_BIAS)
        NeuralNetwork::NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer)
    #else
        NeuralNetwork::NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights, IS_CONST IDFLOAT *default_Bias, const unsigned int &NumberOflayers, byte *_ActFunctionPerLayer)
    #endif
    {
        isAllocdWithNew = false;
        numberOflayers = NumberOflayers - 1;

        layers = new Layer[numberOflayers]; // there has to be a faster way by alocating memory for example...

        #if defined(ACTIVATION__PER_LAYER)
            ActFunctionPerLayer = _ActFunctionPerLayer;
        #endif  
        
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            weights = default_Weights;
        #else
            unsigned int weightsFromPoint = 0;
        #endif

        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference" | 2024-03-12 04:01:04 PM todo γιατι οπως μου ειχε πει "ενα ροζ συννεφακι": "κανε ενα-ενα τα πραγματα, οχι ολα μαζι..."
            unsigned int biasesFromPoint = 0;
        #endif

        for (int i = 0; i < numberOflayers; i++)
        {
            #if defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                #if defined(NO_BIAS)
                    layers[i] = Layer(layer_[i], layer_[i + 1], HAS_NO_BIAS, this);
                #elif defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Bias[biasesFromPoint],this);
                #else
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Bias[i],this);
                #endif
            #else
                #if defined(NO_BIAS)
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], this);
                #elif defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], &default_Bias[biasesFromPoint],this);
                #else
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], &default_Bias[i],this);
                #endif
                weightsFromPoint += layer_[i] * layer_[i + 1];
            #endif
            #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                biasesFromPoint += layer_[i + 1];
            #endif
            
        }
    }

    #if !defined(NO_BACKPROP)
        #if defined(NO_BIAS)
            NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const DFLOAT &LRw, byte *_ActFunctionPerLayer )
        #else
            NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers, const DFLOAT &LRw, const DFLOAT &LRb,  byte *_ActFunctionPerLayer )
        #endif
        {
            LearningRateOfWeights = LRw; // Initializing the Learning Rate of Weights
            #if !defined(NO_BIAS)
                LearningRateOfBiases = LRb; // Initializing the Learning Rate of Biases
            #endif

            numberOflayers = NumberOflayers - 1;

            layers = new Layer[numberOflayers];

            #if defined(ACTIVATION__PER_LAYER)
                ActFunctionPerLayer = _ActFunctionPerLayer;
            #endif 

            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2) //footprint episis san leksi // TODO: SIMD
                for (int i = 0; i < numberOflayers; i++)
                    i_j += layer_[i] * layer_[i + 1];
                
                weights = new DFLOAT[i_j];
                i_j=0;
            #endif

            for (int i = 0; i < numberOflayers; i++)
            {
                layers[i] =  Layer(layer_[i], layer_[i + 1],this);
            }

        }

        //maybe i will  add one more constructor so i can release memory from feedforward outputs in case i dont want backprop?

        NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers,  byte *_ActFunctionPerLayer )
        {
            numberOflayers = NumberOflayers - 1;

            layers = new Layer[numberOflayers];

            #if defined(ACTIVATION__PER_LAYER)
                ActFunctionPerLayer = _ActFunctionPerLayer;
            #endif 

            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2) //footprint episis san leksi // TODO: SIMD
                for (int i = 0; i < numberOflayers; i++)
                    i_j += layer_[i] * layer_[i + 1];
                
                weights = new DFLOAT[i_j];
                i_j=0;
            #endif

            for (int i = 0; i < numberOflayers; i++)
            {
                layers[i] =  Layer(layer_[i], layer_[i + 1],this);
            }
        }
    #endif

    #if defined(USE_INTERNAL_EEPROM)

        template< typename T >
        T get_EEPROM_value(unsigned int &addr){
            // T val = EEPROM.get(addr,val);
            // addr += sizeof(T);
            // return val;
            // T val;
            // uint8_t *ptr = reinterpret_cast<uint8_t*>(&val);
            // for (int i = 0; i < sizeof(T); ++i, ++addr) {
            //     ptr[i] = EEPROM.read(addr);
            // }
            // return (T)ptr;
            uint8_t ptr[sizeof(T)];
            for (int i = 0; i < sizeof(T); ++i, ++addr) {
                ptr[i] = EEPROM.read(addr);
            }
            return *reinterpret_cast<T*>(ptr);
        }

        //TODO: common get function that adds to address for  EEPROM
        NeuralNetwork::NeuralNetwork(unsigned int addr){
            // isAllocdWithNew = false; // no need because of pdestract #if condition
            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif
            numberOflayers = get_EEPROM_value<unsigned int>(addr);
            layers = new Layer[numberOflayers];

            unsigned int tmp1;
            unsigned int tmp2;
            for (int i = 0; i < numberOflayers; i++){
                layers[i] =  Layer(EEPROM.get(addr,tmp1), EEPROM.get(addr+sizeof(unsigned int),tmp2), this);
                addr += sizeof(unsigned int);
            }
            address = addr + sizeof(unsigned int);
        }
    #endif

    void NeuralNetwork::reset_Individual_Input_Counter() { Individual_Input = 0;}

    DFLOAT *NeuralNetwork::FeedForward_Individual(const DFLOAT &input) 
    {
        #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
            me = this;
        #endif
        #if defined(USE_PROGMEM)
            layers[0].FdF_Individual_PROGMEM(input, Individual_Input);
        #elif defined(USE_INTERNAL_EEPROM)
            unsigned int tmp_addr = address;
            layers[0].FdF_Individual_iEEPROM(input, Individual_Input);
            address = tmp_addr;
        #else
            layers[0].FeedForward_Individual(input, Individual_Input);
        #endif
        Individual_Input++;

        if (Individual_Input == layers[0]._numberOfInputs)
        {
            Individual_Input=0;

            #if defined(USE_INTERNAL_EEPROM)
                #if defined(MULTIPLE_BIASES_PER_LAYER)
                    #if defined(ACTIVATION__PER_LAYER)
                        address += SIZEOF_FX + layers[0]._numberOfOutputs * sizeof(IDFLOAT) + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #else
                        address +=             layers[0]._numberOfOutputs * sizeof(IDFLOAT) + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #endif
                #elif defined(NO_BIAS)
                    #if defined(ACTIVATION__PER_LAYER)
                        address += SIZEOF_FX + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #else
                        address +=           + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #endif
                #else
                    #if defined(ACTIVATION__PER_LAYER)
                        address += SIZEOF_FX + sizeof(IDFLOAT) + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #else
                        address +=           + sizeof(IDFLOAT) + (sizeof(IDFLOAT) * layers[0]._numberOfInputs * layers[0]._numberOfOutputs);
                    #endif
                #endif
            #endif
        
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                if (FIRST_TIME_FDFp == true) // is it the first time ? if not, then delete trashes
                {
                    delete[] layers[numberOflayers - 1].outputs;
                    layers[numberOflayers - 1].outputs = NULL;
                }else{
                    FIRST_TIME_FDFp = true;
                }
            #endif

            for (int i = 1; i < numberOflayers; i++)
            {
                #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
                    sumOfSoftmax = 0; //(in case of USE_ALL...) i won't use if statment for each layer cause an initialization is nothing compared to an if statment  for every loop checking if layer points to Softmax
                #endif
                #if defined(ACTIVATION__PER_LAYER) && !defined(USE_INTERNAL_EEPROM)
                    AtlayerIndex = i;
                #endif  
                #if defined(USE_PROGMEM)
                    layers[i].FdF_PROGMEM(layers[i - 1].outputs);
                #elif defined(USE_INTERNAL_EEPROM)
                    layers[i].FdF_IN_EEPROM(layers[i - 1].outputs);
                #else
                    layers[i].FeedForward(layers[i - 1].outputs);
                #endif
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    delete[] layers[i - 1].outputs;
                    layers[i - 1].outputs = NULL;
                #endif
            }

            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
                sumOfSoftmax = 0; //(in case of USE_ALL...) i won't use if statment for each layer cause an initialization is nothing compared to an if statment  for every loop checking if layer points to Softmax
            #endif
            #if defined(USE_INTERNAL_EEPROM)
                address = tmp_addr;
            #endif
            return  layers[numberOflayers - 1].outputs;
        }

        return NULL;
    }

    DFLOAT *NeuralNetwork::FeedForward(const DFLOAT *inputs)
    {
        _inputs = inputs;

        #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
            me = this;
        #endif
        
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            if (FIRST_TIME_FDFp == true) // is it the first time ? if not, then delete trashes
            {
                delete[] layers[numberOflayers - 1].outputs;
                layers[numberOflayers - 1].outputs = NULL;
            }else{
                FIRST_TIME_FDFp = true;
            }
        #endif

        // Reseting the index to which layer we are back to 0, the 1st layer
        #if defined(ACTIVATION__PER_LAYER)
            AtlayerIndex = 0;
        #endif  
        // resets starting point (could have had a function returning it instead of initializing it on constructor too?)
        #if defined(REDUCE_RAM_WEIGHTS_LVL2) 
            i_j=0;
        #endif
        
        #if defined(USE_PROGMEM)
            layers[0].FdF_PROGMEM(_inputs);
        #elif defined(USE_INTERNAL_EEPROM)
            unsigned int tmp_addr = address;
            layers[0].FdF_IN_EEPROM(_inputs);
        #else
            layers[0].FeedForward(_inputs);
        #endif

        for (int i = 1; i < numberOflayers; i++)
        {
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
                sumOfSoftmax = 0;  //(in case of USE_ALL...) i won't use if statment for each layer cause an initialization is nothing compared to an if statment  for every loop checking if layer points to Softmax
            #endif
            #if defined(ACTIVATION__PER_LAYER)
                AtlayerIndex = i;
            #endif  
            #if defined(USE_PROGMEM)
                layers[i].FdF_PROGMEM(layers[i - 1].outputs);
            #elif defined(USE_INTERNAL_EEPROM)
                layers[i].FdF_IN_EEPROM(layers[i - 1].outputs);
            #else
                layers[i].FeedForward(layers[i - 1].outputs);
            #endif
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                delete[] layers[i - 1].outputs;
                layers[i - 1].outputs = NULL;
            #endif
        }
        #if defined(USE_INTERNAL_EEPROM)
            address = tmp_addr;
        #endif

        return layers[numberOflayers - 1].outputs;
    }



    #if !defined (NO_BACKPROP)
        void NeuralNetwork::BackProp(const DFLOAT *expected)
        {
            /* i dont find any reason of having this if Backprop will never be used more than once imidiatly after once [...] but just in case ... commented .... The same goes for i_j too | Meaning: NN.Backprop(..); \n NN.Backprop(..); without a feedforward in between
            #if defined(ACTIVATION__PER_LAYER)
                AtlayerIndex = numberOflayers - 1;
            #endif  
            */

            #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
                me = this;
            #endif

            layers[numberOflayers - 1].BackPropOutput(expected, layers[numberOflayers - 2].outputs); // issue because backprop einai anapoda ta weights [Fixed]

            for (int i = numberOflayers - 2; i > 0; i--)
            {
                layers[i].BackPropHidden(&layers[i + 1], layers[i - 1].outputs);
                delete[] layers[i + 1].preLgamma;
                layers[i + 1].preLgamma = NULL; // 18/5/2019
            }

            layers[0].BackPropHidden(&layers[1], _inputs);

            delete[] layers[1].preLgamma;
            delete[] layers[0].preLgamma;

            layers[0].preLgamma = NULL;
            layers[1].preLgamma = NULL;
        }
    #endif


    //LOSS_FUNCTIONS
    //inputsPerEpoch = batch size
    #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
        DFLOAT NeuralNetwork::getMeanSqrdError          (unsigned int inputsPerEpoch) { return loss(sumSquaredError, MeanSqrdError, inputsPerEpoch)                        ;}
    #endif
    #if defined(CATEGORICAL_CROSS_ENTROPY)
        DFLOAT NeuralNetwork::getCategoricalCrossEntropy(unsigned int inputsPerEpoch) { return loss(sumOfCategoricalCrossEntropy, CategoricalCrossEntropy, inputsPerEpoch) ;}
    #endif
    #if defined(BINARY_CROSS_ENTROPY)
        DFLOAT NeuralNetwork::getBinaryCrossEntropy     (unsigned int inputsPerEpoch) { return loss(sumOfBinaryCrossEntropy, BinaryCrossEntropy, inputsPerEpoch)           ;}
    #endif

    DFLOAT NeuralNetwork::loss(DFLOAT &sum, DFLOAT &loss, unsigned int batch_size)
    {
        loss = (sum/(layers[numberOflayers - 1]._numberOfOutputs * batch_size));
        sum = 0; // resets the value of the sum-variable that passes by reference to 0
        return loss;
    }
    

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        bool NeuralNetwork::save(String file) 
        {
            File myFile = SD.open(file, SD_NN_WRITE_MODE);
            if (myFile){
                int totalNumOfWeights = 0;
                myFile.println("        "); // yes... it needs those spaces
                myFile.println(numberOflayers+1); 
                for(int n=0; n<numberOflayers; n++){
                    #if defined(ACTIVATION__PER_LAYER)
                        myFile.println(ActFunctionPerLayer[n]); 
                    #endif
                    myFile.println(layers[n]._numberOfInputs); 
                    myFile.println(layers[n]._numberOfOutputs); 
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(*layers[n].bias)); 
                    #endif
                    for(int i=0; i<layers[n]._numberOfOutputs; i++){
                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                            myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(layers[n].bias[i])); 
                        #endif
                        for(int j=0; j<layers[n]._numberOfInputs; j++){
                            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(weights[totalNumOfWeights])); // I would had used i_j but I have totalNumOfWeights so... :)
                            #else
                                myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(layers[n].weights[i][j])); 
                            #endif
                            totalNumOfWeights++;
                        }
                    }
                }
                myFile.seek(0); // NOTE: that's SuS depending on the defined SD library one might choose | in relation to the myFile.println("        "); and print below | espressif's ESP32 SD-FS implementation uses default seek mode to 	SEEK_SET – It moves file pointer position to the beginning of the file.
                myFile.print(totalNumOfWeights);
                myFile.close();
            }
            return false;
        }


        bool NeuralNetwork::load(String file)
        {
            if (numberOflayers !=0 || isAlreadyLoadedOnce) // to prevent undefined delete[] and memory leaks for the sake of reloading as many times as you want :)
                pdestract();

            File myFile = SD.open(file);
            if (myFile) {
                isAllocdWithNew = true;

                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    int count_ij = 0;
                    i_j = 0;
                    weights = new IDFLOAT[myFile.readStringUntil('\n').toInt()];
                #else
                    myFile.readStringUntil('\n').toInt(); // Skipping line
                #endif

                numberOflayers = myFile.readStringUntil('\n').toInt() - 1;
                layers = new Layer[numberOflayers]; 

                #if defined(ACTIVATION__PER_LAYER)
                    isAlreadyLoadedOnce = true;
                    ActFunctionPerLayer = new byte[numberOflayers];
                #endif  

                #if defined(REDUCE_RAM_STATIC_REFERENCE)
                    me = this;
                #endif

                unsigned int tmp_layerInputs;
                unsigned int tmp_layerOutputs;

                #if !defined(NO_BIAS)
                    IDFLOAT *tmp_bias;
                #endif
                #if !defined(USE_INT_QUANTIZATION)
                    LLONG tmp;
                #else
                    IDFLOAT tmp; // any intX_t
                #endif

                for (int i = 0; i < numberOflayers; i++)
                {
                    #if defined(ACTIVATION__PER_LAYER)
                        ActFunctionPerLayer[i] = myFile.readStringUntil('\n').toInt();
                    #endif      
                    tmp_layerInputs  = myFile.readStringUntil('\n').toInt();
                    tmp_layerOutputs = myFile.readStringUntil('\n').toInt();
                    #if !defined(NO_BIAS)
                        #if !defined(MULTIPLE_BIASES_PER_LAYER)
                            #if !defined(USE_INT_QUANTIZATION)
                                tmp       = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                tmp_bias  = new DFLOAT;
                                *tmp_bias = *((DFLOAT*)(&tmp));
                            #else
                                tmp_bias  = new IDFLOAT;
                                *tmp_bias = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                            #endif
                        #else
                            tmp_bias  = new IDFLOAT[tmp_layerOutputs];
                        #endif
                    #endif

                    #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                        #if defined(NO_BIAS)
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS, this);
                        #else
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias, this);
                        #endif
                        layers[i].weights = new IDFLOAT *[tmp_layerOutputs];
                    #endif

                    #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                        for(int j=0; j<tmp_layerOutputs; j++){
                            #if defined(MULTIPLE_BIASES_PER_LAYER)
                                #if !defined(USE_INT_QUANTIZATION)
                                    tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                    layers[i].bias[j] = *((DFLOAT*)(&tmp));
                                #else
                                    layers[i].bias[j] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                #endif
                            #endif
                            layers[i].weights[j] = new IDFLOAT[tmp_layerInputs];
                            for(int k=0; k<tmp_layerInputs; k++){
                                #if !defined(USE_INT_QUANTIZATION)
                                    tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                    layers[i].weights[j][k] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                #else
                                    layers[i].weights[j][k] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                #endif
                            }
                        }
                    #else // I won't elif here cause I want to have a clear image of the "division" below
                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                            for(int j=0; j<tmp_layerOutputs; j++){
                                #if !defined(USE_INT_QUANTIZATION)
                                    tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                    tmp_bias[j] = *((DFLOAT*)(&tmp));
                                #else
                                    tmp_bias[j] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                #endif
                                for(int k=0; k<tmp_layerInputs; k++){
                                    #if !defined(USE_INT_QUANTIZATION)
                                        tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                        weights[count_ij] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                    #else
                                        weights[count_ij] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                    #endif
                                    count_ij++;
                                }
                            }
                        #else
                            for(int j=0; j<tmp_layerInputs * tmp_layerOutputs; j++){
                                #if !defined(USE_INT_QUANTIZATION)
                                    tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                    weights[count_ij] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                #else
                                    weights[count_ij] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                #endif
                                count_ij++;
                            }
                        #endif
                    #endif
                    #if defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                        #if defined(NO_BIAS)
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS, this);
                        #else
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias, this);
                        #endif
                    #endif
                }
                myFile.close();
                return true;
              }
            return false;
        }
    #endif
    #if defined(INCLUDES_EEPROM_H)
        template< typename T >
        void put_EEPROM_value(unsigned int &addr, T val){
            EEPROM.put(addr, val);
            addr += sizeof(T);
        }

        unsigned int NeuralNetwork::save(unsigned int atAddress){
            unsigned int tmp_addr = 0;
            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                i_j = 0;
            #endif
            put_EEPROM_value(atAddress, numberOflayers);
            tmp_addr = atAddress;
            atAddress += (numberOflayers+1)*sizeof(unsigned int);
            for(int n=0; n<numberOflayers; n++){
                put_EEPROM_value(tmp_addr, layers[n]._numberOfInputs);
                #if defined(ACTIVATION__PER_LAYER)
                    put_EEPROM_value(atAddress, ActFunctionPerLayer[n]);
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    put_EEPROM_value(atAddress, *layers[n].bias);
                #endif
                for(int i=0; i<layers[n]._numberOfOutputs; i++){
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        put_EEPROM_value(atAddress, layers[n].bias[i]);
                    #endif
                    for(int j=0; j<layers[n]._numberOfInputs; j++){
                        #if !defined(REDUCE_RAM_WEIGHTS_LVL2)
                            put_EEPROM_value(atAddress, layers[n].weights[i][j]);
                        #else
                            put_EEPROM_value(atAddress, weights[i_j]);
                            i_j++;
                        #endif
                    }
                }
            }
            put_EEPROM_value(tmp_addr, layers[numberOflayers-1]._numberOfOutputs);
            return atAddress;
        }
    #endif

    //If Microcontroller isn't one of the .._No_Common_Serial_Support Series then it compiles the code below.
    #if !defined(As__No_Common_Serial_Support) // then Compile:
    void NeuralNetwork::print()
    {
        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            i_j=0; 
        #endif
        #if defined(USE_INTERNAL_EEPROM)
            unsigned int tmp_addr = address;
        #endif

        Serial.println();
        Serial.println(F_MACRO("----------------------"));

        for (int i = 0; i < numberOflayers; i++)
        {
            #if defined(ACTIVATION__PER_LAYER) && !defined(USE_INTERNAL_EEPROM)  // not def USE_INTERNAL_EEPROM, because AtlayerIndex is not needed
                AtlayerIndex = i;
            #endif  
            #if defined(USE_PROGMEM)
                layers[i].print_PROGMEM();
            #elif defined(USE_INTERNAL_EEPROM)
                layers[i].print_INTERNAL_EEPROM();
            #else
                layers[i].print();
            #endif
        }
        #if defined(USE_INTERNAL_EEPROM)
            address = tmp_addr;
        #endif
    }
    #endif
#pragma endregion NeuralNetwork.cpp



//=======================================================================================================================================================================
// Layer.cpp
//=======================================================================================================================================================================

#pragma region Layer.cpp

    // Initialization of the array-of-pointers-to-(activation and derivative) functions without `inline`. see also issue #35
    // Additionally: in case of any future `const` to `constexpr` take a look here https://stackoverflow.com/a/40272829/11465149
    #if defined(ACTIVATION__PER_LAYER)
        const NeuralNetwork::method_function NeuralNetwork::activation_Function_ptrs[NUM_OF_USED_ACTIVATION_FUNCTIONS] = {
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Sigmoid)
                &NeuralNetwork::Layer::Sigmoid,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Tanh)
                &NeuralNetwork::Layer::Tanh,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ReLU)
                &NeuralNetwork::Layer::ReLU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyELU)
                &NeuralNetwork::Layer::LeakyELU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
                &NeuralNetwork::Layer::ELU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
                &NeuralNetwork::Layer::SELU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
                &NeuralNetwork::Layer::SoftmaxSum,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Identity)
                &NeuralNetwork::Layer::Identity,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(BinaryStep)
                &NeuralNetwork::Layer::BinaryStep,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softplus)
                &NeuralNetwork::Layer::Softplus,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SiLU)
                &NeuralNetwork::Layer::SiLU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(GELU)
                &NeuralNetwork::Layer::GELU,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Mish)
                &NeuralNetwork::Layer::Mish,
            #endif
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Gaussian)
                &NeuralNetwork::Layer::Gaussian,
            #endif

            #if defined(CUSTOM_AF1)
                &NeuralNetwork::Layer::CUSTOM_AF1,
            #endif
            #if defined(CUSTOM_AF2)
                &NeuralNetwork::Layer::CUSTOM_AF2,
            #endif
            #if defined(CUSTOM_AF3)
                &NeuralNetwork::Layer::CUSTOM_AF3,
            #endif
            #if defined(CUSTOM_AF4)
                &NeuralNetwork::Layer::CUSTOM_AF4,
            #endif
            #if defined(CUSTOM_AF5)
                &NeuralNetwork::Layer::CUSTOM_AF5,
            #endif
        };
        #if !defined(NO_BACKPROP)
            const NeuralNetwork::method_function NeuralNetwork::derivative_Function_ptrs[NUM_OF_USED_ACTIVATION_FUNCTIONS] = {
                #if defined(Sigmoid)
                    &NeuralNetwork::Layer::SigmoidDer,
                #endif
                #if defined(Tanh)
                    &NeuralNetwork::Layer::TanhDer,
                #endif
                #if defined(ReLU)
                    &NeuralNetwork::Layer::ReLUDer,
                #endif
                #if defined(LeakyELU)
                    &NeuralNetwork::Layer::LeakyELUDer,
                #endif
                #if defined(ELU)
                    &NeuralNetwork::Layer::ELUDer,
                #endif
                #if defined(SELU)
                    &NeuralNetwork::Layer::SELUDer,
                #endif
                #if defined(Softmax)
                    &NeuralNetwork::Layer::SoftmaxDer,
                #endif
                #if defined(Identity)
                    &NeuralNetwork::Layer::IdentityDer,
                #endif

                #if defined(CUSTOM_DF1)
                    &NeuralNetwork::Layer::CUSTOM_DF1,
                #endif
                #if defined(CUSTOM_DF2)
                    &NeuralNetwork::Layer::CUSTOM_DF2,
                #endif
                #if defined(CUSTOM_DF3)
                    &NeuralNetwork::Layer::CUSTOM_DF3,
                #endif
                #if defined(CUSTOM_DF4)
                    &NeuralNetwork::Layer::CUSTOM_DF4,
                #endif
                #if defined(CUSTOM_DF5)
                    &NeuralNetwork::Layer::CUSTOM_DF5,
                #endif
            };
        #endif
    #endif



    #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
        #if defined(NO_BIAS)
            NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Weights, NeuralNetwork * const NN )
        #else
            NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Weights, IS_CONST IDFLOAT *default_Bias, NeuralNetwork * const NN )
        #endif
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif
            

            #if !defined(NO_BIAS) // TODO: REDUCE_RAM_BIASES "common reference"
                bias = default_Bias; //                          ##1    Bias as Default Bias. Biases if defined MULTIPLE_BIASES_PER_LAYER | A reference
            #endif
            weights = new IS_CONST IDFLOAT *[_numberOfOutputs]; //      ##1    New Array of Pointers to (IDFLOAT) weights.

            for (int i = 0; i < _numberOfOutputs; i++)              // [matrix] (_numberOfOutputs * _numberOfInputs)
                weights[i] = &default_Weights[i * _numberOfInputs]; // Passing Default weights to ##1 weights by reference.  
        }
    #endif


    #if defined(NO_BIAS)
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, bool has_no_bias, NeuralNetwork * const NN) // has_no_bias is something the compiler i'm 99% sure it will optimize\remove
    #else
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, IS_CONST IDFLOAT *default_Bias, NeuralNetwork * const NN )
    #endif
    {
        _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
        _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

        #if !defined(REDUCE_RAM_STATIC_REFERENCE)
            me = NN;
        #endif

        #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
            outputs = new DFLOAT[_numberOfOutputs]; //    ##1    New Array of Outputs.
        #endif
        
        #if !defined(NO_BIAS)
            bias = default_Bias; //                          ##1    Bias as Default Bias. Biases if defined MULTIPLE_BIASES_PER_LAYER | A reference
        #endif
    }

    #if !defined(USE_PROGMEM) && !defined(USE_INTERNAL_EEPROM)
        //- [ numberOfInputs in into this layer , NumberOfOutputs of this layer ]
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, NeuralNetwork * const NN ) // TODO: IDFLOAT support 
        {

            _numberOfInputs = NumberOfInputs;                             // ##1       Number of Inputs .
            _numberOfOutputs = NumberOfOutputs;                           // ##1       Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs];                     // ##1    New Array of Outputs.
            #endif 
            #if !defined(REDUCE_RAM_WEIGHTS_COMMON)      
                weights = new IDFLOAT *[_numberOfOutputs];                  // ##1    New Array of Pointers to (IDFLOAT) weights.
            #endif
            #if defined(MULTIPLE_BIASES_PER_LAYER)
                bias = new IDFLOAT[_numberOfOutputs];                       // ##1    New          Biases
            #elif !defined(NO_BIAS)
                bias = new IDFLOAT;                                         // ##1    New          Bias   .
                *bias = 1.0; // SuS cause IDFLOAT
            #endif

            for (int i = 0; i < _numberOfOutputs; i++)
            {
                #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
                    weights[i] = new IDFLOAT[_numberOfInputs];
                #endif

                #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                    bias[i] = (IDFLOAT)random(-90000, 90000) / 100000;
                #endif
                
                for (int j = 0; j < _numberOfInputs; j++)
                {
                    #if defined(REDUCE_RAM_WEIGHTS_LVL2) // TODO: IDFLOAT support | ignore IDFLOAT below for now
                        me->weights[me->i_j] = (IDFLOAT)random(-90000, 90000) / 100000;
                        me->i_j++;
                    #else
                        weights[i][j] = (IDFLOAT)random(-90000, 90000) / 100000;  // Pseudo-Random Number between -90000 and 90000, divided by 100000.
                    #endif
                }
            }

        }
    // Yes, it needs the "elif" else it doesn't find any decleration of the function\method bellow
    #elif defined(USE_INTERNAL_EEPROM)
        NeuralNetwork::Layer::Layer(const unsigned int &NumberOfInputs, const unsigned int &NumberOfOutputs, NeuralNetwork * const NN )
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif
        }
    #endif

    // TODO: maybe create a static variable which will take a reference to a function. Once when j==0 (for output init) and once when j == _numberOfInputs -1
    void NeuralNetwork::Layer::FdF_Individual_PROGMEM(const DFLOAT &input, const int &j)
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
            if (j == 0) // if it is the first input then create output array (for the output layer of this current layer)
                outputs = new DFLOAT[_numberOfOutputs]; // ? speed ? or {} or memset .. it matters
        #endif
        //outputs[i] = 0; kai o midenismos se for

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            me->i_j = 0; // 1/2 only places that represents ony the i
        #endif

        //feed forwards
        int i;
        
        for (i = 0; i < _numberOfOutputs; i++)
        {
            if (j == 0){
                #if defined(NO_BIAS)
                    outputs[i] = 0; // ? speed ? safe one..
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = PGM_READ_IDFLOAT(&bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                #else
                    outputs[i] = PGM_READ_IDFLOAT(bias) MULTIPLY_BY_INT_IF_QUANTIZATION;
                #endif
            }

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                outputs[i] += input * PGM_READ_IDFLOAT(&me->weights[me->i_j+j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
            #else
                outputs[i] += input * PGM_READ_IDFLOAT(&weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION; // if double pgm_read_dword 
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                me->i_j += _numberOfInputs;
            #endif
        }

        // when all individual inputs get summed and multiplied by their weights in their outputs, then pass them from the activation function
        if (j == _numberOfInputs -1){
            for (i = 0; i < _numberOfOutputs; i++)
            {
                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[0]])(outputs[i]);  // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                #elif defined(Softmax)
                    outputs[i] = exp(outputs[i]);
                    sumOfSoftmax += outputs[i];
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); // if double pgm_read_dword
                #endif
            }

            #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                if (me->ActFunctionPerLayer[0] == 6)
                    Softmax();
            #elif defined(Softmax)
                Softmax();
            #endif
        }
    }

    void NeuralNetwork::Layer::FeedForward_Individual(const DFLOAT &input, const int &j)
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
            if (j == 0) // if it is the first input then create output array (for the output layer of this current layer)
                outputs = new DFLOAT[_numberOfOutputs];
        #endif
        //outputs[i] = 0; kai o midenismos se for

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            me->i_j = 0; // 1/2 only places that represents ony the i
        #endif

        //feed forwards
        int i;
        for (i = 0; i < _numberOfOutputs; i++)
        {
            if (j == 0){
                #if defined(NO_BIAS)
                    outputs[i] = 0; // ? speed ? safe one..
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = bias[i];
                #else
                    outputs[i] = *bias;
                #endif
            }

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                outputs[i] += input * me->weights[me->i_j+j];
            #else
                outputs[i] += input * weights[i][j];
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                me->i_j += _numberOfInputs;
            #endif
        }

        // when all individual inputs get summed and multiplied by their weights in their outputs, then pass them from the activation function
        if (j == _numberOfInputs -1){
            for (i = 0; i < _numberOfOutputs; i++){
                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[0]])(outputs[i]); // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                #elif defined(Softmax)
                    outputs[i] = exp(outputs[i]);
                    sumOfSoftmax += outputs[i];
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                #endif
            }

            #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                if (me->ActFunctionPerLayer[0] == 6)
                    Softmax();
            #elif defined(Softmax)
                Softmax();
            #endif
        }
    }


    #if defined (USE_INTERNAL_EEPROM) 
        void NeuralNetwork::Layer::FdF_Individual_iEEPROM(const DFLOAT &input, const int &j) // Not my proudest implementation, ngl... but it does the job for now
        {
            // TODO: 2024-03-09 I guess?? Why Don't you just declare `static byte F1` here?  
            if (j == 0){ // if it is the first input then create output array (for the output layer of this current layer)
                #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif
                #if defined(ACTIVATION__PER_LAYER)
                    me->F1 = get_EEPROM_value<byte>(me->address);
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    bias = new IDFLOAT(get_EEPROM_value<IDFLOAT>(me->address));
                #endif
            }else{
                #if defined(MULTIPLE_BIASES_PER_LAYER)
                    #if defined(ACTIVATION__PER_LAYER)
                        me->address += SIZEOF_FX; 
                    #endif
                #else
                    #if defined(NO_BIAS)
                        #if defined(ACTIVATION__PER_LAYER)
                            me->address += SIZEOF_FX 
                        #endif
                    #else
                        #if defined(ACTIVATION__PER_LAYER)
                            me->address += SIZEOF_FX + sizeof(IDFLOAT); 
                        #else
                            me->address += sizeof(IDFLOAT); 
                        #endif
                    #endif
                #endif
            }
            #if defined(MULTIPLE_BIASES_PER_LAYER)
                bias = new IDFLOAT(get_EEPROM_value<IDFLOAT>(me->address));
            #endif

            IDFLOAT tmp_jweight;
            int i;
            for (i = 0; i < _numberOfOutputs; i++) 
            {
                if (j == 0){
                    #if defined(NO_BIAS)
                        outputs[i] = 0;
                    #else
                        outputs[i] = *bias MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #endif
                }
                outputs[i] += input * EEPROM.get(me->address + j*sizeof(IDFLOAT), tmp_jweight) MULTIPLY_BY_INT_IF_QUANTIZATION;
                me->address += _numberOfInputs * sizeof(IDFLOAT); 
                #if defined(MULTIPLE_BIASES_PER_LAYER) // This line is suspicious in case of when reading beyond EEPROM's length (which might happen if the initial address is not less than 4 bytes away from the end)
                    *bias = get_EEPROM_value<IDFLOAT>(me->address);
                #endif
            }
            #if defined(MULTIPLE_BIASES_PER_LAYER)
                delete bias;
            #endif

            // when all individual inputs get summed and multiplied by their weights in their outputs, then pass them from the activation function
            if (j == _numberOfInputs -1){
                for (i = 0; i < _numberOfOutputs; i++){
                    #if defined(ACTIVATION__PER_LAYER)
                        outputs[i] = ((this)->*(activation_Function_ptrs)[me->F1])(outputs[i]); // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                    #elif defined(Softmax)
                        outputs[i] = exp(outputs[i]);
                        sumOfSoftmax += outputs[i];
                    #else
                        outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                    #endif
                }
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    delete bias;
                #endif

                #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                    // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                    if (me->F1 == 6)
                        Softmax();
                #elif defined(Softmax)
                    Softmax();
                #endif
            }
        }


        void NeuralNetwork::Layer::FdF_IN_EEPROM(const DFLOAT *inputs)
        {
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs];
            #endif
            #if defined(ACTIVATION__PER_LAYER)
                byte fx = get_EEPROM_value<byte>(me->address); 
            #endif

            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                IDFLOAT tmp_bias = get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; 
            #endif
            for (int i = 0; i < _numberOfOutputs; i++)
            {
                #if defined(NO_BIAS)
                    outputs[i] = 0;
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; 
                #else
                    outputs[i] = tmp_bias;
                #endif

                for (int j = 0; j < _numberOfInputs; j++) // REDUCE_RAM_WEIGHTS_LVL2 is disabled
                {
                    outputs[i] += inputs[j] * get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                }

                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = ((this)->*(activation_Function_ptrs)[fx])(outputs[i]);
                #elif defined(Softmax)
                    outputs[i] = exp(outputs[i]);
                    sumOfSoftmax += outputs[i];
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]);
                #endif
            }

            #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                if (fx == 6)
                    Softmax();
            #elif defined(Softmax)
                Softmax();
            #endif
        }
    #endif

    void NeuralNetwork::Layer::FdF_PROGMEM(const DFLOAT *inputs) //*
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            outputs = new DFLOAT[_numberOfOutputs];
        #endif
        
        //feed forwards
        for (int i = 0; i < _numberOfOutputs; i++)
        {
            #if defined(NO_BIAS)
                outputs[i] = 0;
            #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                outputs[i] = PGM_READ_IDFLOAT(&bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
            #else
                outputs[i] = PGM_READ_IDFLOAT(bias) MULTIPLY_BY_INT_IF_QUANTIZATION;
            #endif

            for (int j = 0; j < _numberOfInputs; j++) 
            {
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    outputs[i] += inputs[j] * PGM_READ_IDFLOAT(&me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    me->i_j++;
                #else
                    outputs[i] += inputs[j] * PGM_READ_IDFLOAT(&weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                #endif
            }
            #if defined(ACTIVATION__PER_LAYER)
                outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
            #elif defined(Softmax)
                outputs[i] = exp(outputs[i]);
                sumOfSoftmax += outputs[i];
            #else
                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]);
            #endif
        }

        #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
            // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
            if (me->ActFunctionPerLayer[me->AtlayerIndex] == 6)
                Softmax();
        #elif defined(Softmax)
            Softmax();
        #endif
    }

    void NeuralNetwork::Layer::FeedForward(const DFLOAT *inputs) //*
    {
        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            outputs = new DFLOAT[_numberOfOutputs];
        #endif
    
        //feed forwards
        for (int i = 0; i < _numberOfOutputs; i++)
        {
            #if defined(ESP_SUPPORTS_SIMD)
                #if !defined(REDUCE_RAM_WEIGHTS_LVL2)
                    dsps_dotprod_f32(inputs, weights[i], &outputs[i], _numberOfInputs); // https://github.com/GiorgosXou/NeuralNetworks/discussions/16#discussioncomment-7479256
                #else
                    dsps_dotprod_f32(inputs, &me->weights[me->i_j], &outputs[i], _numberOfInputs); 
                    me->i_j+= _numberOfInputs;
                #endif

                #if defined(MULTIPLE_BIASES_PER_LAYER) // No need for MULTIPLY_BY_INT_IF_QUANTIZATION because there's no SIMD support for it// TODO: REDUCE_RAM_BIASES "common reference" 
                    outputs[i] += bias[i]; 
                #elif !defined(NO_BIAS)
                    outputs[i] += *bias;
                #endif
            #else
                #if defined(NO_BIAS)
                    outputs[i] = 0;
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = bias[i] MULTIPLY_BY_INT_IF_QUANTIZATION;
                #else
                    outputs[i] = *bias MULTIPLY_BY_INT_IF_QUANTIZATION;
                #endif

                for (int j = 0; j < _numberOfInputs; j++)
                {
                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        outputs[i] += inputs[j] * me->weights[me->i_j] MULTIPLY_BY_INT_IF_QUANTIZATION;
                        me->i_j++;
                    #else
                        outputs[i] += inputs[j] * weights[i][j] MULTIPLY_BY_INT_IF_QUANTIZATION; // (neuron[i]'s 1D array/vector of inputs) * (neuron[i]'s 2D array/matrix weights) = neuron[i]'s output
                    #endif
                }
            #endif

            #if defined(ACTIVATION__PER_LAYER)
                outputs[i] = ((this)->*(activation_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]); //if softmax then calls the SoftmaxSum
            #elif defined(Softmax)
                outputs[i] = exp(outputs[i]);
                sumOfSoftmax += outputs[i];
            #else
                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
            #endif
        }

        #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
            // if current's Activation function == 6 == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
            if (me->ActFunctionPerLayer[me->AtlayerIndex] == 6)
                Softmax();
        #elif defined(Softmax)
            Softmax();
        #endif
        // return outputs;
    } 

    
    DFLOAT NeuralNetwork::Layer::erf(DFLOAT x)
    {
        // constants | don't trust the precision you see here
        DFLOAT a1 =  0.254829592;
        DFLOAT a2 = -0.284496736;
        DFLOAT a3 =  1.421413741;
        DFLOAT a4 = -1.453152027;
        DFLOAT a5 =  1.061405429;
        DFLOAT p  =  0.3275911;

        // Save the sign of x
        int sign = 1;
        if (x < 0)
            sign = -1;
        x = fabs(x);

        // A&S formula 7.1.26
        DFLOAT t = 1.0/(1.0 + p*x);
        DFLOAT y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

        return sign*y;
    }

    /*
    αρα θα βγαλω τη sigmoid απο _numberOfOutputs loop ==> Sigmoid(ACTIVATION_FUNCTION, outputs[i] + (*bias))
    και θα τη βαλω στο _numberOfInputs loop ==> inputs[j] (για εξοικονομηση RAM, διαφορετικα BeforeActivationOutputs 1D Array [πριν το activation δλδ] με Property)
    ωστε να μπορω οταν θα κανω backprop να παρω τις παραγωγους και αλλων συναρτισεων ενεργοποιησης 
    που απετουν το Input πριν το activation.... αααχ issues τελικα it was too good to be true..

    https://stackoverflow.com/questions/1253934/c-pre-processor-defining-for-generated-function-names
    */


    DFLOAT NeuralNetwork::Layer::Sigmoid       (const DFLOAT &x) { return 1 / (1 + exp(-x))                                ;}
    DFLOAT NeuralNetwork::Layer::Tanh          (const DFLOAT &x) { return (exp(2*x) - 1) / (exp(2*x) + 1)                  ;}
    DFLOAT NeuralNetwork::Layer::ReLU          (const DFLOAT &x) { return (x > 0) ? x : 0                                  ;}

    // REMINDER: They are wrapped in #defines because of their Alphas
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyELU)
        DFLOAT NeuralNetwork::Layer::LeakyELU  (const DFLOAT &x) { return (x > 0) ? x : me->AlphaLeaky * x                 ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
        DFLOAT NeuralNetwork::Layer::ELU       (const DFLOAT &x) { return (x > 0) ? x : me->AlphaELU  * (exp(x) - 1)       ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
        DFLOAT NeuralNetwork::Layer::SELU      (const DFLOAT &x) { return (x > 0) ? x : me->AlphaSELU * (exp(x) - 1)       ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
        DFLOAT NeuralNetwork::Layer::SoftmaxSum(const DFLOAT &x) { DFLOAT tmp = exp(x); me->sumOfSoftmax +=tmp; return tmp  ;}
        void  NeuralNetwork::Layer::Softmax() {for (int i = 0; i < _numberOfOutputs; i++){outputs[i] /= me->sumOfSoftmax;}}
    #endif

    DFLOAT NeuralNetwork::Layer::Identity      (const DFLOAT &x) {return x                                                 ;}
    //NO_BACKPROP
    DFLOAT NeuralNetwork::Layer::BinaryStep    (const DFLOAT &x) {return (x < 0) ? 0 : 1                                   ;}
    DFLOAT NeuralNetwork::Layer::Softplus      (const DFLOAT &x) {return log(1 + exp(x))                                   ;}
    DFLOAT NeuralNetwork::Layer::SiLU          (const DFLOAT &x) {return x / (1 + exp(-x))                                 ;}
    DFLOAT NeuralNetwork::Layer::GELU          (const DFLOAT &x) {return (1/2) * x * (1 + erf(x / sqrt(x)))                ;}
    DFLOAT NeuralNetwork::Layer::Mish          (const DFLOAT &x) {return x * Tanh(log(1 + exp(x)))                         ;}
    DFLOAT NeuralNetwork::Layer::Gaussian      (const DFLOAT &x) {return exp(-(x*x))                                       ;}

    #if !defined(NO_BACKPROP)

        DFLOAT NeuralNetwork::Layer::SigmoidDer  (const DFLOAT &fx) { return fx - fx * fx                                                     ;} 
        DFLOAT NeuralNetwork::Layer::TanhDer     (const DFLOAT &fx) { return 1 - fx * fx                                                      ;}
        DFLOAT NeuralNetwork::Layer::ReLUDer     (const DFLOAT &fx) { return (fx > 0) ? 1 : 0                                                 ;} 

        #if defined(LeakyELU)    
            DFLOAT NeuralNetwork::Layer::LeakyELUDer(const DFLOAT &fx) { return (fx > 0) ? 1 : me->AlphaLeaky                                 ;} 
        #endif
        #if defined(ELU)
            DFLOAT NeuralNetwork::Layer::ELUDer     (const DFLOAT &fx) { return (fx > 0) ? 1 : fx + me->AlphaELU                              ;} 
        #endif
        #if defined(SELU)
            DFLOAT NeuralNetwork::Layer::SELUDer    (const DFLOAT &fx) { return (fx > 0) ? me->LamdaSELU : fx + me->AlphaSELU * me->LamdaSELU ;} 
        #endif
        
        DFLOAT NeuralNetwork::Layer::SoftmaxDer     (const DFLOAT &fx) { return fx * (1 - fx)                                                 ;} // hmm...?
        DFLOAT NeuralNetwork::Layer::IdentityDer    (const DFLOAT &x ) {return 1                                                              ;}


        void NeuralNetwork::Layer::BackPropOutput(const DFLOAT *_expected_, const DFLOAT *inputs)
        {

            preLgamma = new DFLOAT[_numberOfInputs]{}; // create gamma of previous layer and initialize{} values to 0 .. meh
            

            #if !defined(NO_BIAS)
                DFLOAT bias_Delta = 1.0;
            #endif
            DFLOAT gamma;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                for (int i = _numberOfOutputs -1; i >= 0; i--)
                {
                    //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                    gamma = (outputs[i] - _expected_[i]);
                    
                     // I want to believe that it is being optimised/removed when not used | update 5/8/2021 ain't sure althought i've used "https://godbolt.org/" so... Macros
                    #if defined(CATEGORICAL_CROSS_ENTROPY)
                        me->sumOfCategoricalCrossEntropy -= _expected_[i] * log(outputs[i]);
                    #endif
                    #if defined(BINARY_CROSS_ENTROPY)
                        me->sumOfBinaryCrossEntropy -=  _expected_[i] * log(outputs[i]) + (1 - _expected_[i]) * log(1 - outputs[i]); // https://forum.arduino.cc/t/maths-help-log/339211 https://math.stackexchange.com/questions/293783/when-log-is-written-without-a-base-is-the-equation-normally-referring-to-log-ba
                    #endif
                    #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
                        me->sumSquaredError += gamma * gamma; 
                    #endif

                    
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = gamma * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = gamma * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]);
                    #endif
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        bias[i] -= gamma * me->LearningRateOfBiases; // This is the only line in the entire source-code, for which I asked and slightly trusted CHATGPT, because I wasn't 100% sure 
                    #elif !defined(NO_BIAS)
                        bias_Delta *= gamma;
                    #endif

                    for (int j = _numberOfInputs -1; j >= 0; j--)
                    {
                        me->i_j--;
                        preLgamma[j] += gamma * me->weights[me->i_j];
                        me->weights[me->i_j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;   
                    }
                }

            #else
                for (int i = 0; i < _numberOfOutputs; i++)
                {
                    //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                    //gamma = (outputs[i] - _expected_[i]) * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // outputs[i] is f(x) not x in this case, because i wanted to delete the array of inputs before activation

                     //#3
                    gamma = (outputs[i] - _expected_[i]); 
                    
                    // I want to believe that it is being optimised/removed when not used | update 5/8/2021 ain't sure althought i've used "https://godbolt.org/" so... Macros again lol
                    #if defined(CATEGORICAL_CROSS_ENTROPY)
                        me->sumOfCategoricalCrossEntropy -= _expected_[i] * (DFLOAT)log(outputs[i]);
                    #endif
                    #if defined(BINARY_CROSS_ENTROPY)
                        me->sumOfBinaryCrossEntropy -=  _expected_[i] * (DFLOAT)log(outputs[i]) + (1.0 - _expected_[i]) * (DFLOAT)log(1.0 - outputs[i]); // https://forum.arduino.cc/t/maths-help-log/339211 https://math.stackexchange.com/questions/293783/when-log-is-written-without-a-base-is-the-equation-normally-referring-to-log-ba
                    #endif
                    #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
                        me->sumSquaredError += gamma * gamma; 
                    #endif
                    
                   
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = gamma * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = gamma * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]);
                    #endif
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        bias[i] -= gamma * me->LearningRateOfBiases; // This is the only line in the entire source-code, for which I asked and slightly trusted CHATGPT, because I wasn't 100% sure 
                    #elif !defined(NO_BIAS)
                        bias_Delta *= gamma;
                    #endif

                    for (int j = 0; j < _numberOfInputs; j++) // TODO: 2024-03-12 07:03:29 AM this could go into a seperate common function
                    {
                        preLgamma[j] += gamma * weights[i][j];
                        weights[i][j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }
                }
            #endif
            
            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                *bias -= bias_Delta * me->LearningRateOfBiases;
            #endif
        }

        void NeuralNetwork::Layer::BackPropHidden(const Layer *frontLayer, const DFLOAT *inputs)
        {
            #if defined(ACTIVATION__PER_LAYER)
                me->AtlayerIndex -= 1; 
            #endif
            preLgamma = new DFLOAT[_numberOfInputs]{};

            #if !defined(NO_BIAS)
                DFLOAT bias_Delta = 1.0;
            #endif
            DFLOAT gamma;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                for (int i = _numberOfOutputs -1; i >= 0; i--)
                {
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = frontLayer->preLgamma[i] * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = frontLayer->preLgamma[i] * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // if i remember well , frontLayer->preLgamma[i] means current layer gamma?
                    #endif

                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        bias[i] -= gamma * me->LearningRateOfBiases; // This is the only line in the entire source-code, for which I asked and slightly trusted CHATGPT, because I wasn't 100% sure 
                    #elif !defined(NO_BIAS)
                        bias_Delta *= gamma;
                    #endif

                    for (int j = _numberOfInputs -1; j >= 0; j--)
                    {
                        me->i_j--;
                        preLgamma[j] += gamma * me->weights[me->i_j];
                        me->weights[me->i_j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }

                }

            #else
                for (int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(ACTIVATION__PER_LAYER)
                        gamma = frontLayer->preLgamma[i] * ((this)->*(derivative_Function_ptrs)[me->ActFunctionPerLayer[me->AtlayerIndex]])(outputs[i]);
                    #else
                        gamma = frontLayer->preLgamma[i] * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // if i remember well , frontLayer->preLgamma[i] means current layer gamma?
                    #endif

                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        bias[i] -= gamma * me->LearningRateOfBiases; // This is the only line in the entire source-code, for which I asked and slightly trusted CHATGPT, because I wasn't 100% sure 
                    #elif !defined(NO_BIAS)
                        bias_Delta *= gamma;
                    #endif

                    for (int j = 0; j < _numberOfInputs; j++)
                    {
                        preLgamma[j] += gamma * weights[i][j];
                        weights[i][j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                    }

                }
            #endif

            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                *bias -= bias_Delta * me->LearningRateOfBiases;
            #endif
        }
    #endif


    //If Microcontroller isn't one of the Attiny Series then it compiles the code below.
    #if !defined(As__No_Common_Serial_Support) // then Compile:
    void NeuralNetwork::Layer::print()
    { 
        #if defined(USE_INT_QUANTIZATION)
            Serial.print(F_MACRO("INT_Q "));
        #endif
        Serial.print(_numberOfInputs);
        Serial.print(F_MACRO("x"));
        Serial.print(_numberOfOutputs);
        #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
            Serial.print(F_MACRO("| bias:"));
            Serial.print(*bias MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
        #endif
        #if defined(ACTIVATION__PER_LAYER)
            Serial.print(F_MACRO("| F(x):"));
            Serial.print(me->ActFunctionPerLayer[me->AtlayerIndex]);
        #endif
        Serial.println();

        for (int i = 0; i < _numberOfOutputs; i++)
        {
            #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                Serial.print(F_MACRO("   B:"));
                Serial.println(bias[i] MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
            #endif
            Serial.print(i + 1);
            Serial.print(F_MACRO(" "));
            for (int j = 0; j < _numberOfInputs; j++)
            {
                Serial.print(F_MACRO(" W:"));
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    if (me->weights[me->i_j] > 0) Serial.print(F_MACRO(" ")); // dont even bothered to opt. here lol
                    Serial.print(me->weights[me->i_j] MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    me->i_j++;
                #else
                    if (weights[i][j] > 0) Serial.print(F_MACRO(" "));
                    Serial.print(weights[i][j] MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                #endif
                Serial.print(F_MACRO(" "));
            }
            Serial.println();
        }
        Serial.println(F_MACRO("----------------------"));

    }

    void NeuralNetwork::Layer::print_PROGMEM()
    {
        #if defined(USE_INT_QUANTIZATION)
            Serial.print(F_MACRO("INT_Q PROGMEM "));
        #else
            Serial.print(F_MACRO("PROGMEM "));
        #endif
        Serial.print(_numberOfInputs);
        Serial.print(F_MACRO("x"));
        Serial.print(_numberOfOutputs);
        #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
            Serial.print(F_MACRO("| bias:"));
            Serial.print(PGM_READ_IDFLOAT(bias) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
        #endif
        #if defined(ACTIVATION__PER_LAYER)
            Serial.print(F_MACRO("| F(x):"));
            Serial.print(me->ActFunctionPerLayer[me->AtlayerIndex]);
        #endif
        Serial.println();

        for (int i = 0; i < _numberOfOutputs; i++)
        {
            #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                Serial.print(F_MACRO("   B:"));
                Serial.println(PGM_READ_IDFLOAT(&bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
            #endif
            Serial.print(i + 1);
            Serial.print(" ");
            for (int j = 0; j < _numberOfInputs; j++)
            {
                //weights[i][j] = (DFLOAT)j;
                Serial.print(F_MACRO(" W:"));
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    if (PGM_READ_IDFLOAT(&me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0) Serial.print(F_MACRO(" ")); // if gratter than 10 too or something would be nice
                    Serial.print(PGM_READ_IDFLOAT(&me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    me->i_j++;
                #else
                    if (PGM_READ_IDFLOAT(&weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0 ) Serial.print(F_MACRO(" "));
                    Serial.print(PGM_READ_IDFLOAT(&weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                #endif
                Serial.print(F_MACRO(" "));
            }
            Serial.println();
        }
        Serial.println(F_MACRO("----------------------"));
    }

        #if defined(USE_INTERNAL_EEPROM)
            void NeuralNetwork::Layer::print_INTERNAL_EEPROM()
            {
                #if defined(USE_INT_QUANTIZATION)
                    Serial.print(F_MACRO("INT_Q EEPROM "));
                #else
                    Serial.print(F_MACRO("EEPROM "));
                #endif
                Serial.print(_numberOfInputs);
                Serial.print(F_MACRO("x"));
                Serial.print(_numberOfOutputs);
                #if defined(ACTIVATION__PER_LAYER)
                    Serial.print(F_MACRO("| F(x):"));
                    Serial.print(get_EEPROM_value<byte>(me->address));
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    Serial.print(F_MACRO("| bias:"));
                    Serial.print(get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                #endif
                Serial.println();
                DFLOAT tmp_ijweight; // Reminder: don't change it to IDFLOAT
                for (int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        Serial.print(F_MACRO("   B:"));
                        Serial.println(get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    Serial.print(i + 1);
                    Serial.print(F_MACRO(" "));
                    for (int j = 0; j < _numberOfInputs; j++)
                    {
                        tmp_ijweight = get_EEPROM_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        Serial.print(F_MACRO(" W:"));
                        if (tmp_ijweight > 0 ) Serial.print(F_MACRO(" "));
                        Serial.print(tmp_ijweight, DFLOAT_LEN);
                        Serial.print(F_MACRO(" "));
                    }
                    Serial.println();
                }
                Serial.println(F_MACRO("----------------------"));
            }
        #endif

    #endif

#pragma endregion Layer.cpp
#endif


/*
#2 https://stackoverflow.com/questions/22318677/is-it-faster-to-have-the-compiler-initialize-an-array-or-to-manually-iterate-over  [I am slightly confused. Anyways...]
#4 https://stackoverflow.com/questions/65860934/undefined-reference-to-outterclassfunction-ptrs-variable-issue

#5 (Most Probably) It will be Optimised by the compiler if no needed
#6 https://stackoverflow.com/questions/68689135/unusual-behavior-unnecessary-variables-inside-a-class-result-in-extra-bytes-of

In Arduino log() = ln = natural logarithm = logarithm with base e 
*/
