package com.digimon.agumon.graphe;

import javafx.scene.shape.Circle;
import javafx.scene.text.Text;

import java.util.ArrayList;
import java.util.Objects;

public class Sommet {
    private String nom;
    private Sommet predecesseur;
    private int distance;
    private Circle cercle;
    private Text texte;


    public Text getTexte() {
        return texte;
    }

    public void setTexte(Text texte) {
        this.texte = texte;
    }

    public Circle getCercle() {
        return cercle;
    }

    public void setCercle(Circle cercle) {
        this.cercle = cercle;
    }

    static public Sommet getSommetAvecNom(ArrayList<Sommet> sommets, String nom) {
        for (Sommet s : sommets) {
            if (s.getNom().equals(nom)) {
                return s;
            }
        }
        System.out.println("Sommet non trouvé");
        return null;
    }

    public Sommet(String nom, Sommet pred, int distance) {
        setNom(nom);
        setDistance(distance);
        this.predecesseur = pred;
    }

    public Sommet(String nom) {
        this.nom = nom;
    }

    private void validerNom(String nom) {
        if (nom.trim().isEmpty()) {
            throw new IllegalArgumentException("Nom vide ou null");
        }
    }


    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        validerNom(nom);
        this.nom = nom;
    }

    public int getDistance() {
        return distance;
    }

    public double getDistanceEntreDeuxSommets(Sommet a) {
        double x = this.getCercle().getCenterX();
        double y = this.getCercle().getCenterY();
        double xb = a.getCercle().getCenterX();
        double yb = a.getCercle().getCenterY();
        double r = x - xb;
        double s = y - yb;
        return Math.sqrt(r * r + s * s);
    }

    public void updatePosSommet(double dx, double dy) {
        double x = getCercle().getCenterX();
        double y = getCercle().getCenterY();
        x += dx;
        y += dy;
        getCercle().setCenterX(x);
        getCercle().setCenterY(y);
        getTexte().setX(x + 10);
        getTexte().setY(y);
    }


    public void setDistance(int distance) {
        if (distance < 0)
            throw new IllegalArgumentException("Distance négative ..");
        this.distance = distance;
    }

    public Sommet getPredecesseur() {
        return predecesseur;
    }

    public void setPredecesseur(Sommet pred) {
        this.predecesseur = pred;
    }

    @Override
    public String toString() {
        return "Sommet{" +
                "nom='" + nom + '\'' +
                ", predecesseur=" + predecesseur +
                ", distance=" + distance +
                ", cercle=" + cercle +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Sommet sommet)) return false;
        return Objects.equals(getNom(), sommet.getNom());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(getNom());
    }
}
