project(01-simple-library)

set(01-source-files "${PROJECT_SOURCE_DIR}/Prac.cpp" CACHE INTERNAL "")

add_library(
    01-simple-library SHARED ${01-source-files} ${Testing_SOURCE_DIR}/include/Prac.h
)



