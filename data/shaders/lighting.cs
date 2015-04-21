#version 410 core

// define the number of CPs in the output patch
layout (vertices = 3) out;

in vec3 position_cs_in[];
in vec3 normal_cs_in[];
in vec2 uv_cs_in[];

out vec3 position_es_in[];
out vec3 normal_es_in[];
out vec2 uv_es_in[];

float GetTessLevel(float d0, float d1)
{
    float d = (d0 + d1) / 2.0;

    return 2.0;

    if (d <= 2.0) {
        return 10.0;
    }
    else if (d <= 5.0) {
        return 7.0;
    }
    else {
        return 3.0;
    }
} 

void main()
{
    // Set the control points of the output patch
    position_es_in[gl_InvocationID] = position_cs_in[gl_InvocationID];
    normal_es_in[gl_InvocationID] = normal_cs_in[gl_InvocationID];
    uv_es_in[gl_InvocationID] = uv_cs_in[gl_InvocationID];

    float distance0 = length(position_es_in[0]);
    float distance1 = length(position_es_in[1]);
    float distance2 = length(position_es_in[2]);

    gl_TessLevelOuter[0] = GetTessLevel( distance1, distance2 );
    gl_TessLevelOuter[1] = GetTessLevel( distance2, distance0 );
    gl_TessLevelOuter[2] = GetTessLevel( distance0, distance1 );
    gl_TessLevelInner[0] = (
            gl_TessLevelOuter[0] +
            gl_TessLevelOuter[1] +
            gl_TessLevelOuter[2] ) / 3;
} 
