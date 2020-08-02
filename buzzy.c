// *************** BUZZY.C ***************

// ================= Include ==================
#include "buzzy.h"
#if BUILDMODE == 0
#include "buzzy-inline.c"
#endif

// Global variables
const double BUZZY_RANGE[49] = {

  BUZZY_C1,
  BUZZY_D1,
  BUZZY_E1,
  BUZZY_F1,
  BUZZY_G1,
  BUZZY_A1,
  BUZZY_B1,
  BUZZY_C2,
  BUZZY_D2,
  BUZZY_E2,
  BUZZY_F2,
  BUZZY_G2,
  BUZZY_A2,
  BUZZY_B2,
  BUZZY_C3,
  BUZZY_D3,
  BUZZY_E3,
  BUZZY_F3,
  BUZZY_G3,
  BUZZY_A3,
  BUZZY_B3,
  BUZZY_C4,
  BUZZY_D4,
  BUZZY_E4,
  BUZZY_F4,
  BUZZY_G4,
  BUZZY_A4,
  BUZZY_B4,
  BUZZY_C5,
  BUZZY_D5,
  BUZZY_E5,
  BUZZY_F5,
  BUZZY_G5,
  BUZZY_A5,
  BUZZY_B5,
  BUZZY_C6,
  BUZZY_D6,
  BUZZY_E6,
  BUZZY_F6,
  BUZZY_G6,
  BUZZY_A6,
  BUZZY_B6,
  BUZZY_C7,
  BUZZY_D7,
  BUZZY_E7,
  BUZZY_F7,
  BUZZY_G7,
  BUZZY_A7,
  BUZZY_B7

};

// ================ Functions implementation ==================

// Create a static Buzzy structure
// There must be only one instance of Buzzy at a time
Buzzy BuzzyCreateStatic(void) {

  // Declare the new Buzzy
  Buzzy that;

  // Initialize the libao
  ao_initialize();

  // Get the list of available audio drivers
  that.audioDrivers = ao_driver_info_list(&(that.nbAudioDrivers));

  // Get the id of the default driver and initialize the current driver
  that.idDefaultDriver = ao_default_driver_id();
  that.idCurDriver = that.idDefaultDriver;

  // Initialise the audio sample format
  memset(
    &(that.sampleFormat),
    0,
    sizeof(ao_sample_format));
  that.sampleFormat.byte_format =
    (ao_is_big_endian() ? AO_FMT_BIG : AO_FMT_LITTLE);

  // Initialise the device
  that.device = NULL;

  // Return the new Buzzy
  return that;

}

// Free the memory used by the static Buzzy 'that' and close the
// attached audio device if necessary
void BuzzyFreeStatic(Buzzy* that) {

  if (that == NULL) {

    return;

  }

  // Make sur the device is closed
  BuzzyClose(that);

  // Shutdown the libao
  ao_shutdown();

}

// Set the format of the audio sample
// 'nbBits' is the number of bits per sample, must be sizeof(typeof(sample))
// 'rate' is the number of samples per second per channel
// 'nbChannels' is the number of channels (1 for mono, 2 for stereo, ...)
void BuzzySetFormat(
  Buzzy* that,
     int nbBits,
     int rate,
     int nbChannels) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Set the sample's format
  that->sampleFormat.bits = nbBits;
  that->sampleFormat.rate = rate;
  that->sampleFormat.channels = nbChannels;

}

// Print the available audio drivers list on 'stream'
void BuzzyPrintAudioDrivers(
  const Buzzy* that,
         FILE* stream) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

  if (stream == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'stream' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Loop on the audio drivers
  for (
    int i = 0;
    i < BuzzyGetNbAudioDriver(that);
    ++i) {

    fprintf(
      stream,
      "audio driver #%d : %s\n",
      i,
      that->audioDrivers[i]->name);

  }

}

// Open the device of the Buzzy 'that'
void BuzzyOpen(Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Make sure the device is closed
  BuzzyClose(that);

  // Open the device with the current format
  that->device =
    ao_open_live(
      that->idCurDriver,
      &(that->sampleFormat),
      NULL);

  if (that->device == NULL) {

    BuzzyErr->_type = PBErrTypeRuntimeError;
    sprintf(
      BuzzyErr->_msg,
      "ao_open_live failed for %s",
      that->audioDrivers[that->idCurDriver]->name);
    BuzzyErr->_fatal = false;
    PBErrCatch(BuzzyErr);
    BuzzyErr->_fatal = true;

  }

}

