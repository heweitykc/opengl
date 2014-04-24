//#############################################################################
//  File:      SLSceneView.h
//  Author:    Marcus Hudritsch
//  Date:      February 2014
//  Copyright: 2002-2014 Marcus Hudritsch
//             This software is provide under the GNU General Public License
//             Please visit: http://opensource.org/licenses/GPL-3.0
//#############################################################################

#ifndef SLSCENEVIEW_H
#define SLSCENEVIEW_H

#include <stdafx.h>

#include <SLScene.h>
#include <SLEventHandler.h>
#include <SLRaytracer.h>
#include <SLPathtracer.h>
#include <SLAABBox.h>
#include <SLShape.h>
#include <SLDrawBits.h>
#include <SLAverage.h>
#include <SLGLOculus.h>

//-----------------------------------------------------------------------------
class SLCamera;
class SLGroup;
class SLShape;
class SLLight;
class SLButton;

//-----------------------------------------------------------------------------
//! SceneView class represents a dynamic real time 3D view onto the scene.
/*!      
The SLSceneView class has a pointer to an active camera that is used to 
generate the 3D view into a window of the clients window system. 
OpenGL ES2.0 is used as the lowlevel rendering API. 
All mouse, touch, keyboard, resize and paint events of the window system are 
handled in this class by the appropriate event handler methods.
*/
class SLSceneView: public SLObject
{  friend class SLGroup;
   friend class SLRaytracer;
   friend class SLPathtracer;
   
   public:           
                        SLSceneView       (SLstring name,
                                           SLint screenWidth,
                                           SLint screenHeight,
                                           SLint dotsPerInch);
                       ~SLSceneView       ();

            // Setters
            void        camera            (SLCamera* camera);
            void        scrW              (const SLint  scrW){_scrW = scrW;}
            void        scrH              (const SLint  scrH){_scrH = scrH;} 
            void        waitEvents        (const SLbool wait){_waitEvents = wait;}
            void        dpi               (SLint newDPI);

            // Getters
     inline SLCamera*   camera            () {return _camera;}
     inline SLint       scrW              () {return _scrW;}
     inline SLint       scrH              () {return _scrH;}
     inline SLint       scrWdiv2          () {return _scrWdiv2;}
     inline SLint       scrHdiv2          () {return _scrHdiv2;}
     inline SLfloat     scrWdivH          () {return _scrWdivH;}
     inline SLint       dpi               () {return _dpi;}
     inline SLfloat     dpmm              () {return (float)_dpi/25.4f;}
     inline SLDrawBits* drawBits          () {return &_drawBits;}
            SLuint      doFrustumCulling  () {return _doFrustumCulling;}
            SLfloat     fps               () {return _fps;}
            SLVShape*   blendShapes       () {return &_blendShapes;}
            SLGLOculus* oculus            () {return &_oculus;}   
            SLRaytracer* raytracer        () {return &_raytracer;}
            SLPathtracer* pathtracer      () {return &_pathtracer;}

            // Main event handlers
            void        onInitialize      ();
            SLbool      onPaint           ();
            void        onResize          (const SLint width, const SLint height);
            SLbool      onMouseDown       (const SLMouseButton button, 
                                           SLint x, SLint y,
                                           const SLKey mod);  
            SLbool      onMouseUp         (const SLMouseButton button, 
                                           SLint x, SLint y,
                                           const SLKey mod); 
            SLbool      onMouseMove       (SLint x, SLint y);
            SLbool      onMouseWheelPos   (const SLint wheelPos, const SLKey mod);
            SLbool      onMouseWheel      (const SLint delta, const SLKey mod); 
            SLbool      onTouch2Down      (SLint x1, SLint y1,
                                           SLint x2, SLint y2);
            SLbool      onTouch2Move      (SLint x1, SLint y1,
                                           SLint x2, SLint y2);
            SLbool      onTouch2Up        (SLint x1, SLint y1,
                                           SLint x2, SLint y2);
            SLbool      onDoubleClick     (const SLMouseButton button, 
                                           SLint x, SLint y,
                                           const SLKey mod);
            SLbool      onKeyPress        (const SLKey key, const SLKey mod);
            SLbool      onKeyRelease      (const SLKey key, const SLKey mod);
            void        onRotation        (SLfloat yaw, SLfloat pitch, SLfloat roll);
            SLbool      onCommand         (const SLCmd cmd);
            
