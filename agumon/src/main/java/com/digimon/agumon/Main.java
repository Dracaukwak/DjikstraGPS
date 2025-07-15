package com.digimon.agumon;

public class Main {
    //Charge la DLL générée (adapte le chemin!!!)
    public static void main(String[] args) {
        System.load("C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\cmake-build-debug\\libdijkstra.dll");
        appelDjikstra d = new appelDjikstra();

        d.runDjikstra("C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\data\\map3", "solution2Java.txt", "Metz", 0);
    }

}
