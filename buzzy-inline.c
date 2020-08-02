// *************** BUZZY-INLINE.C ***************

// ================ Functions implementation ====================

// Get the ID of the default audio driver
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetIdDefaultDriver(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->idDefaultDriver;

}

// Get the ID of the current audio driver
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetIdCurDriver(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->idCurDriver;

}

// Set the ID of the current audio driver of the Buzzy 'that' to 'id'
// No effect if id is invalid
#if BUILDMODE != 0
static inline
#endif
void BuzzySetIdCurDriver(
  Buzzy* that,
     int id) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  if (id >= 0 && id < BuzzyGetNbAudioDriver(that)) {

    that->idCurDriver = id;

  }

}

// Get the number of audio drivers
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbAudioDriver(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->nbAudioDrivers;

}

// Get the info about the audio drivers
#if BUILDMODE != 0
static inline
#endif
ao_info* const* BuzzyGetInfoAudioDriver(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->audioDrivers;

}

// Get the format of the audio sample
#if BUILDMODE != 0
static inline
#endif
ao_sample_format BuzzyGetFormat(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->sampleFormat;

}

// Get the number of bits of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbBits(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->sampleFormat.bits;

}

// Get the rate (number of samples per second per channel) of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetRate(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->sampleFormat.rate;

}

// Get the number of channels of the audio sample
#if BUILDMODE != 0
static inline
#endif
int BuzzyGetNbChannels(const Buzzy* that) {

#if BUILDMODE == 0

  if (that == NULL) {

    BuzzyErr->_type = PBErrTypeNullPointer;
    sprintf(
      BuzzyErr->_msg,
      "'that' is null");
    PBErrCatch(BuzzyErr);

  }

#endif

  return that->sampleFormat.channels;

}
