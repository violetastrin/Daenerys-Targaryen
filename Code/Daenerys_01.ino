// Ponte H
#define ENA 8
#define dirfrente 7 // IN1
#define dirre 6     // IN2

#define esqre 5     // IN3
#define esqfrente 4 // IN4
#define ENB 9

#define sensoresq 48
#define sensormeio 50
#define sensordir 52

int velocidade = 255;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Trabalhando"); 

  pinMode(ENA, OUTPUT);
  pinMode(esqfrente, OUTPUT);
  pinMode(esqre, OUTPUT);

  pinMode(dirre, OUTPUT);
  pinMode(dirfrente, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(sensoresq, INPUT);
  pinMode(sensormeio, INPUT);
  pinMode(sensordir, INPUT);
}

void loop() {
  int esq = digitalRead(sensoresq);
  int meio = digitalRead(sensormeio);
  int dir = digitalRead(sensordir);

  // Monitoramento
  Serial.print(esq);
  Serial.print(" ");
  Serial.print(meio);
  Serial.print(" ");
  Serial.println(dir);

  // Lógica de Movimentação Baseada nos Sensores (Esq - Meio - Dir)
  
  // 100 (só esq) OU 110 (esq + meio) -> Avança um pouco e vira Esquerda
  if ((esq == 1 && meio == 0 && dir == 0) || (esq == 1 && meio == 1 && dir == 0)) {
    frente();
    delay(250);
    
    // Continua virando enquanto o sensor do meio NÃO encontrar a linha (meio == 0)
    while (digitalRead(sensormeio) == 0) {
      esquerda();
    }
  } 
  // 001 (só dir) OU 011 (meio + dir) -> Avança um pouco e vira Direita
  else if ((esq == 0 && meio == 0 && dir == 1) || (esq == 0 && meio == 1 && dir == 1)) {
    frente();
    delay(250);
    
    // Continua virando enquanto o sensor do meio NÃO encontrar a linha (meio == 0)
    while (digitalRead(sensormeio) == 0) {
      direita();
    }
  } 
  // Qualquer outra combinação (ex: 010, 111, 000) -> Frente
  else {
    frente();
  }
}

// ===============================
// MOVIMENTOS
// ===============================

void frente() {
  digitalWrite(esqfrente, HIGH);
  digitalWrite(esqre, LOW);

  digitalWrite(dirfrente, HIGH);
  digitalWrite(dirre, LOW);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void re() {
  digitalWrite(esqfrente, LOW);
  digitalWrite(esqre, HIGH);

  digitalWrite(dirfrente, LOW);
  digitalWrite(dirre, HIGH);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void esquerda() {
  digitalWrite(esqfrente, LOW);
  digitalWrite(esqre, HIGH);

  digitalWrite(dirfrente, HIGH);
  digitalWrite(dirre, LOW);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void direita() {
  digitalWrite(esqfrente, HIGH);
  digitalWrite(esqre, LOW);
  
  digitalWrite(dirfrente, LOW);
  digitalWrite(dirre, HIGH);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void parar() {
  digitalWrite(esqfrente, LOW);
  digitalWrite(esqre, LOW);

  digitalWrite(dirfrente, LOW);
  digitalWrite(dirre, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
