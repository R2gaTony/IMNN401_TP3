#version 460


uniform sampler2D myFBO;
uniform int k;

in vec2 uv;
layout (location = 0) out vec4 Color;
void main()
{
	vec3 c = vec3(0,0,0);
	
	ivec2 size = textureSize(myFBO,0);
	int compteur = 0;

	for(int i = -k; i <= k; i++){
		vec2 offset = vec2(0, i) / vec2(size);
		c = c + texture(myFBO, uv.xy + offset).rgb;
		compteur++;

	}

	Color = vec4(c.rgb/compteur,1.0);
}