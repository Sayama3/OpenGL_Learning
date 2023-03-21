//
// Created by Iannis on 04/03/2023.
//
#include "Triangle.hpp"

namespace Sayama::OpenGLLearning {
// Triangle

    Triangle::Triangle() : vertices() {

    }

    Triangle::Triangle(const Vertex &v1) : vertices{v1} {

    }

    Triangle::Triangle(const Vertex &v1, const Vertex &v2) : vertices{v1, v2} {

    }

    Triangle::Triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3) : vertices{v1, v2, v3} {

    }

    bool Triangle::Equal(const Triangle &other) const {
        return vertices[0] == other.vertices[0]
               && vertices[1] == other.vertices[1]
               && vertices[2] == other.vertices[2];
    }

    bool Triangle::operator==(const Triangle &other) const {
        return this->Equal(other);
    }

    bool Triangle::operator!=(const Triangle &other) const {
        return !(this->Equal(other));
    }
}

#include "Triangle.hpp"
