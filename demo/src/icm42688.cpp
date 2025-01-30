#include "icm42688.h"

void icm42688_init(void) {
    Wire.begin();
    icm42688_reset();
}

void icm42688_reset(void) {
    icm42688_reg_device_config_t device_config = icm42688_reg_new_device_config();
    device_config.soft_reset_config = ICM42688_REG_DEVICE_CONFIG_SOFT_RESET_CONFIG_ENABLE;
    icm42688_reg_set_device_config(&device_config);
    delay(100);
}

void icm42688_wait(void) {
    icm42688_reg_int_status_t int_status;
    do {
        icm42688_reg_get_int_status(&int_status);
    } while (!int_status.data_rdy_int);
}

void icm42688_read_reg(uint8_t reg, uint8_t* rx_data) {
    Wire.beginTransmission(ICM42688_I2C_ADDRES);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(ICM42688_I2C_ADDRES, 1);
    *rx_data = Wire.read();
}

void icm42688_write_reg(uint8_t reg, uint8_t tx_data) {
    Wire.beginTransmission(ICM42688_I2C_ADDRES);
    Wire.write(reg);
    Wire.write(tx_data);
    Wire.endTransmission();
}

icm42688_reg_accel_config0_t icm42688_reg_new_accel_config0(void) {
    icm42688_reg_accel_config0_t accel_config0;
    accel_config0.accel_fs_sel = ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_16G;
    accel_config0.accel_odr = ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_1_KHZ;
    return accel_config0;
}

void icm42688_reg_set_accel_config0(icm42688_reg_accel_config0_t* accel_config0) {
    uint8_t accel_config0_data = __ICM42688_REG_ACCEL_CONFIG0_DEFAULT_VALUE;
    accel_config0_data &= ~(0x03 << 5);
    accel_config0_data |= (accel_config0->accel_fs_sel & 0x03) << 5;
    accel_config0_data &= ~0x0F;
    accel_config0_data |= (accel_config0->accel_odr & 0x0F);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_ACCEL_CONFIG0, accel_config0_data);
}

void icm42688_reg_get_accel_config0(icm42688_reg_accel_config0_t* accel_config0) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t accel_config0_data = 0;
    icm42688_read_reg(ICM42688_REG_ACCEL_CONFIG0, &accel_config0_data);
    accel_config0->accel_fs_sel = (accel_config0_data >> 5) & 0x03;
    accel_config0->accel_odr = accel_config0_data & 0x0F;
}

icm42688_reg_accel_config1_t icm42688_reg_new_accel_config1(void) {
    icm42688_reg_accel_config1_t accel_config1;
    accel_config1.accel_ui_filt_ord = ICM42688_REG_ACCEL_CONFIG1_ACCEL_UI_FILT_ORD_2;
    accel_config1.accel_dec2_m2_ord = ICM42688_REG_ACCEL_CONFIG1_ACCEL_DEC2_M2_ORD_3;
    return accel_config1;
}

void icm42688_reg_set_accel_config1(icm42688_reg_accel_config1_t* accel_config1) {
    uint8_t accel_config1_data = __ICM42688_REG_ACCEL_CONFIG1_DEFAULT_VALUE;
    accel_config1_data &= ~(0x03 << 3);
    accel_config1_data |= (accel_config1->accel_ui_filt_ord & 0x03) << 3;
    accel_config1_data &= ~(0x03 << 1);
    accel_config1_data |= (accel_config1->accel_dec2_m2_ord & 0x03) << 1;
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_ACCEL_CONFIG1, accel_config1_data);
}

void icm42688_reg_get_accel_config1(icm42688_reg_accel_config1_t* accel_config1) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t accel_config1_data = 0;
    icm42688_read_reg(ICM42688_REG_ACCEL_CONFIG1, &accel_config1_data);
    accel_config1->accel_ui_filt_ord = (accel_config1_data >> 3) & 0x03;
    accel_config1->accel_dec2_m2_ord = (accel_config1_data >> 1) & 0x03;
}

