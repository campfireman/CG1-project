#version 130  

in vec3 vertex;
in vec3 normal;

out vec3 vert;
out vec3 vertNormal;
out vec4 light;


    uniform mat4 projMatrix;
    uniform mat4 lookAtMatrix;
    uniform mat4 modelviewMatrix;
    uniform mat3 normalMatrix;
    uniform vec4 lightpos;

    void main() {
       vert = vertex.xyz;
      vec4 vert4=vec4(vertex,1.0);  
      light = projMatrix * lookAtMatrix * lightpos;
       vertNormal = normalMatrix * normal;
       gl_Position = projMatrix * modelviewMatrix * vert4;
    }

