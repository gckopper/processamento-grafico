#include <glad/gl.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <cstring>

#pragma once

constexpr GLenum glprimitive_decay(const GLenum num) {
    switch (num) {
        case GL_DOUBLE_MAT3x4:
        case GL_DOUBLE_MAT4x3:
        case GL_DOUBLE_MAT2x4:
        case GL_DOUBLE_MAT4x2:
        case GL_DOUBLE_MAT2x3:
        case GL_DOUBLE_MAT3x2:
        case GL_DOUBLE_MAT4:
        case GL_DOUBLE_MAT3:
        case GL_DOUBLE_VEC4:
        case GL_DOUBLE_MAT2:
        case GL_DOUBLE_VEC3:
        case GL_DOUBLE_VEC2:
        case GL_DOUBLE:
            return GL_DOUBLE;
        case GL_UNSIGNED_INT_VEC4:
        case GL_UNSIGNED_INT_VEC3:
        case GL_UNSIGNED_INT_VEC2:
        case GL_UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        case GL_INT_VEC4:
        case GL_INT_VEC3:
        case GL_INT_VEC2:
        case GL_INT:
            return GL_INT;
        case GL_FLOAT_MAT3x4:
        case GL_FLOAT_MAT4x3:
        case GL_FLOAT_MAT2x4:
        case GL_FLOAT_MAT4x2:
        case GL_FLOAT_MAT2x3:
        case GL_FLOAT_MAT3x2:
        case GL_FLOAT_MAT4:
        case GL_FLOAT_MAT3:
        case GL_FLOAT_VEC4:
        case GL_FLOAT_MAT2:
        case GL_FLOAT_VEC3:
        case GL_FLOAT_VEC2:
        case GL_FLOAT:
            return GL_FLOAT;
        default:
            return 0;
    }
}

constexpr int glprimitive_to_size(const GLenum num) noexcept {
     switch (num) {
        case GL_DOUBLE_MAT3x4:
        case GL_DOUBLE_MAT4x3:
            return 3*4*sizeof(GLdouble);
        case GL_DOUBLE_MAT2x4:
        case GL_DOUBLE_MAT4x2:
            return 2*4*sizeof(GLdouble);
        case GL_DOUBLE_MAT2x3:
        case GL_DOUBLE_MAT3x2:
            return 2*3*sizeof(GLdouble);
        case GL_DOUBLE_MAT4:
            return 16*sizeof(GLdouble);
        case GL_DOUBLE_MAT3:
            return 9*sizeof(GLdouble);
        case GL_DOUBLE_VEC4:
        case GL_DOUBLE_MAT2:
            return 4*sizeof(GLdouble);
        case GL_DOUBLE_VEC3:
            return 3*sizeof(GLdouble);
        case GL_DOUBLE_VEC2:
            return 2*sizeof(GLdouble);
        case GL_DOUBLE:
            return sizeof(GLdouble);
        case GL_UNSIGNED_INT_VEC4:
            return 4*sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC3:
            return 3*sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC2:
            return 2*sizeof(GLuint);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_INT_VEC4:
            return 4*sizeof(GLint);
        case GL_INT_VEC3:
            return 3*sizeof(GLint);
        case GL_INT_VEC2:
            return 2*sizeof(GLint);
        case GL_INT:
            return sizeof(GLint);
        case GL_FLOAT_MAT3x4:
        case GL_FLOAT_MAT4x3:
            return 3*4*sizeof(GLfloat);
        case GL_FLOAT_MAT2x4:
        case GL_FLOAT_MAT4x2:
            return 2*4*sizeof(GLfloat);
        case GL_FLOAT_MAT2x3:
        case GL_FLOAT_MAT3x2:
            return 2*3*sizeof(GLfloat);
        case GL_FLOAT_MAT4:
            return 16*sizeof(GLfloat);
        case GL_FLOAT_MAT3:
            return 9*sizeof(GLfloat);
        case GL_FLOAT_VEC4:
        case GL_FLOAT_MAT2:
            return 4*sizeof(GLfloat);
        case GL_FLOAT_VEC3:
            return 3*sizeof(GLfloat);
        case GL_FLOAT_VEC2:
            return 2*sizeof(GLfloat);
        case GL_FLOAT:
            return sizeof(GLfloat);
        default:
            return 0;
    }
}

struct VertElem {
    // Amount of components
    GLint size = 0;  
    // size of this type in bytes
    GLint len = 0;
    // attibute location inside shader program
    GLint id = 0;
    // opengl data type
    GLenum primitive;
    // Offset inside the VBO
    size_t offset = 0;
};
class VAOBuilder {
    public:
        VAOBuilder(GLuint shader);
        template<typename T>
        void addData(const std::string &var_name, const std::vector<T> &arr) {
            static_assert(std::is_same<GLfloat, T>::value
                    || std::is_same<GLdouble, T>::value
                    || std::is_same<GLuint, T>::value
                    || std::is_same<GLint, T>::value,
                    "addData function in VAOBuilder can only receive GLfloat, GLdouble, GLuint and GLint vectors as input");
            auto elem = atributts.find(var_name);
            if (elem == atributts.end()) {
                std::cerr << "Cant find " << var_name << " attribute. Is it an active attribute?\n";
                exit(-3);
                return;
            }
            GLenum primi = glprimitive_decay(elem->second.primitive);
            if ((std::is_same<GLfloat, T>::value && GL_FLOAT != primi)
                    || (std::is_same<GLdouble, T>::value && GL_DOUBLE != primi)
                    || (std::is_same<GLuint, T>::value && GL_UNSIGNED_INT != primi)
                    || (std::is_same<GLint, T>::value && GL_INT != primi)) {
                std::cerr << "Type mismatch adding data to VAO\n";
                exit(-3);
                return;
            }
            if ((sizeof(T) * arr.size()) % elem->second.len != 0) {
                std::cerr << "Size mismatch in addData function. arr's size is not a multiple of the associated element type\n";
                exit(-3);
                return;
            }
            const size_t offset = elem->second.offset;
            const size_t elem_len = elem->second.len;
            // the size of the of each element in T
            const size_t len_in_t = elem_len/sizeof(T);
            const size_t vert_count = arr.size()/len_in_t;
            if (vert_count*vertex_size > vbo.size()) {
                vbo.insert(vbo.end(), vertex_size*vert_count - vbo.size(), 0);
            }

            for (size_t i = 0; i < vert_count; ++i) {
                memcpy(vbo.data()+i*vertex_size+offset, arr.data()+i*len_in_t, elem_len);
            }
            elem->second.offset += vertex_size*vert_count;
        }
        GLuint build();
    private:
        std::vector<uint8_t> vbo;
        uint64_t vertex_size;
        std::unordered_map<std::string, VertElem> atributts;
};
