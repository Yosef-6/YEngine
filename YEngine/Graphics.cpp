#include "Graphics.h"

// resource
YEngine::Graphics::Resource YEngine::Graphics::Resource::m_resourceInstance;
int YEngine::Graphics::Resource::loadShaderConf(const std::string& filename) {


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

const std::string& YEngine::Graphics::Resource::getShaderSource(shaderType type)
{
    if (m_shaderSource.find(type) != m_shaderSource.end())
        return m_shaderSource.at(type);
    return std::string();

}
void YEngine::Graphics::Resource::init()
{
    m_resourceInstance.loadShaderConf("res/shader/base.shader");

}
// shader

YEngine::Graphics::Shader::Shader(shaderType vertex, shaderType fragment)
{
    m_vertexType = vertex;
    m_fragmentType = fragment;
    Resource& res = Resource::getResourceHandle();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vSource = res.getShaderSource(vertex).c_str();
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);
    // vertex shader compile log
    GLint vSuccess;
    GLchar vInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);

    if (!vSuccess) {

        glGetShaderInfoLog(vertexShader, 512, NULL, vInfoLog);
        std::cerr << " SHADER::VERTEX::COMPILATION FAILED\n" << vInfoLog << '\n';

    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fSource = res.getShaderSource(fragment).c_str();
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);

    GLint fSuccess;
    GLchar fInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);

    if (!fSuccess) {

        glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
        std::cerr << " SHADER::FRAGMENT::COMPILATION FAILED\n" << fInfoLog << '\n';

    }

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShader);
    glAttachShader(m_programId, fragmentShader);
    glLinkProgram(m_programId);

    // check link process
    GLint  linkSuccess;
    GLchar linkInfo[512];
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess) {

        glGetProgramInfoLog(m_programId, 512, NULL, linkInfo);
        std::cerr << " SHADER_PROGRAM::COMPILATION FAILED\n" << linkInfo << '\n';

    }
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}
void YEngine::Graphics::Shader::useShader()
{
    glUseProgram(m_programId);
}