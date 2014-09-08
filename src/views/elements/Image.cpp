#include "Image.h"


Image::Image(){
	hasMaxSize			= false;
	changed				= false;
    isUpdateReal		= false;
    img					= new ofImage();
    loaded				= false;
	loadingAsync		= false;
	loadingPlaceholder	= NULL;
	mode				= OF_RECTMODE_CORNER;

	tmpResizeCounter	= 0;
	tmpFilepath			= "";
}


Image::~Image(){
	img->clear();
}


void Image::update(){
	if (img) {
		if (loadingAsync) {
			if (img->getWidth() > 0) {
				loaded		= true;
				loadingAsync= false;
				changed		= true;
				BasicScreenObject::setSize(img->getWidth(), img->getHeight());
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


void Image::_draw(){
	if (img == NULL || loadingAsync) return;
	
	
	if (img->getWidth() > 0) {
		ofPushStyle();
		
		ofSetRectMode(mode);
        img->draw(0, 0, width, height);
		ofPopStyle();
	}
	/*
	 if (tmpResizeCounter>1) {
	 ofLog(OF_LOG_NOTICE, "resized more than once (" + ofToString(tmpResizeCounter) + "): " + tmpFilepath);
	 }
	 */
	tmpResizeCounter = 0;
}


void Image::load(string _filename){
	img->clear();
	img->loadImage(_filename);
	setSize(img->getWidth(), img->getHeight());
	changed = true;
	loaded  = true;
	ofNotifyEvent(imageLoadedEvent, myEventArgs, this);
	tmpFilepath = _filename;
}


void Image::loadAsyncFromDisk(string _filename, ofxThreadedImageLoader* loader) {
	loadingAsync = true;
	loaded		 = false;
	if (loadingPlaceholder != NULL) {
		loadingPlaceholder->isVisible(true);
	}
	img->clear();
	loader->loadFromDisk(*img, _filename);
	tmpFilepath = _filename;
}


void Image::loadAsyncFromURL(string _url, ofxThreadedImageLoader* loader) {
	loadingAsync = true;
	loaded		 = false;
	if (loadingPlaceholder != NULL) {
		loadingPlaceholder->isVisible(true);
	}
	img->clear();
	loader->loadFromURL(*img, _url);
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
    if(img) img->resize(width, height);	// heavy lifting here... causes lags
	//ofLog(OF_LOG_NOTICE, tmpFilepath + " resizing to (" + ofToString(tmpResizeCounter) + "): " + ofToString(width) + ", " + ofToString(height));
	tmpResizeCounter++;
}


void Image::crop(int x, int y, int w, int h) {
	BasicScreenObject::setSize(w,h);
	if (img==NULL) return;
	img->crop(x, y, w, h);
}


void Image::clone(Image* _srcImage) {
	setSize(_srcImage->getWidth(), _srcImage->getHeight());
	img->clone(*_srcImage->getImagePointer());
}


void Image::clone(ofImage* _srcImage) {
	setSize(_srcImage->getWidth(), _srcImage->getHeight());
	img->clone(*_srcImage);
}


void Image::setMaxSize(float _maxwidth, float _maxheight){
	hasMaxSize	= true;
	maxWidth	= _maxwidth;
	maxHeight	= _maxheight;
	changed = true;
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

/**
 * scales down the image to fit the max _width and _height dimensions and pads the borders with _color
 * image will have _width and _height as its dimensions after calling this method
 */
void Image::scaleFitPad(int _width, int _height, ofColor _color, bool _vcenter, bool _hcenter) {
	ofFbo		compose;
	ofPixels	pixels;
	
	setMaxSize(_width, _height);
	updateSize();
	
	compose.allocate(_width, _height, GL_RGBA);
	pixels.allocate(_width, _height, OF_IMAGE_COLOR_ALPHA);
	compose.begin();
	
    ofPushStyle();
	ofSetColor(_color);
	ofRect(0, 0, _width, _height);

	ofSetColor(255,255,255);
	int vpos = 0;
	int hpos = 0;
	if (_vcenter==true) vpos = (_width-img->getWidth())*.5;
	if (_hcenter==true) hpos = (_height-img->getHeight())*.5;
	img->draw(vpos, hpos);
	ofPopStyle();
	compose.end();
	
	compose.readToPixels(pixels);
	img->setFromPixels(pixels.getPixels(), _width, _height, OF_IMAGE_COLOR_ALPHA, true );
	img->update();
	BasicScreenObject::setSize(_width, _height);
}


void Image::setRectMode(ofRectMode _mode) {
	mode = _mode;
}