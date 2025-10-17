/*
 * =================================================================================
 * Desafio Nível Mestre: Tetris Stack - Integração Fila e Pilha
 * =================================================================================
 * Implementa a fila circular de peças futuras e a pilha de reserva,
 * permitindo jogar, reservar, usar peças reservadas e realizar trocas
 * estratégicas entre as duas estruturas.
 */

#include <stdio.h>
#include <stdlib.h> // Para rand(), srand()
#include <string.h> // Para strcpy()
#include <time.h>   // Para time() na inicialização do srand()

// --- Definições Globais e Estruturas ---

#define MAX_FILA 5 // Capacidade da Fila [cite: 1164, 1171]
#define MAX_PILHA 3 // Capacidade da Pilha [cite: 1164, 1172]

/*
 * Atributos das peças [cite: 1184]
 * Struct Peca: representa uma peça do jogo.
 */
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L') [cite: 1186]
    int id;     // Identificador único [cite: 1187]
} Peca;

/*
 * Fila circular: armazena as próximas peças.
 * Baseada na implementação de Fila com array e controle circular[cite: 100, 303].
 */
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total; // Contador para facilitar verificação de cheia/vazia
} Fila;

/*
 * Pilha linear: armazena as peças reservadas.
 * Baseada na implementação de Pilha com array e controle de topo[cite: 696].
 */
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// --- Protótipos das Funções ---

// Funções Utilitárias
void limparBuffer();
Peca gerarPeca(); // Gera peças automaticamente [cite: 1188]
void inicializarJogo(Fila *f, Pilha *p); // Preenche a fila inicial

// Funções da Fila (baseadas nos exemplos do PDF) [cite: 167, 278]
void inicializarFila(Fila *f);
int filaVazia(const Fila *f);
int filaCheia(const Fila *f);
void inserirFila(Fila *f, Peca peca); // enqueue [cite: 177]
Peca removerFila(Fila *f);          // dequeue [cite: 212]
void mostrarFila(const Fila *f);

// Funções da Pilha (baseadas nos exemplos do PDF) [cite: 539, 660]
void inicializarPilha(Pilha *p);
int pilhaVazia(const Pilha *p);
int pilhaCheia(const Pilha *p);
void pushPilha(Pilha *p, Peca peca); // push [cite: 553]
Peca popPilha(Pilha *p);             // pop [cite: 583]
Peca peekPilha(const Pilha *p);     // peek (consultar topo) [cite: 612]
void mostrarPilha(const Pilha *p);

// Funções de Interação (Requisitos Funcionais) [cite: 1173]
void jogarPeca(Fila *f);
void reservarPeca(Fila *f, Pilha *p);
void usarPecaReservada(Pilha *p);
void trocarPecaAtual(Fila *f, Pilha *p); // 
void trocaMultipla(Fila *f, Pilha *p);  // 
void mostrarEstadoAtual(const Fila *f, const Pilha *p); // [cite: 1177, 1180]
void exibirMenu();

// Variável global para controlar IDs únicos das peças [cite: 1187]
int proximoId = 0;

// --- Função Principal ---
int main() {
    Fila filaPecas;
    Pilha pilhaReserva;
    int opcao;

    srand(time(NULL)); // Inicializa gerador de números aleatórios para gerarPeca

    inicializarJogo(&filaPecas, &pilhaReserva); // Inicializa e preenche a fila

    do {
        mostrarEstadoAtual(&filaPecas, &pilhaReserva);
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: // Jogar Peça [cite: 1174, 1194]
                jogarPeca(&filaPecas);
                break;
            case 2: // Reservar Peça [cite: 1175, 1194]
                reservarPeca(&filaPecas, &pilhaReserva);
                break;
            case 3: // Usar Peça Reservada [cite: 1176, 1194]
                usarPecaReservada(&pilhaReserva);
                break;
            case 4: // Trocar Peça Atual [cite: 1178, 1194]
                trocarPecaAtual(&filaPecas, &pilhaReserva);
                break;
            case 5: // Troca Múltipla [cite: 1179, 1194]
                trocaMultipla(&filaPecas, &pilhaReserva);
                break;
            case 0: // Sair [cite: 1182, 1194]
                printf("\nEncerrando o Tetris Stack...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao >= 1 && opcao <= 3) { // Gera nova peça se jogou, reservou ou usou da reserva (ajustado - só se jogou ou reservou)
             if (opcao == 1 || opcao == 2) {
                 if (!filaCheia(&filaPecas)) {
                     inserirFila(&filaPecas, gerarPeca()); // Mantém a fila cheia 
                 }
             }
        }


        // Pausa antes de mostrar o próximo estado (exceto ao sair)
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            // system("cls || clear"); // Limpa a tela (opcional)
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Limpa o buffer de entrada (stdin)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Gera uma nova peça com tipo aleatório e ID único. [cite: 1188]
 * Tipos: 'I', 'O', 'T', 'L' [cite: 1186]
 */
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // Escolhe um tipo aleatoriamente
    nova.id = proximoId++;         // Atribui ID único e incrementa [cite: 1187]
    return nova;
}

// Inicializa Fila e Pilha e preenche a Fila inicial 
void inicializarJogo(Fila *f, Pilha *p) {
    inicializarFila(f);
    inicializarPilha(p);
    printf("Iniciando Tetris Stack...\n");
    printf("Gerando pecas iniciais para a fila...\n");
    for (int i = 0; i < MAX_FILA; i++) {
        inserirFila(f, gerarPeca());
    }
    printf("Fila inicializada!\n");
}

// --- Funções da Fila ---

// Inicializa os ponteiros/contadores da fila [cite: 316]
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0; // Começa vazia
}

