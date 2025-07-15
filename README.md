### GPS
## Pour générer le appelDijkstra.h faire :   
``javac -h . .\appelDjikstra.java`` dans le dossier qui contient ce fichier. 
- Ca génère un .h à mettre à portée du fichier.c qui contient l'interface JNI
- Dans l'interface faire correspondre le chemin qui mène jusqu'au fichier .java, ex :(Java_com_digimon_agumon_appelDjikstra_runDjikstra)
- Rebuild le code C lors d'un changement de ce côté (pour les fonctions exportées)
- Puis exécuter le code java..