#pragma once
#include <iostream>
#include <sstream>
#include<SOIL2.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace YEngine {

	class Texture {

	private:
		GLint m_textures;
		GLuint* m_texturesId;
		GLuint m_programId;
	public:
		Texture(const char** textures, GLint numTextures, GLuint programId);
		~Texture();
		void bindTextures();
		inline void setProgram(GLuint m_programId) {
			this->m_programId = m_programId;
		}
	};




}