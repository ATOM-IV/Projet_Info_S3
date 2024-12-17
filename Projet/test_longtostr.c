#include <stdio.h>
#include <stdlib.h>

char* longToString(long value) {
    // On alloue un buffer suffisamment grand pour stocker le nombre et le caractère '\0'
    // Par exemple, 20 caractères suffisent pour stocker un long (y compris un signe négatif).
    char* buffer = malloc(21 * sizeof(char)); // 20 chiffres max + '\0'
    if (buffer == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Conversion du long en chaîne
    sprintf(buffer, "%ld", value);

    return buffer; // Retourne le pointeur vers la chaîne
}

int main() {
    long number = 1234567890;

    // Appel de la fonction
    char* result = longToString(number);

    if (result != NULL) {
        printf("Le nombre %ld converti en chaîne : %s\n", number, result);
        free(result); // Libération de la mémoire allouée
    }

    return 0;
}