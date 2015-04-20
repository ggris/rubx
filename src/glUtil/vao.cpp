#include <sstream>
#include <string>
#include <fstream>

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
    std::vector<float> obj_normals;
    std::vector<float> obj_uv;
    std::vector<float> points;
    std::vector<float> normals;
    std::vector<float> uv;
    std::vector<unsigned short> index;

    LOG_DEBUG << "Reading VAO";

    std::ifstream infile(filename.c_str());

    LOG_DEBUG << "yp : " << infile.is_open();
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v")
        {
            LOG_DEBUG << "v : " << infile.is_open();
            float x, y, z;
            iss >> x >> y >> z;
            points.push_back(x);
            points.push_back(y);
            points.push_back(z);
            points.push_back(1.0f);
        }
        else if (token == "vn")
        {
            LOG_DEBUG << "vn : " << infile.is_open();
            float x, y, z;
            iss >> x >> y >> z;
            obj_normals.push_back(x);
            obj_normals.push_back(y);
            obj_normals.push_back(z);
            obj_normals.push_back(0.0f);
        }
        else if (token == "vt")
        {
            LOG_DEBUG << "vt : " << infile.is_open();
            float u, v;
            iss >> u >> v;
            obj_uv.push_back(u);
            obj_uv.push_back(v);
        }
        else if (token == "f")
        {
            LOG_DEBUG << "f : " << infile.is_open();
            int i, j, k;
            char c;
            for (int i_l = 0; i_l < 3; i_l++)
            {
                iss >> i >> c >> j >> c >> k;
                index.push_back(--i);
                if (normals.size() < (i+1)*3)
                    normals.resize((i+1)*3);
                k--;
                j--;
                normals[i*3] = obj_normals[k*3];
                normals[i*3+1] = obj_normals[k*3+1];
                normals[i*3+2] = obj_normals[k*3+2];
                if (uv.size() < (i+1)*2)
                    uv.resize((i+1)*2);
                uv[i*2] = obj_uv[j*2];
                uv[i*2+1] = obj_uv[j*2+1];
            }
        }
    }

    LOG_DEBUG << "File read, ok !";

    length_ = index.size();
    return genVAO(points, normals, uv, index);
}


