
/*
  NeuralNetwork.h - Library for Neural Networks.
  Created by George Chousos, April 11, 2019. *0
  Released into the public domain.

  *0: Mainly Based on: https://www.youtube.com/watch?v=L_PByyJ9g-I
  https://www.arduino.cc/en/Hacking/libraryTutorial
*/


// STR(MSGX) | pragma message
#define MSG0
// i would love if there could be a list of microcontrollers or a way to determine with defined(..) the size of SRAM or etc.
// Defines a list of microcontroller Attiny series As__AVR_ATtinyXXX__
#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    #define As__AVR_ATtinyX__
    #define DISABLE_NN_SERIAL_SUPPORT

    #if defined(__AVR_ATtiny85__)
        #undef MSG0
        #define MSG0 \n- " [X] ////////// [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] `NN.print()` function is disabled for ATtiny85 [...]"
    #endif
#endif

// Disables serial support:  
#if defined(DISABLE_NN_SERIAL_SUPPORT)
    #define AS__NO_COMMON_SERIAL_SUPPORT
#endif

#define SD_NN_WRITE_MODE O_WRITE | O_CREAT
#if defined(CORE_TEENSY)
    #undef SD_NN_WRITE_MODE
    #define SD_NN_WRITE_MODE FILE_WRITE
#elif defined(ESP32)
    #define AS_SOFTWARE_EMULATED_EEPROM
    #undef SD_NN_WRITE_MODE
    #define SD_NN_WRITE_MODE "w"
#endif


// - This prevents problems if someone accidently #include's your library twice.
#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#define __NN_VERSION__ "VERSION: 4.1.0-Alpha"\n


#if defined(ARDUINO)
    #include "Arduino.h"  // - That gives you access to the standard types and constants of the Arduino language.
    #define NN_RANDOM(min,max)  random(min,max)
    #define NN_RANDOM_SET(seed) randomSeed(seed)
    #define NN_PRINT_1(x)       Serial.print(x)
    #define NN_PRINT_2(x,y)     Serial.print(x,y)
    #define NN_PRINTLN()        Serial.println()
    #define NN_PRINTLN_1(x)     Serial.println(x)
    #define NN_PRINTLN_2(x,y)   Serial.println(x,y)
    #define CHAR_BYTE byte
    #define NN_FS_SEEK(x) seek(x)
#else 
    // By "native" I mean not bare-metal (nor ARDUINO) eg. Linux Windows Mac etc. 
    // (but it should mostly work as it is for bare-metal too), 
    // #define NATIVE_NN
    #define NATIVE_OR_BARE_NN
    // using char since that's acceptaple natively
    #define CHAR_BYTE char
    // g++ -o main.o main.cpp
    // #include <stdio.h> // (for printf) but don't include it here.
    #include <math.h>
    #include <stdint.h> // for int8_t
    using byte = uint8_t; // supports -std=c++11 too
    #define NN_RANDOM(min,max) (rand() % (max - min) + min)
    #define NN_RANDOM_SET(seed) srand(seed)
    // for SUPPORTS_FS_FUNCTIONALITY + #include <fstream>
    // seek at position in file
    #define NN_FS_SEEK(x) seekp(x)
    // just a printf | simply map UART to printf and you should be fine
    static inline void nn_print(float         v) { printf("%f" , v);}
    static inline void nn_print(double        v) { printf("%lf", v);}
    static inline void nn_print(unsigned char v) { printf("%u" , v);}
    static inline void nn_print(int           v) { printf("%d" , v);}
    static inline void nn_print(unsigned int  v) { printf("%u" , v);}
    static inline void nn_print(const char*   v) { printf("%s" , v);}
    #define NN_PRINT_1(x)     nn_print(x)
    #define NN_PRINT_2(x,y)   nn_print(x)
    #define NN_PRINTLN()      printf("\n")
    #define NN_PRINTLN_1(x)   printf("%s\n",x)
    #define NN_PRINTLN_2(x,y) do {nn_print(x); printf("\n");} while(0)
#endif



// Minimal type traits (primarely) for Arduino (don't worry they are evaluated at compile-time)
template<bool B, typename T = void> struct nn_enable_if {};
template<typename T>                struct nn_enable_if<true, T> { typedef T type; };

template<typename T> struct is_not_a_cstring                { static const bool value = true ;};
template<size_t   N> struct is_not_a_cstring<const char[N]> { static const bool value = false;};
template<size_t   N> struct is_not_a_cstring<      char[N]> { static const bool value = false;};


// https://arduino.stackexchange.com/questions/94743/is-ifdef-sd-h-considered-a-bad-practice/
// considering there's a scope it's looking for the library if you declare it above the #include <NeuralNetwork.h> it will enable the functionality else no.. meaning that I don't need to worry about destructor optimization #8
// INCLUDES_FRAM_H and INCLUDES_EEPROM_H need to be there for save() function.
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

// #define FRAM_LIB_NAME "FRAM.h"
#if defined(FRAM_OK) // Meh.. library uses #pragma once so I had to use another macro
    #define INCLUDES_FRAM_H
    // This will result on issues if the library is included below <NeuralNetwork.h> for some weird reason, so I believe this is enough anyways
// #elif defined __has_include
//     #if __has_include(FRAM_LIB_NAME)
//         #include FRAM_LIB_NAME 
//         #define INCLUDES_FRAM_H
//     #endif
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
#define MSG16
#define MSG17
#define MSG18
#define MSG19
#define MSG20
#define MSG21
#define MSG22
#define MSG23
#define MSG24
#define MSG25
#define LOVE \n 𝖀𝖓𝖈𝖔𝖓𝖉𝖎𝖙𝖎𝖔𝖓𝖆𝖑 𝕷𝖔𝖛𝖊 
                     
// Memmory substrate message PROGMEM EEPROM etc.
#define MEM_SUBSTRATE_MSG

#define F_MACRO  

#define MULTIPLY_BY_INT_IF_QUANTIZATION

#define ACCUMULATED_DOT_PRODUCT_OF accumulatedDotProduct

//NOTE: IF YOU ARE A DEVELOPER\PROGRAMMER SEE #13 (and follow DISABLE_STATIC_FOR_ACTS)
#define IS_STATIC static
#define IS_IN_LAYER_SCOPE
#define IS_THIS

// Determins whether or not it supports FeedForward_Individual-type functions eg. when USE_GRU_LAYERS_ONLY or USE_LSTM_LAYERS_ONLY it #undefs it | see also #24
#define SUPPORTS_INDIVIDUAL_FEEDFORWARD

// Optional Bias Macro, inlines/appends x if biases are enabled (not-NO_BIAS), else it does nothing
#define OPTIONAL_BIAS(x) , x
// Optional Bias Macro, inlines/appends x if multiple biases are enabled (MULTIPLE_BIASES_PER_LAYER)
#define OPTIONAL_MULTI_BIAS(x)
// Optional Bias Macro, inlines/appends x if single biases are enabled
#define OPTIONAL_SINGLE_BIAS(x)

// Forces (REDUCE_RAM_WEIGHTS_LVL2) when GRU or LSTM layers are used, due to potential-incompatibility-issues
#if defined(USE_GRU__NB) or defined(USE_LSTM__NB) // #21
    #undef MSG3
    #if defined(NO_FORCED_WEIGHTS_LVL2) // the reason I define IGNORE_OB0001_OPT instead of simply using NO_FORCED_WEIGHTS_LVL2 is to prevent other (NN_TYPE_ARCHITECTURE)s besides LSTM/GRU from using NO_FORCED_WEIGHTS_LVL2
        #define IGNORE_OB0001_OPT
        #define MSG3 \n- " [1] 0B000X0000 [Χ] [𝗪𝗔𝗥𝗡𝗜𝗡𝗚] Disabling (REDUCE_RAM_WEIGHTS_LVL2) for LSTM/GRU, makes save()/load() incompatible."
    #else
        #define FORCED_REDUCE_RAM_WEIGHTS_LVL2
        #define REDUCE_RAM_WEIGHTS_COMMON
        #define REDUCE_RAM_WEIGHTS_LVL2
        #define MSG3 \n- " [1] 0B00010000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (FORCED_REDUCE_RAM_WEIGHTS_LVL2) for LSTM/GRU, unless (NO_FORCED_WEIGHTS_LVL2) is defined."
    #endif
#endif

#define ATOL atol
#define LLONG long
#define DFLOAT float
#define DFLOAT_LEN 7
#define TYPE_MEMMORY_READ_IDFLOAT(x) (x)
#define IS_CONST
#if defined(_1_OPTIMIZE)
    #if ((_1_OPTIMIZE bitor 0B01111111) == 0B11111111)
        #undef MSG1
        #undef IS_CONST
        #undef MEM_SUBSTRATE_MSG
        #if defined(__AVR__)
            #define MSG1 \n- " [1] 0B10000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (USE_PROGMEM)."
            #undef TYPE_MEMMORY_READ_IDFLOAT
            #define TYPE_MEMMORY_READ_IDFLOAT(x) pgm_read_float(&x)
            #define AVR_PROGMEM_LOGIC
        #elif defined(NATIVE_OR_BARE_NN)
            #define MSG1 \n- " [1] 0B10000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Simply using `const`, (non-AVR) (CONST_MODERN_PROGMEM_LOGIC)."
            #define CONST_MODERN_PROGMEM_LOGIC
        #else
            #define MSG1 \n- " [1] 0B10000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using (non-AVR), (CONST_MODERN_PROGMEM_LOGIC)." 
            #define CONST_MODERN_PROGMEM_LOGIC
        #endif
        #define IS_CONST const
        #define NO_BACKPROP
        #define USE_PROGMEM
        #define MEM_SUBSTRATE_MSG [𝗣𝗥𝗢𝗚𝗠𝗘𝗠]
    #endif
    #if ((_1_OPTIMIZE bitor 0B10111111) == 0B11111111)
        #define REDUCE_RAM_DELETE_OUTPUTS
        #define NO_BACKPROP
        #undef MSG2
        #define MSG2 \n- " [1] 0B01000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (REDUCE_RAM_DELETE_OUTPUTS)."
    #endif  

    #if ((_1_OPTIMIZE bitor 0B11011111) == 0B11111111)
        #undef MSG22
        #define MSG22 \n- " [1] 0B00100000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using (DISABLE_SIMD_SUPPORT), allows any type to be used as input-data."
        #define DISABLE_SIMD_SUPPORT
    #endif
    
    #if ((_1_OPTIMIZE bitor 0B11101111) == 0B11111111) && !defined(FORCED_REDUCE_RAM_WEIGHTS_LVL2) && !defined(IGNORE_OB0001_OPT)
        #define REDUCE_RAM_WEIGHTS_COMMON
        #define REDUCE_RAM_WEIGHTS_LVL2
        //#warning [Δ] Backpropagating more than once after a FeedForward [...]
        #undef MSG3
        #define MSG3 \n- " [1] 0B00010000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using (REDUCE_RAM_WEIGHTS_LVL2)."
    #endif

    // NOTE: 2025-10-31 09:17:45 AM | (the line bellow is related to an [old] always-enabled optimization called `REDUCE_RAM_DELETE_PREVIOUS_LAYER_GAMMA`, that was replaced in favor of `REDUCED_SKETCH_SIZE_DOT_PROD`)
    // ^^^^^ 2025-02-25 01:35:49 AM | #10 I just realised that it doesn't really matter, since it has to zero the preLgamma-arrays prior to BackPropopagation [...]

    #if ((_1_OPTIMIZE bitor 0B11110111) == 0B11111111)
        #define REDUCED_SKETCH_SIZE_DOT_PROD
        #undef MSG4
        #define MSG4 \n- " [1] 0B00001000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using (REDUCED_SKETCH_SIZE_DOT_PROD)."
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111011) == 0B11111111)
        #define REDUCE_RAM_STATIC_REFERENCE
        #undef MSG5
        #define MSG5 \n- " [1] 0B00000100 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] If multiple NN objects, see: _2_OPTIMIZE 0B00000010!"
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111101) == 0B11111111)
        #define DISABLE_MSE
        #undef MSG6
        #define MSG6 \n- " [1] 0B00000010 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] MSE is disabled (DISABLE_MSE) (DEFAULT_LOSS)"
    #endif

    #if ((_1_OPTIMIZE bitor 0B11111110) == 0B11111111)
        #include <float.h>
        #if (DBL_MANT_DIG == FLT_MANT_DIG) // https://stackoverflow.com/questions/8751109
            #error "💥 Your MCU doesn't support 64bit/8byte double-precision !!! | (DBL_MANT_DIG == FLT_MANT_DIG)"
        #endif
        #undef ATOL 
        #undef LLONG 
        #undef DFLOAT_LEN 
        #undef DFLOAT 
        #undef TYPE_MEMMORY_READ_IDFLOAT 
        #define USE_64_BIT_DOUBLE
        #define ATOL atoll
        #define LLONG long long
        #define DFLOAT_LEN 15
        #define DFLOAT double
        #define TYPE_MEMMORY_READ_IDFLOAT(x) pgm_read_double(&x)

        double pgm_read_double(const double* address) {
            double result;
            memcpy_P(&result, address, sizeof(double));
            return result;
        }

        #undef MSG7
        #define MSG7 \n- " [1] 0B00000001 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using 64bit\8byte double-precision (USE_64_BIT_DOUBLE)."
    #endif
    //if i'll make most of the things static/global, i can significantly reduce rom but with the "limitation" of "one" NN per skeatch
#endif

#define IDFLOAT DFLOAT

// [OLD VERSION V.2.X.X] If not USE_INT_QUANTIZATION then the line bellow is used for SD save
#define CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(value) *((LLONG*)(&value))

