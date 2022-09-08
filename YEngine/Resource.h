#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
namespace YEngine {

	enum class shaderType {
		NONE =0,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		LIGHT_FRAGMENT_SHADER
	};

	
	class Resource
	{
	public:
		Resource(const Resource&) = delete;
		static std::optional<std::string> getShaderSource(shaderType type);
		void init();
		constexpr inline static Resource& getHandle(){
			return m_resourceInstance;
		}
	private:
		Resource() {};
		int loadShaderConf(const std::string& filename);
		static std::unordered_map <shaderType, std::string> m_shaderSource;
		static Resource m_resourceInstance;
	};
}

