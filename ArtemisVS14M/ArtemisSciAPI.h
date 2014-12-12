/****************************************
 * ArtemisSciAPI.h
 *
 * This file is autogenerated.
 *
 ****************************************/

//#pragma once



#include <comdef.h>

#ifndef _ARTEMISSCIAPI_H_
#define _ARTEMISSCIAPI_H_
//////////////////////////////////////////////////////////////////////////
//
// Interface functions for Artemis CCD Camera Library
//


//Error codes

enum ARTEMISERROR
{
	ARTEMIS_OK = 0,
	ARTEMIS_INVALID_PARAMETER,
	ARTEMIS_NOT_CONNECTED,
	ARTEMIS_NOT_IMPLEMENTED,
	ARTEMIS_NO_RESPONSE,
	ARTEMIS_INVALID_FUNCTION,
	ARTEMIS_NOT_INITIALIZED,
	ARTEMIS_OPERATION_FAILED,
};

// Colour properties
enum ARTEMISCOLOURTYPE
{
	ARTEMIS_COLOUR_UNKNOWN = 0,
	ARTEMIS_COLOUR_NONE,
	ARTEMIS_COLOUR_RGGB
};

//Other enumeration types
enum ARTEMISPRECHARGEMODE
{
	PRECHARGE_NONE = 0,		// Precharge ignored
	PRECHARGE_ICPS,			// In-camera precharge subtraction
	PRECHARGE_FULL,			// Precharge sent with image data
};

// Camera State
enum ARTEMISCAMERASTATE
{
	CAMERA_ERROR = -1,
	CAMERA_IDLE = 0,
	CAMERA_WAITING,
	CAMERA_EXPOSING,
	CAMERA_READING,
	CAMERA_DOWNLOADING,
	CAMERA_FLUSHING,
};

// Parameters for ArtemisSendMessage
enum ARTEMISSENDMSG
{
	ARTEMIS_LE_LOW				=0,
	ARTEMIS_LE_HIGH				=1,
	ARTEMIS_GUIDE_NORTH			=10,
	ARTEMIS_GUIDE_SOUTH			=11,
	ARTEMIS_GUIDE_EAST			=12,
	ARTEMIS_GUIDE_WEST			=13,
	ARTEMIS_GUIDE_STOP			=14,
};

// Parameters for ArtemisGet/SetProcessing
// These must be powers of 2.
enum ARTEMISPROCESSING
{
	ARTEMIS_PROCESS_LINEARISE	=1,	// compensate for JFET nonlinearity
	ARTEMIS_PROCESS_VBE			=2, // adjust for 'Venetian Blind effect'
};

// Parameters for ArtemisSetUpADC
enum ARTEMISSETUPADC
{
	ARTEMIS_SETUPADC_MODE		=0,
	ARTEMIS_SETUPADC_OFFSETR	=(1<<10),
	ARTEMIS_SETUPADC_OFFSETG	=(2<<10),
	ARTEMIS_SETUPADC_OFFSETB	=(3<<10),
	ARTEMIS_SETUPADC_GAINR		=(4<<10),
	ARTEMIS_SETUPADC_GAING		=(5<<10),
	ARTEMIS_SETUPADC_GAINB		=(6<<10),
};

enum ARTEMISPROPERTIESCCDFLAGS
{
	ARTEMIS_PROPERTIES_CCDFLAGS_INTERLACED =1, // CCD is interlaced type
	ARTEMIS_PROPERTIES_CCDFLAGS_DUMMY=0x7FFFFFFF // force size to 4 bytes
};

