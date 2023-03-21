//
// Created by Iannis on 04/03/2023.
//

#include "Vertex.hpp"

namespace Sayama::OpenGLLearning {

    Vertex::Vertex() : position() {

    }
    Vertex::Vertex(glm::vec3 position) : position(position) {

    }

    Vertex::Vertex(float x, float y, float z) : position(x, y, z) {

    }



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