// Verifica se a fila está vazia [cite: 325]
int filaVazia(const Fila *f) {
    return f->total == 0;
}

// Verifica se a fila está cheia [cite: 325]
int filaCheia(const Fila *f) {
    return f->total == MAX_FILA;
}

/*
 * Insere um elemento no final da fila (enqueue) [cite: 177, 339]
 * Usa lógica circular para o índice 'fim' [cite: 100, 136]
 */
void inserirFila(Fila *f, Peca peca) {
    if (filaCheia(f)) {
        printf("DEBUG: Fila cheia, nao inseriu a peca %c%d\n", peca.nome, peca.id);
        return; // Não insere se cheia
    }
    f->itens[f->fim] = peca;              // Insere na posição 'fim'
    f->fim = (f->fim + 1) % MAX_FILA;    // Avança 'fim' circularmente
    f->total++;                          // Incrementa o total de itens
}

/*
 * Remove e retorna o elemento do início da fila (dequeue) [cite: 212, 339]
 * Usa lógica circular para o índice 'inicio' [cite: 160, 161]
 */
Peca removerFila(Fila *f) {
    Peca vazia = {' ', -1}; // Peça inválida para retorno em caso de erro
    if (filaVazia(f)) {
        printf("DEBUG: Fila vazia, nao removeu.\n");
        return vazia; // Retorna peça inválida se vazia
    }
    Peca removida = f->itens[f->inicio];     // Pega o item do início
    f->inicio = (f->inicio + 1) % MAX_FILA; // Avança 'inicio' circularmente
    f->total--;                             // Decrementa o total
    return removida;
}

// Exibe os elementos da fila na ordem (Início -> Fim) [cite: 366]
void mostrarFila(const Fila *f) {
    printf("Fila de pecas \t: ");
    if (filaVazia(f)) {
        printf("[Vazia]");
    } else {
        int indice = f->inicio;
        for (int i = 0; i < f->total; i++) {
            // Formato [NomeID] [cite: 1191]
            printf("[%c%d] ", f->itens[indice].nome, f->itens[indice].id);
            indice = (indice + 1) % MAX_FILA; // Move para o próximo índice circularmente
        }
    }
    printf("\n");
}

// --- Funções da Pilha ---

// Inicializa o topo da pilha [cite: 716]
void inicializarPilha(Pilha *p) {
    p->topo = -1; // -1 indica pilha vazia
}

