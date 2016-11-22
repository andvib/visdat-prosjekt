#version 430 core

uniform layout(location=5) float chosen;
layout(location=2) in vec4 color_in;
out vec4 color_out;

void main()
{
  if (chosen == 1.0){
    color_out = vec4(0.5f, 0.5f, 0.5f, 1.0f);
  } else {
  	color_out = color_in;
  }
}
