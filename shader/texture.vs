#version 460 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

//* SSBO *//
struct GPU_SSBO
{
	vec4 src;
	vec4 tint;
	mat4 model;
};

layout(std430, binding = 1) buffer GPU_SSBO_buffer
{
	GPU_SSBO common_data[];
};

//* Camera UBO_Shared shared *//
struct GPU_UBO
{
	mat4 ViewProjection;
};

layout(std140, binding = 0) uniform GPU_UBO_buffer_shared
{
	GPU_UBO global_data;
};

//* Texture type UBO_Shared non-shared *//
layout(std140, binding = 1) uniform GPU_UBO_buffer_nonshared
{
	int Type_in;
};

out vec4 tint;
out vec2 TexCoord;
out flat int Type;

void main()
{
	GPU_SSBO common_data =  common_data[gl_InstanceID];

	TexCoord    = common_data.src.xy + aTexCoord * common_data.src.zw;
	gl_Position = global_data.ViewProjection * common_data.model * vec4(aPos, 0.0, 1.0);
	
	tint = common_data.tint / 255.0;
	Type = Type_in;
}
