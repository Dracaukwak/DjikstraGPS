package com.digimon.agumon.graphe;

import javafx.scene.shape.Line;
import javafx.scene.text.Text;

import java.util.ArrayList;

public class Arete {
    private Sommet a, b;
    private double distance;
    private Line line;
    private Text texteDistance;


    public Arete(Sommet a, Sommet b, double distance) {
        this.a = a;
        this.b = b;
        this.distance = distance;
    }

    static public Arete getArete(ArrayList<Arete> aretes,Sommet a, Sommet b){
        for (Arete ar : aretes){
            if((ar.getA().equals(a) && ar.getB().equals(b) )|| (ar.getA().equals(b) && ar.getB().equals(a))){
                return ar;
            }
        }
        System.out.println("Arête pas trouvée");
        return null;
    }

    static public void updateLine(Sommet a, Sommet b,Line line) {
        line.setStartX(a.getCercle().getCenterX());
        line.setStartY(a.getCercle().getCenterY());
        line.setEndX(b.getCercle().getCenterX());
        line.setEndY(b.getCercle().getCenterY());
    }

    static public void updateAllLines(ArrayList<Arete> aretes){
        for(Arete ar : aretes){
            Sommet a = ar.getA();
            Sommet b = ar.getB();
            updateLine(a,b,ar.getLine());
        }
    }


    public Text getTexteDistance() {
        return texteDistance;
    }

    public void setTexteDistance(Text texteDistance) {
        this.texteDistance = texteDistance;
    }

    public Line getLine() {
        return line;
    }

    public void setLine(Line line) {
        this.line = line;
    }

    public Sommet getA() {
        return a;
    }

    public void setA(Sommet a) {
        this.a = a;
    }

    public Sommet getB() {
        return b;
    }

    public void setB(Sommet b) {
        this.b = b;
    }

    public double getDistance() {
        return distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    @Override
    public String toString() {
        return "Arete{" +
                "a=" + a +
                ", b=" + b +
                ", distance=" + distance +
                '}';
    }
}
