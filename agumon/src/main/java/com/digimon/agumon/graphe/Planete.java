package com.digimon.agumon.graphe;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;

public class Planete {
    private String nom;
    private Circle cercle;
    private Color color;
    private double diametre;
    private Text texte;

    public Planete(String nom, Circle cercle, Color color, Text texte, double diametre) {
        this.nom = nom;
        this.cercle = cercle;
        this.color = color;
        this.texte = texte;
        this.diametre = diametre;
    }

    public Planete(String nom) {
        this.nom = nom;
        texte = new Text(nom);
    }

    public void genererPlanete(double hauteur, double largeur) {
        double x = Math.random() * largeur;
        double y = Math.random() * hauteur;

        float hue = (float) Math.random() * 360;
        float saturation = 0.6f + (float) (Math.random() * 0.4); // [0.6, 1.0]
        float brightness = 0.7f + (float) (Math.random() * 0.3); // [0.7, 1.0]

        color = Color.hsb(hue, saturation, brightness);

        // Diamètre aléatoire biaisé : plus petit diamètre est plus probable
        // On utilise une puissance pour biaiser la distribution

        double minDiam = 5;
        double maxDiam = 50;
        double poids = Math.pow(Math.random(), 2.5);
        diametre = minDiam + (1 - poids) * (maxDiam - minDiam);
        cercle = new Circle(x, y, diametre / 2, color);
        texte.setX(x + diametre);
        texte.setY(y);
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public Circle getCercle() {
        return cercle;
    }

    public void setCercle(Circle cercle) {
        this.cercle = cercle;
    }

    public void setPosition(double x, double y) {
        getCercle().setCenterX(x);
        getCercle().setCenterY(y);
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public double getDiametre() {
        return diametre;
    }

    public void setDiametre(double diametre) {
        this.diametre = diametre;
    }

    public Text getTexte() {
        return texte;
    }

    public void setTexte(Text texte) {
        this.texte = texte;
    }

    @Override
    public String toString() {
        return "Planete{" +
                "nom='" + nom + '\'' +
                ", cercle=" + cercle +
                ", color=" + color +
                ", diametre=" + diametre +
                ", texte=" + texte +
                '}';
    }
}
