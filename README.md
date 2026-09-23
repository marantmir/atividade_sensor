# Atividade Avaliativa Prática 2/6 — Leitura de Sensor

Projeto desenvolvido com **ESP32-S3 + MPU6050**, utilizando **ESP-IDF em C** e simulação pelo **Wokwi integrado ao VS Code**.

## Objetivo

Desenvolver uma aplicação embarcada capaz de inicializar um sensor simulado, realizar leituras e exibir os dados no monitor serial.

## Hardware utilizado

- ESP32-S3 DevKitC-1
- MPU6050
- Comunicação I2C

## Ligações do circuito

| MPU6050 | ESP32-S3 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 8 |
| SCL | GPIO 9 |

O endereço I2C utilizado pelo MPU6050 é `0x68`.

## Funcionamento

A aplicação:

1. Inicializa o barramento I2C.
2. Adiciona o MPU6050 ao barramento.
3. Retira o sensor do modo sleep pelo registrador `PWR_MGMT_1`.
4. Lê 14 bytes a partir do registrador `0x3B`.
5. Extrai os valores brutos dos três eixos do acelerômetro e do giroscópio.
6. Exibe as leituras no monitor serial a cada segundo.

Exemplo de saída:

```text
I (...) MPU6050_APP: Inicializando barramento I2C...
I (...) MPU6050_APP: Configurando sensor MPU6050...
I (...) MPU6050_APP: Sensor MPU6050 ativo! Lendo acelerometro e giroscopio...
I (...) MPU6050_APP: Acelerometro [X: 0 | Y: 0 | Z: 16384]
I (...) MPU6050_APP: Giroscopio   [X: 0 | Y: 0 | Z: 0]
```

## Compilação

Abra um terminal ESP-IDF na raiz do projeto e execute:

```bash
idf.py set-target esp32s3
idf.py build
```

Ao final, o terminal deve apresentar a conclusão do build sem erros.

## Simulação no Wokwi

O projeto usa os arquivos:

- `diagram.json` — circuito do ESP32-S3 com o MPU6050;
- `wokwi.toml` — firmware e arquivo ELF utilizados pelo simulador.

Depois do build, no VS Code execute:

```text
Wokwi: Start Simulator
```

O monitor serial deve mostrar continuamente as leituras do acelerômetro e do giroscópio.

## Estrutura principal

```text
atividade_sensor/
├── CMakeLists.txt
├── diagram.json
├── wokwi.toml
├── sdkconfig
├── main/
│   ├── CMakeLists.txt
│   └── main.c
└── evidencias/
```

As pastas de compilação `build/` e `build-check/` não devem ser versionadas.

## Evidências para a entrega

Salvar na pasta `evidencias/`:

1. `01-configuracao-esp-idf-wokwi.png` — VS Code mostrando ESP-IDF configurado e Wokwi conectado.
2. `02-circuito-esp32s3-mpu6050.png` — circuito completo no Wokwi.
3. `03-build-sem-erros.png` — terminal exibindo o build finalizado sem erros.
4. `04-monitor-serial.png` — simulação executando e monitor serial exibindo leituras do MPU6050.

## Critérios atendidos

- Configuração do ESP-IDF e Wokwi.
- Circuito ESP32-S3 + MPU6050.
- Código em C com ESP-IDF.
- Inicialização do sensor via I2C.
- Leitura do acelerômetro e do giroscópio.
- Exibição das leituras no monitor serial.
- Projeto versionado em Git.