icm42688_reg_accel_config_static2_t icm42688_reg_new_accel_config_static2(void) {
    icm42688_reg_accel_config_static2_t accel_config_static2;
    accel_config_static2.accel_aaf_delt = 0x18;
    accel_config_static2.accel_aaf_dis = ICM42688_REG_ACCEL_CONFIG_STATIC2_ACCEL_AAF_DIS_ENABLED;
    return accel_config_static2;
}

void icm42688_reg_set_accel_config_static2(icm42688_reg_accel_config_static2_t* accel_config_static2) {
    uint8_t accel_config_static2_data = __ICM42688_REG_ACCEL_CONFIG_STATIC2_DEFAULT_VALUE;
    accel_config_static2_data &= ~(0x3F << 1);
    accel_config_static2_data |= (accel_config_static2->accel_aaf_delt & 0x3F) << 1;
    accel_config_static2_data &= ~0x01;
    accel_config_static2_data |= (accel_config_static2->accel_aaf_dis & 0x01);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 2);
    icm42688_write_reg(ICM42688_REG_ACCEL_CONFIG_STATIC2, accel_config_static2_data);
}

void icm42688_reg_get_accel_config_static2(icm42688_reg_accel_config_static2_t* accel_config_static2) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 2);
    uint8_t accel_config_static2_data = 0;
    icm42688_read_reg(ICM42688_REG_ACCEL_CONFIG_STATIC2, &accel_config_static2_data);
    accel_config_static2->accel_aaf_delt = (accel_config_static2_data >> 1) & 0x3F;
    accel_config_static2->accel_aaf_dis = accel_config_static2_data & 0x01;
}

void icm42688_reg_get_accel_data_x(icm42688_reg_accel_data_x_t* accel_data_x) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_X0, &accel_data_x->accel_data_x_l);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_X1, &accel_data_x->accel_data_x_h);
}

void icm42688_reg_get_accel_data_y(icm42688_reg_accel_data_y_t* accel_data_y) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_Y0, &accel_data_y->accel_data_y_l);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_Y1, &accel_data_y->accel_data_y_h);
}

void icm42688_reg_get_accel_data_z(icm42688_reg_accel_data_z_t* accel_data_z) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_Z0, &accel_data_z->accel_data_z_l);
    icm42688_read_reg(ICM42688_REG_ACCEL_DATA_Z1, &accel_data_z->accel_data_z_h);
}

icm42688_reg_device_config_t icm42688_reg_new_device_config(void) {
    icm42688_reg_device_config_t device_config;
    device_config.spi_mode = ICM42688_REG_DEVICE_CONFIG_SPI_MODE_0_3;
    device_config.soft_reset_config = ICM42688_REG_DEVICE_CONFIG_SOFT_RESET_CONFIG_NORMAL;
    return device_config;
}

void icm42688_reg_set_device_config(icm42688_reg_device_config_t* device_config) {
    uint8_t device_config_data = __ICM42688_REG_DEVICE_CONFIG_DEFAULT_VALUE;
    device_config_data &= ~(0x01 << 4);
    device_config_data |= (device_config->spi_mode & 0x01) << 4;
    device_config_data &= ~0x01;
    device_config_data |= (device_config->soft_reset_config & 0x01);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_DEVICE_CONFIG, device_config_data);
}

void icm42688_reg_get_device_config(icm42688_reg_device_config_t* device_config) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t device_config_data = 0;
    icm42688_read_reg(ICM42688_REG_DEVICE_CONFIG, &device_config_data);
    device_config->spi_mode = (device_config_data >> 4) & 0x01;
    device_config->soft_reset_config = device_config_data & 0x01;
}

icm42688_reg_drive_config_t icm42688_reg_new_drive_config(void) {
    icm42688_reg_drive_config_t drive_config;
    drive_config.i2c_slew_rate = ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_20_60_NS;
    drive_config.spi_slew_rate = ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_0_2_NS;
    return drive_config;
}

void icm42688_reg_set_drive_config(icm42688_reg_drive_config_t* drive_config) {
    uint8_t drive_config_data = __ICM42688_REG_DRIVE_CONFIG_DEFAULT_VALUE;
    drive_config_data &= ~(0x07 << 3);
    drive_config_data |= (drive_config->i2c_slew_rate & 0x07) << 3;
    drive_config_data &= ~0x07;
    drive_config_data |= (drive_config->spi_slew_rate & 0x07);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_DRIVE_CONFIG, drive_config_data);
}

