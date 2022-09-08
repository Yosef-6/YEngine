#include "Shader.h"

GLuint YEngine::Shader::activeShader = -1; 
YEngine::Shader::Shader(shaderType vertex, shaderType fragment) :m_vertexType(vertex), m_fragmentType(fragment)
{

    std::string source; 
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    if (!YEngine::Resource::getShaderSource(vertex).has_value())
        LOG(" The requested resource not found -> shaderLoadingFailed");
    else
        source = std::move(YEngine::Resource::getShaderSource(vertex).value());

    
    const GLchar* vSource = source.c_str();
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
   
    source = "";
    if (!YEngine::Resource::getShaderSource(fragment).has_value())
        LOG(" The requested resource not found -> shaderLoadingFailed");
    else 
       source = std::move(YEngine::Resource::getShaderSource(fragment).value());
    const GLchar* fSource = source.c_str();
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

    //for now i need the locaion of uniforms
    GLint count;
    glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &count);
    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
    const GLsizei bufSize = 32; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length
    for (GLint i = 0; i < count; i++)
    {
        glGetActiveUniform(m_programId,(GLuint)i, bufSize, &length, &size, &type, name);
        uniformLoc[name] = i;
    }

}
YEngine::Shader::~Shader()
{
    glDeleteProgram(m_programId);
}
void YEngine::Shader::useProgram()
{  

    glUseProgram(m_programId);
    activeShader = m_programId;

}

void YEngine::Shader::setMat4fv(const glm::mat4& mat, const std::string& uniform)
{
    if (activeShader != m_programId)
        useProgram();
    glUniformMatrix4fv(uniformLoc[uniform], 1, GL_FALSE, glm::value_ptr(mat));

}

void YEngine::Shader::setMat3fv(const glm::mat3& mat, const std::string& uniform)
{
    if (activeShader != m_programId)
        useProgram();
    glUniformMatrix3fv(uniformLoc[uniform], 1, GL_FALSE, glm::value_ptr(mat));

}

void YEngine::Shader::setVec3f(const glm::vec3& vec, const std::string& uniform)
{
    if (activeShader != m_programId)
        useProgram();
    glUniform3f(uniformLoc[uniform],vec.x,vec.y,vec.z);

}

void YEngine::Shader::setScalar1f(GLfloat val, const std::string& uniform)
{
    if (activeShader != m_programId)
        useProgram();
    glUniform1f(uniformLoc[uniform],val);
}

