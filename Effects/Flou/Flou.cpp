
#include "Flou.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>


Flou::Flou(string name) :
	EffectGL(name)
{
	tmp = new FrameBufferObject();

	vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(EffectPath + "Flou/Flou-FS.glsl", GL_FRAGMENT_SHADER);
	fph = new GLProgram(EffectPath + "Flou/FlouHorizontal-FS.glsl", GL_FRAGMENT_SHADER);
	fpv = new GLProgram(EffectPath + "Flou/FlouVertical-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->link();
	m_ProgramPipeline->printInfoLog();

	l_Texture = glGetUniformLocation(fp->getId(), "myFBO");
	l_constante = glGetUniformLocation(fp->getId(), "k");

}

Flou::~Flou()
{

}

void Flou::apply(FrameBufferObject* src, FrameBufferObject* target)
{

	
	// note the most efficient but here for usability purposes (could be set up in the constructor if src is constant)
	glProgramUniformHandleui64ARB(fph->getId(), l_Texture, src->getColorTexture()->getHandle());
	glProgramUniform1i(fph->getId(), l_constante, 10);
	glProgramUniform1i(fpv->getId(), l_constante, 10);
	
	// Passe 1
	tmp->enable();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_ProgramPipeline->useProgramStage(fph, GL_FRAGMENT_SHADER_BIT);
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();
	tmp->disable();

	// Passe 2
	glProgramUniformHandleui64ARB(fpv->getId(), l_Texture, tmp->getColorTexture()->getHandle());
	m_ProgramPipeline->useProgramStage(fpv, GL_FRAGMENT_SHADER_BIT);

	if (target)
		target->enable();

	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ProgramPipeline->bind();
	drawQuad();	
	m_ProgramPipeline->release(); 
	if (target)
		target->disable();

}
void Flou::animate( const float elapsedTime)
{


}
