//
// Created by Iannis on 04/03/2023.
//
#include "Triangle.hpp"

namespace Sayama {
    namespace OpenGLLearning {
// Triangle
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
}

#include "Triangle.hpp"
