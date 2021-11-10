#include "Shader.h"

Shader::Shader() {}

Shader::~Shader() {}

void Shader::compileVertexShader()
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    checkShaderErrors(vs, "vertex");
}

void Shader::compileFragmentShader()
{
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    checkShaderErrors(fs, "fragment");
}

void Shader::createShaderProgram()
{
    // Create program
    programId = glCreateProgram();
    glAttachShader(programId, fs);
    glAttachShader(programId, vs);
    glLinkProgram(programId);

    // Check for linking error
    int params = -1;
    glGetProgramiv(programId, GL_LINK_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "Could not link shader programme GL index " << programId;
        printProgramInfoLog(programId);
    }
    if (!isValid(programId))
    {
        LOG(Error) << "Could not validate shader" << programId;
    }

    // Delete shaders for they are no longer used
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader &Shader::use()
{
    glUseProgram(programId);
    return *this;
}


void Shader::setFloat(const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(programId, name), value);
}
void Shader::setInteger(const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(programId, name), value);
}
void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(programId, name), x, y);
}
void Shader::setVector2f(const GLchar *name, const Vector2 &value)
{
    glUniform2f(glGetUniformLocation(programId, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(programId, name), x, y, z);
}
void Shader::setVector3f(const GLchar *name, const Vector3 &value)
{
    glUniform3f(glGetUniformLocation(programId, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(programId, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar *name, const array<GLfloat,4> value)
{
    glUniform4fv(glGetUniformLocation(programId, name), 1,&value[0]);
}
void Shader::setMatrix4(const GLchar *name, const Matrix4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}

/*
void Shader::setMatrix4Row(const GLchar *name, const Matrix4Row &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}
*/

void Shader::checkShaderErrors(GLuint shader, std::string shaderType)
{
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "GL " << shaderType << " shader index " << shader << " did not compile.";
        printShaderInfoLog(shader);
    }
}

void Shader::printShaderInfoLog(GLuint shaderIndex)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];
    glGetShaderInfoLog(shaderIndex, maxLength, &actualLength, log);
    LOG(Info) << "Shader info log for GL index" << shaderIndex;
    LOG(Info) << log;
}

void Shader::printProgramInfoLog(GLuint programId)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];
    glGetProgramInfoLog(programId, maxLength, &actualLength, log);
    LOG(Info) << "program info log for GL index" << programId;
    LOG(Info) << log;
}


const char *Shader::GLTypeToString(GLenum type)
{
    switch (type)
    {
    case GL_BOOL:
        return "bool";
    case GL_INT:
        return "int";
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_SAMPLER_2D:
        return "sampler2D";
    case GL_SAMPLER_3D:
        return "sampler3D";
    case GL_SAMPLER_CUBE:
        return "samplerCube";
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2DShadow";
    default:
        return "other";
    }
}

void Shader::printAllParams(GLuint programId)
{
    LOG(Info) << "-----------------------------";
    LOG(Info) << "Shader programme " << programId << " info:";
    int params = -1;
    glGetProgramiv(programId, GL_LINK_STATUS, &params);
    LOG(Info) << "GL_LINK_STATUS = " << params;

    glGetProgramiv(programId, GL_ATTACHED_SHADERS, &params);
    LOG(Info) << "GL_ATTACHED_SHADERS = " << params;

    glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &params);
    LOG(Info) << "GL_ACTIVE_ATTRIBUTES = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int maxLength = 64;
        int actualLength = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(programId, i, maxLength, &actualLength, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char longName[77];
#if __linux__
                sprintf(longName, "%s[%i]", name, j);
#else
                sprintf_s(longName, "%s[%i]", name, j);
#endif
                int location = glGetAttribLocation(programId, longName);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << longName << " location:" << location;
            }
        }
        else
        {
            int location = glGetAttribLocation(programId, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }

    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &params);
    LOG(Info) << "GL_ACTIVE_UNIFORMS = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int maxLength = 64;
        int actualLength = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(programId, i, maxLength, &actualLength, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char longName[77];
                sprintf(longName, "%s[%i]", name, j);
                int location = glGetUniformLocation(programId, longName);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << longName << " location:" << location;
            }
        }
        else
        {
            int location = glGetUniformLocation(programId, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }
    printProgramInfoLog(programId);
}

bool Shader::isValid(GLuint programId)
{
    glValidateProgram(programId);
    int params = -1;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &params);
    LOG(Info) << "program " << programId << " GL_VALIDATE_STATUS = " << params;
    if (params != GL_TRUE)
    {
        printProgramInfoLog(programId);
        return false;
    }
    return true;
}
