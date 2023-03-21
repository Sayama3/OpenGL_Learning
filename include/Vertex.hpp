//
// Created by Iannis on 04/03/2023.
//

#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "VertexBufferLayout.hpp"

namespace Sayama::OpenGLLearning {
        struct Vertex {
        public:
            glm::vec3 position;
            // TODO: Add normal for the lightning and other stuffs.
        public:
            Vertex();
            Vertex(glm::vec3 position);
            Vertex(float x, float y, float z);

            bool Equal(const Vertex& other) const;

            bool operator==(const Vertex& other) const;

            bool operator!=(const Vertex& other) const;

            // The layout of a vertex
            inline static VertexBufferLayout GetLayout() {
                VertexBufferLayout vbl;
                vbl.Push<glm::vec3>(1);
                return vbl;
            }
        };

    } // OpenGLLearning

