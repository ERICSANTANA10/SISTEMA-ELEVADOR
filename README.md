# 🛗 Sistema de Elevador Inteligente com Sensores Hall e LCD

Este repositório contém o desenvolvimento de um protótipo de elevador automatizado de 4 andares. O projeto integra controle de hardware via Arduino, detecção magnética de posição e uma interface visual para o usuário.


## 🚀 O que este projeto faz?

O sistema gerencia a movimentação da cabine entre o Térreo e o 3º andar, utilizando uma lógica de estados para garantir precisão e segurança:

1.  **Identificação de Andar:** Utiliza sensores de efeito Hall para detectar a passagem da cabine por ímãs posicionados em cada nível.
2.  **Interface LCD:** Exibe em tempo real o status do elevador (Subindo, Descendo ou Aguardando) e o andar atual.
3.  **Controle de Motor:** Gerencia o sentido e a velocidade de um motor DC através de uma Ponte H L9110s.
4.  **Auto-Posicionamento:** Ao ser ligado, o sistema executa uma rotina de busca para encontrar o andar de referência mais próximo.

## 🛠️ Tecnologias Utilizadas

*   **Linguagem:** C++ (Arduino)
*   **Hardware:** 
    *   Arduino Uno (Microcontrolador)
    *   Sensores Hall (Sensores de proximidade magnética)
    *   Ponte H L9110s (Driver de potência para o motor)
    *   Display LCD 16x2 com módulo I2C
    *   Botões Push-button para chamadas de cabine

## 📁 Estrutura do Código (`ELEVADOR.ino`)

O código foi desenvolvido de forma modular para facilitar a manutenção e escalabilidade:

*   `verificarBotoes()`: Faz a leitura das entradas e define o andar alvo.
*   `procurarAndarMaisProximo()`: Função de calibração inicial (Homing).
*   `sobe()` / `desce()` / `parado()`: Funções de baixo nível para controle direto da Ponte H.
*   `atualizarDisplay()`: Sistema de cache para evitar "flicker" (piscadas) no LCD.

## ⚙️ Pinagem de Referência

| Componente | Pinos Arduino |
| :--- | :--- |
| **Sensores Hall (T a 3)** | 4, 5, 6, 7 |
| **Botões de Chamada** | 8, 11, 12, 13 |
| **Driver L9110s** | 9, 10 |
| **Display LCD** | SDA (A4), SCL (A5) |
