#include <string>

#include "logger.hpp"
#include "mesh_cube.hpp"
#include <cmath>

MeshCube::MeshCube()
{
    float points[] = {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };

    float normals[] = {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned short index_array[] = {
        0, 3, 2,
        0, 2, 1,
        0, 1, 5,
        0, 5, 4,
        1, 2, 6, 
        1, 6, 5,
        2, 3, 7,
        2, 7, 6,
        3, 0, 4,
        3, 4, 7,
        4, 5, 6,
        4, 6, 7,
    };

    std::string vert_shader_str = "#version 410 \n"
        "layout(location = 0) in vec4 position; \n"
        "uniform vec4 camera_position; \n"
        "uniform mat4 projection_matrix; \n"
        "smooth out vec4 color;\n"
        "void main() \n"
        "{ \n"
        "       float s = 0.2f;\n"
        "       vec4 base_position = position * vec4(s, s, s, 1.0f) + camera_position; \n"
        "        gl_Position = projection_matrix * base_position;\n"
        "       color = position; \n"
        "}";

    std::string frag_shader_str = "#version 410 \n"
        "smooth in vec4 color;\n"
        "out vec4 outColor; \n"
        "void main() \n"
        "{ \n"
        "       outColor = color;\n" 
        "}";

    GLuint points_vbo;
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, 32 * sizeof (float), points, GL_STATIC_DRAW);

    GLuint normals_vbo;
    glGenBuffers (1, &normals_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glBufferData (GL_ARRAY_BUFFER, 32 * sizeof (float), normals, GL_STATIC_DRAW);

    GLuint index_buffer_object;
    glGenBuffers (1, &index_buffer_object);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, 48 * sizeof (unsigned short), index_array, GL_STATIC_DRAW);

    glGenVertexArrays (1, &m_vao);
    glBindVertexArray (m_vao);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);

    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

    glBindVertexArray(0);

    GLuint vert_shader = createShader(GL_VERTEX_SHADER, vert_shader_str.c_str());
    GLuint frag_shader = createShader(GL_FRAGMENT_SHADER, frag_shader_str.c_str());

    std::vector<GLuint> shaders;
    shaders.push_back(vert_shader);
    shaders.push_back(frag_shader);

    m_program = CreateProgram(shaders);

    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);


}

GLuint MeshCube::createShader(GLenum eShaderType, const char *shader_source)
{
    GLuint shader = glCreateShader(eShaderType);
    glShaderSource(shader, 1, &shader_source, 0);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        const char *strShaderType = NULL;
        switch(eShaderType)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        LOG_ERROR << "Compile failure in " << strShaderType << " shader :\n"
            << strInfoLog;
        delete[] strInfoLog;
    }

    return shader;
}

GLuint MeshCube::CreateProgram(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glAttachShader(program, shaderList[iLoop]);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        LOG_ERROR << "Linker failure :\n" << strInfoLog;
        delete[] strInfoLog;
    }

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);

    return program;
}

void MeshCube::display(float t)
{
    glUseProgram(m_program);

    GLuint offsetUniform = glGetUniformLocation(m_program, "camera_position");
    GLuint perspectiveMatrixUnif = glGetUniformLocation(m_program, "projection_matrix");
    float fFrustumScale = 1.0f; float fzNear = 0.1f; float fzFar = 30.0f;
    float theMatrix[16];
    memset(theMatrix, 0, sizeof(float) * 16);
    theMatrix[0] = fFrustumScale;
    theMatrix[5] = fFrustumScale;
    theMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
    theMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    theMatrix[11] = -1.0f;
    glUniform4f(offsetUniform, cos(t), sin(t), -2, 0);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);

    glUseProgram(0);
}





