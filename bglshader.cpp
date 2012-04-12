#include "bglshader.h"
#include <iostream>

BGLShader::BGLShader()
{
    glewInit();
}
void BGLShader::run() {
    const GLchar * data[] = {
        "void main(void)"
        "{"
        "    gl_FragColor = vec4(0.7, 1.0, 1.0, 1.0);"
        "}"
    };

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSourceARB(fragment, 1, data, 0);
    glCompileShaderARB(fragment);

    GLint compiled;
    glGetObjectParameterivARB(fragment, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        //GLint length;
        //glGetObjectParameterivARB(fragment, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

        //GLchar * log = new GLchar[length];
        //glGetInfoLogARBARB(fragment, length, &length, log);
        std::cout << "Compile log: " <<  std::endl;
    }

    GLint program = glCreateProgram();
    glAttachShader(program, fragment);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked) {
        glUseProgram(program);
        std::cout << "Baf" << std::endl;
    } else {
        std::cout << "error program" << std::endl;
    }
}
