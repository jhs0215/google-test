#version 330 core

struct TLight
{
	int nLightType; // 0:Directional, 1:Point, 2:Point(Attenuation), 3:Spotlight
	
	vec3 aLightDir;
	vec3 aLightPos;
	vec3 aAttenuation; // x:Constant, y:Linear, z:Quadratic
	float fCutOff;
	float fCutOffOuter;

	vec3 aAmbient;
	vec3 aDiffuse;
	vec3 aSpecular;
};

struct TMaterial
{
	vec3 aAmbient; // The value must be 'vec3(1.f)'
	vec3 aDiffuse; // The value must be 'vec3(1.f)'
	vec3 aSpecular; // The value must be 'vec3(1.f)'
	float fShininess;

	sampler2D DiffuseTex2D;
	sampler2D SpecularTex2D;
	sampler2D EmissionTex2D;
};

out vec4 FragColor;

in vec3 aFragPos;
in vec3 aFragNormal;
in vec2 aFragTexcel;

uniform TLight tLight;
uniform TMaterial tMaterial;

vec3 GetDirectionalLight()
{
	vec3 aAmbientColor = tLight.aAmbient * tMaterial.aAmbient * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(-tLight.aLightDir);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = tLight.aDiffuse * fDiffuse * tMaterial.aDiffuse * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), tMaterial.fShininess);
	vec3 aSpecularColor = tLight.aSpecular * fSpecular * tMaterial.aSpecular * texture(tMaterial.SpecularTex2D, aFragTexcel).rgb;

	vec3 aEmissionColor = texture(tMaterial.EmissionTex2D, aFragTexcel).rgb;

	return (aAmbientColor + aDiffuseColor + aSpecularColor + aEmissionColor);
}

vec3 GetPointLight()
{
	vec3 aAmbientColor = tLight.aAmbient * tMaterial.aAmbient * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(tLight.aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = tLight.aDiffuse * fDiffuse * tMaterial.aDiffuse * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), tMaterial.fShininess);
	vec3 aSpecularColor = tLight.aSpecular * fSpecular * tMaterial.aSpecular * texture(tMaterial.SpecularTex2D, aFragTexcel).rgb;

	vec3 aEmissionColor = texture(tMaterial.EmissionTex2D, aFragTexcel).rgb;

	return (aAmbientColor + aDiffuseColor + aSpecularColor + aEmissionColor);
}

vec3 GetPointLightAttenuation()
{
	float fDistance = length(tLight.aLightPos - aFragPos);
	float fAttenuation = 1.f / (tLight.aAttenuation.x + tLight.aAttenuation.y * fDistance + tLight.aAttenuation.z * fDistance * fDistance);

	vec3 aAmbientColor = tLight.aAmbient * tMaterial.aAmbient * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(tLight.aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = tLight.aDiffuse * fDiffuse * tMaterial.aDiffuse * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), tMaterial.fShininess);
	vec3 aSpecularColor = tLight.aSpecular * fSpecular * tMaterial.aSpecular * texture(tMaterial.SpecularTex2D, aFragTexcel).rgb;

	return fAttenuation * (aAmbientColor + aDiffuseColor + aSpecularColor);
}

vec3 GetSpotLight()
{	
	float fDistance = length(tLight.aLightPos - aFragPos);
	float fAttenuation = 1.f / (tLight.aAttenuation.x + tLight.aAttenuation.y * fDistance + tLight.aAttenuation.z * fDistance * fDistance);

	vec3 aAmbientColor = tLight.aAmbient * tMaterial.aAmbient * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(tLight.aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = tLight.aDiffuse * fDiffuse * tMaterial.aDiffuse * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), tMaterial.fShininess);
	vec3 aSpecularColor = tLight.aSpecular * fSpecular * tMaterial.aSpecular * texture(tMaterial.SpecularTex2D, aFragTexcel).rgb;
	
	float fTheta = dot(aLightDir, aNormal);
	float fEpsilon = tLight.fCutOff - tLight.fCutOffOuter;
	float fIntensity = clamp((fTheta - tLight.fCutOffOuter) / fEpsilon, 0.f, 1.f);

	return fAttenuation * fIntensity * (aAmbientColor + aDiffuseColor + aSpecularColor);
}

void main()
{
	vec3 result = vec3(0.f);
	if(tLight.nLightType == 0)
		result = GetDirectionalLight();
	else if(tLight.nLightType == 1)
		result = GetPointLight();
	else if(tLight.nLightType == 2)
		result = GetPointLightAttenuation();
	else if(tLight.nLightType == 3)
		result = GetSpotLight();
	else
		result = vec3(1.f);

	FragColor = vec4(result, 1.f);
}