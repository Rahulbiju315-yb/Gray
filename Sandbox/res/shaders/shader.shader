~VertexShader

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 invModel;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(inPos, 1.0f));
	//FragPos = vec3(vec2(inTexCoord), 0);

	TexCoord = vec2(inTexCoord);
	Normal = mat3(transpose(invModel)) * inNormal;

	gl_Position = projection * view * vec4(FragPos, 1.0f);
}

~FragmentShader

#version 330 core

#define NR_SPOT_LIGHTS 4
#define NR_POINT_LIGHTS 10
#define NR_DIRECTIONAL_LIGHTS 1

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;

	float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 viewPos;



struct PointLight
{
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float const_term;
	float lin_term;
	float quad_term;
};

struct DirectionalLight
{
	vec3 dir;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 pos;
	vec3 dir;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float const_term;
	float lin_term;
	float quad_term;
};

uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight[NR_SPOT_LIGHTS];
uniform DirectionalLight dirLight[NR_DIRECTIONAL_LIGHTS];

uniform int nrOfPointLights;
uniform int nrOfSpotLights;
uniform int nrOfDirectionalLights;

vec3 CalcPointLight(PointLight source, vec3 normal, vec3 viewDir)
{
	float d = length(FragPos - source.pos);
	float attenuation = 1.0f / (source.const_term + d * source.lin_term + d * d * source.quad_term);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	ambient = vec3(texture(material.diffuse, TexCoord)) * source.ambient;

	vec3 sourceDir = normalize(source.pos - FragPos);
	float diff = max(dot(normal, sourceDir), 0);
	diffuse = vec3(texture(material.diffuse, TexCoord)) * diff * source.diffuse;

	vec3 reflectDir = normalize(reflect(-sourceDir, normal));
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	specular = vec3(texture(material.specular, TexCoord)) * spec * source.specular;

	return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcDirectionalLight(DirectionalLight source, vec3 normal, vec3 viewDir)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	ambient = vec3(texture(material.diffuse, TexCoord)) * source.ambient;

	vec3 sourceDir = normalize(source.dir);
	float diff = max(dot(normal, sourceDir), 0);
	diffuse = vec3(texture(material.diffuse, TexCoord)) * diff * source.diffuse;

	vec3 reflectDir = normalize(reflect(-sourceDir, normal));
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	specular = vec3(texture(material.specular, TexCoord)) * spec * source.specular;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight source, vec3 normal, vec3 viewDir)
{
	float d = length(FragPos - source.pos);
	float attenuation = 1.0f / (source.const_term + d * source.lin_term + d * d * source.quad_term);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 sourceDir = normalize(source.pos - FragPos);
	ambient = vec3(texture(material.diffuse, TexCoord)) * source.ambient;

	float theta = dot(sourceDir, -normalize(source.dir));
	float epsilon = source.cutOff - source.outerCutOff;
	float intensity = clamp((theta - source.outerCutOff) / epsilon, 0.0, 1.0);

	float diff = max(dot(normal, sourceDir), 0);
	diffuse = vec3(texture(material.diffuse, TexCoord)) * diff * source.diffuse;

	vec3 reflectDir = normalize(reflect(-sourceDir, normal));
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	specular = vec3(texture(material.specular, TexCoord)) * spec * source.specular;

	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular) * attenuation;

}
void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lighting;
	for (int i = 0; i < nrOfPointLights; i++)
		lighting += CalcPointLight(pointLight[i], norm, viewDir);
	
	for (int i = 0; i < nrOfSpotLights; i++)
		lighting += CalcSpotLight(spotLight[i], norm, viewDir);

	for (int i = 0; i < nrOfDirectionalLights; i++)
		lighting += CalcDirectionalLight(dirLight[i], norm, viewDir);

	vec3 emission = vec3(texture(material.emission, TexCoord));

	FragColor = vec4(emission + lighting, 1.0f);
	//FragColor = vec4(1.0f);
}