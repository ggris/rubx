#version 410 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 projection_matrix;
uniform sampler2D bumpmap_Sampler;

in vec3 position_es_in[];
in vec3 normal_es_in[];
in vec2 uv_es_in[];

out vec3 position_fs_in;
out vec3 normal_fs_in;
out vec2 uv_fs_in;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
        return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
        return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
} 

void main()
{
    // Interpolate the attributes of the output vertex using the barycentric coordinates
    position_fs_in = interpolate3D(position_es_in[0], position_es_in[1], position_es_in[2]);
    normal_fs_in = interpolate3D(normal_es_in[0], normal_es_in[1], normal_es_in[2]);
    normal_fs_in = normalize(normal_fs_in);
    uv_fs_in = interpolate2D(uv_es_in[0], uv_es_in[1], uv_es_in[2]);

    vec3 bump =texture(bumpmap_Sampler, uv_fs_in).rgb;
    float displacement = (bump[0]+bump[1]+bump[2]) * 0.0;

    position_fs_in += normal_fs_in * displacement;

    gl_Position = projection_matrix * vec4(position_fs_in, 1.0);

}
