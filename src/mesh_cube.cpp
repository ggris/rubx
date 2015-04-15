#include <string>
#include <cmath>

#include "util/logger.hpp"
#include "mesh_cube.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glProgram/program.hpp"

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

    // Creating program

    Program program;

    program.emplace_back("pos.vert", GL_VERTEX_SHADER);
    program.emplace_back("smooth.frag", GL_FRAGMENT_SHADER);

    program.link();

    program.clearShaders();

    m_program = program.getProgram();

}

void MeshCube::display(float t)
{
    glUseProgram(m_program);

    // Get program uniforms

    GLuint offsetUniform = glGetUniformLocation(m_program, "camera_position");
    GLuint perspectiveMatrixUnif = glGetUniformLocation(m_program, "projection_matrix");

    // Define projection matrix

    glm::mat4 projection =
        glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);

    // Define uniform values

    glUniform4f(offsetUniform, cos(t), sin(t), -2, 0);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);

    glUseProgram(0);
}





