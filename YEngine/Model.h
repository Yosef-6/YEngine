#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace YEngine {
	class Model
	{
	public:
		
		Model(const std::string& path)
		{
			this->loadModel(path);
		}
		inline void Draw(Shader* shader) {
			for (GLuint i = 0; i < m_meshes.size(); i++)
				m_meshes[i].draw(shader);
		}
	private:
		/* Model Data */
		std::vector<Mesh>m_meshes;
		std::unordered_map<std::string,texture>loaded_textures;
		std::string m_directory;
		/* Functions */
		void loadModel(const std::string &path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	};
}