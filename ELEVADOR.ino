#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Faça o download da biblioteca ou adicione .ZIP
 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço da tela, Digitos, Linhas
 
 
// Define os pinos do Sensor HALL
const int hall4 = 7;  // Andar 3
const int hall3 = 6;  // Andar 2
const int hall2 = 5;  // Andar 1
const int hall1 = 4;  // Terreo
 
/*
 * Botões devem ser ligados ao GND
 */
 
// Define os pinos dos Botões
const int botao4 = 13;  // Andar 3
const int botao3 = 12;  // Andar 2
const int botao2 = 11;  // Andar 1
const int botao1 = 8;   // Terreo
 
// Define os pinos de utilização do Driver ponte H L9110s
const int motorB1 = 10;  // Conectado ao B-1A da ponte H
const int motorB2 = 9;   // Conectado ao B-1B da ponte H
 
int andarAlvo = 1;    // Andar onde devemos parar (1 a 4)
int andarAtual = -1;  // Inicia com um andar inexistente (-1 a 4)
 
String displayLinha1 = "";  // Sistema de cachê do display, evitando
String displayLinha2 = "";  // atualizações desnecessárias e bugs visuais
 
const int tempoAtualizar = 10;  // Milissegundos, variável de delay de checagem dos sensores
 
const int velocidadeMotor = 255;  // Velocidade do motor de 0 a 255
const int sensibilidadeDescida = 5; // Quanto maior, menos sensívl aos sensores
 
void setup() {
 
  // Setup do display LCD
  lcd.init();
  lcd.backlight();
 
  // Define os pinos do Drive como saída de sinal
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
 
  // Define os pinos dos HALL como entrada de sinal
  pinMode(hall1, INPUT_PULLUP);
  pinMode(hall2, INPUT_PULLUP);
  pinMode(hall3, INPUT_PULLUP);
  pinMode(hall4, INPUT_PULLUP);
 
  // Define os pinos dos Botões como entrada de sinal
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(botao4, INPUT_PULLUP);
 
  Serial.begin(115200);
 
  Serial.println("Elevador - Iniciando...");
 
  atualizarDisplay("   Elevador", 1);
  atualizarDisplay("  Iniciando...  ", 2);
 
  delay(3000);
}
 
void loop() {
 
  verificarBotoes();
 
  if (andarAtual == -1) {        // Iniciou o programa
    procurarAndarMaisProximo();  // Se posicionar em um andar corretamente
  }
 
  if (andarAlvo > andarAtual) {  // Queremos ir para um andar acima da gente
    Serial.println("Indo ao próximo andar");
 
    // Mostrar que estamos subindo e o andar que queremos ir
    String tmpDisplay = "  Subindo  > " + nomeAndar(andarAlvo) + "  ";
    atualizarDisplay(tmpDisplay, 2);  // Atualizar apenas a 2° linha
    delay(500);
 
    proximoAndar();                     // Ir para o próximo andar
  } else if (andarAlvo < andarAtual) {  // Queremos ir para um andar abaixo da gente
    Serial.println("Indo ao andar anterior");
 
    // Mostrar que estamos descendo e o andar que queremos ir
    String tmpDisplay = "  Descendo > " + nomeAndar(andarAlvo) + "  ";
    atualizarDisplay(tmpDisplay, 2);  // Atualizar apenas a 2° linha
    delay(500);
 
    andarAnterior();  // Ir para o andar anterior
  } else {
    parado();  // Desligar o motor
    delay(100);
 
    atualizarDisplay("ESCOLHA UM ANDAR", 2);  // Terminamos, solicitar andar ao usuário
    Serial.print("Cheguei ao andar ");
    Serial.println(andarAlvo);
  }
}
 
void procurarAndarMaisProximo() {
  while (andarAtual == -1) {
    Serial.println("Procurando andar mais próximo...");
 
    atualizarDisplay("----------------", 1);  // Atualizar 1° linha
    atualizarDisplay("   AGUARDE...   ", 2);  // Atualizar 2° linha
 
    if (ondeEstou() != -1) {     // Se encontrar um andar
      andarAtual = ondeEstou();  // Salva o andar
      andarAlvo = andarAtual;    // Define o Alvo no mesmo andar
 
      Serial.println("Andar ondeEstou:");
      Serial.println(andarAtual);
 
      atualizarAndar(andarAtual);  // Atualiza a Tela
    }
    delay(tempoAtualizar);
    desce();  // Desce até encontrar um andar...
  }
}
 
