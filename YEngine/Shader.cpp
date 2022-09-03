#include "Shader.h"

YEngine::Shader::Shader(shaderType vertex, shaderType fragment) :m_vertexType(vertex), m_fragmentType(fragment)
{

    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vSource = YEngine::Resource::getShaderSource(vertex).c_str();
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
    const GLchar* fSource = YEngine::Resource::getShaderSource(fragment).c_str();
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
YEngine::Shader::~Shader()
{
    glDeleteProgram(m_programId);
}
void YEngine::Shader::useProgram()
{
    glUseProgram(m_programId);
}

