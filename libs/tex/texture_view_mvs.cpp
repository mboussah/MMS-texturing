#include "texture_view_mvs.h"
#include "texture_view.h"
#include <mve/image_io.h>
#include <mve/image_tools.h>

TextureView_mvs::TextureView_mvs(std::size_t id, mve::CameraInfo const & camera,
    std::string const & image_file)
    : TextureView(id, image_file)
{
    mve::image::ImageHeaders header;
    try {
         header = mve::image::load_file_headers(image_file);
    } catch (util::Exception e) {
        std::cerr << "Could not load image header of " << image_file << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    width = header.width;
    height = header.height;

    camera.fill_calibration(*projection, width, height);
    camera.fill_camera_pos(*pos);
    camera.fill_viewing_direction(*viewdir);
    camera.fill_world_to_cam(*world_to_cam);
}

inline math::Vec2f
TextureView_mvs::get_pixel_coords(math::Vec3f const & vertex) const
{
    math::Vec3f pixel = projection * world_to_cam.mult(vertex, 1.0f);
    pixel /= pixel[2];
    return math::Vec2f(pixel[0] - 0.5f, pixel[1] - 0.5f);
}
