#version 330 core
in vec4 pos;
in vec3 vertexNormal;
in vec3 fragmentPosition;

out vec4 color;

uniform vec3 uColor = vec3(0.5,0.0,0.5);
float specularStrength = 1.0;
float ambientColorEnv = 0.5;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

//sterowanie œwiatlem
uniform bool ambientBool;
uniform bool diffuseBool;
uniform bool specularBool;
void main()
{

	float ambientColor = ambientColorEnv;
	vec3 normalNormalized = normalize(vertexNormal);
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	float diffuse = max(dot(normalNormalized, lightDirection), 0.0);
	vec3 diffuseColor = diffuse * lightColor;
	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalNormalized);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 64);
	vec3 specularColor = specularStrength * specular * lightColor;

	if(!ambientBool) ambientColor = 0.0;
	if(!diffuseBool) diffuseColor = vec3(0.0,0.0,0.0);
	if(!specularBool) specularColor = vec3(0.0,0.0,0.0);


	color = vec4(uColor * (ambientColor + diffuseColor+specularColor), 1.0);



}
