#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

uniform float uScale;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
	// gl_Position = vec4(vPos * uScale, 1.0);
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fColor = vColor;
	fTexCoord = vTexCoord;
}