#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform float elapsedTime;


 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 0) out vec4 Color;



void main()
{
    gl_Position = Proj * View* Model * vec4(Position +Normal * abs(sin(elapsedTime)) / 100,1.0) ;
	Color = vec4( Normal,1.0);
}