// Close the device of the Buzzy 'that'
void BuzzyClose(Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  if (that->device != NULL) {

    ao_close(that->device);
    that->device = NULL;

  }

}

// Calculate the flat value of a sample for the BuzzyNote 'note' at
// time 'timeMs' for the Buzzy 'that' given the max amplitude 'ampMax'
// 'vals' must be an array of 'that->nbChannels', the result values are
// stored in 'vals'
void BuzzyFlatNote(
      Buzzy* that,
  BuzzyNote* note,
      double ampMax,
      double timeMs,
     double* vals) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

  if (note == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'note' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Get the relative time
  double tNote = timeMs - note->start;

  // Loop on the channels
  for (
    int iChannel = BuzzyGetNbChannels(that);
    iChannel--;) {

    // If the time is inside the note interval
    if (
      tNote >= 0.0 &&
      tNote <= note->delayMs) {

      // Calculate the value
      vals[iChannel] +=
        ampMax * note->amp *
        sin(6.28318 * note->freq * tNote / 1000.0);

    }

  }

}

// Calculate the linearly fading value of a sample for the BuzzyNote 'note' at
// time 'timeMs' for the Buzzy 'that' given the max amplitude 'ampMax'
// 'vals' must be an array of 'that->nbChannels', the result values are
// stored in 'vals'
void BuzzyLinearFadingNote(
      Buzzy* that,
  BuzzyNote* note,
      double ampMax,
      double timeMs,
     double* vals) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

  if (note == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'note' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Get the relative time
  double tNote = timeMs - note->start;

  // Loop on the channels
  for (
    int iChannel = BuzzyGetNbChannels(that);
    iChannel--;) {

    // If the time is inside the note interval
    if (
      tNote >= 0 &&
      tNote <= note->delayMs) {

      // Calculate the fading value
      double fade = 1.0 - tNote / note->delayMs;

      // Calculate the value
      vals[iChannel] +=
        ampMax * note->amp * fade *
        sin(6.28318 * note->freq * tNote / 1000.0);

    }

  }

}

// Play a single flat note with frequency 'freq' during 'delayMs' microseconds
// on the Buzzy 'that'
void BuzzyPlaySingleFlatNote(
        Buzzy* that,
  unsigned int delayMs,
         float freq) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Create the note
  BuzzyNote note = {

    .amp = 1.0,
    .start = 0.0,
    .delayMs = delayMs,
    .freq = freq,
    .noteShape = BuzzyFlatNote

  };

  // Create the music
  GSet music = GSetCreateStatic();
  GSetAppend(
    &music,
    &note);

  // Play the music
  BuzzyPlayMusic(
    that,
    &music,
    0.0,
    delayMs);

  // Free memory
  GSetFlush(&music);

}

// Play a single linear decreasing note with frequency 'freq' during
// 'delayMs' microseconds on the Buzzy 'that'
void BuzzyPlaySingleLinerarDecreasingNote(
        Buzzy* that,
  unsigned int delayMs,
         float freq) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Create the note
  BuzzyNote note = {

    .amp = 1.0,
    .start = 0.0,
    .delayMs = delayMs,
    .freq = freq,
    .noteShape = BuzzyLinearFadingNote

  };

  // Create the music
  GSet music = GSetCreateStatic();
  GSetAppend(
    &music,
    &note);

  // Play the music
  BuzzyPlayMusic(
    that,
    &music,
    0.0,
    delayMs);

  // Free memory
  GSetFlush(&music);

}

// Return the maximum absolute amplitude of the GSet of BuzzyNote 'music'
// from time 'timeStartMs' to time 'timeEndMs' on the Buzzy 'that'
double BuzzyGetMaxValMusic(
  Buzzy* that,
   GSet* music,
   float timeStartMs,
   float timeEndMs) {

  // Declare the result amplitude
  double maxVal = 0.0;

  // Get the size of the sample buffer
  double nb =
    (double)BuzzyGetRate(that) *
    (timeEndMs - timeStartMs) / 1000.0;
  size_t nbSamples = (size_t)floor(nb);

  // Calculate the max amplitude of a sample
  double maxAmp = 0.5 *
    pow(
      2.0,
      (double)BuzzyGetNbBits(that));

  // Allocate memory to calculate the value of the samples
  double* vals =
    PBErrMalloc(
      BuzzyErr,
      sizeof(double) * BuzzyGetNbChannels(that));

  // Loop on the sample
  for (
    size_t iSample = 0;
    iSample < nbSamples;
    ++iSample) {

    // Get the time in millisecond of the sample
    double tSample =
      timeStartMs + 1000.0 * ((double)iSample / (double)BuzzyGetRate(that));

    // Reset the sample values
    for (
      int iChannel = BuzzyGetNbChannels(that);
      iChannel--;) {

      vals[iChannel] = 0.0;

    }

    // Loop on the note of the music
    GSetIterForward iter = GSetIterForwardCreateStatic(music);

    do {

      // Get the note
      BuzzyNote* note = GSetIterGet(&iter);

      // Add the value of the sample for this note
      note->noteShape(
        that,
        note,
        maxAmp,
        tSample,
        vals);

    } while (GSetIterStep(&iter));

    // Loop on the channels
    for (
      int iChannel = BuzzyGetNbChannels(that);
      iChannel--;) {

      if (fabs(vals[iChannel]) > maxVal) {

        maxVal = fabs(vals[iChannel]);

      }

    }

  }

  // Free memory
  free(vals);

  // Return the result amplitude
  return maxVal;

}

