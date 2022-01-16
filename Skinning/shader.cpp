#include "shader.h"
#include "glad.h"


Shader::Shader() {
	_handle = glCreateProgram();
}

Shader::Shader(const std::string& vertex, const std::string& fragment) {
	_handle = glCreateProgram();
	Load(vertex, fragment);
}

Shader::~Shader() {
	glDeleteProgram(_handle);
}

std::vector<char> Shader::ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

uint32_t Shader::CompileVertexShader(const std::string& vertex) {
    uint32_t v = glCreateShader(GL_VERTEX_SHADER);
    const char* source = vertex.c_str();
    glShaderSource(v, 1, &source, NULL);
    glCompileShader(v);

    GLint success = 0;

    glGetShaderiv(v, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(v, 512, NULL, infoLog);
        std::cout << "Vertex compile failed.\n";
        std::cout << "\t" << infoLog << "\n";
        glDeleteShader(v);
        return 0;
    }
    return v;
}

uint32_t Shader::CompileFragmentShader(const std::string& fragment) {
    uint32_t f = glCreateShader(GL_FRAGMENT_SHADER);
    const char* source = fragment.c_str();
    glShaderSource(f, 1, &source, NULL);
    glCompileShader(f);

    GLint success = 0;

    glGetShaderiv(f, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(f, 512, NULL, infoLog);
        std::cout << "Fragment compile failed.\n";
        std::cout << "\t" << infoLog << "\n";
        glDeleteShader(f);
        return 0;
    }
    return f;
}

bool Shader::LinkShaders(uint32_t vertex, uint32_t fragment) {
    glAttachShader(_handle, vertex);
    glAttachShader(_handle, fragment);
    glLinkProgram(_handle);

    GLint success;
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(_handle, 512, NULL, infoLog);
        std::cout << "Shader link failed.\n";
        std::cout << "\t" << infoLog << "\n";
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return true;
}

void Shader::PopulateAttributes() {
    GLint count = -1;
    GLsizei length;
    GLchar name[128];
    GLint size;
    GLenum type;
    glUseProgram(_handle);
    glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &count);
    for (GLuint i = 0; i < count; i++) {
        memset(name, 0, sizeof(char) * 128);
        glGetActiveAttrib(_handle, i, 128, &length, &size, &type, name);
        GLint attrib = glGetAttribLocation(_handle, name);
        if (attrib >= 0) {
            _attributes[name] = attrib;
        }
    }

    glUseProgram(0);
}

void Shader::PopulateUniforms() {
    GLint count = -1;
    GLsizei length;
    GLchar name[128];
    GLint size;
    GLenum type;
    char testName[256];

    glUseProgram(_handle);
    glGetProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &count);
    for (GLuint i = 0; i < count; i++) {
        memset(name, 0, sizeof(char) * 128);
        glGetActiveUniform(_handle, i, 128, &length, &size, &type, name);

        GLint uniform = glGetUniformLocation(_handle, name);
        if (uniform >= 0) {
            std::string uniformName = name;
            //uniform arrayがあるか確認
            std::size_t found = uniformName.find('[');
            //値が見つかったか
            if (found != std::string::npos) {
                uniformName.erase(uniformName.begin() + found, uniformName.end());
                unsigned int uniformIndex = 0;
                while (true) {
                    memset(testName, 0, sizeof(char) * 256);
                    sprintf(testName, "%s[%d]", uniformName.c_str(), uniformIndex++);
                    int uniformLocation = glGetUniformLocation(_handle, testName);
                    if (uniformLocation < 0) {
                        break;
                    }
                    _uniforms[testName] = uniformLocation;
                }
            }
            _attributes[name] = uniform;
        }
    }

    glUseProgram(0);
}