#include "Resource.h"


std::unordered_map <YEngine::shaderType, std::string>  YEngine::Resource::m_shaderSource;
YEngine::Resource YEngine::Resource::m_resourceInstance;

int YEngine::Resource::loadShaderConf(const std::string& filename) {

 


    std::ifstream file(filename);
    std::stringstream source;
    std::string buffer;
    shaderType currentShader = shaderType::NONE;
    file.exceptions(std::ifstream::badbit); //set up atry catch
    if (file.is_open()) {

        while (std::getline(file, buffer)) {

            if (buffer.find("#shader") != std::string::npos) {

                if (currentShader != shaderType::NONE) {

                    m_shaderSource[currentShader] = source.str();
                    currentShader = shaderType::NONE;
                    source.str(std::string());
                }

                if (buffer.find("vertex") != std::string::npos)
                    currentShader = shaderType::VERTEX_SHADER;
                else if (buffer.find("fragment") != std::string::npos)
                    currentShader = shaderType::FRAGMENT_SHADER;
                else if (buffer.find("lightFragment") != std::string::npos)
                    currentShader = shaderType::LIGHT_FRAGMENT_SHADER;
                else if (buffer.find("end") != std::string::npos)
                    break;

            }
            else
                source << buffer << '\n';

        }
        file.close();

        std::cout << " loaded ->" << filename << std::endl;;
        return 1;
    }
    std::cerr << "unable to open file:" << filename << '\n';
    return 0;
}

std::optional<std::string> YEngine::Resource::getShaderSource(shaderType type) // optionale
{
   
    if (m_shaderSource.find(type) != m_shaderSource.end())
        return m_shaderSource.at(type);
    return {};

}
void YEngine::Resource::init()
{
    loadShaderConf("res/shader/base.shader");

}
