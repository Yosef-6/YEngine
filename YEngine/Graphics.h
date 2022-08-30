#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <SOIL2.h>
namespace YEngine {
	
	namespace Graphics {

		enum class shaderType {
			NONE,
			VERTEX_SHADER,
			FRAGMENT_SHADER
		};

		
		class Resource{
		public:
			Resource(const Resource&) = delete;
			const std::string& getShaderSource(shaderType type);
			inline static Resource& getResourceHandle() {
				return m_resourceInstance;
			};
			void init();
		private:
			Resource() {};
			int loadShaderConf(const std::string& filename);
			std::unordered_map <shaderType, std::string> m_shaderSource;
			static Resource m_resourceInstance;
		};

		class Shader {
		private:
			shaderType m_vertexType;
			shaderType m_fragmentType;
			GLuint m_programId;
		public:
			Shader(shaderType vertex,shaderType fragment);
			~Shader();
			inline GLuint getProgram() {
				return m_programId;
			}
			void useProgram();
        };

		class Texture {
           
		private:
			GLint m_textures;
			GLuint *m_texturesId;
			GLuint m_programId;
		public:
			Texture(const char**textures,GLint numTextures,GLuint programId);
			~Texture();
			void bindTextures();
			inline void setProgram(GLuint m_programId) {
				this->m_programId = m_programId;
			}
		};




	}


}
