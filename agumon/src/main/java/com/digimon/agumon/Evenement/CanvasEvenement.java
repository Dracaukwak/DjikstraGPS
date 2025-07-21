package com.digimon.agumon.Evenement;

import com.digimon.agumon.graphe.Arete;
import com.digimon.agumon.graphe.Sommet;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import java.util.ArrayList;

public class CanvasEvenement {
    static public boolean sommetSelected = false;

    static public void createSommetOnClick(Pane canvas, ArrayList<Sommet> sommets, ArrayList<Arete> aretesPerso) {
        canvas.setOnMouseClicked(event -> {
            double x = event.getX();
            double y = event.getY();
            String nom = "Ville " + (sommets.size() + 1);
            Sommet s = new Sommet(nom, x, y);
            gestionGraphe(s);
            sommets.add(s);
            if (sommetSelected) {
                Sommet v = Sommet.getSommetSelected(sommets);
                Arete a = new Arete(v, s, s.getDistanceEntreDeuxSommets(v));
                aretesPerso.add(a);
                canvas.getChildren().addAll(a.getLine(), a.getTexteDistance());
                v.setSelected(false);
                v.getCercle().setFill(Color.BROWN);
            }

            canvas.getChildren().add(s.getCercle());
            canvas.getChildren().add(s.getTexte());
            sommetSelected = false;


        });
    }

    static public void gestionGraphe(Sommet s) {
        s.getCercle().setOnMouseClicked(event -> {
            event.consume();
            s.getCercle().setFill(Color.RED);
            s.setSelected(true);
            sommetSelected = true;

        });
    }
}
