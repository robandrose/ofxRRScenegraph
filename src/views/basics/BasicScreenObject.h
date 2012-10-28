/*
 *  BasicScreenObject.h
 *
 *  Created by Matthias Rohrbach 2 on 10.06.12.
 *  Copyright 2012 rob & rose grafik. All rights reserved.
 *
 */


#pragma once
#ifndef BASIC_SCREEN_OBJECT
#define BASIC_SCREEN_OBJECT

#include "ofMain.h"
#include "CppTweener.h"
#include "ofxTimer.h"
#include "BasicScreenObjectEvent.h"
#include "IPositioner.h"

#define MASK_TYPE_STENCIL 0
#define MASK_TYPE_SCISSOR 1
#define MASK_TYPE_CLIPPLANES 2

class BasicScreenObject:public ofNode, tween::TweenerListener{

	
	
	
public:

	
	BasicScreenObject();
	virtual ~BasicScreenObject();
	
	virtual void setup(){};
	virtual void firstUpdate(){};
	virtual void update(){};
    
    // called by parentobject, draws all children in childlist
    virtual void draw(); 
	virtual void drawChildren();
    
    virtual void drawForPicking();
    virtual void drawChildrenForPicking();
	
    //abstract method, must be overwritten
	virtual void _draw()=0; //the elements private draw method
	
	virtual void _drawForPicking(){};
    virtual void _drawAfterChildren(){};
    
	virtual void exit(){};
	virtual void onKill(BasicScreenObjectEvent &event);
	virtual void _onKill();
    
    //functions called by ofEvents
	void _draw(ofEventArgs &e);
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
	void _exit(ofEventArgs &e);
    
	// Basic Setters and Getters
    void setName(string _name){myname=_name;};
	string getName(){return myname;};
		
	void setId(int _id){myid=_id;};
	int getId(){return myid;};
	
	void isUpdating(bool _isupdating);
	bool isUpdating();
	
    bool isVisible();
	void isVisible(bool _visible);
	
	bool isInteractive();
	void isInteractive(bool _isinteractive){isinteractive=_isinteractive;};
	
	// Search through the tree upwards 
	bool getCombinedVisible();
	float getCombinedAlpha();
	
	// Child Parent Root Relations:
	
	using ofNode::setParent;
	void setParent(BasicScreenObject* _parent);
	
	using ofNode::getParent;
	BasicScreenObject* getParent();
	
	BasicScreenObject* getRoot();
	
	virtual void addChild(BasicScreenObject* _child);
	virtual void addChildAt(BasicScreenObject* _child, int _index);
	virtual void removeChild(BasicScreenObject* _child);
	virtual void removeChildAt(BasicScreenObject* _child, int _index);
	virtual void removeChildren();
	virtual void moveMeToTop();
	virtual void moveChildToTop(BasicScreenObject* _child);
	virtual vector<BasicScreenObject*>* getChildren();
	virtual void killMeSoftly(float _time);
	
	bool isAdded();
	
	void isOrderChildrenByZ(bool _isorderbyz);
	bool isOrderChildrenByZ();
	void doOrderChildrenByZ();
    
	//ofVec3f getScreenPosition(ofVec3f _);
	
	ofVec3f globalToLocalDir(ofVec3f _global);
	
    ofVec3f localToGlobal(ofVec3f _local);
	ofVec3f localToGlobal(float _x, float _y, float _z=0);
	
	ofVec3f globalToLocal(ofVec3f _global);
	ofVec3f globalToLocal(float _x, float _y, float _z=0);
	
	ofVec3f foreignToLocal(BasicScreenObject* _foreign, ofVec3f _foreignpos);
	ofVec3f foreignToLocal(BasicScreenObject* _foreign, float _x, float _y, float _z);
	
	ofVec3f localToForeign(BasicScreenObject* _foreign, ofVec3f _local);
	ofVec3f localToForeign(BasicScreenObject* _foreign, float _x, float _y, float _z);
	
