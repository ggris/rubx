#ifndef VAO_HPP
#define VAO_HPP

#include <vector>
#include <string>

#include "../util/include_gl.hpp"

class VAO
{
    public:
        VAO(const std::vector<float> &points,
                const std::vector<float> &normals,
                const std::vector<float> &uv,
                const std::vector<unsigned short> &index);

        VAO(const std::string & filename);

        void bindAndDraw() const;

    private:
        const GLuint vao_;
        unsigned int length_;

        GLuint genVAO(const std::vector<float> &points,
                const std::vector<float> &normals,
                const std::vector<float> &uv,
                const std::vector<unsigned short> &index);
        GLuint genVAO(const std::string & filename);


};

#endif
