#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edf-header.h"

StaticHeader* initialiseStaticHeader() {
  StaticHeader* header = malloc(sizeof(StaticHeader));
  header->version = malloc(HEADER_VERSION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_VERSION_LENGTH);
  header->localPatientIdentification = malloc(HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->localPatientIdentification, ' ', HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH);
  header->localRecordingIdentification = malloc(HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->localRecordingIdentification, ' ', HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH);
  header->startDate = malloc(HEADER_STARTDATE_RECORDING_LENGTH * sizeof(char));
  memset(header->startDate, ' ', HEADER_STARTDATE_RECORDING_LENGTH);
  header->startTime = malloc(HEADER_STARTTIME_RECORDING_LENGTH * sizeof(char));
  memset(header->startTime, ' ', HEADER_STARTTIME_RECORDING_LENGTH);
  header->totalBytes = malloc(HEADER_TOTAL_BYTES_LENGTH * sizeof(char));
  memset(header->totalBytes, ' ', HEADER_TOTAL_BYTES_LENGTH);
  header->reserved = malloc(HEADER_RESERVED * sizeof(char));
  memset(header->reserved, ' ', HEADER_RESERVED);
  header->numDataRecords = malloc(HEADER_NUMBER_DATA_RECORDS_LENGTH * sizeof(char));
  memset(header->numDataRecords, ' ', HEADER_NUMBER_DATA_RECORDS_LENGTH);
  header->dataDuration = malloc(HEADER_DATA_DURATION_LENGTH * sizeof(char));
  memset(header->dataDuration, ' ', HEADER_DATA_DURATION_LENGTH);
  header->numSignals = malloc(HEADER_NUMBER_SIGNALS_LENGTH * sizeof(char));
  memset(header->numSignals, ' ', HEADER_NUMBER_SIGNALS_LENGTH);
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
  free(staticHeader);

  return NULL;
}

DynamicHeader* initialiseDynamicHeader() {
  DynamicHeader* header = malloc(sizeof(DynamicHeader));
  header->label = malloc(HEADER_VERSION_LENGTH * sizeof(char));
  memset(header->label, ' ', HEADER_VERSION_LENGTH);
  header->transducerType = malloc(HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->transducerType, ' ', HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH);
  header->physicalDimension = malloc(HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->physicalDimension, ' ', HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH);
  header->physicalMin = malloc(HEADER_STARTDATE_RECORDING_LENGTH * sizeof(char));
  memset(header->physicalMin, ' ', HEADER_STARTDATE_RECORDING_LENGTH);
  header->physicalMax = malloc(HEADER_STARTTIME_RECORDING_LENGTH * sizeof(char));
  memset(header->physicalMax, ' ', HEADER_STARTTIME_RECORDING_LENGTH);
  header->digitalMin = malloc(HEADER_TOTAL_BYTES_LENGTH * sizeof(char));
  memset(header->digitalMin, ' ', HEADER_TOTAL_BYTES_LENGTH);
  header->digitalMax = malloc(HEADER_RESERVED * sizeof(char));
  memset(header->digitalMax, ' ', HEADER_RESERVED);
  header->prefiltering = malloc(HEADER_NUMBER_DATA_RECORDS_LENGTH * sizeof(char));
  memset(header->prefiltering, ' ', HEADER_NUMBER_DATA_RECORDS_LENGTH);
  header->numSamples = malloc(HEADER_DATA_DURATION_LENGTH * sizeof(char));
  memset(header->numSamples, ' ', HEADER_DATA_DURATION_LENGTH);
  header->reserved = malloc(HEADER_NUMBER_SIGNALS_LENGTH * sizeof(char));
  memset(header->reserved, ' ', HEADER_NUMBER_SIGNALS_LENGTH);
  return header;
}

DynamicHeader* freeDynamicHeader(DynamicHeader* dynamicHeader) {
  free(dynamicHeader->label);
  free(dynamicHeader->transducerType);
  free(dynamicHeader->physicalDimension);
  free(dynamicHeader->physicalMin);
  free(dynamicHeader->physicalMax);
  free(dynamicHeader->digitalMin);
  free(dynamicHeader->digitalMax);
  free(dynamicHeader->prefiltering);
  free(dynamicHeader->numSamples);
  free(dynamicHeader->reserved);
  free(dynamicHeader);

  return NULL;
}

