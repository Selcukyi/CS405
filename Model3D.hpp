#ifndef VAO_HPP
#define VAO_HPP

#include <string>
#include <iostream>
#include <vector>
#include "GameObj3D.hpp"
#include <glm.hpp>
#include <glad/glad.h>
using namespace std;

class Model3D
{
public:
    Model3D(const vector<glm::vec3>& positions, const vector<glm::vec3>& normals, const vector<unsigned int>& indices);
    ~Model3D();

    unsigned int getIndicesCount();

private:
    unsigned int vao = -1;
    unsigned int vbo_norm = -1, vbo_pos = -1, ibo = -1;
    unsigned int indicesCount = -1;

    void create(const vector<glm::vec3>& positions, const vector<glm::vec3>& normals, const vector<unsigned int>& indices);
    void bind();

    friend class GameObj3D;
};

Model3D::Model3D(const vector<glm::vec3>& positions, const vector<glm::vec3>& normals, const vector<unsigned int>& indices)
{
    create(positions, normals, indices);
    this->indicesCount = indices.size();
};

Model3D::~Model3D() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo_pos);
    glDeleteBuffers(1, &ibo);
}

unsigned int Model3D::getIndicesCount()
{
    return this->indicesCount;
}

void Model3D::create(const vector<glm::vec3>& positions, const vector<glm::vec3>& normals, const vector<unsigned int>& indices)
{
    // create vao
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // create attrib (positions)
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // create attrib (normals)
    glGenBuffers(1, &vbo_norm);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_norm);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // create indices
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void Model3D::bind()
{
    glBindVertexArray(this->vao);
}

#endif