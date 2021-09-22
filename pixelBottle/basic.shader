#shader vertex
#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

uniform float uScale;

void main()
{
	// gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
	gl_Position = vec4(vPos * uScale, 1.0);

	fColor = vColor;
	fTexCoord = vTexCoord;
}


#shader fragment
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