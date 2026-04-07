#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform float elapsedTime;
uniform vec3 posLum;
uniform vec3 posCam;


 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 2) in vec3 ColorIn;
layout (location = 0) out vec3 Color;
layout (location = 1) out vec3 L;
layout (location = 2) out vec3 V;
layout (location = 3) out vec3 N;





void main()
{  
    L = posLum - Position;
    V = posCam - Position;
    N = Normal;
    
    gl_Position = Proj * View* Model * vec4(Position +Normal * abs(sin(elapsedTime)) / 100,1.0);
    Color = ColorIn;
    
}