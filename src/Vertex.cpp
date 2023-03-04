//
// Created by Iannis on 04/03/2023.
//

#include "Vertex.hpp"

namespace Sayama::OpenGLLearning {
        // Vertex
        bool Vertex::Equal(const Vertex &other) const {
            return this->position == other.position;
        }

        bool Vertex::operator==(const Vertex& other) const {
            return this->Equal(other);
        }

        bool Vertex::operator!=(const Vertex& other) const {
            return !(this->Equal(other));
        }

    } // OpenGLLearning