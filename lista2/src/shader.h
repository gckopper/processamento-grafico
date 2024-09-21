#include <string>
#include <glad/gl.h>
#include <optional>

class Shader {
    public:
        Shader(const std::string &vertex_source, const std::string &frag_source): vert_source(vertex_source), tesselation_source(), geometry_source(), frag_source(frag_source) {}
        void setTransformSource(std::string &transform_path);
        void setTesselationSource(std::string &tesselation_path);
        std::optional<GLuint> compile();
    private:
        const std::string vert_source;
        std::optional<std::string> tesselation_source;
        std::optional<std::string> geometry_source;
        const std::string frag_source;
        std::optional<GLuint> generic_compile(const std::string &source, GLenum shader_type);
};
