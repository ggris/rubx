#version 410

in vec2 uv_fs_in;

out vec4 fragColor;

uniform sampler2D texture_sampler;

float Offsets[4] = float[]( -1.5, -0.5, 0.5, 1.5 );

void main()
{
    vec3 Color = vec3(0.0, 0.0, 0.0);

    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            vec2 tc = uv_fs_in;
            tc.x = uv_fs_in.x + Offsets[j] / textureSize(texture_sampler, 0).x;
            tc.y = uv_fs_in.y + Offsets[i] / textureSize(texture_sampler, 0).y;
            Color += texture(texture_sampler, tc).xyz;
        }
    }

    Color /= 16.0;

    fragColor = vec4(Color, 1.0);
}