void icm42688_reg_get_drive_config(icm42688_reg_drive_config_t* drive_config) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t drive_config_data = 0;
    icm42688_read_reg(ICM42688_REG_DRIVE_CONFIG, &drive_config_data);
    drive_config->i2c_slew_rate = (drive_config_data >> 3) & 0x07;
    drive_config->spi_slew_rate = drive_config_data & 0x07;
}

icm42688_reg_gyro_accel_config0_t icm42688_reg_new_gyro_accel_config0(void) {
    icm42688_reg_gyro_accel_config0_t gyro_accel_config0;
    gyro_accel_config0.accel_ui_filt_bw = ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_4;
    gyro_accel_config0.gyro_ui_filt_bw = ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_4;
    return gyro_accel_config0;
}

void icm42688_reg_set_gyro_accel_config0(icm42688_reg_gyro_accel_config0_t* gyro_accel_config0) {
    uint8_t gyro_accel_config0_data = __ICM42688_REG_GYRO_ACCEL_CONFIG0_DEFAULT_VALUE;
    gyro_accel_config0_data &= ~(0x0F << 4);
    gyro_accel_config0_data |= (gyro_accel_config0->accel_ui_filt_bw & 0x0F) << 4;
    gyro_accel_config0_data &= ~0x0F;
    gyro_accel_config0_data |= (gyro_accel_config0->gyro_ui_filt_bw & 0x0F);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_GYRO_ACCEL_CONFIG0, gyro_accel_config0_data);
}

void icm42688_reg_get_gyro_accel_config0(icm42688_reg_gyro_accel_config0_t* gyro_accel_config0) {
    icm42688_write_reg(ICM42688_REG_GYRO_ACCEL_CONFIG0, 0);
    uint8_t gyro_accel_config0_data = 0;
    icm42688_read_reg(ICM42688_REG_GYRO_ACCEL_CONFIG0, &gyro_accel_config0_data);
    gyro_accel_config0->accel_ui_filt_bw = (gyro_accel_config0_data >> 4) & 0x0F;
    gyro_accel_config0->gyro_ui_filt_bw = gyro_accel_config0_data & 0x0F;
}

void icm42688_reg_get_gyro_data_x(icm42688_reg_gyro_data_x_t* gyro_data_x) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_X0, &gyro_data_x->gyro_data_x_l);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_X1, &gyro_data_x->gyro_data_x_h);
}

void icm42688_reg_get_gyro_data_y(icm42688_reg_gyro_data_y_t* gyro_data_y) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_Y0, &gyro_data_y->gyro_data_y_l);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_Y1, &gyro_data_y->gyro_data_y_h);
}

void icm42688_reg_get_gyro_data_z(icm42688_reg_gyro_data_z_t* gyro_data_z) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_Z0, &gyro_data_z->gyro_data_z_l);
    icm42688_read_reg(ICM42688_REG_GYRO_DATA_Z1, &gyro_data_z->gyro_data_z_h);
}

icm42688_reg_int_config1_t icm42688_reg_new_int_config1(void) {
    icm42688_reg_int_config1_t int_config1;
    int_config1.int_tpulse_duration = ICM42688_REG_INT_CONFIG1_INT_TPULSE_DURATION_100US;
    int_config1.int_tdeassert_disable = ICM42688_REG_INT_CONFIG1_INT_TDEASSERT_DISABLE_MINIMUM;
    int_config1.int_async_reset = ICM42688_REG_INT_CONFIG1_INT_ASYNC_RESET_DISABLED;
    return int_config1;
}

