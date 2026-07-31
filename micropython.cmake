# Create an INTERFACE library for our C module.
add_library(usermod_sasppu INTERFACE)

# Add our source files to the lib
target_sources(usermod_sasppu INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_background_map.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_background_state.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_buffer.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_cmath_state.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_graphics_plane.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_hdma.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_main_state.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_mpy_help.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_mpy.c
    ${CMAKE_CURRENT_LIST_DIR}/sasppu_sprite.c
    ${CMAKE_CURRENT_LIST_DIR}/subscr_load_adapter.c
)

# Add the current directory as an include directory.
target_include_directories(usermod_sasppu INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../../components/sasppu
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_sasppu)