            // Drawing subroutines
            SLbool      updateAndDraw3D   (SLfloat elapsedTimeSec);
            SLbool      updateAndRT3D     (SLfloat elapsedTimeSec);
            SLbool      updateAndPT3D     (SLfloat elapsedTimeSec);
            void        draw3DBlended     ();
            SLbool      updateAndDraw2D   (SLfloat elapsedTimeSec);
            
            // Misc.
            void        init              ();
            void        build2DMenus      ();
            void        build2DInfoGL     ();
            void        build2DInfoRT     ();
            void        build2DMsgBoxes   ();
            SLfloat     calcFPS           (SLfloat deltaTimeSec); 
            SLstring    windowTitle       ();
            void        startRaytracing   (SLint maxDepth);
            void        startPathtracing  (SLint maxDepth, SLint samples);
   
   protected:
            SLGLState*  _stateGL;         //!< Pointer to the global SLGLState instance
            SLCamera*   _camera;          //!< Pointer to the _active camera
            SLDrawBits  _drawBits;        //!< Drawing flags for the view

            SLbool      _doDepthTest;     //!< Flag if depth test is turned on
            SLbool      _doMultiSample;   //!< Flag if anti aliasing is on
            SLbool      _waitEvents;      //!< Event waiting if true
            SLbool      _doFrustumCulling;//!< Flag if view frustum culling is on
            SLbool      _showStats;       //!< Flag if stats should be displayed
            SLbool      _showInfo;        //!< Flag if help should be displayed
            
            SLfloat     _fps;             //!< Averaged no. of frames per second
            SLAvgFloat  _frameTimeMS;     //!< Averaged time per frame in ms
            SLAvgFloat  _updateTimeMS;    //!< Averaged time for update in ms
            SLAvgFloat  _cullTimeMS;      //!< Averaged time for culling in ms
            SLAvgFloat  _draw3DTimeMS;    //!< Averaged time for 3D drawing in ms
            SLAvgFloat  _draw2DTimeMS;    //!< Averaged time for 2D drawing in ms
            SLuint      _totalBufferCount;//!< Total NO. of VBOs in last frame
            SLuint      _totalBufferSize; //!< Total size of buffer memory in last frame
            SLuint      _totalDrawCalls;  //!< Total NO. of drawCalls in last frame

            SLbool      _mouseDownL;      //!< Flag if left mouse button is pressed
            SLbool      _mouseDownR;      //!< Flag if right mouse button is pressed
            SLbool      _mouseDownM;      //!< Flag if middle mouse button is pressed
            SLKey       _mouseMod;        //!< mouse modifier key on key down
            SLint       _touchDowns;      //!< finger touche down count
            SLVec2i     _touch[3];        //!< up to 3 finger touch coordinates
            SLGLBuffer  _bufTouch;        //!< Buffer for touch pos. rendering
            SLint       _scrW;            //!< Screen width in pixels
            SLint       _scrH;            //!< Screen height in pixels
            SLint       _scrWdiv2;        //!< Screen half width in pixels
            SLint       _scrHdiv2;        //!< Screen half height in pixels
            SLfloat     _scrWdivH;        //!< Screen side aspect ratio
            SLint       _dpi;             //!< Screen resolution in dots per inch
            SLGLOculus  _oculus;          //!< Oculus Rift interface

            SLAABBox    _aabb;            //!< Axis aligned bounding box of scene
            SLVShape    _blendShapes;     //!< Vector of blended shapes
            
            SLRaytracer _raytracer;       //!< Whitted style raytracer
            SLbool      _doRT;            //!< Flag to render with RT instead GL
            SLbool      _stopRT;          //!< Flag to stop the RT

            SLPathtracer _pathtracer;     //!< Pathtracer
            SLbool      _doPT;            //!< Flag to render with PT instead GL
            SLbool      _stopPT;          //!< Flag to stop the PT 
};
//-----------------------------------------------------------------------------
#endif
