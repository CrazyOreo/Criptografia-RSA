#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int modPow(int a, int b, int m) {
    if (b == 0)
        return 1;
    int result = modPow(a, b / 2, m);
    result = (result * result) % m;
    if (b % 2 == 1)
        result = (result * a) % m;
    return result;
}

void rsaEncrypt(char *plainText, int n, int e) {
    int plainTextLength = strlen(plainText);
    int cipherText[plainTextLength];

    for (int i = 0; i < plainTextLength; i++) {
        cipherText[i] = modPow(plainText[i], e, n);
    }

    printf("Texto Criptografado: ");
    system ("cls");
    for (int i = 0; i < plainTextLength; i++) {
        printf("%d ", cipherText[i]);
    }
    printf("\n");

    FILE *file = fopen("cipher.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < plainTextLength; i++) {
            fprintf(file, "%d ", cipherText[i]);
        }
        fclose(file);
        printf("Texto Criptografado foi salvo no arquivo 'cipher.txt'\n\n");
    } else {
        printf("Erro ao criar o arquivo 'cipher.txt'\n");
    }
}

void rsaDecrypt(char *inputFile, int n, int d) {
    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    char outputText[101];
    int i = 0;
    int cipherText;

    while (fscanf(file, "%d", &cipherText) != EOF) {
        int decryptedText = modPow(cipherText, d, n);
        outputText[i++] = decryptedText;
    }

    outputText[i] = '\0';
    fclose(file);

    file = fopen("decrypted.txt", "w");
    if (file != NULL) {
        system ("cls");
        fprintf(file, "%s", outputText);
        fclose(file);
        printf("Texto Descriptografado foi salvo no arquivo 'decrypted.txt'\n\n");
    } else {
        system ("color 4");
        printf("Erro ao criar o arquivo 'decrypted.txt'\n");
    }
}

int main() {
    int p, q, n, e, d, phi;
    char inputText[101];
    int choice;

    while (1) {
            system ("color F");
        printf("+----------------------+\n");
        printf("|Criptossistema RSA    |\n");
        printf("|1. Criptografar       |\n");
        printf("|2. Descriptografar    |\n");
        printf("|3. Encerrar o programa|\n");
        printf("+----------------------+\n");
        printf("-->");
        scanf("%d", &choice);

        if (choice == 3) {
                system ("cls");
                system ("color B");
            printf ("\n");
            printf ("Programa encerrado\n");
            printf ("Agradecimentos especiais\n\n");
            printf ("+---------------------------------------------+\n");
            printf ("|Paulo - Desenvolvimento da criptografia      |\n");
            printf ("|Pedro - Visibilidade do codigo               |\n");
            printf ("|Tiago - Resumo expandido                     |\n");
            printf ("|Jefferson - Sub-Desenvolvimento do codigo    |\n");
            printf ("|Victor Hugo - Finalizacao do resumo expandido|\n");
            printf ("|                                             |\n");
            printf ("|Agradecemos sua atencao!!                    |\n");
            printf ("+---------------------------------------------+\n\n");
            break;
        }

        if (choice != 1 && choice != 2) {
        system ("color 4");
            printf("Escolha invalida.\n");
            continue;
        }

        if (choice == 1) {
            printf("Digite o texto (maximo de 100 caracteres): ");
            getchar();
            fgets(inputText, sizeof(inputText), stdin);
            inputText[strcspn(inputText, "\n")] = 0;

            // Escolha de números primos adequados
            p = 61;
            q = 53;

            n = p * q;
            phi = (p - 1) * (q - 1);

            // Escolha de e adequado
            e = 17;

            d = modInverse(e, phi);

            rsaEncrypt(inputText, n, e);
        } else if (choice == 2) {
            rsaDecrypt("cipher.txt", n, d);
        }
    }

    return 0;
}
