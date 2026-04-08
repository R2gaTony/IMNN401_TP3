#version 460

layout (location = 0) out vec4 Color;
layout (location = 0) in vec3 inColor;
layout (location = 1) in vec3 L;
layout (location = 2) in vec3 V;
layout (location = 3) in vec3 N;


void main()
{
	vec3 White = vec3(1,1,1);
    vec3 LNorm = normalize(L);
    vec3 VNorm = normalize(V);
    vec3 NNorm = normalize(N);
    vec3 R = reflect(-LNorm, NNorm);

    float angle = max(dot(NNorm,LNorm),0.0);
    vec3 diffuse =  angle * White;      
    
    float forceAmbiant = 0.3;
    vec3 ambiant = forceAmbiant * White;

    vec3 specular = pow(max(dot(R,VNorm),0.0), 32) * White; 

	Color = vec4((diffuse + ambiant + specular) * inColor, 1.0);
}