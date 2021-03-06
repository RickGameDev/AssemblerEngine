macro(path_linux_to_win MsysPath ResultingPath)
  string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" ${ResultingPath} "${MsysPath}")
endmacro()
macro(path_win_to_linux MsysPath ResultingPath)
  string(REGEX REPLACE "^([a-zA-Z]):/" "/\\1/" ${ResultingPath} "${MsysPath}")
endmacro()

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)

    find_program(PLANT_UML_PATH plantuml.jar PATH_SUFFIXES PlantUML plantuml Plantuml 
        PATHS /usr/share /usr/local/share/ /usr/local/bin c/Program\ Files* )
    if(NOT PLANT_UML_PATH)
        message(WARNING "Looking for PlantUML - not found, some UML diagrams will not be generated via doxygen.")
    else()
        message(STATUS "  + PlantUML - for custom UML             YES ")
    endif()

    #Search for DOT for autogenerated UML diagrams from doxygen
    find_program(DOT_PATH dot PATH_SUFFIXES graphviz2.38/bin graphviz/bin)
    if(NOT DOT_PATH)
        message(WARNING "Looking for DOT (Graphviz) - not found, some UML diagrams will not be generated via doxygen.")
    else()
        message(STATUS "  + Graphviz/Dot - for generated graphs   YES ")
    endif()

    if(WIN32)
        set(CMAKE_CURRENT_SOURCE_DIR_DOCS ${CMAKE_CURRENT_SOURCE_DIR})
        set(PROJECT_SOURCE_DIR_DOCS ${PROJECT_SOURCE_DIR})
        set(CMAKE_CURRENT_BINARY_DIR_DOCS ${CMAKE_CURRENT_BINARY_DIR})
        set(DOT_PATH_DOCS ${DOT_PATH})
        set(PLANT_UML_PATH_DOCS ${PLANT_UML_PATH})
        set(DOCS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/docs)
    elseif(UNIX)
        path_win_to_linux(${CMAKE_CURRENT_SOURCE_DIR} CMAKE_CURRENT_SOURCE_DIR_DOCS)
        path_win_to_linux(${PROJECT_SOURCE_DIR} PROJECT_SOURCE_DIR_DOCS)
        path_win_to_linux(${DOT_PATH} DOT_PATH_DOCS)
        path_win_to_linux(${PLANT_UML_PATH} PLANT_UML_PATH_DOCS)
        path_win_to_linux(${CMAKE_CURRENT_BINARY_DIR} CMAKE_CURRENT_BINARY_DIR_DOCS)
    endif()

    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)