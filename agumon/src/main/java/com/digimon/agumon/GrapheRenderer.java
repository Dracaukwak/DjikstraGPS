package com.digimon.agumon;

import com.digimon.agumon.graphe.Arete;
import com.digimon.agumon.graphe.Planete;
import com.digimon.agumon.graphe.Sommet;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 */
public class GrapheRenderer {
    public static void clearGraphe(Pane canvas){
        canvas.getChildren().clear();
    }
    public static void afficherGraphe(Pane canvas, ArrayList<Sommet> sommets, ArrayList<Arete> aretes) {
        clearGraphe(canvas);
        Random random = new Random();
        double largeur = canvas.getPrefWidth();
        double hauteur = canvas.getPrefHeight();

        // Pour les sommets
        for (int i = 0; i < sommets.size(); i++) {
            double x = random.nextDouble() * largeur;
            double y = random.nextDouble() * hauteur;
            Circle cercle = new Circle(x, y, 8, Color.LIGHTBLUE);
            Text nomVille = new Text(x + 10, y, sommets.get(i).getNom());
            sommets.get(i).setCercle(cercle);
            sommets.get(i).setTexte(nomVille);
            canvas.getChildren().add(cercle);
            canvas.getChildren().add(nomVille);
        }

        // Pour les arêtes
        for (int i = 0; i < aretes.size(); i++) {
            Arete edge = aretes.get(i);
            Sommet a = edge.getA();
            Sommet b = edge.getB();
            double posAx = a.getCercle().getCenterX();
            double posAy = a.getCercle().getCenterY();
            double posBx = b.getCercle().getCenterX();
            double posBy = b.getCercle().getCenterY();
            double midX = (posAx + posBx) /2;
            double midY = (posAy + posBy) / 2;
            Line line = new Line(posAx, posAy, posBx, posBy);
            line.setStroke(Color.GRAY);
            Text texte = new Text(midX,midY,Double.toString(edge.getDistance()));
            edge.setTexteDistance(texte);
            edge.setLine(line);
            canvas.getChildren().add(line);
            canvas.getChildren().add(texte);
        }


    }

    public static void resetGraph(ArrayList<Arete> aretes,ArrayList<Sommet>sommets){
        for(Arete a : aretes){
            a.getLine().setStroke(Color.GRAY);
            a.getLine().setStrokeWidth(1.0);
        }
        for(Sommet s :sommets){
            s.getCercle().setStroke(Color.LIGHTBLUE);
        }
    }

    public static void afficherPlanete(Pane canvas, ArrayList<Planete> planetes) {
        canvas.getChildren().clear();
        for (int i = 0; i < planetes.size(); i++) {
            Planete p = planetes.get(i);
            p.genererPlanete(canvas.getPrefHeight(), canvas.getPrefWidth());
            canvas.getChildren().addAll(p.getCercle(), p.getTexte());
        }
    }

    public static void appliquerDijkstra( ArrayList<Arete> aretesSolution,String villeSource, ArrayList<Sommet>sommets) {
        Sommet source = Sommet.getSommetAvecNom(sommets,villeSource);
        source.getCercle().setStroke(Color.BROWN);
        for(Arete a : aretesSolution){
            a.getLine().setStroke(Color.RED);
            a.getLine().setStrokeWidth(3.0);
            Text texte = a.getTexteDistance();
            double midX = (a.getA().getCercle().getCenterX() + a.getB().getCercle().getCenterX()) /2;
            double midY = (a.getA().getCercle().getCenterY() + a.getB().getCercle().getCenterY()) /2;
            texte = new Text(midX,midY,Double.toString(a.getDistance()));
        }
    }

}
