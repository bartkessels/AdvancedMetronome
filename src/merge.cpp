#include "merge.h"

#include <bitset>
#include <iostream>
#include <chrono>
#include <math.h>
#include <fstream>
#include <iomanip>

#define PI 3.14159265359

Merge::Merge(QObject *parent):
    QObject(parent)
{

}

void Merge::create()
{
    int samplesize          = 16;
    unsigned int samplerate = 44100;
    int duration            = 15; // seconds
    int channels            = 1;
    //long samples            = 4096;
    long samples            = samplerate * duration; // per channel
    long total_samples      = samples * channels; // all channels

    long inputLength        = total_samples * samplesize / 8;


    std::cout << inputLength << std::endl;

    // Create test input buffer
    char input[inputLength];

    // Initialize test buffer with zeros
    for (long i = 0; i < inputLength; i++){
        input[i] = 0;
    }

    int l = .8 * 0x8000;// * (440/samplerate);

    input[0] = l;
    input[100] = l;
    input[700] = l;
    input[1100] = l;

    // Export raw audio data to file
    std::ofstream fout("/home/bkessels/sine_char16bit.raw", std::ios::out | std::ios::binary);
    if (fout.is_open()){
        fout.write(input, total_samples * samplesize / 8);
    }
    fout.close();
}
