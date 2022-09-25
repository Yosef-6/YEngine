#include "Mesh.h"


void YEngine::Mesh::draw(Shader* shader)
{     
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < m_textures.size(); i++)
	{
		
		std::stringstream ss;
		std::string number;
		std::string name = m_textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
		shader->setScalar1f((GLfloat)i, ("material." +
			name + number));
	}
	glActiveTexture(GL_TEXTURE0);
	// Draw mesh
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES,m_indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);

}

void YEngine::Mesh::setUpMesh()
{
	GLuint vbo, ebo;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(vertex),
		&this->m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(GLuint), &this->m_indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
		(GLvoid*)offsetof(vertex, normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
		(GLvoid*)offsetof(vertex, texCoords));

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

}
