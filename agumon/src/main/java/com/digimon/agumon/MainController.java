package com.digimon.agumon;


import com.digimon.agumon.Physique.Interaction;
import com.digimon.agumon.graphe.Arete;
import com.digimon.agumon.graphe.Chargeur;
import com.digimon.agumon.graphe.Planete;
import com.digimon.agumon.graphe.Sommet;
import javafx.animation.AnimationTimer;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javafx.scene.control.TextArea;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;

public class MainController {

    @FXML
    private TextField sourceField;
    @FXML
    private TextField filePathField;
    @FXML
    private TextArea zoneSolution;
    @FXML
    private RadioButton dyntableRadio;
    @FXML
    private RadioButton treeRadio;
    @FXML
    private RadioButton listRadio;
    @FXML
    private Pane canvas;

    private int heapType = 0;

    private AnimationTimer animation;


    private ArrayList<Sommet> villes = new ArrayList<>();
    private ArrayList<Arete> aretes = new ArrayList<>();
    private ArrayList<Planete> planetes = new ArrayList<>();


    private int getHeapType() {
        if (dyntableRadio.isSelected()) {
            heapType = 0;
        } else if (treeRadio.isSelected()) {
            heapType = 1;
        } else if (listRadio.isSelected()) {
            heapType = 2;
        }
        return heapType;
    }

    private void afficheTypeTas() {
        switch (heapType) {
            case 0:
                System.out.println("Type tas = Dyntable");
                break;
            case 1:
                System.out.println("Type tas = Tree");
                break;
            case 2:
                System.out.println("Type tas = List");
                break;
        }
    }

    @FXML
    private void nettoyerPane(){
        GrapheRenderer.clearGraphe(canvas);
    }

    @FXML
    private void onRunDijkstra() {

        String villeSource = sourceField.getText().trim();
        if(villeSource.trim().isEmpty()){
            sourceField.setText("Entrer une ville source !!");
            return;
        }
        System.out.println("Ville de départ choisie :" + villeSource);
        String cheminSource = filePathField.getText();
        if(cheminSource.trim().isEmpty()){
            zoneSolution.setText("Entrer un fichier !!!");
            return;
        }
        System.load("C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\cmake-build-debug\\libdijkstra.dll");
        appelDjikstra d = new appelDjikstra();
        String fichierSorti = "maSolutionJavaUltime.txt";
        int heatType = getHeapType();
        afficheTypeTas();

        d.runDjikstra(cheminSource, fichierSorti, villeSource, heatType);
        ArrayList<Arete> solution = Chargeur.chargerSolutionDepuisFichier(fichierSorti,villes,aretes);
        Path path = Paths.get(fichierSorti);
//
        try {
            String content = Files.readString(path);
            System.out.println("Le fichier contient :");
            System.out.println(content);
            GrapheRenderer.resetGraph(aretes,villes);
            GrapheRenderer.appliquerDijkstra(solution,villeSource,villes);
            zoneSolution.setText(content);


        } catch (IOException e) {
            System.out.println("problemo" + e.getMessage());
        }

    }

    @FXML
    private void onFileChoose() {
        FileChooser fileChooser = new FileChooser();
        File fichier = fileChooser.showOpenDialog(new Stage());
        String cheminComplet = fichier.getAbsolutePath();
        if (fichier != null) {
            System.out.println("Fichier choisis : " + fichier.getName());
            filePathField.setText(cheminComplet);
        }

        villes = Chargeur.chargerSommetDepuisFichier(cheminComplet);
        aretes = Chargeur.chargerAreteDepuisFichier(cheminComplet, villes);
        GrapheRenderer.afficherGraphe(canvas, villes, aretes);
    }

    @FXML
    private void chargerPlanete() {
        String chemin = "C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\agumon\\src\\main\\java\\com\\digimon\\agumon\\planetes.txt";
        planetes = Chargeur.chargerPlaneteDepuisFichier(chemin);
        GrapheRenderer.afficherPlanete(canvas,planetes);
    }

    @FXML
    public void quitter() {
        Platform.exit();
    }

    @FXML
    public void lancerAnimation() {
        if (animation != null) return;

        animation = new AnimationTimer() {
            @Override
            public void handle(long l) {
                Interaction.boogieWoogie(villes);
                Arete.updateAllLines(aretes);

            }
        };
        animation.start();
    }

    @FXML
    public void lancerForce() {
        if (animation != null) return;

        animation = new AnimationTimer() {
            @Override
            public void handle(long l) {
                Interaction.repousse(villes);
                Arete.updateAllLines(aretes);

            }
        };
        animation.start();
    }


    @FXML
    public void arreterAnimation() {
        if (animation != null) {
            animation.stop();
            animation = null;
        }
    }


}
