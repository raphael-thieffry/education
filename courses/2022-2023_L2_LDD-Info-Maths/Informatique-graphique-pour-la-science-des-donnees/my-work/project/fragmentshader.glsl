#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

uniform sampler2D wallnmap;

uniform mat4 modelview;
uniform mat4 transform;
uniform mat3 normalMatrix;
uniform vec4 lightPosition;
uniform vec4 lightColor;

varying vec3 vertNormal;
varying vec4 vertPosition;
varying vec4 vertColor;
varying vec4 vertTexCoord;

uniform sampler2D texture;
uniform sampler2D wallheightmap;

void main() {
    
        
  vec3 p = vec3(modelview * vertPosition);  
  vec3 n =
    normalize(
        (vertNormal+((texture2D(wallnmap, vertTexCoord.st).rgb)*2.0 - 1))
            );

  vec3 dif = lightPosition.xyz - p;
  float lightDist = length(dif);
  vec3 direction = normalize(normalMatrix * dif);    
  float intensity = 3*max(0.0, dot(direction, n));

  vec3 A = normalMatrix*p; //coord dans le repere du triangle ?
  //gestion height map
  float Aaltitude = texture2D(wallheightmap, vertTexCoord.st).rgb[0];
  float Adeepness = (1-Aaltitude);
  vec2 newtexcoord = vertTexCoord.st + direction.st*(-Adeepness);
  newtexcoord.x = newtexcoord.x%texture.width;
  newtexcoord.y = newtexcoord.y%texture.height;
  //gl_FragColor = vertColor;
  gl_FragColor = vec4(texture2D(texture, vertTexCoord.st).rgb*intensity, 1.0); // * vertColor;
   
}