#!/bin/bash

# OBJECTIF :
#
# Créer un fichier contenant une nouvelle instance du problème,
# c'est-à-dire un graphe, générée aléatoirement.

# PARAMÈTRES DU SCRIPT :
#
# $1 nom du fichier à créer
# $2 nombre des sommets du graphe
# $3 paramètre utilisé pour définir la densité du graphe, et donc le nombre
#    de ses arêtes. Ça peut prendre des valeurs dans l'intervalle [0,100].


# FONCTION getNormalDistributionSample
#
# Génère de façon aléatoire un entier dans l'intervalle [min,max]
# selon la distribution normale.
#
# PARAMÈTRES : deux entiers correspondants aux limites de l'intervalle.

getNormalDistributionSample () {
	min=$1
	max=$2
	echo $(( min + (RANDOM % (max-min+1)) ))
}


# FONCTION getParetoDistributionSample
#
# Génère de façon aléatoire un entier selon la distribution de Pareto.


getParetoDistributionSample () {

    x=$(echo "" | awk -v seed=$RANDOM 'BEGIN {alpha=1.1d; lambda=20; u=(seed+1)/32768; printf("%.0f\n", lambda*u^(-1/alpha));}')

    echo "$x"

}

# GESTION DE PARAMÈTRES
#
# Si :
# - le nombre de paramètres n'est pas correct, ou
# - le fichier indiqué par le paramètre $1 existe, ou
# - le paramètre $3 n'est pas une valeur entière dans l'intervalle [0,100],
# alors affichez un message d'erreur et arrêtez l'exécution du script.
# S'il n'y a pas d'erreur, affectez les paramètres aux variables locales.

if [ $# -ne 3 ]; then
  echo "Erreur : Nombre de paramètre incorrect"
  echo "Usage: $0 <filename> <number_of_vertices> <density>"
  exit 1
fi

if [ -f $1 ]; then
  echo "Erreur : $1 existe déjà"
  exit  1
fi

if ! [[ $3 =~ ^[0-9]+$ ]]; then
  echo "Erreur : la densité doit être un entier"
  exit 1
fi

if [ $3 -lt 0 ] || [ $3 -gt 100 ]; then
  echo "Erreur : la densité doit être dans [0;100]"
  exit 1
fi




# GÉNÉRATION DES SOMMETS
#
# Il n'y a rien à faire pour générer les sommets d'un graphe.
# Il suffit de connaitre leur nombre qui en fait est donné en paramètre (n).
# Les identifiants des sommets dépendrons du nombre des chiffres de n.
#
# Exemple 1 : Si n = 5, alors les identifiants seront 1 2 3 4 5
# Exemple 2 : Si n = 12, alors les identifiants seront
#             01 02 03 04 05 06 07 08 09 10 11 12
# Exemple 3 : Si n = 2000, alors les identifiants seront
#             0001 0002 0003 ... 0100 0101 0102 ... 1999 2000


# GÉNÉRATION DES ARÊTES
#
# Dans la suite, cherchez et utilisez la commande "seq".
#
# Pour chaque couple des sommets u et v, il y a deux décisions aléatoires
# à prendre par rapport à l'arête (u,v) :
# 1. si cette arête existe
# 2. et si oui, quelle est sa distance.
#
# Pour decider si l'arête existe, on va se baser sur un entier, soit X, généré
# de façon aléatoire dans l'intervalle [0,100] selon la distribution normale.
# Pour cela, vous devez appeler la fonction getNormalDistributionSample
# définie ci-dessous. Si l'entier généré X est inférieur ou égale au troisième
# paramètre du script (correspondant à la densité), alors l'arête existe.
#
# La valeur de la distance de chaque arête est basée sur la distribution
# Pareto. Pour la générer aléatoirement, il faut appeler la fonction
# getParetoDistributionSample.
#
# Attention ! une arête entre le couple des sommets u et v doit être considérée
# une seule fois, soit comme (u,v) soit comme (v,u).
#
# Indication : sauvegarder les arêtes générées avec leurs distances dans un
# tableau associatif initialement vide.

