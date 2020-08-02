#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "pberr.h"
#include "buzzy.h"

void UnitTestBuzzyCreateFree() {

  Buzzy buzz = BuzzyCreateStatic();
  if (
    buzz.audioDrivers == NULL ||
    buzz.idDefaultDriver != buzz.idCurDriver ||
    buzz.device != NULL) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyCreateStatic failed");
    PBErrCatch(BuzzyErr);

  }

  BuzzyFreeStatic(&buzz);

  printf("UnitTestBuzzyCreateFree OK\n");

}

void UnitTestBuzzyGetSet() {

  Buzzy buzz = BuzzyCreateStatic();
  ao_sample_format format = BuzzyGetFormat(&buzz);
  int retcmp =
    memcmp(
      &format,
      &(buzz.sampleFormat),
      sizeof(ao_sample_format));
  if (retcmp != 0) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetFormat failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetIdCurDriver(&buzz) != buzz.idCurDriver) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetIdCurDriver failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetIdDefaultDriver(&buzz) != buzz.idDefaultDriver) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetIdDefaultDriver failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetInfoAudioDriver(&buzz) != buzz.audioDrivers) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetInfoAudioDriver failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetNbAudioDriver(&buzz) != buzz.nbAudioDrivers) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetNbAudioDriver failed");
    PBErrCatch(BuzzyErr);

  }

  BuzzySetFormat(
    &buzz,
    16,
    44100,
    2);
  if (
    buzz.sampleFormat.bits != 16 ||
    buzz.sampleFormat.rate != 44100 ||
    buzz.sampleFormat.channels != 2) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzySetFormat failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetNbBits(&buzz) != buzz.sampleFormat.bits) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetNbBits failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetRate(&buzz) != buzz.sampleFormat.rate) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetRate failed");
    PBErrCatch(BuzzyErr);

  }

  if (BuzzyGetNbChannels(&buzz) != buzz.sampleFormat.channels) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzyGetNbChannels failed");
    PBErrCatch(BuzzyErr);

  }

  BuzzySetIdCurDriver(
    &buzz,
    1);
  if (BuzzyGetIdCurDriver(&buzz) != 1) {

    BuzzyErr->_type = PBErrTypeUnitTestFailed;
    sprintf(
      BuzzyErr->_msg,
      "BuzzySetIdCurDriver failed");
    PBErrCatch(BuzzyErr);

  }

  BuzzyFreeStatic(&buzz);

  printf("UnitTestBuzzyGetSet OK\n");

}

void UnitTestBuzzyPlayNote() {

  Buzzy buzz = BuzzyCreateStatic();
  BuzzySetFormat(
    &buzz,
    16,
    44100,
    2);
  BuzzyOpen(&buzz);
  printf("BuzzyPlaySingleFlatNote\n");
  BuzzyPlaySingleFlatNote(
    &buzz,
    1000,
    BUZZY_A4);
  printf("BuzzyPlaySingleLinerarDecreasingNote\n");
  BuzzyPlaySingleLinerarDecreasingNote(
    &buzz,
    1000,
    BUZZY_A3);
  printf("BuzzyPlayWholeRange\n");
  BuzzyPlayWholeRange(&buzz);
  printf("BuzzyPlayStarWars\n");
  BuzzyPlayStarWars(&buzz);
  BuzzyClose(&buzz);
  BuzzyFreeStatic(&buzz);
  printf("UnitTestBuzzyPlayNote OK\n");

}

void UnitTestAll() {

  UnitTestBuzzyCreateFree();
  UnitTestBuzzyGetSet();
  UnitTestBuzzyPlayNote();
  printf("UnitTestAll OK\n");

}

int main() {

  UnitTestAll();

  // Return success code
  return 0;

}
