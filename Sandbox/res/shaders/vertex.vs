~VertexShader

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPos, 1.0f);
	TexCoord = vec2(inTexCoord);
}

~FragmentShader

#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2d tex1;

void main()
{
	FragColor = texture(tex1, TexCoord);
}