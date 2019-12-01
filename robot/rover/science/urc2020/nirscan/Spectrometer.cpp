#include "Spectrometer.h"
#include "refCalMatrix.h"

#include <iostream>
#include <fstream>

using namespace std;

bool Spectrometer::init()
{
    activeConfiguration = NULL;
    if (USB_Init() != 0)
    {
        return false;
    }

    if (USB_Open() != 0)
    {
        return false;
    }

    NNO_SetHibernate(false);

    FetchRefCalData();
    FetchRefCalMatrix();
    return true;
}

void Spectrometer::deinit()
{

    USB_Close();
    USB_Exit();
}

int Spectrometer::scan(Spectrum &spectrum)
{
    uint8_t scanDatBlob[SCAN_DATA_BLOB_SIZE];
    uScanData *scanDat = (uScanData *)scanDatBlob;

    // fetchActiveConfig();

    if (runScan() != PASS)
    {
        return FAIL;
    }

    int realFileSize = fetchScan(scanDatBlob);

    scanResults results;
    scanResults refResults;
    dlpspec_scan_interpret(scanDatBlob, realFileSize, &results);
    dlpspec_scan_interpReference(refCalDataBlob, SCAN_DATA_BLOB_SIZE,
                                 refCalMatrixBlob, REF_CAL_MATRIX_BLOB_SIZE,
                                 &results, &refResults);

    dlpspec_scan_read_data(scanDatBlob, realFileSize);

    spectrum.dataSize = results.length;
    for (size_t i = 0; i < results.length; i++)
    {
        spectrum.wavelength[i] = refResults.wavelength[i];
        spectrum.reference[i] = refResults.intensity[i];
        spectrum.intensity[i] = results.intensity[i];
    }
    spectrum.startWavelength = results.cfg.section[0].wavelength_start_nm;
    spectrum.endWavelength = results.cfg.section[0].wavelength_end_nm;
    spectrum.repeats = results.cfg.head.num_repeats;
    spectrum.exposureTime = results.cfg.section[0].exposure_time;
    spectrum.resolution = results.cfg.section[0].width_px;

    spectrum.gain = scanDat->slew_data.pga;
    spectrum.detectorTemperature = scanDat->slew_data.detector_temp_hundredths / 100.0;
    spectrum.systemTemperature = scanDat->slew_data.system_temp_hundredths / 100.0;
    spectrum.relHumidity = scanDat->slew_data.humidity_hundredths / 100.0;
    spectrum.lampIntensity = scanDat->slew_data.lamp_pd;

    uint32 pVal;
    NNO_error_status_struct error_status;
    NNO_ReadDeviceStatus(&pVal);
    NNO_ReadErrorStatus(&error_status);

    cout << "Device status: " << pVal << endl
         << "Error status: " << error_status.status << endl
         << "Error code adc: " << (int)error_status.errorCodes.adc << endl
         << "Error code eeprom: " << (int)error_status.errorCodes.eeprom << endl
         << "Error code hdc: " << (int)error_status.errorCodes.hdc << endl
         << "Error code hw: " << (int)error_status.errorCodes.hw << endl
         << "Error code spec_lib: " << (int)error_status.errorCodes.spec_lib << endl
         << "Error code scan: " << (int)error_status.errorCodes.scan << endl
         << "Error code tmp: " << (int)error_status.errorCodes.tmp << endl
         << "Error code memory: " << (int)error_status.errorCodes.memory << endl;

    return PASS;
}

int Spectrometer::fetchScan(unsigned char *buffer)
{
    size_t fileSize = NNO_GetFileSizeToRead(NNO_FILE_SCAN_DATA);
    return NNO_GetFile(buffer, fileSize);
}

int Spectrometer::fetchActiveConfig()
{
    int activeIndex = NNO_GetActiveScanIndex();

    uint32 fileSize;
    int res = NNO_GetScanCfg(activeIndex, activeConfigurationBuffer, &fileSize);

    res = dlpspec_scan_read_configuration(activeConfigurationBuffer, fileSize);

    activeConfiguration = (uScanConfig *)activeConfigurationBuffer;

    if (activeConfiguration->slewScanCfg.head.scan_type != SLEW_TYPE)
    {
        cout << "Error: Wrong scan configuration type: " << (int)activeConfiguration->slewScanCfg.head.scan_type << "!" << endl;
        return FAIL;
    }

    cout << "Configuration:" << endl
         << "Active configuration: " << activeIndex << endl
         << "Config name: " << activeConfiguration->slewScanCfg.head.config_name << endl
         << "Scan type: " << (int)activeConfiguration->slewScanCfg.head.scan_type << endl
         << "Repeats: " << (int)activeConfiguration->slewScanCfg.head.num_repeats << endl
         << "Sections: " << (int)activeConfiguration->slewScanCfg.head.num_sections << endl
         << "Section[0]: " << endl
         << "startWavelength: " << (int)activeConfiguration->slewScanCfg.section[0].wavelength_start_nm << endl
         << "endWavelength: " << (int)activeConfiguration->slewScanCfg.section[0].wavelength_end_nm << endl
         << "exposureTime: " << (int)activeConfiguration->slewScanCfg.section[0].exposure_time << endl;

    return res;
}

int Spectrometer::runScan()
{
    unsigned int devStatus;

    NNO_SetScanNumRepeats(6);

    int scanTime = NNO_GetEstimatedScanTime();
    NNO_PerformScan(false);

    usleep(scanTime * 1000);

    int retries = 0;
    while (NNO_ReadDeviceStatus(&devStatus) == PASS && retries < 3)
    {
        if ((devStatus & NNO_STATUS_SCAN_IN_PROGRESS) != NNO_STATUS_SCAN_IN_PROGRESS)
            return PASS;
        usleep(500 * 1000);
        retries++;
    }
    return FAIL;
}

void *Spectrometer::GetRefCalMatrixBlob()
{
    refCalMatrix tmpRefCalMatrix;

    memcpy(tmpRefCalMatrix.width, refCalMatrix_widths, sizeof(uint8_t) * REF_CAL_INTERP_WIDTH);
    memcpy(tmpRefCalMatrix.wavelength, refCalMatrix_wavelengths, sizeof(double) * REF_CAL_INTERP_WAVELENGTH);
    memcpy(tmpRefCalMatrix.ref_lookup, refCalMatrix_intensities, sizeof(uint16_t) * REF_CAL_INTERP_WIDTH * REF_CAL_INTERP_WAVELENGTH);

    dlpspec_calib_write_ref_matrix(&tmpRefCalMatrix, refCalMatrixBlob, REF_CAL_MATRIX_BLOB_SIZE);

    return refCalMatrixBlob;
}

void *Spectrometer::GetRefCalDataBlob()
{
    return refCalDataBlob;
}

int Spectrometer::FetchRefCalData()
{
    int refCalSize = NNO_GetFileSizeToRead(NNO_FILE_REF_CAL_DATA);

    if (NNO_GetFile((unsigned char *)refCalDataBlob, refCalSize) == refCalSize)
        return PASS;
    else
        return FAIL;
}

int Spectrometer::FetchRefCalMatrix()
{
    int refCalSize = NNO_GetFileSizeToRead(NNO_FILE_REF_CAL_MATRIX);

    if (NNO_GetFile((unsigned char *)refCalMatrixBlob, refCalSize) == refCalSize)
        return PASS;
    else
        return FAIL;
}
