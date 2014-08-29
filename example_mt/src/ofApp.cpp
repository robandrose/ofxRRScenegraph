#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    renderer.setSize(ofGetWidth(), ofGetHeight());
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 2, 5);
    renderer.startTuio(3333);
    
    for(int i=0;i<100;i++){
        schnipsel[i].setSize(100, 100);
        schnipsel[i].setPosition(ofRandomWidth(),ofRandomHeight());
        schnipsel[i].setColor(255, 0, 0);
        schnipsel[i].setRandomColor();
        cont.addChild(&schnipsel[i]);
        
    }
    
    renderer.addChild(&cont);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    renderer.resize();
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 2, 5);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}