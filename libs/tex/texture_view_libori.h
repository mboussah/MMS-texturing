#ifndef TEXTURE_VIEW_LIBORI_H
#define TEXTURE_VIEW_LIBORI_H

#include "Orientation/modeleprojection.hpp"
#include "Orientation/modeleprojectionconique.hpp"
#include "texture_view.h"

using OrientationMATIS::ModeleProjection;
using namespace OrientationMATIS;

//#ifdef TEXTURE_VIEW_LIBORI

class TextureView_libori : public tex::TextureView
{
    ori_shared_ptr<ModeleProjectionConique> m_ori;
    const char * m_systeme_geodesie;
public:
    TextureView_libori(std::size_t id,
                       std::string const & ori_file,
                       std::string const & image_file);
    math::Vec2f get_pixel_coords(math::Vec3f const & vertex) const;
};

//#define //TEXTURE_VIEW_LIBORI

#endif // TEXTURE_VIEW_LIBORI_H
