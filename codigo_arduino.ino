// CONFIGURACOES INICIAIS
// TB6600
#define PINO_PULSO 46
#define PINO_DIRECAO 48
#define PINO_ENABLE 50

// FIM DE CURSOS
#define PINO_FIM_CURSO_TOPO 10
#define PINO_FIM_CURSO_BASE 11

// SENSOR DE LUMINOSIDADE
#define PINO_SENSOR_LUMINOSIDADE_01 A0
#define PINO_SENSOR_LUMINOSIDADE_02 A1

// MOTOR
#define NUMERO_PASSOS_POR_REVOLUCAO 200

// CONSTANTES
#define ATIVADO = HIGH;
#define DESATIVADO = LOW;

#define FIM_CURSO_ATIVADO = LOW;
#define FIM_CURSO_DESATIVADO = HIGH;

#define HORARIO = LOW;
#define ANTI_HORARIO = HIGH;

#define TAXA_DIFERENCA_LUMINOSIDADE 100

// CABECALHOS FUNCOES
void acionarMotorSubir();
void acionarMotorDescer();
int abs(int valor);

// PRINCIPAL
void setup() {
    // TB6600
    pinMode(PINO_PULSO, OUTPUT);
    pinMode(PINO_DIRECAO, OUTPUT);
    pinMode(PINO_ENABLE, OUTPUT);

    digitalWrite(PINO_ENABLE, LOW);

    // FIM DE CURSOS
    pinMode(PINO_FIM_CURSO_TOPO, INPUT_PULLUP);
    pinMode(PINO_FIM_CURSO_BASE, INPUT_PULLUP);

    // DEBUG
    Serial.begin(9600);
}

void loop() {
    //ler os valores dos sensores de luminosidade
    int valor_sensor_luminosidade_1 = analogRead(PINO_SENSOR_LUMINOSIDADE_01);
    int valor_sensor_luminosidade_2 = analogRead(PINO_SENSOR_LUMINOSIDADE_02);

    // calcula a diferenca
    int diferenca_luminosidade = valor_sensor_luminosidade_1 - valor_sensor_luminosidade_2;

    // aciona o motor
    if (diferenca_luminosidade < 0) {
        if (abs(diferenca_luminosidade) >= TAXA_DIFERENCA_LUMINOSIDADE)
            acionarMotorDescer();
    } else {
        if (abs(diferenca_luminosidade) >= TAXA_DIFERENCA_LUMINOSIDADE)
            acionarMotorSubir();
    }

    // DEBUG
    Serial.print("Sensor luminosidade 1: ");
    Serial.println(valor_sensor_luminosidade_1);
    Serial.print("Sensor luminosidade 2: ");
    Serial.println(valor_sensor_luminosidade_2);
    Serial.print("Diferenca de luminosidade: ");
    Serial.println(diferenca_luminosidade);
}

// IMPLEMENTACAO DAS FUNCOES
int abs(int valor) {
    return (valor < 0) ? -valor : valor;
}

void acionarMotorSubir() {
    // DEFINE A DIRECAO QUE O MOTOR IRA GIRAR
    digitalWrite(PINO_DIRECAO, HORARIO);

    // REALIZA O GIRO DE 1.8 GRAUS
    for (int i = 0; i < NUMERO_PASSOS_POR_REVOLUCAO; i++) {
        // VERIFICA SE O FIM DE CURSO ESTA ATIVADO
        if (digitalRead(PINO_FIM_CURSO_TOPO) == ATIVADO)
            return;

        // REALIZA O GIRO
        digitalWrite(PINO_PULSO, ATIVADO);
        delayMicroseconds(500);
        digitalWrite(PINO_PULSO, DESATIVADO);
        delayMicroseconds(500);

        //AGUARDA UM MOMENTO PARA VERIFICAR O ESTADO DO FIM DE CURSO
        delay(500);
    }
}

void acionarMotorDescer() {
    // DEFINE A DIRECAO QUE O MOTOR IRA GIRAR
    digitalWrite(PINO_DIRECAO, ANTI_HORARIO);

    // REALIZA O GIRO DE 1.8 GRAUS
    for (int i = 0; i < NUMERO_PASSOS_POR_REVOLUCAO; i++) {
        // VERIFICA SE O FIM DE CURSO ESTA ATIVADO
        if (digitalRead(PINO_FIM_CURSO_BASE) == ATIVADO)
            return;

        // REALIZA O GIRO
        digitalWrite(PINO_PULSO, ATIVADO);
        delayMicroseconds(500);
        digitalWrite(PINO_PULSO, DESATIVADO);
        delayMicroseconds(500);

        //AGUARDA UM MOMENTO PARA VERIFICAR O ESTADO DO FIM DE CURSO
        delay(500);
    }
}