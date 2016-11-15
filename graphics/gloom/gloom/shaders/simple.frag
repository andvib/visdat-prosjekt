#version 430 core

layout(location=2) in vec4 color_in;
out vec4 color_out;

void main()
{
    //color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	color_out = color_in;
}
