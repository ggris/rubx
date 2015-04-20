#include <sstream>
#include <string>

#include "logger.hpp"

#include "vao.hpp"

VAO:VAO(const std::vector<float> &points,
            const std::vector<float> &normals,
            const std::vector<float> &uv,
            const std::vector<unsigned short> &index):
    vao_(genVAO(points, normals, uv, index))
{
}

    VAO::VAO(const std::string & filename)
vao_genVAO(filename)
{
}


void VAO::BindAndDraw()
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);
}


GLuint VAO::genVAO(const std::vector<float> &points,
        const std::vector<float> &normals,
        const std::vector<float> &uv,
        const std::vector<unsigned short> &index)
{
    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof (float), points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint normals_vbo;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof (float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint uv_vbo;
    glGenBuffers(1,&uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,uv_vbo);
    glBufferData(GL_ARRAY_BUFFER,tex_coord.size() * sizeof (float),tex_coord.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint index_buffer_object;
    glGenBuffers(1, &index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof (unsigned short), index.data(), GL_STATIC_DRAW);

    return vao;
}

GLuint VAO::genVAO(const std::string & filename)
{
    std::vector<float> & points;
    std::vector<float> & normals;
    std::vector<float> & uv;
    std::vector<unsigned short> & index;

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;
            points.push_back(x);
            points.push_back(y);
            points.push_back(z);
            points.push_back(1.0f);
        }

    process pair (a,b)
    }
}


