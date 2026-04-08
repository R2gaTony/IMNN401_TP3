#version 460
#extension GL_ARB_bindless_texture: require

layout(bindless_sampler) uniform sampler2D textureHandle1;
layout(bindless_sampler) uniform sampler2D textureHandle3;

layout (location = 0) out vec4 Color;
in val{
    vec2 uv;
    vec3 L;
    vec3 V;
};


void main()
{
    vec4 normal = (texture(textureHandle3, uv) * 2) - 1;
    vec3 N = normalize(normal.xyz);

	vec3 White = vec3(1,1,1);
    vec3 LNorm = normalize(L);
    vec3 VNorm = normalize(V);
    vec3 NNorm = N;
    vec3 R = reflect(-LNorm, NNorm);

    float angle = max(dot(NNorm,LNorm),0.0);
    vec3 diffuse =  angle * White;      
    
    float forceAmbiant = 0.3;
    vec3 ambiant = forceAmbiant * White;

    vec3 specular = pow(max(dot(R,VNorm),0.0), 32) * White;

    vec4 texColor = texture(textureHandle1, uv);

	Color = vec4((diffuse + ambiant + specular) * texColor.xyz, 1.0);
}