#version 330 core

// LIGHT CALCULATIONS ***

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec3 CalcDirLight(DirLight light, Material material, vec3 normal, vec3 viewDir, vec2 texCoord) {
  vec3 lightDir = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
  vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
  return (ambient + diffuse + specular);
}

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec3 CalcPointLight(PointLight light, Material material, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texCoord) {
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
  vec3 diffuse =
      light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
  vec3 specular =
      light.specular * spec * vec3(texture(material.specular, texCoord));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}
/*
struct SpotLight {

  int state;
  vec3 direction;
  float cutOff;
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};*/

/*
vec3 CalcSpotLight(Spotlight light, Material material, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 texCoord) {

  vec3 lightDir = normalize(light.position - fragPos);
  float theta = dot(lightDir, normalize(-light.direction));

  if (theta > light.cutOff && state == 1) {

    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse =
        light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular =
        light.specular * spec * vec3(texture(material.specular, texCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
  } 
  
  else return 0;
}
*/
// END OF LIGHT CALCULATIONS ***

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform DirLight dirLight;
#define NR_POINT_LIGHTS 1 // TODO add uniform value
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform vec3 viewPos;
//uniform SpotLight spotLight;

uniform Material material;

//uniform int lampState;

void main() {

  // properties
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  // phase 1: Directional lighting
  vec3 result = CalcDirLight(dirLight, material, norm, viewDir, TexCoord);

  // phase 2: Point lights
  for (int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], material, norm, FragPos, viewDir, TexCoord);

  // phase 3: Spot light
  //result += CalcSpotLight(spotLight, material, norm, FragPos, viewDir, TexCoord);

  FragColor = vec4(result, 1.0);
}