#include "Model.h"

void YEngine::Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void YEngine::Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);

}

YEngine::Mesh YEngine::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{

	std::vector<vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<texture> textures;
	vertices.reserve(mesh->mNumVertices);
	textures.reserve(5); // 5 
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {

		vertex n_vertex;
		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		n_vertex.position = vec;
		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		n_vertex.normal = vec;
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 tex;
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
			n_vertex.texCoords = tex;
		}
		else
			n_vertex.texCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(n_vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	std::cerr <<mesh->mMaterialIndex << std::endl;
	if (mesh->mMaterialIndex >= 0) {

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return {vertices,indices,textures};
	
}

std::vector<YEngine::texture> YEngine::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,const std::string& typeName)
{

	std::vector<texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		if (loaded_textures.find(str.C_Str()) != loaded_textures.end()) {

			textures.push_back(loaded_textures[str.C_Str()]);
			skip = true;
		}
		if (!skip) {
			texture l_texture;
			l_texture.id = Texture::TextureFromFile(str.C_Str(), m_directory);
			l_texture.type = typeName;
			loaded_textures[str.C_Str()] = l_texture;
			textures.push_back(l_texture);
		}
	}
	return textures;

}
