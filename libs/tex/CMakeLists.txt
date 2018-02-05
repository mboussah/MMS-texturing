#file (GLOB HEADERS "*.h")
#file (GLOB SOURCES "[^_]*.cpp")
set(HEADERS
    uni_graph.h
    tri.h timer.h
    texture_view.h
    texture_patch.h
    texture_atlas.h
    seam_leveling.h
    rectangular_bin.h
    poisson_blending.h
    obj_model.h
    material_lib.h
    histogram.h
    texture_view_mvs.h)

set(SOURCES
    view_selection.cpp
    uni_graph.cpp tri.cpp
    timer.cpp texture_view.cpp
    texture_patch.cpp
    texture_atlas.cpp
    seam_leveling.cpp
    rectangular_bin.cpp
    prepare_mesh.cpp
    poisson_blending.cpp
    partition_mesh.cpp
    obj_model.cpp
    material_lib.cpp
    local_seam_leveling.cpp
    histogram.cpp
    global_seam_leveling.cpp
    generate_texture_views.cpp
    generate_texture_patches.cpp
    generate_texture_atlases.cpp
    generate_debug_embeddings.cpp
    calculate_data_costs.cpp
    build_obj_model.cpp
    build_adjacency_graph.cpp
    texture_view_mvs.cpp)

if(TEXTURE_VIEW_LIBORI)
    set(HEADERS ${HEADERS} texture_view_libori.h)
    set(SOURCES ${SOURCES} texture_view_libori.cpp)
endif()

set(LIBRARY tex)
add_library(${LIBRARY} STATIC ${SOURCES})
add_dependencies(${LIBRARY} ext_mve ext_rayint ext_eigen)
target_link_libraries(${LIBRARY} mrf -lmve -lmve_util ${JPEG_LIBRARIES} ${PNG_LIBRARIES} ${TIFF_LIBRARIES})
#-----------------------------------------------
if(TEXTURE_VIEW_LIBORI)
    target_link_libraries(${LIBRARY} ${Orientation_LIBRARIES})
endif()
#-----------------------------------------------
install(TARGETS ${LIBRARY} ARCHIVE DESTINATION lib)
