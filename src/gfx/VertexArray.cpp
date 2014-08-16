#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>

#include "VertexArray.hpp"

VertexArray::VertexArray(std::shared_ptr<std::vector<float>> vertex_data, std::shared_ptr<std::vector<unsigned int>> index_data, unsigned int size, std::vector<unsigned int> attribute_sizes):
  vertex_count(size),
  attribute_sizes(attribute_sizes),
  vertex_data(vertex_data),
  index_data(index_data)
{
  init();
  flip();
}


VertexArray::VertexArray(const VertexArray& other):
  vertex_count(other.vertex_count),
  attribute_sizes(other.attribute_sizes),
  vertex_data(other.vertex_data),
  attr_size_sum(other.attr_size_sum),
  vao_id(other.vao_id),
  vbo_id(other.vbo_id),
  index_buf_id(other.index_buf_id)
{
  std::cout << "Invoked copy constructor of VertexArray" << std::endl;
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  glDeleteBuffers(1, &index_buf_id);
}

void VertexArray::init() {
  attr_size_sum = 0;
  for(unsigned int& i: attribute_sizes)
    attr_size_sum += i;

  glGenVertexArrays(1, &vao_id);
  glGenBuffers(1, &vbo_id);
  glGenBuffers(1, &index_buf_id);
}

void VertexArray::flip(void) {
  int data_size = attr_size_sum * vertex_count * sizeof(float);

  glBindVertexArray(vao_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, data_size, vertex_data->data(), GL_STATIC_DRAW);

  int pointer = 0;
  for(unsigned int i = 0; i < attribute_sizes.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attribute_sizes[i], GL_FLOAT, GL_TRUE, attr_size_sum * sizeof(float), (void*)(pointer * sizeof(float)));
    pointer += attribute_sizes[i];
    glDisableVertexAttribArray(i);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data->size() * sizeof(unsigned int), index_data->data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::bind() {
  glBindVertexArray(vao_id);
  for(unsigned int i = 0; i < attribute_sizes.size(); i++)
    glEnableVertexAttribArray(i);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  is_bound = true;
}

void VertexArray::render(Mesh mesh) {
  glDrawElementsBaseVertex(GL_TRIANGLES, mesh.end - mesh.start, GL_UNSIGNED_INT, (void*) (mesh.start * 4L), 0);
}

void VertexArray::render_array(GLuint mode) {
  glDrawArrays(mode, 0, vertex_count);
}

void VertexArray::unbind() {
  for(unsigned int i = 0; i < attribute_sizes.size(); i++)
    glDisableVertexAttribArray(i);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  is_bound = false;
}