enum ARTEMISPROPERTIESCAMERAFLAGS
{
	ARTEMIS_PROPERTIES_CAMERAFLAGS_FIFO =1, // Camera has readout FIFO fitted
	ARTEMIS_PROPERTIES_CAMERAFLAGS_EXT_TRIGGER =2, // Camera has external trigger capabilities
	ARTEMIS_PROPERTIES_CAMERAFLAGS_PREVIEW =4, // Camera can return preview data
	ARTEMIS_PROPERTIES_CAMERAFLAGS_SUBSAMPLE =8, // Camera can return subsampled data
	ARTEMIS_PROPERTIES_CAMERAFLAGS_HAS_SHUTTER =16, // Camera has a mechanical shutter
	ARTEMIS_PROPERTIES_CAMERAFLAGS_HAS_GUIDE_PORT =32, // Camera has a guide port
	ARTEMIS_PROPERTIES_CAMERAFLAGS_HAS_GPIO =64, // Camera has GPIO capability
	ARTEMIS_PROPERTIES_CAMERAFLAGS_HAS_WINDOW_HEATER =128, // Camera has a window heater
	ARTEMIS_PROPERTIES_CAMERAFLAGS_DUMMY=0x7FFFFFFF // force size to 4 bytes
};

//Structures

// camera/CCD properties
struct ARTEMISPROPERTIES
{
	int Protocol;
	int nPixelsX;
	int nPixelsY;
	float PixelMicronsX;
	float PixelMicronsY;
	int ccdflags;
	int cameraflags;
	char Description[40];
	char Manufacturer[40];
};

typedef void* ArtemisHandle;



#define artfn extern


// interface functions

// Abort exposure, if one is in progress
artfn  int ArtemisAbortExposure(ArtemisHandle hCam);

// Set the CCD amplifier on or off
artfn  int ArtemisAmplifier(ArtemisHandle hCam, bool bOn);

// Return API version. XYY X=major, YY=minor
artfn  int ArtemisAPIVersion();

// Allow/disallow automatic black level adjustment (only applies to quickercams)
artfn  int ArtemisAutoAdjustBlackLevel(ArtemisHandle hCam, bool bEnable);

// Set the x,y binning factors
artfn  int ArtemisBin(ArtemisHandle hCam, int x, int y);

// Return camera type and serial number
// Low byte of flags is camera type, 1=4021, 2=11002, 3=IC24/285, 4=205, 5=QC
// Bits 8-31 of flags are reserved.
artfn  int ArtemisCameraSerial(ArtemisHandle hCam, int* flags, int* serial);

// Retrieve the current camera state
artfn  int ArtemisCameraState(ArtemisHandle hCam);

// Clear the VRegs
artfn  int ArtemisClearVRegs(ArtemisHandle hCam);

// Return colour properties
artfn  int ArtemisColourProperties(ArtemisHandle hCam, ARTEMISCOLOURTYPE *colourType, int *normalOffsetX, int *normalOffsetY, int *previewOffsetX, int *previewOffsetY);

// Connect to given device. If Device=-1, connect to first available
// Returns handle if connected as requested, else NULL
artfn  ArtemisHandle ArtemisConnect(int Device);

artfn  int ArtemisCoolerWarmUp(ArtemisHandle hCam);

artfn  int ArtemisCoolingInfo(ArtemisHandle hCam, int* flags, int* level, int* minlvl, int* maxlvl, int* setpoint);

// Return true if Nth USB device exists and is a camera.
artfn  bool ArtemisDeviceIsCamera(int Device);

// Get USB Identifier of Nth USB device. Return false if no such device.
// pName must be at least 40 chars long.
artfn  bool ArtemisDeviceName(int Device, char *pName);

// Get USB Serial number of Nth USB device. Return false if no such device.
// pName must be at least 40 chars long.
artfn  bool ArtemisDeviceSerial(int Device, char *pName);

// Disconnect from given device.
// Returns true if disconnected as requested
artfn  bool ArtemisDisconnect(ArtemisHandle hCam);

// Disconnect all connected devices
artfn  bool ArtemisDisconnectAll();

// Percentage downloaded
artfn  int ArtemisDownloadPercent(ArtemisHandle hCam);

// Set a window message to be posted on completion of image download
// hWnd=NULL for no message.
artfn  int ArtemisExposureReadyCallback(ArtemisHandle hCam, HWND hWnd, int msg, int wParam, int lParam);

// Return time remaining in current exposure, in seconds
artfn  float ArtemisExposureTimeRemaining(ArtemisHandle hCam);

// Return true if amp switched off during exposures
artfn  bool ArtemisGetAmplifierSwitched(ArtemisHandle hCam);

