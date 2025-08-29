#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hex(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt(char *message, unsigned char **ciphertext, unsigned char **key) {
    int len = strlen(message);
    *ciphertext = malloc(len);
    *key = malloc(len);

    for (int i = 0; i < len; i++) {
        (*key)[i] = rand() % 256; // Random key for demonstration
        (*ciphertext)[i] = message[i] ^ (*key)[i]; // XOR operation
    }
}

unsigned char* hex_to_bin(const char *hex, int *out_len) {
    int len = strlen(hex);
    *out_len = len / 2;
    unsigned char *bin = malloc(*out_len);

    for (int i = 0; i < *out_len; i++) {
        sscanf(hex + 2 * i, "%2hhx", &bin[i]);
    }

    return bin;
}

int main() {
    printf("Welcome to gzl\n");
    printf("\n1) Encryption\n2) Decryption\n");
    printf("Choose: ");

    int sec;
    scanf("%d", &sec);
    while (getchar() != '\n'); // Consume the newline character left in the buffer

    char message[1024];
    unsigned char *ciphertext;
    char ciphertextm[1024];
    unsigned char *key;
    char keym[1024];
    int len;

    switch (sec) {
        case 1:
            printf("Write message: ");
            fgets(message, sizeof(message), stdin);
            len = strlen(message);
            printf("\nOriginal: %s\n", message);
            encrypt(message, &ciphertext, &key);
            printf("Ciphertext (hex): ");
            print_hex(ciphertext, len);
            printf("Key (hex): ");
            print_hex(key, len);
            printf("Decrypted: ");
            for (int i = 0; i < len; i++) {
                putchar(ciphertext[i] ^ key[i]);
            }
            free(ciphertext);
            free(key);
            break;
        case 2:
            printf("Write Ciphertext (hex): ");
            fgets(ciphertextm, sizeof(ciphertextm), stdin);
            int ciphertext_len;
            unsigned char *ciphertext_bin = hex_to_bin(ciphertextm, &ciphertext_len);

            printf("Write Key (hex): ");
            fgets(keym, sizeof(keym), stdin);
            int key_len;
            unsigned char *key_bin = hex_to_bin(keym, &key_len);

            if (ciphertext_len != key_len) {
                printf("Error: Ciphertext and key lengths do not match.\n");
                free(ciphertext_bin);
                free(key_bin);
                return 1;
            }

            printf("Decrypted: ");
            for (int i = 0; i < ciphertext_len; i++) {
                putchar(ciphertext_bin[i] ^ key_bin[i]);
            }
            printf("\n");

            free(ciphertext_bin);
            free(key_bin);
            break;
    }

    return 0;
}
