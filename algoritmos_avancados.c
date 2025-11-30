#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições de Estrutura ---

// 1. Definição do nó (cômodo) da Árvore Binária
typedef struct No {
    char nome[50];       // Nome do cômodo (Sala de estar, Cozinha, etc.)
    struct No *esquerda; // Ponteiro para o cômodo da esquerda
    struct No *direita;  // Ponteiro para o cômodo da direita
} Comodo;


// --- Protótipos das Funções ---

Comodo* criarSala(const char *nome);
void montarMansao();
void explorarMansao(Comodo *atual);
void limpar_buffer();


// --- Variáveis Globais ---

// O ponteiro raiz para o início da mansão (Hall de entrada)
Comodo *hall_entrada = NULL;


// --- Função Auxiliar: Limpar o Buffer ---
// Essencial para remover o '\n' do buffer após o uso de scanf/getchar
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


// --- Função: Criar um Novo Cômodo (Nó) ---
// Aloca memória dinamicamente para um novo cômodo e o inicializa.
Comodo* criarSala(const char *nome) {
    // Aloca espaço para a nova estrutura Comodo
    Comodo *novo_comodo = (Comodo *)malloc(sizeof(Comodo));
    
    // Verifica se a alocação foi bem-sucedida
    if (novo_comodo == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    
    // Inicializa o nome e os ponteiros
    strcpy(novo_comodo->nome, nome);
    novo_comodo->esquerda = NULL;
    novo_comodo->direita = NULL;
    
    return novo_comodo;
}


// --- Função: Montar a Mansão (Árvore Binária Definida) ---
// Define a estrutura da mansão usando alocação dinâmica.
void montarMansao() {
    // Nível 0 (Raiz)
    hall_entrada = criarSala("Hall de Entrada");

    // Nível 1
    Comodo *sala_estar = criarSala("Sala de Estar");
    Comodo *escritorio = criarSala("Escritorio");
    hall_entrada->esquerda = sala_estar;
    hall_entrada->direita = escritorio;

    // Nível 2
    Comodo *cozinha = criarSala("Cozinha");
    Comodo *biblioteca = criarSala("Biblioteca");
    Comodo *quarto_principal = criarSala("Quarto Principal");
    sala_estar->esquerda = cozinha;
    sala_estar->direita = biblioteca;
    escritorio->direita = quarto_principal; // Escritorio so tem caminho a direita

    // Nível 3 (Nós-Folha)
    Comodo *jardim = criarSala("Jardim");        // Nó-Folha 1
    Comodo *dispensa = criarSala("Dispensa");    // Nó-Folha 2
    Comodo *varanda = criarSala("Varanda");      // Nó-Folha 3
    cozinha->esquerda = jardim;
    cozinha->direita = dispensa;
    biblioteca->esquerda = varanda;
    // O quarto principal é um nó-folha, nao tem filhos.

    // Nível 4 (Nó-Folha)
    Comodo *porao = criarSala("Porao");         // Nó-Folha 4
    dispensa->esquerda = porao;
    // dispensa->direita = NULL (Folha na direita)
}


// --- Função: Explorar a Mansão (Exploração Interativa) ---
void explorarMansao(Comodo *atual) {
    char escolha;
    
    // Enquanto o cômodo atual não for nulo e não for um nó-folha
    while (atual != NULL) {
        // Exibe o cômodo atual (requisito: exibir o nome de cada sala visitada)
        printf("\nVoce esta em: %s\n", atual->nome);

        // Verifica se é um nó-folha (sem filhos ou sem caminhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n--- EXPLORACAO CONCLUIDA ---\n");
            printf("Voce chegou a um comodo que nao possui saidas (No-Folha): %s\n", atual->nome);
            break; // Sai do loop (exploracao continua ate um no-folha)
        }

        // --- Opções de Navegação ---
        printf("Caminhos disponiveis:\n");
        if (atual->esquerda != NULL) {
            printf("[E] Esquerda (para %s)\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("[D] Direita (para %s)\n", atual->direita->nome);
        }
        printf("Escolha (e/d): ");

        // Leitura da escolha do usuário
        if (scanf(" %c", &escolha) != 1) { // Espaço antes de %c para ignorar whitespace
            limpar_buffer();
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        // --- Navegação (Altera o nó atual) ---
        if ((escolha == 'e' || escolha == 'E') && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if ((escolha == 'd' || escolha == 'D') && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("Caminho invalido ou nao disponivel. Tente novamente.\n");
            // Se a escolha for inválida, o loop continua e o cômodo 'atual' não é alterado.
        }
    }
}


// --- Função Principal ---
int main() {
    printf("--- Simulador de Exploracao da Mansao (Arvore Binaria) ---\n");

    // 1. Cria a estrutura da mansão
    montarMansao();

    // 2. Inicia a exploração a partir do Hall de entrada
    if (hall_entrada != NULL) {
        explorarMansao(hall_entrada);
    } else {
        printf("A mansao nao pode ser montada.\n");
    }

      
    return 0;
}