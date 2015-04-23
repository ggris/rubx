#version 410

layout ( location = 0 ) in vec4 position_vs_in;

out vec2 uv_fs_in;

void main()
{
    gl_Position = position_vs_in;
    uv_fs_in = ( position_vs_in.xy + vec2( 1.0 ) ) / 2.0;
}