// Get the x,y binning factors
artfn  int ArtemisGetBin(ArtemisHandle hCam, int *x, int *y);

// Return true if dark mode is set - ie the shutter is kept closed during exposures
artfn  bool ArtemisGetDarkMode(ArtemisHandle hCam);

/////////////////////////////////////////////////
// Get camera description, for 3rd-party software
// recv is a 40-byte buffer for the data
// info tells which data to return:
//  0  camera description from firmware
//  1  FTDI device name
//  2  FTDI device serial number
// unit is the camera number
// returns:
//  0  OK
//  1  camera busy
//  2  no camera active
artfn  int ArtemisGetDescription(char *recv, int info, int unit);

// Retrieve the downloaded image as a 2D array of type VARIANT
artfn  int ArtemisGetImageArray(ArtemisHandle hCam, VARIANT *pImageArray);

// Retrieve image dimensions and binning factors.
// x,y are actual CCD locations. w,h are pixel dimensions of image
artfn  int ArtemisGetImageData(ArtemisHandle hCam, int *x, int *y, int *w, int *h, int *binx, int *biny);

// Get the maximum x,y binning factors
artfn  int ArtemisGetMaxBin(ArtemisHandle hCam, int *x, int *y);

// Get current image processing options
artfn  int ArtemisGetProcessing(ArtemisHandle hCam);

// Get the pos and size of imaging subframe
artfn  int ArtemisGetSubframe(ArtemisHandle hCam, int *x, int *y, int *w, int *h);

// Activate a guide relay, axis=0,1,2,3 for N,S,E,W
artfn  int ArtemisGuide(ArtemisHandle hCam, int axis);

// Set guide port bits (bit 1 = N, bit 2 = S, bit 3 = E, bit 4 = W)
artfn  int ArtemisGuidePort(ArtemisHandle hCam, int nibble);

// Set download thread to high or normal priority
artfn  int ArtemisHighPriority(ArtemisHandle hCam, bool bHigh);

// Return pointer to internal image buffer (actually unsigned shorts)
artfn  void* ArtemisImageBuffer(ArtemisHandle hCam);

// Return true if an image is ready to be retrieved
artfn  bool ArtemisImageReady(ArtemisHandle hCam);

// Returns TRUE if currently connected to a device
artfn  bool ArtemisIsConnected(ArtemisHandle hCam);

// Return duration of last exposure, in seconds
artfn  float ArtemisLastExposureDuration(ArtemisHandle hCam);

// Return ptr to static buffer containing time of start of last exposure
artfn  char* ArtemisLastStartTime(ArtemisHandle hCam);

// Return fraction-of-a-second part of time of start of last exposure
// NB timing accuracy only justifies ~0.1s precision but milliseconds returned in case it might be useful
artfn  int ArtemisLastStartTimeMilliseconds(ArtemisHandle hCam);

// Get an internal DLL value specified by peekCode
artfn  int ArtemisPeek(ArtemisHandle hCam, int peekCode, int* peekValue);

// Set an internal DLL value specified by pokeCode
artfn  int ArtemisPoke(ArtemisHandle hCam, int pokeCode, int pokeValue);

// Set the Precharge mode
artfn  int ArtemisPrechargeMode(ArtemisHandle hCam, int mode);

// Fills in pProp with camera properties
artfn  int ArtemisProperties(ArtemisHandle hCam, struct ARTEMISPROPERTIES *pProp);

// Activate a guide relay for a short interval, axis=0,1,2,3 for N,S,E,W
artfn  int ArtemisPulseGuide(ArtemisHandle hCam, int axis, int milli);

// Set whether amp is switched off during exposures
artfn  int ArtemisSetAmplifierSwitched(ArtemisHandle hCam, bool bSwitched);

artfn  int ArtemisSetCooling(ArtemisHandle hCam, int setpoint);

// Enable/disable dark mode - ie the shutter is to be kept closed during exposures
artfn  int	ArtemisSetDarkMode(ArtemisHandle hCam, bool bEnable);

// Set preview mode (if supported by camera). True=preview mode enabled.
artfn  int ArtemisSetPreview(ArtemisHandle hCam, bool bPrev);