	ofRectangle getBoundingBox(BasicScreenObject* ref);
	
	ofRectangle getScreenBoundingBox();
	ofVec3f getScreenPosition();
	
	
	// Show Hide with Calbacks
	void hide();
	void hide(float _time);
	void show();
	void show(float _time);	
	virtual void onHide(BasicScreenObjectEvent &event){};
	virtual void onShow(BasicScreenObjectEvent &event){};
	
	
	void enableDepthTest();
	void disableDepthTest();
    bool isDepthTestEnabled(){return depthtestenabled;};
	
	void enableLighting();
	void disableLighting();
	bool isLightingEnabled(){return lightingenabled;};
	    
	
	// Masking
	virtual void setMaskObject(BasicScreenObject *_maskobject);
	void isMask(bool _ismask);
	bool isMask();
	void hasMask(bool _hasmask);
	bool hasMask();
	BasicScreenObject* getMaskObject();
	void setMaskType(int _masktype){masktype=_masktype;};
    
	// GL Functions for Masking;
	void setupMask();
	void restoreMask();

	// Position, Offset and Anchorpoint

	// position (ofNode inherit)
	//void setPosition(float px, float py, float pz);
	//void setPosition(const ofVec3f& p);
	//void setGlobalPosition(float px, float py, float pz);
	//void setGlobalPosition(const ofVec3f& p);
	
	using ofNode::setPosition; 
	virtual void setPosition(float _x, float _y);
	
	virtual void setX(float _x);
	virtual void setY(float _y);
	virtual void setZ(float _z);
	
	virtual void setOffset(float _x, float _y, float _z=0);
	virtual void setOffset(ofVec3f _newoffset);
	
	virtual void setAnchorPoint(float _x, float _y, float _z=0);
	virtual void setAnchorPoint(ofVec3f _newoffset);	
	
	// Attraction Point
	void setMoveAttractionPoint(float _endx, float _endy, float _endz, float _strength=0.1, float _drag=0.6);
	void stopMoveAttraction();
	void setRotationAttractionAngles(float _xrot, float _yrot, float _zrot, float _force, bool _inverse=false);
	void stopRotationAttraction();	
	
	void setSpeed(ofVec3f _dir, float _drag=-1){setSpeed(_dir.x, _dir.y, _dir.z, _drag);};
	void setSpeed(float _x, float _y, float _z, float _drag=-1);
	
	void addSpeed(ofVec3f _dir, float _drag=-1){addSpeed(_dir.x, _dir.y, _dir.z, _drag);};
	void addSpeed(float _x, float _y, float _z, float _drag=-1);
	
	
	// Size and Scale
	virtual void setSize(float _width, float _height);	
	
	// scale set (ofNode inherit)
	// void setScale(float s);
	// void setScale(float sx, float sy, float sz);
	// void setScale(const ofVec3f& s);
	
	// Color and Alpha and BlendFactors
	virtual void setAlpha(float _a);
	virtual void setColor(float _r, float _g, float _b);
	virtual void setColor(ofColor _c);
	virtual void setNormalizedColor(ofColor _c);
	virtual void setRandomColor();
	void setBlendFactors(float _sfactor, float _dfactor);
    
	// Rotation
	// orientation (ofNode inherit)
	// void setOrientation(const ofQuaternion& q);			// set as quaternion
	// void setOrientation(const ofVec3f& eulerAngles);	// or euler can be useful, but prepare for gimbal lock
	
	using ofNode::setOrientation;
	void setOrientation(const ofQuaternion&	q, bool _inverse);
	void setOrientation(float _xangle, float _yangle, float _zangle);
	
	
	//helpful rotation methods (ofNode inherit)
	
