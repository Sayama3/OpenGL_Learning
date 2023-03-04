//
// Created by Iannis on 04/03/2023.
//

#include "Mesh.hpp"
#include <algorithm>

namespace Sayama {
    namespace OpenGLLearning {

        // Mesh
        int Mesh::FindTriangle(const Triangle& triangle) const {
            int index = -1;
            auto it = std::find(triangles.begin(), triangles.end(), triangle);

            // If element was found
            if (it != triangles.end())
            {
                // calculating the index
                index = it - triangles.begin();
            }

            return index;
        }

        int Mesh::AddTriangle(const Triangle& tri) {
            int index = FindTriangle(tri);
            if (index < 0) {
                this->triangles.push_back(tri);
                index = this->triangles.size() - 1;
            }
            return index;
        }

        std::vector<int> Mesh::AddTriangles(const std::vector<Triangle>& tris) {
            std::vector<int> index(tris.size());
            for (const auto& tri : tris) {
                index.push_back(AddTriangle(tri));
            }
            return index;
        }
        void Mesh::AddIndex(int index) {
            this->indices.push_back(index);
        }
        void Mesh::AddIndex(std::vector<int> index) {
            this->indices.insert(std::end(indices), std::begin(index), std::end(index));
        }

        IndexBuffer Mesh::GetIndexBuffer() const {
            return {
                this->indices.data(),
                static_cast<unsigned int>(this->indices.size())
            };
        }

        VertexBuffer Mesh::GetVertexBuffer() const {
            return {
                this->triangles.data(),
                static_cast<unsigned int>(this->triangles.size()) * Triangle::VertexPerTriangle * Vertex::GetLayout().GetStride()
            };
        }

        Mesh::Mesh() : triangles(), indices() {

        }

        Mesh::Mesh(const std::vector<Triangle>& triangles, const std::vector<unsigned int>& indexes) : triangles(triangles), indices(indexes){

        }


    } // Sayama
} // OpenGLLearning