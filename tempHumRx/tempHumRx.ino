/*******************************************************************************************************************************************************************

                                                                RECEPTOR - RX
  
  Material: Arduino Uno / Módulo LCD /  Transceiver NRF24L01 / Jampers / Bateria 9Vcc / Cabo alimentação.

  Efeito: Transceive recebe o valor de temperatura e humidade do sensor DHT11, enviado por um transmissor NRF24L01 distante.
          A monitoração é feita através do monitor serial.
 
  Aluno: Jailson Correia dos Santos

  Data: 17/02/21  
  

*******************************************************************************************************************************************************************/

/********************************************************** IMPORTAÇÃO DE BIBLIOTECAS *****************************************************************************/

#include <RF24.h>                            // Biblioteca do radio 

#include <SPI.h>                             // Biblioteca do protocolo SPI (Serial Peripheral Interface)

#include <LiquidCrystal.h>                   // Biblioteca LCD


/******************************************************************************MAPEAMENTO DE HARDWARE*************************************************************/

LiquidCrystal lcd (7,6,5,4,3,2);             // Criado o objeto lcd. Pinos: 7(RS),6(E),5(D4),4(D5),3(D6),2(D7);


RF24 radio (8, 9);                           // Aqui o objeto radio recebe dos argumentos (CE, CSN)
const byte endereco [6] = "00001";           // Endereço que os módulos RF irão utilizar para comunicação.

char texto [6] = "";
String umidade = "";
String temperatura = "";


/*************************************************************************** CÓDIGO ******************************************************************************/


void setup() {

  Serial.begin (9600);                              // Inicialização do monitor serial - Para confirmação da leitura dos dados.
  radio.begin();                                    // Inicialização do objeto radio.
  lcd.begin(16,2);                                  // Inicia o objeto lcd. Recebe acomo parâmetros o numero de colunas(16) e o numero de linhas (2).
  
  radio.openReadingPipe (0, endereco);              // Abertura do canal de comunicação entre os radios com a introdução do endereço.
  radio.setPALevel (RF24_PA_MIN);                   // Set do nível do sinal que será utilizado entre os equipamentos
  radio.startListening ();                          // Diretriz que informa que esse rádio irá apenas receber informação.

}

void loop() {

  radio.read (&texto, sizeof(texto));
  temperatura = String(texto[0]) + String(texto[1])+"C";             // VAriável que recebe os dois primeiros caracteres enviados pelo receptor
  umidade = String(texto[2]) + String(texto[3]) + "%";               // VAriável que recebe os dois ultimos caracteres enviados pelo receptor

  Serial.println(temperatura);                                       // DEBUG - Verifica se os dados estão sendo recebidos no monitor serial.
  
  lcd.clear();                                                       // Imprime resultado no módulo LCD.
  lcd.print("Temp:");
  lcd.print(temperatura);
  lcd.setCursor(0,1);
  lcd.print("Umid Ar:");
  lcd.print(umidade);
  delay(5000);

}
