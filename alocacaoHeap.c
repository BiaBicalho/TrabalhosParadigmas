#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TAM_HEAP 10

// Enum com as estratégias de alocação
typedef enum {
    FIRST_FIT,
    WORST_FIT
} AlocacaoEstrategia;

bool heap[TAM_HEAP]; // false = livre, true = ocupado
AlocacaoEstrategia estrategiaAtual = FIRST_FIT; // Estratégia padrão

// Exibe o estado atual da memória simulada
void exibeHeap() {
    printf("\nEstado do Heap: ");
    for (int i = 0; i < TAM_HEAP; i++)
        printf("%c", heap[i] ? '@' : '.');
    printf("\n");
}

// Libera toda a memória
void liberar() {
    memset(heap, false, sizeof(heap)); // Garante que tudo fica livre
    printf("Memória completamente liberada!\n");
}

// Estratégias de Alocação

// First Fit – procura o primeiro espaço livre que caiba
int firstFit(int blocos) {
    int livres = 0;
    for (int i = 0; i < TAM_HEAP; i++) {
        if (!heap[i]) { // bloco livre
            livres++;
            if (livres == blocos)
                return i - blocos + 1;
        } else {
            livres = 0; // reinicia contagem
        }
    }
    return -1;
}

// Worst Fit – procura o maior espaço livre
int worstFit(int blocos) {
    int maiorInicio = -1, maiorTam = 0;
    int i = 0;
    while (i < TAM_HEAP) {
        if (!heap[i]) {
            int inicio = i;
            int tam = 0;
            while (i < TAM_HEAP && !heap[i]) {
                tam++;
                i++;
            }
            if (tam > maiorTam) {
                maiorTam = tam;
                maiorInicio = inicio;
            }
        } else {
            i++;
        }
    }
    if (maiorTam >= blocos)
        return maiorInicio;
    return -1;
}

// Funções

// Aloca blocos conforme a estratégia escolhida
void alocar(int blocos) {
    if (blocos <= 0 || blocos > TAM_HEAP) {
        printf("Quantidade inválida de blocos.\n");
        return;
    }

    int inicio = -1;
    if (estrategiaAtual == FIRST_FIT)
        inicio = firstFit(blocos);
    else if (estrategiaAtual == WORST_FIT)
        inicio = worstFit(blocos);

    if (inicio != -1) {
        for (int i = inicio; i < inicio + blocos; i++)
            heap[i] = true;
        printf("Alocação realizada do bloco %d até %d.\n", inicio, inicio + blocos - 1);
    } else {
        printf("Não há espaço suficiente para alocar %d blocos.\n", blocos);
    }
}

// Libera blocos de um intervalo específico
void deletarVariavel(int inicio, int blocos) {
    if (inicio < 0 || inicio >= TAM_HEAP || blocos <= 0 || inicio + blocos > TAM_HEAP) {
        printf("Intervalo inválido para deletar.\n");
        return;
    }

    for (int i = inicio; i < inicio + blocos; i++)
        heap[i] = false;

    printf("Blocos %d até %d foram liberados.\n", inicio,(inicio + blocos) - 1);
}

// Troca a estratégia atual
void alterarEstrategia() {
    if (estrategiaAtual == FIRST_FIT) {
        estrategiaAtual = WORST_FIT;
        printf("Estratégia alterada para WORST FIT.\n");
    } else {
        estrategiaAtual = FIRST_FIT;
        printf("Estratégia alterada para FIRST FIT.\n");
    }
}

int main() {
    memset(heap, false, sizeof(heap)); // Inicializa tudo como livre
    int opcao, blocos, inicio;

    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Exibir Heap\n");
        printf("2 - Alocar blocos\n");
        printf("3 - Deletar variável (liberar parte)\n");
        printf("4 - Liberar toda memória\n");
        printf("5 - Trocar estratégia\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibeHeap();
                break;
            case 2:
                printf("Quantos blocos deseja alocar? ");
                scanf("%d", &blocos);
                alocar(blocos);
                break;
            case 3:
                printf("Informe o bloco inicial e a quantidade: ");
                scanf("%d %d", &inicio, &blocos);
                deletarVariavel(inicio, blocos);
                break;
            case 4:
                liberar();
                break;
            case 5:
                alterarEstrategia();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}