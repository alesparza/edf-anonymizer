
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
  #define HEADER_LENGTH HEADER_VERSION \\
          + HEADER_LOCAL_PATIENT_IDENTIFICATION_LENGTH \\
          + HEADER_LOCAL_RECORDING_IDENTIFICATION_LENGTH \\
          + HEADER_STARTDATE_RECORDING_LENGTH \\
          + HEADER_STARTTIME_RECORDING_LENGTH \\
          + HEADER_TOTAL_BYTES_LENGTH \\
          + HEADER_RESERVED \\
          + HEADER_NUMBER_DATA_RECORDS_LENGTH \\
          + HEADER_DATA_DURATION_LENGTH \\
          + HEADER_NUMBER_SIGNALS_LENGTH

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
  #define HEADER_SIGNAL_LENGTH HEADER_SIGNAL_LABEL_LENGTH \\
          + HEADER_SIGNAL_TRANSUDER_TYPE_LENGTH \\
          + HEADER_SIGNAL_PHYSICAL_DIMENSION_LENGTH \\
          + HEADER_SIGNAL_PHYSICAL_MINIMUM_LENGTH \\
          + HEADER_SIGNAL_PHYSICAL_MAXIMUM_LENGTH \\
          + HEADER_SIGNAL_DIGITAL_MINIMUM_LENGTH \\
          + HEADER_SIGNAL_DIGITAL_MAXIMUM_LENGTH \\
          + HEADER_SIGNAL_PREFILTERING_LENGTH \\
          + HEADER_SIGNAL_NUMBER_SAMPLES_LENGTH \\
          + HEADER_SIGNAL_RESERVED

  typedef struct DYNAMIC_HEADER_STRUCT {
    char* label;
    char* transducerType;
    char* physicalDimension;
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
  * It is "static" becasue the size is always 256 bytes.
  * Each field is initialised with spaces for the length of the field.
  */
  StaticHeader* initialiseStaticHeader();

  /**
  * Frees all the data in the static header.
  */
  StaticHeader* freeStaticHeader(StaticHeader* staticHeader);

  /**
  * Initialise the dynamic header.
  * It is "dynamic" because the size changes depending on how many signals exist in the file.
  * Each field is initialised with spaces for the length of the field.
  */
  DynamicHeader* initialiseDynamicHeader(int signalCount);

  /**
  * Frees all the data in the static header.
  */
  DynamicHeader* freeDynamicHeader(DynamicHeader* dynamicHeader);

#endif /* EDFHEADER_H */

