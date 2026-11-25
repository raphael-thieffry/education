uniform mat4 modelview;
uniform mat4 transform;
uniform mat3 normalMatrix;
uniform mat4 texMatrix;

uniform vec4 lightPosition; //position de la lumière (given by processing)
uniform vec4 lightColor;    //color of the light (given by processing)

attribute vec2 texCoord;  //coord texture for each point given by processing
attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;

varying vec3 vertNormal;
varying vec4 vertPosition;
varying vec4 vertColor;
varying vec4 vertTexCoord; //coord passed to frag shader

uniform sampler2D wallnmap; //texture passée manuellement
uniform sampler2D texture;  //texture passée dans les beginshape get automatiqument
uniform sampler2D walltex;
uniform sampler2D wallheightmap;

varying int iswall; //si c'est un mur, on utilise la texture de mur
void main() {
  gl_Position = transform * position;    
  vec3 ecPosition = vec3(modelview * position);  
  vec3 ecNormal = normalize(normalMatrix * normal);

  vec3 direction = normalize(lightPosition.xyz - ecPosition);    
  float intensity = max(0.0, dot(direction, ecNormal));

  // Use the parameters above to compute vertColor e.g.
  vertColor = vec4(intensity, intensity, intensity, 1) * color; 
  vertTexCoord = texMatrix * vec4(texCoord, 1.0, 1.0);    

  vertNormal   = normal;
  vertPosition = position;
  vertColor    = color;  
  iswall = int(texture == walltex)    ;
}