#include <Arduino.h>
#include <stdint.h>

#include "icm42688.h"

#define SAMPLE_RATE 100

void setup(void) {
    icm42688_init();

    icm42688_reg_accel_config0_t icm42688_reg_accel_config0 = icm42688_reg_new_accel_config0();
    icm42688_reg_accel_config0.accel_fs_sel = ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_2G;
    icm42688_reg_accel_config0.accel_odr = ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_1_KHZ;
    icm42688_reg_set_accel_config0(&icm42688_reg_accel_config0);

    icm42688_reg_gyro_accel_config0_t icm42688_reg_gyro_accel_config0 = icm42688_reg_new_gyro_accel_config0();
    icm42688_reg_gyro_accel_config0.accel_ui_filt_bw = ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_LOW_LATENCY_ODR_DEC2;
    icm42688_reg_set_gyro_accel_config0(&icm42688_reg_gyro_accel_config0);

    icm42688_reg_accel_config_static2_t icm42688_reg_accel_config_static2 = icm42688_reg_new_accel_config_static2();
    icm42688_reg_accel_config_static2.accel_aaf_delt = 100;
    icm42688_reg_accel_config_static2.accel_aaf_dis = ICM42688_REG_ACCEL_CONFIG_STATIC2_ACCEL_AAF_DIS_ENABLED;
    icm42688_reg_set_accel_config_static2(&icm42688_reg_accel_config_static2);

    icm42688_reg_pwr_mgmt0_t icm42688_reg_pwr_mgmt0 = icm42688_reg_new_pwr_mgmt0();
    icm42688_reg_pwr_mgmt0.temp_dis = ICM42688_REG_PWR_MGMT0_TEMP_DIS_DISABLED;
    icm42688_reg_pwr_mgmt0.accel_mode = ICM42688_REG_PWR_MGMT0_ACCEL_MODE_LOW_NOISE;
    icm42688_reg_set_pwr_mgmt0(&icm42688_reg_pwr_mgmt0);

    Serial.begin(115200);
}

uint32_t prev_millis = 0;

void loop(void) {
    uint32_t current_millis = millis();
    if (current_millis - prev_millis >= (1000 / SAMPLE_RATE)) {
        icm42688_reg_accel_data_x_t accel_data_x;
        icm42688_reg_get_accel_data_x(&accel_data_x);
        Serial.print((int16_t)(accel_data_x.accel_data_x_h << 8 | accel_data_x.accel_data_x_l));
        Serial.print("\t");

        icm42688_reg_accel_data_y_t accel_data_y;
        icm42688_reg_get_accel_data_y(&accel_data_y);
        Serial.print((int16_t)(accel_data_y.accel_data_y_h << 8 | accel_data_y.accel_data_y_l));
        Serial.print("\t");

        icm42688_reg_accel_data_z_t accel_data_z;
        icm42688_reg_get_accel_data_z(&accel_data_z);
        Serial.print((int16_t)(accel_data_z.accel_data_z_h << 8 | accel_data_z.accel_data_z_l));
        Serial.print("\n");

        prev_millis = current_millis;
    }
}
