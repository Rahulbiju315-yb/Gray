~VertexShader

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec2 TexCoord;
out vec3 pos;

out float TexSel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	pos = inPos;

	TexCoord = vec2(inTexCoord);
}

~FragmentShader

#version 330 core

in vec2 TexCoord;
in vec3 pos;

in float TexSel;

out vec4 FragColor;

uniform sampler2D Tex1;
uniform vec3 light;

void main()
{
	FragColor = vec4(light, 1.0f);//vec4(1.0f, 1.0f, 1.0f, 1.0f);
}