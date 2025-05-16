<h1 align="center"> Vinheria Agnello 🍷 -- Monitoramento de Temperatura e Luminosidade💡</h1>
A Vinheria Agnello é uma empresa familiar, dirigida pelo proprietário Giulio e sua filha Bianca, que atua há mais de 15 anos com apenas uma loja física, que emprega mais 6 funcionários, entre a administração, estoques e vendas.  


## 🔴 Problema
Uma das particularidades relevantes dos vinhos é o risco de sua degradação, ou ao menos alteração de suas características de coloração, aromas e sabor, caso sejam mal armazenados, ***expostos por muito tempo à luz natural, temperaturas altas, ou mesmo quando expostos a vibrações ou movimentações constantes***.  Conhecedora desses riscos, a Vinheria Agnello adota cuidados especiais na armazenagem de seus vinhos, em especial com os vinhos de maior valor e vinhos raros, buscando assim garantir a seus clientes mais exigentes a qualidade original de cada garrafa, como recebida de seus fornecedores ou mesmo das vinícolas de origem.

## 💡 Solução
Na primeira etapa da solução, foi desenvolvido um sistema que capta a luminosidade do ambiente para criar condições adequadas de armazenamento. Para que essa informação seja comunicada aos responsáveis pelo estoque, será utilizado um indicador de LED que mostrará a condição de luminosidade em que o produto se encontra. Além dos LEDs, que auxiliam no diagnóstico, também será utilizada uma buzina para alertar caso a luminosidade do ambiente esteja completamente fora das condições ideais.

Na segunda etapa da solução, será desenvolvido um sistema capaz de captar a temperatura e a umidade do ambiente. Com isso, somado à primeira etapa, será possível criar um sistema de feedback mais completo e informativo. Além da adição dos parâmetros de temperatura e umidade, utilizaremos uma tela de LCD para exibir visualmente as leituras de temperatura, umidade e luminosidade.

## 🛠️ Detalhes Técnicos
Para captar e processar dados sobre a luminosidade, utilizaremos um componente chamado LDR (Light Dependent Resistor), cujo princípio de funcionamento baseia-se na variação da condutividade elétrica conforme a presença ou ausência de luz. Esse componente, em conjunto com resistores, pode ser usado para criar condições específicas de leitura. O funcionamento técnico do LDR pode ser descrito da seguinte forma: quanto maior a luminosidade, maior a resistência e menor a tensão; por outro lado, quanto menor a luminosidade, menor a resistência e maior a tensão.

Para captar e tratar dados de temperatura e umidade, utilizaremos um componente chamado DHT22, capaz de medir temperaturas entre -80 °C e 80 °C, além da umidade em uma escala de 0 a 100%. Seu princípio de funcionamento baseia-se na utilização de uma entrada digital que retorna valores binários (0 e 1); a partir desses dados, realiza-se uma conversão para um número hexadecimal (HEX) e, em seguida, para decimal (DEC). Exemplo: Umidade: 0011 0101 = 35H = 53%RH; Temperatura: 0001 1000 = 18H = 24 °C.

O display LCD 16x2 (com interface I2C) será mais uma ferramenta utilizada para exibir visualmente as informações obtidas pelas leituras dos sensores.

Para parametrizar a quantidade ideal da luz utilizaremos uma escala chamada LUX, segue tabela e código de conversão(quando o VCC for 5v):
<table><thead><tr><th>Condition</th><th>Illumination (lux)</th><th>LDR Resistance</th><th>Voltage*</th><th>analogRead() value</th></tr></thead><tbody><tr><td>Full moon</td><td>0.1</td><td>1.25MΩ</td><td>4.96</td><td>1016</td></tr><tr><td>Deep twilight</td><td>1</td><td>250kΩ</td><td>4.81</td><td>985</td></tr><tr><td>Twilight</td><td>10</td><td>50kΩ</td><td>4.17</td><td>853</td></tr><tr><td>Computer monitor**</td><td>50</td><td>16.2kΩ</td><td>3.09</td><td>633</td></tr><tr><td>Stairway lighting</td><td>100</td><td>9.98kΩ</td><td>2.50</td><td>511</td></tr><tr><td>Office lighting</td><td>400</td><td>3.78kΩ</td><td>1.37</td><td>281</td></tr><tr><td>Overcast day</td><td>1,000</td><td>1.99kΩ</td><td>0.83</td><td>170</td></tr><tr><td>Full daylight</td><td>10,000</td><td>397Ω</td><td>0.19</td><td>39</td></tr><tr><td>Direct sunlight</td><td>100,000</td><td>79Ω</td><td>0.04</td><td>8</td></tr></tbody></table>

```c
const float GAMMA = 0.7;
const float RL10 = 50;

// Converte o AnalogRead(ldr) no valor em lux:
int analogValue = analogRead(A0);
float voltage = analogValue / 1024. * 5;
float resistance = 2000 * voltage / (1 - voltage / 5);
float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
```



