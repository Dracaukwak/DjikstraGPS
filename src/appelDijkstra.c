#include "../include/com_digimon_agumon_appelDjikstra.h"
#include "../include/graph.h"
#include <stdio.h>

extern void Dijkstra(graph G, const char *source_name, int heap_type);
extern graph read_graph(const char *filename);
extern void save_solution(const char *filename, graph G, const char *source_name);
extern void view_solution(graph G, const char* source_name);

JNIEXPORT void JNICALL Java_com_digimon_agumon_appelDjikstra_runDjikstra
(JNIEnv *env, jobject obj, jstring graph_filename, jstring solution_filename, jstring source, jint heap_type) {
    const char *c_graph_filename = (*env)->GetStringUTFChars(env, graph_filename, NULL);
    const char *c_solution_filename = (*env)->GetStringUTFChars(env, solution_filename, NULL);
    const char *c_source = (*env)->GetStringUTFChars(env, source, NULL);

    graph G = read_graph(c_graph_filename);
    Dijkstra(G, c_source, heap_type);
    save_solution(c_solution_filename, G, c_source);
    // view_solution(G, c_source);
    // printf("Hello mon pote");

    (*env)->ReleaseStringUTFChars(env, graph_filename, c_graph_filename);
    (*env)->ReleaseStringUTFChars(env, solution_filename, c_solution_filename);
    (*env)->ReleaseStringUTFChars(env, source, c_source);
}
