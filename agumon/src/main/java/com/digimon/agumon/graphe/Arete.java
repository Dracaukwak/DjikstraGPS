package com.digimon.agumon.graphe;

public class Arete {
    private Sommet a,b;
    private double distance;

    public Arete(Sommet a, Sommet b, double distance) {
        this.a = a;
        this.b = b;
        this.distance = distance;
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
