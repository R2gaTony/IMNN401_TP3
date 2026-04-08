
#include "TextureMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/include/glfw3.h>
#include <Texture2D.h>


TextureMaterial::TextureMaterial(string name, Texture2D *texture1, Texture2D *texture2, Texture2D *texture3) :
	MaterialGL(name)
{

	vp = new GLProgram(MaterialPath + "TextureMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "TextureMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

	m_Texture1 = texture1;
	m_Texture2 = texture2;
	m_Texture3 = texture3;

	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
	l_PosLum = glGetUniformLocation(vp->getId(), "posLum");
	l_PosCam = glGetUniformLocation(vp->getId(), "posCam");

	l_TextureHandle1 = glGetUniformLocation(fp->getId(), "textureHandle1");
	l_TextureHandle2 = glGetUniformLocation(fp->getId(), "textureHandle2");
	l_TextureHandle3 = glGetUniformLocation(fp->getId(), "textureHandle3");

	//m_Texture1->makeResident();
	glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle1, m_Texture1->getHandle());
	//m_Texture2->makeResident();
	glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle2, m_Texture2->getHandle());
	//m_Texture3->makeResident();
	glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle3, m_Texture3->getHandle());


}

TextureMaterial::~TextureMaterial()
{

}

void TextureMaterial::render(Node* o)
{


	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}


void TextureMaterial::animate(Node* o, const float elapsedTime)
{
	/**********************************************
	*
	* TP 2 - A completer
	Calculer et Transmettre les matrices Model View et Proj au shaders
	- Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
	- Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv

	****************************************************/
	//totalTime += elapsedTime / 100;
	double time = glfwGetTime();

	auto view = scene->camera()->getViewMatrix();
	auto proj = scene->camera()->getProjectionMatrix();
	auto model = o->frame()->getModelMatrix();
	auto posLum = o->frame()->convertPtFrom(glm::vec3(0, 0, 0), scene->getNode("Light")->frame());
	auto posCam = o->frame()->convertPtFrom(glm::vec3(0, 0, 0), scene->camera()->frame());

	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(proj));
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));
	glProgramUniform3fv(vp->getId(), l_PosLum, 1, glm::value_ptr(posLum));
	glProgramUniform3fv(vp->getId(), l_PosCam, 1, glm::value_ptr(posCam));
	//m_Texture1->makeResident();
	//glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle1, m_Texture1->getHandle());
	//m_Texture2->makeResident();
	//glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle2, m_Texture2->getHandle());
	//m_Texture3->makeResident();
	//glProgramUniformHandleui64ARB(fp->getId(), l_TextureHandle3, m_Texture3->getHandle());



	/*********************************************/


}
