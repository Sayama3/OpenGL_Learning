//
// Created by Iannis on 04/03/2023.
//

#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "Triangle.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Sayama::OpenGLLearning {

    struct Mesh {
        std::vector<Triangle> triangles;
        std::vector<unsigned int> indices;

        Mesh();
        Mesh(const std::vector<Triangle>& triangles, const std::vector<unsigned int>& indexes);

        int AddTriangle(const Triangle& tri);
        std::vector<int> AddTriangles(const std::vector<Triangle>& tris);

        void AddIndex(int index);
        void AddIndex(std::vector<int> index);

        IndexBuffer GetIndexBuffer() const;
        VertexBuffer GetVertexBuffer() const;

    private:
        int FindTriangle(const Triangle& triangle) const;
    };
} // OpenGLLearning
