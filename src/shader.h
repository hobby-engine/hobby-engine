#ifndef _HOBBY_SHADER_H
#define _HOBBY_SHADER_H

#include "typedefs.h"
#include "linmath.h"
#include "color.h"

enum hb_ShaderType {
  hb_SHADER_TYPE_VERTEX,
  hb_SHADER_TYPE_FRAGMENT,
};

struct hb_Shader {
  u32 glId;
};

struct hb_Shader hb_createInternalShader(const char* vertSource, const char* fragSource);
struct hb_Shader hb_loadShader(const char* vertPath, const char* fragPath);
void hb_destroyShader(struct hb_Shader* program);
void hb_useShader(struct hb_Shader* program);

void hb_setShaderF32(struct hb_Shader* program, const char* name, f32 value);
void hb_setShaderVec2(struct hb_Shader* program, const char* name, vec2 value);
void hbesetShaderVec3(struct hb_Shader* program, const char* name, vec3 value);
void hb_setShaderVec4(struct hb_Shader* program, const char* name, vec4 value);
void hb_setShaderMat4(struct hb_Shader* program, const char* name, mat4x4 value);
void hb_setShaderColor(struct hb_Shader* program, const char* name, struct hb_Color value);

#endif
