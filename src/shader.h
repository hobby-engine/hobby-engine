#ifndef _HOBBY_SHADER_H
#define _HOBBY_SHADER_H

#include "typedefs.h"
#include "linmath.h"
#include "color.h"

enum ShaderType {
  SHADER_TYPE_VERTEX,
  SHADER_TYPE_FRAGMENT,
};

struct Shader {
  u32 glId;
};

struct Shader createInternalShader(const char* vertSource, const char* fragSource);
struct Shader loadShader(const char* vertPath, const char* fragPath);
void destroyShader(struct Shader* program);
void useShader(struct Shader* program);

void setShaderF32(struct Shader* program, const char* name, f32 value);
void setShaderVec2(struct Shader* program, const char* name, vec2 value);
void setShaderVec3(struct Shader* program, const char* name, vec3 value);
void setShaderVec4(struct Shader* program, const char* name, vec4 value);
void setShaderMat4(struct Shader* program, const char* name, mat4x4 value);
void setShaderColor(struct Shader* program, const char* name, struct Color value);

#endif
