#ifndef _SPECTROMETER_H_
#define _SPECTROMETER_H_

#include <unistd.h>
#include <string>

#include "API.h"
#include "usb.h"
#include <dlpspec/dlpspec_scan_col.h>

struct Spectrum
{
  std::string title;
  std::string comment;
  std::string isoDate;

  double detectorTemperature;
  double systemTemperature;
  double relHumidity;
  double lampIntensity;

  double resolution;
  double exposureTime;
  int gain;
  int repeats;

  int startWavelength;
  int endWavelength;

  size_t dataSize;
  double wavelength[ADC_DATA_LEN];
  int intensity[ADC_DATA_LEN];
  int reference[ADC_DATA_LEN];
};

class Spectrometer
{
public:
  bool init();
  void deinit();

  int scan(Spectrum &spectrum);

private:
  int runScan();
  int fetchActiveConfig();
  int fetchScan(unsigned char *buffer);
  int interpretScan(unsigned char *buffer, int size, scanResults *results);
  int interpretReference(scanResults *results, scanResults *referenceResults);

  void *GetRefCalMatrixBlob();
  void *GetRefCalDataBlob();
  int FetchRefCalData();
  int FetchRefCalMatrix();

  uint8_t refCalMatrixBlob[REF_CAL_MATRIX_BLOB_SIZE];
  uint8_t refCalDataBlob[SCAN_DATA_BLOB_SIZE];

  uint8_t activeConfigurationBuffer[SCAN_DATA_BLOB_SIZE];
  uScanConfig *activeConfiguration;
};

#endif // _SPECTROMETER_H_
