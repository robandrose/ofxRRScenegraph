#include "Image.h"


Image::Image(){
	hasMaxSize	= false;
	changed		= false;
    isUpdateReal= false;
    img			= new ofImage();
    loaded		= false;
	loadingAsync= false;
	loadingPlaceholder = NULL;
	mode		= OF_RECTMODE_CORNER;
}


Image::~Image(){
	img->clear();
}


void Image::setup(){
	
}


void Image::update(){
	if (img) {
		if (loadingAsync) {
			if (img->getWidth() > 0) {
				loaded		= true;
				loadingAsync= false;
				changed		= true;
				setSize(img->getWidth(), img->getHeight());
				if (loadingPlaceholder != NULL) {
					loadingPlaceholder->isVisible(false);
				}
				ofNotifyEvent(imageLoadedEvent, myEventArgs, this);
			}
		}
		if(changed){
			updateSize();
		}
	}
}


void Image::load(string _filename){
	img->clear();
	img->loadImage(_filename);
	setSize(img->getWidth(), img->getHeight());
	changed = true;
	loaded  = true;
	ofNotifyEvent(imageLoadedEvent, myEventArgs, this);
}


void Image::loadAsyncFromDisk(string _filename, ofxThreadedImageLoader* loader) {
	loadingAsync = true;
	loaded		 = false;
	if (loadingPlaceholder != NULL) {
		loadingPlaceholder->isVisible(true);
	}
	img->clear();
	loader->loadFromDisk(img, _filename);
}


void Image::loadAsyncFromURL(string _url, ofxThreadedImageLoader* loader) {
	loadingAsync = true;
	loaded		 = false;
	if (loadingPlaceholder != NULL) {
		loadingPlaceholder->isVisible(true);
	}
	img->clear();
	loader->loadFromURL(img, _url);
}


void Image::setLoadingPlaceholder(BasicScreenObject* _loadingPlaceholder) {
	if (loadingPlaceholder != NULL) {
		removeChild(loadingPlaceholder);
	}
	loadingPlaceholder = _loadingPlaceholder;
	addChild(loadingPlaceholder);
	loadingPlaceholder->setPosition((width - loadingPlaceholder->getWidth())/2.0, (height - loadingPlaceholder->getHeight())/2.0);
	loadingPlaceholder->isVisible(false);
}


ofImage* Image::getImagePointer(){
	return img;
}


void Image::setSize(float _width, float _height){
	BasicScreenObject::setSize(_width, _height);
	if(isUpdateReal){
        updateRealImageSize();
	}
}


void Image::updateRealImageSize(){
    if(img) img->resize(width, height);
}


void Image::crop(int x, int y, int w, int h) {
	if (img==NULL) return;
	img->crop(x, y, w, h);
	BasicScreenObject::setSize(w,h);
}


void Image::setMaxSize(float _maxwidth, float _maxheight){
	hasMaxSize	= true;
	maxWidth	= _maxwidth;
	maxHeight	= _maxheight;
	
	updateSize();
}


void Image::updateSize(){
    if (img == NULL) return;
    if(!hasMaxSize) return;
	float fact = (maxWidth/maxHeight)/(img->getWidth()/img->getHeight());
	float newwidth	= maxWidth;
	float newheight	= maxHeight;
	if(fact >= 1){
		newwidth = maxHeight/img->getHeight()*img->getWidth();
	}else{
		newheight = maxWidth/img->getWidth()*img->getHeight();
	}
	setSize(newwidth, newheight);
	changed=false;
}


void Image::_draw(){
	if (img == NULL || loadingAsync) return;
	
	
	if (img->getWidth() > 0) {
		ofPushStyle();
		ofSetRectMode(mode);
        img->draw(0, 0, width, height);
		ofPopStyle();
	}
}


bool Image::isLoaded() {
    return loaded;
}


void Image::clear() {
	if (loaded && img != NULL) {
        img->clear();
    }
}


void Image::setImagePointer(ofImage* _img) {
    img		= _img;
    changed	= true;
    loaded	= true;
}


/**
 *	fits the image into the supplied rect (width/height) and center-crops the image.
 *  image will have _width and _hight as its dimensions after calling this method
 */
void Image::cropFitScale(int _width, int _height) {
	float sourceAspect	= getWidth() / float(getHeight());
	float destAspect	= _width / float(_height);
	float tempWidth, tempHeight;
	
	if (sourceAspect > destAspect) {
		// landscape
		tempHeight	= _height;
		tempWidth	= _height * sourceAspect;
	} else {
		// portrait
		tempWidth	= _width;
		tempHeight	= _width / sourceAspect;
	}
	
	setSize(tempWidth, tempHeight);
	
	// do crop / center
	float cropX = (tempWidth - _width) / 2.0;
	float cropY = (tempHeight - _height) / 2.0;
	
	crop(cropX, cropY, _width, _height);
}


void Image::setRectMode(ofRectMode _mode) {
	mode = _mode;
}
