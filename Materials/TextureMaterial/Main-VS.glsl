#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform vec3 posLum;
uniform vec3 posCam;


 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 textures;
layout (location = 4) in vec4 tangeante;
out val{
    vec2 uv;
    vec3 L;
    vec3 V;
};





void main()
{
    vec3 T = normalize(vec3(Model * tangeante));
    vec3 N = normalize(vec3(Model * vec4(Normal, 0.0)));

    T = normalize(T - dot(T, N) * N);

    vec3 B = cross(N, T);
    mat3 TBN = mat3(T, B, N);

    L = (posLum - Position) * transpose(TBN);
    V =  (posCam - Position) * transpose(TBN);

    gl_Position = Proj * View* Model * vec4(Position,1.0);
    uv = textures.xy;   
}