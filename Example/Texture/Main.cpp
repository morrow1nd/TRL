#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include "TRL/GpuBuffer.h"
#include "TRL/AttributeData.h"
#include "TRL/AttributeVariable.h"
#include "TRL/GpuProgram.h"
#include "TRL/GpuShader.h"
#include "TRL/GpuTexture2D.h"
#include <cstdlib>
#include "GLFW/glfw3.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "GLFW/../../../../stb/include/stb_image.h"


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

    GLFWwindow* window = glfwCreateWindow(800, 600, "TRL Texture Example", NULL, NULL);
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


    // Shader Program
    const char *vertexShaderSource = R"(
#version 330 core

in vec3 aPos;
in vec2 a_texCoord;

out vec2 v_texCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_texCoord = a_texCoord;
}
)";
    const char *fragmentShaderSource = R"(
#version 330 core

in vec2 v_texCoord;
uniform sampler2D s_texture;
uniform sampler2D s_texture2;

out vec4 FragColor;
void main()
{
    FragColor = texture(s_texture, v_texCoord) * texture(s_texture2, v_texCoord);
}
)";

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

    // Texture

    const GpuUByte textureData[] = 
    {
        255,0,0,255,
        0,255,0,255,
        0,0,255,255,
        255,255,255,255,
    };
    GpuTexture2D texture2D, texture2D_2;
    texture2D.Init();
    texture2D.UploadImage(GpuTextureBaseFormat::GPU_RGBA, 2, 2, PixelFormat::RGBA, PixelDataType::UNSIGNED_BYTE,
        textureData);
    texture2D.GenerateMipmap();
    texture2D.SetMagFilter(GpuTextureMagFilterMode::NEAREST);
    texture2D.SetMinFilter(GpuTextureMinFilterMode::NEAREST);

    texture2D_2.Init();
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {    
        texture2D_2.UploadImage(GpuTextureBaseFormat::GPU_RGBA, width, height, PixelFormat::RGBA, PixelDataType::UNSIGNED_BYTE,
             data);
        texture2D_2.GenerateMipmap();
        texture2D_2.SetMagFilter(GpuTextureMagFilterMode::NEAREST);
        texture2D_2.SetMinFilter(GpuTextureMinFilterMode::NEAREST);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        system("pause");
        return -6;
    }

    // Vertex Data

    float vertices[] = {
   //   #pos                 #textCoord
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    GpuBuffer vbo;
    vbo.Init();
    vbo.Bind(GPU_ARRAY_BUFFER);
    vbo.UploadData(vertices, 20 * sizeof(GpuFloat), GpuBufferDataType::GPU_STATIC_DRAW);

    GpuBuffer ebo;
    ebo.Init();
    ebo.Bind(GPU_ELEMENT_ARRAY_BUFFER);
    ebo.UploadData(indices, 6 * sizeof(GpuUInt), GpuBufferDataType::GPU_STATIC_DRAW);

    AttributeData attrib;
    attrib.Init();
    attrib.Active();
    auto pos = program.FindAttribute("aPos");
    auto aTextCoord = program.FindAttribute("a_texCoord");
    if (pos == AttributeVariable::None || aTextCoord == AttributeVariable::None)
    {
        std::cout << "can't find ...";
        return -3;
    }

    attrib.SetAttributeArray(pos, vbo, GpuVariableComponentSize::_3, GPU_FLOAT, AttributeData::NormalizeAction::NotNeedNormalize, 5*sizeof(float), 0);
    attrib.SetAttributeArray(aTextCoord, vbo, GpuVariableComponentSize::_2, GPU_FLOAT, AttributeData::NormalizeAction::NotNeedNormalize, 5 * sizeof(float), 3*sizeof(float));
    attrib.SetIndicesBuffer(ebo, 6, GPU_UNSIGNED_INT);
    attrib.Inactive();

    auto textureUniform = program.FindUniform("s_texture");
    if (textureUniform == UniformVariable::None)
    {
        std::cout << "can't find s_texture";
        return -4;
    }

    auto textureUniform2 = program.FindUniform("s_texture2");
    if (textureUniform2 == UniformVariable::None)
    {
        std::cout << "can't find s_texture";
        return -4;
    }

    RenderAPI renderAPI;

    while (true)
    {
        attrib.Active();
        renderAPI.ActiveGpuProgram(program);
        
        program.SetUniformTex(textureUniform, texture2D, 0);
        program.SetUniformTex(textureUniform2, texture2D_2, 1);
        renderAPI.DrawIndices(GpuPrimitiveType::GPU_TRIANGLES, attrib, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        Sleep(100); // 0.1 second
        //std::cout << "-" << std::endl;
    }

    system("pause");
    return 0;
}