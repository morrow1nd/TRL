#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/CommonType.h"
#include "TRL/GpuTexture.h"


namespace TRL
{


class GpuTexture2D : public GpuTexture
{
public:
    void Init();

    // level: specifies which mip level to load. The first level is specified by 0
    void UploadImage(GpuTextureBaseFormat internalFormat, GpuSizei width, GpuSizei height,
        PixelFormat format, PixelDataType type, const void* data, int level = 0);

    void SetMinFilter(GpuTextureMinFilterMode filterMode);
    void SetMagFilter(GpuTextureMagFilterMode filterMode);

    void SetWrapS(GpuTextureWrapMode wrapMode);
    void SetWrapR(GpuTextureWrapMode wrapMode);
    void SetWrapT(GpuTextureWrapMode wrapMode);

    // Specifies the index of the lowest defined mipmap level. The initial value is 0.
    void SetBaseLevel(int level);

    // more: compare_func, compare_mode, min_filter, max_filter, min_lod, max_lod, max_level, swizzle_(rgba)

    // Automatic generate mipmap
    void GenerateMipmap();

    void Destory();
};


} // end of namespace TRL