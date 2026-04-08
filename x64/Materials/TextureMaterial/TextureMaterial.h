
#ifndef _TextureMaterial_
#define _TextureMaterial_


#include <Texture2D.h>
#include "MaterialGL.h"

class TextureMaterial : public MaterialGL
{
public:

	//Attributs

	//Constructeur-Destructeur

	/**
		Constructeur de la classe à partir du nom du matériau
		@param name : nom du matériau
	*/
	TextureMaterial(string name = "", Texture2D *texture1 = nullptr, Texture2D *texture2 = nullptr, Texture2D *texture3 = nullptr);

	/**
		Destructeur de la classe
	*/
	~TextureMaterial();

	//Méthodes

	/**
		Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
		@param o : Node/Objet pour lequel on veut effectuer le rendu
	*/
	virtual void render(Node* o);

	/**
		Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
		@param o : Node/Objet concerné par le rendu
		@param elapsedTime : temps écoulé depuis la dernière frame
	*/
	virtual void animate(Node* o, const float elapsedTime);


	virtual void displayInterface() {};


protected:
	GLProgram* vp;
	GLProgram* fp;

	GLuint l_View, l_Proj, l_Model, l_Time, l_PosLum, l_PosCam, l_TextureHandle1, l_TextureHandle2, l_TextureHandle3;
	Texture2D* m_Texture1;
	Texture2D* m_Texture2;
	Texture2D* m_Texture3;

	float totalTime;
};

#endif