struct Directional
{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct Point
{
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

varying vec3 v_FragPos;
varying vec3 v_Normal;
varying vec2 v_TexCoord;

uniform vec3 u_ViewPos;

uniform Directional dirLights[];

uniform Point pointLights[1];

uniform sampler2D u_Texture;

vec3 CalcDirLight(Directional light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
  vec3 norm = normalize(v_Normal);
  vec3 viewDir = normalize(u_ViewPos - v_FragPos);
  vec3 result = vec3(0.0);

  for(int i = 0; i < u_No_Dir_Lights; i++)
  {
    result += CalcDirLight(dirLights[i], norm, viewDir);
  }

  for(int i = 0; i < u_No_Point_Lights; i++)
  {
    result += CalcPointLight(pointLights[i], norm, v_FragPos, viewDir);
  }

  vec4 tex = texture2D(u_Texture, v_TexCoord);

  gl_FragColor = tex * vec4(result, 1.0);
}

vec3 CalcDirLight(Directional light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);

  float diff = max(dot(normal, lightDir), 0.0);

  vec3 ambient = light.ambient;
  vec3 diffuse = light.diffuse * diff;

  return (ambient + diffuse);
}

vec3 CalcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);

  float diff = max(dot(normal, lightDir), 0.0);

  float dist = distance(light.position, fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

  vec3 ambient = light.ambient;
  vec3 diffuse = light.diffuse * diff;

  ambient *= attenuation;
  diffuse *= attenuation;

  return(ambient + diffuse);
}