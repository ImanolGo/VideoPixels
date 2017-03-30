/*
 *  AudioEqualizer2.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#include "ofMain.h"

#include "AudioEqualizer2.h"


#include "AppManager.h"




AudioEqualizer2::AudioEqualizer2(): m_numFrames(0), m_currentFrame(0)
{
	//Intentionally left empty
}


AudioEqualizer2::~AudioEqualizer2()
{
    ofLogNotice() <<"AudioEqualizer2::Destructor" ;
}


void AudioEqualizer2::setup()
{
    this->setupNumFrames();
    this->setupImage();
    this->setupRectangle();
}


void AudioEqualizer2::setupNumFrames()
{
    float fps =  24;
    float animationTimeInS = 0.9;
    
    m_numFrames = animationTimeInS*fps;
    
}

void AudioEqualizer2::setupRectangle()
{
    m_rectangle.width = AudioVisualsManager::FBO_WIDTH;
    m_rectangle.height = AudioVisualsManager::FBO_HEIGHT;
    
    
    
}

void AudioEqualizer2::setupImage()
{
    m_image = ofPtr<ImageVisual>(new ImageVisual(ofVec3f(0,0,0), "Equalizer"));
    m_image->setHeight( AudioVisualsManager::FBO_HEIGHT);
    m_image->setWidth( AudioVisualsManager::FBO_WIDTH);
}



void AudioEqualizer2::update()
{
    //ofLogNotice() <<"AudioEqualizer2::update" ;
    
    float height = ofMap(m_currentFrame, 0, m_numFrames-1, 0, AudioVisualsManager::FBO_HEIGHT);
    m_rectangle.height = height;
    
    m_currentFrame = (m_currentFrame + 1)%m_numFrames;
    //ofLogNotice() <<"AudioEqualizer2::update-> current frame " << m_currentFrame;
}

void AudioEqualizer2::draw()
{
    ofPushStyle();
    m_image->draw();
    ofSetColor(0, 0, 0);
    ofRect(m_rectangle);
    ofPopStyle();
}