void icm42688_reg_set_int_config1(icm42688_reg_int_config1_t* int_config1) {
    uint8_t int_config1_data = __ICM42688_REG_INT_CONFIG1_DEFAULT_VALUE;
    int_config1_data &= ~(0x01 << 6);
    int_config1_data |= (int_config1->int_tpulse_duration & 0x01) << 6;
    int_config1_data &= ~(0x01 << 5);
    int_config1_data |= (int_config1->int_tdeassert_disable & 0x01) << 5;
    int_config1_data &= ~(0x01 << 4);
    int_config1_data |= (int_config1->int_async_reset & 0x01) << 4;
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_INT_CONFIG1, int_config1_data);
}

void icm42688_reg_get_int_config1(icm42688_reg_int_config1_t* int_config1) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t int_config1_data = 0;
    icm42688_read_reg(ICM42688_REG_INT_CONFIG1, &int_config1_data);
    int_config1->int_tpulse_duration = (int_config1_data >> 6) & 0x01;
    int_config1->int_tdeassert_disable = (int_config1_data >> 5) & 0x01;
    int_config1->int_async_reset = (int_config1_data >> 4) & 0x01;
}

icm42688_reg_int_config_t icm42688_reg_new_int_config(void) {
    icm42688_reg_int_config_t int_config;
    int_config.int2_mode = ICM42688_REG_INT_CONFIG_INT2_MODE_PULSED;
    int_config.int2_drive_circuit = ICM42688_REG_INT_CONFIG_INT2_DRIVE_CIRCUIT_OPEN_DRAIN;
    int_config.int2_polarity = ICM42688_REG_INT_CONFIG_INT2_POLARITY_ACTIVE_LOW;
    int_config.int1_mode = ICM42688_REG_INT_CONFIG_INT1_MODE_PULSED;
    int_config.int1_drive_circuit = ICM42688_REG_INT_CONFIG_INT1_DRIVE_CIRCUIT_OPEN_DRAIN;
    int_config.int1_polarity = ICM42688_REG_INT_CONFIG_INT1_POLARITY_ACTIVE_LOW;
    return int_config;
}

void icm42688_reg_set_int_config(icm42688_reg_int_config_t* int_config) {
    uint8_t int_config_data = __ICM42688_REG_INT_CONFIG_DEFAULT_VALUE;
    int_config_data &= ~(0x01 << 5);
    int_config_data |= (int_config->int2_mode & 0x01) << 5;
    int_config_data &= ~(0x01 << 4);
    int_config_data |= (int_config->int2_drive_circuit & 0x01) << 4;
    int_config_data &= ~(0x01 << 3);
    int_config_data |= (int_config->int2_polarity & 0x01) << 3;
    int_config_data &= ~(0x01 << 2);
    int_config_data |= (int_config->int1_mode & 0x01) << 2;
    int_config_data &= ~(0x01 << 1);
    int_config_data |= (int_config->int1_drive_circuit & 0x01) << 1;
    int_config_data &= ~0x01;
    int_config_data |= (int_config->int1_polarity & 0x01);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_INT_CONFIG, int_config_data);
}

void icm42688_reg_get_int_config(icm42688_reg_int_config_t* int_config) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t int_config_data = 0;
    icm42688_read_reg(ICM42688_REG_INT_CONFIG, &int_config_data);
    int_config->int2_mode = (int_config_data >> 5) & 0x01;
    int_config->int2_drive_circuit = (int_config_data >> 4) & 0x01;
    int_config->int2_polarity = (int_config_data >> 3) & 0x01;
    int_config->int1_mode = (int_config_data >> 2) & 0x01;
    int_config->int1_drive_circuit = (int_config_data >> 1) & 0x01;
    int_config->int1_polarity = int_config_data & 0x01;
}

icm42688_reg_intf_config1_t icm42688_reg_new_intf_config1(void) {
    icm42688_reg_intf_config1_t intf_config1;
    intf_config1.accel_lp_clk_sel = ICM42688_REG_INTF_CONFIG1_ACCEL_LP_CLK_SEL_WAKEUP_OSC;
    intf_config1.rtc_mode = ICM42688_REG_INTF_CONFIG1_RTC_MODE_DISABLED;
    intf_config1.clksel = ICM42688_REG_INTF_CONFIG1_CLKSEL_PLL_OR_RC;
    return intf_config1;
}

