package com.digimon.agumon.graphe;

import javafx.scene.paint.Color;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Chargeur {

    /**
     * Charge les sommets du fichier dans une liste
     * Format du fichier :
     * 3
     * SF
     * NY
     * LA
     * 3
     * SF NY 4683
     * SF LA 613
     * NY LA 4497
     *
     * @param cheminFichier
     * @return la liste des sommets
     */
    static public ArrayList<Sommet> chargerSommetDepuisFichier(String cheminFichier) {
        ArrayList<Sommet> villes = new ArrayList<>();
        List<String> lignes;
        try {
            lignes = Files.readAllLines(Paths.get(cheminFichier));
        } catch (IOException e) {
            throw new IllegalArgumentException("Erreur : chargerSommetDepuisFichier");
        }

        int nbVille = Integer.parseInt(lignes.getFirst());
        for (int i = 1; i <= nbVille; i++) {

            Sommet s = new Sommet(lignes.get(i));
            villes.add(s);
        }
        return villes;
    }

    /**
     * Charge les aretes du fichier dans une liste
     * les arêtes sont créées en recherchant au préalable leur nom dans la liste des sommets
     * pour obtenir la même intance !!!
     *
     * @param cheminFichier chemin contenant les aretes
     * @return la liste des aretes
     */
    static public ArrayList<Arete> chargerAreteDepuisFichier(String cheminFichier, ArrayList<Sommet> sommets) {
        ArrayList<Arete> aretes = new ArrayList<>();
        List<String> lignes;
        try {
            lignes = Files.readAllLines(Paths.get(cheminFichier));
        } catch (IOException e) {
            throw new IllegalArgumentException("Erreur : chargerAreteDepuisFichier");
        }

        int nbVilles = Integer.parseInt(lignes.getFirst());
        int departArete = nbVilles + 2;
        int fin = lignes.size();

        for (int i = departArete; i < fin; i++) {
            String[] parties = lignes.get(i).split((" "));
            String nomU = parties[0];
            String nomV = parties[1];
            double distance = Double.parseDouble(parties[2]);
            Sommet u = Sommet.getSommetAvecNom(sommets, nomU);
            Sommet v = Sommet.getSommetAvecNom(sommets, nomV);
            Arete a = new Arete(u, v, distance);
            aretes.add(a);
        }
        return aretes;
    }

    /**
     * Charge les resultats du fichier dans une liste d'arêtes
     * Format du fichier :
     * 3
     * LA
     * LA 613 SF
     * LA 4497 NY
     *
     * @param cheminFichierSolution
     * @return
     */
    public static ArrayList<Arete> chargerSolutionDepuisFichier(String cheminFichierSolution, ArrayList<Sommet> sommets, ArrayList<Arete> aretes) {
        ArrayList<Arete> areteResultats = new ArrayList<>();
        List<String> lignes;
        try {
            lignes = Files.readAllLines(Paths.get(cheminFichierSolution));
        } catch (IOException e) {
            throw new IllegalArgumentException("Erreur : chargerSolutionDepuisFichier");
        }
        int nbVilles = Integer.parseInt(lignes.getFirst());
        String villeSource = lignes.get(1); // Si jamais besoin
        for (int i = 2; i <= nbVilles; i++) {
            String[] parties = lignes.get(i).split(" ");
            String nomU = parties[0];
            double distance = Double.parseDouble(parties[1]);
            String nomV = parties[2];
            Sommet u = Sommet.getSommetAvecNom(sommets, nomU);
            Sommet v = Sommet.getSommetAvecNom(sommets, nomV);
            Arete a = Arete.getArete(aretes, u, v);
            a.setDistance(distance);
            if (a != null) {
                areteResultats.add(a);
            }
        }
        return areteResultats;
    }

    static public ArrayList<Planete> chargerPlaneteDepuisFichier(String nomFichier) {
        ArrayList<Planete> planetes = new ArrayList<>();
        List<String> lignes;

        try {
            lignes = Files.readAllLines(Paths.get(nomFichier));
        } catch (IOException e) {
            throw new IllegalArgumentException("Erreur planete chargement" + e.getMessage());
        }
        int nbPlanete = Integer.parseInt(lignes.getFirst());
        for (int i = 1; i <= nbPlanete; i++) {
            String nom = lignes.get(i);
            Planete p = new Planete(nom);
            planetes.add(p);
        }
        return planetes;

    }


}
