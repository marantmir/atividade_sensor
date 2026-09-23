#include <stddef.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "MPU6050_APP";

#define I2C_MASTER_SCL_IO           9
#define I2C_MASTER_SDA_IO           8
#define I2C_MASTER_NUM              I2C_NUM_0
#define I2C_MASTER_FREQ_HZ          100000
#define I2C_MASTER_TIMEOUT_MS       1000
#define MPU6050_ADDR                0x68
#define MPU6050_PWR_MGMT_1          0x6B
#define MPU6050_ACCEL_XOUT_H        0x3B

static i2c_master_bus_handle_t i2c_bus = NULL;
static i2c_master_dev_handle_t mpu6050_dev = NULL;

static esp_err_t mpu6050_register_write(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = { reg_addr, data };
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS);
}

static esp_err_t mpu6050_register_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS);
}

static esp_err_t i2c_master_init(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    esp_err_t ret = i2c_new_master_bus(&bus_config, &i2c_bus);
    if (ret != ESP_OK) {
        return ret;
    }

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU6050_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };

    ret = i2c_master_bus_add_device(i2c_bus, &dev_config, &mpu6050_dev);
    if (ret != ESP_OK) {
        i2c_del_master_bus(i2c_bus);
        i2c_bus = NULL;
        mpu6050_dev = NULL;
    }

    return ret;
}

void app_main(void)
{
    ESP_LOGI(TAG, "Inicializando barramento I2C...");
    ESP_ERROR_CHECK(i2c_master_init());

    ESP_LOGI(TAG, "Configurando sensor MPU6050...");
    ESP_ERROR_CHECK(mpu6050_register_write(mpu6050_dev, MPU6050_PWR_MGMT_1, 0x00));
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "Sensor MPU6050 ativo! Lendo dados...");

    uint8_t raw_data[6];
    int16_t accel_x, accel_y, accel_z;

    while (1) {
        esp_err_t ret = mpu6050_register_read(mpu6050_dev, MPU6050_ACCEL_XOUT_H, raw_data, sizeof(raw_data));

        if (ret == ESP_OK) {
            accel_x = (int16_t)((uint16_t)raw_data[0] << 8 | raw_data[1]);
            accel_y = (int16_t)((uint16_t)raw_data[2] << 8 | raw_data[3]);
            accel_z = (int16_t)((uint16_t)raw_data[4] << 8 | raw_data[5]);

            ESP_LOGI(TAG, "Acelerometro [X: %d | Y: %d | Z: %d]", accel_x, accel_y, accel_z);
        } else {
            ESP_LOGE(TAG, "Erro ao ler o sensor!");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
