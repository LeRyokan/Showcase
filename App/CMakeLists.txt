
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${ZLIB_INCLUDE_DIR}
    ${XERCESC_INCLUDE_DIR}
)

set(ShowcaseMod_LIBS
    FreeCADApp
)

SET(ShowcaseMod_SRCS
    AppShowcaseMod.cpp
    AppShowcaseModPy.cpp
    PreCompiled.cpp
    PreCompiled.h
)

add_library(ShowcaseMod SHARED ${ShowcaseMod_SRCS})
target_link_libraries(ShowcaseMod ${ShowcaseMod_LIBS})


fc_target_copy_resource(ShowcaseMod 
    ${CMAKE_SOURCE_DIR}/src/Mod/ShowcaseMod
    ${CMAKE_BINARY_DIR}/Mod/ShowcaseMod
    Init.py)

SET_BIN_DIR(ShowcaseMod ShowcaseMod /Mod/ShowcaseMod)
SET_PYTHON_PREFIX_SUFFIX(ShowcaseMod)

install(TARGETS ShowcaseMod DESTINATION ${CMAKE_INSTALL_LIBDIR})
