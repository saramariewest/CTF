#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <omp.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define DEFAULT_PASSWORD_FILE "rockyou.txt"

typedef struct {
    char *name;
    int hash_length;
    const EVP_MD *(*evp_md_func)();
} HashFunction;

HashFunction hash_functions[] = {
    {"MD5", 128, EVP_md5},
    {"SHA-1", 160, EVP_sha1},
    {"SHA-256", 256, EVP_sha256},
    {"SHA-384", 384, EVP_sha384},
    {"SHA-512", 512, EVP_sha512}
};
#define HASH_COUNT (sizeof(hash_functions) / sizeof(HashFunction))

void identify_hash_function(const char *hash_value) {
    int hash_length = strlen(hash_value) * 4;
    int found = 0;
    printf("Possible hash functions for %d bits:\n", hash_length);
    for (int i = 0; i < HASH_COUNT; i++) {
        if (hash_functions[i].hash_length == hash_length) {
            printf("- %s\n", hash_functions[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("Unknown hash function\n");
    }
}

void calculate_hash(const EVP_MD *md, const char *input, unsigned char *output, unsigned int *output_length) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input, strlen(input));
    EVP_DigestFinal_ex(mdctx, output, output_length);
    EVP_MD_CTX_free(mdctx);
}

void compute_and_check_hashes(const char *hash_value, const char *password_file) {
    FILE *file = fopen(password_file, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open password file '%s'.\n", password_file);
        fprintf(stderr, "Download 'rockyou.txt' and place it in the script directory:\n");
        fprintf(stderr, "wget https://example.com/rockyou.txt -O rockyou.txt\n");
        exit(EXIT_FAILURE);
    }

    char password[129];
    int found_match = 0;

    #pragma omp parallel for shared(found_match)
    for (int i = 0; i < HASH_COUNT; i++) {
        if (found_match) continue;
        const EVP_MD *md = hash_functions[i].evp_md_func();
        unsigned char hash_output[EVP_MAX_MD_SIZE];
        unsigned int hash_output_length;

        FILE *file_copy = fopen(password_file, "r");
        if (!file_copy) continue;

        while (fscanf(file_copy, "%128s", password) == 1) {
            calculate_hash(md, password, hash_output, &hash_output_length);

            char hash_string[EVP_MAX_MD_SIZE * 2 + 1];
            for (unsigned int j = 0; j < hash_output_length; j++) {
                sprintf(&hash_string[j * 2], "%02x", hash_output[j]);
            }

            if (strcmp(hash_string, hash_value) == 0) {
                #pragma omp critical
                {
                    printf("Match found! Password: %s, Hash function: %s\n", password, hash_functions[i].name);
                    found_match = 1;
                }
                fclose(file_copy);
                break;
            }
        }
        fclose(file_copy);
    }
    if (!found_match) {
        printf("No matching password found!\n");
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <hash_value> [password_file]\n", argv[0]);
        printf("Using default password file: %s\n", DEFAULT_PASSWORD_FILE);
        argv[2] = DEFAULT_PASSWORD_FILE;
    }
    OpenSSL_add_all_digests();
    system(CLEAR_SCREEN);
    identify_hash_function(argv[1]);
    compute_and_check_hashes(argv[1], (argc >= 3) ? argv[2] : DEFAULT_PASSWORD_FILE);
    return 0;
}