// Verifica se a pilha está vazia [cite: 724]
int pilhaVazia(const Pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha está cheia [cite: 732]
int pilhaCheia(const Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

/*
 * Insere um elemento no topo da pilha (push) [cite: 553, 741]
 */
void pushPilha(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("DEBUG: Pilha cheia, nao inseriu a peca %c%d\n", peca.nome, peca.id);
        return; // Não insere se cheia
    }
    p->topo++;             // Avança o topo
    p->itens[p->topo] = peca; // Insere a peça na nova posição do topo
}

/*
 * Remove e retorna o elemento do topo da pilha (pop) [cite: 583, 755]
 */
Peca popPilha(Pilha *p) {
    Peca vazia = {' ', -1};
    if (pilhaVazia(p)) {
        printf("DEBUG: Pilha vazia, nao removeu.\n");
        return vazia; // Retorna peça inválida se vazia
    }
    Peca removida = p->itens[p->topo]; // Pega o item do topo
    p->topo--;                         // Decrementa o topo
    return removida;
}

/*
 * Retorna o elemento do topo sem remover (peek) [cite: 612, 769]
 */
Peca peekPilha(const Pilha *p) {
    Peca vazia = {' ', -1};
    if (pilhaVazia(p)) {
        return vazia;
    }
    return p->itens[p->topo]; // Retorna o item do topo
}

// Exibe os elementos da pilha (Topo -> Base) [cite: 781]
void mostrarPilha(const Pilha *p) {
    printf("Pilha de reserva \t: ");
    if (pilhaVazia(p)) {
        printf("[Vazia]");
    } else {
        printf("(Topo -> Base): ");
        for (int i = p->topo; i >= 0; i--) {
            // Formato [NomeID] [cite: 1191]
            printf("[%c%d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

// --- Funções de Interação ---

// Remove a peça da frente da fila ("jogar") [cite: 1174]
void jogarPeca(Fila *f) {
    printf("\nAcao: Jogar peca da fila.\n");
    if (filaVazia(f)) {
        printf("Erro: Fila esta vazia. Nao ha pecas para jogar.\n");
        return;
    }
    Peca jogada = removerFila(f);
    printf("Peca [%c%d] jogada!\n", jogada.nome, jogada.id);
}

// Move a peça da frente da fila para a pilha de reserva [cite: 1175]
void reservarPeca(Fila *f, Pilha *p) {
    printf("\nAcao: Enviar peca da fila para a reserva.\n");
    if (filaVazia(f)) {
        printf("Erro: Fila esta vazia. Nenhuma peca para reservar.\n");
        return;
    }
    if (pilhaCheia(p)) {
        printf("Erro: Pilha de reserva esta cheia. Nao pode reservar.\n");
        return;
    }
    Peca reservada = removerFila(f); // Tira da fila
    pushPilha(p, reservada);        // Coloca na pilha
    printf("Peca [%c%d] enviada para a reserva!\n", reservada.nome, reservada.id);
}

// Remove a peça do topo da pilha ("usar") [cite: 1176]
void usarPecaReservada(Pilha *p) {
    printf("\nAcao: Usar peca da reserva.\n");
    if (pilhaVazia(p)) {
        printf("Erro: Pilha de reserva esta vazia. Nenhuma peca para usar.\n");
        return;
    }
    Peca usada = popPilha(p); // Tira da pilha
    printf("Peca [%c%d] usada da reserva!\n", usada.nome, usada.id);
}

/*
 * Troca a peça da frente da fila com o topo da pilha. 
 * Implementado como troca direta dos valores nos arrays.
 */
void trocarPecaAtual(Fila *f, Pilha *p) {
    printf("\nAcao: Trocar peca da frente da fila com topo da pilha.\n");
    if (filaVazia(f)) {
        printf("Erro: Fila vazia. Impossivel trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia. Impossivel trocar.\n");
        return;
    }

    // Pega as peças (sem remover)
    Peca pecaFila = f->itens[f->inicio]; // Peek da fila
    Peca pecaPilha = p->itens[p->topo];  // Peek da pilha

    // Realiza a troca nos arrays
    f->itens[f->inicio] = pecaPilha;
    p->itens[p->topo] = pecaFila;

    printf("Troca realizada: [%c%d] (fila) <-> [%c%d] (pilha)\n",
           f->itens[f->inicio].nome, f->itens[f->inicio].id,
           p->itens[p->topo].nome, p->itens[p->topo].id);
}

/*
 * Troca as 3 primeiras peças da fila com as 3 da pilha. 
 * Requer que ambas tenham pelo menos 3 peças.
 */
void trocaMultipla(Fila *f, Pilha *p) {
    printf("\nAcao: Trocar os 3 primeiros da fila com os 3 da pilha.\n");

    // Verifica se há peças suficientes
    if (f->total < 3) {
        printf("Erro: Fila nao tem 3 pecas para trocar.\n");
        return;
    }
    // Para pilha com MAX_PILHA = 3, topo == 2 significa cheia (3 elementos)
    if (p->topo < MAX_PILHA - 1) {
        printf("Erro: Pilha nao tem 3 pecas para trocar.\n");
        return;
    }

    printf("Realizando troca multipla...\n");

    // Índices da Fila (circulares)
    int idxFila1 = f->inicio;
    int idxFila2 = (f->inicio + 1) % MAX_FILA;
    int idxFila3 = (f->inicio + 2) % MAX_FILA;

    // Índices da Pilha (topo para base)
    int idxPilha1 = p->topo;     // Topo
    int idxPilha2 = p->topo - 1;
    int idxPilha3 = p->topo - 2; // Base (dos 3)

    // Troca usando uma variável temporária para cada par
    Peca temp;

    // Troca 1 (Frente da Fila <-> Base da Pilha)
    temp = f->itens[idxFila1];
    f->itens[idxFila1] = p->itens[idxPilha3];
    p->itens[idxPilha3] = temp;

    // Troca 2 (Segundo da Fila <-> Meio da Pilha)
    temp = f->itens[idxFila2];
    f->itens[idxFila2] = p->itens[idxPilha2];
    p->itens[idxPilha2] = temp;

    // Troca 3 (Terceiro da Fila <-> Topo da Pilha)
    temp = f->itens[idxFila3];
    f->itens[idxFila3] = p->itens[idxPilha1];
    p->itens[idxPilha1] = temp;

    printf("Troca multipla concluida!\n");
}

// Exibe o estado atual da Fila e da Pilha [cite: 1177]
void mostrarEstadoAtual(const Fila *f, const Pilha *p) {
    printf("\n--- ESTADO ATUAL DO JOGO ---\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("-----------------------------\n");
}

// Exibe o menu de opções para o jogador
void exibirMenu() {
    printf("\nOpcoes de Acao:\n");
    printf("1. Jogar peca da fila\n");
    printf("2. Enviar peca da fila para a reserva\n");
    printf("3. Usar peca da reserva\n");
    printf("4. Trocar peca atual (Fila <-> Pilha)\n");
    printf("5. Troca Multipla (3 Fila <-> 3 Pilha)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}