// Play the GSet of BuzzyNote 'music' from time 'timeStartMs' to time
// 'timeEndMs' on the Buzzy 'that'
// The music is automatically scaled ot fit the maximum amplitude
void BuzzyPlayMusic(
  Buzzy* that,
   GSet* music,
   float timeStartMs,
   float timeEndMs) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

  if (music == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'music' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Get the size of the sample buffer
  double nb =
    (double)BuzzyGetRate(that) *
    (timeEndMs - timeStartMs) / 1000.0;
  size_t nbSamples = (size_t)floor(nb);
  size_t nbBytes = BuzzyGetNbBits(that) / 8;
  size_t bufferSize =
    nbBytes *
    BuzzyGetNbChannels(that) *
    nbSamples;

  // Allocate memory for the sample buffer
  char* samples =
    PBErrMalloc(
      BuzzyErr,
      bufferSize * nbBytes);

  // Calculate the max amplitude of a sample
  double maxAmp = 0.5 *
    pow(
      2.0,
      (double)BuzzyGetNbBits(that));

  // Allocate memory to calculate the value of the samples
  double* vals =
    PBErrMalloc(
      BuzzyErr,
      sizeof(double) * BuzzyGetNbChannels(that));

  // Get the scale coefficient of the music to avoid overflow
  double maxVal =
    BuzzyGetMaxValMusic(
      that,
      music,
      timeStartMs,
      timeEndMs);
  double scaleAmp = maxAmp / maxVal;

  // Loop on the sample
  for (
    size_t iSample = 0;
    iSample < nbSamples;
    ++iSample) {

    // Get the time in millisecond of the sample
    double tSample =
      timeStartMs + 1000.0 * ((double)iSample / (double)BuzzyGetRate(that));

    // Reset the sample values
    for (
      int iChannel = BuzzyGetNbChannels(that);
      iChannel--;) {

      vals[iChannel] = 0.0;

    }

    // Loop on the note of the music
    GSetIterForward iter = GSetIterForwardCreateStatic(music);

    do {

      // Get the note
      BuzzyNote* note = GSetIterGet(&iter);

      // Add the value of the sample for this note
      note->noteShape(
        that,
        note,
        maxAmp * scaleAmp,
        tSample,
        vals);

    } while (GSetIterStep(&iter));

    // Loop on the channels
    for (
      int iChannel = BuzzyGetNbChannels(that);
      iChannel--;) {

      uint_8 sampleVal8 = (uint_8)floor(vals[iChannel]);
      uint_16 sampleVal16 = (uint_16)floor(vals[iChannel]);
      uint_32 sampleVal32 = (uint_32)floor(vals[iChannel]);

      // Get the offset of the sample in the buffer
      size_t offsetSample =
        iSample * (BuzzyGetNbChannels(that) * nbBytes) +
        iChannel * nbBytes;

      // Loop on the bytes of the sample
      for (
        size_t iByte = nbBytes;
        iByte--;) {

        // Write the byte in the buffer
        switch (nbBytes) {

          case 1:
            samples[offsetSample + iByte] =
              (sampleVal8 >> (iByte * 8)) & 0xff;
            break;

          case 2:
            samples[offsetSample + iByte] =
              (sampleVal16 >> (iByte * 8)) & 0xff;
            break;

          case 4:
            samples[offsetSample + iByte] =
              (sampleVal32 >> (iByte * 8)) & 0xff;
            break;

          default:
            break;

        }

      }

    }

  }

  // Play the sample
  ao_play(
    that->device,
    samples,
    bufferSize);

  // Free memory
  free(samples);
  free(vals);

}

