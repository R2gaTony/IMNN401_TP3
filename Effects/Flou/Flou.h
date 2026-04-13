#pragma once

#include "EffectGL.h"

#include "Texture2D.h"

class Flou : public EffectGL
{
public:



	Flou(string name);

	
	~Flou();



	virtual void apply(FrameBufferObject* src, FrameBufferObject* target);

	virtual void animate(const float elapsedTime);


	virtual void FlouInterface() {};


protected:
	GLProgram* vp;
	GLProgram* fp;
	GLuint l_Texture, l_constante;
	

};