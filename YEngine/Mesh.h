#pragma once
#include "Texture.h"
namespace YEngine {

	struct vertex {
		glm::vec3 position;glm::vec3 normal;glm::vec2 texCoords;
	};
	struct texture {
		GLuint id;
		textureType type;
	};
	class Mesh
	{
	public :
		std::vector<vertex>m_vertices;
		std::vector<GLuint>m_indices;
		std::vector<texture>m_textures;

		Mesh(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<texture>& textures) :m_vertices(vertices),m_indices(indices),m_textures(textures){
			setUpMesh();
		}
		void draw(Shader* shader);
	private:
		GLuint m_vao;
		void setUpMesh();
	};
}