void verificarBotoes() {
  int andar = -1;  // Inicia sem botão clicado
 
  if (!digitalRead(botao1)) {  // Caso tenha clicado no botão T
    andar = 1;
  } else if (!digitalRead(botao2)) {
    andar = 2;
  } else if (!digitalRead(botao3)) {
    andar = 3;
  } else if (!digitalRead(botao4)) {
    andar = 4;
  }
 
 
  if (andar >= 1 && andar < 5) {  // Caso um botão tenha sido pressionado
    andarAlvo = andar;
  }
}
 
void atualizarAndar(int andar) {  // Atualização da tela
  switch (andar) {                // Recebe o Andar do sistema
    case 1:
      atualizarDisplay("------ T ------", 1);  // Mostra o Andar correto na tela
      break;
    case 2:
      atualizarDisplay("------ 1 ------", 1);
      break;
    case 3:
      atualizarDisplay("------ 2 ------", 1);
      break;
    case 4:
      atualizarDisplay("------ 3 ------", 1);
      break;
  }
}
 
void proximoAndar() {
  while (andarAtual < andarAlvo) {  // Enquanto não chegar no andarAlvo
 
    /*
     * Caso seja diferente ou chegue ao ultimo andar, pare
     * ajuda evitar que estoure a linha caso algum sensor antes falhe.
     */
 
    if (ondeEstou() == 4) {
      andarAtual = 4;
      atualizarAndar(andarAtual);  // Atualização forçada do sistema
      break;
    }
 
 
    sobe();
    delay(tempoAtualizar);
 
 
    // Verifica qual andar passamos
    int novoAndar = ondeEstou();
    if (novoAndar != -1) {
      andarAtual = novoAndar;
      atualizarAndar(novoAndar);
    }
  }
 
  parado();  // Desliga os motores depois de encontrar o Andar
  delay(500);
}
 
void andarAnterior() {  // Lógica semelhante à função acima
  while (andarAtual > andarAlvo) {
 
 
    // Verifica qual andar passamos
    int novoAndar = ondeEstou();
    if (novoAndar != -1) {
      andarAtual = novoAndar;
      atualizarAndar(novoAndar);
    }
    desce();
 
    delay(tempoAtualizar * sensibilidadeDescida);
  }
 
  parado();
  delay(500);
}
 
int ondeEstou() {  // Reliza a leitura dos sensores Hall
 
  if (!digitalRead(hall1)) {
    return 1;
  } else if (!digitalRead(hall2)) {
    return 2;
  } else if (!digitalRead(hall3)) {
    return 3;
  } else if (!digitalRead(hall4)) {
    return 4;
  }
 
  return -1;  // Estamos em movimento ou posição indefinida
}
 
 
String nomeAndar(int andar) {  // Transforma o número dos sensores em nome do andar
  switch (andar) {
    case 1: return "T";
    case 2: return "1";
    case 3: return "2";
    case 4: return "3";
    default: return "?";  // Retorno padrão para valores inválidos
  }
}
 
// Inicia o motor com o comando descer
void desce() {
  analogWrite(motorB1, velocidadeMotor);
  analogWrite(motorB2, 0);
}
 
// Inicia o motor com o comando subir
void sobe() {
  analogWrite(motorB2, velocidadeMotor);
  analogWrite(motorB1, 0);
}
 
// Para o motor
void parado() {
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 0);
}
 
// Função para gerenciamento do display
void atualizarDisplay(String texto, int linha) {
 
  // 1° Linha && apenas se mudar o texto da tela seguimos, assim evitamos bugs visuais e atualização desnecessária
  if (linha == 1 && texto != displayLinha1) {
    lcd.setCursor(0, 0);            // Move ao início
    lcd.print("                ");  // limpa linha
    lcd.setCursor(0, 0);            // Move ao início
    lcd.print(texto);               // Mostra o novo texto
 
    displayLinha1 = texto;  // Salva o texto em cachê
 
  } else if (linha == 2 && texto != displayLinha2) {  // 2° Linha, lógica semelhante
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(texto);
 
    displayLinha2 = texto;
  }
}