#if defined(_2_OPTIMIZE)
    #if ((_2_OPTIMIZE bitor 0B01111111) == 0B11111111)
        #define NO_BACKPROP
        #define USE_INTERNAL_EEPROM
        #if defined(USE_PROGMEM)
            #error "💥 You can't USE_INTERNAL_EEPROM and USE_PROGMEM together. Either disable `_2_OPTIMIZE 0B1` or `_1_OPTIMIZE 0B1` accordingly."
        #endif
        #undef MEM_SUBSTRATE_MSG
        #if defined(AS_SOFTWARE_EMULATED_EEPROM)
            #undef MSG9
            #define MSG9 \n- " [2] 0B10000000 [Δ] [𝗪𝗔𝗥𝗡𝗜𝗡𝗚] ESP32 MCUs are defined (AS_SOFTWARE_EMULATED_EEPROM)."
            #define MEM_SUBSTRATE_MSG [𝗦𝗢𝗙𝗧𝗪𝗔𝗥𝗘 𝗘𝗠𝗨𝗟𝗔𝗧𝗘𝗗 𝗘𝗘𝗣𝗥𝗢𝗠]
        #else
            #define MEM_SUBSTRATE_MSG [𝗘𝗘𝗣𝗥𝗢𝗠]
        #endif
        #undef MSG8
        #define MSG8 \n- " [2] 0B10000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed with (USE_INTERNAL_EEPROM)."
        #if !defined(EEPROM_h) || !defined(__EEPROM_H__) 
            // for some reason it says 'EEPROM' was not declared in this scope even though i #include it below. So it needs it at the sketch i guess too
            #include <EEPROM.h>
            #define INCLUDES_EEPROM_H
        #endif
    #endif

    #if ((_2_OPTIMIZE bitor 0B10111111) == 0B11111111)
        #undef MSG11
        #undef OPTIONAL_BIAS
        #define OPTIONAL_BIAS(x)
        #define MSG11 \n- " [2] 0B01000000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Biases are disabled (NO_BIAS)."
        #define HAS_NO_BIAS true
        #define NO_BIAS
    #endif

    #if ((_2_OPTIMIZE bitor 0B11011111) == 0B11111111)
        #if defined(NO_BIAS)
            #error "💥 You can't have both NO_BIAS and MULTIPLE_BIASES_PER_LAYER."
        #endif
        #undef MSG12
        #define MSG12 \n- " [2] 0B00100000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You are using (MULTIPLE_BIASES_PER_LAYER)."
        #define MULTIPLE_BIASES_PER_LAYER
        #undef OPTIONAL_MULTI_BIAS
        #define OPTIONAL_MULTI_BIAS(x) , x
    #endif

    #if ((_2_OPTIMIZE bitor 0B11101111) == 0B11111111)
        #undef MSG13
        #if defined(NATIVE_OR_BARE_NN)
            #define MSG13 \n- " [2] 0B000X0000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] There's no native or bare-metal support for F() macro."
        #elif defined(ESP32)
            #define MSG13 \n- " [2] 0B000X0000 [I] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] PROGMEM on ESP32 is emulated, therefore F() macro is not used."
        #else
            #define MSG13 \n- " [2] 0B00010000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You are using F() macro for NN.print()."
            #undef F_MACRO
            #define F_MACRO F
        #endif
    #endif

    #if (((_2_OPTIMIZE bitor 0B11110111) == 0B11111111) or ((_2_OPTIMIZE bitor 0B11111011) == 0B11111111)) 
        #if (((_2_OPTIMIZE bitor 0B11110111) == 0B11111111) and ((_2_OPTIMIZE bitor 0B11111011) == 0B11111111)) 
            #error "💥 You can't use both int16_t and int8_t! use either 16 or 8."
        #endif
        #if defined(USE_64_BIT_DOUBLE)
            #error "💥 You can't USE_64_BIT_DOUBLE precision with USE_INT_QUANTIZATION."
        #endif
        #undef MSG14
        #undef IDFLOAT
        #undef TYPE_MEMMORY_READ_IDFLOAT 
        #undef MULTIPLY_BY_INT_IF_QUANTIZATION
        #undef CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION
        #if (_2_OPTIMIZE bitor 0B11110111) == 0B11111111
            #define MSG14 \n- " [2] 0B00001000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using int16_t quantization (NO_BACKPROP yet)."
            #define IDFLOAT int16_t
            #define TYPE_MEMMORY_READ_IDFLOAT(x) pgm_read_int16_t(&x)
            #define TYPE_MEMMORY_READ_IDFLOAT_NAME pgm_read_int16_t
        #else
            #define MSG14 \n- " [2] 0B00000100 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Using int8_t quantization (NO_BACKPROP yet)."
            #define IDFLOAT int8_t
            #define TYPE_MEMMORY_READ_IDFLOAT(x) pgm_read_int8_t(&x)
            #define TYPE_MEMMORY_READ_IDFLOAT_NAME pgm_read_int8_t
        #endif
        #define NO_BACKPROP
        #define USE_INT_QUANTIZATION

        IDFLOAT TYPE_MEMMORY_READ_IDFLOAT_NAME(const IDFLOAT* address) {
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
        #define MULTIPLY_BY_INT_IF_QUANTIZATION * ((DFLOAT)Q_FLOAT_RANGE/Q_INT_RANGE)

        #define CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(value) value
    #endif

    #if ((_2_OPTIMIZE bitor 0B11111101) == 0B11111111)
        #undef MSG15
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            #error "💥 You don't have to define both _1_ 0B00000100 (REDUCE_RAM_STATIC_REFERENCE) and _2_ 0B00000010 (REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)."
        #endif
        #define MSG15 \n- " [2] 0B00000010 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] If single NN object, use: _1_OPTIMIZE 0B00000100 instead."
        #define REDUCE_RAM_STATIC_REFERENCE
        #define REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS
    #endif
#endif


#if defined(_3_OPTIMIZE)
    #if ((_3_OPTIMIZE bitor 0B01111111) == 0B11111111)
        #if defined(USE_INTERNAL_EEPROM)
            #error "💥 You can't yet USE_INTERNAL_EEPROM and USE_EXTERNAL_FRAM together."
        #endif
        #if defined(USE_PROGMEM)
            #error "💥 You can't USE_EXTERNAL_FRAM and USE_PROGMEM together. Either disable `_3_OPTIMIZE 0B1` or `_1_OPTIMIZE 0B1` accordingly."
        #endif
        #undef MEM_SUBSTRATE_MSG
        #undef MSG17
        #define MSG17 \n- " [3] 0B10000000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not allowed with (USE_EXTERNAL_FRAM)."
        #define MEM_SUBSTRATE_MSG [𝗙𝗥𝗔𝗠]
        #define USE_EXTERNAL_FRAM
        #define NO_BACKPROP
        // #if !defined(FRAM_h) || !defined(__FRAM_H__) 
        //     #include "FRAM.h"
        // #endif
        // no need for #define INCLUDES_FRAM_H
    #endif

    #if ((_3_OPTIMIZE bitor 0B10111111) == 0B11111111)
        #undef MSG18
        #define MSG18 \n- " [3] 0B01000000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You enabled (RAM_EFFICIENT_HILL_CLIMB)."
        #define RAM_EFFICIENT_HILL_CLIMB
        #define AS_TYPE_OF_HILL_CLIMB
    #endif

    #if ((_3_OPTIMIZE bitor 0B11011111) == 0B11111111)
        #if defined(RAM_EFFICIENT_HILL_CLIMB)
            #error "💥 You can't use both (RAM_EFFICIENT_HILL_CLIMB) and (RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)."
        #endif
        #undef MSG18
        #define MSG18 \n- " [3] 0B00100000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Only pre-established NNs allowed with (RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)."
        #define RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW
        #define AS_TYPE_OF_HILL_CLIMB
        #define NO_BACKPROP
    #endif

    #if ((_3_OPTIMIZE bitor 0B11101111) == 0B11111111)
        #if !defined(RAM_EFFICIENT_HILL_CLIMB) and !defined(RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)
            #error "💥 You can't use (HILL_CLIMB_DYNAMIC_LEARNING_RATES) without enabling either (RAM_EFFICIENT_HILL_CLIMB) or (RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)"
        #endif
        #undef MSG19
        #define MSG19 \n- " [3] 0B00010000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You enabled support for (HILL_CLIMB_DYNAMIC_LEARNING_RATES)."
        #define HILL_CLIMB_DYNAMIC_LEARNING_RATES
    #endif

    #if ((_3_OPTIMIZE bitor 0B11110111) == 0B11111111)
        #undef MSG20
        #define MSG20 \n- " [3] 0B00001000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You enabled (SUPPORT_NO_HIDDEN_BACKPROP)."
        #define SUPPORT_NO_HIDDEN_BACKPROP
    #endif

    #if ((_3_OPTIMIZE bitor 0B11111011) == 0B11111111) // see #13
        #undef MSG21
        #define MSG21 \n- " [3] 0B00000100 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (DISABLE_STATIC_FOR_ACTS) is used."
        #define DISABLE_STATIC_FOR_ACTS
    #endif

    #if ((_3_OPTIMIZE bitor 0B11111101) == 0B11111111) // Using an optimization bit instead of __has_include due to the fact that "FS.h" is inside most of the cores and therefore it gets compiled
        #undef MSG23
        #if defined(NATIVE_OR_BARE_NN)
            #define MSG23 \n- " [3] 0B00000010 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (SUPPORTS_FS_FUNCTIONALITY) for (NATIVE_OR_BARE_NN) enabled." 
        #else
            #define MSG23 \n- " [3] 0B00000010 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (SUPPORTS_FS_FUNCTIONALITY) enabled."
        #endif
        #define SUPPORTS_FS_FUNCTIONALITY
    #endif

    #if ((_3_OPTIMIZE bitor 0B11111110) == 0B11111111)
        #if (!defined(USE_GRU__NB) and !defined(USE_LSTM__NB)) // REMINDER: ##30
            #error "💥 (REDUCE_RAM_DELETE__GATED_OUTPUTS) is only available for GRU & LSTM."
        #endif
        #undef MSG24
        #define MSG24 \n- " [3] 0B00000001 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (REDUCE_RAM_DELETE__GATED_OUTPUTS) enabled."
        #define REDUCE_RAM_DELETE__GATED_OUTPUTS
    #endif
#endif


#if defined(_4_OPTIMIZE)
    #if ((_4_OPTIMIZE bitor 0B01111111) == 0B11111111) // NOTE: error #31
        #undef MSG25
        #define MSG25 \n- " [4] 0B10000000 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (REDUCE_RAM_RESET_STATES_BY_DELETION) enabled."
        #define REDUCE_RAM_RESET_STATES_BY_DELETION
    #endif
#endif


// _5_OPTIMIZE will be here <-------------------------------
// TODO: PORTABLE_ACROSS_NN_ARCHITECTURES and add error if hardcoded RELATIVE_ACTIVATION_FUNCTION number is not defined #19 // SUPPORT_CROSS_DEFINITION_COMPATIBILITY_ACROSS_NN_TYPE_ARCHITECTURES
// TODO: DISABLE_TIMESTEP_LOGIC #17 or maybe SWITCH instead of DISABLE since by default plain/_ONLY RNNs of any type don't use it


// Keyword-based NN optimizations
//
#if !defined(NO_BIAS) && !defined(MULTIPLE_BIASES_PER_LAYER)
    #undef OPTIONAL_SINGLE_BIAS
    #define OPTIONAL_SINGLE_BIAS(x) , x
#endif

/// Messages
#define NN_ARCH_MSG [𝗗𝗘𝗡𝗦𝗘]

/// Casting/Converting the Function of NN into Type: LSTM GRU ANN RNN etc.
/// When Blank it default to either ANN or RNN
#define NN_TYPE_ARCHITECTURE
#define EXPAND_MACRO(x, z) x ## z
#define FUNCTION_OF(nn_type, nn_function) EXPAND_MACRO(nn_type, nn_function)

// (Default) type-holder/type-name for activation-function (and/or NN_TYPE_ARCHITECTURE and/or etc.)
#define LayerType byte
// (Default) Does nothing unlees: LayerType defined as LayerProps then it is Used to retrive the value of activation-function from the namespace of the struct
#define GET_ACTIVATION_FUNCTION_FROM(x) (x)

// Determins whether it is necessary or not for Layer to have LayerProps.arch
#define OPTIONAL_LAYER_TYPE_ARCHITECTURE(x)

// TODO: Might be more efficient (in terms of sketch size) to define zy_FROM as actual static functions for some cases
#define NUMBER_FROM(x, y, z) x * y
#define INDEX_FROM(x, y, z, w) x * y
#define SIZEOF_FROM(x, y, z) x

// (Bit-filed) Struct used when MULTIPLE_NN_TYPE_ARCHITECTURES to store the extra Layer's properties
struct LayerProps {
    #if defined(ACTIVATION__PER_LAYER)
        byte fx : 4;  // Activation Function
    #else
        byte  : 4;  // Skipping Activation Function | #19 might todo a way to default it with macro-define for cross-definition support
    #endif
    byte arch : 3;  // Architecture |  NOTE:  I could theoritically use 2 instead with something like `n + (n >> 1)` for remapping but not sure yet...
    byte      : 1;  // Skipping 1   |  TODO: (bias\no-bias)-selection ?
};

/// Number of States, Gates, or Outputs
#define NUMBER_OF_PATHS 1

#if defined(USE_DENSE_GRU_PAIR__NB)
    #error "💥 There is no DENSE + GRU support yet. (USE_DENSE_GRU_PAIR__NB)"
#endif
#if defined(USE_DENSE_LSTM_PAIR__NB)
    #error "💥 There is no DENSE + LSTM support yet. (USE_DENSE_LSTM_PAIR__NB)"
#endif

/// USE_RNN_LAYERS_ONLY && NO_BACKPROP
#if defined(USE_RNN__NB) or defined(USE_DENSE_RNN_PAIR__NB)
    #undef NN_ARCH_MSG
    #undef NUMBER_FROM
    #undef INDEX_FROM
    #undef SIZEOF_FROM
    #define WITH_RNN_USE
    #define HAS_HIDDEN_STATES
    #define NO_BACKPROP
    #if !defined(USE_DENSE_RNN_PAIR__NB) // in other words if defined(USE_RNN__NB)
        #define NUMBER_FROM(x, y, z) ((x * y) + (y * y)) 
        #define INDEX_FROM(x, y, z, w) (x * (y + z))
        #define SIZEOF_FROM(x, y, z) (x + y)
        #define USE_RNN_LAYERS_ONLY
        #define NN_ARCH_MSG [𝗥𝗡𝗡]
        #undef NN_TYPE_ARCHITECTURE
        #define NN_TYPE_ARCHITECTURE RNN_Only_
    #else
        // WARN: ##26 Reminder to either add 0-check or disable REDUCED_SKETCH_SIZE_DOT_PROD when I'll add the merged RNN+DENSE optimization (SLOW_PAIR_RNN_SKETCH_REDUCE) | I am saying this because when merged, I'm planing to pass `len` as `(me->PropsPerLayer[me->AtlayerIndex]).arch * _numberOfOutputs` in `accumulatedDotProduct(..., len )`
        #undef LayerType
        #define A_TYPE_OF_RNN_ARCHITECTURE RNN_Only_
        #undef OPTIONAL_LAYER_TYPE_ARCHITECTURE
        #define OPTIONAL_LAYER_TYPE_ARCHITECTURE(x) , x
        #define MULTIPLE_NN_TYPE_ARCHITECTURES
        #define NUMBER_FROM(x, y, z) ((x * y) + z * (y * y))
        #define INDEX_FROM(x, y, z, w) (x * (y + (z * w)))
        #define SIZEOF_FROM(x, y, z) (x + (z * y))
        #define USE_PAIR__DENSE_RNN
        #define USE_DENSE_PAIR
        #define NN_ARCH_MSG [𝗗𝗘𝗡𝗦𝗘+𝗥𝗡𝗡]
        #define LayerType LayerProps
        // (SINGLE_TIMESTEP_THRESHOLD) Defaults to being enabled
        #define ENABLE_SINGLE_TIMESTEP_THRESHOLD
        #if defined(ACTIVATION__PER_LAYER)
            #undef GET_ACTIVATION_FUNCTION_FROM
            #define GET_ACTIVATION_FUNCTION_FROM(x) ((x).fx)
            #define RNN(fx) {fx,1}
            #define DENSE(fx) {fx,0}
        #else
            #define RNN() {1}
            #define DENSE() {0}
        #endif
        // DENSE+RNN doesn't support FeedForward_Individual-type functions yet, therefore we #undef it | see also #24
        #undef SUPPORTS_INDIVIDUAL_FEEDFORWARD
    #endif

// TODO: either use  (x * y) * (!(bool)z) + z * ((x * y) + (y * y)); or if else branch | As of 2025-11-05 11:09:37 AM this might not be needed alsmost at all since SIZEOF_FROM logic changed but good to have this as a note here
// NUMBER_OF_PATHS for dense pairs might need to become NUMBER_OF_PATHS(z) where z will be an arch and all together be defined as something like NUMBER_OF_PATHS(z) (((bool)z) * z) ?
#elif defined(USE_GRU__NB) // (TensorFlow GRU(...reset_after=False) // #21 #30
    #undef NN_ARCH_MSG
    #undef NUMBER_FROM
    #undef INDEX_FROM
    #undef SIZEOF_FROM
    #undef NUMBER_OF_PATHS
    #define WITH_RNN_USE
    #define USE_GRU_LAYERS_ONLY
    #define HAS_HIDDEN_STATES
    #define NUMBER_OF_PATHS 3
    #define NUMBER_FROM(x, y, z) ((x * y) + (y * y)) * NUMBER_OF_PATHS
    #define INDEX_FROM(x, y, z, w) (x * ((y + z) * NUMBER_OF_PATHS))
    #define SIZEOF_FROM(x, y, z) (x + y)
    #define HAS_GATED_OUTPUTS // NOTE: It enables gateActivationOf too
    #define NO_BACKPROP
    // 2025-04-30 02:19:56 PM  TODO: It might be a good idea to have both "single-bias" but also "single-bias-per-gate" (make sure to iterate biasesFromPoint if per-gate)
    // 2025-04-30 02:31:34 PM  NOTE: But make sure to use a selective-OPTIONAL_BIAS type-of macro instead of this #14 | 2025-05-03 03:21:35 AM I guess?
    //
    #if defined(Softmax) // #16
        #error "💥 There is no Softmax support when you (USE_GRU_LAYERS_ONLY)"
    #endif
    // GRU doesn't support FeedForward_Individual-type functions yet, therefore we #undef it | see also #24
    #undef SUPPORTS_INDIVIDUAL_FEEDFORWARD
    // Defining Explicit type architecture of the NN
    #undef NN_TYPE_ARCHITECTURE
    #define NN_TYPE_ARCHITECTURE GRU_Only_
    #if defined(GRU_ACT) // I may add GRU_DER (...ivative) when I 'll support backprop
        #define ID_Softmax 1
        #define MAP_HELPER(x) ID_ ## x
        #define INDEX_NN(x) MAP_HELPER(x)
        #if INDEX_NN(GRU_ACT) == ID_Softmax // https://stackoverflow.com/a/79556797/11465149
            #error "💥 (GRU_ACT) You are not allowed to use Softmax-activation-function for update-or-reset gate."
        #endif
        #define GRU_ACTIVATION_FUNCTION GRU_ACT
        #define NN_ARCH_MSG [𝗚𝗥𝗨.GRU_ACT]
    #else
        #define GRU_ACTIVATION_FUNCTION Sigmoid
        #define NN_ARCH_MSG [𝗚𝗥𝗨]
    #endif

#elif defined(USE_LSTM__NB) // #21 #30
    #undef NN_ARCH_MSG
    #undef NUMBER_FROM
    #undef INDEX_FROM
    #undef SIZEOF_FROM
    #undef NUMBER_OF_PATHS
    #define WITH_RNN_USE
    #define USE_LSTM_LAYERS_ONLY
    #define HAS_HIDDEN_STATES
    #define NUMBER_OF_PATHS 4
    #define NUMBER_FROM(x, y, z) ((x * y) + (y * y)) * NUMBER_OF_PATHS
    #define INDEX_FROM(x, y, z, w) (x * ((y + z) * NUMBER_OF_PATHS))
    #define SIZEOF_FROM(x, y, z) (x + y)
    #define HAS_GATED_OUTPUTS // NOTE: It enables gateActivationOf too
    #define NO_BACKPROP
    #if defined(Softmax) // #16
        #error "💥 There is no Softmax support when you (USE_LSTM_LAYERS_ONLY)"
    #endif
    // LSTM doesn't support FeedForward_Individual-type functions yet, therefore we #undef it | see also #24
    #undef SUPPORTS_INDIVIDUAL_FEEDFORWARD
    // Defining Explicit type architecture of the NN
    #undef NN_TYPE_ARCHITECTURE
    #define NN_TYPE_ARCHITECTURE LSTM_Only_
    #if defined(LSTM_ACT) // I may add LSTM_DER (...ivative) when I 'll support backprop
        #define ID_Softmax 1
        #define MAP_HELPER(x) ID_ ## x
        #define INDEX_NN(x) MAP_HELPER(x)
        #if INDEX_NN(LSTM_ACT) == ID_Softmax // https://stackoverflow.com/a/79556797/11465149
            #error "💥 (LSTM_ACT) You are not allowed to use Softmax-activation-function for gates."
        #endif
        #define LSTM_ACTIVATION_FUNCTION LSTM_ACT
        #define NN_ARCH_MSG [𝗟𝗦𝗧𝗠.LSTM_ACT]
    #else
        #define LSTM_ACTIVATION_FUNCTION Sigmoid
        #define NN_ARCH_MSG [𝗟𝗦𝗧𝗠]
    #endif
#endif


// Macro for passing the layer's index to layer's print() function for printing the OPTIONAL_TIME when EEPROM or FRAM is used (due to the absence of AtlayerIndex)
#define OPTIONAL_TIME__TYPE_MEMMORY_INDEX(x)

// Basicly, if defined as any kind of paired-architectures   : it auto-enables  (SINGLE_TIMESTEP_THRESHOLD) by default, unless user defines (DISABLE_...)
// Alternatively, If simply a single-architecture is defined : it auto-DISABLES (SINGLE_TIMESTEP_THRESHOLD) by default, unless user defines ( ENABLE_...)
#if (!defined(DISABLE_SINGLE_TIMESTEP_THRESHOLD) and defined(ENABLE_SINGLE_TIMESTEP_THRESHOLD)) // #17
    #undef OPTIONAL_TIME
    #undef TIMESTEP_MSG
    #define TIMESTEP_MSG [TIME-SCHEDULED]
    #define OPTIONAL_TIME(x, y) , x , y
    #define SINGLE_TIMESTEP_THRESHOLD
    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
        #undef OPTIONAL_TIME__TYPE_MEMMORY_INDEX
        #define OPTIONAL_TIME__TYPE_MEMMORY_INDEX(x) x
    #endif
    #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD) // TODO: ##24 cause I have to figure out SINGLE_TIMESTEP_THRESHOLD-suppport at NeuralNetwork::Layer::FeedForward_Individual
        #undef SUPPORTS_INDIVIDUAL_FEEDFORWARD
    #endif
#else
    // Default Message related to TIMESTEP_THRESHOLD
    #define TIMESTEP_MSG
    // Default macro expansion
    #define OPTIONAL_TIME(x, y)
#endif


#if defined(REDUCE_RAM_RESET_STATES_BY_DELETION)  // ##31
    #if !defined(HAS_HIDDEN_STATES)
        #error "💥 Please disable `#define _4_OPTIMIZE 0B10000000` | You can't use REDUCE_RAM_RESET_STATES_BY_DELETION with an MLP (a neural-netwrok architecture, that doesn't have hidden-states)."
    #endif
    #if defined(USE_DENSE_PAIR)
        #error "💥 Please disable `#define _4_OPTIMIZE 0B10000000` | You can't USE_DENSE_PAIR with REDUCE_RAM_RESET_STATES_BY_DELETION yet."
    #endif
#endif

// TODO: Once I'll add support for FRAM I need to change those errors for RAM_EFFICIENT_HILL_CLIMB to inform the user to use RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW instead! 
// Because there is no initialization nor destrcuction proccess of dynamic parameters during FRAM usage
#if defined(RAM_EFFICIENT_HILL_CLIMB) or defined(RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)
    #if defined(USE_INTERNAL_EEPROM)
        #error "💥 You can't USE_INTERNAL_EEPROM with HillClimb yet."
    #endif
    #if defined(USE_EXTERNAL_FRAM)
        #error "💥 You can't USE_EXTERNAL_FRAM with HillClimb yet."
    #endif
    #if defined(USE_INT_QUANTIZATION)
        #error "💥 You can't USE_INT_QUANTIZATION with HillClimb yet."
    #endif
    #if defined(USE_PROGMEM)
        #error "💥 You can't USE_PROGMEM with HillClimb"
    #endif
#endif

#if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
    #if defined(REDUCE_RAM_WEIGHTS_COMMON)
        #undef MSG3
        #define MSG3 \n- " [1] 0B000X0000 [Χ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] There is no need for (REDUCE_RAM_WEIGHTS_LVLX)"
    #endif
    #if defined(ACTIVATION__PER_LAYER)
        #define SIZEOF_FX sizeof(LayerType)
    #endif
#endif

// Handle this optimization last because above might add other ones that disable NO_BACKPROP
#if defined(_2_OPTIMIZE) and ((_2_OPTIMIZE bitor 0B11111110) == 0B11111111)
    #undef MSG16
    #if defined(NO_BACKPROP)
        #define MSG16 \n- " [2] 0B00000001 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] NO_BACKPROP is already set!"
    #else
        #define MSG16 \n- " [2] 0B00000001 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Disabled Backpropagation."
        #define NO_BACKPROP
    #endif
#endif

// Disable SIMD parallel processing if double-precision or int-quntization is enabled
#if (!defined(DISABLE_SIMD_SUPPORT) && (defined(CONFIG_IDF_TARGET_ESP32S3) || defined(USE_ESP_SIMD)))
    #undef MSG22
    #if defined(USE_64_BIT_DOUBLE)
        #define MSG22 \n- " [1] 0B00100000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] SIMD disabled, there is no support when double precision."
    #elif defined(USE_INT_QUANTIZATION)
        #define MSG22 \n- " [1] 0B00100000 [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] SIMD disabled, there is no support for USE_INT_QUANTIZATION."
    #else
        #define ESP_SUPPORTS_SIMD
        #undef ACCUMULATED_DOT_PRODUCT_OF
        // TODO: tmp_dest will be removed once I implement the custom-assembly-dotprod function of esp32 and stuff
        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            // We keep me->i_j+= len; for Backprop but //TODO: might remove it when (NO_BACKPROP and (NO USE_RNN_LAYERS_ONLY))

            /* 💥 𝗡𝗢𝗧𝗘: Try `#define _1_OPTIMIZE 0B00100000` to `DISABLE_SIMD_SUPPORT` OR simply use `float` values as inputs if you're having type-errors */ #define ACCUMULATED_DOT_PRODUCT_OF(src1, src2, dest, len) do { dsps_dotprod_f32(src1, src2, &me->tmp_dest, len); *dest+=me->tmp_dest; me->i_j+=len; } while(0)
        #else
            /* 💥 𝗡𝗢𝗧𝗘: Try `#define _1_OPTIMIZE 0B00100000` to `DISABLE_SIMD_SUPPORT` OR simply use `float` values as inputs if you're having type-errors */ #define ACCUMULATED_DOT_PRODUCT_OF(src1, src2, dest, len) do { dsps_dotprod_f32(src1, src2, &me->tmp_dest, len); *dest+=me->tmp_dest; } while(0)
        #endif
        #define MSG22 \n- " [1] 0B00X00000 [I] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] You are using SIMD acceleration."
        #if defined(REDUCED_SKETCH_SIZE_DOT_PROD)
            #undef MSG4
            #define MSG4 \n- " [1] 0B0000X000 [Χ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (REDUCED_SKETCH_SIZE_DOT_PROD) not used since (ESP_SUPPORTS_SIMD)."
        #endif
        #include "esp_dsp.h"
    #endif
#endif

// REMINDER DO NOT UNCOMMENT THIS!!!!!! BECAUSE IT WILL RESULT ON ESP32-S3 NOT COMPILING WITH USE_PROGMEM or USE_INTERNAL_EEPROM AT ALL | i keep it here as a future reminder
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

// STR(AX) | pragma message | AN = Activation Name | ALL_A = All | CA = Custom Activation
#define AN_1
#define AN_2
#define AN_3
#define AN_4
#define AN_5
#define AN_6
#define AN_7
#define AN_8
#define AN_9
#define AN_10
#define AN_11
#define AN_12
#define AN_13
#define AN_14
#define ALL_A

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


#if defined(LeakyELU)
    #error "💥 Replace LeakyELU with LeakyReLU. That was a stupid typo of mine."
#endif

#if defined(Sigmoid) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_1
    #undef ACT1
    #undef Sigmoid
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT1 1
    #define ACTIVATION 
    #define ACTIVATION_FUNCTION Sigmoid
    #define Sigmoid Sigmoid
    #define AN_1 |> Sigmoid 
#endif
#if defined(Tanh) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_2
    #undef ACT2
    #undef Tanh
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT2 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Tanh
    #define Tanh Tanh
    #define AN_2 |> Tanh 
#endif
#if defined(ReLU) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_3
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
    #define AN_3 |> ReLU 
#endif
#if defined(LeakyReLU) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_4
    #undef ACT4
    #undef LeakyReLU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT4 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION LeakyReLU
    #define SUPPORTS_CLIPPING // i mean  "supports" / usually-needs  ?
    #define LeakyReLU LeakyReLU
    #define AN_4 |> LeakyReLU 
#endif
#if defined(ELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_5
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
    #define AN_5 |> ELU 
#endif
#if defined(SELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_6
    #undef ACT6
    #undef SELU
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT6 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION SELU
    #define SELU SELU
    #define AN_6 |> SELU 
#endif
#if defined(Softmax)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_7
    #undef ACT7
    #undef Softmax
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT7 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Softmax
    #define Softmax Softmax
    #define AN_7 |> Softmax 
#endif
#if defined(Identity)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef AN_8
    #undef ACT8
    #undef Identity
    #undef ACTIVATION
    #undef ACTIVATION_FUNCTION
    #undef DEFAULT_ACTIVATION_FUNCTION
    #define ACT8 1
    #define ACTIVATION
    #define ACTIVATION_FUNCTION Identity
    #define Identity Identity
    #define AN_8 |> Identity 
#endif
#if defined(BinaryStep) && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_9
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
    #define AN_9 |> BinaryStep 
#endif
#if defined(Softplus)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_10
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
    #define AN_10 |> Softplus 
#endif
#if defined(SiLU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_11
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
    #define AN_11 |> SiLU 
#endif
#if defined(GELU)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_12
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
    #define AN_12 |> GELU 
#endif
#if defined(Mish)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_13
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
    #define AN_13 |> Mish 
#endif
#if defined(Gaussian)  && (defined(ACTIVATION__PER_LAYER) || !defined(ACTIVATION))
    #undef NB
    #undef AN_14
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
    #define AN_14 |> Gaussian 
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
    #define CUSTOM_AF1_DEFINITION IS_STATIC DFLOAT CUSTOM_AF1(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF1)
        #undef CUSTOM_DF1
        #undef CUSTOM_DF1_DEFINITION
        #define CUSTOM_DF1 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF1, Der)
        #define CUSTOM_DF1_DEFINITION IS_STATIC DFLOAT CUSTOM_DF1(const float &fx);
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
    #define CUSTOM_AF2_DEFINITION IS_STATIC DFLOAT CUSTOM_AF2(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF2)
        #undef CUSTOM_DF2
        #undef CUSTOM_DF2_DEFINITION
        #define CUSTOM_DF2 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF2, Der)
        #define CUSTOM_DF2_DEFINITION IS_STATIC DFLOAT CUSTOM_DF2(const DFLOAT &fx);
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
    #define CUSTOM_AF3_DEFINITION IS_STATIC DFLOAT CUSTOM_AF3(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF3)
        #undef CUSTOM_DF3
        #undef CUSTOM_DF3_DEFINITION
        #define CUSTOM_DF3 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF3, Der)
        #define CUSTOM_DF3_DEFINITION IS_STATIC DFLOAT CUSTOM_DF3(const DFLOAT &fx);
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
    #define CUSTOM_AF4_DEFINITION IS_STATIC DFLOAT CUSTOM_AF4(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF4)
        #undef CUSTOM_DF4
        #undef CUSTOM_DF4_DEFINITION
        #define CUSTOM_DF4 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF4, Der)
        #define CUSTOM_DF4_DEFINITION IS_STATIC DFLOAT CUSTOM_DF4(const DFLOAT &fx);
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
    #define CUSTOM_AF5_DEFINITION IS_STATIC DFLOAT CUSTOM_AF5(const DFLOAT &x);
    #define CSTA ||| (𝗖𝗨𝗦𝗧𝗢𝗠)
    #if defined(CUSTOM_DF5)
        #undef CUSTOM_DF5
        #undef CUSTOM_DF5_DEFINITION
        #define CUSTOM_DF5 CONCATENATE_WITHOUT_SPACE(CUSTOM_AF5, Der)
        #define CUSTOM_DF5_DEFINITION IS_STATIC DFLOAT CUSTOM_DF5(const DFLOAT &fx);
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


// NUM_OF_USED_ACTIVATION_FUNCTIONS is the number that initializes the size of the array-of-pointers to activation-functions (and derivative ones)
// While, SOFTMAX_POSITION_IN_ARRAY is the position at which the softmax-activation function is present, based on what other activation-functions have been enabled to be compiled
#define NUM_OF_USED_ACTIVATION_FUNCTIONS (ACT1 + ACT2 + ACT3 + ACT4 + ACT5 + ACT6 + ACT7 + ACT8 + ACT9 + ACT9 + ACT10 + ACT11 + ACT12 + ACT13 + ACT14 + CACT1 + CACT2 + CACT3 + CACT4 + CACT5)
#define SOFTMAX_POSITION_IN_ARRAY (ACT1 + ACT2 + ACT3 + ACT4 + ACT5 + ACT6)


// vvv Meaning that if not exclusivly defined one (or more) ACTIVATION function
#if !defined(ACTIVATION)
    #if defined(ACTIVATION__PER_LAYER)
        // ACTIVATE ALL FUNCTIONS
        #if defined(USE_GRU_LAYERS_ONLY) or defined(USE_LSTM_LAYERS_ONLY)// #16
            #error "💥 There's no support for (ALL_ACTIVATION_FUNCTIONS) with GRU or LSTM, since Softmax is not supported. Please explicitly #define any activation-function you want."
        #endif
        #if !defined(DISABLE_STATIC_FOR_ACTS)
            #undef MSG21
            #define DISABLE_STATIC_FOR_ACTS 
            #define MSG21 \n- " [3] 0B00000100 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (DISABLE_STATIC_FOR_ACTS) is auto-enabled due to (ALL_ACTIVATION_FUNCTIONS), specifically due to Softmax."
        #endif
        #define NO_BACKPROP
        #define ALL_ACTIVATION_FUNCTIONS
        #undef ALL_A
        #define ALL_A |> "(ALL_ACTIVATION_FUNCTIONS)"
        #undef NUM_OF_USED_ACTIVATION_FUNCTIONS
        #define NUM_OF_USED_ACTIVATION_FUNCTIONS (14 + CACT1 + CACT2 + CACT3 + CACT4 + CACT5)
        #undef MSG10
        #define MSG10 \n- "////////////// [Δ] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] Backpropagation is not Allowed With (ALL_ACTIVATION_FUNCTIONS)."
    #else
        //ENABLE DEFAULT ACTIVATION FUNCTION
        // i will also create a mechanism to show #error if more than one is defined with B opperations?
        #undef AN_1
        #undef Sigmoid
        #define DEFAULT_ACTIVATION_FUNCTION
        #define ACTIVATION //Sigmoid default but for more than one you must declare it
        #define ACTIVATION_FUNCTION Sigmoid
        #define Sigmoid Sigmoid
        #define AN_1 |> Sigmoid 
    #endif
#endif


// Check if there's NO_TRAINING_METHOD
#if defined(NO_BACKPROP) && !defined(AS_TYPE_OF_HILL_CLIMB)
    #define NO_TRAINING_METHOD
#endif


#define MAKE_FUN_NAME1(actname,value) actname(value)
#define MAKE_FUN_NAME2(actname,value) actname ## Der(value)

#define ACTIVATE_WITH(actname,value) MAKE_FUN_NAME1(actname,value)
#define DERIVATIVE_OF(actname,value) MAKE_FUN_NAME2(actname,value)


//LOSS | If there's no Loss function definition and no DISABLE_MSE definition, define the Default  | MEAN_SQUARED_ERROR = Default
#if !defined(CATEGORICAL_CROSS_ENTROPY) and !defined(BINARY_CROSS_ENTROPY) and !defined(MEAN_SQUARED_ERROR) and !defined(DISABLE_MSE)
    #define  DEFAULT_LOSS
#endif

// #13 | Don't Worry about IS_STATIC in CUSTOM_AFX, I just relised that even though they are defined with the previous definition of IS_STATIC, it happens that the definition is expanded when used not when defined!
// "Macros are never replaced in the body of a #define directive..." see also https://stackoverflow.com/a/42096144/11465149
#if defined(DISABLE_STATIC_FOR_ACTS) || defined(Softmax)
    #if defined(Softmax)
        // Even though this condition is not necessary yet, it's nice to be here just in case I do anything more crazy involving (DISABLE_STATIC_FOR_ACTS) somewhere else in the future
        #if !defined(DISABLE_STATIC_FOR_ACTS)
            #define DISABLE_STATIC_FOR_ACTS
        #endif
        #undef MSG21
        #define MSG21 \n- " [3] 0B00000100 [Ι] [𝗥𝗲𝗺𝗶𝗻𝗱𝗲𝗿] (DISABLE_STATIC_FOR_ACTS) is auto-enabled due to Softmax."
    #endif
    #undef IS_STATIC
    #undef IS_IN_LAYER_SCOPE
    #undef IS_THIS
    #define IS_STATIC
    #define IS_IN_LAYER_SCOPE Layer::
    #define IS_THIS this->*
#endif


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define INFORMATION LOVE __NN_VERSION__ MSG0 MSG1 MSG2 MSG22 MSG3 MSG4 MSG5 MSG6 MSG7 MSG8 MSG9 MSG10 MSG11 MSG12 MSG13 MSG14 MSG15 MSG16 MSG17 MSG18 MSG19 MSG20 MSG21 MSG23 MSG24 MSG25 \n\n 𝗨𝗦𝗜𝗡𝗚 MEM_SUBSTRATE_MSG NN_ARCH_MSG TIMESTEP_MSG [ƒx] ALL_A AN_1 AN_2 AN_3 AN_4 AN_5 AN_6 AN_7 AN_8 AN_9 AN_10 AN_11 AN_12 AN_13 AN_14 CSTA CA1 CA2 CA3 CA4 CA5 |~|\n\n NB AN_9 AN_10 AN_11 AN_12 AN_13 AN_14 NB_CA1 NB_CA2 NB_CA3 NB_CA4 NB_CA5
#pragma message( STR(INFORMATION) )


#if defined(ACTIVATION__PER_LAYER)
    enum
    {
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Sigmoid)
            Idx_Sigmoid,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Tanh)
            Idx_Tanh,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ReLU)
            Idx_ReLU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyReLU)
            Idx_LeakyReLU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
            Idx_ELU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
            Idx_SELU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
            Idx_SoftmaxSum,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Identity)
            Idx_Identity,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(BinaryStep)
            Idx_BinaryStep,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softplus)
            Idx_Softplus,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SiLU)
            Idx_SiLU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(GELU)
            Idx_GELU,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Mish)
            Idx_Mish,
        #endif
        #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Gaussian)
            Idx_Gaussian,
        #endif

        #if defined(CUSTOM_AF1)
            Idx_ ## CUSTOM_AF1,
        #endif
        #if defined(CUSTOM_AF2)
            Idx_ ## CUSTOM_AF2,
        #endif
        #if defined(CUSTOM_AF3)
            Idx_ ## CUSTOM_AF3,
        #endif
        #if defined(CUSTOM_AF4)
            Idx_ ## CUSTOM_AF4,
        #endif
        #if defined(CUSTOM_AF5)
            Idx_ ## CUSTOM_AF5,
        #endif
    };
