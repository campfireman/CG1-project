#version 130

in vec3 vert;
in vec3 vertNormal;
in vec4 light;

uniform vec4 mycolor;
uniform vec4 matAmbientColor;
uniform vec4 lightAmbientColor;

uniform vec4 matDiffuseColor;
uniform vec4 lightDiffuseColor;

uniform vec4 matSpecularColor;
uniform vec4 lightSpecularColor;

uniform int lighting;

void main() {
   if (lighting == 1) {
      float k_a = 0.8;
      float k_d = 0.1;
      float k_s = 0.1;

      vec4 ambient =  k_a * matAmbientColor * lightAmbientColor;
      vec4 intensity = ambient;
      vec4 L = vec4(vert, 0.0) - light;
      vec4 N = vec4(vert, 0.0) + vec4(vertNormal, 0.0);
      float angle = dot(L, N);

      if (angle > 0) {
         vec4 diffuse =  k_d * angle * lightDiffuseColor * matDiffuseColor;
         float length_L = length(L);
         vec4 H = L / length_L;
         
         vec4 specular =  k_s * pow(dot(H, N), 5) * matSpecularColor * lightSpecularColor;
         intensity = intensity + diffuse + specular;
      } 
      gl_FragColor = mycolor * intensity;
   } else {
      gl_FragColor = mycolor;
   }
}