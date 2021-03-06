#ifndef HONDO_DEBUGSHADER_HPP
#define HONDO_DEBUGSHADER_HPP
class DebugShader;
#include "gfx/shader/ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class DebugShader {
  private:
    ShaderProgram shader_program;
    const GLuint pos_id, color_id, mvp_mat_id, mode_id;
  public:
    DebugShader(); 
    void operator()();
    void stop();
    void set_pos(const glm::vec3& pos);
    void set_color(const glm::vec3& color);
    void set_MVP(const glm::mat4& mvpMat);
    void set_mode(const float& mode);
};
#endif

