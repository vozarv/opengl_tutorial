#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
  float transparency;
};

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec4 CalcDirLight(DirLight light, Material material, vec3 normal,
                  vec3 viewDir) {

  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

  // combine results
  vec4 ambient = vec4(light.ambient, 1.0) * vec4(material.diffuse, 1.0);
  vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(material.diffuse, 1.0);
  vec4 specular = vec4(light.specular, 1.0) * spec * vec4(material.specular, 1.0);
  return (ambient + diffuse + specular);
}

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform Material material;
uniform DirLight dirLight;

uniform samplerCube skybox;

void main() {


vec3 normal = texture(texture_normal1, TexCoords).rgb;
normal = normalize(normal * 2.0 - 1.0);

vec3 color = texture(texture_diffuse1, TexCoords).rgb;
vec3 ambient = 0.1 * color;
    
    
vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
float diff = max(dot(lightDir, normal), 0.0);
vec3 diffuse = diff * color;

vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
vec3 reflectDir = reflect(-lightDir, normal);
vec3 halfwayDir = normalize(lightDir + viewDir);  
float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

vec3 specular = vec3(0.2) * spec;
FragColor = vec4(ambient + diffuse + specular, 1.0);




// vec3 viewDir = normalize(viewPos - FragPos);




//   vec4 result = CalcDirLight(dirLight, material, norm, viewDir);

//   vec3 reflectDir = reflect(-viewDir, norm);
//   float ratio = 1.00 / 1.52;
//   vec3 refractDir = refract(-viewDir, norm, ratio);

//   // background reflection
//   vec4 reflection = texture(skybox, reflectDir);
//   vec4 refraction = texture(skybox, refractDir);

// //   if (material.transparency < 0.1) {
// //     discard;
// //   }

//   //FragColor = result;
//   //FragColor = vec4(reflectDir, 1.0);
//   //FragColor = 0.98 * result + 0.02 * reflection;
//   //FragColor = texture(texture_diffuse1, TexCoords);
//   FragColor = texture(texture_specular1, TexCoords);
  //FragColor = texture(skybox, vec3(FragPos.x, FragPos.y, FragPos.z));

}