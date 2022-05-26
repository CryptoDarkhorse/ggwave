#pragma once

#include "ggwave/ggwave.h"

#include <string>
#include <memory>

//class GGWave;
//struct TxProtocol;

// GGWave helpers



void GGWave_setDefaultCaptureDeviceName(std::string name);
void GGWave_setDefaultCaptureDeviceNamePtr(const char * name);
bool GGWave_init(const int playbackId, const int captureId, const int payloadLength = -1, const float sampleRateOffset = 0);
GGWave * GGWave_instance();
void GGWave_reset(void * parameters);
bool GGWave_mainLoop();
bool GGWave_deinit();

bool GGWave_initObj(GGWave * instance, int dataSize, const char * dataBuffer, const GGWave::TxProtocol & txProtocol, const int volume);
GGWave::TxProtocol GGWave_getTxProtocol(int id);
