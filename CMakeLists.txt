project(Game)


 cmake_minimum_required(VERSION 3.6)
 add_definitions(-DNEED_XPARSEGEOMETRY_IMPL)
 ADD_DEFINITIONS(-DGLEW_STATIC)
 add_definitions(-DFREEGLUT_EXPORTS)
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/freeglut/include)
SET(FREEGLUT_HEADERS
    freeglut/include/GL/freeglut.h
    freeglut/include/GL/freeglut_ext.h
    freeglut/include/GL/freeglut_std.h
    freeglut/include/GL/glut.h
)
SET(FREEGLUT_SRCS
    ${FREEGLUT_HEADERS}
    freeglut/src/fg_callbacks.c
    freeglut/src/fg_cursor.c
    freeglut/src/fg_display.c
    freeglut/src/fg_ext.c
    freeglut/src/fg_font_data.c
    freeglut/src/fg_gamemode.c
    freeglut/src/fg_geometry.c
    freeglut/src/fg_gl2.c
    freeglut/src/fg_gl2.h
    freeglut/src/fg_init.c
    freeglut/src/fg_init.h
    freeglut/src/fg_internal.h
    freeglut/src/fg_input_devices.c
    freeglut/src/fg_joystick.c
    freeglut/src/fg_main.c
    freeglut/src/fg_misc.c
    freeglut/src/fg_overlay.c
    freeglut/src/fg_spaceball.c
    freeglut/src/fg_state.c
    freeglut/src/fg_stroke_mono_roman.c
    freeglut/src/fg_stroke_roman.c
    freeglut/src/fg_structure.c
    freeglut/src/fg_teapot.c
    freeglut/src/fg_teapot_data.h
    freeglut/src/fg_videoresize.c
    freeglut/src/fg_window.c
	freeglut/src/fg_menu.c
	freeglut/src/fg_font.c
	freeglut/src/util/xparsegeometry_repl.c
)

if (WIN32)
	   ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	LIST(APPEND FREEGLUT_SRCS
        freeglut/src/mswin/fg_cursor_mswin.c
        freeglut/src/mswin/fg_display_mswin.c
        freeglut/src/mswin/fg_ext_mswin.c
        freeglut/src/mswin/fg_gamemode_mswin.c
        freeglut/src/mswin/fg_init_mswin.c
        freeglut/src/mswin/fg_internal_mswin.h
        freeglut/src/mswin/fg_input_devices_mswin.c
        freeglut/src/mswin/fg_joystick_mswin.c
        freeglut/src/mswin/fg_main_mswin.c
        freeglut/src/mswin/fg_menu_mswin.c
        freeglut/src/mswin/fg_spaceball_mswin.c
        freeglut/src/mswin/fg_state_mswin.c
        freeglut/src/mswin/fg_structure_mswin.c
        freeglut/src/mswin/fg_window_mswin.c
    )
else()

endif()

file(GLOB MATH
        ${CMAKE_CURRENT_SOURCE_DIR}/math/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/math/*.h
)


file(GLOB GLEW
        ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/include/GL/glew.h
		 ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/include/GL/wglew.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/src/glew.c
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/include)

SOURCE_GROUP(glut_src FILES ${FREEGLUT_SRCS})
SOURCE_GROUP(math_src FILES ${MATH})
SOURCE_GROUP(glew_src FILES ${GLEW})

add_executable(${PROJECT_NAME} ${FREEGLUT_SRCS} ${MATH} ${GLEW} main.cpp)