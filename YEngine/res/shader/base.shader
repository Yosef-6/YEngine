#shader begin
#shader vertex
#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCord;
out vec3 Normal;
out vec2 texCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
out vec3 fragPos;
void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	Normal = normalMatrix * normal;
	fragPos = vec3(model * vec4(position.xyz, 1.0f));
	texCoords = texCord;
}
#shader fragment
#version 410 core
out vec4 color;
in  vec3 Normal;     // normal vec in world
in  vec3 fragPos;    //frag position in world
in  vec2 texCoords;
uniform vec3 viewPos; 
//Dir light
#define NR_POINT_LIGHTS 4
struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight {
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3  ambient;
	vec3  diffuse;
	vec3  specular;
};
struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct Material{

	sampler2D diffuse;     // diffuse map specfic diffuse color for each fragment          
	sampler2D specular;    // sets the color impact a specular light has on the object
	sampler2D emission;
	float shiny;            // impacts the scattering / radius of the specular highlight.
};
vec3 CalcDirLight( DirLight light , vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
void main() {
 
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 output = CalcDirLight(dirLight,normal,viewDir);
	for (int i = 0; i < 4; i++) 
		output += CalcPointLight(pointLights[i], normal, fragPos, viewDir);	
	output += CalcSpotLight(spotLight,normal,fragPos,viewDir);
	color = vec4(output, 1.0f);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {

	vec3 lightDir  = normalize(-light.direction);
	float diff     = max(dot(normal, lightDir), 0.0f);
	vec3 reflectDir= reflect(-lightDir, normal);
	float spec     = pow(max(dot(viewDir,reflectDir),0.0f), material.shiny);

	vec3 ambient   = light.ambient * vec3(texture(material.diffuse,texCoords));
	vec3 diffuse   = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3 specular  = light.specular* spec * vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir     = normalize(light.position - fragPos);
	float diff        = max(dot(normal, lightDir), 0.0f);
	vec3 reflectDir   = reflect(-lightDir,normal);
	float spec        = pow(max(dot(viewDir, reflectDir), 0.0f), material.shiny);
	float distance    = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient      = light.ambient * vec3(texture(material.diffuse,texCoords));
	vec3 diffuse      = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3 specular     = light.specular* spec * vec3(texture(material.specular, texCoords));

	ambient           *= attenuation;
	diffuse           *= attenuation;
	specular          *= attenuation;

	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiny);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular,texCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
#shader lightFragment
#version 410 core
out vec4 color;
uniform vec3 lampColor;
void main() {
	color = vec4(lampColor,1.0f);
}
#shader end