#pragma once

#include "ggwave-common-sdl2.h"

#include <thread>
#include <vector>

std::thread initMain();
void renderMain();
void deinitMain(std::thread & worker);

// share info

struct ShareInfo {
    std::string uri;
    std::string filename;
    const char * dataBuffer;
    size_t dataSize;
};

int getShareId();
ShareInfo getShareInfo();

// delete file

struct DeleteInfo {
    std::string uri;
    std::string filename;
};

int getDeleteId();
DeleteInfo getDeleteInfo();

// receive

struct ReceiveInfo {
    const char * uri;
    const char * filename;
    const char * dataBuffer;
    size_t dataSize;
};

int getReceivedId();
std::vector<ReceiveInfo> getReceiveInfos();
bool confirmReceive(const char * uri);

// input

void clearAllFiles();
void clearFile(const char * uri);

void addFile(
        const char * uri,
        const char * filename,
        const char * dataBuffer,
        size_t dataSize);

void addFile(
        const char * uri,
        const char * filename,
        std::vector<char> && data);
