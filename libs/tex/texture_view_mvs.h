#ifndef TEXTURE_VIEW_MVS_H
#define TEXTURE_VIEW_MVS_H


#include "texture_view.h"
//#include <mve/camera.h>
//#include <mve/image_io.h>
class TextureView_mvs : public tex::TextureView
{
    math::Matrix3f projection;
    math::Matrix4f world_to_cam;
public:
    //texture_view_mvs();
    TextureView_mvs(std::size_t id, mve::CameraInfo const & camera, std::string const & image_file);
    math::Vec2f get_pixel_coords(math::Vec3f const & vertex) const;
};

#endif // TEXTURE_VIEW_MVS_H
