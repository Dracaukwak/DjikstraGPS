package com.digimon.agumon.graphe;

public class Resultat {
    public Sommet ville;
    public double distance;
    public Sommet predecesseur;

    public Resultat(Sommet ville, double distance, Sommet predecesseur) {
        this.ville = ville;
        this.distance = distance;
        this.predecesseur = predecesseur;
    }

    @Override
    public String toString() {
        return "Resultat{" +
                "ville=" + ville +
                ", distance=" + distance +
                ", predecesseur=" + predecesseur +
                '}';
    }
}
