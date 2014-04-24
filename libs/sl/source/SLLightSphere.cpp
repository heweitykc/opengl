//#############################################################################
//  File:      SLLightSphere.cpp
//  Author:    Marcus Hudritsch
//  Date:      February 2014
//  Copyright (c): 2002-2014 Marcus Hudritsch
//             This software is provide under the GNU General Public License
//             Please visit: http://opensource.org/licenses/GPL-3.0
//#############################################################################

#include <stdafx.h>           // precompiled headers
#ifdef SL_MEMLEAKDETECT
#include <nvwa/debug_new.h>   // memory leak detector
#endif

#include "SLLightSphere.h"
#include "SLRay.h"
#include "SLScene.h"
#include "SLSceneView.h"
#include "SLGroup.h"
#include "SLMaterial.h"
#include "SLMesh.h"

//-----------------------------------------------------------------------------
SLLightSphere::SLLightSphere(SLfloat radius) : 
               SLSphere(radius, 16, 16, "Sphere Light")
{  
   _samples.samples(1,1,false);
}
//-----------------------------------------------------------------------------
SLLightSphere::SLLightSphere(SLfloat posx, 
                             SLfloat posy, 
                             SLfloat posz,
                             SLfloat radius,
                             SLfloat ambiPower,
                             SLfloat diffPower,
                             SLfloat specPower) : 
               SLSphere(radius, 16, 16, "Sphere Light"), 
               SLLight(ambiPower, diffPower, specPower)
{  
   _samples.samples(1,1,false);
   translate(posx, posy, posz);
}
//-----------------------------------------------------------------------------
//! shapeInit sets the light id, the light states & creates an emissive mat.
void SLLightSphere::shapeInit(SLSceneView* sv)
{  
   // Check if OpenGL lights are available
   if (SLScene::current->lights().size() >= SL_MAX_LIGHTS) 
      SL_EXIT_MSG("Max. NO. of lights is exceeded!");

   // Add the light to the lights array of the scene
      if (_id==-1)
   {  _id = (SLint)SLScene::current->lights().size();
      SLScene::current->lights().push_back(this);
   }
   
   // Set the OpenGL light states
   SLLightSphere::setState(stateGL);
   stateGL->numLightsUsed = (SLint)SLScene::current->lights().size();
   
   // Automatically create emissive light material (lights do not reflect)
   if (M && M->mat==0)
   {  M->mat = new SLMaterial(_name.c_str(), SLCol4f::BLACK, SLCol4f::BLACK);
      M->mat->emission(_on ? diffuse() : SLCol4f::BLACK);
      SLScene::current->materials().push_back(M->mat);   
   }
   
   SLMesh::shapeInit(sv);
}
//-----------------------------------------------------------------------------
/*!
SLLightSphere::shapeCopy returns a full copy of itself
*/
SLShape* SLLightSphere::shapeCopy()
{  
   // Check if OpenGL lights are available
   if (SLScene::current->lights().size() >= SL_MAX_LIGHTS) 
      SL_EXIT_MSG("Max. NO. of lights is exceeded!");
      
   SLLightSphere* copy = new SLLightSphere(_radius);
   copy->on(_on);
   copy->spotCutoff(_spotCutoff);
   copy->spotExponent(_spotExponent);
   copy->kc(_kc);
   copy->kl(_kl);
   copy->kq(_kq);
   copy->ambient(_ambient);
   copy->diffuse(_diffuse);
   copy->specular(_specular);
   return copy;
}
//-----------------------------------------------------------------------------
/*!
SLLightSphere::shapeDraw sets the light states and calls then the shapeDraw 
method of its mesh.
*/
void SLLightSphere::shapeDraw(SLSceneView* sv)
{  
   if (_id!=-1) 
   {  
      // Set the light state and the no. of lights used
      SLLightSphere::setState(stateGL);
      stateGL->numLightsUsed = (SLint)SLScene::current->lights().size();
   
      // now draw the inherited object
      SLMesh::shapeDraw(sv);
   }
}
//-----------------------------------------------------------------------------
/*!
SLLightSphere::intersect calls the mesh intersection code.
*/
SLbool SLLightSphere::shapeHit(SLRay* ray)
{     
   // do not intersect shadow rays
   if (ray->type==SHADOW) return false;
   
   // only allow intersection with primary rays (no lights in reflections)
   if (ray->type!=PRIMARY) return false;
   
   // call the intersection routine of the mesh   
   return SLMesh::shapeHit(ray);;
}
//-----------------------------------------------------------------------------     
/*!
SLLightSphere::shadowTest returns 0.0 if the hit point is completely shaded and 
1.0 if it is 100% lighted. A return value inbetween is calculate by the ratio 
of the shadow rays not blocked to the total number of casted shadow rays.
*/
SLfloat SLLightSphere::shadowTest(SLRay* ray,         // ray of hit point
                                  const SLVec3f& L,   // vector from hit point to light
                                  SLfloat lightDist)  // distance to light
{  
   if (_samples.samples()==1)
   {  
      // define shadow ray and shoot 
      SLRay shadowRay(lightDist, L, ray);      
      SLScene::current->root3D()->hit(&shadowRay);
      
      if (shadowRay.length < lightDist)
      {  
         // Handle shadow value of transparent materials
         if (shadowRay.hitMat->hasAlpha())
         {  shadowRay.hitShape->preShade(&shadowRay);
            SLfloat shadowTransp = SL_abs(shadowRay.dir.dot(shadowRay.hitNormal));
            return shadowTransp * shadowRay.hitMat->kt();
         }
         else return 0.0f;
      } 
      else return 1.0f;
   } 
   else // do light sampling for soft shadows
   {  
      SLVec3f C(_wm.translation()); // Center of light
      SLVec3f LightX, LightY;       // main axis of sample plane
      SLfloat lighted = 0.0f;       // return value
      SLfloat invSamples = 1.0f/(_samples.samples());
      SLbool  outerCircleIsLighting = true;
      SLbool  innerCircleIsNotLighting = true;

      // Build normalized plain vectors X and Y that are perpendicular to L (=Z)
      if (fabs(L.x) >= fabs(L.y))
      {  SLfloat invLength = 1.0f/sqrt(L.x*L.x + L.z*L.z);
         LightX.set(L.z*invLength, 0, -L.x*invLength);  
      } else
      {  SLfloat invLength = 1.0f/sqrt(L.y*L.y + L.z*L.z);
         LightX.set(0, L.z*invLength, -L.y*invLength); 
      }
      LightY.cross(L,LightX);
      LightY*=_radius;
      LightX*=_radius;
      
      // Loop over radius r and angle phi of light circle
      for (SLint iR=_samples.samplesX()-1; iR>=0; --iR)
      {  for (SLint iPhi=_samples.samplesY()-1; iPhi>=0; --iPhi)
         {  SLVec2f discPos(_samples.point(iR,iPhi));

            // calculate disc position and vector LDisc to it
            SLVec3f conePos(C + discPos.x*LightX + discPos.y*LightY);
            SLVec3f LDisc(conePos - ray->hitPoint);
            LDisc.normalize();

            SLRay shadowRay(lightDist, LDisc, ray);
            
            SLScene::current->root3D()->hit(&shadowRay);

            if (shadowRay.length < lightDist) 
            {  outerCircleIsLighting = false;               
            } else 
            {  lighted += invSamples; // sum up the light
               innerCircleIsNotLighting = false;
            }
         }
         
         // Early break 1: 
         // If the outer circle of shadow rays where not blocked return 1.0
         if (outerCircleIsLighting) return 1.0f;
         
         // Early break 2:
         // If a circle was completely shaded return lighted amount
         if (innerCircleIsNotLighting) return lighted;
         innerCircleIsNotLighting = true;
      }
      return lighted;
   }
}

