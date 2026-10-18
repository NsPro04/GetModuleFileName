add_library(GMFN src/main.cpp)

add_library(GMFN::GMFN ALIAS GMFN)

target_include_directories(GMFN PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_definitions(GMFN PRIVATE "_UNICODE" "UNICODE")

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

    if (BUILD_SHARED_LIBS)
        install(FILES $<TARGET_PDB_FILE:GMFN>
                TYPE BIN
                COMPONENT pdb
                OPTIONAL)
    endif ()
endif ()