// Play the whole range from BUZZY_C1 to BUZZY_B7 on the Buzzy 'that'
void BuzzyPlayWholeRange(Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Create the music
  GSet music = GSetCreateStatic();

  // Loop on the note of the range
  for (
    int iNote = 0;
    iNote < 49;
    ++iNote) {

    // Create the note
    BuzzyNote* note =
      PBErrMalloc(
        BuzzyErr,
        sizeof(BuzzyNote));
    *note = (BuzzyNote) {

      .amp = 1.0,
      .start = (double)iNote * 500.0,
      .delayMs = 750.0,
      .freq = BUZZY_RANGE[iNote],
      .noteShape = BuzzyLinearFadingNote

    };

    // Add the note to the music
    GSetAppend(
      &music,
      note);

  }

  // Play the music
  BuzzyPlayMusic(
    that,
    &music,
    0.0,
    50000.0);

  // Free memory
  while (GSetNbElem(&music) > 0) {

    BuzzyNote* note = GSetPop(&music);
    free(note);

  }

}

// Play the Star Wars thema song on the Buzzy 'that'
void BuzzyPlayStarWars(Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  // Create the music
  GSet music = GSetCreateStatic();

  // Create the notes
  BuzzyNote notes[16];

  notes[0].start = 0.0;
  notes[0].delayMs = 1000.0;
  notes[0].freq = BUZZY_G3;
  notes[1].start = notes[0].start + notes[0].delayMs * 0.75;
  notes[1].delayMs = 1000.0;
  notes[1].freq = BUZZY_D4;
  notes[2].start = notes[1].start + notes[1].delayMs * 0.75;
  notes[2].delayMs = 166.5;
  notes[2].freq = BUZZY_C4;
  notes[3].start = notes[2].start + notes[2].delayMs * 0.75;
  notes[3].delayMs = 166.5;
  notes[3].freq = BUZZY_B3;
  notes[4].start = notes[3].start + notes[3].delayMs * 0.75;
  notes[4].delayMs = 166.5;
  notes[4].freq = BUZZY_A3;
  notes[5].start = notes[4].start + notes[4].delayMs * 0.75;
  notes[5].delayMs = 1000.0;
  notes[5].freq = BUZZY_G4;
  notes[6].start = notes[5].start + notes[5].delayMs * 0.75;
  notes[6].delayMs = 500.0;
  notes[6].freq = BUZZY_D4;
  notes[7].start = notes[6].start + notes[6].delayMs * 0.75;
  notes[7].delayMs = 166.5;
  notes[7].freq = BUZZY_C4;
  notes[8].start = notes[7].start + notes[7].delayMs * 0.75;
  notes[8].delayMs = 166.5;
  notes[8].freq = BUZZY_B3;
  notes[9].start = notes[8].start + notes[8].delayMs * 0.75;
  notes[9].delayMs = 166.5;
  notes[9].freq = BUZZY_A3;
  notes[10].start = notes[9].start + notes[9].delayMs * 0.75;
  notes[10].delayMs = 1000.0;
  notes[10].freq = BUZZY_G4;
  notes[11].start = notes[10].start + notes[10].delayMs * 0.75;
  notes[11].delayMs = 500.0;
  notes[11].freq = BUZZY_D4;
  notes[12].start = notes[11].start + notes[11].delayMs * 0.75;
  notes[12].delayMs = 166.5;
  notes[12].freq = BUZZY_C4;
  notes[13].start = notes[12].start + notes[12].delayMs * 0.75;
  notes[13].delayMs = 166.5;
  notes[13].freq = BUZZY_B3;
  notes[14].start = notes[13].start + notes[13].delayMs * 0.75;
  notes[14].delayMs = 166.5;
  notes[14].freq = BUZZY_C4;
  notes[15].start = notes[14].start + notes[14].delayMs * 0.75;
  notes[15].delayMs = 1000.0;
  notes[15].freq = BUZZY_A3;

  for (
    int iNote = 0;
    iNote < 16;
    ++iNote) {

    notes[iNote].amp = 1.0;
    notes[iNote].noteShape = BuzzyLinearFadingNote;
    GSetAppend(
      &music,
      notes + iNote);

  }

  // Play the music
  BuzzyPlayMusic(
    that,
    &music,
    0.0,
    notes[15].start + notes[15].delayMs);

  // Free memory
  GSetFlush(&music);

}
