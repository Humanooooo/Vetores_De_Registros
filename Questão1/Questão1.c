#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 26
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    int num_veiculos;
    int num_acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    printf("\n=== COLETA DE DADOS DOS ESTADOS ===\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\nEstado %d de %d:\n", i + 1, NUM_ESTADOS);
        printf("Nome do estado: ");
        fgets(estados[i].nome, MAX_NOME, stdin);
        estados[i].nome[strcspn(estados[i].nome, "\n")] = 0;
        
        printf("Numero de veiculos (2007): ");
        scanf("%d", &estados[i].num_veiculos);
        
        printf("Numero de acidentes (2007): ");
        scanf("%d", &estados[i].num_acidentes);
        while (getchar() != '\n');
    }
}

void encontrarMaiorMenorAcidentes(Estado estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    
    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > estados[*indiceMaior].num_acidentes) {
            *indiceMaior = i;
        }
        if (estados[i].num_acidentes < estados[*indiceMenor].num_acidentes) {
            *indiceMenor = i;
        }
    }
}

float calcularPercentual(Estado estados[], int indice) {
    if (estados[indice].num_veiculos == 0) {
        return 0.0;
    }
    return (float)estados[indice].num_acidentes / estados[indice].num_veiculos * 100;
}

float calcularMediaAcidentes(Estado estados[]) {
    int total_acidentes = 0;
    
    for (int i = 0; i < NUM_ESTADOS; i++) {
        total_acidentes += estados[i].num_acidentes;
    }
    
    return (float)total_acidentes / NUM_ESTADOS;
}

void exibirEstadosAcimaMedia(Estado estados[], float media) {
    printf("\n=== ESTADOS ACIMA DA MEDIA DE ACIDENTES ===\n");
    printf("Media do pais: %.2f acidentes\n\n", media);
    
    int encontrou = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > media) {
            printf("%s: %d acidentes\n", estados[i].nome, estados[i].num_acidentes);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum estado esta acima da media.\n");
    }
}

int main() {
    Estado estados[NUM_ESTADOS];
    int indiceMaior, indiceMenor;
    
    coletarDados(estados);
    
    encontrarMaiorMenorAcidentes(estados, &indiceMaior, &indiceMenor);
    
    printf("\n=== RESULTADOS ===\n");
    printf("Maior numero de acidentes: %s - %d acidentes\n", 
           estados[indiceMaior].nome, estados[indiceMaior].num_acidentes);
    printf("Menor numero de acidentes: %s - %d acidentes\n", 
           estados[indiceMenor].nome, estados[indiceMenor].num_acidentes);
    
    printf("\n=== PERCENTUAL DE VEICULOS ENVOLVIDOS EM ACIDENTES ===\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        float percentual = calcularPercentual(estados, i);
        printf("%s: %.2f%%\n", estados[i].nome, percentual);
    }
    
    float media = calcularMediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2f\n", media);
    
    exibirEstadosAcimaMedia(estados, media);
    
    return 0;
}