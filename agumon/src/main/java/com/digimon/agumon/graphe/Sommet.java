package com.digimon.agumon.graphe;

public class Sommet {
    private String nom;
    private Sommet predecesseur;
    private int distance;

    public Sommet(String nom, Sommet pred, int distance){
        setNom(nom);
        setDistance(distance);
        this.predecesseur = pred;

    }

    public Sommet(String nom) {
        this.nom = nom;
    }

    private void validerNom(String nom){
        if(nom.trim().isEmpty()){
            throw new IllegalArgumentException("Nom vide ou null");
        }
    }
    public String getNom(){
        return nom;
    }

    public void setNom(String nom){
        validerNom(nom);
        this.nom=nom;
    }

    public int getDistance(){
        return distance;
    }
    public void setDistance(int distance){
        if(distance < 0)
            throw new IllegalArgumentException("Distance négative ..");
        this.distance = distance;
    }

    public Sommet getPredecesseur(){
        return predecesseur;
    }

    public void setPredecesseur(Sommet pred){
        this.predecesseur = pred;
    }

    @Override
    public String toString() {
        return "Sommet{" +
                "nom='" + nom + '\'' +
                ", predecesseur=" + predecesseur +
                ", distance=" + distance +
                '}';
    }
}
