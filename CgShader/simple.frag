#version 130

in vec3 vert;
in vec3 vertNormal;
in vec4 light;

uniform vec4 mycolor;
uniform vec4 lightColor;
uniform vec4 matAmbientColor;

uniform vec4 matDiffuseColor;

uniform vec4 matSpecularColor;
uniform float specShininess;

uniform int lighting;

void main() {
   if (lighting == 1) {
      float k_a = 0.8;
      float k_d = 0.1;
      float k_s = 0.1;

      vec4 ambient =  k_a * lightColor * matAmbientColor;
      vec4 intensity = ambient;
      vec4 L = vec4(vert, 1.0) - light;
      vec4 N = vec4(vert, 1.0) + vec4(vertNormal, 0.0);

      float L_N = dot(L, N);
      vec4 diffuse =  k_d * max(L_N, 0.0) * lightColor * matDiffuseColor;

      float length_L = length(L);
      vec4 H = L / length_L;
      vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
      if (L_N >= 0) {
         specular =  k_s * pow(max(dot(H, N), 0.0), specShininess) * lightColor * matSpecularColor;
      }
      intensity = intensity + diffuse + specular;
      gl_FragColor = intensity;
   } else {
      gl_FragColor = mycolor;
   }
}