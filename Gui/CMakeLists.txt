
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIR}
    ${QT_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${SOQT_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${XERCESC_INCLUDE_DIR}
)

set(ShowcaseModGui_LIBS
    ShowcaseMod
    FreeCADGui
)

qt4_add_resources(ShowcaseMod_QRC_SRCS Resources/ShowcaseMod.qrc)

SET(ShowcaseModGui_SRCS
    ${ShowcaseMod_QRC_SRCS}
    Actions.cpp
    Actions.h
    AppShowcaseModGui.cpp
    AppShowcaseModGuiPy.cpp
    Command.cpp
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
)

add_library(ShowcaseModGui SHARED ${ShowcaseModGui_SRCS})
target_link_libraries(ShowcaseModGui ${ShowcaseModGui_LIBS})

fc_target_copy_resource(ShowcaseModGui 
    ${CMAKE_SOURCE_DIR}/src/Mod/ShowcaseMod
    ${CMAKE_BINARY_DIR}/Mod/ShowcaseMod
    InitGui.py)

SET_BIN_DIR(ShowcaseModGui ShowcaseModGui /Mod/ShowcaseMod)
SET_PYTHON_PREFIX_SUFFIX(ShowcaseModGui)
    
install(TARGETS ShowcaseModGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
