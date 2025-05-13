// Bibliotecas
#include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>                                   // Biblioteca DHT
#include <DHT_U.h>                                 // Biblioteca DHT
#include <LiquidCrystal_I2C.h>                     // Biblioteca LCD 16x2 IC2
#include <Wire.h>                                  // Biblioteca LCD 16x2 IC2

// Pino analógico - Fio Amarelo
#define sensor_ldr  A3
#define lcdSDA A4
#define lcdSCL A5

// Pinos digitais - Fio Verde
#define DHTPIN 4
#define led_verde 5
#define led_amarelo 6
#define led_vermelho 7
#define buzzer  8

//Leitura do sensor LDR
unsigned int leitura_sensor_ldr = 0; //Variavel para guardar a leitura do sensor
//Faixa de variação do LDR(min -> 8 || max -> 1016)
unsigned int variacao_luz = 0; //Variavel utilizada no map para variacao de luz
//Varivel para mapear Lux
float variacao_lux = 0;

//Temporizador
unsigned int tempo_buzina_alerta = 0; //Variavel para parametrizar o millis() na funcao alerta
unsigned int tempo_buzina_problema = 0;//Variavel para parametrizar o millis() na funcao problema

//SETUP DHT22
#define DHTTYPE DHT22 //definindo tipo de DHT   
DHT_Unified dht(DHTPIN, DHTTYPE); // configurando o Sensor DHT - pino e tipo

//SETUP LCD I2C 16X02
#define col 16 // definindo quantas colunas tem matriz do lcd
#define lin 2 // definindo quantas linhas tem na matriz do lcd
#define ende 0x27
LiquidCrystal_I2C lcd(ende,col,lin);


//Variaveis para conversao de lux
const float GAMMA = 0.7;
const float RL10 = 50;


void setup() {
  //Inicialização do Console
  Serial.begin(9600);
  //OUTPUT dos pinos digitais
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(sensor_ldr,INPUT); //Por padrão a entrada analogica será um INPUT mas está declarada
  pinMode(DHTPIN, INPUT);

  //inicialização do sensor DHT 22
  dht.begin();                                   

  //Inicialização e printe inicial do LCD
  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); //Limpa qualquer informação no Display
  lcd.setCursor(0,0); //Posicionamento coluna,linha
  lcd.print("Vinheria");
  lcd.setCursor(0,1);//Posicionamento coluna,linha
  lcd.print("Agnello");
}

void loop() {
  //Leitura
  leitura_sensor_ldr = analogRead(sensor_ldr);//LEITURA DO SENSOR LDR
  //Conversão para Lux
  float voltage = leitura_sensor_ldr / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  //Mapeamento
  variacao_luz = map(leitura_sensor_ldr,8,1016,0,100); //Mapeamento de valores a partir da leitura direta do analogRead()
  variacao_lux = map(lux,0.1,100000,0,100); // Mapeamento em LUX a partir da leitura do sensor + formula de conversao

  //Feedback do console
  //Valores do LDR e Lux
  Serial.println("Leitura da Luminosidade: ");//Escreve "leitura" no console
  Serial.println("---------------------------------------------------------");
  Serial.print("Valor do analogRead(): ");
  Serial.print(variacao_luz);//Valor da leitura_sensor_ldr em byte na forma de porcentagem
  Serial.println("%");
  Serial.print("Valor da leitura em lux: ");
  Serial.print(variacao_lux);//Valor da leitura_sensor_ldr em LUX em porcentagem
  Serial.println("%");
  delay(5000);
  //Valores Temperatura e umidade
  Serial.println("");
  Serial.println("Leitura de Temperatura e umidade");
  Serial.println("-----------------------------------------------------------------");
  sensors_event_t event;                        // inicializa o evento
  dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
    Serial.print("Temperatura: ");              // imprime a Temperatura
    Serial.print(event.temperature);
    Serial.println(" *C");
  dht.humidity().getEvent(&event);              // faz a leitura de umidade                                        
    Serial.print("Umidade: ");                  // imprime a Umidade
    Serial.print(event.relative_humidity);
    Serial.println("%");
  
  
  // if(variacao_luz >= 0 && variacao_luz <=85){ 
  // 	status_ok();
  // }
  // else if(variacao_luz >85 && variacao_luz <=95){ 
  // 	status_alerta();
  // }
  // else{ 
  // 	status_problema();
  // }

}
// void status_ok(){ //Em caso da luminosidade estar baixa, nivel ideal para o armazenamento do vinho
  
//   digitalWrite(led_verde,HIGH);
//   digitalWrite(buzzer,LOW);
//   digitalWrite(led_amarelo, LOW);
//   digitalWrite(led_vermelho, LOW);
// }
 
// void status_alerta(){ //Em caso da luminosidade estar no nivel de alerta, nivel não ideal para o armazenamento do vinho
  
  
//   digitalWrite(led_amarelo,HIGH);
//   digitalWrite(led_verde, LOW);
//   digitalWrite(led_vermelho, LOW);
  
//   if(millis() - tempo_buzina_alerta >= 500){
//   	digitalWrite(buzzer,HIGH);
//   }
//   if(millis() - tempo_buzina_alerta >=3000){
//   	digitalWrite(buzzer,LOW);
//     tempo_buzina_alerta = millis();
//   }
  
// }

// void status_problema(){ //Em caso da luminosidade estar no nivel de problema, nivel não ideal para o armazenamento do vinho
  
//   digitalWrite(led_vermelho,HIGH);
//   digitalWrite(led_verde, LOW);
//   digitalWrite(led_amarelo, LOW);
  
//   if(millis() - tempo_buzina_problema >= 500){
//   	digitalWrite(buzzer,HIGH);
//   }
//   if(millis() - tempo_buzina_problema >=3000){
//   	digitalWrite(buzzer,LOW);
//     tempo_buzina_problema = millis();
//   }
// }