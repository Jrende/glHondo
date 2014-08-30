#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GL/glew.h>

RenderObject::RenderObject(std::shared_ptr<VertexArray> vertex_array, Mesh mesh):
  vertex_array(vertex_array),
  mesh(mesh),
  model_matrix(),
  pos(0, 0, 0),
  scale_val(1, 1, 1),
  rot()
{
}

void RenderObject::render() const {
  vertex_array->render(mesh);
}

RenderObject::RenderObject(const RenderObject& other):
    vertex_array(other.vertex_array),
    model_matrix(other.model_matrix),
    mesh(other.mesh)
{
  std::cout << "RenderObject copy constructor called" << std::endl;
}

void RenderObject::bind_material(SimpleShader& simple_shader) const {
  simple_shader.set_diffuse_sampler(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh.material.diffuse_map);
}

void RenderObject::translate(const glm::vec3& pos) {
  //model_matrix = glm::translate(model_matrix, pos);
  this->pos += pos;
}

void RenderObject::scale(const glm::vec3& scale) {
  //model_matrix = glm::scale(model_matrix, scale);
  this->scale_val *= scale;
}

void RenderObject::rotate(float angle, const glm::vec3& axis) {
  rot = glm::rotate(rot, angle, axis);
}

const glm::mat4& RenderObject::get_model_matrix() {
  model_matrix = glm::mat4(1.0f);
  model_matrix = glm::translate(model_matrix, pos);
  model_matrix = glm::scale(model_matrix, scale_val);
  model_matrix = model_matrix * glm::mat4_cast(rot);
  return model_matrix;
}

void RenderObject::set_position(const glm::vec3& pos) {
  this->pos = pos;
}