## 🖲️ Requisitos Funcionais
1. Enquanto o ambiente estiver escuro, o LED Verde deve ficar aceso;
2. Enquanto o ambiente estiver a meia luz, o LED amarelo deve ficar aceso e mensagem de 
“Ambiente a meia luz” deve ser mostrado no Display;
3. Enquanto o ambiente estiver totalmente iluminado, o LED vermelho deve ficar aceso e a 
mensagem “Ambiente muito claro” deve ser mostrado no display;
4. Enquanto o ambiente estiver totalmente iluminado, o Buzzer deve ficar ligado 
continuamente;
5. Enquanto o ambiente estiver com uma temperatura entre 10°C e 15°C, o Display deve 
informar “Temperatura OK” e também mostrar o valor da temperatura;
6. Enquanto o ambiente estiver com uma umidade entre 50% e 70%, o Display deve 
informar “Umidade OK”, e também mostrar o valor da umidade;
7. Os valores apresentados no display devem ser a média de pelo menos 5 leituras dos 
sensores, e os valores devem ser apresentados a cada 5 segundos;
8. Enquanto a temperatura estiver fora da faixa ideal, o LED Amarelo deve ficar aceso e o 
Buzzer deve ligar continuamente;
9. Enquanto a temperatura estiver fora da faixa ideal, o Display deve informar “Temp. Alta”, 
para valores acima de 15°C e também mostrar a temperatura;
10. Enquanto a temperatura estiver fora da faixa ideal, o Display deve informar “Temp. 
Baixa”, para valores abaixo de 10°C e também mostrar a temperatura;
11. Enquanto a umidade estiver fora da faixa ideal, o LED Vermelho deve ficar aceso e o 
Buzzer deve ligar continuamente;
12. Enquanto a umidade estiver fora da faixa ideal, o Display deve informar “Umidade. Alta”, 
para valores acima de 70% e também mostrar a umidade;
13. Enquanto a umidade estiver fora da faixa ideal, o Display deve informar “Umidade. Baixa”, 
para valores abaixo de 50% e também mostrar a umidade;



## 🧭 Material
- 01 Arduino UNO = Para controlar o sistema
- 01 Breadboard = para montagem do circuito
- Cabos Jumper = Para realizar as conexões na breadboard
- 04 Resistores = 3 para os LED e 01 para o DHT22
- 01 LED Verde 🟢 = Para indicar que está tudo OK
- 01 LED Amarelo 🟡 = Para indicar ALERTA
- 01 LED Vermelho 🔴 = Para indicar PROBLEMA
- 01 Buzzer 🔈 = Ativado para chamar atenção
- 01 LDR = Sensor para medir a luminosidade do ambiente(Parametros entre 8-1016)
- 01 DHT22 = Medidor de temperatura(-80 C -- 80 C) e umidade(0% - 100%)
- 01 LCD 16X2 I2C = Tela que irá informar as leituras dos componentes.

## 🔗Como acessar o projeto
Para acessar o diagrama do projeto [clique aqui](https://wokwi.com/projects/430970555017844737)

Link para o video sobre o projeto: falta video

## 🧰 Tecnologias utilizadas
- Software de Repósitorio Remoto: GitHub
- Software Simulador de Circuito: Wokwi
- Linguagem de Programação: C
- Bibliotecas:
  - DHT sensor library
  - Adafruit Unified Sensor
  - LiquidCrystal I2C

## 🧑‍💻 Equipe
<table>
  <tr><th><span>Integrantes</span></th><th><span>Tarefas</span></th></tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/202196268?v=4" width="100px" alt= "Camila Martins Profile Image"/><p><a href = "https://github.com/dev-camila">Camila Martins</a></p><span><b>RM:561492</b></span>
    </td>
    <td>
      <ul>
        <li>Requisitos funcionais para Luminosidade, Display e Led</li>
      </ul>
    </td>
  </tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/80047823?v=4" width="100px" alt= "Gabriel Amara Profile Image"/><p><a href = "https://github.com/gabrielamara98">Gabriel Amara</a></p><span><b>RM:561403</b></span>
    </td>
    <td>
      <ul>
        <li>Gestão do README e repositório</li>
        <li>Importar Projeto para o Wokwi</li>
        <li>Criar e montar o setup do projeto</li>
        <li>Revisão de código</li>
      </ul>
    </td>
  </tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/105310868?v=4" width="100px" alt= "Guilherme Godoy Profile Image"/><p><a href = "https://github.com/godooooy">Guilherme Godoy </a></p><span><b>RM:564417</b></span>
    </td>
    <td>
      <ul>
        <li>Requisitos Funcionais Temperatura e Display</li>
        <li>Requisitos Funcionais Umidade e Display </li>
      </ul>
    </td>
  </tr>
    <tr>
    <td align = "center">
      <img src="https://avatars.githubusercontent.com/u/101485201?v=4" width="100px" alt= "Pedro Lucas Profile Image"/><p><a href = "https://github.com/pedroviscz">Pedro Lucas Almeida</a></p><span><b>RM:566256</b></span>
    </td>
    <td>
      <ul>
        <li>Requisitos funcionais para o Display</li>
      </ul>
    </td>
  </tr>
</table>

## 📓 Notas:
Projeto: Case-Vinheria Agnello

Repositório que servirá como 2º Checkpoint da disciplina de Edge Computing da FIAP

Professor avaliador: Lucas Demetrius Augusto

