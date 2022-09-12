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
in  vec3 Normal;
in  vec3 fragPos;
in  vec2 texCoords;
uniform vec3 lightPos;
uniform vec3 viewPos;
// definig a material color for each lighting componenets
//material property for an object
struct Light {
	vec3 position;
	vec3 ambient;  
	vec3 diffuse;  // diffuse component of a light source is usually set to the exact color we’d like a light to have; often a bright white color
	vec3 specular; //The specular component is usually kept at vec3(1.0f) shining at full intensity
};
struct Material{

	sampler2D diffuse;     // diffuse map specfic diffuse color for each fragment          
	sampler2D specular;    // sets the color impact a specular light has on the object
	sampler2D emission;
	float shiny;            // impacts the scattering / radius of the specular highlight.
};
uniform Material material;
uniform Light light;
void main() {
	//So each material property of the object is returned with full intensity for each of the light’s
	//components.
	//lights ambient intensity componenet   
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,texCoords));

	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	//float shiny = 2;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiny);
	
	vec3 specular = light.specular * spec * vec3(texture (material.specular,texCoords)) ;
	
	vec3 emission = vec3(texture (material.emission, texCoords));
	
	color = vec4((ambient + diffuse + specular + emission), 1.0f);
}
#shader lightFragment
#version 410 core
out vec4 color;
void main() {
	color = vec4(1.0f);
}
#shader end