#pragma once
#include <iostream>
#include "Resource.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace YEngine {
	class Shader
	{
		
	private:
		YEngine::shaderType m_vertexType;
		shaderType m_fragmentType;
		GLuint m_programId;
	public:
		Shader(shaderType vertex, shaderType fragment);
		~Shader();
		inline GLuint getProgram() const {
			return m_programId;
		}
	void useProgram();
		void setMat4(const std::string&,glm::mat4&);

	
	};
}
