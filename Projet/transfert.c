#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

// Fonction pour sommer les valeurs selon une condition sur une colonne
long somme_colonne_si_case(int colonne_condition, char *valeur_condition, int colonne_a_sommer) {
    FILE *file = fopen("c-wire_v00.dat", "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    long total = 0;

    // Parcourir le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // Découper la ligne en colonnes
        char *colonnes[8];
        int i = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 8) {
            colonnes[i] = token;
            token = strtok(NULL, ";");
            i++;
        }

        // Vérifier si la condition est remplie
        if (i > (colonne_condition - 1) && strcmp(colonnes[colonne_condition - 1], valeur_condition) == 0) {
            // Vérifier si la colonne à sommer n'est pas vide ou "-"
            if (i > (colonne_a_sommer - 1) && strcmp(colonnes[colonne_a_sommer - 1], "-") != 0) {
                total += atol(colonnes[colonne_a_sommer - 1]);
            }
        }
    }

    fclose(file);
    return total;
}

// Exemple d'utilisation
int main() {
    int colonne_condition = 2;
    char *valeur_condition = "1";
    int colonne_a_sommer = 8;

    long somme = somme_colonne_si_case(colonne_condition, valeur_condition, colonne_a_sommer);
    if (somme != -1) {
        printf("La somme est : %ld\n", somme);
    }

    return 0;
}