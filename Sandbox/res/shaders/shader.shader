~VertexShader

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec2 TexCoord;
out vec3 Normal_;
out vec3 FragPos_;

uniform mat4 model;
uniform mat4 invModel;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos_ = vec3(model * vec4(inPos, 1.0f));
	TexCoord = vec2(inTexCoord);
	Normal_ = mat3(transpose(invModel)) * inNormal;

	gl_Position = projection * view * vec4(FragPos_, 1.0f);
}

~FragmentShader

#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

uniform Material material;

in vec2 TexCoord;
in vec3 Normal_;
in vec3 FragPos_;

out vec4 FragColor;

uniform sampler2D Tex1;

uniform vec3 light;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal_);
	vec3 lightDir = normalize(lightPos - FragPos_);
	vec3 viewDir = normalize(viewPos - FragPos_);
	vec3 reflectDir = normalize(reflect(-lightPos, norm));

	float diff = max(dot(norm, lightDir), 0.0f);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32);

	vec3 diffuse = diff * material.diffuse * light;
	vec3 specular = spec * material.specular * light;
	vec3 ambient = material.ambient * light;

	//FragColor = texture(Tex1, TexCoord) * vec4((ambient + diffuse + specular), 1.0f);
	FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f) * vec4((ambient + diffuse + specular), 1.0f);
}