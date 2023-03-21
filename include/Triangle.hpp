//
// Created by Iannis on 04/03/2023.
//
#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Vertex.hpp"

namespace Sayama::OpenGLLearning {

    struct Triangle {
        static const unsigned int VertexPerTriangle = 3;
        struct Vertex vertices[VertexPerTriangle];

        Triangle();
        Triangle(const struct Vertex& v1);
        Triangle(const struct Vertex& v1, const struct Vertex& v2);
        Triangle(const struct Vertex& v1, const struct Vertex& v2, const struct Vertex& v3);

        bool Equal(const Triangle &other) const;

        bool operator==(const Triangle &other) const;

        bool operator!=(const Triangle &other) const;
    };
}


