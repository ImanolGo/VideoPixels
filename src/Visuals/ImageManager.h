/*
 *  ImageManager.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#pragma once

#include "Manager.h"
#include "Led.h"
#include "Manager.h"


//========================== class ImageManager ==============================
//============================================================================
/** \class ImageManager ImageManager.h
 *	\brief Class managing the images to be exported
 *	\details it reads from the Led visuals and saves it on a file on demand
 */


class ImageManager: public Manager
{
    
    static const int IMAGE_WIDTH;
    
public:
    
    //! Constructor
    ImageManager();
    
    //! Destructor
    ~ImageManager();
    
    //! Setup the Image Manager
    void setup();
    
    //! Update the Image Manager
    void update();
    
    //! Draw the Image Manager
    void draw();
    
    void onRecordingChange(bool& value);
    
    void onMirroringChange(bool& value) {m_mirror = value;}
    
private:
    
    void saveImage();
    
    void saveImageSample();
    
    void saveImageMirror();
    
    void updateColorPixels();
    
    string getDateTime();
    
private:
    
    typedef vector< ofColor > ColorVector;
    
    bool                m_isRecording;
    bool                m_mirror;
    
    ofImage             m_image;
    ColorVector         m_colors;
};




