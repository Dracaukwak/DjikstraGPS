module com.digimon.agumon {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires java.desktop;


    opens com.digimon.agumon to javafx.fxml;
    exports com.digimon.agumon;
}