#include "app.h"
#include "uniform.h"
#include "draw.h"

App::App() {
	_rotation = 0;
	_shader = nullptr;
	_texture = nullptr;
	_vertexPositions = nullptr;
	_vertexNormals = nullptr;
	_vertexTexCoords = nullptr;
	_indexBuffer = nullptr;
}

void App::Initialize() {
	_rotation = 0.0f;
	_shader = new Shader("Shaders/shader.vert", "Shaders/shader.frag");
	_texture = new Texture("Assets/uv.png");

	_vertexPositions = new Attribute<glm::vec3>();
	_vertexNormals = new Attribute<glm::vec3>();
	_vertexTexCoords = new Attribute<glm::vec2>();
	_indexBuffer = new IndexBuffer();

	std::vector<glm::vec3> positions;
	positions.push_back(glm::vec3(-1, -1, 0));
	positions.push_back(glm::vec3(-1, 1, 0));
	positions.push_back(glm::vec3(1, -1, 0));
	positions.push_back(glm::vec3(1, 1, 0));

	_vertexPositions->Set(positions);

	std::vector<glm::vec3> normals;
	normals.resize(4, glm::vec3(0, 0, 1));
	_vertexNormals->Set(normals);

	std::vector<glm::vec2> uvs;
	uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(1, 1));
	_vertexTexCoords->Set(uvs);

	std::vector<uint32_t > indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
	_indexBuffer->Set(indices);
}

void App::Update(float deltaTime) {
	_rotation += deltaTime * 45.0f;
	while (_rotation > 360.0f) {
		_rotation -= 360.0f;
	}
}

void App::Render(float aspectRatio) {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::toMat4(glm::angleAxis(_rotation * DEG2RAD, glm::vec3(0, 0, 1)));

	_shader->Bind();
	_vertexPositions->BindTo(_shader->GetAttributeIndex("position"));
	_vertexNormals->BindTo(_shader->GetAttributeIndex("normal"));
	_vertexTexCoords->BindTo(_shader->GetAttributeIndex("texCoord"));


	Uniform<glm::mat4>::Set(_shader->GetUniformIndex("model"), model);
	Uniform<glm::mat4>::Set(_shader->GetUniformIndex("view"), view);
	Uniform<glm::mat4>::Set(_shader->GetUniformIndex("projection"), projection);
	Uniform<glm::vec3>::Set(_shader->GetUniformIndex("light"), glm::vec3(0, 0, 1));
	_texture->Set(_shader->GetUniformIndex("tex0"), 0);
	Draw(*_indexBuffer, DrawMode::Triangles);

	_texture->UnSet(0);
	_vertexPositions->UnBind(_shader->GetAttributeIndex("position"));
	_vertexNormals->UnBind(_shader->GetAttributeIndex("normal"));
	_vertexTexCoords->UnBind(_shader->GetAttributeIndex("texCoord"));

	_shader->UnBind();
}

void App::Shutdown() {
	delete _shader;
	delete _texture;
	delete _vertexPositions;
	delete _vertexNormals;
	delete _vertexTexCoords;
	delete _indexBuffer;
}