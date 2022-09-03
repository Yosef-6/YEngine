#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
namespace YEngine {

	enum class shaderType {
		NONE,
		VERTEX_SHADER,
		FRAGMENT_SHADER
	};

	
	class Resource
	{
	public:
		Resource(const Resource&) = delete;
		static std::string getShaderSource(shaderType type);
		void init();
		Resource();
	private:
		
		int loadShaderConf(const std::string& filename);
		static std::unordered_map <shaderType, std::string> m_shaderSource;

	};
}

