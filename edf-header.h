#ifndef EDFHEADER_H
  #define EDFHEADER_H

  // static header lengths
  #define HEADER_ROWS 16
  #define HEADER_VERSION_LENGTH 8
  #define HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH 80
  #define HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH 80
  #define HEADER_STARTDATE_RECORDING_LENGTH 8
  #define HEADER_STARTTIME_RECORDING_LENGTH 8
  #define HEADER_TOTAL_BYTES_LENGTH 8
  #define HEADER_RESERVED 44
  #define HEADER_NUMBER_DATA_RECORDS_LENGTH 8
  #define HEADER_DATA_DURATION_LENGTH 8
  #define HEADER_NUMBER_SIGNALS_LENGTH 4

  typedef struct STATIC_HEADER_STRUCT {
    char* version;
    char* localPatientIdentification;
    char* localRecordingIdentification;
    char* startDate;
    char* startTime;
    char* totalBytes;
    char* reserved;
    char* numDataRecords;
    char* dataDuration;
    char* numSignals;
  } StaticHeader;

  // dynamic header lengths
  #define HEADER_SIGNAL_LABEL_LENGTH 16
  #define HEADER_SIGNAL_TRANSUDER_TYPE_LENGTH 80
  #define HEADER_SIGNAL_PHYSICAL_DIMENSION_LENGTH 8
  #define HEADER_SIGNAL_PHYSICAL_MINIMUM_LENGTH 8
  #define HEADER_SIGNAL_PHYSICAL_MAXIMUM_LENGTH 8
  #define HEADER_SIGNAL_DIGITAL_MINIMUM_LENGTH 8
  #define HEADER_SIGNAL_DIGITAL_MAXIMUM_LENGTH 8
  #define HEADER_SIGNAL_PREFILTERING_LENGTH 80
  #define HEADER_SIGNAL_NUMBER_SAMPLES_LENGTH 8
  #define HEADER_SIGNAL_RESERVED 32

  typedef struct DYNAMIC_HEADER_STRUCT {
    char* label;
    char* transducerType;
    char* physicalDimention;
    char* physicalMin;
    char* physicalMax;
    char* digitalMin;
    char* digitalMax;
    char* prefiltering;
    char* numSamples;
    char* reserved;
  } DynamicHeader;

  // functions

  /**
  * Initialise the static header.
  * Each field is initialised with spaces for the length of the field.
  */
  StaticHeader* initialiseStaticHeader();

  /**
  * Frees all the data in the static header.
  */
  StaticHeader* freeStaticHeader(StaticHeader* staticHeader);

#endif /* EDFHEADER_H */

