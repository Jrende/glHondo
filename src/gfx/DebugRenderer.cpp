#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include "DebugRenderer.hpp"

DebugRenderer::DebugRenderer():
  debug_shader(),
  line_shader(),
  vertex_array(
      std::make_shared<std::vector<float>>(std::vector<float>({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})),
      std::make_shared<std::vector<unsigned int>>(std::vector<unsigned int>({0})),
      2,
      {3})
{
  
}

void DebugRenderer::draw_line(const glm::vec3& from, const glm::vec3& to, const glm::mat4& vp_mat) {
  //Optimization opportunity: No need to rebind shader every line
  //Also, vertex_buffer binding might be reusable between line and point
  line_shader();
  line_shader.set_color({1,1,1});
  line_shader.set_MVP(vp_mat);
  line_shader.set_from(from);
  line_shader.set_to(to);
  vertex_array.bind();
  glDrawArrays(GL_POINTS, 0, 1);
  vertex_array.unbind();
  line_shader.stop();
}

void DebugRenderer::draw_point(const glm::vec3& pos, const glm::mat4& vp_mat) {
  debug_shader();
  debug_shader.set_color({1,1,1});
  debug_shader.set_MVP(vp_mat);
  debug_shader.set_pos(pos);
  vertex_array.bind();
  glDrawArrays(GL_POINTS, 0, 1);
  vertex_array.unbind();
  debug_shader.stop();
}