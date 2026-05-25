#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100
#define MAX_NOME 100
#define MAX_TELEFONE 20
#define MAX_CPF 15

typedef struct {
    int numero_conta;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char telefone[MAX_TELEFONE];
    float saldo;
} Conta;

int buscarConta(Conta cadastro[], int num_contas, int numero_conta) {
    if (num_contas == 0) {
        return -1;
    }
    
    for (int i = 0; i < num_contas; i++) {
        if (cadastro[i].numero_conta == numero_conta) {
            return i;
        }
    }
    
    return -2;
}

void cadastrarConta(Conta cadastro[], int *num_contas, int numero_conta) {
    if (*num_contas >= MAX_CONTAS) {
        printf("ERRO: Cadastro cheio!\n");
        return;
    }
    
    int posicao = buscarConta(cadastro, *num_contas, numero_conta);
    
    if (posicao != -2) {
        printf("ERRO: Numero de conta %d ja esta cadastrado!\n", numero_conta);
        return;
    }
    
    cadastro[*num_contas].numero_conta = numero_conta;
    
    printf("Digite o nome do cliente: ");
    fgets(cadastro[*num_contas].nome, MAX_NOME, stdin);
    cadastro[*num_contas].nome[strcspn(cadastro[*num_contas].nome, "\n")] = 0;
    
    printf("Digite o CPF: ");
    fgets(cadastro[*num_contas].cpf, MAX_CPF, stdin);
    cadastro[*num_contas].cpf[strcspn(cadastro[*num_contas].cpf, "\n")] = 0;
    
    printf("Digite o telefone para contato: ");
    fgets(cadastro[*num_contas].telefone, MAX_TELEFONE, stdin);
    cadastro[*num_contas].telefone[strcspn(cadastro[*num_contas].telefone, "\n")] = 0;
    
    cadastro[*num_contas].saldo = 0.0;
    
    (*num_contas)++;
    
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(Conta cadastro[], int num_contas, int numero_conta) {
    int posicao = buscarConta(cadastro, num_contas, numero_conta);
    
    if (posicao == -1) {
        printf("ERRO: Cadastro vazio!\n");
    } else if (posicao == -2) {
        printf("ERRO: Conta %d nao esta cadastrada!\n", numero_conta);
    } else {
        printf("\n=== DADOS DA CONTA ===\n");
        printf("Conta: %d\n", cadastro[posicao].numero_conta);
        printf("Titular: %s\n", cadastro[posicao].nome);
        printf("Saldo: R$ %.2f\n", cadastro[posicao].saldo);
    }
}

void fazerDeposito(Conta cadastro[], int num_contas, int numero_conta) {
    int posicao = buscarConta(cadastro, num_contas, numero_conta);
    
    if (posicao == -1) {
        printf("ERRO: Cadastro vazio!\n");
    } else if (posicao == -2) {
        printf("ERRO: Conta %d nao esta cadastrada!\n", numero_conta);
    } else {
        float valor;
        printf("Digite o valor do deposito: R$ ");
        scanf("%f", &valor);
        while (getchar() != '\n');
        
        if (valor > 0) {
            cadastro[posicao].saldo += valor;
            printf("Deposito realizado com sucesso!\n");
            printf("Novo saldo: R$ %.2f\n", cadastro[posicao].saldo);
        } else {
            printf("ERRO: Valor invalido!\n");
        }
    }
}

void fazerSaque(Conta cadastro[], int num_contas, int numero_conta) {
    int posicao = buscarConta(cadastro, num_contas, numero_conta);
    
    if (posicao == -1) {
        printf("ERRO: Cadastro vazio!\n");
    } else if (posicao == -2) {
        printf("ERRO: Conta %d nao esta cadastrada!\n", numero_conta);
    } else {
        float valor;
        printf("Digite o valor do saque: R$ ");
        scanf("%f", &valor);
        while (getchar() != '\n');
        
        if (valor <= 0) {
            printf("ERRO: Valor invalido!\n");
        } else if (valor > cadastro[posicao].saldo) {
            printf("ERRO: Saldo insuficiente!\n");
            printf("Saldo disponivel: R$ %.2f\n", cadastro[posicao].saldo);
        } else {
            cadastro[posicao].saldo -= valor;
            printf("Saque realizado com sucesso!\n");
            printf("Novo saldo: R$ %.2f\n", cadastro[posicao].saldo);
        }
    }
}

void exibirTodasContas(Conta cadastro[], int num_contas) {
    if (num_contas == 0) {
        printf("\nNenhuma conta cadastrada.\n");
        return;
    }
    
    printf("\n=== LISTA DE CONTAS ===\n");
    for (int i = 0; i < num_contas; i++) {
        printf("Conta: %d | Titular: %s | Telefone: %s\n", 
               cadastro[i].numero_conta, 
               cadastro[i].nome, 
               cadastro[i].telefone);
    }
}

int main() {
    Conta contas_corrente[MAX_CONTAS];
    Conta contas_poupanca[MAX_CONTAS];
    int num_corrente = 0;
    int num_poupanca = 0;
    int opcao, tipo_conta, numero_conta;
    
    do {
        printf("\n=== BANCO DINHEIRO CERTO ===\n");
        printf("1 - Cadastrar conta corrente\n");
        printf("2 - Cadastrar conta poupanca\n");
        printf("3 - Consultar saldo\n");
        printf("4 - Fazer deposito\n");
        printf("5 - Fazer saque\n");
        printf("6 - Exibir todas as contas corrente\n");
        printf("7 - Exibir todas as contas poupanca\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');
        
        switch (opcao) {
            case 1:
                printf("Digite o numero da nova conta corrente: ");
                scanf("%d", &numero_conta);
                while (getchar() != '\n');
                cadastrarConta(contas_corrente, &num_corrente, numero_conta);
                break;
                
            case 2:
                printf("Digite o numero da nova conta poupanca: ");
                scanf("%d", &numero_conta);
                while (getchar() != '\n');
                cadastrarConta(contas_poupanca, &num_poupanca, numero_conta);
                break;
                
            case 3:
                printf("Digite o tipo (1-Corrente, 2-Poupanca): ");
                scanf("%d", &tipo_conta);
                printf("Digite o numero da conta: ");
                scanf("%d", &numero_conta);
                while (getchar() != '\n');
                
                if (tipo_conta == 1) {
                    consultarSaldo(contas_corrente, num_corrente, numero_conta);
                } else if (tipo_conta == 2) {
                    consultarSaldo(contas_poupanca, num_poupanca, numero_conta);
                } else {
                    printf("Tipo de conta invalido!\n");
                }
                break;
                
            case 4:
                printf("Digite o tipo (1-Corrente, 2-Poupanca): ");
                scanf("%d", &tipo_conta);
                printf("Digite o numero da conta: ");
                scanf("%d", &numero_conta);
                while (getchar() != '\n');
                
                if (tipo_conta == 1) {
                    fazerDeposito(contas_corrente, num_corrente, numero_conta);
                } else if (tipo_conta == 2) {
                    fazerDeposito(contas_poupanca, num_poupanca, numero_conta);
                } else {
                    printf("Tipo de conta invalido!\n");
                }
                break;
                
            case 5:
                printf("Digite o tipo (1-Corrente, 2-Poupanca): ");
                scanf("%d", &tipo_conta);
                printf("Digite o numero da conta: ");
                scanf("%d", &numero_conta);
                while (getchar() != '\n');
                
                if (tipo_conta == 1) {
                    fazerSaque(contas_corrente, num_corrente, numero_conta);
                } else if (tipo_conta == 2) {
                    fazerSaque(contas_poupanca, num_poupanca, numero_conta);
                } else {
                    printf("Tipo de conta invalido!\n");
                }
                break;
                
            case 6:
                exibirTodasContas(contas_corrente, num_corrente);
                break;
                
            case 7:
                exibirTodasContas(contas_poupanca, num_poupanca);
                break;
                
            case 0:
                printf("Encerrando programa...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}