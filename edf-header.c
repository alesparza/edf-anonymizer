#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edf-header.h"

StaticHeader* initialiseStaticHeader() {
  StaticHeader* header = malloc(sizeof(StaticHeader));
  header->version = malloc(HEADER_VERSION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_VERSION_LENGTH);
  header->localPatientIdentification = malloc(HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH);
  header->localRecordingIdentification = malloc(HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH);
  header->startDate = malloc(HEADER_STARTDATE_RECORDING_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_STARTDATE_RECORDING_LENGTH);
  header->startTime = malloc(HEADER_STARTTIME_RECORDING_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_STARTTIME_RECORDING_LENGTH);
  header->totalBytes = malloc(HEADER_TOTAL_BYTES_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_TOTAL_BYTES_LENGTH);
  header->reserved = malloc(HEADER_RESERVED * sizeof(char));
  memset(header->version, ' ', HEADER_RESERVED);
  header->numDataRecords = malloc(HEADER_NUMBER_DATA_RECORDS_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_NUMBER_DATA_RECORDS_LENGTH);
  header->dataDuration = malloc(HEADER_DATA_DURATION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_DATA_DURATION_LENGTH);
  header->numSignals = malloc(HEADER_NUMBER_SIGNALS_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_NUMBER_SIGNALS_LENGTH);
  return header;
}

StaticHeader* freeStaticHeader(StaticHeader* staticHeader) {
  free(staticHeader->version);
  free(staticHeader->localPatientIdentification);
  free(staticHeader->localRecordingIdentification);
  free(staticHeader->startDate);
  free(staticHeader->startTime);
  free(staticHeader->totalBytes);
  free(staticHeader->reserved);
  free(staticHeader->numDataRecords);
  free(staticHeader->dataDuration);
  free(staticHeader->numSignals);

  return NULL;
}

