/*
 *  VideoPixelsApp.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "AppManager.h"

#include "VideoPixelsApp.h"

//--------------------------------------------------------------
void VideoPixelsApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void VideoPixelsApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void VideoPixelsApp::draw(){
    AppManager::getInstance().draw();
}

void VideoPixelsApp::exit()
{
    ofLogNotice() <<"VideoPixelsApp::exit";

}

//--------------------------------------------------------------
void VideoPixelsApp::keyPressed(int key){

}

//--------------------------------------------------------------
void VideoPixelsApp::keyReleased(int key){

}

//--------------------------------------------------------------
void VideoPixelsApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void VideoPixelsApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void VideoPixelsApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void VideoPixelsApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void VideoPixelsApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void VideoPixelsApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void VideoPixelsApp::dragEvent(ofDragInfo dragInfo){

}