//-----------------------------------------------------------------------------     
/*!
SLLightSphere::shadowTest returns 0.0 if the hit point is completely shaded and
1.0 if it is 100% lighted. A return value inbetween is calculate by the ratio
of the shadow rays not blocked to the total number of casted shadow rays.
*/
SLbool SLLightSphere::shadowTestMC(SLRay* ray,         // ray of hit point
   const SLVec3f& L,   // vector from hit point to light
   SLfloat lightDist)  // distance to light
{
   if (_samples.samples() == 1)
   {
      // define shadow ray and shoot 
      SLRay shadowRay(lightDist, L, ray);
      SLScene::current->root3D()->hit(&shadowRay);

      if (shadowRay.length < lightDist)
      {
         // Handle shadow value of transparent materials
         if (shadowRay.hitMat->hasAlpha())
         {
            shadowRay.hitShape->preShade(&shadowRay);
            SLfloat shadowTransp = SL_abs(shadowRay.dir.dot(shadowRay.hitNormal));
            return shadowTransp * shadowRay.hitMat->kt();
         }
         else return 0.0f;
      }
      else return 1.0f;
   }
   else // do light sampling for soft shadows
   {
      SLVec3f C(_wm.translation()); // Center of light
      SLVec3f LightX, LightY;       // main axis of sample plane
      SLfloat lighted = 0.0f;       // return value
      SLfloat invSamples = 1.0f / (_samples.samples());
      SLbool  outerCircleIsLighting = true;
      SLbool  innerCircleIsNotLighting = true;

      // Build normalized plain vectors X and Y that are perpendicular to L (=Z)
      if (fabs(L.x) >= fabs(L.y))
      {
         SLfloat invLength = 1.0f / sqrt(L.x*L.x + L.z*L.z);
         LightX.set(L.z*invLength, 0, -L.x*invLength);
      }
      else
      {
         SLfloat invLength = 1.0f / sqrt(L.y*L.y + L.z*L.z);
         LightX.set(0, L.z*invLength, -L.y*invLength);
      }
      LightY.cross(L, LightX);
      LightY *= _radius;
      LightX *= _radius;

      // Loop over radius r and angle phi of light circle
      for (SLint iR = _samples.samplesX() - 1; iR >= 0; --iR)
      {
         for (SLint iPhi = _samples.samplesY() - 1; iPhi >= 0; --iPhi)
         {
            SLVec2f discPos(_samples.point(iR, iPhi));

            // calculate disc position and vector LDisc to it
            SLVec3f conePos(C + discPos.x*LightX + discPos.y*LightY);
            SLVec3f LDisc(conePos - ray->hitPoint);
            LDisc.normalize();

            SLRay shadowRay(lightDist, LDisc, ray);

            SLScene::current->root3D()->hit(&shadowRay);

            if (shadowRay.length < lightDist)
            {
               outerCircleIsLighting = false;
            }
            else
            {
               lighted += invSamples; // sum up the light
               innerCircleIsNotLighting = false;
            }
         }

         // Early break 1: 
         // If the outer circle of shadow rays where not blocked return 1.0
         if (outerCircleIsLighting) return 1.0f;

         // Early break 2:
         // If a circle was completely shaded return lighted amount
         if (innerCircleIsNotLighting) return lighted;
         innerCircleIsNotLighting = true;
      }
      return true;
   }
}

//-----------------------------------------------------------------------------
/*! SLLightRect::setState sets the global rendering state
*/
void SLLightSphere::setState(SLGLState* state)
{  
   if (_id!=-1) 
   {  state->lightIsOn[_id]       = _on;
      state->lightPosWS[_id]      = positionWS();
      state->lightDirWS[_id]      = spotDirWS();           
      state->lightAmbient[_id]    = _ambient;              
      state->lightDiffuse[_id]    = _diffuse;              
      state->lightSpecular[_id]   = _specular;    
      state->lightSpotCutoff[_id] = _spotCutoff;           
      state->lightSpotCosCut[_id] = _spotCosCut;           
      state->lightSpotExp[_id]    = _spotExponent;         
      state->lightAtt[_id].x      = _kc;  
      state->lightAtt[_id].y      = _kl;    
      state->lightAtt[_id].z      = _kq; 
      state->lightDoAtt[_id]      = isAttenuated();
   }
}
//-----------------------------------------------------------------------------
