#version 460 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

struct GPU_SSBO
{
	vec4 Src;
	vec4 TintColor;
	mat4 Model;
};

layout(std430, binding = 1) buffer GPU_SSBO_buffer
{
	GPU_SSBO common_data[];
};

struct GPU_UBO
{
	int Type;
	mat4 ViewProjection;
};

layout(std140, binding = 0) uniform GPU_UBO_buffer
{
	GPU_UBO global_data;
};

out vec4 TintColor;
out vec2 TexCoord;
out flat int Type;

void main()
{
	GPU_SSBO common_data =  common_data[gl_InstanceID];

	TexCoord  = common_data.Src.xy + aTexCoord * common_data.Src.zw;
	gl_Position = global_data.ViewProjection * common_data.Model * vec4(aPos, 0.0, 1.0);
	
	TintColor = common_data.TintColor / 255.0;
	Type      = global_data.Type;
}
