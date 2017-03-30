/*
 *  AudioEqualizer2.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#pragma once


//========================== class AudioEqualizer2 ==============================
//============================================================================
/** \class AudioEqualizer2 AudioEqualizer2.h
 *	\brief Class representing audio equalizer visuals
 *	\details it creates and updates the audio equalizer
 */

#include "LedsManager.h"

#include "ImageVisual.h"

class AudioEqualizer2
{

    public:

        //! Constructor
        AudioEqualizer2();

        //! Destructor
        ~AudioEqualizer2();

        //! Setup the Audio Equalizer
        void setup();

        //! Update the Audio Equalizer
        void update();
    
        //! Draw the Audio Equalizer
        void draw();
    
    private:
    
        void setupNumFrames();
    
        void setupImage();
    
        void setupRectangle();
    
    private:
    
        int m_numFrames;
        int m_currentFrame;
    
        ofPtr<ImageVisual>  m_image;
        ofRectangle  m_rectangle;
};




