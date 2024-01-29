// INCLUSÃO DE BIBLIOTECA
#include <IRremote.h>
#include <SoftwareSerial.h>
//#include <PushButton.h>

// DIRETIVAS DE COMPILAÇÃO
#define tempoTecla 350
#define frequencia 38 // kHz

// DEFINIÇÃO DOS PINOS
#define pinReceptor 11
#define IR_SEND_PIN 3
#define pinLed 12

// INSTANCIANDO OBJETOS
IRrecv receptorIR(pinReceptor);
IRsend emissorIR;
SoftwareSerial espSerial(5, 6);

// DECLARAÇÃO VARIÁVEIS GLOBAIS
bool lerComando = false;

// DECLARAÇÃO DAS FUNÇÕES DE LEITURA
void ircode   (decode_results *results);
void encoding (decode_results *results);
void dumpInfo (decode_results *results);
void dumpRaw  (decode_results *results);
void dumpCode (decode_results *results);

//  DECLARAÇÃO DAS TECLAS CLONADAS
/*Aqui vai ser o código que vc pecisar implementar. Sugiro usar o vídeo de base*/


void setup() {
  
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(IR_SEND_PIN, OUTPUT);

  // INICIANDO RECEPTOR IR
  receptorIR.enableIRIn();
  emissorIR.enableIROut(frequencia);
  Serial.print("Setup Concluído");
}
void stringToIntArray(const String& input, int* output, int tamString) {
    int size = 0;
    int start = 0;

    // Percorre a string até o final
    for (int i = 0; i < tamString; i++) {
        // Se encontrou uma vírgula ou chegou ao final da string
        if (input[i] == ',' || i == tamString - 1) {
            // Obtém o número entre start e i (ou i+1 se for o final da string)
            String num = input.substring(start, i + 1);
            output[size++] = num.toInt();  // Converte para inteiro e adiciona ao vetor
            start = i + 1;  // Atualiza o índice de início para o próximo número
        }
    }
}


int tamVetor(const String& command){
  int tam = 1;
    for (char c : command) {
        if (c == ',') {
            tam++;
        }
    }
  return tam;
}

void loop() {

  // BLOCO PARA RECEBER DADOS DA SERIAL E INICIAR EMISSOR IR
  String command;
  if (espSerial.available()>0) {
    command = espSerial.readString();
    Serial.println(command);
    Serial.println(command.length());
  }
  int tamString = command.length();
  int tamVet = tamVetor(command);
  Serial.println(tamVet);
  unsigned int *raw = new unsigned int[tamVet];
  stringToIntArray(command, raw, tamString);

  delay(500);

  emissorIR.sendRaw(raw, tamVet, frequencia);

  for(int i=0; i<tamVet; i++){
    Serial.print(raw[i]);
  }

  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);

  delete[] raw;
  delay(500);
}
