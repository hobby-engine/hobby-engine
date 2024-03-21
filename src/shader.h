#ifndef _HOBBY_SHADER_H
#define _HOBBY_SHADER_H

#include "basic_types.h"
#include "linmath.h"

typedef enum {
  hb_SHADER_TYPE_VERTEX,
  hb_SHADER_TYPE_FRAGMENT,
} hb_ShaderType;

typedef struct {
  u32 glId;
  hb_ShaderType type;
  const char* path;
} hb_Shader;

typedef struct {
  u32 glId;
  hb_Shader* vertex;
  hb_Shader* fragment;
} hb_ShaderProgram;

hb_Shader* hb_createShader(const char* source, hb_ShaderType type);
hb_Shader* hb_loadShader(const char* path, hb_ShaderType type);
void hb_compileShader(hb_Shader* shader);
hb_Shader* hb_createAndCompileShader(const char* source, hb_ShaderType type);
hb_Shader* hb_loadAndCompileShader(const char* path, hb_ShaderType type);
void hb_destroyShader(hb_Shader* shader);

hb_ShaderProgram hb_createShaderProgram();
void hb_addShaderToProgram(hb_ShaderProgram* program, hb_Shader* shader);
void hb_linkProgram(hb_ShaderProgram* program);
hb_ShaderProgram hb_createAndLinkShaderProgram(hb_Shader* vert, hb_Shader* frag);
hb_ShaderProgram hb_createShaderProgramFromSources(
    const char* vertSource, const char* fragSource);
hb_ShaderProgram hb_loadShaderProgram(const char* vertPath, const char* fragPath);
void hb_destroyShaderProgram(hb_ShaderProgram* program);
void hb_useShaderProgram(hb_ShaderProgram* program);

void hb_setShaderProgramFloat(hb_ShaderProgram* program, const char* name, f32 value);
void hb_setShaderProgramVec2(hb_ShaderProgram* program, const char* name, vec2 value);
void hb_setShaderProgramVec3(hb_ShaderProgram* program, const char* name, vec3 value);
void hb_setShaderProgramVec4(hb_ShaderProgram* program, const char* name, vec4 value);
void hb_setShaderProgramMat4(hb_ShaderProgram* program, const char* name, mat4x4 value);

#endif
