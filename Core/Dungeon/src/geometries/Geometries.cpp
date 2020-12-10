#include <GL/glew.h>
#include <GL/GL.h>

#include <geometries/Geometries.hpp>

#include <glm/vec3.hpp>
#include <array>

TrivialDrawable geom_test_triangle ()
{
    TrivialDrawable drawable;

    const std::array<glm::vec3, 3> points{glm::vec3{0.25f, 0.25f, 0.0f}, glm::vec3{0.75f, 0.25f, 0.0f}, glm::vec3{0.75f, 0.75f, 0.0f}};

    const std::array<uint32_t, 3> indices{0, 1, 2};

    if (GL_NONE == drawable.vbo)
    {
        glGenVertexArrays(1, &drawable.vbo);
    }

    glBindVertexArray(drawable.vbo);

    GLuint pointsBuffer;
    glGenBuffers(1, &pointsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    GLuint indicesBuffer;
    glGenBuffers(1, &indicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(GL_NONE);
    glDeleteBuffers(1, &pointsBuffer);
    glDeleteBuffers(1, &indicesBuffer);

    drawable.count = static_cast<GLsizei> (indices.size());

    return drawable;
}
