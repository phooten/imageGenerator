#version 330 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform sampler2D uTex0;

void main()
{
	
	//FragColor = vec4(fColor, 1.0f);
	FragColor = texture(uTex0, fTexCoord);
	
}