
#include "rlWebkitRenderer.h"

#include <EAWebKit/EAWebKit.h>
#include <EAWebKit/EAWebkitAllocator.h>
#include <EAWebKit/EAWebKitFileSystem.h>
#include <EAWebKit/EAWebKitClient.h>
#include <EAWebKit/EAWebKitView.h>
#include "EAWebKit/EAWebKitTextInterface.h"

#include <vector>
#include <array>
#include <iostream>

RLRenderer::RLRenderer()
{

}

RLRenderer::~RLRenderer()
{

}

EA::WebKit::ISurface * RLRenderer::CreateSurface(EA::WebKit::SurfaceType surfaceType, const void* data /*= 0*/, size_t length /*= 0*/)
{
    RLSurface* res = new RLSurface();
    if (data && length)
    {
        EA::WebKit::ISurface::SurfaceDescriptor sd = {};
        res->Lock(&sd);
        memcpy(sd.mData, data, length);
        res->Unlock();
    }
    return res;
}

void RLRenderer::SetRenderTarget(EA::WebKit::ISurface *target)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::RenderSurface(EA::WebKit::ISurface *surface, EA::WebKit::FloatRect &target, EA::WebKit::TransformationMatrix &matrix, float opacity, EA::WebKit::CompositOperator op, EA::WebKit::TextureWrapMode wrap, EA::WebKit::Filters &filters)
{
   std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::FillColor(uint32_t premultiplied_rgba32, EA::WebKit::FloatRect &target, EA::WebKit::TransformationMatrix &matrix, EA::WebKit::CompositOperator op)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::DrawOutline(uint32_t premultiplied_rgba32, EA::WebKit::FloatRect &target, EA::WebKit::TransformationMatrix &matrix)
{
    std::cout << __FUNCTION__ << std::endl;
}

int32_t RLRenderer::MaxTextureSize(void)
{
    return 4096;
}

void RLRenderer::Clear(EA::WebKit::ClearFlags flags, uint32_t premultiplied_rgba32, float z, uint32_t stencil)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::ScissorClip(EA::WebKit::IntRect axisAlignedRect)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::DrawStencil(EA::WebKit::TransformationMatrix &matrix, EA::WebKit::FloatRect &target, uint32_t stencilIndex)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::ClipAgainstStencil(uint32_t stencilIndex)
{
    std::cout << __FUNCTION__ << std::endl;
}

bool RLRenderer::UseCustomClip()
{
    return false;
}

void RLRenderer::BeginClip(EA::WebKit::TransformationMatrix &matrix, EA::WebKit::FloatRect &target)
{
    std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::EndClip(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

EA::WebKit::IntRect RLRenderer::CurrentClipBound()
{
    return EA::WebKit::IntRect(0, 0, 800, 600);
}

void RLRenderer::BeginPainting(void)
{
   std::cout << __FUNCTION__ << std::endl;
}

void RLRenderer::EndPainting(void)
{
    std::cout << __FUNCTION__ << std::endl;
}



//------------------------GL Surface ------------------------------------


RLSurface::RLSurface()
{

}

RLSurface::~RLSurface()
{

}

void RLSurface::Lock(SurfaceDescriptor *pSDOut, const EA::WebKit::IntRect *rect /*= NULL*/)
{

}

void RLSurface::Unlock(void)
{

}

void RLSurface::Release(void)
{

}

bool RLSurface::IsAllocated(void) const
{
   return false;
}

void RLSurface::Reset(void)
{
    // no idea what this is supposed to do
}

void RLSurface::AllocateSurface(int width, int height)
{
 
}
