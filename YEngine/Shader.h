#pragma once
#include <iostream>
#include <unordered_map>
#include "Resource.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG(x) std::cout << x << std::endl
namespace YEngine {
	class Shader
	{
    		
	private:
		static GLuint activeShader;
		YEngine::shaderType m_vertexType;
		shaderType m_fragmentType;
		GLuint m_programId;
		std::unordered_map<std::string,GLuint>uniformLoc;
	public:
		Shader(shaderType vertex, shaderType fragment);
		~Shader();
		inline constexpr GLuint getProgram() const {
			return m_programId;
		}
	    void useProgram();
		void setMat4fv(const glm::mat4& mat,const std::string& uniform);
		void setMat3fv(const glm::mat3& mat, const std::string& uniform);
		void setVec3f(const glm::vec3& vec , const std::string& uniform);
		void setScalar1f(GLfloat val, const std::string& uniform);
	};
}
