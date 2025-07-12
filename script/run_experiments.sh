#!/bin/bash

# OBJECTIF :
#
# Réaliser une campagne expérimentale sur une collection des instances.

# PARAMÈTRES DU SCRIPT :
#
# $1 nom du répertoire contenant la collection des instances
# $2 nom du fichier avec les résultats


# GESTION DE PARAMÈTRES
#
# Testez si le nombre de paramètres est correct et affichez un message dans
# le cas contraire.
# Assurez vous que le premier paramètre correspond bien à un répertoire.

if [ $# -ne 2 ]; then
  echo "Usage: $0 <repertoire_des_instance> <fichier_resultat>"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Erreur : $1 n'est pas un répertoire valide"
  exit 1
fi

# Affectation des paramètres aux variables.

dir_instances=$1
fichier_resultat=$2

 # EXÉCUTION DE L'EXPÉRIENCE
 #
 # Pour toutes les instances de la collection, exécutez le programme "./expe".
 # Il faut choisir comme sommet de depart le premier sommet du graphe
 # (2eme ligne de chaque fichier).
 # Pour chaque exécution, vous devez écrire une ligne dans le fichier
 # $out_filename avec 6 colonnes :
 # Colonne 1 : nombre des sommets du graphe
 # Colonne 2 : paramètre concernant la densité du graphe
 # Colonne 3 : numéro de l'instance avec ces paramètres
 # Colonnes 4-6 : résultats obtenus par l'exécution du programme "./expe"
 # Les colonnes sont séparées par une espace.

> $fichier_resultat

for instanceFile in "$dir_instances"/*; do
  filename=$(basename "$instanceFile")
  sommet_depart=$(head -n 2 "$instanceFile" | tail -n 1)
  IFS='_' read nb_sommet densite instance <<< "$filename"
  resultat=$(../cmake-build-debug/experience $instanceFile $sommet_depart)

  echo "$nb_sommet $densite $instance $resultat" >> $fichier_resultat
done

echo "Campagne expérimentale terminée. Résultats enregistrés dans $fichier_resultat"