#endif


// i might change static variables to plain variables and just pass a pointer from outer class?
class NeuralNetwork
{
private:
    #if defined(SINGLE_TIMESTEP_THRESHOLD) // #17
        byte timestep = 0;
        byte threshold;
        byte atIndex;
        bool is_threshold_reached(const unsigned int i);
    #endif

    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
        unsigned int address = 0;
        template< typename T > T get_type_memmory_value(unsigned int &addr);
        #if defined(ACTIVATION__PER_LAYER)
            byte F1; // first activation function only for use in (type_memmory)-FeedForward_Individual
        #endif
    #endif

    #if defined(USE_EXTERNAL_FRAM)
        FRAM *fram;
    #endif

    #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8
        bool isAllocdWithNew = true;  // If weights and biases are allocated with new, for the destractor later | TODO: #if !defined(USE_PROGMEM) and etc. in constructors
    #endif

    #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)
        unsigned int Individual_Input = 0;
    #endif
    #if !defined(NO_BACKPROP)
        const DFLOAT *_inputs;        // Pointer to primary/first Inputs Array from Sketch    .
    #endif                            // (Used for backpropagation)                           .

    #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY)
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
            IS_CONST IDFLOAT *bias;     // bias    of this     layer  | or biases if MULTIPLE_BIASES_PER_LAYER enabled | Please do not wrap it into #ifdef USE_INTERNAL_EEPROM because it is being used when (type_memmory)-FeedForward_Individual
        #endif
        DFLOAT *outputs;                // outputs of this     layer  [1D Array] pointers.

        #if defined(USE_LSTM_LAYERS_ONLY)
            DFLOAT *cellStates;       // LSTM cell-states of this layer at time t  [1D Array] pointers.
        #endif

        // TODO: REDUCE_RAM_DELETE__GATED_OUTPUTS | I need to also make an optimization for static fixed size gatedOutputs amongs NNs and layers (a bit more manual labor for end-user though). Could be done for outputs too, although it might be a bit more complex
        // inside NeuralNetwork class? definatelly something like: DFLOAT gatedOutputs[CONST_GATED_SIZE];
        #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // I used &&! because it seems better to keep it locally in stack see #29
            DFLOAT *gatedOutputs; // GRU: (z_t) The Outputs of update-gate at time t & (r_t) The Outputs of reset-gate at time t || LSTM: Gates [...]
        #endif

        #if defined(HAS_HIDDEN_STATES)
            void resetStates();
            #if defined(USE_DENSE_PAIR) 
                DFLOAT *hiddenStates = NULL; // Nulling it to simplify deletion\deconstructor-logic (simply ignored by delete[])
            #else
                DFLOAT *hiddenStates;        // previous timestep's outputs of this layer  [1D Array] pointers.
            #endif
        #endif

        #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
            void initializeStates();
        #endif
        
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
            Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture = 0), NeuralNetwork * const NN = NULL ); // #0  | defined(NO_BIAS) is there 2024-03-02
        #endif

        #if defined(NO_BIAS)
            Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, IS_CONST IDFLOAT *default_Weights OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture = 0), NeuralNetwork * const NN = NULL ); // #1  #(used if NOT #REDUCE_RAM_WEIGHTS_LVL2 defined)
            Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, bool has_no_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture = 0), NeuralNetwork * const NN = NULL ); // has_no_bias is something the compiler 99% will optimize\remove | This is just a trick for distinguishing the constructors from the one who auto-generates the weights
        #else
            Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, IS_CONST IDFLOAT *default_Bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture = 0), NeuralNetwork * const NN = NULL ); //                                       #(used if     #REDUCE_RAM_WEIGHTS_LVL2 defined)
            Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, IS_CONST IDFLOAT *default_Weights, IS_CONST IDFLOAT *default_Bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture = 0), NeuralNetwork * const NN = NULL ); // #1  #(used if NOT #REDUCE_RAM_WEIGHTS_LVL2 defined)
        #endif


        // NOTE: We keep all `Layer::...FeedForward_Individual` seperate insted of `void FUNCTION_OF(...)` for future implementation of multi-type-memmory NNs (during runtime)
        #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)
            #if defined(USE_RNN_LAYERS_ONLY) // #20 // ##25 we don't need `or defined(USE_PAIR__DENSE_RNN)` because by default we merge them in `FeedForward_Individual`
                void RNN_Only_FeedForward_Individual(const DFLOAT &input, const unsigned int j);
            #endif
            void FeedForward_Individual(const DFLOAT &input, const unsigned int j);
        #endif

        // NOTE: src2 is IDFLOAT not just DFLOAT !!! | src2 is meant to be weights
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            template<typename T> void accumulatedDotProduct(const T *src, DFLOAT *dest, unsigned int len); // WithSrc2Address
        #else
            template<typename T> void accumulatedDotProduct(const T *src1, const IDFLOAT *src2, DFLOAT *dest, unsigned int len);
        #endif

        #if defined(HAS_GATED_OUTPUTS)
            #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                template<typename T, typename T2> void gateActivationOf(const T *inputs, const DFLOAT *inputs2 OPTIONAL_SINGLE_BIAS(const DFLOAT tmp_single_bias), T2 activate, DFLOAT *_outputs);
            #else
                template<typename T, typename T2> void gateActivationOf(const T *inputs, const DFLOAT *inputs2 OPTIONAL_MULTI_BIAS(const IDFLOAT *b)             , T2 activate, DFLOAT *_outputs, const unsigned int offset=0);
            #endif
        #endif

        // NOTE: We keep all `Layer::...FeedForward` seperate insted of `void FUNCTION_OF(...)` for future implementation of multi-architectural NNs (during runtime)
        #if defined(USE_GRU_LAYERS_ONLY)
            template<typename T> void GRU_Only_FeedForward(const T *inputs);
        #endif
        #if defined(USE_LSTM_LAYERS_ONLY)
            template<typename T> void LSTM_Only_FeedForward(const T *inputs);
        #endif
        #if defined(USE_RNN_LAYERS_ONLY) or defined(USE_PAIR__DENSE_RNN)
            template<typename T> void RNN_Only_FeedForward(const T *inputs);
        #endif
        template<typename T> void FeedForward(const T *inputs); // Calculates the outputs() of layer.


        #if !defined (NO_BACKPROP)
            void BackPropOutput(const DFLOAT *_expected_, const DFLOAT *inputs);
            void BackPropHidden(const Layer *frontLayer, const DFLOAT *inputs);
            // Common Compute\train gamma Weights preLgamma (and MULTIPLE_BIASES_PER_LAYER if defined)
            void CommonCompute(DFLOAT &gamma, DFLOAT preLgammaORgamma, const DFLOAT *inputs, unsigned int i, unsigned int j);
        #endif

        // (I guess) No need for encapsulation of this function into macro when all error-funtions (eg. MSE, ...) are disabled, since (it will be blank) the compiler will optimize it anyways for any user that uses it.
        template<typename T> void ComputeSummedErrors(const T *_expected_);


        // "Extra Math"
        IS_STATIC DFLOAT erf(DFLOAT x);

        //if i actually consider using other complicated activation functions i might need to think again about the before_Activation_output Array [...]
        IS_STATIC DFLOAT Sigmoid     (const DFLOAT &x ); // Sigmoid Activation Function 1/(1+e^(-x)) .
        IS_STATIC DFLOAT SigmoidDer  (const DFLOAT &fx); // Derivative of Sigmoid Activation Function.
        
        IS_STATIC DFLOAT Tanh        (const DFLOAT &x );
        IS_STATIC DFLOAT TanhDer     (const DFLOAT &fx);

        IS_STATIC DFLOAT ReLU        (const DFLOAT &x );
        IS_STATIC DFLOAT ReLUDer     (const DFLOAT &fx); // x is also fx on ReLU

        IS_STATIC DFLOAT LeakyReLU   (const DFLOAT &x );
        IS_STATIC DFLOAT LeakyReLUDer(const DFLOAT &fx);

        IS_STATIC DFLOAT ELU         (const DFLOAT &x ); // α = 1
        IS_STATIC DFLOAT ELUDer      (const DFLOAT &fx);
        
        IS_STATIC DFLOAT SELU        (const DFLOAT &x ); // Maybe use https://stackoverflow.com/a/42264773/11465149
        IS_STATIC DFLOAT SELUDer     (const DFLOAT &fx);

        void   Softmax     ();
        IS_STATIC DFLOAT SoftmaxSum  (const DFLOAT &x ); // returns exp(outputs[i] + (*bias)) to each output and then sums it into sumOfSoftmax
        IS_STATIC DFLOAT SoftmaxDer  (const DFLOAT &fx);

        IS_STATIC DFLOAT Identity    (const DFLOAT &x );
        IS_STATIC DFLOAT IdentityDer (const DFLOAT &x );

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
        IS_STATIC DFLOAT BinaryStep (const DFLOAT &x );
        IS_STATIC DFLOAT Softplus   (const DFLOAT &x );
        IS_STATIC DFLOAT SiLU       (const DFLOAT &x );
        IS_STATIC DFLOAT GELU       (const DFLOAT &x );
        IS_STATIC DFLOAT Mish       (const DFLOAT &x );
        IS_STATIC DFLOAT Gaussian   (const DFLOAT &x );
        

        // Print related functions
        #if defined(USE_GRU_LAYERS_ONLY) or defined(USE_LSTM_LAYERS_ONLY)
            #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                void printGateWeights(const unsigned int len);
                void gatePrint();
            #else
                void printGateWeights(const IDFLOAT *w, const unsigned int len);
                void gatePrint(const unsigned int offset OPTIONAL_MULTI_BIAS(const IDFLOAT *b));
            #endif
        #endif
        #if defined(USE_GRU_LAYERS_ONLY)
            void GRU_Only_print();
        #endif
        #if defined(USE_LSTM_LAYERS_ONLY)
            void LSTM_Only_print();
        #endif
        #if defined(USE_RNN_LAYERS_ONLY)
            void RNN_Only_print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex));
        #endif
        void print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex));
    };  


public:

    #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
        void initializeStates();
    #endif

    #if defined(HAS_HIDDEN_STATES)
        void resetStates();
    #endif

    #if defined(ESP_SUPPORTS_SIMD)
        DFLOAT tmp_dest; // TODO: tmp_dest will be removed once I implement the custom-assembly-dotprod function of esp32 and stuff
    #endif

    //just like "static IDFLOAT *wights" [...]  i might have a function to switch? | 2024-05-28 07:21:09 PM UPDATE: not sure what I meant back then... comment was moved here since `inline` change (this date), see also issue #35
    // this is the part where we declare an array-of-pointers-to-(activation and derivative) functions 
    #if defined(ACTIVATION__PER_LAYER)
        typedef DFLOAT (IS_IN_LAYER_SCOPE *method_function) (const DFLOAT &);
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
        unsigned int i_j = 0;
    #endif   

    #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
        #if !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM)
            unsigned int AtlayerIndex; // who 's gonna make a network with more than 255 layers :P ?!?!? but anyways i will use int or i will add byte too, using a property definition with bunch of other things like this for max optimization ... lol
        #endif
        // TODO: wrap PropsPerLayer to !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM) too (but first i need to wrap the rest of functions)
        // NOTE: 2025-01-18 06:20:30 AM (from a test i did) Seems that the compiler is smart enough to optimize this case (unless I did test it wrongly)
        LayerType *PropsPerLayer; // lets be realistic... byte because. xD | 2025-01-04 07:57:32 PM If I ever change it, remember to change SD-save too (and if anything else) | 2025-08-27 05:12:24 AM TODO: #17 see SD
    #endif

    // #5 This is the sum of the exp(outputs) of the previous layer (for All and each layer)
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
        DFLOAT sumOfSoftmax = 0;
    #endif

    // no negative values allowed, (just saying..)
    // Alphas and Lamdas of Activation Functions | #6 MACROS.
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyReLU)
        static DFLOAT AlphaLeaky;
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
        static DFLOAT AlphaSELU;
        static DFLOAT LamdaSELU;
    #endif        
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
        static DFLOAT AlphaELU;
    #endif


    Layer *layers;                   // layers in the network [1D Array].
    unsigned int numberOflayers = 0; // Number of layers.


    // unsigned float doesn't exist..? lol // #11
    #if !defined (NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) || defined(RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)
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
    #elif defined(USE_EXTERNAL_FRAM)
        NeuralNetwork(FRAM &framObj, unsigned int address);
    #endif
    // Here we only check for RAM_EFFICIENT_HILL_CLIMB because the whole purpose of RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW is to reduce sketch size by removing initialization and deconstructor logic
    #if !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB)
        NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), LayerType *_PropsPerLayer = NULL);                                              // #0
        NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), const DFLOAT LRw OPTIONAL_BIAS(const DFLOAT LRb), LayerType *_PropsPerLayer = NULL);          // #0
    #endif
    NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights OPTIONAL_BIAS(IS_CONST IDFLOAT *default_Bias), const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), LayerType *_PropsPerLayer = NULL); // #1
    
    #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)
        void  reset_Individual_Input_Counter();
        DFLOAT *FeedForward_Individual(const DFLOAT &input);
    #endif
    #if defined(USE_DENSE_PAIR)
        void paired_FeedForward(const DFLOAT *inputs, const unsigned int i);
    #endif
    template<typename T> DFLOAT *FeedForward(const T *inputs); // Moves Calculated outputs as inputs to next layer.
    
    //LOSS FUNCTIONS +common
    DFLOAT getMeanSqrdError           (unsigned int inputsPerEpoch); 
    DFLOAT getBinaryCrossEntropy      (unsigned int inputsPerEpoch); 
    DFLOAT getCategoricalCrossEntropy (unsigned int inputsPerEpoch); 
    DFLOAT loss  (DFLOAT &sum, DFLOAT &loss, unsigned int batch_size);        

    #if defined(RAM_EFFICIENT_HILL_CLIMB) or defined(RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)
        #if defined(HILL_CLIMB_DYNAMIC_LEARNING_RATES) // #11 | those variables should be private but anyways for now ...
            DFLOAT OldLearningRateOfWeights = 0.33 ; // Old Learning Rate of Weights in cases where learning rate changes dynamically by the user.
            #if !defined(NO_BIAS)
                DFLOAT OldLearningRateOfBiases  = 0.066; // Old Learning Rate of Biases in cases where learning rate changes dynamically by the user.
            #endif
        #endif

        unsigned int nn_seed   = 0;
        DFLOAT       old_error = -1;
        void climb(int8_t direction);
        bool HillClimb(DFLOAT error, DFLOAT tolerance);
    #endif
    template<typename T> void ComputeSummedErrors(const T *_expected_);

    #if !defined(NO_BACKPROP)
        void BackProp(const DFLOAT *expected);    // BackPropopagation - (error, delta-weights, etc.).
    #endif

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        NeuralNetwork(String file);
        bool load    (String file);
        bool save    (String file); // TODO: load\Save from RAM and PROGMEM, EEPROM, FRAM and other medias
        bool save_old(String file); // [OLD V.2.X.X] For migration to V3.0.0 or backwards compatibility
        bool load_old(String file); // [OLD V.2.X.X] For migration to V3.0.0 or backwards compatibility
    #endif
    #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) 
        template <typename T_File, typename = typename nn_enable_if<is_not_a_cstring<T_File>::value>::type> NeuralNetwork(T_File&  file);
        template <typename T_File, typename = typename nn_enable_if<is_not_a_cstring<T_File>::value>::type> bool save    (T_File&  file);
        template <typename T_File, typename = typename nn_enable_if<is_not_a_cstring<T_File>::value>::type> bool load    (T_File&  file);
    #endif

    #if defined(INCLUDES_EEPROM_H) and !defined(USE_INTERNAL_EEPROM)
        template< typename T > void put_type_memmory_value(unsigned int &addr, T val);
        unsigned int save(unsigned int atAddress); // EEPROM , FRAM
    #elif defined(INCLUDES_FRAM_H) and !defined(USE_EXTERNAL_FRAM)
        template< typename T > void put_type_memmory_value(FRAM &fram, unsigned int &addr, T val);
        unsigned int save(FRAM &fram, unsigned int atAddress); // FRAM
    #endif
    
    void print();
     
};
#if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyReLU)
    DFLOAT NeuralNetwork::AlphaLeaky = 0.01   ;
#endif
#if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
    DFLOAT NeuralNetwork::AlphaSELU  = 1.67326324;
    DFLOAT NeuralNetwork::LamdaSELU  = 1.05070098;
#endif
#if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
    DFLOAT NeuralNetwork::AlphaELU   = 1.0    ;
#endif
#if defined(REDUCE_RAM_STATIC_REFERENCE)
    NeuralNetwork *NeuralNetwork::me;
#endif
    


