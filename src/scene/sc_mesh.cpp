#include <string>
#include <cstring>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "logger.hpp"
#include "program.hpp"

#include "sc_mesh.hpp"

ScMesh::ScMesh(Camera * camera,
        const std::vector<float> &points,
        const std::vector<float> &normals,
        const std::vector<float> &tex_coord,
        const std::vector<unsigned short> &index) :
    camera_(camera)
{
    GLuint points_vbo;
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, points.size() * sizeof (float), points.data(), GL_STATIC_DRAW);

    GLuint normals_vbo;
    glGenBuffers (1, &normals_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glBufferData (GL_ARRAY_BUFFER, normals.size() * sizeof (float), normals.data(), GL_STATIC_DRAW);

    GLuint index_buffer_object;
    glGenBuffers (1, &index_buffer_object);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof (unsigned short), index.data(), GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao_);
    glBindVertexArray (vao_);
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
    //program.emplace_back("smooth.frag", GL_FRAGMENT_SHADER);
    program.emplace_back("ggx.frag", GL_FRAGMENT_SHADER);

    program.link();

    program.clearShaders();

    program_ = program.getProgram();

}

void ScMesh::display()
{
    float t = glfwGetTime();
    glUseProgram(program_);

    // Get program uniforms

    GLuint offsetUniform = glGetUniformLocation(program_, "camera_position");
    GLuint perspectiveMatrixUnif = glGetUniformLocation(program_, "projection_matrix");

    // Define projection matrix

    glm::mat4 projection = camera_->get_mat_camera();

    // Define uniform values

    glUniform4f(offsetUniform, cos(t), sin(t), -2, 0);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);

    glUseProgram(0);
}





