cmake_minimum_required(VERSION 3.28)
project(DjikstraGPS C)

set(CMAKE_C_STANDARD 11)
# == CHEMIN DU JDK ===

set(JAVA_HOME "C:/Users/jorda/.jdks/openjdk-24.0.1")
include_directories(${JAVA_HOME}/include)
include_directories(${JAVA_HOME}/include/win32)

# === FICHIER EN COMMUN DU GANGE ===

set(SOURCES
        src/list.c
        src/util.c
        src/dyntable.c
        src/tree.c
        src/heap.c
        src/graph.c
        src/algo.c
)

add_executable(DjikstraGPS src/main.c ${SOURCES})
add_executable(test src/test.c ${SOURCES})
add_executable(experience src/expe.c ${SOURCES})

# === JNI librairie ===
add_library(dijkstra SHARED src/appelDijkstra.c ${SOURCES})