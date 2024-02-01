// INCLUSÃO DE BIBLIOTECA
#include <IRremote.h>
//#include <PushButton.h>

// DIRETIVAS DE COMPILAÇÃO
#define tempoTecla 350
#define frequencia 38  // kHz

// DEFINIÇÃO DOS PINOS
#define pinReceptor 11
#define pinLed 12

// INSTANCIANDO OBJETOS
IRrecv receptorIR(pinReceptor);
IRsend emissorIR;

// DECLARAÇÃO VARIÁVEIS GLOBAIS
bool lerComando = false;

// DECLARAÇÃO DAS FUNÇÕES DE LEITURA
void ircode(decode_results *results);
void encoding(decode_results *results);
void dumpInfo(decode_results *results);
void dumpRaw(decode_results *results);
void dumpCode(decode_results *results);

//  DECLARAÇÃO DAS TECLAS CLONADAS
/*Aqui vai ser o código que vc pecisar implementar. Sugiro usar o vídeo de base*/
unsigned int frerp1_on[] = { 3100, 1650, 400, 1150, 400, 1150, 400, 400, 400, 450, 400, 450, 400, 1150, 400, 400, 450, 400, 400, 1200, 400, 1150, 400, 400, 400, 1150, 400, 450, 400, 400, 400, 1200, 400, 1150, 400, 400, 400, 1150, 400, 1150, 400, 400, 450, 400, 400, 1200, 400, 400, 400, 450, 400, 1150, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 450, 400, 400, 1150, 400, 400, 450, 400, 450, 1150, 400, 400, 400, 450, 400, 1150, 400, 1150, 400, 400, 400, 450, 450, 400, 450, 400, 400, 450, 400, 400, 450, 1150, 400, 400, 450, 1150, 400, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 450, 400, 400, 450, 400, 450, 1150, 400, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 1150, 400, 400, 450, 400, 450, 400, 400, 450, 400, 400, 450, 400, 450, 1150, 400 };
unsigned int frerp1_off[] = { 3150, 1600, 450, 1050, 450, 1100, 450, 400, 450, 400, 450, 400, 450, 1100, 400, 400, 500, 350, 450, 1100, 500, 1050, 450, 400, 450, 1100, 450, 350, 500, 350, 450, 1100, 450, 1100, 450, 400, 450, 1100, 450, 1100, 450, 350, 500, 350, 500, 1100, 400, 400, 450, 400, 450, 1100, 400, 400, 500, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 500, 350, 450, 400, 500, 350, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 1100, 450, 400, 450, 400, 450, 1100, 450, 1100, 400, 400, 450, 400, 450, 400, 500, 350, 450, 400, 450, 350, 450, 1100, 450, 400, 450, 1150, 400, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 500, 1050, 450, 400, 450, 400, 450, 350, 450, 400, 500, 350, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 400, 400, 400, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 400, 450, 400, 450, 400, 450, 400, 450, 350, 450, 400, 450, 1150, 400, 400, 400, 1150, 400, 1150, 400, 1150, 400, 1150, 400, 1150, 350, 450, 400 };

void setup() {

  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);

  // INICIANDO RECEPTOR IR
  receptorIR.enableIRIn();
  Serial.print("Setup Concluído");
}

void loop() {
  // LAÇO PARA LEITURA DO RECEPTOR IR QUANDO FOR PRESSIONADO O BOTÃO
  while (lerComando) {

    decode_results results;

    if (receptorIR.decode(&results)) {
      ircode(&results);
      encoding(&results);
      dumpInfo(&results);
      dumpRaw(&results);
      dumpCode(&results);
      receptorIR.resume();
      lerComando = false;
      digitalWrite(pinLed, LOW);
    }
  }

  // BLOCO PARA RECEBER DADOS DA SERIAL E INICIAR EMISSOR IR
  if (Serial.available()) {

    String command = Serial.readString();

    if (command == "a") {
      emissorIR.sendRaw(frerp1_on, sizeof(frerp1_on) / sizeof(frerp1_on[0]), frequencia);
      Serial.println("Enviando Tecla A clonada");
      delay(tempoTecla);
    } else if (command == "b") {
      emissorIR.sendRaw(frerp1_off, sizeof(frerp1_off) / sizeof(frerp1_off[0]), frequencia);
      Serial.println("Enviando Tecla B clonada");
      delay(tempoTecla);
    } else {
      if (!lerComando) {
        lerComando = true;
        digitalWrite(pinLed, HIGH);
      } else if (lerComando) {
        lerComando = false;
        digitalWrite(pinLed, LOW);
      }
    }
  }
}
