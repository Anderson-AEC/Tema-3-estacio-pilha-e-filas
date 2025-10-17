# Jogo Tetris Stack - Gerenciador de Peças (Fila e Pilha)

[cite_start]Este projeto implementa a lógica de gerenciamento de peças para o jogo fictício **Tetris Stack**, desenvolvido como parte de um desafio de programação proposto pela ByteBros[cite: 1353]. [cite_start]O objetivo é aplicar e integrar as estruturas de dados **Fila Circular** e **Pilha Linear** em linguagem C [cite: 1332, 1333, 2540, 2542] [cite_start]para simular a chegada de peças futuras (Fila) e uma área de reserva estratégica (Pilha)[cite: 1357, 2169].

[cite_start]Esta implementação corresponde ao **Nível Mestre** do desafio [cite: 2252][cite_start], integrando ambas as estruturas e oferecendo funcionalidades avançadas de troca entre elas[cite: 2492].

## 🚀 Funcionalidades Implementadas

[cite_start]O programa gerencia uma Fila Circular (capacidade 5) [cite: 2491, 2498] [cite_start]e uma Pilha (capacidade 3) [cite: 2491, 2499] de peças de Tetris, permitindo ao jogador realizar as seguintes ações estratégicas:

* [cite_start]**Visualizar Estado Atual:** Exibe o conteúdo da Fila de Peças Futuras e da Pilha de Reserva[cite: 2504, 2507].
* [cite_start]**Jogar Peça:** Remove a peça da frente da Fila (Dequeue)[cite: 2501].
* [cite_start]**Reservar Peça:** Move a peça da frente da Fila para o topo da Pilha (Dequeue + Push), se houver espaço na Pilha[cite: 2502].
* [cite_start]**Usar Peça Reservada:** Remove a peça do topo da Pilha (Pop), simulando seu uso no jogo[cite: 2503].
* [cite_start]**Trocar Peça Atual:** Substitui a peça da frente da Fila pela peça no topo da Pilha, e vice-versa[cite: 2505].
* [cite_start]**Troca Múltipla:** Alterna as 3 primeiras peças da Fila com as 3 peças da Pilha (requer que ambas tenham pelo menos 3 peças)[cite: 2506].
* [cite_start]**Geração Automática de Peças:** A Fila é automaticamente preenchida com uma nova peça gerada aleatoriamente sempre que uma peça é jogada ou reservada, mantendo o fluxo do jogo[cite: 2508, 2515].
* [cite_start]**Interface Interativa:** Um menu simples via terminal guia o jogador através das opções disponíveis[cite: 2521, 2523].

## 💡 Conceitos Trabalhados

Este projeto aplica diversos conceitos fundamentais da programação em C e estruturas de dados, conforme ensinado no material de referência:

* [cite_start]Implementação de **Fila Circular** com Array, utilizando lógica de índices com módulo para reaproveitamento de espaço[cite: 1427, 1784, 2540].
* [cite_start]Implementação de **Pilha Linear** com Array, utilizando um índice `topo` para controle LIFO[cite: 1829, 2175, 2542].
* [cite_start]Uso de **`structs`** para representar dados complexos (a `Peca` com `nome` e `id`)[cite: 1785, 2543].
* [cite_start]**Modularização** do código em funções com responsabilidades bem definidas (inicializar, inserir, remover, mostrar, trocar, etc.)[cite: 1787, 2545].
* [cite_start]**Integração e Comunicação** entre diferentes estruturas de dados (transferência e troca de elementos entre Fila e Pilha)[cite: 2263, 2541].
* Manipulação de **ponteiros** para modificar as estruturas (passagem por referência para Fila e Pilha).
* Uso de **`#define`** para constantes (capacidades da Fila e Pilha).
* [cite_start]**Entrada e Saída Padrão** (`printf`, `scanf`) para interação com o usuário[cite: 1786, 2544].
* [cite_start]**Lógica Condicional** (`if`, `switch`) e **Laços** (`for`, `while`, `do-while`) para controle de fluxo e validações[cite: 1788, 2546].
* [cite_start]Geração de **números aleatórios** (`rand`, `srand`) para simular a chegada de peças[cite: 2181, 2515].

## 🔧 Como Compilar e Executar

1.  **Pré-requisitos:** Você precisa de um compilador C instalado (como o GCC).
2.  **Salvar o Código:** Salve o código-fonte em um arquivo chamado `tetris_stack_mestre.c` (ou outro nome de sua preferência).
3.  **Compilar:** Abra um terminal ou prompt de comando, navegue até o diretório onde salvou o arquivo e execute o comando de compilação:
    ```bash
    gcc tetris_stack_mestre.c -o tetris_stack_mestre
    ```
    Isso criará um arquivo executável chamado `tetris_stack_mestre` (ou `tetris_stack_mestre.exe` no Windows).
4.  **Executar:** Execute o programa compilado:
    * No Linux/macOS:
        ```bash
        ./tetris_stack_mestre
        ```
    * No Windows:
        ```bash
        .\tetris_stack_mestre.exe
        ```
    ou
    ```bash
    tetris_stack_mestre.exe
    ```
5.  **Interagir:** Siga as instruções do menu exibido no terminal para interagir com o gerenciador de peças.

## 🎮 Exemplo de Uso

Ao executar o programa, você verá uma saída semelhante a esta:
