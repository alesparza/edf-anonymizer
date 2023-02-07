
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edf-header.h"

StaticHeader* initialiseStaticHeader() {
  StaticHeader* header = malloc(sizeof(StaticHeader));
  header->version = malloc(HEADER_VERSION_LENGTH * sizeof(char));
  memset(header->version, ' ', HEADER_VERSION_LENGTH * sizeof(char));

  header->localPatientIdentification = malloc(HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->localPatientIdentification, ' ', HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH * sizeof(char));
  
  header->localRecordingIdentification = malloc(HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH * sizeof(char));
  memset(header->localRecordingIdentification, ' ', HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH * sizeof(char));
  
  header->startDate = malloc(HEADER_STARTDATE_RECORDING_LENGTH * sizeof(char));
  memset(header->startDate, ' ', HEADER_STARTDATE_RECORDING_LENGTH * sizeof(char));
  
  header->startTime = malloc(HEADER_STARTTIME_RECORDING_LENGTH * sizeof(char));
  memset(header->startTime, ' ', HEADER_STARTTIME_RECORDING_LENGTH * sizeof(char));
  
  header->totalBytes = malloc(HEADER_TOTAL_BYTES_LENGTH * sizeof(char));
  memset(header->totalBytes, ' ', HEADER_TOTAL_BYTES_LENGTH * sizeof(char));
  
  header->reserved = malloc(HEADER_RESERVED * sizeof(char));
  memset(header->reserved, ' ', HEADER_RESERVED * sizeof(char));
  
  header->numDataRecords = malloc(HEADER_NUMBER_DATA_RECORDS_LENGTH * sizeof(char));
  memset(header->numDataRecords, ' ', HEADER_NUMBER_DATA_RECORDS_LENGTH * sizeof(char));
  
  header->dataDuration = malloc(HEADER_DATA_DURATION_LENGTH * sizeof(char));
  memset(header->dataDuration, ' ', HEADER_DATA_DURATION_LENGTH * sizeof(char));
  
  header->numSignals = malloc(HEADER_NUMBER_SIGNALS_LENGTH * sizeof(char));
  memset(header->numSignals, ' ', HEADER_NUMBER_SIGNALS_LENGTH * sizeof(char));
  
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

DynamicHeader* initialiseDynamicHeader(int signalCount) {
  DynamicHeader* header = malloc(sizeof(DynamicHeader));
  header->label = malloc(HEADER_SIGNAL_LABEL_LENGTH * sizeof(char) * signalCount);
  memset(header->label, ' ', HEADER_SIGNAL_LABEL_LENGTH * sizeof(char) * signalCount);
  
  header->transducerType = malloc(HEADER_SIGNAL_TRANSUDER_TYPE_LENGTH * sizeof(char) * signalCount);
  memset(header->transducerType, ' ', HEADER_SIGNAL_TRANSUDER_TYPE_LENGTH * sizeof(char) * signalCount);
  
  header->physicalDimension = malloc(HEADER_SIGNAL_PHYSICAL_DIMENSION_LENGTH * sizeof(char) * signalCount);
  memset(header->physicalDimension, ' ', HEADER_SIGNAL_PHYSICAL_DIMENSION_LENGTH * sizeof(char) * signalCount);
  
  header->physicalMin = malloc(HEADER_SIGNAL_PHYSICAL_MINIMUM_LENGTH * sizeof(char) * signalCount);
  memset(header->physicalMin, ' ', HEADER_SIGNAL_PHYSICAL_MINIMUM_LENGTH * sizeof(char) * signalCount);
  
  header->physicalMax = malloc(HEADER_SIGNAL_PHYSICAL_MAXIMUM_LENGTH * sizeof(char) * signalCount);
  memset(header->physicalMax, ' ', HEADER_SIGNAL_PHYSICAL_MAXIMUM_LENGTH * sizeof(char) * signalCount);
  
  header->digitalMin = malloc(HEADER_SIGNAL_DIGITAL_MINIMUM_LENGTH * sizeof(char) * signalCount);
  memset(header->digitalMin, ' ', HEADER_SIGNAL_DIGITAL_MINIMUM_LENGTH * sizeof(char) * signalCount);
  
  header->digitalMax = malloc(HEADER_SIGNAL_DIGITAL_MAXIMUM_LENGTH * sizeof(char) * signalCount);
  memset(header->digitalMax, ' ', HEADER_SIGNAL_DIGITAL_MAXIMUM_LENGTH * sizeof(char) * signalCount);
  
  header->prefiltering = malloc(HEADER_SIGNAL_PREFILTERING_LENGTH * sizeof(char) * signalCount);
  memset(header->prefiltering, ' ', HEADER_SIGNAL_PREFILTERING_LENGTH * sizeof(char) * signalCount);
  
  header->numSamples = malloc(HEADER_SIGNAL_NUMBER_SAMPLES_LENGTH * sizeof(char) * signalCount);
  memset(header->numSamples, ' ', HEADER_SIGNAL_NUMBER_SAMPLES_LENGTH * sizeof(char) * signalCount);
  
  header->reserved = malloc(HEADER_SIGNAL_RESERVED * sizeof(char) * signalCount);
  memset(header->reserved, ' ', HEADER_SIGNAL_RESERVED * sizeof(char) * signalCount);
  
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

