#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    renderer.setSize(ofGetWidth(), ofGetHeight());
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 3, 3);
    
    
    renderer.startTuio(3333);
    
    cont.enableDepthTest();
    for(int i=0;i<40;i++){
        buttons[i].setSize(100, 100);
        buttons[i].setPosition(ofRandomWidth(),ofRandomHeight());
        buttons[i].setColor(255, 0, 0);
        buttons[i].enableDepthTest();
        buttons[i].setRandomColor();
        cont.addChild(&buttons[i]);
    }
    renderer.addChild(&cont);
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
    if(key=='c'){
        ofCamera* camera=renderer.getCamera();
        camera->rotate(30 , 0, 1, 0);
        
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
    renderer.setupColorPicker(ofGetWidth(), ofGetHeight(), 3, 3);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}