#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <cassert>

#include "../util/logger.hpp"
#include "vao.hpp"

VAO::VAO(const std::vector<float> &points,
        const std::vector<float> &normals,
        const std::vector<float> &uv,
        const std::vector<unsigned short> &index):
    vao_(genVAO(points, normals, uv, index)),
    length_(index.size() * 3)
{
}

VAO::VAO(const std::string & filename) :
    vao_(genVAO(filename))
{
}


void VAO::bindAndDraw() const
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, length_, GL_UNSIGNED_SHORT, 0);
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
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof (float), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint index_buffer_object;
    glGenBuffers(1, &index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof (unsigned short), index.data(), GL_STATIC_DRAW);

    return vao;
}

GLuint VAO::genVAO(const std::string & filename)
{
    LOG_TRACE << "reading : " << filename;
    std::vector<float> obj_points;
    std::vector<float> obj_normals;
    std::vector<float> obj_uv;

    std::unordered_map<std::string, int> verts;

    std::vector<float> points;
    std::vector<float> normals;
    std::vector<float> uv;
    std::vector<unsigned short> index;

    std::ifstream infile(filename.c_str());
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
            obj_points.push_back(x);
            obj_points.push_back(y);
            obj_points.push_back(z);
        }
        else if (token == "vn")
        {
            float x, y, z;
            iss >> x >> y >> z;
            obj_normals.push_back(x);
            obj_normals.push_back(y);
            obj_normals.push_back(z);
        }
        else if (token == "vt")
        {
            float u, v;
            iss >> u >> v;
            obj_uv.push_back(u);
            obj_uv.push_back(v);
        }
        else if (token == "f")
        {
            std::string vert;
            std::getline(iss, vert, ' ');
            for (unsigned int i_l = 0; i_l < 3; i_l++)
            {
                std::getline(iss, vert, ' ');
                auto itt = verts.find(vert);
                if ( itt == verts.end() )
                {
                    unsigned int n = verts.size();
                    verts.insert({vert, n});
                    index.push_back(n);

                    char c;
                    unsigned int v, vt, vn;
                    std::istringstream issv(vert);
                    issv >> v >> c >> vt >> c >> vn;

                    assert( obj_points.size() >= 3 * v );
                    assert( obj_uv.size() >= 2 * vt );
                    assert( obj_normals.size() >= 3 * vn );

                    v--;
                    vt--;
                    vn--;
                    points.push_back( obj_points[v * 3] );
                    points.push_back( obj_points[v * 3 + 1] );
                    points.push_back( obj_points[v * 3 + 2] );
                    points.push_back( 1.0f );
                    uv.push_back( obj_uv[vt * 2] );
                    uv.push_back( obj_uv[vt * 2 + 1] );
                    normals.push_back( obj_normals[vn * 3] );
                    normals.push_back( obj_normals[vn * 3 + 1] );
                    normals.push_back( obj_normals[vn * 3 + 2] );
                    normals.push_back( 0.0f );

                    assert( ( n + 1 ) * 4 == points.size() );
                    assert( points.size() == normals.size() );
                    assert( points.size() == uv.size() * 2 );

                }
                else
                {
                    index.push_back(itt->second);
                }
            }
        }
    }

    LOG_TRACE << filename << " ==> done";

    length_ = index.size();
    return genVAO(points, normals, uv, index);
}


