#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

// Fonction pour sommer les valeurs selon une condition sur une colonne
long somme_colonne_si_case(const char filepath, int colonne_condition, const charvaleur_condition, int colonne_a_sommer) {
    FILE file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    long total = 0;

    // Parcourir le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // Découper la ligne en colonnes
        charcolonnes[10]; // Supposons qu'il y a au maximum 10 colonnes
        int i = 0;
        char token = strtok(line, ";");

        while (token != NULL && i < 10) {
            colonnes[i++] = token;
            token = strtok(NULL, ";");
        }

        // Vérifier si la condition est remplie
        if (i > colonne_condition - 1 && strcmp(colonnes[colonne_condition - 1], valeur_condition) == 0) {
            // Vérifier si la colonne à sommer n'est pas vide ou "-"
            if (i > colonne_a_sommer - 1 && strcmp(colonnes[colonne_a_sommer - 1], "-") != 0) {
                total += atol(colonnes[colonne_a_sommer - 1]);
            }
        }
    }

    fclose(file);
    return total;
}

// Exemple d'utilisation
int main() {
    const charfilepath = "chemin/vers/le/fichier.txt";
    int colonne_condition = 2;
    const char *valeur_condition = "1";
    int colonne_a_sommer = 7;

    long somme = somme_colonne_si_case(filepath, colonne_condition, valeur_condition, colonne_a_sommer);
    if (somme != -1) {
        printf("La somme est : %ld\n", somme);
    }

    return 0;
}