	// void tilt(float degrees);						// tilt up+down (around local x axis)
	// void pan(float degrees);						// rotate left+right (around local y axis)
	// void roll(float degrees);						// roll left+right (around local z axis)
	// void rotate(const ofQuaternion& q);				// rotate by quaternion
	// void rotate(float degrees, const ofVec3f& v);	// rotate around arbitrary axis by angle
	// void rotate(float degrees, float vx, float vy, float vz);
	
	
	// Depreacated 
	//virtual void setRotation(float _xangle, float _yangle, float _zangle, bool _inverse=false);
	//virtual void setRotation(ofQuaternion _newquat, bool _inverse=false);
    //virtual void setRotationGL(float _xangle, float _yangle, float _zangle);
	
	
	ofVec3f getOrientationAxisAngles();
	
	void addRotation(float _xrot, float _yrot, float _zrot);
	void setRotationSpeed(float _xrot, float _yrot, float _zrot, float _drag=-1);
	void addRotationSpeed(float _xrot, float _yrot, float _zrot, float _drag=-1);
	void setRotationDrag(float _drag);
	
    //getters
	
	//ofVec3f getPosition() const;
	//float getX() const;
	//float getY() const;
	//float getZ() const;
	
	ofVec3f getOffset();
	ofVec3f getAnchorPoint();
	
	// float getPitch() const;
	// float getHeading() const;
	// float getRoll() const;
	// ofQuaternion getOrientationQuat() const;
	// ofVec3f getOrientationEuler() const;
	
	ofVec3f getOrientationAngles() const;
	
    float getAlpha();
	float getWidth();
	float getHeight();
	
	ofColor getColor();
    
	//tweened
	void moveTo(float _endx, float _endy, float _endz, float _movetime);
	void fadeTo(float _endalpha, float _fadetime);
	void growTo(float _endwidth, float _endheight, float _growtime);
	void scaleTo(float _endxscale, float _endyscale,float _endzscale, float _scaletime);
	void uniformScaleTo(float _endscale, float _scaletime);
	void colorTo(float _endr, float _endg, float _endb, float _colortime);
	void colorTo(ofColor _color, float _colortime);
	void rotateTo(float _x, float _y, float _z, float _slerptime);
    void rotateTo(ofQuaternion _quat, float _slerptime);
    
    
	// Tweener events;
	virtual void onStart(tween::TweenerParam& param);
	virtual void onStep(tween::TweenerParam& param);
	virtual void onComplete(tween::TweenerParam& param);

    
    // Tweener Params
    
    tween::Tweener tweener;
	tween::TweenerParam moveParam;
	tween::TweenerParam rotateParam;
	tween::TweenerParam scaleParam;	
	tween::TweenerParam growParam;
	tween::TweenerParam fadeParam;
	tween::TweenerParam colorParam;
	tween::TweenerParam visibleParam;
    
    // Events:
	BasicScreenObjectEvent myEventArgs;
	
	ofEvent<BasicScreenObjectEvent> moveToStartEvent;
	ofEvent<BasicScreenObjectEvent> moveToStepEvent;
	ofEvent<BasicScreenObjectEvent> moveToCompleteEvent;
	
	ofEvent<BasicScreenObjectEvent> rotateToStartEvent;
	ofEvent<BasicScreenObjectEvent> rotateToStepEvent;
	ofEvent<BasicScreenObjectEvent>	rotateToCompleteEvent;
	
	ofEvent<BasicScreenObjectEvent> scaleToStartEvent;
	ofEvent<BasicScreenObjectEvent> scaleToStepEvent;
	ofEvent<BasicScreenObjectEvent> scaleToCompleteEvent;
	
	ofEvent<BasicScreenObjectEvent> growToStartEvent;
	ofEvent<BasicScreenObjectEvent> growToStepEvent;
	ofEvent<BasicScreenObjectEvent> growToCompleteEvent;
	
	ofEvent<BasicScreenObjectEvent> fadeToStartEvent;
	ofEvent<BasicScreenObjectEvent> fadeToStepEvent;
	ofEvent<BasicScreenObjectEvent> fadeToCompleteEvent;
	
	ofEvent<BasicScreenObjectEvent> colorToStartEvent;
	ofEvent<BasicScreenObjectEvent> colorToStepEvent;
	ofEvent<BasicScreenObjectEvent> colorToCompleteEvent;
		
