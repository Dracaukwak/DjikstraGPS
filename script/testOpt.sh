#!/usr/bin/env bash

while getopts ":f:n:" option; do
  case $option in
  f)filname=$OPTARG;;
  n) nbSommet=$OPTARG;;
  \?) echo "Option invalide : $OPTARG";
      exit 1;;
  esac
done

echo $filname
echo $nbSommet