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

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Tex1;
uniform vec4 color;

void main()
{
	FragColor = texture(Tex1, TexCoord);
}