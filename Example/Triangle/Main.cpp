#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include <cstdlib>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <Windows.h>


using namespace ToyUtility;
using namespace TRL;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle Example", NULL, NULL);
    if (window == NULL)
    {
        // TODO: showErrorMsgBox(...)
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // TODO: showErrorMsgBox(...)
        // std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    float vertices[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        //1, 2, 3   // second Triangle
    };
    const char *vertexShaderSource = R"(
#version 330 core

in vec3 aPos;
in vec3 aColor;

out vec3 Color;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Color = aColor;
}
)";
    const char *fragmentShaderSource = R"(
#version 330 core
in vec3 Color;

out vec4 FragColor;
void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(Color.x, Color.y, Color.z, 1.0f);
}
)";

    auto renderAPI = RenderAPI::CreateDefaultRenderAPI();

    auto vertShader = renderAPI->GpuShaderCreate(vertexShaderSource, GpuShaderType::GPU_VERTEX_SHADER);
    auto fragShader = renderAPI->GpuShaderCreate(fragmentShaderSource, GpuShaderType::GPU_FRAGMENT_SHADER);

    if (renderAPI->GpuShaderIsCompiledSucc(vertShader) == false)
    {
        std::cout << "vert: " + renderAPI->GpuShaderGetCompileErrorInfo(vertShader) << std::endl;
    }

    if (renderAPI->GpuShaderIsCompiledSucc(fragShader) == false)
    {
        std::cout << "frag: " + renderAPI->GpuShaderGetCompileErrorInfo(fragShader) << std::endl;
    }

    auto program = renderAPI->GpuProgramCreate(vertShader, fragShader);

    // Prepare data
    auto vbo = renderAPI->GpuBufferCreate();
    renderAPI->GpuBufferSendData(vbo, GPU_VERTEX_BUFFER, vertices, 24 * sizeof(float), GpuBufferDataType::GPU_STATIC_DRAW);

    auto ebo = renderAPI->GpuBufferCreate();
    renderAPI->GpuBufferSendData(ebo, GPU_INDEX_BUFFER, indices, 3 * sizeof(uint32), GpuBufferDataType::GPU_STATIC_DRAW);

    auto attrib = renderAPI->GpuAttributeDataCreate();

    auto aPos = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindAttribute("aPos");
    auto aColor = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindAttribute("aColor");
    if (aPos == AttributeVariable::None)
    {
        std::cout << "can't find aPos";
        return -3;
    }
    if (aColor == AttributeVariable::None)
    {
        std::cout << "can't find aColor";
        return -3;
    }

    renderAPI->SetAttributeArray(attrib, aPos, vbo, GpuVariableComponentSize::_3, GPU_FLOAT,
        NormalizeActionType::NotNeedNormalize,
        6*sizeof(float), 0);
    renderAPI->SetAttributeArray(attrib, aColor, vbo, GpuVariableComponentSize::_3, GPU_FLOAT,
        NormalizeActionType::NotNeedNormalize, 6*sizeof(float), 3 * sizeof(float));
    renderAPI->GpuAttributeDataSetIndicesBuffer(attrib, ebo, 3, GPU_UINT32);
    
    while (true)
    {
        renderAPI->DrawIndices(program, attrib, GpuPrimitiveType::GPU_TRIANGLES, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        Sleep(100); // 0.1 second
        //std::cout << "-" << std::endl;
    }

    system("pause");
    return 0;
}