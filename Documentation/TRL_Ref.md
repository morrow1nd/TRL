# ToyRenderLayer


* Windows Management
* Vertex Data(Attribute Variable)
* Shader Program and Uniform Data
* Other State(Blend State, Depth & Stencil State)
* Draw Operation
* RenderAPI Class


## Windows Management


## Vertex Data(Attribute Variable)

These OpenGL concepts can be found here:
    VBO, EBO, VAO


public:
    C:AttributeData - VAO
        S:GetMaxAttributeNumber() : int
        -
        M:SetAttributeArray(AttributeVariable variable, GpuBuffer vbo, int size, GpuDataType type, bool normalized, int stride, int begin_offset)
        M:EnableAttributeArray(AttributeVariable variable) - default to enable
        M:SetConstantAttribute(AttributeVariable variable, GpuFloat x)
        M:SetConstantAttribute(AttributeVariable variable, GpuFloat x, GpuFloat y)
        M:SetConstantAttribute...... See more at http://docs.gl/es3/glVertexAttrib
        M:Active()
    C:GpuBuffer - VBO, EBO
        M:Init(GpuBufferType type)
        M:UploadData(void* data, int size, GpuBufferDataType dataType)
        M:UploadSubData(void* data, int size, int offset)
        M:CleanData() - tell GPU we don't need this data anymore
        M:Destory() - glDeleteBuffers


## Shader Program and Uniform Data


public:
    C:TRLShader
        M:Init(GpuShaderType shaderType)
        M:LoadText(String trlShaderCode)
        M:LoadCompiled()......
        M:GenerateGpuShader(ToyRenderType targetType) : GpuShader
    C:GpuShader
        M:Load(void* p)
        M:Destory()
        M:GetInfoLog
        M:GetShaderSourceLength()
        M:GetShaderType() : GpuShaderType
        M:GetUniformVariableNumber()
        M:GetUniformVariable(int index) : UniformVariable
        M:GetUniformVariableList() : Vector<UniformVariable>
        M:GetAttributeVariableNumber()
        ...
    C:GpuProgram
        M:Init(GpuShader vertShader, GpuShader fragShader)
        M:Destory()
        M:IsActive() : bool


## RenderAPI Class

C:RenderAPI
    M:GetActiveGpuProgram() : GpuProgram
    M:ActiveGpuProgram(GpuProgram program)