void icm42688_reg_set_intf_config1(icm42688_reg_intf_config1_t* intf_config1) {
    uint8_t intf_config1_data = __ICM42688_REG_INTF_CONFIG1_DEFAULT_VALUE;
    intf_config1_data &= ~(0x01 << 3);
    intf_config1_data |= (intf_config1->accel_lp_clk_sel & 0x01) << 3;
    intf_config1_data &= ~(0x01 << 2);
    intf_config1_data |= (intf_config1->rtc_mode & 0x01) << 2;
    intf_config1_data &= ~0x03;
    intf_config1_data |= (intf_config1->clksel & 0x03);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_INTF_CONFIG1, intf_config1_data);
}

void icm42688_reg_get_intf_config1(icm42688_reg_intf_config1_t* intf_config1) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t intf_config1_data = 0;
    icm42688_read_reg(ICM42688_REG_INTF_CONFIG1, &intf_config1_data);
    intf_config1->accel_lp_clk_sel = (intf_config1_data >> 3) & 0x01;
    intf_config1->rtc_mode = (intf_config1_data >> 2) & 0x01;
    intf_config1->clksel = intf_config1_data & 0x03;
}

icm42688_reg_int_source0_t icm42688_reg_new_int_source0(void) {
    icm42688_reg_int_source0_t int_source0;
    int_source0.ui_fsync_int1_en = ICM42688_REG_INT_SOURCE0_UI_FSYNC_INT1_EN_DISABLED;
    int_source0.pll_rdy_int1_en = ICM42688_REG_INT_SOURCE0_PLL_RDY_INT1_EN_DISABLED;
    int_source0.reset_done_int1_en = ICM42688_REG_INT_SOURCE0_RESET_DONE_INT1_EN_ENABLED;
    int_source0.ui_drdy_int1_en = ICM42688_REG_INT_SOURCE0_UI_DRDY_INT1_EN_DISABLED;
    int_source0.fifo_ths_int1_en = ICM42688_REG_INT_SOURCE0_FIFO_THS_INT1_EN_DISABLED;
    int_source0.fifo_full_int1_en = ICM42688_REG_INT_SOURCE0_FIFO_FULL_INT1_EN_DISABLED;
    int_source0.ui_agc_rdy_int1_en = ICM42688_REG_INT_SOURCE0_UI_AGC_RDY_INT1_EN_DISABLED;
    return int_source0;
}

void icm42688_reg_set_int_source0(icm42688_reg_int_source0_t* int_source0) {
    uint8_t int_source0_data = __ICM42688_REG_INT_SOURCE0_DEFAULT_VALUE;
    int_source0_data &= ~(0x01 << 6);
    int_source0_data |= (int_source0->ui_fsync_int1_en & 0x01) << 6;
    int_source0_data &= ~(0x01 << 5);
    int_source0_data |= (int_source0->pll_rdy_int1_en & 0x01) << 5;
    int_source0_data &= ~(0x01 << 4);
    int_source0_data |= (int_source0->reset_done_int1_en & 0x01) << 4;
    int_source0_data &= ~(0x01 << 3);
    int_source0_data |= (int_source0->ui_drdy_int1_en & 0x01) << 3;
    int_source0_data &= ~(0x01 << 2);
    int_source0_data |= (int_source0->fifo_ths_int1_en & 0x01) << 2;
    int_source0_data &= ~(0x01 << 1);
    int_source0_data |= (int_source0->fifo_full_int1_en & 0x01) << 1;
    int_source0_data &= ~0x01;
    int_source0_data |= (int_source0->ui_agc_rdy_int1_en & 0x01);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_INT_SOURCE0, int_source0_data);
}

void icm42688_reg_get_int_source0(icm42688_reg_int_source0_t* int_source0) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t int_source0_data = 0;
    icm42688_read_reg(ICM42688_REG_INT_SOURCE0, &int_source0_data);
    int_source0->ui_fsync_int1_en = (int_source0_data >> 6) & 0x01;
    int_source0->pll_rdy_int1_en = (int_source0_data >> 5) & 0x01;
    int_source0->reset_done_int1_en = (int_source0_data >> 4) & 0x01;
    int_source0->ui_drdy_int1_en = (int_source0_data >> 3) & 0x01;
    int_source0->fifo_ths_int1_en = (int_source0_data >> 2) & 0x01;
    int_source0->fifo_full_int1_en = (int_source0_data >> 1) & 0x01;
    int_source0->ui_agc_rdy_int1_en = int_source0_data & 0x01;
}

