#version 460 core

in vec4 TintColor;
in vec2 TexCoord;
in flat int Type;
layout(location = 0) out vec4 FragColor;

layout(binding = 0) uniform sampler2D u_Texture;

void main()
{
	switch (Type)
	{
		case 0:
			FragColor = texture(u_Texture, TexCoord) * TintColor;
			break;

		case 1:
			FragColor = (texture(u_Texture, vec2(TexCoord.x, 1.0 - TexCoord.y))) * TintColor;
			break;

		case 2:
			float color = texture(u_Texture, TexCoord).r;
			FragColor = vec4(color, color, color, color) * TintColor;
			break;
	}
}
