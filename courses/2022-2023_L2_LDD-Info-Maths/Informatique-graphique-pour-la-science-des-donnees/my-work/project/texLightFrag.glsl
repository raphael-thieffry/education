/*
  Part of the Processing project - http://processing.org
  Copyright (c) 2012-21 The Processing Foundation
  Copyright (c) 2004-12 Ben Fry and Casey Reas
  Copyright (c) 2001-04 Massachusetts Institute of Technology
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, version 2.1.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

uniform sampler2D texture;

uniform vec2 texOffset;

varying vec4 vertTexCoord;
varying vec4 vertPosition;
varying vec3 vertNormal;

attribute vec3 normal;
attribute vec4 color;
attribute vec4 ambient;
attribute vec4 specular;
attribute vec4 emissive;
attribute float shininess;

varying float fragshininess;
varying vec4 fragcolor;
varying vec4 fragambient;
varying vec4 fragspecular;
varying vec4 fragemissive;


uniform sampler2D wallnmap;

uniform int lightCount;
uniform vec4 lightPosition[8];
uniform vec3 lightNormal[8];
uniform vec3 lightAmbient[8];
uniform vec3 lightDiffuse[8];
uniform vec3 lightSpecular[8];      
uniform vec3 lightFalloff[8];
uniform vec2 lightSpot[8];

uniform mat4 modelviewMatrix;
uniform mat3 normalMatrix;
uniform mat4 transformMatrix;
uniform mat4 texMatrix;

const float zero_float = 0.0;
const float one_float = 1.0;
const vec3 zero_vec3 = vec3(0);

int ftoi(float f) {
  highp int index = int(f);
  return index;
}


float falloffFactor(vec3 lightPos, vec3 vertPos, vec3 coeff) {
  vec3 lpv = lightPos - vertPos;
  vec3 dist = vec3(one_float);
  dist.z = dot(lpv, lpv);
  dist.y = sqrt(dist.z);
  return one_float / dot(dist, coeff);
}

float spotFactor(vec3 lightPos, vec3 vertPos, vec3 lightNorm, float minCos, float spotExp) {
  vec3 lpv = normalize(lightPos - vertPos);
  vec3 nln = -one_float * lightNorm;
  float spotCos = dot(nln, lpv);
  return spotCos <= minCos ? zero_float : pow(spotCos, spotExp);
}

float lambertFactor(vec3 lightDir, vec3 vecNormal) {
  return max(zero_float, dot(lightDir, vecNormal));
}

float blinnPhongFactor(vec3 lightDir, vec3 vertPos, vec3 vecNormal, float shine) {
  vec3 np = normalize(vertPos);
  vec3 ldp = normalize(lightDir - np);
  return pow(max(zero_float, dot(ldp, vecNormal)), shine);
}


void main() {
    vec3 n =
    normalize(
        (normalMatrix*vertNormal+normalMatrix*((texture2D(wallnmap, vertTexCoord.st).rgb)*2.0 - 1))
            );
    vec3 p = vec3(modelviewMatrix * vertPosition);  // coordonnées dans le repère de la caméra
    float intensityperso = 1;
    /* for (int i = 0; i < 8; i++) {
      if (lightCount == i) break;
      vec3 dif = (modelviewMatrix*lightPosition[i]).xyz - p;
      vec3 direction = normalize(normalMatrix*dif);   
      intensityperso += 1.5*max(0.0, dot(direction, n));
    } */

    vec3 trucPourRemplacerEcVertex = p;
    vec3 trucPourRemplacerEcNormal = n;
    vec3 trucPourRemplacerEcNormalInv = -n;

    // Light calculations
  vec3 totalAmbient = vec3(0, 0, 0);
  
  vec3 totalFrontDiffuse = vec3(0, 0, 0);
  vec3 totalFrontSpecular = vec3(0, 0, 0);
  
  vec3 totalBackDiffuse = vec3(0, 0, 0);
  vec3 totalBackSpecular = vec3(0, 0, 0);
  
  for (int i = 0; i < 8; i++) {
    if (lightCount == i) break;
    
    vec3 lightPos = lightPosition[i].xyz;
    bool isDir = lightPosition[i].w < one_float;
    float spotCos = lightSpot[i].x;
    float spotExp = lightSpot[i].y;
    
    vec3 lightDir;
    float falloff;    
    float spotf;
      
    if (isDir) {
      falloff = one_float;
      lightDir = -one_float * lightNormal[i];
    } else {
      falloff = falloffFactor(lightPos, trucPourRemplacerEcVertex, lightFalloff[i]);  
      lightDir = normalize(lightPos - trucPourRemplacerEcVertex);
    }
  
    spotf = spotExp > zero_float ? spotFactor(lightPos, trucPourRemplacerEcVertex, lightNormal[i], 
                                              spotCos, spotExp) 
                                 : one_float;
    
    if (any(greaterThan(lightAmbient[i], zero_vec3))) {
      totalAmbient       += lightAmbient[i] * falloff;
    }
    
    if (any(greaterThan(lightDiffuse[i], zero_vec3))) {
      totalFrontDiffuse  += lightDiffuse[i] * falloff * spotf * 
                            lambertFactor(lightDir, trucPourRemplacerEcNormal);
      totalBackDiffuse   += lightDiffuse[i] * falloff * spotf * 
                            lambertFactor(lightDir, trucPourRemplacerEcNormalInv);
    }
    
    if (any(greaterThan(lightSpecular[i], zero_vec3))) {
      totalFrontSpecular += lightSpecular[i] * falloff * spotf * 
                            blinnPhongFactor(lightDir, trucPourRemplacerEcVertex, trucPourRemplacerEcNormal, fragshininess);
      totalBackSpecular  += lightSpecular[i] * falloff * spotf * 
                            blinnPhongFactor(lightDir, trucPourRemplacerEcVertex, trucPourRemplacerEcNormalInv, fragshininess);
    }     
  }   


  vec4 fragColor =     vec4(totalAmbient, 0) * fragambient + 
                  vec4(totalFrontDiffuse, 1) * fragcolor + 
                  vec4(totalFrontSpecular, 0) * fragspecular + 
                  vec4(fragemissive.rgb, 0);

  vec4 backVertColor = vec4(totalAmbient, 0) * fragambient + 
                  vec4(totalBackDiffuse, 1) * fragcolor + 
                  vec4(totalBackSpecular, 0) * fragspecular + 
                  vec4(fragemissive.rgb, 0);

  /* //position camera
  vec3 cameraPosition = vec3(0,0,0);
  vec3 cameraDirection = normalize(p - cameraPosition); //direction frag -> camera

  vec3 direction = normalize(normalMatrix*cameraDirection); //direction frag -> camera dans le repere du triangle
    //gestion de la hauteur
  float Aaltitude = texture2D(wallheightmap, vertTexCoord.st).r;
  float Adeepness = (1-Aaltitude);
  vec2 newtexcoord = vertTexCoord.st + direction.st*(-Adeepness);
  vec2 shape = textureSize(texture, 2);
  newtexcoord.x = ftoi(newtexcoord.x)%ftoi(shape.x);
  newtexcoord.y = ftoi(newtexcoord.y)%ftoi(shape.y);  //gestion profondeur mais deconne quand on regarde en arrière, voir une autre methode
 */


 // gl_FragColor =  vec4(texture2D(texture, vertTexCoord.st).rgb*intensity, 1.0)* (gl_FrontFacing ? vertColor : backVertColor);
  gl_FragColor = vec4(intensityperso*texture2D(texture, vertTexCoord.st).rgb, 1) * (gl_FrontFacing ? fragColor : backVertColor);
}