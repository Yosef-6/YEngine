#pragma once
#include <iostream>
#include <sstream>
#include <SOIL2.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>


#include "Shader.h"



namespace YEngine {

	enum class textureType{
		TEXTURE_2D = 0x0DE1,
		TEXTURE_3D = 0x806F
	};
 
	class Texture {

	private:
		GLuint m_textureId;
		std::string m_sampler;
		bool isInit;
	    std::unordered_map<GLuint,std::tuple<GLint,GLint>> m_texInfo; //targetShader, unit, sampler Location 
	public:
		Texture(const std::string& loc,const std::string & sampler = "");
		bool attachTexture(Shader *);
		~Texture();

		inline constexpr const std::string& getSampler() const {
			return m_sampler;
		}
		inline constexpr bool getStatus() {
			return isInit;
		}
		void bindTexture();
	};
}