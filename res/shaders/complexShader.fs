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

vec4 CalcDirLight(DirLight light, Material material, vec3 normal, vec3 viewDir,
                  vec2 texCoord) {
  vec3 lightDir = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // combine results
  vec4 ambient = vec4(light.ambient, 1.0) * texture(material.diffuse, texCoord);
  vec4 diffuse =
      vec4(light.diffuse, 1.0) * diff * texture(material.diffuse, texCoord);
  vec4 specular =
      vec4(light.specular, 1.0) * spec * texture(material.specular, texCoord);
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

vec4 CalcPointLight(PointLight light, Material material, vec3 normal,
                    vec3 fragPos, vec3 viewDir, vec2 texCoord) {
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
  vec4 ambient = vec4(light.ambient, 1.0) * texture(material.diffuse, texCoord);
  vec4 diffuse =
      vec4(light.diffuse, 1.0) * diff * texture(material.diffuse, texCoord);
  vec4 specular =
      vec4(light.specular, 1.0) * spec * texture(material.specular, texCoord);
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}

struct SpotLight {
  int state;
  vec3 direction;
  float cutOff;
  float outerCutOff;
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec4 CalcSpotLight(SpotLight light, Material material, vec3 normal,
                   vec3 fragPos, vec3 viewDir, vec2 texCoord) {

  vec4 ambient = vec4(light.ambient, 1.0) * texture(material.diffuse, texCoord);

  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0);
  vec4 diffuse = vec4(light.diffuse, 1.0) * diff * texture(material.diffuse, texCoord);

  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec4 specular =
      vec4(light.specular, 1.0) * spec * texture(material.specular, texCoord);

  // spotlight (soft edges)
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity =
      light.state * clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  diffuse *= intensity;
  specular *= intensity;

  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

// END OF LIGHT CALCULATIONS ***

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform DirLight dirLight;
#define NR_POINT_LIGHTS 1 // TODO add uniform value
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform vec3 viewPos;
uniform SpotLight spotLight;

uniform Material material;

void main() {

  // properties
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  // phase 1: Directional lighting
  vec4 result = CalcDirLight(dirLight, material, norm, viewDir, TexCoord);

  // phase 2: Point lights
  for (int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], material, norm, FragPos, viewDir,
                             TexCoord);

  // phase 3: Spot light
  result +=
      CalcSpotLight(spotLight, material, norm, FragPos, viewDir, TexCoord);

  vec4 texColor = texture(material.diffuse, TexCoord);
  if(texColor.a < 0.1){
   discard;
  }

  FragColor = result;

  //FragColor = texColor;

}