#include "Texture.h"

YEngine::Texture::Texture(const char** textures, GLint numTextures, GLuint programId) :m_textures(numTextures), m_texturesId(nullptr), m_programId(programId) {

    m_texturesId = new GLuint[m_textures];
    glGenTextures(m_textures, m_texturesId);
    unsigned char* image;

    for (GLint i = 0; i < m_textures; i++) {
        int width = -1, height = -1;
        image = SOIL_load_image(textures[i], &width, &height, 0, SOIL_LOAD_RGB);
        if (width < 0 || height < 0) {
            std::cerr << " Image " << textures[i] << " cant be loaded " << '\n';
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, m_texturesId[i]);
            // setting 2D  default wraping and filteringoptions  params will be added in the constructor for 3d  configs
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
            SOIL_free_image_data(image);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
YEngine::Texture::~Texture()
{
    glDeleteTextures(m_textures, m_texturesId);
    delete[] m_texturesId;
}
void YEngine::Texture::bindTextures()
{
    std::stringstream sampler;
    for (GLint i = 0; i < m_textures; i++) {
        sampler << "ourTexture" << i + 1;
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_texturesId[i]);
        glUniform1i(glGetUniformLocation(m_programId, sampler.str().c_str()), i);
        sampler.str(std::string());
    }
}