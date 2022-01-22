#include "app.h"
#include "uniform.h"
#include "draw.h"

App::App() {

}

void App::Initialize() {


}

void App::Update(float deltaTime) {

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

}