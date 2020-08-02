// *************** BUZZY.H ***************
#ifndef BUZZY_H
#define BUZZY_H

// Based on the libao library
// https://www.xiph.org/ao/doc/libao-api.html

// ================= Include ==================
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "pberr.h"
#include "gset.h"
#include "ao/ao.h"

// ================= Define ==================

#define BUZZY_B7 3951.0660
#define BUZZY_A7 3520.0000
#define BUZZY_G7 3135.9630
#define BUZZY_F7 2793.8260
#define BUZZY_E7 2637.0200
#define BUZZY_D7 2349.2180
#define BUZZY_C7 2093.0050

#define BUZZY_B6 1975.5330
#define BUZZY_A6 1760.0000
#define BUZZY_G6 1567.9820
#define BUZZY_F6 1396.9130
#define BUZZY_E6 1318.5100
#define BUZZY_D6 1174.6590
#define BUZZY_C6 1046.5020

#define BUZZY_B5 0987.7666
#define BUZZY_A5 0880.0000
#define BUZZY_G5 0783.9909
#define BUZZY_F5 0698.4565
#define BUZZY_E5 0659.2551
#define BUZZY_D5 0587.3295
#define BUZZY_C5 0523.2511

#define BUZZY_B4 0493.8833
#define BUZZY_A4 0440.0000
#define BUZZY_G4 0391.9954
#define BUZZY_F4 0349.2282
#define BUZZY_E4 0329.6276
#define BUZZY_D4 0293.6648
#define BUZZY_C4 0261.6256

#define BUZZY_B3 0246.9417
#define BUZZY_A3 0220.0000
#define BUZZY_G3 0195.9977
#define BUZZY_F3 0174.6141
#define BUZZY_E3 0164.8138
#define BUZZY_D3 0146.8324
#define BUZZY_C3 0130.8128

#define BUZZY_B2 0123.4708
#define BUZZY_A2 0110.0000
#define BUZZY_G2 0097.9988
#define BUZZY_F2 0087.3071
#define BUZZY_E2 0082.4069
#define BUZZY_D2 0073.4162
#define BUZZY_C2 0065.4064

#define BUZZY_B1 0061.7354
#define BUZZY_A1 0055.0000
#define BUZZY_G1 0048.9994
#define BUZZY_F1 0043.6535
#define BUZZY_E1 0041.2034
#define BUZZY_D1 0036.7081
#define BUZZY_C1 0032.7032

extern const double BUZZY_RANGE[49];

typedef struct Buzzy Buzzy;
typedef struct BuzzyNote BuzzyNote;
#define BUZZY_NOTE_SHAPE void(*noteShape)( \
  Buzzy*, BuzzyNote*, double, double,  double*)

// ================= Data structures ===================

typedef struct Buzzy {

  // Info about the available audio drivers
  ao_info* const* audioDrivers;

  // Number of available audio drivers
  int nbAudioDrivers;

  // ID of the default audio driver
  int idDefaultDriver;

  // ID of the current audio driver
  int idCurDriver;

  // Format of the audio sample
  ao_sample_format sampleFormat;

  // Output audio device
  ao_device* device;

} Buzzy;

typedef struct BuzzyNote {

  // Frequency
  double freq;

  // Amplitude in [0,1]
  double amp;

  // Start time in millisecond
  double start;

  // Duration in millisecond
  double delayMs;

  // Note shape
  BUZZY_NOTE_SHAPE;

} BuzzyNote;

// ================ Functions declaration ====================

// Create a static Buzzy structure
// There must be only one instance of Buzzy at a time
Buzzy BuzzyCreateStatic(void);

// Free the memory used by the static Buzzy 'that' and close the
// attached audio device if necessary
void BuzzyFreeStatic(Buzzy* that);

