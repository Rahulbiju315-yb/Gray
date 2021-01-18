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
uniform float kernel[9];

const float offset = 1.0f / 300;
void main()
{
	vec3 output = vec3(0);

	vec2 offsets[9] = vec2[]
	(
		vec2(-offset, offset) , vec2(0, offset) , vec2(offset, offset) ,
		vec2(-offset, 0)	  , vec2(0, 0)      , vec2(offset, 0)      ,
		vec2(-offset, -offset), vec2(0, -offset), vec2(offset, -offset)
	);

	vec3 texColors[9];

	for (int i = 0; i < 9; i++)
		texColors[i] = vec3(texture(tex, TexCoord + offsets[i]));

	for (int i = 0; i < 9; i++)
		output += texColors[i] * kernel[i];
	
	FragColor = vec4(output, 1);
}