// Set current image processing options
artfn  int ArtemisSetProcessing(ArtemisHandle hCam, int options);

// Start an exposure
artfn  int ArtemisStartExposure(ArtemisHandle hCam, float Seconds);

// Prematurely end an exposure, collecting image data.
artfn  int ArtemisStopExposure(ArtemisHandle hCam);

// Switch off all guide relays
artfn  int ArtemisStopGuiding(ArtemisHandle hCam);

// Enable/disable termination of guiding before downloading the image
artfn  int ArtemisStopGuidingBeforeDownload(ArtemisHandle hCam, bool bEnable);

// set the pos and size of imaging subframe inunbinned coords
artfn  int ArtemisSubframe(ArtemisHandle hCam, int x, int y, int w, int h);

// Set the start x,y coords for imaging subframe.
// X,Y in unbinned coordinates
artfn  int ArtemisSubframePos(ArtemisHandle hCam, int x, int y);

// Set the width and height of imaging subframe
// W,H in unbinned coordinates
artfn  int ArtemisSubframeSize(ArtemisHandle hCam, int w, int h);

artfn  int ArtemisTemperatureSensorInfo(ArtemisHandle hCam, int sensor, int* temperature);

// Try to load the Artemis DLL.
// Returns true if loaded ok.
artfn bool ArtemisLoadDLL(char *FileName);

// Unload the Artemis DLL.
artfn void ArtemisUnLoadDLL();


// Return true if camera can overlap exposure time with image download time
artfn  bool ArtemisCanOverlapExposures(ArtemisHandle hCam);

// Return true if continuous exposing mode is supported, in which the exposure function simply reads out the CCD without clearing it first and without waiting
artfn  bool ArtemisContinuousExposingModeSupported(ArtemisHandle hCam);

// Return true if overlapped mode is set - ie the exposure function simply reads out the CCD without clearing it first and without waiting
artfn  bool ArtemisGetContinuousExposingMode(ArtemisHandle hCam);

// Get the number of GPIO lines and the value of the input on each line
// (value of input on nth line given by value of nth bit in lineValues)
artfn  int ArtemisGetGpioInformation(ArtemisHandle hCam, int* lineCount, int* lineValues);

// Return true if the previous overlapped exposure had the requested exposure time.
artfn  bool ArtemisOverlappedExposureValid(ArtemisHandle hCam);

// Enable/disable overlapped mode - ie the exposure function is to simply read out the CCD without clearing it first and without waiting
artfn  int ArtemisSetContinuousExposingMode(ArtemisHandle hCam, bool bEnable);

// Set the GPIO line directions
// (nth line is set as an input (output) if nth bit of directionMask is 1 (0)
artfn  int	ArtemisSetGpioDirection(ArtemisHandle hCam, int directionMask);

//Set GPIO output line values
// (nth line (if it's an output) is set to high (low) if nth bit of lineValues is 1 (0)
artfn  int ArtemisSetGpioValues(ArtemisHandle hCam, int lineValues);

// Set duration for overlapped exposures. Call once, not every frame.
artfn  int	ArtemisSetOverlappedExposureTime(ArtemisHandle hCam, float Seconds);

// Set conversion speed.
artfn  int ArtemisSetOversample(ArtemisHandle hCam, int oversample);

// Set subsampling mode (if supported by camera). True=subsampling enabled.
artfn  int ArtemisSetSubSample(ArtemisHandle hCam, bool bSub);

// Request an overlapped exposure to be downloaded when ready
artfn  int	ArtemisStartOverlappedExposure(ArtemisHandle hCam);

// Set External Trigger mode (if supported by camera). True=wait for trigger.
artfn  int ArtemisTriggeredExposure(ArtemisHandle hCam, bool bAwaitTrigger);

// Set the window heater power
artfn  int ArtemisSetWindowHeaterPower(ArtemisHandle hCam, int windowHeaterPower);

// Get the window heater power
artfn  int ArtemisGetWindowHeaterPower(ArtemisHandle hCam, int* windowHeaterPower);

#undef artfn


#endif //_ARTEMISSCIAPI_H_