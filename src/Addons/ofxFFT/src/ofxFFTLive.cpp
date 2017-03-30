/*
 *  ofxFFTLive.cpp
 *  Created by lukasz karluk on 29/08/09.
 *
 */

#include "ofxFFTLive.h"

ofxFFTLive::ofxFFTLive() : ofxFFTBase() {
    soundStream = NULL;
}

ofxFFTLive::~ofxFFTLive() {
    if(soundStream == NULL) {
        return;
    }
    soundStream->stop();
    soundStream->close();
    delete soundStream;
    soundStream = NULL;
}

void ofxFFTLive::setup() {
    ofSoundStream * soundStream = new ofSoundStream();
    soundStream->setup(this,                   // callback obj.
                       0,                      // out channels.
                       1,                      // in channels.
                       44100,                  // sample rate.
                       getBufferSize(),        // buffer size.
                       4);                     // number of buffers.
    this->soundStream = soundStream;
}

void ofxFFTLive::audioIn(float * input, int bufferSize, int nChannels) {
    ofxFFTBase::audioIn(input);
}