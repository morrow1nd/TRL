#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include "TRL/GpuBuffer.h"
#include "TRL/AttributeData.h"
#include "TRL/AttributeVariable.h"
#include "TRL/GpuProgram.h"
#include "TRL/GpuShader.h"
#include <cstdlib>
#include "GLFW/glfw3.h"
#include <iostream>


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
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        //1, 2, 3   // second Triangle
    };
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    // Prepare data
    GpuBuffer pos;
    pos.Init();
    pos.Bind(GPU_ARRAY_BUFFER);
    pos.UploadData(vertices, 12 * sizeof(GpuFloat), GpuBufferDataType::GPU_STATIC_DRAW);

    GpuBuffer ebo;
    ebo.Init();
    ebo.Bind(GPU_ELEMENT_ARRAY_BUFFER);
    ebo.UploadData(indices, 3 * sizeof(GpuUInt), GpuBufferDataType::GPU_STATIC_DRAW);

    AttributeData attrib;
    attrib.Init();
    attrib.Active();
    attrib.SetAttributeArray(AttributeVariable(0), pos, 3, GPU_FLOAT, false, 3*sizeof(float), 0);
    attrib.SetIndicesBuffer(ebo, 3, GPU_UNSIGNED_INT);
    attrib.Inactive();

    GpuShader vertShader, fragShader;
    vertShader.Init(vertexShaderSource, GpuShaderType::GPU_VERTEX_SHADER);
    if (vertShader.IsCompiledSucc() == false)
    {
        std::cout << "vert: " + vertShader.GetCompileLogInfo() << std::endl;
    }

    fragShader.Init(fragmentShaderSource, GpuShaderType::GPU_FRAGMENT_SHADER);
    if (fragShader.IsCompiledSucc() == false)
    {
        std::cout << "frag: " + fragShader.GetCompileLogInfo() << std::endl;
    }

    GpuProgram program;
    program.Init(vertShader, fragShader);
    
    RenderAPI renderAPI;

    while (true)
    {
        attrib.Active();
        renderAPI.ActiveGpuProgram(program);
        renderAPI.DrawIndices(GpuPrimitiveType::GPU_TRIANGLES, attrib, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        Sleep(1000000);
        std::cout << "-" << std::endl;
    }

    system("pause");
    return 0;
}