//=======================================================================================================================================================================
//NeuralNetwork.cpp
//=======================================================================================================================================================================
// #pragma region NeuralNetwork.cpp
    NeuralNetwork::NeuralNetwork() {
        #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8
            isAllocdWithNew = false;
        #endif
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif
    }

    #if defined(SUPPORTS_SD_FUNCTIONALITY)
        NeuralNetwork::NeuralNetwork(String file){
            #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8
                isAllocdWithNew = false;
            #endif
            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif
            load(file);
        }
    #endif

    #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY)
        template <typename T_File, typename>
        NeuralNetwork::NeuralNetwork(T_File& file){
            #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8
                isAllocdWithNew = false;
            #endif
            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif
            load(file);
        }
    #endif
    

    void NeuralNetwork::pdestract()
    {
        #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8 // !defined(USE_PROGMEM) && !defined(USE_INTERNAL_EEPROM)
            
            //NOTE: SPECIAL CASE
            #define SPECIAL_CASE_DESTRUCTION

            if (isAllocdWithNew){ // Because of undefined behavior in some MCUs like ESP32-C3
                unsigned int i=0;
                while(true) // for (unsigned int i = 0; i < numberOflayers; i++)
                {
                    #if !defined(REDUCE_RAM_WEIGHTS_COMMON) // && !defined(USE_PROGMEM)
                        for (unsigned int j = 0; j < layers[i]._numberOfOutputs; j++) // because of this i wont make _numberOfOutputs/inputs private :/ or maybe.. i ll see... or i will change them to const* ... what? i've just read it again lol
                        {
                            delete[] layers[i].weights[j];
                        }
                        delete[] layers[i].weights; // Delete the array of pointers
                    #endif

                    // #if !defined(USE_PROGMEM)
                    #if !defined(NO_BIAS)
                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                            delete[] layers[i].bias;
                        #else
                            delete layers[i].bias;
                        #endif
                    #endif
                    // #endif

                    /*
                    #if defined(REDUCE_RAM_WEIGHTS_LVL1) // && !defined(USE_PROGMEM) // no need for progmem condition because progmem is never going to be initialized with new
                        delete[] layers[i].weights;
                    #endif
                    */

                    if (i == numberOflayers-1){ // -1 because we need final-outputs(below) to be managed by user. (not gatedOutputs...)
                        break;
                    }

                    #if defined(USE_LSTM_LAYERS_ONLY) // NOTE: SEE SPECIAL CASE
                        delete[] layers[i].cellStates;
                    #endif

                    #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // NOTE: SEE SPECIAL CASE
                        delete[] layers[i].gatedOutputs;
                    #endif

                    #if defined(HAS_HIDDEN_STATES) // NOTE: SEE SPECIAL CASE
                        delete[] layers[i].hiddenStates;
                    #endif

                    // this macro-condition is needed since this runs even if NO_BACKPROP
                    #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                        delete[] layers[i].outputs;
                    #endif
                    i++;
                }

                #if defined(REDUCE_RAM_WEIGHTS_LVL2) // && !defined(USE_PROGMEM) // no need for progmem condition because progmem is never going to be initialized with new
                    delete weights;
                #endif
            }else{
                #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                    for (unsigned int i = 0; i < numberOflayers -1; i++){ // -1 because we need final-outputs to be managed by user.
                        delete[] layers[i].outputs;
                        #if defined(USE_LSTM_LAYERS_ONLY)
                            delete[] layers[i].cellStates;
                        #endif
                        #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                            delete[] layers[i].gatedOutputs;
                        #endif
                        #if defined(HAS_HIDDEN_STATES)
                            delete[] layers[i].hiddenStates;
                        #endif
                    }

                    //NOTE: SEE SPECIAL CASE

                #elif defined(HAS_HIDDEN_STATES)
                    for (unsigned int i = 0; i < numberOflayers; i++){
                        #if defined(USE_LSTM_LAYERS_ONLY)
                            delete[] layers[i].cellStates;
                        #endif
                        #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                            delete[] layers[i].gatedOutputs;
                        #endif
                        delete[] layers[i].hiddenStates;
                    }
                #endif
            }
        #elif !defined(REDUCE_RAM_DELETE_OUTPUTS)
            for (unsigned int i = 0; i < numberOflayers -1; i++){ // -1 because we need final-outputs to be managed by user.
                delete[] layers[i].outputs;
                #if defined(USE_LSTM_LAYERS_ONLY)
                    delete[] layers[i].cellStates;
                #endif
                #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                    delete[] layers[i].gatedOutputs;
                #endif
                #if defined(HAS_HIDDEN_STATES)
                    delete[] layers[i].hiddenStates;
                #endif
            }

            //NOTE: SPECIAL CASE
            #define SPECIAL_CASE_DESTRUCTION

        #elif defined(HAS_HIDDEN_STATES)
            for (unsigned int i = 0; i < numberOflayers; i++){
                #if defined(USE_LSTM_LAYERS_ONLY)
                    delete[] layers[i].cellStates;
                #endif
                #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                    delete[] layers[i].gatedOutputs;
                #endif
                delete[] layers[i].hiddenStates;
            }
        #endif

        #if (defined(ACTIVATION__PER_LAYER) || defined(MULTIPLE_NN_TYPE_ARCHITECTURES)) && (defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY))
            if (isAlreadyLoadedOnce){
                delete[] PropsPerLayer;
            }
        #endif  

        if (numberOflayers !=0){
            //NOTE: SPECIAL CASE
            #if defined(HAS_HIDDEN_STATES) && defined(SPECIAL_CASE_DESTRUCTION)
                #if defined(USE_LSTM_LAYERS_ONLY)
                    delete[] layers[numberOflayers -1].cellStates;
                #endif
                #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                    delete[] layers[numberOflayers -1].gatedOutputs;
                #endif
                delete[] layers[numberOflayers -1].hiddenStates;
            #endif
            delete[] layers;
        }
    }
    NeuralNetwork::~NeuralNetwork() { pdestract(); } 



    NeuralNetwork::NeuralNetwork(const unsigned int *layer_, IS_CONST IDFLOAT *default_Weights OPTIONAL_BIAS(IS_CONST IDFLOAT *default_Bias), const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), LayerType *_PropsPerLayer)
    {
        #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) || !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB) // #8
            isAllocdWithNew = false;
        #endif
        #if defined(SINGLE_TIMESTEP_THRESHOLD)
            threshold = _threshold;
            atIndex   = _atIndex;
        #endif
        numberOflayers = NumberOflayers - 1;

        layers = new Layer[numberOflayers]; // there has to be a faster way by alocating memory for example...
        #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
            PropsPerLayer = _PropsPerLayer;
        #endif  
        
        #if defined(REDUCE_RAM_STATIC_REFERENCE)
            me = this;
        #endif

        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            weights = default_Weights;
        #else
            unsigned int weightsFromPoint = 0;
        #endif

        // TODO: it might be a great idea to add an optimization removing biasesFromPoint and using plain i * ... computations for sketch-size reduction via a macro like `REDUCE_SKETCH_SIZE_AT_CONSTRUCTOR`
        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference" | 2024-03-12 04:01:04 PM todo γιατι οπως μου ειχε πει "ενα ροζ συννεφακι": "κανε ενα-ενα τα πραγματα, οχι ολα μαζι..."
            unsigned int biasesFromPoint = 0;
        #endif

        for (unsigned int i = 0; i < numberOflayers; i++)
        {
            #if defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                #if defined(NO_BIAS)
                    layers[i] = Layer(layer_[i], layer_[i + 1], HAS_NO_BIAS OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                #elif defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Bias[biasesFromPoint] OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch),this);
                #else
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Bias[i] OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch),this);
                #endif
            #else
                #if defined(NO_BIAS)
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint] OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                #elif defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], &default_Bias[biasesFromPoint] OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch),this);
                #else
                    layers[i] = Layer(layer_[i], layer_[i + 1], &default_Weights[weightsFromPoint], &default_Bias[i] OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch),this);
                #endif

                weightsFromPoint += NUMBER_FROM(layer_[i], layer_[i + 1], PropsPerLayer[i].arch); 
            #endif
            #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                #if defined(HAS_GATED_OUTPUTS)
                    biasesFromPoint += layer_[i + 1] * NUMBER_OF_PATHS; // GRU 3 gates * Units\layer_[i] | (TensorFlow GRU(...reset_after=False)) if True then this should be: 3 gates * Units * 2 bias_vectors) // LSTM 4 gates * Units\layer_[i] = Forget Update Output CellState // RNN 1
                #else
                    biasesFromPoint += layer_[i + 1]; // even for USE_RNN_LAYERS_ONLY or USE_PAIR__DENSE_RNN is ok
                #endif
            #endif
        }

        #if defined(REDUCE_RAM_DELETE_OUTPUTS)
            layers[numberOflayers -1].outputs = NULL;
        #endif
    }

    #if !defined(NO_BACKPROP) || defined(RAM_EFFICIENT_HILL_CLIMB)
        NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), const DFLOAT LRw OPTIONAL_BIAS(const DFLOAT LRb),  LayerType *_PropsPerLayer )
        : NeuralNetwork(layer_, NumberOflayers OPTIONAL_TIME(_threshold, _atIndex), _PropsPerLayer)  // Delegate to the second constructor | this is better, even though it uses a few extra bytes (the compiler doesn't optimize directly the values of learning rates)
        {
            // no need for this since there's ... && old_error != -1
            // #if defined(HILL_CLIMB_DYNAMIC_LEARNING_RATES) // #11
            //     OldLearningRateOfWeights = LRw;
            // #endif
            LearningRateOfWeights = LRw; // Initializing the Learning Rate of Weights
            #if !defined(NO_BIAS)
                LearningRateOfBiases = LRb; // Initializing the Learning Rate of Biases
                // no need for this since theres ... && old_error != -1
                // #if defined(HILL_CLIMB_DYNAMIC_LEARNING_RATES) // #11
                //     OldLearningRateOfBiases = LRb;
                // #endif
            #endif
        }

        //maybe i will  add one more constructor so i can release memory from feedforward outputs in case i dont want backprop?

        NeuralNetwork::NeuralNetwork(const unsigned int *layer_, const unsigned int &NumberOflayers OPTIONAL_TIME(const byte _threshold, const byte _atIndex), LayerType *_PropsPerLayer )
        {
            numberOflayers = NumberOflayers - 1;

            #if defined(SINGLE_TIMESTEP_THRESHOLD)
                threshold = _threshold;
                atIndex   = _atIndex;
            #endif

            layers = new Layer[numberOflayers];

            #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                PropsPerLayer = _PropsPerLayer;
            #endif 

            #if defined(REDUCE_RAM_STATIC_REFERENCE)
                me = this;
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2) //footprint episis san leksi // TODO: SIMD
                for (unsigned int i = 0; i < numberOflayers; i++)
                    i_j += NUMBER_FROM(layer_[i], layer_[i + 1], PropsPerLayer[i].arch);
                
                weights = new DFLOAT[i_j];
                i_j=0;
            #endif

            for (unsigned int i = 0; i < numberOflayers; i++)
                layers[i] =  Layer(layer_[i], layer_[i + 1],this);

            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                layers[numberOflayers -1].outputs = NULL;
            #endif
        }
    #endif


    #if defined(INCLUDES_EEPROM_H)
        #define IN_EXTERNAL_TYPE_MEMMORY
        #define TYPE_MEMMORY_GET EEPROM.get
        #define TYPE_MEMMORY_PUT EEPROM.put
        #define TYPE_MEMMORY_ME_GET EEPROM.get
        #define TYPE_MEMMORY_READ EEPROM.read
        #define PRINT_MESSAGE_INT_Q "INT_Q INTERNAL-EEPROM "
        #define PRINT_MESSAGE_TYPE_MEM "INTERNAL-EEPROM "
    #elif defined(INCLUDES_FRAM_H)
        #define TYPE_MEMMORY_GET fram->readObject
        #define TYPE_MEMMORY_ME_GET me->fram->readObject
        #define TYPE_MEMMORY_READ fram->read8
        #define IN_EXTERNAL_TYPE_MEMMORY fram,
        #define TYPE_MEMMORY_PUT fram.writeObject
        #define PRINT_MESSAGE_INT_Q "INT_Q EXTERNAL-FRAM "
        #define PRINT_MESSAGE_TYPE_MEM "EXTERNAL-FRAM "
    #endif

    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)

        template< typename T >
        T NeuralNetwork::get_type_memmory_value(unsigned int &addr){
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
            for (unsigned int i = 0; i < sizeof(T); ++i, ++addr) {
                ptr[i] = TYPE_MEMMORY_READ(addr);
            }
            return *reinterpret_cast<T*>(ptr);
        }
        
        //TODO: common get function that adds to address for  EEPROM
        #if defined(USE_INTERNAL_EEPROM)
            NeuralNetwork::NeuralNetwork(unsigned int addr){
        #else // USE_EXTERNAL_FRAM
            NeuralNetwork::NeuralNetwork(FRAM& framObj, unsigned int addr){
                fram = &framObj;
        #endif
                // isAllocdWithNew = false; // no need because of pdestract #if condition // also #8
                #if defined(REDUCE_RAM_STATIC_REFERENCE)
                    me = this;
                #endif
                
                // at least you can skip the sizeof if you plan on sharing the same NN between MCUs, compiled with SINGLE_TIMESTEP_THRESHOLD and other with DISABLE_SINGLE_TIMESTEP_THRESHOLD
                // even though ideally might have been better if this logic at save() existed at the end
                #if defined(SINGLE_TIMESTEP_THRESHOLD)
                    threshold = get_type_memmory_value<byte>(addr);
                    atIndex   = get_type_memmory_value<byte>(addr);
                #endif

                numberOflayers = get_type_memmory_value<unsigned int>(addr);
                layers = new Layer[numberOflayers];

                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    byte tmp0; // arch
                #endif
                unsigned int tmp1; // _numberOfInputs
                unsigned int tmp2; // _numberOfOutputs
                for (unsigned int i = 0; i < numberOflayers; i++){
                    #if defined(USE_EXTERNAL_FRAM)
                        TYPE_MEMMORY_GET(addr,tmp1);
                        #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                            TYPE_MEMMORY_GET(addr+sizeof(unsigned int),tmp0);
                            TYPE_MEMMORY_GET(addr+sizeof(unsigned int)+sizeof(LayerType),tmp2);
                            layers[i] =  Layer(tmp1, tmp2, tmp0, this);
                            addr += sizeof(unsigned int)+sizeof(LayerType);
                        #else
                            TYPE_MEMMORY_GET(addr+sizeof(unsigned int),tmp2);
                            layers[i] =  Layer(tmp1, tmp2, this);
                            addr += sizeof(unsigned int);
                        #endif
                    #else // defined(USE_INTERNAL_EEPROM) // or maybe any other future case?
                        #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                            layers[i] =  Layer(TYPE_MEMMORY_GET(addr,tmp1), TYPE_MEMMORY_GET(addr+sizeof(unsigned int)+sizeof(LayerType),tmp2), TYPE_MEMMORY_GET(addr+sizeof(unsigned int),tmp0), this);
                            addr += sizeof(unsigned int)+sizeof(LayerType);
                        #else
                            layers[i] =  Layer(TYPE_MEMMORY_GET(addr,tmp1), TYPE_MEMMORY_GET(addr+sizeof(unsigned int),tmp2), this);
                            addr += sizeof(unsigned int);
                        #endif
                    #endif
                }
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    address = addr + sizeof(unsigned int) + sizeof(LayerType);
                #else
                    address = addr + sizeof(unsigned int);
                #endif

                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    layers[numberOflayers -1].outputs = NULL;
                #endif
            }
    #endif


    #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)
        void NeuralNetwork::reset_Individual_Input_Counter() { Individual_Input = 0;}


        DFLOAT *NeuralNetwork::FeedForward_Individual(const DFLOAT &input) 
        {
            #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
                me = this;
            #endif

            #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
                if (layers[0].hiddenStates == NULL) // if the first layer of a type-RNN, has no hidden-states then re-initializeStates 
                    initializeStates();
            #endif

            #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                unsigned int tmp_addr = address; // variable for restoring address back to the original\start, could be and instance-variable too...
            #endif
            layers[0].FUNCTION_OF(NN_TYPE_ARCHITECTURE, FeedForward_Individual)(input, Individual_Input);
            Individual_Input++;

            if (Individual_Input == layers[0]._numberOfInputs)
            {
                Individual_Input=0;

                #if defined(MULTIPLE_BIASES_PER_LAYER) and (defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM))
                    address -= sizeof(IDFLOAT);
                #endif 
            
                #if defined(REDUCE_RAM_DELETE_OUTPUTS) // https://stackoverflow.com/a/4190737/11465149 https://stackoverflow.com/a/50290082/11465149
                    delete[] layers[numberOflayers - 1].outputs;
                #endif

                unsigned int i = 1;
                for (; i < numberOflayers; i++)
                {
                    #if (defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)) && !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM)
                        AtlayerIndex = i;
                    #endif  

                    layers[i].FUNCTION_OF(NN_TYPE_ARCHITECTURE, FeedForward)(layers[i - 1].outputs);

                    #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                        delete[] layers[i - 1].outputs;
                    #endif
                }

                #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                    address = tmp_addr;
                #endif
                return  layers[i - 1].outputs;
            }
            #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                address = tmp_addr;
            #endif

            return NULL;
        }
    #endif


    #if defined(USE_DENSE_PAIR) // eg. USE_PAIR__DENSE_RNN
        void NeuralNetwork::paired_FeedForward(const DFLOAT *inputs, const unsigned int i)
        {
            #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                #if defined(ACTIVATION__PER_LAYER) // we don't shift address ...
                    LayerType props; // LayerProps in this case
                    TYPE_MEMMORY_GET(address, props);
                    if (props.arch) // Always a type of RNN since DENSE is 0
                #else // ... we do via
                    if (get_type_memmory_value<LayerType>(address).arch)
                #endif
            #else
                if (PropsPerLayer[i].arch) // Always a type of RNN since DENSE is 0
            #endif
            {
                layers[i].FUNCTION_OF(A_TYPE_OF_RNN_ARCHITECTURE, FeedForward)(inputs);
            }else{
                layers[i].FUNCTION_OF(, FeedForward)(inputs);
            }
        }
    #endif


    #if defined(SINGLE_TIMESTEP_THRESHOLD) // #17
        bool NeuralNetwork::is_threshold_reached(const unsigned int i)
        {
            if ((atIndex == i) && (timestep != threshold)){
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    delete[] layers[i].outputs;
                #endif
                return true;
            }
            return false;
        }
    #endif


    #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
        void NeuralNetwork::initializeStates()
        {
            for (unsigned int i=0; i < numberOflayers; i++)
                layers[i].initializeStates();
        }
    #endif


    template<typename T> DFLOAT *NeuralNetwork::FeedForward(const T *inputs)
    {
        #if !defined(NO_BACKPROP) // No need for (RAM_EFFICIENT_HILL_CLIMB) | [The bellow line, is just an error note]
            #if defined(RAM_EFFICIENT_HILL_CLIMB) 
                _inputs = inputs; /* 💥 𝗡𝗢𝗧𝗘: Try `#define _2_OPTIMIZE 0B00000001`, most probably you left backpropagation enabled. If purposefully then, please use (DFLOAT) `float` | (`template<typename T>` is not yet supported with backpropagation). */
            #else
                _inputs = inputs; /* 💥 𝗡𝗢𝗧𝗘: Most likely you are using Backpropagation with the wrong type of inputs/training-data, please use (DFLOAT) `float` | `(template<typename T>` is not yet supported with backpropagation). */
            #endif
        #endif

        #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
            me = this;
        #endif

        #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
            if (layers[0].hiddenStates == NULL) // if the first layer of a type-RNN, has no hidden-states then re-initializeStates 
                initializeStates();
        #endif
        
        #if defined(REDUCE_RAM_DELETE_OUTPUTS) // https://stackoverflow.com/a/4190737/11465149 https://stackoverflow.com/a/50290082/11465149
            delete[] layers[numberOflayers - 1].outputs;
            #if defined(SINGLE_TIMESTEP_THRESHOLD) // this is needed due to `threshold` returning null #17
                layers[numberOflayers - 1].outputs = NULL;
            #endif
        #endif

        // Reseting the index to which layer we are back to 0, the 1st layer
        #if (defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)) && !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM)
            AtlayerIndex = 0;
        #endif  
        // resets starting point (could have had a function returning it instead of initializing it on constructor too?)
        #if defined(REDUCE_RAM_WEIGHTS_LVL2) 
            i_j=0;
        #endif

        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            unsigned int tmp_addr = address;
        #endif
        #if defined(USE_DENSE_PAIR) // #20 // TODO: #23 for eep and fram
            paired_FeedForward(inputs, 0);
        #else
            layers[0].FUNCTION_OF(NN_TYPE_ARCHITECTURE, FeedForward)(inputs);
        #endif

        #if defined(SINGLE_TIMESTEP_THRESHOLD) // #17 | I mean ... how often people use many-to-one for more than one layer?
            timestep++;
            if (is_threshold_reached(0)){
                #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                    address = tmp_addr;
                #endif
                return NULL;
            }
        #endif

        unsigned int i = 1;  // TODO: replace i with AtlayerIndex when ACTIVATION__PER_LAYER (don't forget `AtlayerIndex = 1`) OR alternativly you could pass the index to (in this case) FeedForward(input, OPTIONAL_AT_LAYER_INDEX(i)) [...]
        for (; i < numberOflayers; i++)
        {
            #if (defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)) && !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM)
                AtlayerIndex = i;
            #endif  

            #if defined(USE_DENSE_PAIR) // #20
                paired_FeedForward(layers[i - 1].outputs, i);
            #else
                layers[i].FUNCTION_OF(NN_TYPE_ARCHITECTURE, FeedForward)(layers[i - 1].outputs);
            #endif

            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                delete[] layers[i - 1].outputs;
            #endif

            #if defined(SINGLE_TIMESTEP_THRESHOLD) // #17
                if (is_threshold_reached(i)){
                    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
                        address = tmp_addr;
                    #endif
                    return NULL;
                }
            #endif
        }
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            address = tmp_addr;
        #endif

        #if defined(SINGLE_TIMESTEP_THRESHOLD) // #17
            timestep = 0;
        #endif

        return layers[i - 1].outputs;
    }


    template<typename T>
    void NeuralNetwork::Layer::ComputeSummedErrors(const T *_expected_)
    {
        DFLOAT gamma;
        // NOTE: summed errors exist at BackPropOutput too
        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            // ---> #9
            unsigned int i = _numberOfOutputs;
            do {
                i--;
                //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                gamma = (outputs[i] - _expected_[i]);
                
                    // I want to believe that it is being optimised/removed when not used | update 5/8/2021 ain't sure althought i've used "https://godbolt.org/" so... Macros
                #if defined(CATEGORICAL_CROSS_ENTROPY)
                    me->sumOfCategoricalCrossEntropy -= _expected_[i] * (DFLOAT)log(outputs[i]);
                #endif
                #if defined(BINARY_CROSS_ENTROPY)
                    me->sumOfBinaryCrossEntropy -=  _expected_[i] * (DFLOAT)log(outputs[i]) + (1.0 - _expected_[i]) * (DFLOAT)log(1.0 - outputs[i]); // https://forum.arduino.cc/t/maths-help-log/339211 https://math.stackexchange.com/questions/293783/when-log-is-written-without-a-base-is-the-equation-normally-referring-to-log-ba
                #endif
                #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
                    me->sumSquaredError += gamma * gamma; 
                #endif
            } while (i != 0);

        #else
            for (unsigned int i = 0; i < _numberOfOutputs; i++)
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
            }
        #endif
        
    }


    template<typename T>
    void NeuralNetwork::ComputeSummedErrors(const T *_expected_)
    {
        /* i dont find any reason of having this if Backprop or ComputeSummedErrors will never be used more than once imidiatly after once [...] but just in case ... commented .... The same goes for i_j too | Meaning: NN.Backprop(..); \n NN.Backprop(..); without a feedforward in between
        #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
            AtlayerIndex = numberOflayers - 1;
        #endif  
        */

        #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
            me = this;
        #endif

        layers[numberOflayers - 1].ComputeSummedErrors(_expected_);
    }


    #if defined(RAM_EFFICIENT_HILL_CLIMB) or defined(RAM_EFFICIENT_HILL_CLIMB_WITHOUT_NEW)
        void NeuralNetwork::climb(int8_t direction) 
        {
            // TODO: It should be pretty simple to train entirely on FRAM

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                i_j = 0;
            #endif

            #if defined(HILL_CLIMB_DYNAMIC_LEARNING_RATES) // #11
                OldLearningRateOfWeights = LearningRateOfWeights;
                #if !defined(NO_BIAS)
                    OldLearningRateOfBiases = LearningRateOfBiases;
                #endif
            #endif
            
            // NN_RANDOM(-1,2) means {-1,0,1}
            for (unsigned int l = 0; l < numberOflayers; l++){
                #if !defined(NO_BIAS) && !defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                    *layers[l].bias += (LearningRateOfBiases * NN_RANDOM(-1,2) * direction);
                #endif
                for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                    for (unsigned int i = 0; i < layers[l]._numberOfOutputs; i++){
                        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES "common reference"
                            layers[l].bias[i + (p * layers[l]._numberOfOutputs)] += (LearningRateOfBiases * NN_RANDOM(-1,2) * direction);
                        #endif
                        for (unsigned int j = 0; j < SIZEOF_FROM(layers[l]._numberOfInputs, layers[l]._numberOfOutputs, PropsPerLayer[l].arch); j++)
                        {
                            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                weights[i_j++] += (LearningRateOfWeights * NN_RANDOM(-1,2) * direction);
                            #else
                                // eew! but whatever for now... at least for NUMBER_OF_PATHS == 1 it gets optimised
                                layers[l].weights[i][j + (p * SIZEOF_FROM(layers[l]._numberOfInputs, layers[l]._numberOfOutputs, PropsPerLayer[l].arch))] += (LearningRateOfWeights * NN_RANDOM(-1,2) * direction);
                            #endif
                        }
                    }
                }
            }
        }


        /*
        * A computationally-expensive but memmory-efficient Hill-Climbing algorithm,
        * that uses barely any extra amount of RAM to train the NN. (Just a few bytes)
        * WARNING: This algorithm may not work with MCUs that utilize TRNG 
        * (True-RNG) at the back-end of `NN_RANDOM()\random()` function, if not any fallback
        * to PRNG via eg. `NN_RANDOM_SET()\randomSeed()` exists.
        */
        bool NeuralNetwork::HillClimb(DFLOAT error, DFLOAT tolerance)
        {
            if (error <= tolerance)
                return false;

            if (error > old_error && old_error != -1){ // -1 to prevent first loop from "reverting"
                // revert potential changes in dynamic LearningRates
                #if defined(HILL_CLIMB_DYNAMIC_LEARNING_RATES) // #11
                    LearningRateOfWeights = OldLearningRateOfWeights;
                    #if !defined(NO_BIAS)
                        LearningRateOfBiases = OldLearningRateOfBiases;
                    #endif
                #endif

                // climb-back\revert-changes
                --nn_seed;
                // ++ to skip the bad seed later on
                NN_RANDOM_SET(nn_seed++);
                climb(-1);
            }else{
                // if we revert we keep the same old_error, else:
                old_error = error;
            }

            // climb-up\retry
            NN_RANDOM_SET(nn_seed++);
            climb(1);

            // TODO: a HillClimbing with Spike if preciist?
            return true;
        }
    #endif


    #if !defined (NO_BACKPROP)
        void NeuralNetwork::BackProp(const DFLOAT *expected)
        {
            /* i dont find any reason of having this if Backprop or ComputeSummedErrors will never be used more than once imidiatly after once [...] but just in case ... commented .... The same goes for i_j too | Meaning: NN.Backprop(..); \n NN.Backprop(..); without a feedforward in between
            #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                AtlayerIndex = numberOflayers - 1;
            #endif  
            */

            #if defined(REDUCE_RAM_STATIC_REFERENCE_FOR_MULTIPLE_NN_OBJECTS)
                me = this;
            #endif
            
            #if defined(SUPPORT_NO_HIDDEN_BACKPROP)
                if (numberOflayers == 1) { // meaning 2 actual layers {0,1} input-output
                    layers[0].BackPropOutput(expected, _inputs);
                    delete[] layers[0].preLgamma; // #10
                    return;
                }
            #endif

            layers[numberOflayers - 1].BackPropOutput(expected, layers[numberOflayers - 2].outputs); // issue because backprop einai anapoda ta weights [Fixed]

            for (unsigned int i = numberOflayers - 2; i > 0; i--)
            {
                layers[i].BackPropHidden(&layers[i + 1], layers[i - 1].outputs);
            }

            layers[0].BackPropHidden(&layers[1], _inputs);
            delete[] layers[0].preLgamma; // #10
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
    

    #if defined(SUPPORTS_SD_FUNCTIONALITY) || defined(SUPPORTS_FS_FUNCTIONALITY) 
        template <typename T_File, typename>
        bool NeuralNetwork::save(T_File& myFile)
        {
            if (myFile){
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    unsigned int totalNumOfWeights = 0; // we write 0 so we can seek at the end and set the real value
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&totalNumOfWeights), sizeof(totalNumOfWeights));
                #endif
                #if defined(SINGLE_TIMESTEP_THRESHOLD) // I have to move it bellow the line above since at the end it seeks to 0 when REDUCE_RAM_WEIGHTS_LVL2
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&threshold), sizeof(threshold));
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&atIndex)  , sizeof(atIndex));
                #endif
                myFile.write(reinterpret_cast<CHAR_BYTE*>(&numberOflayers), sizeof(numberOflayers));
                for(unsigned int n=0; n<numberOflayers; n++){
                    #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                        myFile.write(reinterpret_cast<CHAR_BYTE*>(&PropsPerLayer[n]), sizeof(*PropsPerLayer));
                    #endif
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&layers[n]._numberOfInputs), sizeof(NeuralNetwork::Layer::_numberOfInputs));
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&layers[n]._numberOfOutputs), sizeof(NeuralNetwork::Layer::_numberOfOutputs));
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        myFile.write(reinterpret_cast<CHAR_BYTE*>(layers[n].bias), sizeof(*NeuralNetwork::Layer::bias));
                    #endif
                    // TODO: make an i_j loop for REDUCE_RAM_WEIGHTS_LVL2 instead
                    for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                        for(unsigned int i=0; i<layers[n]._numberOfOutputs; i++){
                            #if defined(MULTIPLE_BIASES_PER_LAYER)
                                myFile.write(reinterpret_cast<CHAR_BYTE*>(&layers[n].bias[i + (p * layers[n]._numberOfOutputs)]), sizeof(*NeuralNetwork::Layer::bias));
                            #endif
                            //WARN: ##21 T_File compatibility is not guaranteed between MCUs compiled with REDUCE_RAM_WEIGHTS_LVL2 enabled and those compiled with it disabled, specifically for GRU and LSTM layers.
                            for(unsigned int j=0; j<SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch); j++)
                            {
                                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&weights[totalNumOfWeights++]), sizeof(*weights)); // I would had used i_j but I have totalNumOfWeights so... :)
                                #else
                                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&layers[n].weights[i][j + (p * SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch))]), sizeof(**NeuralNetwork::Layer::weights));
                                #endif
                            }
                        }
                    }
                }
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    myFile.NN_FS_SEEK(0); // NOTE: that's SuS depending on the defined SD library one might choose | in relation to the myFile.println("        "); and print below | espressif's ESP32 SD-FS implementation uses default seek mode to 	SEEK_SET – It moves file pointer position to the beginning of the file.
                    myFile.write(reinterpret_cast<CHAR_BYTE*>(&totalNumOfWeights), sizeof(totalNumOfWeights));
                #endif
                return true;
            }
            return false;
        }

        #if defined(SUPPORTS_SD_FUNCTIONALITY)
            bool NeuralNetwork::save(String file)
            {
                File myFile = SD.open(file.c_str(), SD_NN_WRITE_MODE); // it seems that c_str() doesn't work with UNO ...

                bool saved = save(myFile);

                myFile.close();

                return saved;
            }
        

            // WARNING: DEPRECATED FUNCTION
            bool NeuralNetwork::save_old(String file)
            {
                File myFile = SD.open(file.c_str(), SD_NN_WRITE_MODE);

                if (myFile){
                    unsigned int totalNumOfWeights = 0;
                    myFile.println("        "); // yes... it needs those spaces
                    myFile.println(numberOflayers+1); 
                    for(unsigned int n=0; n<numberOflayers; n++){
                        #if defined(ACTIVATION__PER_LAYER)
                            myFile.println(PropsPerLayer[n]); // WARN: Deprecated for LayerType #18
                        #endif
                        myFile.println(layers[n]._numberOfInputs); 
                        myFile.println(layers[n]._numberOfOutputs); 
                        #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                            myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(*layers[n].bias)); 
                        #endif

                        for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                            for(unsigned int i=0; i<layers[n]._numberOfOutputs; i++){
                                #if defined(MULTIPLE_BIASES_PER_LAYER)
                                    myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(layers[n].bias[i + (p * layers[n]._numberOfOutputs)])); 
                                #endif

                                for(unsigned int j=0; j<SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch); j++)
                                {
                                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                        myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(weights[totalNumOfWeights])); // I would had used i_j but I have totalNumOfWeights so... :)
                                    #else
                                        myFile.println(CAST_TO_LLONG_IF_NOT_INT_QUANTIZATION(layers[n].weights[i][j + (p * SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch))])); 
                                    #endif
                                    totalNumOfWeights++;
                                }
                            }
                        }
                    }
                    myFile.seek(0); // NOTE: that's SuS depending on the defined SD library one might choose | in relation to the myFile.println("        "); and print below | espressif's ESP32 SD-FS implementation uses default seek mode to 	SEEK_SET – It moves file pointer position to the beginning of the file.
                    myFile.print(totalNumOfWeights);
                    myFile.close();
                    return true;
                }
                return false;
            }
        #endif


        template <typename T_File, typename>
        bool NeuralNetwork::load(T_File& myFile) {
            if (numberOflayers !=0 || isAlreadyLoadedOnce) // to prevent undefined delete[] and memory leaks for the sake of reloading as many times as you want :)
                pdestract();

            if (myFile) {
                isAllocdWithNew = true;

                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    // TODO: remove count_ij in favor of i_j (if so, reminder: at the end, set it to zero again) see also issue #32
                    unsigned int count_ij; // it needs to be unsigned since we write an unsigned :P
                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&count_ij), sizeof(count_ij)); // don't worry it takes into account USE_RNN_LAYERS_ONLY
                    weights = new IDFLOAT[count_ij];
                    i_j = 0;
                    count_ij = 0;
                #endif

                #if defined(SINGLE_TIMESTEP_THRESHOLD)
                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&threshold), sizeof(threshold));
                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&atIndex)  , sizeof(atIndex));
                #endif

                myFile.read(reinterpret_cast<CHAR_BYTE*>(&numberOflayers), sizeof(numberOflayers));
                layers = new Layer[numberOflayers];

                #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    isAlreadyLoadedOnce = true;
                    PropsPerLayer = new LayerType[numberOflayers];
                #endif

                #if defined(REDUCE_RAM_STATIC_REFERENCE)
                    me = this;
                #endif

                unsigned int tmp_layerInputs;
                unsigned int tmp_layerOutputs;

                #if !defined(NO_BIAS)
                    IDFLOAT *tmp_bias;
                #endif

                for (unsigned int i = 0; i < numberOflayers; i++)
                {
                    #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                        myFile.read(reinterpret_cast<CHAR_BYTE*>(&PropsPerLayer[i]), sizeof(*PropsPerLayer));
                    #endif
                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&tmp_layerInputs), sizeof(tmp_layerInputs));
                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&tmp_layerOutputs), sizeof(tmp_layerOutputs));
                    #if !defined(NO_BIAS)
                        #if !defined(MULTIPLE_BIASES_PER_LAYER)
                            tmp_bias  = new IDFLOAT;
                            myFile.read(reinterpret_cast<CHAR_BYTE*>(tmp_bias), sizeof(*tmp_bias));
                        #else
                            tmp_bias = new IDFLOAT[tmp_layerOutputs * NUMBER_OF_PATHS]; // reminder: this is fine for NOT-REDUCE_RAM_WEIGHTS_LVL2 too
                        #endif
                    #endif

                    #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                        #if defined(NO_BIAS)
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                        #else
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                        #endif
                        layers[i].weights = new IDFLOAT *[tmp_layerOutputs];

                        for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                            for(unsigned int j=0; j<tmp_layerOutputs; j++){
                                #if defined(MULTIPLE_BIASES_PER_LAYER)
                                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&layers[i].bias[j + (tmp_layerOutputs * p)]), sizeof(*NeuralNetwork::Layer::bias));
                                #endif
                                if (!p)
                                    layers[i].weights[j] = new IDFLOAT[SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch) * NUMBER_OF_PATHS]; // #21
                                for(unsigned int k=0; k<SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch); k++){
                                    myFile.read(reinterpret_cast<CHAR_BYTE*>(&layers[i].weights[j][k + (p * SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch))]), sizeof(**NeuralNetwork::Layer::weights));
                                }
                            }
                        }
                    #else // I won't elif here cause I want to have a clear image of the "division" below
                        #if defined(MULTIPLE_BIASES_PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                            for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                                for(unsigned int j=0; j<tmp_layerOutputs; j++){

                                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                                        myFile.read(reinterpret_cast<CHAR_BYTE*>(&tmp_bias[j + (p * tmp_layerOutputs)]), sizeof(*tmp_bias));
                                    #endif

                                    for(unsigned int k=0; k<SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch); k++){ // #21
                                        myFile.read(reinterpret_cast<CHAR_BYTE*>(&weights[count_ij++]), sizeof(*weights));
                                    }
                                }
                            }
                        #else
                            for(unsigned int j=0; j<(SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs,) * NUMBER_OF_PATHS * tmp_layerOutputs); j++){ // #21
                                myFile.read(reinterpret_cast<CHAR_BYTE*>(&weights[count_ij++]), sizeof(*weights));
                            }
                        #endif

                        #if defined(NO_BIAS)
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                        #else
                            layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                        #endif
                    #endif
                }
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    layers[numberOflayers -1].outputs = NULL;
                #endif

                return true;
            }
            return false;
        }


        #if defined(SUPPORTS_SD_FUNCTIONALITY)
            bool NeuralNetwork::load(String file)
            {

                File myFile = SD.open(file.c_str());

                bool loaded = load(myFile);

                myFile.close();

                return loaded;
            }


            // WARNING: DEPRECATED FUNCTION
            bool NeuralNetwork::load_old(String file)
            {
                if (numberOflayers !=0 || isAlreadyLoadedOnce) // to prevent undefined delete[] and memory leaks for the sake of reloading as many times as you want :)
                    pdestract();

                File myFile = SD.open(file.c_str());

                if (myFile) {
                    isAllocdWithNew = true;

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        int count_ij = 0;
                        i_j = 0;
                        weights = new IDFLOAT[myFile.readStringUntil('\n').toInt()];
                    #else
                        myFile.readStringUntil('\n').toInt(); // Skipping line // reminder removed this too
                    #endif

                    numberOflayers = myFile.readStringUntil('\n').toInt() - 1; // reminder I removed +1 from save
                    layers = new Layer[numberOflayers]; 

                    #if defined(ACTIVATION__PER_LAYER)
                        isAlreadyLoadedOnce = true;
                        PropsPerLayer = new byte[numberOflayers]; // WARN: #18
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

                    for (unsigned int i = 0; i < numberOflayers; i++)
                    {
                        #if defined(ACTIVATION__PER_LAYER)
                            PropsPerLayer[i] = myFile.readStringUntil('\n').toInt(); // WARN: #18
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
                                layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this); // #22
                            #else
                                layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this); // I know this macro here is useless at this point but let it be :P ... ##22 the same gose for the PropsPerLayer[i].arch on the rest of those old functions
                            #endif
                            layers[i].weights = new IDFLOAT *[tmp_layerOutputs];
                        #endif

                        #if !defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                            for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                                for(unsigned int j=0; j<tmp_layerOutputs; j++){
                                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                                        #if !defined(USE_INT_QUANTIZATION)
                                            tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                            layers[i].bias[j + (p * tmp_layerOutputs)] = *((DFLOAT*)(&tmp));
                                        #else
                                            layers[i].bias[j + (p * tmp_layerOutputs)] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                        #endif
                                    #endif
                                    if (!p)
                                        layers[i].weights[j] = new IDFLOAT[SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch) * NUMBER_OF_PATHS]; // #22 
                                    for(unsigned int k=0; k<SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch); k++) // #22 
                                    {
                                        #if !defined(USE_INT_QUANTIZATION)
                                            tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                            layers[i].weights[j][k + (p * SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch))] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                        #else
                                            layers[i].weights[j][k + (p * SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch))] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                        #endif
                                    }
                                }
                            }
                        #else // I won't elif here cause I want to have a clear image of the "division" below
                            #if defined(MULTIPLE_BIASES_PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES) // #22
                                for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                                    for(unsigned int j=0; j<tmp_layerOutputs; j++){
                                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                                            #if !defined(USE_INT_QUANTIZATION)
                                                tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                                tmp_bias[j + (p * tmp_layerOutputs)] = *((DFLOAT*)(&tmp));
                                            #else
                                                tmp_bias[j + (p * tmp_layerOutputs)] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                            #endif
                                        #endif

                                        for(unsigned int k=0; k<SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch); k++) // #22
                                        {
                                            #if !defined(USE_INT_QUANTIZATION)
                                                tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                                weights[count_ij++] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                            #else
                                                weights[count_ij++] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                            #endif
                                        }
                                    }
                                }
                            #else
                                for(unsigned int j=0; j<SIZEOF_FROM(tmp_layerInputs, tmp_layerOutputs, PropsPerLayer[i].arch) * NUMBER_OF_PATHS * tmp_layerOutputs; j++) // #22
                                {
                                    #if !defined(USE_INT_QUANTIZATION)
                                        tmp = ATOL((char*)myFile.readStringUntil('\n').c_str());
                                        weights[count_ij++] = *((DFLOAT*)(&tmp)); // toFloat() which is atof() is not accurate (at least on Arduino UNO)
                                    #else
                                        weights[count_ij++] = (IDFLOAT)strtol((char*)myFile.readStringUntil('\n').c_str(), NULL, 10);
                                    #endif
                                }
                            #endif
                        #endif
                        #if defined(REDUCE_RAM_WEIGHTS_LVL2) // #1.1
                            #if defined(NO_BIAS)
                                layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, HAS_NO_BIAS OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                            #else
                                layers[i] = Layer(tmp_layerInputs, tmp_layerOutputs, tmp_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(PropsPerLayer[i].arch), this);
                            #endif
                        #endif
                    }
                    myFile.close();

                    #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                        layers[numberOflayers -1].outputs = NULL;
                    #endif

                    return true;
                }
                return false;
            }
        #endif
    #endif
    #if (defined(INCLUDES_EEPROM_H) or defined(INCLUDES_FRAM_H)) and !(defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM))

        #if defined(INCLUDES_FRAM_H)
            template< typename T > void NeuralNetwork::put_type_memmory_value(FRAM &fram, unsigned int &addr, T val)
        #else
            template< typename T > void NeuralNetwork::put_type_memmory_value(unsigned int &addr, T val)
        #endif
            {
                TYPE_MEMMORY_PUT(addr, val);
                addr += sizeof(T);
            }

        // Because if it is just #included then it is not used, therefore we have to pass an fram object
        #if defined(INCLUDES_FRAM_H)
            unsigned int NeuralNetwork::save(FRAM &fram, unsigned int atAddress)
        #else
            unsigned int NeuralNetwork::save(unsigned int atAddress)
        #endif
            {
                unsigned int tmp_addr = 0;
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    i_j = 0;
                #endif
                #if defined(SINGLE_TIMESTEP_THRESHOLD)
                    put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, threshold);
                    put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, atIndex);
                #endif
                put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, numberOflayers);
                tmp_addr = atAddress;
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    atAddress += (numberOflayers+1)*sizeof(numberOflayers) + (numberOflayers+1)*sizeof(LayerType); // LayerProps in this case
                #else
                    atAddress += (numberOflayers+1)*sizeof(numberOflayers);
                #endif
                for(unsigned int n=0; n<numberOflayers; n++){
                    put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  tmp_addr, layers[n]._numberOfInputs); // NOTE: those 2-lines are in tmp_addr
                    #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                        put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  tmp_addr, PropsPerLayer[n].arch); // yep.. extra byte for the sake of simplicity later on at the constructor (feel free to blame me :P)
                    #endif
                    #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                        put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, PropsPerLayer[n]);
                    #endif
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, TYPE_MEMMORY_READ_IDFLOAT(*layers[n].bias));
                    #endif
                    for(unsigned int p=0; p< NUMBER_OF_PATHS; p++){ // p = path | NOTE: (As fas as I am aware) the compiler is smart enough to optimize\inline this block when NUMBER_OF_PATHS = 1 since it's just a const and always executes once
                        for(unsigned int i=0; i<layers[n]._numberOfOutputs; i++){
                            #if defined(MULTIPLE_BIASES_PER_LAYER)
                                put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, TYPE_MEMMORY_READ_IDFLOAT(layers[n].bias[i + (layers[n]._numberOfOutputs * p)]));
                            #endif

                            //WARN: ##21 File compatibility is not guaranteed between MCUs compiled with REDUCE_RAM_WEIGHTS_LVL2 enabled and those compiled with it disabled, SPECIFICALLY for GRU and LSTM layers.
                            // Additionally in the SPECIFIC case of GRU or LSTM using either FRAM or EEPROM without REDUCE_RAM_WEIGHTS_LVL2 the file won't be loadable after saving. You may ask why I don't make it loadable... 
                            // because the momment I make it loadable it will brake an upcomming feature I want to implement that has to do with off-loading to RAM therefore it's best to keep REDUCE_RAM_WEIGHTS_LVL2-
                            // logic by default (since it is common with the current sate of EEPROM and FRAM in term of how the weights are organized) [...]
                            for(unsigned int j=0; j<SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch); j++)
                            {
                                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                    put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, TYPE_MEMMORY_READ_IDFLOAT(weights[i_j++]));
                                #else
                                    put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  atAddress, TYPE_MEMMORY_READ_IDFLOAT(layers[n].weights[i][j + (p * SIZEOF_FROM(layers[n]._numberOfInputs, layers[n]._numberOfOutputs, PropsPerLayer[n].arch))]));
                                #endif
                            }
                        }
                    }
                }
                put_type_memmory_value(IN_EXTERNAL_TYPE_MEMMORY  tmp_addr, layers[numberOflayers-1]._numberOfOutputs);
                return atAddress;
            }
    #endif

    //If Microcontroller isn't one of the .._No_Common_Serial_Support Series then it compiles the code below.
    #if !defined(AS__NO_COMMON_SERIAL_SUPPORT) // then Compile:
    void NeuralNetwork::print()
    {
        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
            i_j=0; 
        #endif
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            unsigned int tmp_addr = address;
        #endif

        NN_PRINTLN();
        NN_PRINTLN_1(F_MACRO("----------------------"));

        for (unsigned int i = 0; i < numberOflayers; i++)
        {
            #if (defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)) && !defined(USE_INTERNAL_EEPROM) && !defined(USE_EXTERNAL_FRAM) // not def USE_INTERNAL_EEPROM, because AtlayerIndex is not needed
                AtlayerIndex = i;
            #endif  
            layers[i].FUNCTION_OF(NN_TYPE_ARCHITECTURE, print)(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(i)); // It's fine for USE_PAIR__DENSE_RNN since we compact both architectures in plain `print()` (for "useless" functions, it seems best to we care more about sketch-size-logic rather than speed)
            NN_PRINTLN_1(F_MACRO("----------------------"));
        }
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            address = tmp_addr;
        #endif
    }
    #endif


    #if defined(HAS_HIDDEN_STATES)
        void NeuralNetwork::resetStates()
        {
            for (unsigned int i=0; i<numberOflayers; i++)
                layers[i].resetStates();
        }
    #endif
