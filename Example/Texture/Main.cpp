#include <iostream>
#include <cstdlib>

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include "ToyXWindow/XWindowAPI.h"

#define STB_IMAGE_IMPLEMENTATION
#include "glad/../../../../stb/include/stb_image.h"

#include <Windows.h> // Sleep
#undef CreateWindow


using namespace ToyUtility;
using namespace TRL;
using namespace ToyXWindow;


int main()
{
    auto& xwindowAPI = XWindowAPI::Instance();

    XWINDOW_API_STARTUP_DESC desc;
    desc.WindowContextNativeApi = WindowContextNativeApiType::Win_WGL;

    auto res = xwindowAPI.StartUp(desc);

    if (res != ToyXResult::Success)
    {
        std::cout << "XWindowAPI StartUp fail: " << (int)res << std::endl;
        return -1;
    }

    WINDOW_DESC wd;
    wd.Title = "TRL Example Texture";
    wd.Windowed = true;
    wd.WindowRect = ToyUtility::Rect2I(0, 0, 800, 600);
    wd.BufferCount = 1;
    wd.BufferDesc.Height = 600;
    wd.BufferDesc.Width = 800;
    wd.BufferDesc.RefreshRate = ToyUtility::Rational(1, 60);
    wd.SampleDesc = SampleDesc::NoMultiSampling;
    auto window = xwindowAPI.CreateWindow(wd);
    if (window == nullptr)
    {
        std::cout << "Create window fail" << std::endl;
        return -1;
    }

    xwindowAPI.SetMainWindow(window);


    ToyXWindow::PlatformDependentData xwindowData;
    xwindowAPI.GetPlatformDependentData(xwindowData);

    auto renderAPI = RenderAPI::FactoryCreate(TRLNativeApiType::OpenGL);

    RENDER_API_STARTUP_DESC renderAPIDesc;
    memcpy(&renderAPIDesc.PlatformData, &xwindowData, sizeof(TRL::PlatformDependentData));

    renderAPI->StartUp(renderAPIDesc);

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

    GPU_SHADER_DESC sd;
    sd.ShaderType = GpuShaderType::GPU_VERTEX_SHADER;
    sd.SourceCode = vertexShaderSource;
    auto vertShader = renderAPI->GpuShaderCreate(sd);

    sd.ShaderType = GpuShaderType::GPU_FRAGMENT_SHADER;
    sd.SourceCode = fragmentShaderSource;
    auto fragShader = renderAPI->GpuShaderCreate(sd);

    if (renderAPI->GpuShaderIsCompiledSucc(vertShader) == false)
    {
        std::cout << "vert: " + renderAPI->GpuShaderGetCompileErrorInfo(vertShader) << std::endl;
    }

    if (renderAPI->GpuShaderIsCompiledSucc(fragShader) == false)
    {
        std::cout << "frag: " + renderAPI->GpuShaderGetCompileErrorInfo(fragShader) << std::endl;
    }

    auto program = renderAPI->GpuProgramCreate(vertShader, fragShader);

    // Texture

    const uint8 textureData[] =
    {
        255,0,0,255,
        0,255,0,255,
        0,0,255,255,
        255,255,255,255,
    };

    auto texture2D = renderAPI->GpuTexture2DCreate();
    auto texture2D_2 = renderAPI->GpuTexture2DCreate();

    renderAPI->GpuTexture2DSendImage(texture2D, GpuTextureBaseFormat::GPU_RGBA, 2, 2, PixelFormat::RGBA, PixelDataType::UINT8,
        textureData);
    renderAPI->GpuTexture2DGenerateMipmap(texture2D);
    renderAPI->GpuTexture2DSetMagFilter(texture2D, GpuTextureMagFilterMode::NEAREST);
    renderAPI->GpuTexture2DSetMinFilter(texture2D, GpuTextureMinFilterMode::NEAREST);

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        renderAPI->GpuTexture2DSendImage(texture2D_2, GpuTextureBaseFormat::GPU_RGBA, width, height, PixelFormat::RGBA, PixelDataType::UINT8,
            data);
        renderAPI->GpuTexture2DGenerateMipmap(texture2D_2);
        renderAPI->GpuTexture2DSetMagFilter(texture2D_2, GpuTextureMagFilterMode::NEAREST);
        renderAPI->GpuTexture2DSetMinFilter(texture2D_2, GpuTextureMinFilterMode::NEAREST);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
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

    GPU_BUFFER_DESC bd;
    bd.BufferType = GPU_VERTEX_BUFFER;
    bd.Access = GpuBufferAccessType::GpuRead;
    bd.ModifyHint = GpuBufferModifyHint::Static;
    bd.InitData.Size = 20 * sizeof(float);
    bd.InitData.SysMem = vertices;

    auto vbo = renderAPI->GpuBufferCreate(bd);

    bd.BufferType = GPU_INDEX_BUFFER;
    bd.Access = GpuBufferAccessType::GpuRead;
    bd.ModifyHint = GpuBufferModifyHint::Static;
    bd.InitData.Size = 6 * sizeof(uint32);
    bd.InitData.SysMem = indices;
    auto ebo = renderAPI->GpuBufferCreate(bd);

    auto attrib = renderAPI->GpuAttributeDataCreate();

    auto aPos = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindAttribute("aPos");
    auto aTextCoord = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindAttribute("a_texCoord");
    if (aPos == AttributeVariable::None || aTextCoord == AttributeVariable::None)
    {
        std::cout << "can't find attribute ...";
        return -3;
    }

    renderAPI->SetAttributeArray(attrib, aPos, vbo, GpuVariableComponentSize::_3, GPU_FLOAT, NormalizeActionType::NotNeedNormalize, 5 * sizeof(float), 0);
    renderAPI->SetAttributeArray(attrib, aTextCoord, vbo, GpuVariableComponentSize::_2, GPU_FLOAT, NormalizeActionType::NotNeedNormalize, 5 * sizeof(float), 3 * sizeof(float));
    renderAPI->GpuAttributeDataSetIndicesBuffer(attrib, ebo, 6, GPU_UINT32);

    auto textureUniform = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindUniform("s_texture");
    if (textureUniform == UniformVariable::None)
    {
        std::cout << "can't find s_texture";
        return -4;
    }

    auto textureUniform2 = renderAPI->GpuProgramGetAttributeUniformInfo(program).FindUniform("s_texture2");
    if (textureUniform2 == UniformVariable::None)
    {
        std::cout << "can't find s_texture";
        return -4;
    }

    while (window->ShouldClose() == false)
    {
        Sleep(33);

        renderAPI->GpuProgramSetUniformTexture(program, textureUniform, texture2D, GPU_TEXTURE_UNIT0);
        renderAPI->GpuProgramSetUniformTexture(program, textureUniform2, texture2D_2, GPU_TEXTURE_UNIT1);
        renderAPI->DrawIndices(program, attrib, GpuPrimitiveType::GPU_TRIANGLES, 0);

        window->PresentBackBuffer(0);
        xwindowAPI.PollEvents();
    }

    xwindowAPI.ShutDown();

    return 0;
}