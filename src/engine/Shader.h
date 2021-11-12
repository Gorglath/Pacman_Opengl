#ifndef SHADER_H
#define SHADER_H
 
#include <GL/glew.h>
#include "Log.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

class Shader
{
public:
    Shader();
    virtual ~Shader();
 
    GLuint programId;

    void initShader(const char* nVertexShader,const char* nFragmentShader);
    void compileVertexShader();
    void compileFragmentShader();
    void createShaderProgram();

 	// Sets the current shader as active
	Shader& use();

    // Utility functions
	void setFloat(const GLchar *name, GLfloat value);
	void setInteger(const GLchar *name, GLint value);
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar *name, const Vector2 &value);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar *name, const Vector3 &value);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar *name, const array<GLfloat,4> value);
	void setMatrix4(const GLchar *name, const Matrix4 &matrix);
	//void setMatrix4Row(const GLchar *name, const Matrix4Row &matrix);
 
private:
    GLuint vs;
    GLuint fs;
 
    const char* vertexShader;


    const char* fragmentShader;
 
    void checkShaderErrors(GLuint shader, std::string shaderType);

    void printShaderInfoLog(GLuint shaderIndex);
    void printProgramInfoLog(GLuint programId);
    const char *GLTypeToString(GLenum type);
    void printAllParams(GLuint programId);
    bool isValid(GLuint programId);
 
    Shader(const Shader &) = delete;
    Shader& operator=(const Shader &) = delete;
};
 
#endif