// #pragma endregion NeuralNetwork.cpp



//=======================================================================================================================================================================
// Layer.cpp
//=======================================================================================================================================================================

// #pragma region Layer.cpp
    #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
        void NeuralNetwork::Layer::initializeStates()
        {
            #if defined(HAS_HIDDEN_STATES)
                hiddenStates = new DFLOAT[_numberOfOutputs]{}; 
            #endif
            #if defined(USE_LSTM_LAYERS_ONLY)
                cellStates = new DFLOAT[_numberOfOutputs]{}; 
            #endif
        }
    #endif


    #if defined(HAS_HIDDEN_STATES)
        void NeuralNetwork::Layer::resetStates()
        {
            #if defined(USE_DENSE_PAIR) // #31 at some point
                if (hiddenStates == NULL)
                    return;
            #endif

            #if defined(REDUCE_RAM_RESET_STATES_BY_DELETION) // #31
                #if defined(HAS_HIDDEN_STATES)
                    delete[] hiddenStates;
                    hiddenStates = NULL;
                #endif
                #if defined(USE_LSTM_LAYERS_ONLY)
                    delete[] cellStates;
                    cellStates = NULL;
                #endif
            #else
                for (unsigned int i = 0; i < _numberOfOutputs; i++){
                    #if defined(HAS_HIDDEN_STATES)
                        hiddenStates[i] = 0;
                    #endif
                    #if defined(USE_LSTM_LAYERS_ONLY)
                        cellStates[i] = 0;
                    #endif
                }
            #endif
        }
    #endif


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
            #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyReLU)
                &NeuralNetwork::Layer::LeakyReLU,
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
                #if defined(LeakyReLU)
                    &NeuralNetwork::Layer::LeakyReLUDer,
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
        NeuralNetwork::Layer::Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, IS_CONST IDFLOAT *default_Weights OPTIONAL_BIAS(IS_CONST IDFLOAT *default_Bias) OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture), NeuralNetwork * const NN )
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif

            #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                gatedOutputs = new DFLOAT[_numberOfOutputs];
            #endif

            #if defined(HAS_HIDDEN_STATES)
                #if defined(USE_DENSE_PAIR)
                    if (layerArchitecture) // DENSE = 0
                        hiddenStates = new DFLOAT[_numberOfOutputs]{}; // NOTE: {}
                #else
                    hiddenStates = new DFLOAT[_numberOfOutputs]; 
                #endif
            #endif

            #if defined(USE_LSTM_LAYERS_ONLY)
                cellStates = new DFLOAT[_numberOfOutputs];
            #endif

            #if !defined(NO_BIAS) // TODO: REDUCE_RAM_BIASES "common reference"
                bias = default_Bias; //                          ##1    Bias as Default Bias. Biases if defined MULTIPLE_BIASES_PER_LAYER | A reference
            #endif
            weights = new IS_CONST IDFLOAT *[_numberOfOutputs]; //      ##1    New Array of Pointers to (IDFLOAT) weights.

            for (unsigned int i = 0; i < _numberOfOutputs; i++){              // [matrix] (_numberOfOutputs * _numberOfInputs)
                #if defined(HAS_HIDDEN_STATES) and !defined(USE_DENSE_PAIR)
                    hiddenStates[i] = 0;
                #endif
                #if defined(USE_LSTM_LAYERS_ONLY)
                    cellStates[i] = 0;
                #endif
                weights[i] = &default_Weights[INDEX_FROM(i, _numberOfInputs, _numberOfOutputs, layerArchitecture)]; // Passing Default weights to ##1 weights by reference.  
            }
        }
    #endif


    #if defined(NO_BIAS)
        NeuralNetwork::Layer::Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, bool has_no_bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture), NeuralNetwork * const NN ) // has_no_bias is something the compiler i'm 99% sure it will optimize\remove
    #else
        NeuralNetwork::Layer::Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs, IS_CONST IDFLOAT *default_Bias OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture), NeuralNetwork * const NN )
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

        #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
            gatedOutputs = new DFLOAT[_numberOfOutputs];
        #endif

        #if defined(HAS_HIDDEN_STATES)
            #if defined(USE_DENSE_PAIR)
                if (layerArchitecture) // DENSE = 0
                    hiddenStates = new DFLOAT[_numberOfOutputs]{};
            #else
                hiddenStates = new DFLOAT[_numberOfOutputs]{}; 
            #endif
        #endif

        #if defined(USE_LSTM_LAYERS_ONLY)
            cellStates = new DFLOAT[_numberOfOutputs]{};
        #endif
        
        #if !defined(NO_BIAS)
            bias = default_Bias; //                          ##1    Bias as Default Bias. Biases if defined MULTIPLE_BIASES_PER_LAYER | A reference
        #endif
    }

    // NOTE: I added an `OR` because I'm planning to implement HILL_CLIMB for other types of memmory too
    #if !defined(NO_BACKPROP) || !defined(NO_TRAINING_METHOD)
        //- [ numberOfInputs in into this layer , NumberOfOutputs of this layer ]
        NeuralNetwork::Layer::Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture), NeuralNetwork * const NN) // TODO: IDFLOAT support 
        {
            _numberOfInputs = NumberOfInputs;                             // ##1       Number of Inputs .
            _numberOfOutputs = NumberOfOutputs;                           // ##1       Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs];                     // ##1    New Array of Outputs.
            #endif 
            #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                gatedOutputs = new DFLOAT[_numberOfOutputs];
            #endif
            #if defined(HAS_HIDDEN_STATES)
                #if defined(USE_DENSE_PAIR) 
                    if (layerArchitecture) // DENSE = 0
                        hiddenStates = new DFLOAT[_numberOfOutputs]{}; // NOTE: {}
                #else
                    hiddenStates = new DFLOAT[_numberOfOutputs]; 
                #endif
            #endif
            #if defined(USE_LSTM_LAYERS_ONLY)
                cellStates = new DFLOAT[_numberOfOutputs];
            #endif
            #if !defined(REDUCE_RAM_WEIGHTS_COMMON)      
                weights = new IDFLOAT *[_numberOfOutputs];                  // ##1    New Array of Pointers to (IDFLOAT) weights.
            #endif
            #if defined(MULTIPLE_BIASES_PER_LAYER)
                #if defined(HAS_GATED_OUTPUTS)
                    bias = new IDFLOAT[_numberOfOutputs*NUMBER_OF_PATHS]; // ##1 (LSTM or GRU) New Biases
                #else          
                    bias = new IDFLOAT[_numberOfOutputs];                   // ##1    New          Biases  // even for USE_RNN_LAYERS_ONLY or USE_PAIR__DENSE_RNN is ok
                #endif         
            #elif !defined(NO_BIAS) // TODO: Investigate if with GRU or LSTM anything changes
                bias = new IDFLOAT;                                         // ##1    New          Bias   .
                *bias = 1.0; // SuS cause IDFLOAT
            #endif

            for (unsigned int i = 0; i < _numberOfOutputs; i++)
            {
                #if !defined(REDUCE_RAM_WEIGHTS_COMMON)
                    weights[i] = new IDFLOAT[SIZEOF_FROM(_numberOfInputs, _numberOfOutputs, layerArchitecture) * NUMBER_OF_PATHS];
                #endif

                #if defined(HAS_HIDDEN_STATES) and !defined(USE_DENSE_PAIR)
                    hiddenStates[i] = 0;
                #endif
                #if defined(USE_LSTM_LAYERS_ONLY)
                    cellStates[i] = 0;
                #endif

                #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                    #if defined(USE_PAIR__DENSE_RNN) // NOTE: not USE_DENSE_PAIR (also TODO)
                        bias[i] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;
                    #elif defined(USE_LSTM_LAYERS_ONLY)
                        for (unsigned int j = i * 4; j < (i + 1) * 4; ++j) // Meh... It may not be the fastest/energy-efficient but I think it's fine since it is just initialization and as of 2025-05-23 03:23:35 PM Backpop is not implemented yet
                            bias[j] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;
                    #elif defined(USE_GRU_LAYERS_ONLY)
                        for (unsigned int j = i * 3; j < (i + 1) * 3; ++j) // Meh... It may not be the fastest/energy-efficient but I think it's fine since it is just initialization and as of 2025-04-06 09:20:50 PM Backpop is not implemented yet
                            bias[j] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;
                    #else
                        bias[i] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;
                    #endif
                #endif
                
                for (unsigned int j = 0; j < SIZEOF_FROM(_numberOfInputs, _numberOfOutputs, layerArchitecture) * NUMBER_OF_PATHS; j++)
                {
                    #if defined(REDUCE_RAM_WEIGHTS_LVL2) // TODO: IDFLOAT support | ignore IDFLOAT below for now
                        me->weights[me->i_j++] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;
                    #else
                        weights[i][j] = (IDFLOAT)NN_RANDOM(-90000, 90000) / 100000;  // Pseudo-Random Number between -90000 and 90000, divided by 100000.
                    #endif
                }
            }

        }
    #endif


    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
        NeuralNetwork::Layer::Layer(const unsigned int NumberOfInputs, const unsigned int NumberOfOutputs OPTIONAL_LAYER_TYPE_ARCHITECTURE(byte layerArchitecture), NeuralNetwork * const NN )
        {
            _numberOfInputs = NumberOfInputs;   //  (this) layer's  Number of Inputs .
            _numberOfOutputs = NumberOfOutputs; //           ##1    Number of Outputs.

            #if !defined(REDUCE_RAM_STATIC_REFERENCE)
                me = NN;
            #endif

            #if !defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs]; //    ##1    New Array of Outputs.
            #endif

            #if defined(HAS_GATED_OUTPUTS) && !defined(REDUCE_RAM_DELETE__GATED_OUTPUTS)
                gatedOutputs = new DFLOAT[_numberOfOutputs];
            #endif

            #if defined(HAS_HIDDEN_STATES)
                #if defined(USE_DENSE_PAIR) 
                    if (layerArchitecture) // DENSE = 0
                        hiddenStates = new DFLOAT[_numberOfOutputs]{};
                #else
                    hiddenStates = new DFLOAT[_numberOfOutputs]{}; 
                #endif
            #endif

            #if defined(USE_LSTM_LAYERS_ONLY)
                cellStates = new DFLOAT[_numberOfOutputs]{};
            #endif
        }


        template<typename T>
        void NeuralNetwork::Layer::accumulatedDotProduct(const T *src1, DFLOAT *dest, unsigned int len) // WithSrc2Address
        {
            #if defined(REDUCED_SKETCH_SIZE_DOT_PROD) // WARN: #26
                do {
                    *dest += (*src1++) * me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                } while (--len);
            #else
                for (unsigned int i = 0; i < len; i++)
                    *dest += src1[i] * me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
            #endif
        }
    #endif


    #if defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)
        // TODO: maybe create a static variable which will take a reference to a function. Once when j==0 (for output init) and once when j == _numberOfInputs -1
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            #if defined(USE_RNN_LAYERS_ONLY)
                void NeuralNetwork::Layer::RNN_Only_FeedForward_Individual(const DFLOAT &input, const unsigned int j) // Not my proudest implementation, ngl... but it does the job for now
                {
                    // TODO: 2024-03-09 I guess?? Why Don't you just declare `static byte F1` here?  
                    if (j == 0){ // if it is the first input then create output array (for the output layer of this current layer)
                        #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
                            outputs = new DFLOAT[_numberOfOutputs];
                        #endif
                        #if defined(ACTIVATION__PER_LAYER)
                            me->F1 = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<byte>(me->address));
                        #endif
                        #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                            bias = new IDFLOAT(me->get_type_memmory_value<IDFLOAT>(me->address));
                        #endif
                    }else{
                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                            #if defined(ACTIVATION__PER_LAYER)
                                me->address += SIZEOF_FX; 
                            #endif
                        #else
                            #if defined(NO_BIAS)
                                #if defined(ACTIVATION__PER_LAYER)
                                    me->address += SIZEOF_FX;
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
                        bias = new IDFLOAT(me->get_type_memmory_value<IDFLOAT>(me->address));
                    #endif

                    IDFLOAT tmp_jweight;
                    for (unsigned int i = 0; i < _numberOfOutputs; i++) 
                    {
                        if (j == 0){
                            #if defined(NO_BIAS)
                                outputs[i] = 0;
                            #else
                                outputs[i] = *bias MULTIPLY_BY_INT_IF_QUANTIZATION;
                            #endif
                        }
                        #if defined(USE_INTERNAL_EEPROM)
                            outputs[i] += input * TYPE_MEMMORY_ME_GET(me->address + j*sizeof(IDFLOAT), tmp_jweight) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #else // USE_EXTERNAL_FRAM
                            TYPE_MEMMORY_ME_GET(me->address + j*sizeof(IDFLOAT), tmp_jweight);
                            outputs[i] += input * tmp_jweight MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #endif
                        me->address += _numberOfInputs * sizeof(IDFLOAT); 

                        // when all individual inputs get summed and multiplied by their weights in their output, then pass them from the activation function
                        if (j == _numberOfInputs -1){
                            accumulatedDotProduct(hiddenStates, &outputs[i], _numberOfOutputs); // WithSrc2Address
                            #if defined(ACTIVATION__PER_LAYER)
                                outputs[i] = (IS_THIS(activation_Function_ptrs)[me->F1])(outputs[i]); // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                            #elif defined(Softmax)
                                outputs[i] = exp(outputs[i]);
                                me->sumOfSoftmax += outputs[i];
                            #else
                                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                            #endif
                        }else{
                            me->address += _numberOfOutputs * sizeof(IDFLOAT); 
                        }
                        #if defined(MULTIPLE_BIASES_PER_LAYER) //WARN: This line is suspicious in case of when reading beyond EEPROM's length (which might happen if the initial-address (until the length of the NN in type-memmory) is not less than 4 bytes away from the end)
                            *bias = me->get_type_memmory_value<IDFLOAT>(me->address);
                        #endif
                    }
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        delete bias;
                    #endif

                    if (j == _numberOfInputs -1){
                        #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                            delete bias;
                        #endif

                        #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                            // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                            if (me->F1 == SOFTMAX_POSITION_IN_ARRAY)
                                Softmax();
                        #elif defined(Softmax)
                            Softmax();
                        #endif

                        // Update the hidden states **after** all outputs are computed
                        #if defined(REDUCED_SKETCH_SIZE_DOT_PROD)
                            unsigned int i = 0;
                            do {
                                hiddenStates[i] = outputs[i];
                            } while (++i != _numberOfOutputs);
                        #else
                            for (unsigned int i = 0; i < _numberOfOutputs; i++)
                                hiddenStates[j] = outputs[j];
                        #endif
                    }
                }
            #endif


            void NeuralNetwork::Layer::FeedForward_Individual(const DFLOAT &input, const unsigned int j) // Not my proudest implementation, ngl... but it does the job for now
            {
                // TODO: 2024-03-09 I guess?? Why Don't you just declare `static byte F1` here?  
                if (j == 0){ // if it is the first input then create output array (for the output layer of this current layer)
                    #if defined(REDUCE_RAM_DELETE_OUTPUTS) 
                        outputs = new DFLOAT[_numberOfOutputs];
                    #endif
                    #if defined(ACTIVATION__PER_LAYER)
                        me->F1 = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<byte>(me->address));
                    #endif
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        bias = new IDFLOAT(me->get_type_memmory_value<IDFLOAT>(me->address));
                    #endif
                }else{
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        #if defined(ACTIVATION__PER_LAYER)
                            me->address += SIZEOF_FX; 
                        #endif
                    #else
                        #if defined(NO_BIAS)
                            #if defined(ACTIVATION__PER_LAYER)
                                me->address += SIZEOF_FX;
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
                    bias = new IDFLOAT(me->get_type_memmory_value<IDFLOAT>(me->address));
                #endif

                IDFLOAT tmp_jweight;
                for (unsigned int i = 0; i < _numberOfOutputs; i++) 
                {
                    if (j == 0){
                        #if defined(NO_BIAS)
                            outputs[i] = 0;
                        #else
                            outputs[i] = *bias MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #endif
                    }
                    #if defined(USE_INTERNAL_EEPROM)
                        outputs[i] += input * TYPE_MEMMORY_ME_GET(me->address + j*sizeof(IDFLOAT), tmp_jweight) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #else // USE_EXTERNAL_FRAM
                        TYPE_MEMMORY_ME_GET(me->address + j*sizeof(IDFLOAT), tmp_jweight);
                        outputs[i] += input * tmp_jweight MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #endif
                    me->address += _numberOfInputs * sizeof(IDFLOAT); 

                    // when all individual inputs get summed and multiplied by their weights in their output, then pass them from the activation function
                    if (j == _numberOfInputs -1){
                        // #if defined(USE_RNN_LAYERS_ONLY) // #20
                        //     accumulatedDotProduct(hiddenStates, &outputs[i], _numberOfOutputs); // WithSrc2Address
                        // #endif
                        #if defined(ACTIVATION__PER_LAYER)
                            outputs[i] = (IS_THIS(activation_Function_ptrs)[me->F1])(outputs[i]); // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                        #elif defined(Softmax)
                            outputs[i] = exp(outputs[i]);
                            me->sumOfSoftmax += outputs[i];
                        #else
                            outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                        #endif
                    // }else{ // #20
                    //     #if defined(USE_RNN_LAYERS_ONLY)
                    //         me->address += _numberOfOutputs * sizeof(IDFLOAT); 
                    //     #endif
                    }
                    #if defined(MULTIPLE_BIASES_PER_LAYER) //WARN: This line is suspicious in case of when reading beyond EEPROM's length (which might happen if the initial-address (until the length of the NN in type-memmory) is not less than 4 bytes away from the end)
                        *bias = me->get_type_memmory_value<IDFLOAT>(me->address);
                    #endif
                }
                #if defined(MULTIPLE_BIASES_PER_LAYER)
                    delete bias;
                #endif

                if (j == _numberOfInputs -1){
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        delete bias;
                    #endif

                    #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                        // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                        if (me->F1 == SOFTMAX_POSITION_IN_ARRAY)
                            Softmax();
                    #elif defined(Softmax)
                        Softmax();
                    #endif

                    // // Update the hidden states **after** all outputs are computed // #20
                    // #if defined(USE_RNN_LAYERS_ONLY)
                    //     for (unsigned int k = 0; k < _numberOfOutputs; k++)
                    //         hiddenStates[k] = outputs[k];
                    // #endif
                }
            }


        #else // IF NOT(defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM))
            #if defined(USE_RNN_LAYERS_ONLY)
                void NeuralNetwork::Layer::RNN_Only_FeedForward_Individual(const DFLOAT &input, const unsigned int j)
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
                    unsigned int i;
                    for (i = 0; i < _numberOfOutputs; i++)
                    {
                        if (j == 0){
                            #if defined(NO_BIAS)
                                outputs[i] = 0; // ? speed ? safe one..
                            #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                                outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                            #else
                                outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION;
                            #endif
                        }

                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            outputs[i] += input * TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j+j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #else
                            outputs[i] += input * TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION; // if double pgm_read_dword 
                        #endif

                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            me->i_j += _numberOfInputs;
                        #endif

                        // when all individual inputs get summed and multiplied by their weights in their output, then pass them from the activation function
                        if (j == _numberOfInputs -1){
                            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &me->weights[me->i_j], &outputs[i], _numberOfOutputs); // ACCUMULATED_DOT_PRODUCT_OF is safe, since PROGMEM is Blocked for esp32-s3
                            #else
                                ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &weights[i][_numberOfInputs], &outputs[i], _numberOfOutputs);
                            #endif
                            #if defined(ACTIVATION__PER_LAYER)
                                outputs[i] = (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[0])])(outputs[i]);  // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                            #elif defined(Softmax)
                                outputs[i] = exp(outputs[i]);
                                me->sumOfSoftmax += outputs[i];
                            #else
                                outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); // if double pgm_read_dword //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                            #endif
                        }else{
                            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                me->i_j += _numberOfOutputs;
                            #endif
                        }
                    }

                    if (j == _numberOfInputs -1){
                        #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                            // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                            if (GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[0]) == SOFTMAX_POSITION_IN_ARRAY)
                                Softmax();
                        #elif defined(Softmax)
                            Softmax();
                        #endif

                        // Update the hidden states **after** all outputs are computed
                        #if defined(REDUCED_SKETCH_SIZE_DOT_PROD)
                            i = 0;
                            do {
                                hiddenStates[i] = outputs[i];
                            } while (++i != _numberOfOutputs);
                        #else
                            for (i = 0; i < _numberOfOutputs; i++)
                                hiddenStates[i] = outputs[i];
                        #endif
                    }
                }
            #endif


            void NeuralNetwork::Layer::FeedForward_Individual(const DFLOAT &input, const unsigned int j)
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
                unsigned int i;
                for (i = 0; i < _numberOfOutputs; i++)
                {
                    if (j == 0){
                        #if defined(NO_BIAS)
                            outputs[i] = 0; // ? speed ? safe one..
                        #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                            outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #else
                            outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        #endif
                    }

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        outputs[i] += input * TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j+j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #else
                        outputs[i] += input * TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #endif

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        me->i_j += _numberOfInputs;
                    #endif

                    // when all individual inputs get summed and multiplied by their weights in their output, then pass them from the activation function
                    if (j == _numberOfInputs -1){
                        // #if defined(USE_RNN_LAYERS_ONLY) // #20
                        //     #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        //         ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &me->weights[me->i_j], &outputs[i], _numberOfOutputs); // ACCUMULATED_DOT_PRODUCT_OF is safe, since PROGMEM is Blocked for esp32-s3
                        //     #else
                        //         ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &weights[i][_numberOfInputs], &outputs[i], _numberOfOutputs);
                        //     #endif
                        // #endif
                        #if defined(ACTIVATION__PER_LAYER)
                            outputs[i] = (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[0])])(outputs[i]);  // AtlayerIndex is always 0 because FeedForward_Individual always refers to first layer
                        #elif defined(Softmax)
                            outputs[i] = exp(outputs[i]);
                            me->sumOfSoftmax += outputs[i];
                        #else
                            outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); // if double pgm_read_dword
                        #endif
                    // }else{ // #20
                    //     #if defined(USE_RNN_LAYERS_ONLY) && defined(REDUCE_RAM_WEIGHTS_LVL2)
                    //         me->i_j += _numberOfOutputs;
                    //     #endif
                    }
                }

                if (j == _numberOfInputs -1){
                    #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                        // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                        if (GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[0]) == SOFTMAX_POSITION_IN_ARRAY)
                            Softmax();
                    #elif defined(Softmax)
                        Softmax();
                    #endif

                    // // Update the hidden states **after** all outputs are computed // #20
                    // #if defined(USE_RNN_LAYERS_ONLY)
                    //     for (unsigned int k = 0; k < _numberOfOutputs; k++)
                    //         hiddenStates[k] = outputs[k];
                    // #endif 
                }
            }
        #endif // defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)) ELSE [OR NOT...]
    #endif // defined(SUPPORTS_INDIVIDUAL_FEEDFORWARD)


    #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
        #if defined(USE_RNN_LAYERS_ONLY) or defined(USE_PAIR__DENSE_RNN) // #20 && !
            template<typename T>
            void NeuralNetwork::Layer::RNN_Only_FeedForward(const T *inputs)
            {
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif
                #if defined(ACTIVATION__PER_LAYER)
                    byte fx = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<LayerType>(me->address)); 
                #endif

                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    DFLOAT tmp_bias = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; // NOTE: #28
                #endif
                for (unsigned int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(NO_BIAS)
                        outputs[i] = 0;
                    #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                        outputs[i] = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; 
                    #else
                        outputs[i] = tmp_bias;
                    #endif

                    accumulatedDotProduct(inputs, &outputs[i], _numberOfInputs); // WithSrc2Address
                    accumulatedDotProduct(hiddenStates, &outputs[i], _numberOfOutputs); // WithSrc2Address

                    #if defined(ACTIVATION__PER_LAYER)
                        outputs[i] = (IS_THIS(activation_Function_ptrs)[fx])(outputs[i]);
                    #elif defined(Softmax)
                        outputs[i] = exp(outputs[i]);
                        me->sumOfSoftmax += outputs[i];
                    #else
                        outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]);
                    #endif
                }

                #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                    // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                    if (fx == SOFTMAX_POSITION_IN_ARRAY)
                        Softmax();
                #elif defined(Softmax)
                    Softmax();
                #endif

                // Update the hidden states **after** all outputs are computed
                #if defined(REDUCED_SKETCH_SIZE_DOT_PROD)
                    unsigned int i = 0;
                    do {
                        hiddenStates[i] = outputs[i];
                    } while (++i != _numberOfOutputs);
                #else
                    for (unsigned int i = 0; i < _numberOfOutputs; i++)
                        hiddenStates[i] = outputs[i];
                #endif
            }
        #endif


        template<typename T>
        void NeuralNetwork::Layer::FeedForward(const T *inputs)
        {
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs];
            #endif
            #if defined(ACTIVATION__PER_LAYER) // #27
                byte fx = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<LayerType>(me->address)); // #23
            #endif
            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER) // #27
                DFLOAT tmp_bias = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; // NOTE: #28
            #endif
            for (unsigned int i = 0; i < _numberOfOutputs; i++)
            {
                #if defined(NO_BIAS)
                    outputs[i] = 0;
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION; 
                #else
                    outputs[i] = tmp_bias;
                #endif

                // #if defined(USE_RNN_LAYERS_ONLY) // #20
                //     accumulatedDotProduct(inputs, &outputs[i], _numberOfInputs); // WithSrc2Address
                //     accumulatedDotProduct(hiddenStates, &outputs[i], _numberOfOutputs); // WithSrc2Address
                // #else // if simple ANN-MLP
                    #if defined(REDUCED_SKETCH_SIZE_DOT_PROD) // WARN: #26
                        unsigned int j = 0;
                        do {
                            outputs[i] += inputs[j] * me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        } while (++j != _numberOfInputs);
                    #else
                        for (unsigned int j = 0; j < _numberOfInputs; j++) // REDUCE_RAM_WEIGHTS_LVL2 is disabled
                            outputs[i] += inputs[j] * me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #endif
                // #endif

                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = (IS_THIS(activation_Function_ptrs)[fx])(outputs[i]);
                #elif defined(Softmax)
                    outputs[i] = exp(outputs[i]);
                    me->sumOfSoftmax += outputs[i];
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]);
                #endif
            }

            #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                if (fx == SOFTMAX_POSITION_IN_ARRAY)
                    Softmax();
            #elif defined(Softmax)
                Softmax();
            #endif

            // // Update the hidden states **after** all outputs are computed
            // #if defined(USE_RNN_LAYERS_ONLY) // #20
            //     for (unsigned int i = 0; i < _numberOfOutputs; i++)
            //         hiddenStates[i] = outputs[i];
            // #endif 
        }


        #if defined(HAS_GATED_OUTPUTS)
            // gateAccumulatedDotProductWithActivationAndBiases 
            template<typename T, typename T2>
            void NeuralNetwork::Layer::gateActivationOf(const T *inputs, const DFLOAT *inputs2 OPTIONAL_SINGLE_BIAS(const DFLOAT tmp_single_bias), T2 activate, DFLOAT *_outputs)
            {
                for (unsigned int i = 0; i < _numberOfOutputs; i++){
                    #if defined(NO_BIAS)
                        _outputs[i] = 0;
                    #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                        _outputs[i] = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #else 
                        // MULTIPLY_BY_INT_IF_QUANTIZATION is done, don't worry
                        _outputs[i] = tmp_single_bias; // #14 #15 using bias instead of b since it's single per layer // 2025-05-01 04:46:32 PM  TODO: Tensorflow custom training class-implementation
                    #endif

                    ACCUMULATED_DOT_PRODUCT_OF(inputs , &_outputs[i], _numberOfInputs);
                    ACCUMULATED_DOT_PRODUCT_OF(inputs2, &_outputs[i], _numberOfOutputs); 

                    _outputs[i] = activate(_outputs[i]);
                }
            }
        #endif


        #if defined(USE_GRU_LAYERS_ONLY)
            template<typename T>
            void NeuralNetwork::Layer::GRU_Only_FeedForward(const T *inputs)
            {
                #if defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // NOTE: in stack #29
                    DFLOAT gatedOutputs[_numberOfOutputs];
                #endif
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif

                #if defined(ACTIVATION__PER_LAYER) // TODO: ##27 move this logic to NeuralNetwork::FeedForward since it's kinda shared across architectures
                    byte fx = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<LayerType>(me->address)); // #23
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER) // #27 via *bias ? but... bias is IDFLOAT and not DFLOAT unfortunately so I might change it just for it?
                    DFLOAT tmp_bias = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;  // NOTE: ##28 DFLOAT not IDFLOAT
                #endif

                // Since they are MCUs we care a bit more about sketch size vs speed (not that it can be way faster but anyways)
                gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), GRU_ACTIVATION_FUNCTION, gatedOutputs); // r_t #14

                for(unsigned int i =0; i < _numberOfOutputs; i++)
                    gatedOutputs[i] *= hiddenStates[i]; // r_t = r_t * h_(t-1)

                #if defined(ACTIVATION__PER_LAYER)
                    gateActivationOf(inputs,gatedOutputs OPTIONAL_SINGLE_BIAS(tmp_bias), fx, outputs); // Candidate Hidden-State/Output #14
                #else
                    gateActivationOf(inputs,gatedOutputs OPTIONAL_SINGLE_BIAS(tmp_bias), ACTIVATION_FUNCTION, outputs); // Candidate Hidden-State/Output #14
                #endif

                gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), GRU_ACTIVATION_FUNCTION, gatedOutputs); // Update State #14 

                // Update the hidden states **after** all outputs are computed
                for (unsigned int i = 0; i < _numberOfOutputs; i++){
                    outputs[i] = gatedOutputs[i] * (hiddenStates[i] - outputs[i]) + outputs[i]; // h = z * (h_old - hnew) + hnew <=> h = z * h_old + (1 - z) * hnew --> https://stats.stackexchange.com/a/613773/466641 
                    hiddenStates[i] = outputs[i];
                }
            }
        #endif


        #if defined(USE_LSTM_LAYERS_ONLY)
            template<typename T>
            void NeuralNetwork::Layer::LSTM_Only_FeedForward(const T *inputs)
            {
                #if defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // NOTE: in stack #29
                    DFLOAT gatedOutputs[_numberOfOutputs];
                #endif
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif

                #if defined(ACTIVATION__PER_LAYER) // TODO: ##27 move this logic to NeuralNetwork::FeedForward since it's kinda shared across architectures
                    byte fx = GET_ACTIVATION_FUNCTION_FROM(me->get_type_memmory_value<LayerType>(me->address)); // #23
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER) // #27 via *bias ? but... bias is IDFLOAT and not DFLOAT unfortunately so I might change it just for it?
                    DFLOAT tmp_bias = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;  // NOTE: ##28 DFLOAT not IDFLOAT
                #endif

                gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), LSTM_ACTIVATION_FUNCTION, gatedOutputs); // f_t (Forget-Gate at time t) #14

                for (unsigned int i=0; i < _numberOfOutputs; i++) // c_t = f_t * c_t-1 ... | Could be SIMD?
                    cellStates[i] *= gatedOutputs[i];

                gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), LSTM_ACTIVATION_FUNCTION, gatedOutputs); // u_t (Update-Gate at time t) #14

                // CellState-Gate
                #if defined(ACTIVATION__PER_LAYER)
                    gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), fx, outputs); // #14
                #else
                    gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), ACTIVATION_FUNCTION, outputs); // #14
                #endif

                for (unsigned int i=0; i < _numberOfOutputs; i++) // ... + u_t * CellStateGate_t
                    cellStates[i] += gatedOutputs[i] * outputs[i];

                gateActivationOf(inputs,hiddenStates OPTIONAL_SINGLE_BIAS(tmp_bias), LSTM_ACTIVATION_FUNCTION, outputs); // o_t (Output-Gate at time t) #14

                for (unsigned int i=0; i < _numberOfOutputs; i++){
                    #if defined(ACTIVATION__PER_LAYER)
                        outputs[i] *= fx(cellStates[i]);
                    #else
                        outputs[i] *= ACTIVATION_FUNCTION(cellStates[i]);
                    #endif
                    hiddenStates[i] = outputs[i];
                }
            }
        #endif


    #else // IF NOT (defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM))
        template<typename T>
        void NeuralNetwork::Layer::accumulatedDotProduct(const T *src1, const IDFLOAT *src2, DFLOAT *dest, unsigned int len)
        {
            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                me->i_j+= len; // We keep this for Backprop but //TODO: might remove it when (NO_BACKPROP and (NO USE_RNN_LAYERS_ONLY))
            #endif

            #if defined(REDUCED_SKETCH_SIZE_DOT_PROD) // WARN: #26
                do {
                    *dest += (*src1++) * TYPE_MEMMORY_READ_IDFLOAT(*src2++) MULTIPLY_BY_INT_IF_QUANTIZATION;
                } while (--len);
            #else
                for (unsigned int i = 0; i < len; i++)
                    *dest += src1[i] * TYPE_MEMMORY_READ_IDFLOAT(src2[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
            #endif
        }


        template<typename T>
        void NeuralNetwork::Layer::FeedForward(const T *inputs) //*
        {
            #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                outputs = new DFLOAT[_numberOfOutputs];
            #endif
            
            //feed forwards
            for (unsigned int i = 0; i < _numberOfOutputs; i++)
            {
                #if defined(NO_BIAS)
                    outputs[i] = 0;
                #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                    outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                #else
                    outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION; // TODO: Do the MULTIPLY_BY_INT_IF_QUANTIZATION-computation once, outside the loop, in a temp-variable when single-bias per layer.... Maybe? also in feedforward etc.
                #endif

                // https://github.com/GiorgosXou/NeuralNetworks/discussions/16#discussioncomment-7479256
                #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                    ACCUMULATED_DOT_PRODUCT_OF(inputs, &me->weights[me->i_j], &outputs[i], _numberOfInputs);
                #else
                    ACCUMULATED_DOT_PRODUCT_OF(inputs, weights[i], &outputs[i], _numberOfInputs);
                #endif

                // #if defined(USE_RNN_LAYERS_ONLY) // #20
                //     #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                //         ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &me->weights[me->i_j], &outputs[i], _numberOfOutputs);
                //     #else
                //         ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &weights[i][_numberOfInputs], &outputs[i], _numberOfOutputs);
                //     #endif
                // #endif

                #if defined(ACTIVATION__PER_LAYER)
                    outputs[i] = (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])])(outputs[i]);
                #elif defined(Softmax)
                    outputs[i] = exp(outputs[i]);
                    me->sumOfSoftmax += outputs[i];
                #else
                    outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                #endif
            }

            #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                if (GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex]) == SOFTMAX_POSITION_IN_ARRAY)
                    Softmax();
            #elif defined(Softmax)
                Softmax();
            #endif

            // // Update the hidden states **after** all outputs are computed // #20
            // #if defined(USE_RNN_LAYERS_ONLY)
            //     for (unsigned int i = 0; i < _numberOfOutputs; i++)
            //         hiddenStates[i] = outputs[i];
            // #endif 

            // return outputs;
        } 


        #if defined(USE_RNN_LAYERS_ONLY) or defined(USE_PAIR__DENSE_RNN) // #20 && !
            template<typename T>
            void NeuralNetwork::Layer::RNN_Only_FeedForward(const T *inputs) //*
            {
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif
                
                //feed forwards
                for (unsigned int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(NO_BIAS)
                        outputs[i] = 0;
                    #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                        outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #else
                        outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION; // TODO: Do the MULTIPLY_BY_INT_IF_QUANTIZATION-computation once, outside the loop, in a temp-variable when single-bias per layer.... Maybe? also in feedforward etc.
                    #endif

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        ACCUMULATED_DOT_PRODUCT_OF(inputs, &me->weights[me->i_j], &outputs[i], _numberOfInputs);
                        ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &me->weights[me->i_j], &outputs[i], _numberOfOutputs);
                    #else
                        ACCUMULATED_DOT_PRODUCT_OF(inputs, weights[i], &outputs[i], _numberOfInputs); // https://github.com/GiorgosXou/NeuralNetworks/discussions/16#discussioncomment-7479256
                        ACCUMULATED_DOT_PRODUCT_OF(hiddenStates, &weights[i][_numberOfInputs], &outputs[i], _numberOfOutputs);
                    #endif

                    #if defined(ACTIVATION__PER_LAYER)
                        outputs[i] = (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])])(outputs[i]);
                    #elif defined(Softmax)
                        outputs[i] = exp(outputs[i]);
                        me->sumOfSoftmax += outputs[i];
                    #else
                        outputs[i] = ACTIVATE_WITH(ACTIVATION_FUNCTION, outputs[i]); //  (neuron[i]'s output) = Sigmoid_Activation_Function_Value_Of((neuron[i]'s output))
                    #endif
                }

                #if (defined(ACTIVATION__PER_LAYER) and defined(Softmax)) or defined(ALL_ACTIVATION_FUNCTIONS)
                    // if current's Activation function == SOFTMAX_POSITION_IN_ARRAY == Softmax then Activate Outputs | costs in computation as much as numberoflayers * 1 or x if softmax
                    if (GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex]) == SOFTMAX_POSITION_IN_ARRAY)
                        Softmax();
                #elif defined(Softmax)
                    Softmax();
                #endif

                // Update the hidden states **after** all outputs are computed
                #if defined(REDUCED_SKETCH_SIZE_DOT_PROD)
                    unsigned int i = 0;
                    do {
                        hiddenStates[i] = outputs[i];
                    } while (++i != _numberOfOutputs);
                #else
                    for (unsigned int i = 0; i < _numberOfOutputs; i++) // TODO: SLOW_PAIR_RNN_SKETCH_REDUCE for dense+vanilla-RNN not with if-confition but a simmple _numberOfOutputs * arch
                        hiddenStates[i] = outputs[i];
                #endif
            }
        #endif
        


        // TODO: (for both GRU & LSTM) when their recurrent-activation-function and their activation-function is the same, then remove T activate and replace activate with the macro ACTIVATION_FUNCTION
        #if defined(HAS_GATED_OUTPUTS)
            // gateAccumulatedDotProductWithActivationAndBiases 
            //  NOTE: Don't worry about offset=0, as far as I tested, it gets optimised for REDUCE_RAM_WEIGHTS_LVL2 via the compilation since it never gets used
            template<typename T, typename T2>
            void NeuralNetwork::Layer::gateActivationOf(const T *inputs, const DFLOAT *inputs2 OPTIONAL_MULTI_BIAS(const IDFLOAT *b), T2 activate, DFLOAT *_outputs, const unsigned int offset)
            {
                for (unsigned int i = 0; i < _numberOfOutputs; i++){
                    #if defined(NO_BIAS)
                        _outputs[i] = 0;
                    #elif defined(MULTIPLE_BIASES_PER_LAYER)                                                                                 // TODO: REDUCE_RAM_BIASES "common reference"
                        _outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(b[i]) MULTIPLY_BY_INT_IF_QUANTIZATION;
                    #else
                        _outputs[i] = TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION; // #14 #15 using bias instead of b since it's single per layer // 2025-05-01 04:46:32 PM  TODO: Tensorflow custom training class-implementation
                    #endif

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        ACCUMULATED_DOT_PRODUCT_OF(inputs , &me->weights[me->i_j], &_outputs[i], _numberOfInputs);
                        ACCUMULATED_DOT_PRODUCT_OF(inputs2, &me->weights[me->i_j], &_outputs[i], _numberOfOutputs); 
                    #else
                        ACCUMULATED_DOT_PRODUCT_OF(inputs , &weights[i][offset], &_outputs[i], _numberOfInputs);
                        ACCUMULATED_DOT_PRODUCT_OF(inputs2, &weights[i][offset + _numberOfInputs], &_outputs[i], _numberOfOutputs);
                    #endif

                    _outputs[i] = activate(_outputs[i]);
                }
            }
        #endif


        #if defined(USE_GRU_LAYERS_ONLY)
            template<typename T>
            void NeuralNetwork::Layer::GRU_Only_FeedForward(const T *inputs)
            {
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif
                // TODO: 2025-05-17 08:25:02 AM | Actually instead of new/creating & deleting gatedOutputs, I should make one common amongs all layers, via: me->gatedOutputs (at the size of the largest layer) and delete it at the end of NeuralNetwork::feedforward (or not deleting at all [for extra speed])
                // or something along those lines... might split it into multiple optimization macro-parameters.
                // And don't forget to #define NO_BACKPROP | (no issue with redefinition since it's value is nothing)
                #if defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // NOTE: in stack #29 | this above "trick", doesn't seem to be the same case here :P
                    DFLOAT gatedOutputs[_numberOfOutputs];
                #endif

                // Since they are MCUs we care a bit more about sketch size vs speed (not that it can be way faster but anyways)
                gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(bias), GRU_ACTIVATION_FUNCTION, gatedOutputs); // r_t #14

                for(unsigned int i =0; i < _numberOfOutputs; i++)
                    gatedOutputs[i] *= hiddenStates[i]; // r_t = r_t * h_(t-1)

                #if defined(ACTIVATION__PER_LAYER)
                    gateActivationOf(inputs,gatedOutputs OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs]), (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])]), outputs, (_numberOfInputs+_numberOfOutputs)); // Candidate Hidden-State/Output #14
                #else
                    gateActivationOf(inputs,gatedOutputs OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs]), ACTIVATION_FUNCTION, outputs, (_numberOfInputs+_numberOfOutputs)); // Candidate Hidden-State/Output #14
                #endif

                gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*2]), GRU_ACTIVATION_FUNCTION, gatedOutputs, (_numberOfInputs+_numberOfOutputs)*2); // Update State #14 

                // Update the hidden states **after** all outputs are computed
                for (unsigned int i = 0; i < _numberOfOutputs; i++){
                    outputs[i] = gatedOutputs[i] * (hiddenStates[i] - outputs[i]) + outputs[i]; // h = z * (h_old - hnew) + hnew <=> h = z * h_old + (1 - z) * hnew --> https://stats.stackexchange.com/a/613773/466641 
                    hiddenStates[i] = outputs[i];
                }
            }
        #endif


        #if defined(USE_LSTM_LAYERS_ONLY)
            template<typename T>
            void NeuralNetwork::Layer::LSTM_Only_FeedForward(const T *inputs)
            {
                #if defined(REDUCE_RAM_DELETE__GATED_OUTPUTS) // NOTE: in stack #29 | btw keep it above the new statement it uses less sketch size
                    DFLOAT gatedOutputs[_numberOfOutputs];
                #endif
                #if defined(REDUCE_RAM_DELETE_OUTPUTS)
                    outputs = new DFLOAT[_numberOfOutputs];
                #endif

                gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(bias), LSTM_ACTIVATION_FUNCTION, gatedOutputs); // f_t (Forget-Gate at time t) #14

                for (unsigned int i=0; i < _numberOfOutputs; i++) // c_t = f_t * c_t-1 ... | Could be SIMD?
                    cellStates[i] *= gatedOutputs[i];

                gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs]), LSTM_ACTIVATION_FUNCTION, gatedOutputs, (_numberOfInputs+_numberOfOutputs)); // u_t (Update-Gate at time t) #14

                // CellState-Gate
                #if defined(ACTIVATION__PER_LAYER)
                    gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*2]), (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])]), outputs, (_numberOfInputs+_numberOfOutputs)*2); // #14
                #else
                    gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*2]), ACTIVATION_FUNCTION, outputs, (_numberOfInputs+_numberOfOutputs)*2); // #14
                #endif

                for (unsigned int i=0; i < _numberOfOutputs; i++) // ... + u_t * CellStateGate_t
                    cellStates[i] += gatedOutputs[i] * outputs[i];

                gateActivationOf(inputs,hiddenStates OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*3]), LSTM_ACTIVATION_FUNCTION, outputs, (_numberOfInputs+_numberOfOutputs)*3); // o_t (Output-Gate at time t) #14

                for (unsigned int i=0; i < _numberOfOutputs; i++){
                    #if defined(ACTIVATION__PER_LAYER)
                        outputs[i] *= (IS_THIS(activation_Function_ptrs)[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])])(cellStates[i]);
                    #else
                        outputs[i] *= ACTIVATION_FUNCTION(cellStates[i]);
                    #endif
                    hiddenStates[i] = outputs[i];
                }

            }
        #endif
    #endif // (defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)) [OR NOT]

    
    DFLOAT NeuralNetwork::Layer::erf(DFLOAT x)
    {
        DFLOAT sign = (x < 0) ? -1.0 : 1.0;

        x = fabs(x);

        // A&S formula 7.1.26 (Abramowitz & Stegun)
        DFLOAT t = 1.0/(1.0 + 0.3275911*x);

        // return sign*y;
        return sign*(1.0 - (((((1.061405429*t - 1.453152027)*t) + 1.421413741)*t - 0.284496736)*t + 0.254829592)*t*exp(-x*x));
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
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(LeakyReLU)
        DFLOAT NeuralNetwork::Layer::LeakyReLU  (const DFLOAT &x) { return (x > 0) ? x : AlphaLeaky * x                ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(ELU)
        DFLOAT NeuralNetwork::Layer::ELU       (const DFLOAT &x) { return (x > 0) ? x : AlphaELU  * (exp(x) - 1)       ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(SELU)
        DFLOAT NeuralNetwork::Layer::SELU      (const DFLOAT &x) { return (x >= 0) ? x * LamdaSELU : LamdaSELU * AlphaSELU * (exp(x) - 1)       ;}
    #endif
    #if defined(ALL_ACTIVATION_FUNCTIONS) or defined(Softmax)
        DFLOAT NeuralNetwork::Layer::SoftmaxSum(const DFLOAT &x) { DFLOAT tmp = exp(x); me->sumOfSoftmax +=tmp; return tmp  ;}
        void  NeuralNetwork::Layer::Softmax() {for (unsigned int i = 0; i < _numberOfOutputs; i++){outputs[i] /= me->sumOfSoftmax;}; me->sumOfSoftmax = 0;}
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

        #if defined(LeakyReLU)    
            DFLOAT NeuralNetwork::Layer::LeakyReLUDer(const DFLOAT &fx) { return (fx > 0) ? 1 : AlphaLeaky                                 ;}
        #endif
        #if defined(ELU)
            DFLOAT NeuralNetwork::Layer::ELUDer     (const DFLOAT &fx) { return (fx > 0) ? 1 : fx + AlphaELU                              ;}
        #endif
        #if defined(SELU)
            DFLOAT NeuralNetwork::Layer::SELUDer    (const DFLOAT &fx) { return (fx >= 0) ? LamdaSELU : fx + AlphaSELU * LamdaSELU ;}
        #endif
        
        DFLOAT NeuralNetwork::Layer::SoftmaxDer     (const DFLOAT &fx) { return fx * (1 - fx)                                                 ;} // hmm...?
        DFLOAT NeuralNetwork::Layer::IdentityDer    (const DFLOAT &x ) {return 1                                                              ;}


        void NeuralNetwork::Layer::CommonCompute(DFLOAT &gamma, DFLOAT preLgammaORgamma, const DFLOAT *inputs, unsigned int i, unsigned int j=0)
        {
            #if defined(ACTIVATION__PER_LAYER)
                gamma = preLgammaORgamma * (IS_THIS(derivative_Function_ptrs[GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])]))(outputs[i]);
            #else
                gamma = preLgammaORgamma * DERIVATIVE_OF(ACTIVATION_FUNCTION, outputs[i]); // if i remember well , frontLayer->preLgamma[i] means current layer gamma?
            #endif

            #if defined(MULTIPLE_BIASES_PER_LAYER)
                bias[i] -= gamma * me->LearningRateOfBiases; // This is the only line in the entire source-code, for which I asked and slightly trusted CHATGPT, because I wasn't 100% sure
            #endif

            #if defined(REDUCE_RAM_WEIGHTS_LVL2) // [Reference: #9]
                do {
                    j--;
                    me->i_j--;
                    preLgamma[j] += gamma * me->weights[me->i_j];
                    me->weights[me->i_j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                } while (j != 0 );
            #else
                for (; j < _numberOfInputs; j++)
                {
                    preLgamma[j] += gamma * weights[i][j];
                    weights[i][j] -= (gamma * inputs[j]) * me->LearningRateOfWeights;
                }
            #endif
        }


        void NeuralNetwork::Layer::BackPropOutput(const DFLOAT *_expected_, const DFLOAT *inputs)
        {

            preLgamma = new DFLOAT[_numberOfInputs]{}; // create gamma of previous layer and initialize{} values to 0 .. meh  // #10
            

            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                DFLOAT bias_Delta = 1.0;
            #endif
            DFLOAT gamma;

            // NOTE: summed errors exist at ComputeSummedErrors too
            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                // ---> #9
                // 3. in other words it's like: for (int i = _numberOfOutputs -1; i >= 0; i--) OR
                // 2. in other words it's like: for (unsigned int i = _numberOfOutputs -1; i != UINT_MAX; i--) OR
                // 1. in other words it's like: for (unsigned int i = _numberOfOutputs -1;; i--){...if (i == 0){ break; }}
                // But since 1. doesn't use unsigned, 2. bloats FLASH-memmory and 3. uses branching and AVRs may not handle it well?
                // ... I ended up with this :P

                unsigned int i = _numberOfOutputs;
                do {
                    i--;
                    //    γ  = (Error) * Derivative_of_Sigmoid_Activation_Function
                    gamma = (outputs[i] - _expected_[i]);
                    
                     // I want to believe that it is being optimised/removed when not used | update 5/8/2021 ain't sure althought i've used "https://godbolt.org/" so... Macros
                    #if defined(CATEGORICAL_CROSS_ENTROPY)
                        me->sumOfCategoricalCrossEntropy -= _expected_[i] * (DFLOAT)log(outputs[i]);
                    #endif
                    #if defined(BINARY_CROSS_ENTROPY)
                        me->sumOfBinaryCrossEntropy -=  _expected_[i] * (DFLOAT)log(outputs[i]) + (1.0 - _expected_[i]) * (DFLOAT)log(1.0 - outputs[i]); // https://forum.arduino.cc/t/maths-help-log/339211 https://math.stackexchange.com/questions/293783/when-log-is-written-without-a-base-is-the-equation-normally-referring-to-log-ba
                    #endif
                    #if defined(MEAN_SQUARED_ERROR) or defined(DEFAULT_LOSS)
                        me->sumSquaredError += gamma * gamma; 
                    #endif

                    CommonCompute(gamma, gamma, inputs, i, _numberOfInputs);

                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        bias_Delta *= gamma;
                    #endif
                } while (i != 0);

            #else
                for (unsigned int i = 0; i < _numberOfOutputs; i++)
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
                    
                    CommonCompute(gamma, gamma, inputs, i);

                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        bias_Delta *= gamma;
                    #endif
                }
            #endif
            
            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                *bias -= bias_Delta * me->LearningRateOfBiases;
            #endif
        }

        void NeuralNetwork::Layer::BackPropHidden(const Layer *frontLayer, const DFLOAT *inputs)
        {
            #if defined(ACTIVATION__PER_LAYER) or defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                me->AtlayerIndex -= 1; 
            #endif
            preLgamma = new DFLOAT[_numberOfInputs]{}; // #10

            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                DFLOAT bias_Delta = 1.0;
            #endif
            DFLOAT gamma;

            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                // [Reference: #9]
                unsigned int i = _numberOfOutputs;
                do {
                    i--;
                    CommonCompute(gamma, frontLayer->preLgamma[i], inputs, i, _numberOfInputs);

                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        bias_Delta *= gamma;
                    #endif
                } while (i != 0);

            #else
                for (unsigned int i = 0; i < _numberOfOutputs; i++)
                {
                    CommonCompute(gamma, frontLayer->preLgamma[i], inputs, i);

                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        bias_Delta *= gamma;
                    #endif
                }
            #endif

            #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                *bias -= bias_Delta * me->LearningRateOfBiases;
            #endif

            delete[] frontLayer->preLgamma;  // #10
        }
    #endif


    //If Microcontroller isn't one of the Attiny Series then it compiles the code below.
    #if !defined(AS__NO_COMMON_SERIAL_SUPPORT) // then Compile:
        #if defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)
            #if defined(USE_RNN_LAYERS_ONLY) // ##25 we don't need `or defined(USE_PAIR__DENSE_RNN)` since DENSE & RNN are merged together in plain-print
                void NeuralNetwork::Layer::RNN_Only_print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex))
                {
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_INT_Q));
                    #else
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_TYPE_MEM));
                    #endif
                    NN_PRINT_1(F_MACRO("RNN [("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("+"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("]"));
                    #if defined(ACTIVATION__PER_LAYER)
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(me->get_type_memmory_value<byte>(me->address));
                    #endif
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    NN_PRINTLN();
                    DFLOAT tmp_ijweight; // Reminder: don't change it to IDFLOAT
                    for (unsigned int i = 0; i < _numberOfOutputs; i++)
                    {
                        #if defined(MULTIPLE_BIASES_PER_LAYER)
                            NN_PRINT_1(F_MACRO("   B:"));
                            NN_PRINTLN_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #endif

                        NN_PRINT_1(i + 1);
                        NN_PRINT_1(F_MACRO(" "));
                        for (unsigned int j = 0; j < _numberOfInputs; j++)
                        {
                            tmp_ijweight = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                            NN_PRINT_1(F_MACRO(" W:"));
                            if (tmp_ijweight > 0 ) NN_PRINT_1(F_MACRO(" "));
                            NN_PRINT_2(tmp_ijweight, DFLOAT_LEN);
                            NN_PRINT_1(F_MACRO(" "));
                        }
                        NN_PRINTLN();

                        NN_PRINT_1(F_MACRO("  "));
                        for (unsigned int j = 0; j < _numberOfOutputs; j++)
                        {
                            tmp_ijweight = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                            NN_PRINT_1(F_MACRO(" U:"));
                            if (tmp_ijweight > 0 ) NN_PRINT_1(F_MACRO(" "));
                            NN_PRINT_2(tmp_ijweight, DFLOAT_LEN);
                            NN_PRINT_1(F_MACRO(" "));
                        }
                        NN_PRINTLN();

                    }
                }
            #endif


            void NeuralNetwork::Layer::print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex))
            {
                #if defined(USE_INT_QUANTIZATION)
                    NN_PRINT_1(F_MACRO(PRINT_MESSAGE_INT_Q));
                #else
                    NN_PRINT_1(F_MACRO(PRINT_MESSAGE_TYPE_MEM));
                #endif
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    LayerType props= me->get_type_memmory_value<LayerType>(me->address); // LayerProps in this case
                    if (props.arch){
                        NN_PRINT_1(F_MACRO("RNN [("));
                        NN_PRINT_1(_numberOfInputs);
                        NN_PRINT_1(F_MACRO("+"));
                        NN_PRINT_1(_numberOfOutputs);
                        NN_PRINT_1(F_MACRO(")"));
                     }else{
                        NN_PRINT_1(F_MACRO("DENSE ["));
                        NN_PRINT_1(_numberOfInputs);
                     }
                #else
                    NN_PRINT_1(F_MACRO("DENSE "));
                    NN_PRINT_1(_numberOfInputs);
                #endif
                NN_PRINT_1(F_MACRO("*"));
                NN_PRINT_1(_numberOfOutputs);
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    NN_PRINT_1(F_MACRO("]"));
                #endif
                #if defined(ACTIVATION__PER_LAYER)
                    NN_PRINT_1(F_MACRO("| F(x):"));
                    #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                        NN_PRINT_1(props.fx);
                    #else
                        NN_PRINT_1(me->get_type_memmory_value<byte>(me->address));
                    #endif
                #endif
                #if defined(SINGLE_TIMESTEP_THRESHOLD)
                    if (_AtlayerIndex == me->atIndex){
                        NN_PRINT_1(F_MACRO("| Threshold:"));
                        NN_PRINT_1(me->threshold);
                    }
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    NN_PRINT_1(F_MACRO("| bias:"));
                    NN_PRINT_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                #endif
                NN_PRINTLN();
                DFLOAT tmp_ijweight; // Reminder: don't change it to IDFLOAT
                for (unsigned int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("   B:"));
                        NN_PRINTLN_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif

                    NN_PRINT_1(i + 1);
                    NN_PRINT_1(F_MACRO(" "));
                    for (unsigned int j = 0; j < _numberOfInputs; j++)
                    {
                        tmp_ijweight = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        NN_PRINT_1(F_MACRO(" W:"));
                        if (tmp_ijweight > 0 ) NN_PRINT_1(F_MACRO(" "));
                        NN_PRINT_2(tmp_ijweight, DFLOAT_LEN);
                        NN_PRINT_1(F_MACRO(" "));
                    }
                    NN_PRINTLN();

                    #if defined(USE_PAIR__DENSE_RNN)
                        NN_PRINT_1(F_MACRO("  "));
                        for (unsigned int j = 0; j < _numberOfOutputs * props.arch; j++)
                        {
                            tmp_ijweight = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                            NN_PRINT_1(F_MACRO(" U:"));
                            if (tmp_ijweight > 0 ) NN_PRINT_1(F_MACRO(" "));
                            NN_PRINT_2(tmp_ijweight, DFLOAT_LEN);
                            NN_PRINT_1(F_MACRO(" "));
                        }
                        NN_PRINTLN();
                    #endif
                }
            }


            #if defined(USE_GRU_LAYERS_ONLY) || defined(USE_LSTM_LAYERS_ONLY)

                void NeuralNetwork::Layer::printGateWeights(const unsigned int len)
                {
                    DFLOAT w; // DFLOAT because we MULTIPLY_BY_INT_IF_QUANTIZATION
                    for (unsigned int i = 0; i < len; i++){
                        w = me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION;
                        NN_PRINT_1(F_MACRO("  W:"));
                        if (w > 0) NN_PRINT_1(F_MACRO(" "));
                        NN_PRINT_2(w, DFLOAT_LEN);
                    }
                    NN_PRINTLN();

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        me->i_j += len;
                    #endif
                }


                void NeuralNetwork::Layer::gatePrint()
                {
                    for (unsigned int i = 0; i < _numberOfOutputs; i++){
                        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                            NN_PRINT_1(F_MACRO("   B:"));
                            NN_PRINTLN_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #endif
                        NN_PRINT_1(i+1); printGateWeights(_numberOfInputs);
                        NN_PRINT_1(i+1); printGateWeights(_numberOfOutputs);
                    }
                }
            #endif


            #if defined(USE_GRU_LAYERS_ONLY)
                void NeuralNetwork::Layer::GRU_Only_print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex))
                {
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_INT_Q));
                    #else
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_TYPE_MEM));
                    #endif
                    NN_PRINT_1(F_MACRO("GRU [(("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")+("));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("))*3] "));
                    #if defined(ACTIVATION__PER_LAYER)
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(me->get_type_memmory_value<byte>(me->address));
                    #endif
                    #if defined(SINGLE_TIMESTEP_THRESHOLD)
                        if (_AtlayerIndex == me->atIndex){
                            NN_PRINT_1(F_MACRO("| Threshold:"));
                            NN_PRINT_1(me->threshold);
                        }
                    #endif
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    NN_PRINTLN();
                    NN_PRINTLN_1(F_MACRO("- RESET -" )); gatePrint();
                    NN_PRINTLN_1(F_MACRO("- HIDDEN -")); gatePrint();
                    NN_PRINTLN_1(F_MACRO("- UPDATE -")); gatePrint(); // #14
                }
            #endif


            #if defined(USE_LSTM_LAYERS_ONLY)
                void NeuralNetwork::Layer::LSTM_Only_print(OPTIONAL_TIME__TYPE_MEMMORY_INDEX(unsigned int _AtlayerIndex))
                { 
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_INT_Q));
                    #else
                        NN_PRINT_1(F_MACRO(PRINT_MESSAGE_TYPE_MEM));
                    #endif
                    NN_PRINT_1(F_MACRO("LSTM [(("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")+("));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("))*4] "));
                    #if defined(ACTIVATION__PER_LAYER)
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(me->get_type_memmory_value<byte>(me->address));
                    #endif
                    #if defined(SINGLE_TIMESTEP_THRESHOLD)
                        if (_AtlayerIndex == me->atIndex){
                            NN_PRINT_1(F_MACRO("| Threshold:"));
                            NN_PRINT_1(me->threshold);
                        }
                    #endif
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(me->get_type_memmory_value<IDFLOAT>(me->address) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    NN_PRINTLN();
                    NN_PRINTLN_1(F_MACRO("- FORGET -")); gatePrint();
                    NN_PRINTLN_1(F_MACRO("- UPDATE -")); gatePrint(); 
                    NN_PRINTLN_1(F_MACRO("- CELL -"  )); gatePrint();
                    NN_PRINTLN_1(F_MACRO("- OUTPUT -")); gatePrint(); // #14
                }
            #endif


        #else // IF NOT (defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM))
            #if defined(USE_GRU_LAYERS_ONLY) || defined(USE_LSTM_LAYERS_ONLY)

                void NeuralNetwork::Layer::printGateWeights(const IDFLOAT *w, const unsigned int len)
                {
                    for (unsigned int i = 0; i < len; i++){
                        NN_PRINT_1(F_MACRO("  W:"));
                        if (TYPE_MEMMORY_READ_IDFLOAT(w[i]) > 0) NN_PRINT_1(F_MACRO(" "));
                        NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(w[i]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    }
                    NN_PRINTLN();

                    #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                        me->i_j += len;
                    #endif
                }


                void NeuralNetwork::Layer::gatePrint(const unsigned int offset OPTIONAL_MULTI_BIAS(const IDFLOAT *b))
                {
                    for (unsigned int i = 0; i < _numberOfOutputs; i++){
                        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                            NN_PRINT_1(F_MACRO("   B:"));
                            NN_PRINTLN_2(TYPE_MEMMORY_READ_IDFLOAT(b[i]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #endif

                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            NN_PRINT_1(i+1); printGateWeights(&me->weights[me->i_j], _numberOfInputs);
                            NN_PRINT_1(i+1); printGateWeights(&me->weights[me->i_j], _numberOfOutputs);
                        #else
                            NN_PRINT_1(i+1); printGateWeights(&weights[i][offset], _numberOfInputs);
                            NN_PRINT_1(i+1); printGateWeights(&weights[i][offset + _numberOfInputs], _numberOfOutputs);
                        #endif
                    }
                }
            #endif


            #if defined(USE_GRU_LAYERS_ONLY)
                void NeuralNetwork::Layer::GRU_Only_print()
                { 
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO("INT_Q "));
                    #endif
                    #if defined(CONST_MODERN_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("CONST* "));
                    #endif
                    #if defined(AVR_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("PROGMEM "));
                    #endif
                    NN_PRINT_1(F_MACRO("GRU [(("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")+("));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("))*3] "));
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    #if defined(ACTIVATION__PER_LAYER) 
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex]));
                    #endif
                    NN_PRINTLN();

                    NN_PRINTLN_1(F_MACRO("- RESET -" )); gatePrint(0                                    OPTIONAL_MULTI_BIAS(bias));
                    NN_PRINTLN_1(F_MACRO("- HIDDEN -")); gatePrint((_numberOfInputs+_numberOfOutputs)   OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs])); 
                    NN_PRINTLN_1(F_MACRO("- UPDATE -")); gatePrint((_numberOfInputs+_numberOfOutputs)*2 OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*2])); // #14
                }
            #endif


            #if defined(USE_LSTM_LAYERS_ONLY)
                void NeuralNetwork::Layer::LSTM_Only_print()
                { 
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO("INT_Q "));
                    #endif
                    #if defined(CONST_MODERN_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("CONST* "));
                    #endif
                    #if defined(AVR_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("PROGMEM "));
                    #endif
                    NN_PRINT_1(F_MACRO("LSTM [(("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")+("));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("))*4] "));
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    #if defined(ACTIVATION__PER_LAYER)
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex]));
                    #endif
                    NN_PRINTLN();

                    NN_PRINTLN_1(F_MACRO("- FORGET -")); gatePrint(0                                    OPTIONAL_MULTI_BIAS(bias));
                    NN_PRINTLN_1(F_MACRO("- UPDATE -")); gatePrint((_numberOfInputs+_numberOfOutputs)   OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs])); 
                    NN_PRINTLN_1(F_MACRO("- CELL -"  )); gatePrint((_numberOfInputs+_numberOfOutputs)*2 OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*2]));
                    NN_PRINTLN_1(F_MACRO("- OUTPUT -")); gatePrint((_numberOfInputs+_numberOfOutputs)*3 OPTIONAL_MULTI_BIAS(&bias[_numberOfOutputs*3])); // #14
                }
            #endif


            #if defined(USE_RNN_LAYERS_ONLY) // #25
                void NeuralNetwork::Layer::RNN_Only_print()
                {
                    #if defined(USE_INT_QUANTIZATION)
                        NN_PRINT_1(F_MACRO("INT_Q "));
                    #endif
                    #if defined(CONST_MODERN_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("CONST* "));
                    #endif
                    #if defined(AVR_PROGMEM_LOGIC)
                        NN_PRINT_1(F_MACRO("PROGMEM "));
                    #endif
                    NN_PRINT_1(F_MACRO("RNN [("));
                    NN_PRINT_1(_numberOfInputs);
                    NN_PRINT_1(F_MACRO("+"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO(")*"));
                    NN_PRINT_1(_numberOfOutputs);
                    NN_PRINT_1(F_MACRO("]"));
                    #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                        NN_PRINT_1(F_MACRO("| bias:"));
                        NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif
                    #if defined(ACTIVATION__PER_LAYER)
                        NN_PRINT_1(F_MACRO("| F(x):"));
                        NN_PRINT_1(GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex]));
                    #endif
                    NN_PRINTLN();

                    for (unsigned int i = 0; i < _numberOfOutputs; i++)
                    {
                        #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                            NN_PRINT_1(F_MACRO("   B:"));
                            NN_PRINTLN_2(TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #endif

                        NN_PRINT_1(i + 1);
                        NN_PRINT_1(F_MACRO(" "));
                        for (unsigned int j = 0; j < _numberOfInputs; j++)
                        {
                            //weights[i][j] = (DFLOAT)j;
                            NN_PRINT_1(F_MACRO(" W:"));
                            #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                                if (TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0) NN_PRINT_1(F_MACRO(" ")); // if gratter than 10 too or something would be nice
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j++]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                            #else
                                if (TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0 ) NN_PRINT_1(F_MACRO(" "));
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                            #endif
                            NN_PRINT_1(F_MACRO(" "));
                        }
                        NN_PRINTLN();

                        NN_PRINT_1(F_MACRO("  "));
                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            for (unsigned int j = 0; j < _numberOfOutputs; j++)
                            {
                                NN_PRINT_1(F_MACRO(" U:"));
                                if (TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0) NN_PRINT_1(F_MACRO(" ")); // if gratter than 10 too or something would be nice
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j++]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                                NN_PRINT_1(F_MACRO(" "));
                            }
                        #else
                            for (unsigned int j = _numberOfInputs; j < (_numberOfInputs + _numberOfOutputs); j++)
                            {
                                NN_PRINT_1(F_MACRO(" U:"));
                                if (TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0 ) NN_PRINT_1(F_MACRO(" "));
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                                NN_PRINT_1(F_MACRO(" "));
                            }
                        #endif
                        NN_PRINTLN();
                    }
                }
            #endif


            void NeuralNetwork::Layer::print()
            {
                #if defined(USE_INT_QUANTIZATION)
                    NN_PRINT_1(F_MACRO("INT_Q "));
                #endif
                #if defined(CONST_MODERN_PROGMEM_LOGIC)
                    NN_PRINT_1(F_MACRO("CONST* "));
                #endif
                #if defined(AVR_PROGMEM_LOGIC)
                    NN_PRINT_1(F_MACRO("PROGMEM "));
                #endif
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    if (me->PropsPerLayer[me->AtlayerIndex].arch){
                        NN_PRINT_1(F_MACRO("RNN [("));
                        NN_PRINT_1(_numberOfInputs);
                        NN_PRINT_1(F_MACRO("+"));
                        NN_PRINT_1(_numberOfOutputs);
                        NN_PRINT_1(F_MACRO(")"));
                    }else{
                        NN_PRINT_1(F_MACRO("DENSE ["));
                        NN_PRINT_1(_numberOfInputs);
                    }
                #else
                    NN_PRINT_1(F_MACRO("DENSE "));
                    NN_PRINT_1(_numberOfInputs);
                #endif
                NN_PRINT_1(F_MACRO("*"));
                NN_PRINT_1(_numberOfOutputs);
                #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES)
                    NN_PRINT_1(F_MACRO("]"));
                #endif
                #if !defined(NO_BIAS) and !defined(MULTIPLE_BIASES_PER_LAYER)
                    NN_PRINT_1(F_MACRO("| bias:"));
                    NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(*bias) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                #endif
                #if defined(ACTIVATION__PER_LAYER)
                    NN_PRINT_1(F_MACRO("| F(x):"));
                    NN_PRINT_1(GET_ACTIVATION_FUNCTION_FROM(me->PropsPerLayer[me->AtlayerIndex])); // NOTE: GET_ACTIVATION_FUNCTION_FROM takes into account plain MULTIPLE_NN_TYPE_ARCHITECTURES
                #endif
                #if defined(SINGLE_TIMESTEP_THRESHOLD)
                    if (me->AtlayerIndex == me->atIndex){
                        NN_PRINT_1(F_MACRO("| Threshold:"));
                        NN_PRINT_1(me->threshold);
                    }
                #endif
                NN_PRINTLN();

                for (unsigned int i = 0; i < _numberOfOutputs; i++)
                {
                    #if defined(MULTIPLE_BIASES_PER_LAYER) // TODO: REDUCE_RAM_BIASES
                        NN_PRINT_1(F_MACRO("   B:"));
                        NN_PRINTLN_2(TYPE_MEMMORY_READ_IDFLOAT(bias[i]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                    #endif

                    NN_PRINT_1(i + 1);
                    NN_PRINT_1(F_MACRO(" "));
                    for (unsigned int j = 0; j < _numberOfInputs; j++)
                    {
                        //weights[i][j] = (DFLOAT)j;
                        NN_PRINT_1(F_MACRO(" W:"));
                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            if (TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0) NN_PRINT_1(F_MACRO(" ")); // if gratter than 10 too or something would be nice
                            NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j++]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #else
                            if (TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0 ) NN_PRINT_1(F_MACRO(" "));
                            NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                        #endif
                        NN_PRINT_1(F_MACRO(" "));
                    }
                    NN_PRINTLN();

                    #if defined(USE_RNN_LAYERS_ONLY) or defined(USE_PAIR__DENSE_RNN)
                        NN_PRINT_1(F_MACRO("  "));
                        #if defined(REDUCE_RAM_WEIGHTS_LVL2)
                            #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES) // might change it to USE_PAIR__DENSE_RNN
                                for (unsigned int j = 0; j < _numberOfOutputs * me->PropsPerLayer[me->AtlayerIndex].arch; j++)
                            #else
                                for (unsigned int j = 0; j < _numberOfOutputs; j++)
                            #endif
                            {
                                NN_PRINT_1(F_MACRO(" U:"));
                                if (TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0) NN_PRINT_1(F_MACRO(" ")); // if gratter than 10 too or something would be nice
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(me->weights[me->i_j++]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                                NN_PRINT_1(F_MACRO(" "));
                            }
                        #else
                            #if defined(MULTIPLE_NN_TYPE_ARCHITECTURES) // might change it to USE_PAIR__DENSE_RNN
                                for (unsigned int j = _numberOfInputs; j < (_numberOfInputs + _numberOfOutputs * me->PropsPerLayer[me->AtlayerIndex].arch); j++)
                            #else
                                for (unsigned int j = _numberOfInputs; j < (_numberOfInputs + _numberOfOutputs); j++)
                            #endif
                            {
                                NN_PRINT_1(F_MACRO(" U:"));
                                if (TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION > 0 ) NN_PRINT_1(F_MACRO(" "));
                                NN_PRINT_2(TYPE_MEMMORY_READ_IDFLOAT(weights[i][j]) MULTIPLY_BY_INT_IF_QUANTIZATION, DFLOAT_LEN);
                                NN_PRINT_1(F_MACRO(" "));
                            }
                        #endif
                        NN_PRINTLN(); // meh...
                    #endif
                }
            }
        #endif // (defined(USE_INTERNAL_EEPROM) or defined(USE_EXTERNAL_FRAM)) [OR NOT]
    #endif // !defined(AS__NO_COMMON_SERIAL_SUPPORT) 
// #pragma endregion Layer.cpp
#endif


/*
#2 https://stackoverflow.com/questions/22318677/is-it-faster-to-have-the-compiler-initialize-an-array-or-to-manually-iterate-over  [I am slightly confused. Anyways...]
#4 https://stackoverflow.com/questions/65860934/undefined-reference-to-outterclassfunction-ptrs-variable-issue

#5 (Most Probably) It will be Optimised by the compiler if no needed
#6 https://stackoverflow.com/questions/68689135/unusual-behavior-unnecessary-variables-inside-a-class-result-in-extra-bytes-of

In Arduino log() = ln = natural logarithm = logarithm with base e 


 TODO: DOCUMENTING OF:
 - USE_RNN__NB
 - USE_GRU__NB
 - DISABLE_STATIC_FOR_ACTS
 TODO: FEATURES:
 - Statistically based training methond idea (instead of gradient based)
 - Maybe a completly int based NN that doesn't use floats?
 - Replace `unsigned int`s with other types via optimization or macro eg. to byte


// TODO: make add inline macro opt
// #define ACCUMULATED_DOT_PRODUCT_OF(a, b, acc, len) \
//     for (unsigned int _i = 0; _i < (len); ++_i){ *(acc) += (a)[_i] * (b)[_i];} 
// and if defined REDUCE_RAM_WEIGHTS_LVL2 then me->i_j += len; and all in a while(0){} loop

*/
