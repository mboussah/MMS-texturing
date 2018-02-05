#include "texture_view_libori.h"
#include "texture_view.h"

TextureView_libori::TextureView_libori(std::size_t id,
                                       std::string const & ori_file,
                                       std::string const & image_file):
    TextureView(id, image_file)
{
    m_ori = ori_dynamic_pointer_cast<ModeleProjectionConique> (ModeleProjection::ReadFile(ori_file));
    m_systeme_geodesie = m_ori->GetSystemGeodesie().c_str();
    // std::cout<< "m_systeme_geodesie=" << m_systeme_geodesie << std::endl; // BV: this is bugged, don't know why, but no impact as everything is in the same system

    const double *sommet = m_ori->GetExtrinseque().GetSommet();
    // TODO: read pivot from mesh IGN comments
    double pivot[3];
    pivot[0]=561400;
    pivot[1]=6929000;
    pivot[2]=0;
    for(int i=0; i<3; i++) pos[i]=sommet[i]-pivot[i];
    //std::cout<<"ENH init: "<<sommet[0]<<","<<sommet[1]<<","<<sommet[2]<<std::endl;
    //std::cout<<"ENH pivoted: "<<pos[0]<<","<<pos[1]<<","<<pos[2]<<std::endl;
    m_ori->GetExtrinseque().SetSommet(pos[0],pos[1],pos[2]);

    unsigned int nc, nl;
    m_ori->GetTailleImage(nc,nl);
    width = nc;
    height = nl;
    double P0x, P0y, P0z, P1x, P1y, P1z;
    m_ori->ImageToLocalVec(nc/2,nl/2,P0x, P0y, P0z, P1x, P1y, P1z); //P0X, P0y et P0z doivent être respectivement égales à easting, northing et altitude
    //std::cout << "paramètres ImageToLocalVec: "<< "vx = " << P1x-P0x <<" "<< "vy = "<< P1y-P0y <<" "<< "vz = " << P1z-P0z<< std::endl;
    //std::cout << "focal = " << m_ori->GetFocal() << std::endl;
    viewdir[0]=P1x-P0x;
    viewdir[1]=P1y-P0y;
    viewdir[2]=P1z-P0z;
}

inline math::Vec2f
TextureView_libori::get_pixel_coords(math::Vec3f const& vertex)const
{
    math::Vec2f cl;
    double c, l;
    m_ori->LocalToImage(vertex[0],vertex[1],vertex[2],c,l);
    cl[0]=c; cl[1]=l;
    return cl;
}
