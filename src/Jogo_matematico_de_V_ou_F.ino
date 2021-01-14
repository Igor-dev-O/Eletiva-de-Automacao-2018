/*
  Jogo de matemática básica cujo o objetivo é o jogador responder 
as equações que aparecer no display pressionando o botão de verdadeiro ou falso,
acumulando o maior número de acertos.
  Esse projeto aplica as seguintes funções: Uso de display,
botoes, lógicas bolanas, reposta visual ao pressionar o botão
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define V 4 // Verdadeiro
#define F 2 // Falso

int tecla_lida = 0;
int acertos = 0;
int erros = 0;
int tipo_de_conta;
int fator_1;
int fator_2;
int resultado;
int valor_lido;
int tipo_de_resposta;

void setup()
{

  // configura os pinos como entradas
  pinMode(V, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);

  lcd.begin(16, 2); // inicializa o display

  pinMode(5, OUTPUT);
  analogWrite(5, 96);
  lcd.home(); // vai pra primeira linha

  lcd.write("JOGO DE PERGUN-");
  lcd.setCursor(0, 1);
  lcd.write("TAS E RESPOSTAS");
  delay(5000);
  lcd.clear();

  lcd.print("APERTE VERDA-");
  lcd.setCursor(0, 1);
  lcd.print("DEIRO ou FALSO");
  delay(5000);

  lcd.clear();
  lcd.print("APERTE QUALQUER");
  lcd.setCursor(0, 1);
  lcd.print("BOTAO PARA");

  delay(5000);
  lcd.clear();
  lcd.print("INICIAR O JOGO!");

  randomSeed(analogRead(0));

  le_botao();
  lcd.clear();

} // fim do setup

void loop()
{

  tipo_de_conta = random(1, 3); //maior ou igual a um e menor que 3

  switch (tipo_de_conta)
  {
  case 1: // multiplicação
    fator_1 = random(1, 10);
    fator_2 = random(1, 10);
    resultado = fator_1 * fator_2;

    lcd.setCursor(0, 0);
    lcd.print(fator_1);
    lcd.print(" x ");
    lcd.print(fator_2);
    lcd.print(" = ");

    break; //fim da multiplicação

  case 2: // divisão
    resultado = random(1, 10);
    fator_2 = random(1, 10);
    fator_1 = resultado * fator_2;

    lcd.setCursor(0, 0);
    lcd.print(fator_1);
    lcd.print(" / ");
    lcd.print(fator_2);
    lcd.print(" = ");

    break; // fim da divisão

  default:
    lcd.setCursor(3, 0);
    lcd.print("ERRO: caso não previsto!");
    delay(1500);
    lcd.clear();
    break; // fim do default
  }

  delay(1500);

  //--------------- Tipo de resposta --------------//

  tipo_de_resposta = random(1, 3); // 1 significa exibir resposta certa e 2 exibe a resposta errada

  // 1) exibir resposta correta ou errada, de acordo com o sorteio
  // 2) perguntar V/F

  switch (tipo_de_resposta)
  {
  case 1: // O arduino exibe a resposta certa

    // completa a linha da pergunta
    lcd.setCursor(8, 0);
    lcd.print(resultado);
    lcd.setCursor(0, 1);
    lcd.print("V ou F ?"); // o jogador pode responder V ou F
    break;

  case 2: // o arduino exibe a resposta errada
    int resultado_qualquer;
    do
    {
      resultado_qualquer = random(1, 100);     // sorteia qualquer numero
    } while (resultado_qualquer == resultado); // precisamos garantir que esse numero seja diferente da resposta correta

    lcd.setCursor(8, 0);
    lcd.print(resultado_qualquer); // completa a linha da pergunta
    lcd.setCursor(0, 1);
    lcd.print("V ou F ?"); // o jogador pode responder V ou F
    break;
  }

  //------------------ Declaração da variável boolean e leitura do que foi digitado --------------//

  boolean digitado = le_botao();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voce digitou: ");
  lcd.setCursor(0, 1);

  if (digitado == true)
  {
    lcd.print("V"); // botão V é considerado verdadeiro
  }
  else
  {
    lcd.print("F");
  }
  delay(1500);
  lcd.clear();

  //--------------------------- Comparar a resposta com o esperado ------------------//

  switch (tipo_de_resposta)
  {
  case 1: // O arduino sabe que exibiu a resposta certa
    if (digitado == true)
    {
      lcd.setCursor(0, 0);
      lcd.print("Muito bem :-)");
      delay(1500);
      acertos = acertos + 1;
    }
    else
    { // a pessoa F digitou (v)erdadeiro
      lcd.setCursor(0, 0);
      lcd.print("O resultado era");
      lcd.setCursor(0, 1);
      lcd.print("verdadeiro :-( ");
      delay(1500);
      erros = erros + 1;
    }
    break;

  case 2: // o arduino exibiu a resposta errada
    if (digitado == true)
    {
      lcd.setCursor(0, 0);
      lcd.print("Errou :-(");
      delay(1500);
      lcd.clear();
      // informação sobre o resultado
      lcd.setCursor(0, 0);
      lcd.print("O valor correto era: ");
      lcd.setCursor(0, 1);
      lcd.print(resultado);
      delay(1500);
      erros = erros + 1;
    }
    else
    { // a pessoa F digitou (v)erdadeiro
      lcd.print("Muito bem :-)");
      delay(1500);
      acertos = acertos + 1;
    }
    break;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acertos: ");
  lcd.print(acertos);
  lcd.setCursor(0, 1);
  lcd.print("Erros: ");
  lcd.print(erros);
  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vamos tentar");
  lcd.setCursor(0, 1);
  lcd.print("outra pergunta");
  delay(1500);
  lcd.clear();

} // fim do "loop"

// ----------------------- Função booleana le_botao para descobrir qual botão é o verdadeiro, qual o falso ---------------------------//

boolean le_botao()
{
  int tecla_V, tecla_F;

  do
  {
    tecla_V = digitalRead(V);
    tecla_F = digitalRead(F);
  } while (tecla_V == HIGH && tecla_F == HIGH);

  return (tecla_V == LOW); // testar a botão V como true
}