#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Für system()
#include <openssl/evp.h>
#include <openssl/opensslv.h> // Für OpenSSL Versionen
#include <omp.h>    // Für OpenMP

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

typedef struct {
    char *name;
    int hash_length;
    int block_size;
    int secure;
    int collision_resistant;
    const EVP_MD *(*evp_md_func)();
} HashFunction;

HashFunction hash_functions[] = {
    {"MD5", 128, 512, 0, 0, EVP_md5},
    {"SHA-1", 160, 512, 0, 0, EVP_sha1},
    {"SHA-256", 256, 512, 1, 1, EVP_sha256},
    {"SHA-384", 384, 1024, 1, 1, EVP_sha384},
    {"SHA-512", 512, 1024, 1, 1, EVP_sha512}
    // Weitere Hash-Funktionen können hier hinzugefügt werden
};

#define HASH_COUNT (sizeof(hash_functions) / sizeof(HashFunction))

void identify_hash_function(const char *hash_value) {
    int hash_length = strlen(hash_value) * 4; // Hexadezimale Zeichenlänge in Bits umrechnen
    int found = 0;
    
    printf("Mögliche Hash-Funktionen für die Hash-Länge %d Bits:\n", hash_length);
    for (int i = 0; i < HASH_COUNT; i++) {
        if (hash_functions[i].hash_length == hash_length) {
            printf("- %s\n", hash_functions[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("Unbekannte Hash-Funktion\n");
    }
}

void calculate_hash(const EVP_MD *md, const char *input, unsigned char *output, unsigned int *output_length) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input, strlen(input));
    EVP_DigestFinal_ex(mdctx, output, output_length);
    EVP_MD_CTX_free(mdctx);
}

void compute_and_check_hashes(const char *hash_value) {
    FILE *file = fopen("passes.txt", "r");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei passes.txt");
        return;
    }

    char password[129]; // Platz für bis zu 128 Zeichen plus Nullterminator

    int found_match = 0; // Flag für Übereinstimmung

    for (int i = 0; i < HASH_COUNT; i++) {
        const EVP_MD *md = hash_functions[i].evp_md_func();
        unsigned char hash_output[EVP_MAX_MD_SIZE];
        unsigned int hash_output_length;

        // Datei zurück auf den Anfang setzen
        fseek(file, 0, SEEK_SET);

        while (fscanf(file, "%128s", password) == 1) {
            calculate_hash(md, password, hash_output, &hash_output_length);

            // Hash-Wert als Hex-String ausgeben
            char hash_string[EVP_MAX_MD_SIZE * 2 + 1];
            for (unsigned int j = 0; j < hash_output_length; j++) {
                sprintf(&hash_string[j * 2], "%02x", hash_output[j]);
            }

            // Vergleiche den Hash-String ohne zusätzliche Zeilenumbrüche
            if (strcmp(hash_string, hash_value) == 0) {
                printf("Übereinstimmung gefunden! Passwort: %s, Hash-Funktion: %s\n", password, hash_functions[i].name);
                found_match = 1;
                break; // Wenn eine Übereinstimmung gefunden wird, beende die Schleife
            }
        }

        // Wenn Übereinstimmung gefunden wurde, verlasse die äußere Schleife
        if (found_match) {
            break;
        }
    }

    if (!found_match) {
        printf("Kein passendes Passwort gefunden!\n");
    }

    fclose(file);
}

int main() {
    // OpenSSL initialisieren (falls nötig)
    OpenSSL_add_all_digests();

    char hash_input[129]; // Platz für bis zu 512 Bit (128 Hex-Zeichen) plus Nullterminator
    system(CLEAR_SCREEN); // Bildschirm leeren
    printf("Gib einen Hash-Wert ein: ");
    scanf("%128s", hash_input);
    identify_hash_function(hash_input);
    compute_and_check_hashes(hash_input);
    return 0;
}
