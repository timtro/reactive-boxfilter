add_library(signals-and-filters Subject.cpp TimeSignal.cpp)
add_executable(reactive-boxfilter reactive-boxfilter.cpp)
target_link_libraries(reactive-boxfilter signals-and-filters ${CMAKE_THREAD_LIBS_INIT})
