/*******************************************************************************************************************************************************************

                                                                TRANSMISSOR - TX
  
  Material: Arduino Uno / Sensor DHT11 / Transceiver NRF24L01 / Jampers / Bateria 9Vcc / Cabo alimentação.

  Efeito: Transceive enviar o valor de temperatura e humidade do sensor DHT para um receptor NRF24L01 distante.
 
  Aluno: Jailson Correia dos Santos

  Data: 17/02/21  
  

*******************************************************************************************************************************************************************/

/********************************************************** IMPORTAÇÃO DE BIBLIOTECAS *****************************************************************************/

#include <DHT.h>                             // Biblioteca do sensor de Temperatura e Umidade

#include <RF24.h>                            // Biblioteca do transceptor de RF

#include <SPI.h>                             // Biblioteca do protocolo SPI (Serial Peripheral Interface)- Utilizado pelo Radio.


/******************************************************************************MAPEAMENTO DE HARDWARE*************************************************************/

#define dhtPino 2                            // Localização do pino de dados do Sensor.
#define dhtTipo DHT11                        // Declaração do tipo do sensor de temperaura e umidade.

DHT dhtSensor (dhtPino, dhtTipo);            // Declarção do objeto dhtSensor.Recebe dois parâmetros

RF24 radio (7,8);                            // Aqui o objeto radio recebe dos argumentos (CE, CSN)
const byte endereco [6] = "00001";           // Endereço que os módulos RF irão utilizar para comunicação.

char thChar [6] = "";                        // Varável que servira de Buffer para a função toCharArray.
String thString = "";                        // Variável que iriá armazenar os valores (temp e umidade) convertidos para string


/*************************************************************************** CÓDIGO ******************************************************************************/


void setup() {

  Serial.begin (9600);                           // Inicialização do monitor serial - Para confirmação da leitura dos dados.
  dhtSensor.begin ();                            // Inicialização do objeto dhtSensor.
  radio.begin();                                 // Inicialização do objeto radio.

  
  radio.openWritingPipe (endereco);              // Abertura do canal de comunicação entre os radios com a introdução do endereço.
  radio.setPALevel (RF24_PA_MIN);                // Set do nível do sinal que será utilizado entre os equipamentos
  radio.stopListening ();                        // Diretriz que informa que esse rádio irá apenas transmitir.

}

void loop() {

  int umidade = dhtSensor.readHumidity ();
  int temperatura = dhtSensor.readTemperature ();
 
  thString = String(temperatura)+ String(umidade);
  thString.toCharArray (thChar, 6); // 12 valor inicial    // toCharArray - Copia os caracteres da String para um buffer fornecido (buffer, tamanhoBuffer);

  Serial.println (thString);                               // Monitora através do monitor serial, se o sensor estar enviando os dados.
  radio.write (&thChar, sizeof(thChar));                   // A mensagem que será transmitida, pela função,recebe dois argumentos(a mensagem, número de bytes da mensagem)


  delay(5000);
  
}
