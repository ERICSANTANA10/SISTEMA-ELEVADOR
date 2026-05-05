Sistema de Elevador Inteligente - Protótipo com Arduino 🛗
Este projeto consiste no desenvolvimento de um sistema de elevador automatizado utilizando a plataforma Arduino. O objetivo é simular o funcionamento real de um elevador, controlando o movimento entre andares, parada precisa e interface de comando.

🚀 O que este projeto faz?
O código controla a lógica de movimentação de um elevador físico ou simulado, respondendo a comandos de acionamento:

Gerenciamento de Andares: Identifica a posição atual e processa chamadas para diferentes níveis.

Controle de Movimento: Aciona motores (passo ou DC) para subir e descer de forma suave.

Sensores de Presença: Utiliza sensores para identificar a chegada em cada andar e garantir a parada exata.

Interface de Usuário: Responde a botões de comando e pode exibir o status em tempo real.

Segurança: Implementa lógica de parada de emergência ou detecção de obstáculos.

🛠️ Tecnologias Utilizadas
C++ / Arduino Language: Linguagem principal para o desenvolvimento da lógica de controle.

Arduino IDE: Ambiente de desenvolvimento para compilação e upload do código.

Hardware:

Placa Arduino (Uno/Mega).

Servo Motores ou Motores de Passo.

Sensores Ultrassônicos ou Infravermelhos para detecção de posição.

Botões e LEDs para interface física.

📁 Estrutura do Repositório
ELEVADOR.ino: Arquivo principal com o código fonte do sistema.

Docs/: (Opcional) Esquemas de montagem e diagramas de circuito.

Media/: (Opcional) Fotos ou vídeos do protótipo em funcionamento.

⚙️ Como executar
Clone este repositório.

Abra o arquivo ELEVADOR.ino na Arduino IDE.

Conecte seu Arduino ao computador.

Certifique-se de ter instalado as bibliotecas necessárias (ex: Servo.h ou Stepper.h).

Clique em Carregar (Upload).
