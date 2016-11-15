#version 430 core

uniform layout(location=3) mat4x4 i;

layout(location=0) in vec3 position;
layout(location=1) in vec4 color;

out vec4 gl_Position;
layout(location=2) out vec4 color_out;

void main()
{
    gl_Position = vec4(position, 1.0f);


	//mat4 affine;
	//affine[0] = vec4(1, 0, 0, 0);
	//affine[1] = vec4(0, 1, 0, 0);
	//affine[2] = vec4(0, 0, 1, 0);
	//affine[3] = vec4(0, 0, 0, 1);

	gl_Position = i*gl_Position;

	color_out = color;
}
