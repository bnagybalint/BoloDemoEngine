#pragma once

#include "Assist/Common.h"

// ----- Debug related stuff ----- 

#if BDE_AUDIO_DS_DEBUG
# define DS_SafeCall( call ) Assert( !FAILED(call) )
#else
# define DS_SafeCall( call ) call
#endif

// ----- Audio related global constants ----- 

const int AUDIO_SAMPLE_FREQ         = 44100         ; // 44100 Hz sampling frequency
const int AUDIO_SAMPLE_CHANNELS     = 1             ; // mono channel setup
const int AUDIO_SAMPLE_BITS         = 16            ; // 2 bytes per sample
const int AUDIO_SAMPLE_SIZE         = sizeof(int16) ; // 1 sample = 1 short 
const int AUDIO_SAMPLE_BLOCKALIGN   = sizeof(int16) ; // DirectSound: must be (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels
const int AUDIO_SAMPLE_MAX_INTVALUE = 32767         ; // (2^15 - 1) = Max value for sample in integer format

