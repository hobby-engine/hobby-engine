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
} hb_Shader;

hb_Shader hb_createInternalShader(const char* vertSource, const char* fragSource);
hb_Shader hb_loadShader(const char* vertPath, const char* fragPath);
void hb_destroyShader(hb_Shader* program);
void hb_useShader(hb_Shader* program);

void hb_setShaderF32(hb_Shader* program, const char* name, f32 value);
void hb_setShaderVec2(hb_Shader* program, const char* name, vec2 value);
void hbesetShaderVec3(hb_Shader* program, const char* name, vec3 value);
void hb_setShaderVec4(hb_Shader* program, const char* name, vec4 value);
void hb_setShaderMat4(hb_Shader* program, const char* name, mat4x4 value);

#endif
