package com.digimon.agumon.Physique;

import com.digimon.agumon.graphe.Arete;
import com.digimon.agumon.graphe.Sommet;

import java.util.ArrayList;

public class Interaction {
    public final static int EPS = 50;
    static final double FORCE = 2;
    static final double LISSAGE = 0.05;

    static public void repousse(ArrayList<Sommet> sommets) {
        for (Sommet u : sommets) {
            for (Sommet v : sommets) {

                double distance = u.getDistanceEntreDeuxSommets(v);
                if (distance < EPS && distance > 0) {
                    double facteur = FORCE / distance;
                    double dx = u.getCercle().getCenterX() - v.getCercle().getCenterX();
                    double dy = u.getCercle().getCenterY() - v.getCercle().getCenterY();
                    double depX = dx * facteur * LISSAGE;
                    double depY = dy * facteur * LISSAGE;

                    u.updatePosSommet(depX, depY);
                    v.updatePosSommet(-depX, -depY);

                }
            }
        }
    }

    static public void boogieWoogie(ArrayList<Sommet> sommets) {
        for (Sommet s : sommets) {
            double x = (Math.random() - 0.5) * 2; //[-2;2]
            double y = (Math.random() - 0.5) * 2;
            s.updatePosSommet(x, y);
        }
    }
}
