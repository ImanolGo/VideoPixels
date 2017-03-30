/*
 *  ImageManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "ofMain.h"

#include <time.h>

#include "ImageManager.h"
#include "AppManager.h"

const int ImageManager::IMAGE_WIDTH = 512;


ImageManager::ImageManager(): Manager(), m_isRecording(false), m_mirror(false)
{
	//Intentionally left empty
}


ImageManager::~ImageManager()
{
    ofLogNotice() <<"ImageManager::Destructor" ;
}


void ImageManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    m_image.clear();
    m_colors.clear();
    
    
    ofLogNotice() <<"ImageManager::initialized" ;
    
}


void ImageManager::update()
{
    if (m_isRecording) {
         this->updateColorPixels();
    }
}

void ImageManager::draw()
{
    
}

void ImageManager::updateColorPixels()
{
    auto leds = AppManager::getInstance().getLedsManager().getLeds();
    
    for (auto& led: leds){
        m_colors.push_back(led->getColor());
    }
}


void ImageManager::onRecordingChange(bool& value)
{
    if (m_isRecording && !value) {
        this->saveImage();
    }
    else{
        m_image.clear();
        m_colors.clear();
    }
    
    m_isRecording = value;
}


void ImageManager::saveImage()
{
    if(m_mirror){
        this->saveImageMirror();
    }
    else{
        this->saveImageSample();
    }
    
    m_image.clear();
    m_colors.clear();
}



void ImageManager::saveImageMirror()
{
    auto leds = AppManager::getInstance().getLedsManager().getLeds();
    
    
    int width = leds.size();
    int height = 0;
    
    if(width>0){
        height = 2*m_colors.size()/width;
    }
    
    ofLogNotice() <<"ImageManager::saveImageMirror ->  width = " << width;
    ofLogNotice() <<"ImageManager::saveImageMirror ->  height = " << height;
    
    m_image.clear();
    m_image.allocate(IMAGE_WIDTH, height, OF_IMAGE_COLOR);
    
    
    ofPixelsRef pixels = m_image.getPixels();
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int n = x + y*width;
            
            if ( y >= height/2) {
                int y_ = height - y - 1;
                n = x + y_* width;
            }
            
            
            pixels.setColor(x, y, m_colors[n]);
        }
    }
    
    for (int y = 0; y < height; y++) {
        for (int x = width; x < IMAGE_WIDTH ; x++) {
            //ofLogNotice() <<"ImageManager::saveImageSample ->  x = " << x;
            pixels.setColor(x, y, ofColor::black);
        }
    }
    
    m_image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_FR_" + getDateTime() +  ".bmp";
    m_image.save(fileName);
    
    ofLogNotice() <<"ImageManager::saveImageMirror ->  Saved " << fileName;
    
}

void ImageManager::saveImageSample()
{
    
    auto leds = AppManager::getInstance().getLedsManager().getLeds();
    
    int width = leds.size();
    int height = 0;
    
    if(width>0){
        height = m_colors.size()/width;
    }
    
    ofLogNotice() <<"ImageManager::saveImageSample ->  width = " << width;
    ofLogNotice() <<"ImageManager::saveImageSample ->  height = " << height;
    ofLogNotice() <<"ImageManager::saveImageSample ->  colors size = " << m_colors.size();
    
    m_image.clear();
    m_image.allocate(IMAGE_WIDTH, height, OF_IMAGE_COLOR);
    
    ofPixelsRef pixels = m_image.getPixels();
    
    /*
     In a bottom-up DIB, the image buffer starts with the bottom row of pixels, followed by the next row up,
     and so forth. The top row of the image is the last row in the buffer.
     Therefore, the first byte in memory is the bottom-left pixel of the image.
     */
    
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int y_ = height - y - 1;
            int n = x + y_*width;
            pixels.setColor(x, y, m_colors[n]);
        }
    }
    
    for (int y = 0; y < height; y++) {
        for (int x = width; x < IMAGE_WIDTH ; x++) {
            //ofLogNotice() <<"ImageManager::saveImageSample ->  x = " << x;
            pixels.setColor(x, y, ofColor::black);
        }
    }
    
    m_image.update(); // uploads the new pixels to the gfx card
    
    string fileName = "images/saved/image_" + getDateTime() +  ".bmp";
    m_image.save(fileName);
    
    ofLogNotice() <<"ImageManager::saveImageSample ->  Saved " << fileName;
    
}

string ImageManager::getDateTime()
{
    char buffer[80];
    string fmt="%d-%m-%Y-%H-%M-%S";
    time_t rawtime;
    time ( &rawtime );
    
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buffer,80,fmt.c_str(),timeinfo);
    return buffer;
}





