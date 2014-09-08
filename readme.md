# ofxRRScenegraph

This is a collection of classes to fill the need for a simple and versatile basis when creating multitouch applications, originally used with a pq-labs full-hd touchscreen. 

The most important Elements are:
 
## Renderer:
– is the Root of the whole scene graph and provides functionality for picking of interactive objects. 
- Has a ofCamera for global view manipulations
– Works with TUIO or Mouse input
– The picking mechanism is based on FBO color picking, 

## Basic Screen Object:
– Is a super powered element, based on ofNode
– Has functionality for tweened animations (position, size, scale, rotation, color, alpha), parameter restrictions, nested drawing, masking, etc. moveTo, scaleTo, fadeTo etc. 
– Has lots of convenience functionality, like setRandomColor() or killMeSoftly(), moveMeToTop() etc. 

## Basic Interactive Object:
– This Object receives all the multitouch events from the renderer and is drawn in the color picking loop.
– The Multitouch-Actions may be applied directly to the Element itself or to another by setting the MTTarget, can be any BasicScreenObject
– The Object can handle as many multitouchpoints as desired. 
– has info on all multitouchtransforms while multitouch-scope is running, for instance total dragged distance or rotation-speed, etc. 


Everything else is not essential to the scenegraph but very helpful nonetheless:

- TextField, using the marvelous Pango library for Font-Rendering, and the extension the scrollableTextField
- Image, container of an ofImage with great sizing functions
- BasicButton mostly to show how to implement the button functionality
- A simple Shape BaseClass and some shape implementations, very much not finished.

We used this Scenegraph for some Touchscreenapplications successfully. Although the Concept of putting almost all functionality into one magic object may not be the best way build this, but i like it that way, thats why.

Make sure you have all the needed addons linked, the most important ones are included in the libs folder. Some of them are a bit modified. And if using ofxPango, be sure to link to all the needed libraries in header search paths.
 
The Pango version is a fork from roxlu with some added functionality like tabstops. It is hosted under http://www.github.com/robandrose/ofxPango








