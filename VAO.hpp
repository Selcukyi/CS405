#ifndef VAO_HPP
#define VAO_HPP

#include <string>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <glad/glad.h>
using namespace std;

class VAO
{
public:
    VAO(const vector<glm::vec3>& positions, const vector<unsigned int>& indices);

    void bind();
    unsigned int getIndicesCount();

private:
    unsigned int vao = -1;
    unsigned int indicesCount = -1;

    void createVAO(const vector<glm::vec3>& positions, const vector<unsigned int>& indices);
};

VAO::VAO(const vector<glm::vec3>& positions, const vector<unsigned int>& indices)
{
    createVAO(positions, indices);
    this->indicesCount = indices.size();
};

void VAO::bind()
{
    glBindVertexArray(this->vao);
}

unsigned int VAO::getIndicesCount()
{
    return this->indicesCount;
}

void VAO::createVAO(const vector<glm::vec3>& positions, const vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

#endif