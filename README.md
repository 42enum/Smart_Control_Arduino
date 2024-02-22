# Smart Control Arduino

Smart Control Arduino contém as sketchs utilizadas para o funcionamento do dispositivo de automação predial.

## Pré-requisitos

- Arduino IDE
- Generic Module Esp8266 Instalado na IDE 
- IRremote

## Instalação

Siga as etapas abaixo para configurar o ambiente de desenvolvimento:

1. **Instalar a IDE arduino**

  Instale a IDE acessando o link abaixo:
```env
https://www.arduino.cc/en/software
```

2. **Instalar o Module Generic Eesp8266 na IDE**

  Acesse **Arquivo -> Preferencias** e cole no campo **URLs adicionais de Gerenciadores de Placas** a url abaixo:
```bash
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
  Após isso, clique em **Ferramentas -> Placa -> Gerenciador de Placas** e busque pela opção **esp8266 by ESP8266 Community** e clique no botão **Instalar**:

  
  ![image](https://github.com/42enum/Smart_Control_Arduino/assets/116222412/4de604b0-0334-425e-a644-e5ff6c00e6d8)

  Depois de feito esse processo, basta ir em **Ferramentas -> Placa: -> Module Generic Esp8266**.
  
## Execução

1. **Arduino e Esp8266**

   Carregue para a placa Arduino a sketch **Arduino_Mark_Modificado** e a **Sketch_Esp** para o Esp8266 (de preferencia com um adaptador USB para facilitar).
   Após isso faça essa configuração de pinos (de preferencia também usando um adaptador de 3.3V para 5V no Esp8266 a fim de prevenir erros de funcionamento):


   ![WhatsApp Image 2024-02-07 at 13 13 24](https://github.com/42enum/Smart_Control_Arduino/assets/116222412/f1df90df-0c19-47d5-ad26-ca2fd12d7ec6)
   ![WhatsApp Image 2024-02-09 at 13 08 51](https://github.com/42enum/Smart_Control_Arduino/assets/116222412/56745ae9-1278-4cbf-ac86-2897d8927d84)


3. **Arduino Mark_Original**

   Para matutenção do equipamento e buscar rows novas, use a **Mark_Original** com um receptor IR.

4. **Sketch Arduino_com_Esp**

   Essa Sketch deve ser upada apenas em Arduinos com memória superior as do arduino uno, pois com o mesmo há instabilidade no funcionamento.

   
   ![gif 3d](https://github.com/42enum/Smart_Control_Arduino/assets/116222412/67bdc6ce-a17e-4e8a-8115-4e55c20c041a)

