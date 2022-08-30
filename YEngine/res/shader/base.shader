#shader begin
#shader vertex
#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
out vec3 ourColor;
out vec2 TexCoord;
uniform vec4 c; 
void main(){
	gl_Position = vec4(position.xyz,1.0f);ourColor=color;TexCoord=vec2(1.0f-texCoord.x,texCoord.y);
};
#shader fragment
#version 410 core
in vec3 ourColor;
in vec2 TexCoord;
uniform vec4 c;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
out vec4 color;
void main(){
	color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),c.y);
};
#shader end