void icm42688_reg_get_int_status(icm42688_reg_int_status_t* int_status) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t int_status_data = 0;
    icm42688_read_reg(ICM42688_REG_INT_STATUS, &int_status_data);
    int_status->ui_fsync_int = (int_status_data >> 6) & 0x01;
    int_status->pll_rdy_int = (int_status_data >> 5) & 0x01;
    int_status->reset_done_int = (int_status_data >> 4) & 0x01;
    int_status->data_rdy_int = (int_status_data >> 3) & 0x01;
    int_status->fifo_ths_int = (int_status_data >> 2) & 0x01;
    int_status->fifo_full_int = (int_status_data >> 1) & 0x01;
    int_status->agc_rdy_int = int_status_data & 0x01;
}

icm42688_reg_pwr_mgmt0_t icm42688_reg_new_pwr_mgmt0(void) {
    icm42688_reg_pwr_mgmt0_t pwr_mgmt0;
    pwr_mgmt0.temp_dis = ICM42688_REG_PWR_MGMT0_TEMP_DIS_ENABLED;
    pwr_mgmt0.idle = ICM42688_REG_PWR_MGMT0_IDLE_ENABLED;
    pwr_mgmt0.gyro_mode = ICM42688_REG_PWR_MGMT0_GYRO_MODE_OFF;
    pwr_mgmt0.accel_mode = ICM42688_REG_PWR_MGMT0_ACCEL_MODE_OFF;
    return pwr_mgmt0;
}

void icm42688_reg_set_pwr_mgmt0(icm42688_reg_pwr_mgmt0_t* pwr_mgmt0) {
    uint8_t pwr_mgmt0_data = __ICM42688_REG_PWR_MGMT0_DEFAULT_VALUE;
    pwr_mgmt0_data &= ~(0x01 << 5);
    pwr_mgmt0_data |= (pwr_mgmt0->temp_dis & 0x01) << 5;
    pwr_mgmt0_data &= ~(0x01 << 4);
    pwr_mgmt0_data |= (pwr_mgmt0->idle & 0x01) << 4;
    pwr_mgmt0_data &= ~(0x03 << 2);
    pwr_mgmt0_data |= (pwr_mgmt0->gyro_mode & 0x03) << 2;
    pwr_mgmt0_data &= ~0x03;
    pwr_mgmt0_data |= (pwr_mgmt0->accel_mode & 0x03);
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_write_reg(ICM42688_REG_PWR_MGMT0, pwr_mgmt0_data);
}

void icm42688_reg_get_pwr_mgmt0(icm42688_reg_pwr_mgmt0_t* pwr_mgmt0) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    uint8_t pwr_mgmt0_data = 0;
    icm42688_read_reg(ICM42688_REG_PWR_MGMT0, &pwr_mgmt0_data);
    pwr_mgmt0->temp_dis = (pwr_mgmt0_data >> 5) & 0x01;
    pwr_mgmt0->idle = (pwr_mgmt0_data >> 4) & 0x01;
    pwr_mgmt0->gyro_mode = (pwr_mgmt0_data >> 2) & 0x03;
    pwr_mgmt0->accel_mode = pwr_mgmt0_data & 0x03;
}

void icm42688_reg_get_temp_data(icm42688_reg_temp_data_t* temp_data) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_TEMP_DATA0, &temp_data->temp_data_l);
    icm42688_read_reg(ICM42688_REG_TEMP_DATA1, &temp_data->temp_data_h);
}

void icm42688_reg_get_who_am_i(icm42688_reg_who_am_i_t* who_am_i) {
    icm42688_write_reg(ICM42688_REG_REG_BANK_SEL, 0);
    icm42688_read_reg(ICM42688_REG_WHO_AM_I, &who_am_i->dev_id);
}
