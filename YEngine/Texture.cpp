#include "Texture.h"

YEngine::Texture::Texture(const std::string & loc, const std::string& sampler) :m_textureId(0),m_sampler(sampler) {

   
        glGenTextures(1,&m_textureId);
        unsigned char* image;

        int width = -1, height = -1;
        image = SOIL_load_image(loc.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        if (width < 0 || height < 0) {
            std::cerr << loc << " cant be loaded " << '\n';
            isInit = false;
        }
        else
        { 
            //2d config 
            glBindTexture(GL_TEXTURE_2D, m_textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
            SOIL_free_image_data(image);
            glBindTexture(GL_TEXTURE_2D, 0);
            isInit = true;
        }

}
GLuint YEngine::Texture::TextureFromFile(const std::string& rel, const std::string& dir)
{
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char* image = SOIL_load_image((dir + '/' + rel).c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}
bool YEngine::Texture::attachTexture(Shader* shader)
{

    GLint unit = shader->activeUnit();
    if (unit < 0) {
        std::cerr << " No Active unit Found " << '\n';
        return false;
    }
    
    if (!shader->getLoc(m_sampler).has_value()) {
        std::cerr << " uniform with " << m_sampler<<" not found in this shader instance" << '\n';
        return false;
    }
  
    GLint loc = shader->getLoc(m_sampler).value();
    auto& [Unit,Loc] = m_texInfo[shader->getProgram()];
    Unit = unit;  Loc = loc;
    std::cout << unit << "    " << loc << "\n";
    return true;
}
YEngine::Texture::~Texture()
{
    glDeleteTextures(1,&m_textureId);
}
void YEngine::Texture::bindTexture()
{
    GLuint prog = Shader::getActiveProgram();

    if (m_texInfo.find(prog) != m_texInfo.end()) {

       const auto& [unit, loc] = m_texInfo[prog];
       glActiveTexture(GL_TEXTURE0+unit);
       glBindTexture(GL_TEXTURE_2D,m_textureId);
       glUniform1i(loc, unit);
    }
}