// Set the format of the audio sample
// 'nbBits' is the number of bits per sample, must be sizeof(typeof(sample))
// 'rate' is the number of samples per second per channel
// 'nbChannels' is the number of channels (1 for mono, 2 for stereo, ...)
void BuzzySetFormat(
  Buzzy* that,
     int nbBits,
     int rate,
     int nbChannels);

// Print the available audio drivers list on 'stream'
void BuzzyPrintAudioDrivers(
  const Buzzy* that,
         FILE* stream);

// Get the ID of the default audio driver
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetIdDefaultDriver(const Buzzy* that);

// Get the ID of the default audio driver
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetIdDefaultDriver(const Buzzy* that);

// Set the ID of the current audio driver of the Buzzy 'that' to 'id'
// No effect if id is invalid
#if BUILDMODE != 0
static inline
#endif
void BuzzySetIdCurDriver(
  Buzzy* that,
     int id);

// Get the ID of the current audio driver
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetIdCurDriver(const Buzzy* that);

// Get the number of audio drivers
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbAudioDriver(const Buzzy* that);

// Get the info about the audio drivers
#if BUILDMODE != 0
static inline
#endif
ao_info* const* BuzzyGetInfoAudioDriver(const Buzzy* that);

// Get the format of the audio sample
#if BUILDMODE != 0
static inline
#endif
ao_sample_format BuzzyGetFormat(const Buzzy* that);

// Get the number of bits of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbBits(const Buzzy* that);

// Get the rate (number of samples per second per channel) of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetRate(const Buzzy* that);

// Get the number of channels of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbChannels(const Buzzy* that);

// Open the device of the Buzzy 'that'
void BuzzyOpen(Buzzy* that);

// Close the device of the Buzzy 'that'
void BuzzyClose(Buzzy* that);

// Play a single flat note with frequency 'freq' during 'delayMs' microseconds
// on the Buzzy 'that'
void BuzzyPlaySingleFlatNote(
        Buzzy* that,
  unsigned int delayMs,
         float freq);

// Play a single linear decreasing note with frequency 'freq' during
// 'delayMs' microseconds on the Buzzy 'that'
void BuzzyPlaySingleLinerarDecreasingNote(
        Buzzy* that,
  unsigned int delayMs,
         float freq);

// Calculate the flat value of a sample for the BuzzyNote 'note' at
// time 'timeMs' for the Buzzy 'that' given the max amplitude 'ampMax'
// 'val' must be an array of 'that->nbChannels', the result values are
// stored in 'val'
void BuzzyFlatNote(
      Buzzy* that,
  BuzzyNote* note,
      double ampMax,
      double timeMs,
     double* val);

// Calculate the linearly fading value of a sample for the BuzzyNote 'note' at
// time 'timeMs' for the Buzzy 'that' given the max amplitude 'ampMax'
// 'vals' must be an array of 'that->nbChannels', the result values are
// stored in 'vals'
void BuzzyLinearFadingNote(
      Buzzy* that,
  BuzzyNote* note,
      double ampMax,
      double timeMs,
     double* vals);

// Play the GSet of BuzzyNote 'music' from time 'timeStartMs' to time
// 'timeEndMs' on the Buzzy 'that'
// The music is automatically scaled ot fit the maximum amplitude
void BuzzyPlayMusic(
  Buzzy* that,
   GSet* music,
   float timeStartMs,
   float timeEndMs);

// Play the whole range from BUZZY_C1 to BUZZY_B7 on the Buzzy 'that'
void BuzzyPlayWholeRange(Buzzy* that);

// Play the Star Wars thema song on the Buzzy 'that'
void BuzzyPlayStarWars(Buzzy* that);

// Return the maximum absolute amplitude of the GSet of BuzzyNote 'music'
// from time 'timeStartMs' to time 'timeEndMs' on the Buzzy 'that'
double BuzzyGetMaxValMusic(
  Buzzy* that,
   GSet* music,
   float timeStartMs,
   float timeEndMs);

// ================ inliner ====================

#if BUILDMODE != 0
#include "buzzy-inline.c"
#endif

#endif