	ofEvent<BasicScreenObjectEvent> killEvent;
	ofEvent<BasicScreenObjectEvent> hideEvent;
	ofEvent<BasicScreenObjectEvent> showEvent;

	
	ofColor pickingNameToColor(GLint _pickingName);
	GLint colorToPickingName(ofColor& _color);
	
	
	
	// Positioners
	void addPositioner(string _name, IPositioner* _positioner );
	bool removePositioner(string _name);
	IPositioner* getPositioner(string _name);
	bool hasPositioner(string _name);

protected:
    
	/********************************************************
	 *
	 *	GENERAL
	 *
	 ********************************************************/
	
	long age;
    int myid;
	string myname;
	
	bool issetup; // TODO: issetup needed??
    bool isupdating;
    bool isadded;
	bool isvisible;
    bool isinteractive;
	bool isorderbyz;
	
	
	/********************************************************
	 *
	 *	POSITIONING, SCALING, COLOR
	 *
	 ********************************************************/
	
	ofVec3f endposition;
	float tweenx, tweeny, tweenz;
	float tweenscalex, tweenscaley, tweenscalez;
	
	
    ofVec3f offset;
	ofVec3f anchorpoint;
	
	
	float width, height;
	ofRectangle bounding;
	
	// Move
    ofVec3f speed;
	ofVec3f accel;
	float movedrag;
	float moveattractionforce;
	void doMove();
	
	//Rotation
	
	ofVec3f around;
	
	ofQuaternion qx;
	ofQuaternion qy;
	ofQuaternion qz;
	
	float tweenrotslerp;	
	ofQuaternion startquat;
	ofQuaternion endquat;
	
	ofVec3f rotationspeed;
	ofVec3f rotationaccel;
	float rotationdrag;
	
    // Rotation Attraction
    ofQuaternion rotationattractionquat;
	ofVec3f rotationattractionangles;
	float rotationattractionforce;
    void doRotate();
	
	// Color
	ofColor color;
	float tweenr, tweeng, tweenb;
	float alpha;	
	
    // Screenobjects:
    BasicScreenObject* root;
    BasicScreenObject* parent_so;
    BasicScreenObject* maskobject;
	vector <BasicScreenObject*> childlist;
	
	// ofNode callbacks
	virtual void onPositionChanged();
	virtual void onOrientationChanged();
	virtual void onScaleChanged();
	
	// map of active positioners
	map<string, IPositioner*> positioners;
	map<string,IPositioner*>::iterator positioner;
	
    
private:
	
	//BasicScreenObject(const BasicScreenObject &cSource);
	//BasicScreenObject& operator=(const BasicScreenObject& cSource);
	
    void setRoot(BasicScreenObject* _root);
    
    // killing
	ofxTimer killingtimer;
	void killingAfterTimer(ofEventArgs &event);
	
    //visbility
	ofxTimer visibletimer;
	void hideAfterTimer(ofEventArgs &event);
	
	//variables
	bool hasmask;
	bool ismask;
	int masktype;
	
	bool depthtestenabled;
	bool depthtestbefore;
	
	bool lightingenabled;
	bool lightingbefore;
	
 	float sfactor;
	float dfactor;
    
  
	
	GLint pickingName;
	
};

	
	
	/*
    
protected:
	

	// Rotationstuff
	ofxMatrix4x4 mymatrix;
	ofQuaternion nowquat;
		
	// Matrix
	ofxMatrix4x4 myglmodelviewmatrix;
	ofxMatrix4x4 myglparentmodelviewmatrix;
	ofxMatrix4x4 myglprojectionmatrix;
		
	double glmodelmatrix[16];
	double glprojectionmatrix[16];
	int glviewport[4];
	GLdouble zpos;
	
	static msaColor pickingNameToColor(GLint _pickingName);
	static GLint colorToPickingName(msaColor& _color);
	
    */
	


#endif