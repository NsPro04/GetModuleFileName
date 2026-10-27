add_library(GMFN src/main.cpp)

add_library(GMFN::GMFN ALIAS GMFN)

target_include_directories(GMFN PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_definitions(GMFN PRIVATE "_UNICODE" "UNICODE")

if (BUILD_SHARED_LIBS)
    target_compile_definitions(GMFN INTERFACE GMFN_NO_AUTO_LINK)
else ()
    target_compile_definitions(GMFN PUBLIC GMFN_STATIC_LIB)
endif ()

target_compile_options(GMFN PRIVATE "/W4" $<$<BOOL:${GMFN_STRICT}>:/WX>)

target_link_options(GMFN PRIVATE "/MANIFEST:NO")

if (GMFN_INSTALL)
    install(TARGETS GMFN
            EXPORT GMFN
            ARCHIVE
                COMPONENT devel
            LIBRARY
                COMPONENT runtime
            RUNTIME
                COMPONENT runtime
            FRAMEWORK
                COMPONENT runtime
    )

    install(EXPORT GMFN
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
            NAMESPACE GMFN::
            COMPONENT devel)

    if (BUILD_SHARED_LIBS)
        install(FILES $<TARGET_PDB_FILE:GMFN>
                TYPE BIN
                COMPONENT pdb
                OPTIONAL)
    endif ()
endif ()