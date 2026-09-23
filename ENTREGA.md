# Roteiro de Entrega — Atividade Avaliativa Prática 2/6

## O que deve ser entregue

### 1. Link do repositório Git

Repositório:

https://github.com/marantmir/atividade_sensor

Antes de enviar, confirme que o repositório contém pelo menos:

- `CMakeLists.txt`
- `diagram.json`
- `wokwi.toml`
- `sdkconfig`
- `main/CMakeLists.txt`
- `main/main.c`
- `README.md`
- pasta `evidencias/`

### 2. Evidências obrigatórias

Use quatro capturas separadas para deixar cada critério evidente.

#### 01 — Configuração do ESP-IDF e Wokwi

A captura deve mostrar o VS Code com evidência de que:

- a extensão ESP-IDF está instalada/configurada;
- o projeto reconhece o ESP-IDF;
- o Wokwi está instalado e autenticado/conectado.

Nome sugerido:

`evidencias/01-configuracao-esp-idf-wokwi.png`

#### 02 — Circuito montado

A captura deve mostrar:

- ESP32-S3;
- MPU6050;
- VCC ligado a 3V3;
- GND ligado a GND;
- SDA ligado ao GPIO 8;
- SCL ligado ao GPIO 9.

Nome sugerido:

`evidencias/02-circuito-esp32s3-mpu6050.png`

#### 03 — Código compilando sem erros

No terminal ESP-IDF execute:

```bash
idf.py set-target esp32s3
idf.py build
```

Capture a parte final do terminal mostrando a compilação concluída sem erros.

Nome sugerido:

`evidencias/03-build-sem-erros.png`

#### 04 — Monitor serial mostrando leituras

Depois do build execute no VS Code:

`Wokwi: Start Simulator`

A captura deve mostrar leituras como:

```text
Acelerometro [X: ... | Y: ... | Z: ...]
Giroscopio   [X: ... | Y: ... | Z: ...]
```

Nome sugerido:

`evidencias/04-monitor-serial.png`

## Checklist final

- [ ] ESP-IDF configurado.
- [ ] Conta/extensão Wokwi funcionando.
- [ ] ESP32-S3 selecionado como target.
- [ ] MPU6050 conectado corretamente.
- [ ] Código implementado em C.
- [ ] Sensor inicializado via I2C.
- [ ] Acelerômetro sendo lido.
- [ ] Giroscópio sendo lido.
- [ ] `idf.py build` concluído sem erros.
- [ ] Wokwi executando pelo VS Code.
- [ ] Monitor serial exibindo dados.
- [ ] Quatro screenshots salvos na pasta `evidencias/`.
- [ ] Screenshots enviados ao GitHub.
- [ ] Link do repositório testado.

## Texto sugerido para a plataforma da disciplina

**Atividade Avaliativa Prática 2/6 — Leitura de Sensor**

Foi desenvolvida uma aplicação embarcada em C utilizando ESP-IDF, ESP32-S3 e o sensor MPU6050 simulado no Wokwi. A comunicação com o sensor é feita via I2C utilizando SDA no GPIO 8 e SCL no GPIO 9. A aplicação inicializa o MPU6050 e exibe continuamente no monitor serial as leituras dos três eixos do acelerômetro e do giroscópio.

Repositório GitHub:

https://github.com/marantmir/atividade_sensor

As evidências da configuração, circuito, compilação e monitor serial estão incluídas na pasta `evidencias/`.
