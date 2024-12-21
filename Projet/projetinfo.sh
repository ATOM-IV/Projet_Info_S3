#!/bin/bash


read -p "Entrez le chemin du fichier CSV : "
if [ ! -f "$fichier_csv" ]; then
    echo "Erreur : Le fichier $fichier_csv n'existe pas."
    exit 1
fi
read -p "Entrez le type de station: "
if [[ "$type_station" != "hvb" && "$type_station" != "hva" && "$type_station" != "lv" ]]; then
    echo "Erreur : Type de station invalide. Choisissez parmi 'hvb', 'hva', 'lv'."
    exit 1
fi
read -p "Entrez le type de consommateur: "

if [[ "$type_consommateur" != "comp" && "$type_consommateur" != "indiv" && "$type_consommateur" != "all" ]]; then
    echo "Erreur : Type de consommateur invalide. Choisissez parmi 'comp', 'indiv', 'all'."
    exit 1
fi

echo "Vous avez saisi :"
echo "Fichier CSV : $fichier_csv"
echo "Type de station : $type_station"
echo "Type de consommateur : $type_consommateur"
if [ -x "$file_csv" ]; then
    echo "Le fichier '$file_path' a déjà les bonnes permissions d'exécution."
else

    chmod u+x "$file_path"
    echo "Les permissions d'exécution ont été ajoutées pour le fichier '$file_path'."
fi


mkdir -p "tmp"
mkdir -p "result"



	

