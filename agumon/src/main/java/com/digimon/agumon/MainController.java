package com.digimon.agumon;


import javafx.fxml.FXML;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javafx.scene.control.TextArea;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

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

    private int heapType = 0;

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

    @FXML
    private void onRunDijkstra() {
        String villeSource = sourceField.getText().trim();
        String cheminSource = filePathField.getText();
        System.load("C:\\Users\\jorda\\CLionProjects\\DjikstraGPS\\cmake-build-debug\\libdijkstra.dll");
        appelDjikstra d = new appelDjikstra();
        String fichierSorti = "maSolutionJava54.txt";
        heapType = getHeapType();

        d.runDjikstra(cheminSource, fichierSorti, villeSource, heapType);
        Path path = Paths.get(fichierSorti);

        try {
            String content = Files.readString(path);
            zoneSolution.setText(content);

        } catch (IOException e) {
            System.out.println("Erreur: onRunDijkstra readString :" + e.getMessage());
        }


    }

    @FXML
    private void onFileChoose() {
        FileChooser fileChooser = new FileChooser();
        File fichier = fileChooser.showOpenDialog(new Stage());
        String cheminComplet = fichier.getAbsolutePath();
        if (fichier != null) {
            System.out.println("Vous avez choisir " + fichier.getName());
            filePathField.setText(cheminComplet);
        }
    }
}
