package com.digimon.agumon;

import com.digimon.agumon.graphe.Chargeur;

public class Main {
    //Charge la DLL générée (adapte le chemin!!!)
    public static void main(String[] args) {
        System.out.println(Chargeur.chargerSolutionDepuisFichier("C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\agumon\\maSolutionJava54.txt"));
    }

}
