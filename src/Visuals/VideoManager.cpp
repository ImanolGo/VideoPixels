/*
 *  VideoManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "ofMain.h"

#include "VideoManager.h"
#include "AppManager.h"
#include "ofQTKitPlayer.h"


const string VideoManager::VIDEO_PATH = "videos/";

VideoManager::VideoManager(): Manager(), m_playVideo(false), m_recordVideoLoops(false), m_trail(false), m_frameNumber(-1)
{
    //Intentionally left empty
}


VideoManager::~VideoManager()
{
    ofLogNotice() <<"VideoManager::Destructor" ;
}


void VideoManager::setup()
{
    if(m_initialized)
        return;
    
    
    Manager::setup();
    
    this->loadVideos();
    this->setupBoundingBox();
    this->setupFbo();
    
    ofLogNotice() <<"VideoManager::initialized" ;
    
}


void VideoManager::loadVideos()
{

    //shared_ptr<ofQTKitPlayer> videoPlayer = shared_ptr<ofQTKitPlayer>(new ofQTKitPlayer()) ;
    //m_videoPlayer.setPlayer(videoPlayer);
    
    ofLogNotice()<< "VideoManager::loadVideos->loading samples from \""<<VIDEO_PATH<<"\"";
    ofDirectory dir(VIDEO_PATH);
    dir.allowExt("mp4");
    dir.allowExt("mov");
    dir.allowExt("avi");
    //populate the directory object
    if(dir.listDir()==0){
        ofLogNotice()<< "VideoManager::loadVideos-> No samples found in \""<<VIDEO_PATH<<"\"";
    }
    
    //go through and print out all the paths
    for(int i = 0; i < dir.size(); i++)
    {
        string videoPath = dir.getPath(i);
        m_videos.push_back(videoPath);
        ofLogNotice()<< "VideoManager::loadVideos-> Loaded: \""<<videoPath<<"\"";
    }
    
    m_currentVideo = m_videos.front();
    m_videoPlayer.load(m_currentVideo);
    //m_videoPlayer.setLoopState(OF_LOOP_NONE);
    m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
}

void VideoManager::setupBoundingBox()
{
    float ratio = ((float)ofGetWidth())/ofGetHeight();
    
    m_boundingBox.width = AppManager::getInstance().getGuiManager().getWidth();
    m_boundingBox.height = m_boundingBox.width/ratio;
    
    
    m_boundingBox.y = AppManager::getInstance().getGuiManager().getPosition().y + AppManager::getInstance().getGuiManager().getHeight() + 20;
    m_boundingBox.x = AppManager::getInstance().getGuiManager().getPosition().x;
}

void VideoManager::setupFbo()
{
    m_fbo.allocate(m_videoPlayer.getPixels().getWidth(), m_videoPlayer.getPixels().getHeight(),GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void VideoManager::resetPosition()
{
    setupBoundingBox();
}

void VideoManager::update()
{
    if (!m_playVideo) {
        return;
    }
    
    //ofLogNotice()<< "VideoManager::update: ";
    
    if(m_videoPlayer.isFrameNew())
    {
        int frame = m_videoPlayer.getCurrentFrame();
        if(m_frameNumber != frame)
        {
            m_frameNumber = frame;
            ofPixels pixels;
            m_fbo.readToPixels(pixels);
            AppManager::getInstance().getLedsManager().setPixels(pixels);
            //ofLogNotice()<< "VideoManager::newFrame: ";
        }
    }
    
    if(m_recordVideoLoops && m_videoPlayer.getIsMovieDone()){
        m_playVideo = false;
        AppManager::getInstance().getImageManager().onRecordingChange(m_playVideo);

        m_playVideo = true;
        onNextVideoChange();
    }
    
     m_videoPlayer.update();
    
}


void VideoManager::draw()
{
    if (!m_playVideo) {
        return;
    }
    
    
    m_fbo.begin();
    ofPushStyle();
    
    if(m_trail){
        ofEnableAlphaBlending();
        ofFill();
        ofSetColor(0,0,0, 5);
        ofDrawRectangle(0,0,m_fbo.getWidth(),m_fbo.getHeight());
        ofSetColor(m_color, 12);;
    }
    else{
        ofClear(0);
        ofSetColor(m_color);
    }
    
    
    m_videoPlayer.draw(0,0);
    ofPopStyle();
    m_fbo.end();
    
    m_fbo.draw(m_boundingBox);
    
    //m_videoPlayer.draw(0,0);
    
}

void VideoManager::onPlayVideoChange(bool value)
{
    ofLogNotice()<< "VideoManager::onPlayVideoChange: " << value;
    
    if(value){
        m_playVideo = true;
        m_videoPlayer.play();
    }
    else{
        m_playVideo = false;
        m_videoPlayer.stop();
    }
}

void VideoManager::onRecordVideoLoopsChange(bool& value) {
    
    m_recordVideoLoops = value;
    
    if(m_recordVideoLoops){
        m_videoPlayer.setLoopState(OF_LOOP_NONE);
    }
    else{
        m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
    }
    
}

void VideoManager::onVideoTrailChange(bool& value) {
    
    m_trail = value;
}

void VideoManager::onNextVideoChange()
{
    for (int i = 0; i < m_videos.size(); i++) {
        if(m_videos[i] == m_currentVideo){
            int index = (i+1)%m_videos.size();
            m_currentVideo = m_videos[index];
            break;
        }
    }
    
    //m_videoPlayer.closeMovie();
    
    m_videoPlayer.load(m_currentVideo);
    ofLogNotice()<< "VideoManager::onNextVideoChange: Video Loaded" << m_currentVideo;
    
    m_videoPlayer.stop();
    
    if(m_playVideo){
        
        m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
        
        if(m_recordVideoLoops){
            m_videoPlayer.setLoopState(OF_LOOP_NONE);
        }
        
        m_videoPlayer.play();
        AppManager::getInstance().getImageManager().onRecordingChange(m_playVideo);
        m_frameNumber = -1;
    }
    
    this->setupFbo();
    
    
}



