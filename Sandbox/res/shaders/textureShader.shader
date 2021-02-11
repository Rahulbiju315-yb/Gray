~VertexShader

#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

void main()
{
	TexCoord = inTexCoord;
	gl_Position = vec4(inPos.x, inPos.y, 0, 1);
}

~FragmentShader

#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    vec4 col = texture(tex, TexCoord);
    col.a = 1;
    //col = vec4(1);
	FragColor = col;
}