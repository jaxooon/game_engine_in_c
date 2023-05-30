#version 330 core
out vec4 FragColor;
in vec4 aPosition;
void main()
{
   FragColor = aPosition;
}