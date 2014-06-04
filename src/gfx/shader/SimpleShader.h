#ifndef __HONDO_SIMPLESHADER_H__
#define __HONDO_SIMPLESHADER_H__
class SimpleShader;
#include "ShaderProgram.h"
#include <glm/glm.hpp>
class SimpleShader {
  private:
    ShaderProgram shader_program;
    const GLuint colorID;
    const GLuint mvpMatID;
  public:
    SimpleShader(); 
    void operator()();
    void stop();
    void setMVP(glm::mat4 mvpMat);
};
#endif
