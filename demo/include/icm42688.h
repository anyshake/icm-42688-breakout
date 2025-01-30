#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

// User Bank 0 Registers
#define ICM42688_REG_DEVICE_CONFIG 0x11
#define ICM42688_REG_DRIVE_CONFIG 0x13
#define ICM42688_REG_INT_CONFIG 0x14
#define ICM42688_REG_FIFO_CONFIG 0x16
#define ICM42688_REG_TEMP_DATA1 0x1D
#define ICM42688_REG_TEMP_DATA0 0x1E
#define ICM42688_REG_ACCEL_DATA_X1 0x1F
#define ICM42688_REG_ACCEL_DATA_X0 0x20
#define ICM42688_REG_ACCEL_DATA_Y1 0x21
#define ICM42688_REG_ACCEL_DATA_Y0 0x22
#define ICM42688_REG_ACCEL_DATA_Z1 0x23
#define ICM42688_REG_ACCEL_DATA_Z0 0x24
#define ICM42688_REG_GYRO_DATA_X1 0x25
#define ICM42688_REG_GYRO_DATA_X0 0x26
#define ICM42688_REG_GYRO_DATA_Y1 0x27
#define ICM42688_REG_GYRO_DATA_Y0 0x28
#define ICM42688_REG_GYRO_DATA_Z1 0x29
#define ICM42688_REG_GYRO_DATA_Z0 0x2A
#define ICM42688_REG_TMST_FSYNCH 0x2B
#define ICM42688_REG_TMST_FSYNCL 0x2C
#define ICM42688_REG_INT_STATUS 0x2D
#define ICM42688_REG_FIFO_COUNTH 0x2E
#define ICM42688_REG_FIFO_COUNTL 0x2F
#define ICM42688_REG_FIFO_DATA 0x30
#define ICM42688_REG_APEX_DATA0 0x31
#define ICM42688_REG_APEX_DATA1 0x32
#define ICM42688_REG_APEX_DATA2 0x33
#define ICM42688_REG_APEX_DATA3 0x34
#define ICM42688_REG_APEX_DATA4 0x35
#define ICM42688_REG_APEX_DATA5 0x36
#define ICM42688_REG_INT_STATUS2 0x37
#define ICM42688_REG_INT_STATUS3 0x38
#define ICM42688_REG_SIGNAL_PATH_RESET 0x4B
#define ICM42688_REG_INTF_CONFIG0 0x4C
#define ICM42688_REG_INTF_CONFIG1 0x4D
#define ICM42688_REG_PWR_MGMT0 0x4E
#define ICM42688_REG_GYRO_CONFIG0 0x4F
#define ICM42688_REG_ACCEL_CONFIG0 0x50
#define ICM42688_REG_GYRO_CONFIG1 0x51
#define ICM42688_REG_GYRO_ACCEL_CONFIG0 0x52
#define ICM42688_REG_ACCEL_CONFIG1 0x53
#define ICM42688_REG_GYRO_TMST_CONFIG 0x54
#define ICM42688_REG_APEX_CONFIG0 0x56
#define ICM42688_REG_SMD_CONFIG 0x57
#define ICM42688_REG_FIFO_CONFIG1 0x5F
#define ICM42688_REG_FIFO_CONFIG2 0x60
#define ICM42688_REG_FIFO_CONFIG3 0x61
#define ICM42688_REG_FSYNC_CONFIG 0x62
#define ICM42688_REG_INT_CONFIG0 0x63
#define ICM42688_REG_INT_CONFIG1 0x64
#define ICM42688_REG_INT_SOURCE0 0x65
#define ICM42688_REG_INT_SOURCE1 0x66
#define ICM42688_REG_INT_SOURCE3 0x68
#define ICM42688_REG_INT_SOURCE4 0x69
#define ICM42688_REG_FIFO_LOST_PKT0 0x6C
#define ICM42688_REG_FIFO_LOST_PKT1 0x6D
#define ICM42688_REG_SELF_TEST_CONFIG 0x70
#define ICM42688_REG_WHO_AM_I 0x75
#define ICM42688_REG_REG_BANK_SEL 0x76

// User Bank 1 Registers
#define ICM42688_REG_SENSOR_CONFIG0 0x03
#define ICM42688_REG_GYRO_CONFIG_STATIC2 0x0B
#define ICM42688_REG_GYRO_CONFIG_STATIC3 0x0C
#define ICM42688_REG_GYRO_CONFIG_STATIC4 0x0D
#define ICM42688_REG_GYRO_CONFIG_STATIC5 0x0E
#define ICM42688_REG_GYRO_CONFIG_STATIC6 0x0F
#define ICM42688_REG_GYRO_CONFIG_STATIC7 0x10
#define ICM42688_REG_GYRO_CONFIG_STATIC8 0x11
#define ICM42688_REG_GYRO_CONFIG_STATIC9 0x12
#define ICM42688_REG_GYRO_CONFIG_STATIC10 0x13
#define ICM42688_REG_XG_ST_DATA 0x5F
#define ICM42688_REG_YG_ST_DATA 0x60
#define ICM42688_REG_ZG_ST_DATA 0x61
#define ICM42688_REG_TMSTVAL0 0x62
#define ICM42688_REG_TMSTVAL1 0x63
#define ICM42688_REG_TMSTVAL2 0x64
#define ICM42688_REG_INTF_CONFIG4 0x7A
#define ICM42688_REG_INTF_CONFIG5 0x7B
#define ICM42688_REG_INTF_CONFIG6 0x7C

// User Bank 2 Registers
#define ICM42688_REG_ACCEL_CONFIG_STATIC2 0x03
#define ICM42688_REG_ACCEL_CONFIG_STATIC3 0x04
#define ICM42688_REG_ACCEL_CONFIG_STATIC4 0x05
#define ICM42688_REG_XA_ST_DATA 0x3B
#define ICM42688_REG_YA_ST_DATA 0x3C
#define ICM42688_REG_ZA_ST_DATA 0x3D

// User Bank 4 Registers
#define ICM42688_REG_APEX_CONFIG1 0x40
#define ICM42688_REG_APEX_CONFIG2 0x41
#define ICM42688_REG_APEX_CONFIG3 0x42
#define ICM42688_REG_APEX_CONFIG4 0x43
#define ICM42688_REG_APEX_CONFIG5 0x44
#define ICM42688_REG_APEX_CONFIG6 0x45
#define ICM42688_REG_APEX_CONFIG7 0x46
#define ICM42688_REG_APEX_CONFIG8 0x47
#define ICM42688_REG_APEX_CONFIG9 0x48
#define ICM42688_REG_ACCEL_WOM_X_THR 0x4A
#define ICM42688_REG_ACCEL_WOM_Y_THR 0x4B
#define ICM42688_REG_ACCEL_WOM_Z_THR 0x4C
#define ICM42688_REG_INT_SOURCE6 0x4D
#define ICM42688_REG_INT_SOURCE7 0x4E
#define ICM42688_REG_INT_SOURCE8 0x4F
#define ICM42688_REG_INT_SOURCE9 0x50
#define ICM42688_REG_INT_SOURCE10 0x51
#define ICM42688_REG_OFFSET_USER0 0x77
#define ICM42688_REG_OFFSET_USER1 0x78
#define ICM42688_REG_OFFSET_USER2 0x79
#define ICM42688_REG_OFFSET_USER3 0x7A
#define ICM42688_REG_OFFSET_USER4 0x7B
#define ICM42688_REG_OFFSET_USER5 0x7C
#define ICM42688_REG_OFFSET_USER6 0x7D
#define ICM42688_REG_OFFSET_USER7 0x7E
#define ICM42688_REG_OFFSET_USER8 0x7F

void icm42688_init(void);
void icm42688_reset(void);
void icm42688_wait(void);
void icm42688_read_reg(uint8_t reg, uint8_t* rx_data);
void icm42688_write_reg(uint8_t reg, uint8_t tx_data);

#define __ICM42688_REG_ACCEL_CONFIG0_DEFAULT_VALUE 0x06

#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_16G 0x00
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_8G 0x01
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_4G 0x02
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_FS_SEL_2G 0x03

#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_32_KHZ 0x01
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_16_KHZ 0x02
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_8_KHZ 0x03
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_4_KHZ 0x04
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_2_KHZ 0x05
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_1_KHZ 0x06
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_200_HZ 0x07
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_100_HZ 0x08
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_50_HZ 0x09
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_25_HZ 0x0A
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_12_5_HZ 0x0B
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_6_25_HZ 0x0C
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_3_125_HZ 0x0D
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_1_5625_HZ 0x0E
#define ICM42688_REG_ACCEL_CONFIG0_ACCEL_ODR_500_HZ 0x0F

typedef struct {
    // Full scale select for accelerometer UI interface output
    // 0x00: ±16g (default)
    // 0x01: ±8g
    // 0x02: ±4g
    // 0x03: ±2g
    uint8_t accel_fs_sel;
    // Accelerometer ODR selection for UI interface output
    // 0x01: 32kHz (LN mode)
    // 0x02: 16kHz (LN mode)
    // 0x03: 8kHz (LN mode)
    // 0x04: 4kHz (LN mode)
    // 0x05: 2kHz (LN mode)
    // 0x06: 1kHz (LN mode) (default)
    // 0x07: 200Hz (LP or LN mode)
    // 0x08: 100Hz (LP or LN mode)
    // 0x09: 50Hz (LP or LN mode)
    // 0x0A: 25Hz (LP or LN mode)
    // 0x0B: 12.5Hz (LP or LN mode)
    // 0x0C: 6.25Hz (LP mode)
    // 0x0D: 3.125Hz (LP mode)
    // 0x0E: 1.5625Hz (LP mode)
    // 0x0F: 500Hz (LP or LN mode)
    uint8_t accel_odr;
} icm42688_reg_accel_config0_t;

icm42688_reg_accel_config0_t icm42688_reg_new_accel_config0(void);
void icm42688_reg_set_accel_config0(icm42688_reg_accel_config0_t* accel_config0);
void icm42688_reg_get_accel_config0(icm42688_reg_accel_config0_t* accel_config0);

#define __ICM42688_REG_ACCEL_CONFIG1_DEFAULT_VALUE 0x0D

#define ICM42688_REG_ACCEL_CONFIG1_ACCEL_UI_FILT_ORD_1 0x00
#define ICM42688_REG_ACCEL_CONFIG1_ACCEL_UI_FILT_ORD_2 0x01
#define ICM42688_REG_ACCEL_CONFIG1_ACCEL_UI_FILT_ORD_3 0x02

#define ICM42688_REG_ACCEL_CONFIG1_ACCEL_DEC2_M2_ORD_3 0x02

typedef struct {
    // Selects order of ACCEL UI filter
    // 0x00: 1st order
    // 0x01: 2nd order (default)
    // 0x02: 3rd order
    uint8_t accel_ui_filt_ord;
    // Order of Accelerometer DEC2_M2 filter
    // 0x02: 3rd order (default)
    uint8_t accel_dec2_m2_ord;
} icm42688_reg_accel_config1_t;

icm42688_reg_accel_config1_t icm42688_reg_new_accel_config1(void);
void icm42688_reg_set_accel_config1(icm42688_reg_accel_config1_t* accel_config1);
void icm42688_reg_get_accel_config1(icm42688_reg_accel_config1_t* accel_config1);

#define __ICM42688_REG_ACCEL_CONFIG_STATIC2_DEFAULT_VALUE 0x30

#define ICM42688_REG_ACCEL_CONFIG_STATIC2_ACCEL_AAF_DIS_ENABLED 0x00
#define ICM42688_REG_ACCEL_CONFIG_STATIC2_ACCEL_AAF_DIS_DISABLED 0x01

typedef struct {
    // Controls bandwidth of the accelerometer anti-alias filter
    // 0x01 to 0x3F: Accelerometer anti-alias filter bandwidth setting in Hz
    uint8_t accel_aaf_delt;
    // Disables the Accelerometer Anti Alias Filte
    // 0x00: Enable accelerometer anti-aliasing filter (default)
    // 0x01: Disable accelerometer anti-aliasing filter
    uint8_t accel_aaf_dis;
} icm42688_reg_accel_config_static2_t;

icm42688_reg_accel_config_static2_t icm42688_reg_new_accel_config_static2(void);
void icm42688_reg_set_accel_config_static2(icm42688_reg_accel_config_static2_t* accel_config_static2);
void icm42688_reg_get_accel_config_static2(icm42688_reg_accel_config_static2_t* accel_config_static2);

typedef struct {
    // Lower byte of Accel X-axis data
    uint8_t accel_data_x_l;
    // Upper byte of Accel X-axis data
    uint8_t accel_data_x_h;
} icm42688_reg_accel_data_x_t;

void icm42688_reg_get_accel_data_x(icm42688_reg_accel_data_x_t* accel_data_x);

typedef struct {
    // Lower byte of Accel Y-axis data
    uint8_t accel_data_y_l;
    // Upper byte of Accel Y-axis data
    uint8_t accel_data_y_h;
} icm42688_reg_accel_data_y_t;

void icm42688_reg_get_accel_data_y(icm42688_reg_accel_data_y_t* accel_data_y);

typedef struct {
    // Lower byte of Accel Z-axis data
    uint8_t accel_data_z_l;
    // Upper byte of Accel Z-axis data
    uint8_t accel_data_z_h;
} icm42688_reg_accel_data_z_t;

void icm42688_reg_get_accel_data_z(icm42688_reg_accel_data_z_t* accel_data_z);

#define __ICM42688_REG_DEVICE_CONFIG_DEFAULT_VALUE 0x00

#define ICM42688_REG_DEVICE_CONFIG_SPI_MODE_0_3 0x00
#define ICM42688_REG_DEVICE_CONFIG_SPI_MODE_1_2 0x01

#define ICM42688_REG_DEVICE_CONFIG_SOFT_RESET_CONFIG_NORMAL 0x00
#define ICM42688_REG_DEVICE_CONFIG_SOFT_RESET_CONFIG_ENABLE 0x01

typedef struct {
    // SPI mode selection
    // 0x00: Mode 0 and Mode 3 (default)
    // 0x01: Mode 1 and Mode 2
    uint8_t spi_mode;
    // Accelerometer full-scale selection
    // After writing 1 to this bitfield, wait 1ms for soft reset
    // to be effective, before attempting any other register access
    // 0x00: Normal (default)
    // 0x01: Enable reset
    uint8_t soft_reset_config;
} icm42688_reg_device_config_t;

icm42688_reg_device_config_t icm42688_reg_new_device_config(void);
void icm42688_reg_set_device_config(icm42688_reg_device_config_t* device_config);
void icm42688_reg_get_device_config(icm42688_reg_device_config_t* device_config);

#define __ICM42688_REG_DRIVE_CONFIG_DEFAULT_VALUE 0x05

#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_20_60_NS 0x00
#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_12_36_NS 0x01
#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_6_18_NS 0x02
#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_4_12_NS 0x03
#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_2_6_NS 0x04
#define ICM42688_REG_DRIVE_CONFIG_I2C_SLEW_RATE_0_2_NS 0x05

#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_20_60_NS 0x00
#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_12_36_NS 0x01
#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_6_18_NS 0x02
#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_4_12_NS 0x03
#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_2_6_NS 0x04
#define ICM42688_REG_DRIVE_CONFIG_SPI_SLEW_RATE_0_2_NS 0x05

typedef struct {
    // Controls slew rate for output pin 14 in I2C mode only
    // 0x00: 20ns-60ns (default)
    // 0x01: 12ns-36ns
    // 0x02: 6ns-18ns
    // 0x03: 4ns-12ns
    // 0x04: 2ns-6ns
    // 0x05: < 2ns
    uint8_t i2c_slew_rate;
    // Controls slew rate for output pin 14 in SPI or I3CSM mode,
    // and for all other output pins
    // 0x00: 20ns-60ns
    // 0x01: 12ns-36ns
    // 0x02: 6ns-18ns
    // 0x03: 4ns-12ns
    // 0x04: 2ns-6ns
    // 0x05: < 2ns (default)
    uint8_t spi_slew_rate;
} icm42688_reg_drive_config_t;

icm42688_reg_drive_config_t icm42688_reg_new_drive_config(void);
void icm42688_reg_set_drive_config(icm42688_reg_drive_config_t* drive_config);
void icm42688_reg_get_drive_config(icm42688_reg_drive_config_t* drive_config);

#define __ICM42688_REG_GYRO_ACCEL_CONFIG0_DEFAULT_VALUE 0x11

#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_ODR_2 0x00
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_4 0x01
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_5 0x02
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_8 0x03
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_10 0x04
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_16 0x05
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_20 0x06
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_MAX_400HZ_ODR_40 0x07
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_LOW_LATENCY_ODR_DEC2 0x14
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_ACCEL_UI_FILT_BW_LOW_LATENCY_ODR_DEC2_8 0x15

#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_ODR_2 0x00
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_4 0x01
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_5 0x02
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_8 0x03
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_10 0x04
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_16 0x05
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_20 0x06
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_MAX_400HZ_ODR_40 0x07
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_LOW_LATENCY_ODR_DEC2 0x14
#define ICM42688_REG_GYRO_ACCEL_CONFIG0_GYRO_UI_FILT_BW_LOW_LATENCY_ODR_DEC2_8 0x15

typedef struct {
    // Bandwidth for Accel LPF
    // 0x00: BW=ODR/2 in LN mode
    // 0x01: BW=max(400Hz, ODR)/4 in LN mode, 1x AVG filter in LP mode (default)
    // 0x02: BW=max(400Hz, ODR)/5 in LN mode
    // 0x03: BW=max(400Hz, ODR)/8 in LN mode
    // 0x04: BW=max(400Hz, ODR)/10 in LN mode
    // 0x05: BW=max(400Hz, ODR)/16 in LN mode
    // 0x06: BW=max(400Hz, ODR)/20 in LN mode, 16x AVG filter in LP mode
    // 0x07: BW=max(400Hz, ODR)/40 in LN mode
    // 0x14: Low Latency option: Trivial decimation @ ODR of Dec2 filter output. Dec2 runs at max(400Hz, ODR) in LN mode
    // 0x15: Low Latency option: Trivial decimation @ ODR of Dec2 filter output. Dec2 runs at max(400Hz, 8*ODR) in LN mode
    uint8_t accel_ui_filt_bw;
    // Bandwidth for Gyro LPF
    // 0x00: BW=ODR/2 in LN mode
    // 0x01: BW=max(400Hz, ODR)/4 in LN mode
    // 0x02: BW=max(400Hz, ODR)/5 in LN mode
    // 0x03: BW=max(400Hz, ODR)/8 in LN mode
    // 0x04: BW=max(400Hz, ODR)/10 in LN mode
    // 0x05: BW=max(400Hz, ODR)/16 in LN mode
    // 0x06: BW=max(400Hz, ODR)/20 in LN mode
    // 0x07: BW=max(400Hz, ODR)/40 in LN mode
    // 0x14: Low Latency option: Trivial decimation @ ODR of Dec2 filter output. Dec2 runs at max(400Hz, ODR) in LN mode
    // 0x15: Low Latency option: Trivial decimation @ ODR of Dec2 filter output. Dec2 runs at max(400Hz, 8*ODR) in LN mode
    uint8_t gyro_ui_filt_bw;
} icm42688_reg_gyro_accel_config0_t;

icm42688_reg_gyro_accel_config0_t icm42688_reg_new_gyro_accel_config0(void);
void icm42688_reg_set_gyro_accel_config0(icm42688_reg_gyro_accel_config0_t* gyro_accel_config0);
void icm42688_reg_get_gyro_accel_config0(icm42688_reg_gyro_accel_config0_t* gyro_accel_config0);

typedef struct {
    // Lower byte of Gyro X-axis data
    uint8_t gyro_data_x_l;
    // Upper byte of Gyro X-axis data
    uint8_t gyro_data_x_h;
} icm42688_reg_gyro_data_x_t;

void icm42688_reg_get_gyro_data_x(icm42688_reg_gyro_data_x_t* gyro_data_x);

typedef struct {
    // Lower byte of Gyro Y-axis data
    uint8_t gyro_data_y_l;
    // Upper byte of Gyro Y-axis data
    uint8_t gyro_data_y_h;
} icm42688_reg_gyro_data_y_t;

void icm42688_reg_get_gyro_data_y(icm42688_reg_gyro_data_y_t* gyro_data_y);

typedef struct {
    // Lower byte of Gyro Z-axis data
    uint8_t gyro_data_z_l;
    // Upper byte of Gyro Z-axis data
    uint8_t gyro_data_z_h;
} icm42688_reg_gyro_data_z_t;

void icm42688_reg_get_gyro_data_z(icm42688_reg_gyro_data_z_t* gyro_data_z);

#define __ICM42688_REG_INT_CONFIG1_DEFAULT_VALUE 0x10

#define ICM42688_REG_INT_CONFIG1_INT_TPULSE_DURATION_100US 0x00
#define ICM42688_REG_INT_CONFIG1_INT_TPULSE_DURATION_8US 0x01

#define ICM42688_REG_INT_CONFIG1_INT_TDEASSERT_DISABLE_MINIMUM 0x00
#define ICM42688_REG_INT_CONFIG1_INT_TDEASSERT_DISABLE_DISABLED 0x01

#define ICM42688_REG_INT_CONFIG1_INT_ASYNC_RESET_ENABLED 0x00
#define ICM42688_REG_INT_CONFIG1_INT_ASYNC_RESET_DISABLED 0x01

typedef struct {
    // Interrupt pulse duration
    // 0x00: Interrupt pulse duration is 100μs. Use only if ODR < 4kHz (Default)
    // 0x01: Interrupt pulse duration is 8 μs. Required if ODR ≥ 4kHz, optional for ODR < 4kHz
    uint8_t int_tpulse_duration;
    // Interrupt de-assertion duration
    // 0x00: The interrupt de-assertion duration is set to a minimum of 100μs. Use only if ODR < 4kHz (Default)
    // 0x01: Disables de-assert duration. Required if ODR ≥ 4kHz, optional for ODR < 4kHz.
    uint8_t int_tdeassert_disable;
    // User should change setting to 0 from default setting of 1, for proper INT1 and INT2 pin operation
    // 0x00: Enable asynchronous reset
    // 0x01: Disable asynchronous reset (Default)
    uint8_t int_async_reset;
} icm42688_reg_int_config1_t;

icm42688_reg_int_config1_t icm42688_reg_new_int_config1(void);
void icm42688_reg_set_int_config1(icm42688_reg_int_config1_t* int_config1);
void icm42688_reg_get_int_config1(icm42688_reg_int_config1_t* int_config1);

#define __ICM42688_REG_INT_CONFIG_DEFAULT_VALUE 0x00

#define ICM42688_REG_INT_CONFIG_INT2_MODE_PULSED 0x00
#define ICM42688_REG_INT_CONFIG_INT2_MODE_LATCHED 0x01

#define ICM42688_REG_INT_CONFIG_INT2_DRIVE_CIRCUIT_OPEN_DRAIN 0x00
#define ICM42688_REG_INT_CONFIG_INT2_DRIVE_CIRCUIT_PUSH_PULL 0x01

#define ICM42688_REG_INT_CONFIG_INT2_POLARITY_ACTIVE_LOW 0x00
#define ICM42688_REG_INT_CONFIG_INT2_POLARITY_ACTIVE_HIGH 0x01

#define ICM42688_REG_INT_CONFIG_INT1_MODE_PULSED 0x00
#define ICM42688_REG_INT_CONFIG_INT1_MODE_LATCHED 0x02

#define ICM42688_REG_INT_CONFIG_INT1_DRIVE_CIRCUIT_OPEN_DRAIN 0x00
#define ICM42688_REG_INT_CONFIG_INT1_DRIVE_CIRCUIT_PUSH_PULL 0x02

#define ICM42688_REG_INT_CONFIG_INT1_POLARITY_ACTIVE_LOW 0x00
#define ICM42688_REG_INT_CONFIG_INT1_POLARITY_ACTIVE_HIGH 0x02

typedef struct {
    // INT2 interrupt mode
    // 0x00: Pulsed mode (default)
    // 0x01: Latched mode
    uint8_t int2_mode;
    // INT2 drive circuit
    // 0x00: Open-drain (default)
    // 0x01: Push-pull
    uint8_t int2_drive_circuit;
    // INT2 interrupt polarity
    // 0x00: Active-low (default)
    // 0x01: Active-high
    uint8_t int2_polarity;
    // INT1 interrupt mode
    // 0x00: Pulsed mode (default)
    // 0x02: Latched mode
    uint8_t int1_mode;
    // INT1 drive circuit
    // 0x00: Open-drain (default)
    // 0x02: Push-pull
    uint8_t int1_drive_circuit;
    // INT1 interrupt polarity
    // 0x00: Active-low (default)
    // 0x02: Active-high
    uint8_t int1_polarity;
} icm42688_reg_int_config_t;

icm42688_reg_int_config_t icm42688_reg_new_int_config(void);
void icm42688_reg_set_int_config(icm42688_reg_int_config_t* int_config);
void icm42688_reg_get_int_config(icm42688_reg_int_config_t* int_config);

#define __ICM42688_REG_INTF_CONFIG1_DEFAULT_VALUE 0x91

#define ICM42688_REG_INTF_CONFIG1_ACCEL_LP_CLK_SEL_WAKEUP_OSC 0x00
#define ICM42688_REG_INTF_CONFIG1_ACCEL_LP_CLK_SEL_RC_OSC 0x01

#define ICM42688_REG_INTF_CONFIG1_RTC_MODE_DISABLED 0x00
#define ICMS42688_REG_INTF_CONFIG1_RTC_MODE_ENABLED 0x01

#define ICM42688_REG_INTF_CONFIG1_CLKSEL_ALWAYS_RC 0x00
#define ICM42688_REG_INTF_CONFIG1_CLKSEL_PLL_OR_RC 0x01
#define ICM42688_REG_INTF_CONFIG1_CLKSEL_DISABLE_ALL 0x03

typedef struct {
    // Selects the clock source for the accelerometer low power mode
    // 0x00: Accelerometer LP mode uses Wake Up oscillator clock (default)
    // 0x01: Accelerometer LP mode uses RC oscillator clock
    uint8_t accel_lp_clk_sel;
    // RTC mode enable
    // 0x00: No input RTC clock is required (default)
    // 0x01: RTC clock input is required
    uint8_t rtc_mode;
    // Clock source selection
    // 0x00: Always select internal RC oscillator
    // 0x01: Select PLL when available, else select RC oscillator (default)
    // 0x03: Disable all clocks
    uint8_t clksel;
} icm42688_reg_intf_config1_t;

icm42688_reg_intf_config1_t icm42688_reg_new_intf_config1(void);
void icm42688_reg_set_intf_config1(icm42688_reg_intf_config1_t* intf_config1);
void icm42688_reg_get_intf_config1(icm42688_reg_intf_config1_t* intf_config1);

#define __ICM42688_REG_INT_SOURCE0_DEFAULT_VALUE 0x10

#define ICM42688_REG_INT_SOURCE0_UI_FSYNC_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_UI_FSYNC_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_PLL_RDY_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_PLL_RDY_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_RESET_DONE_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_RESET_DONE_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_UI_DRDY_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_UI_DRDY_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_FIFO_THS_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_FIFO_THS_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_FIFO_FULL_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_FIFO_FULL_INT1_EN_ENABLED 0x01

#define ICM42688_REG_INT_SOURCE0_UI_AGC_RDY_INT1_EN_DISABLED 0x00
#define ICM42688_REG_INT_SOURCE0_UI_AGC_RDY_INT1_EN_ENABLED 0x01

typedef struct {
    // Routing of the UI FSYNC interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t ui_fsync_int1_en;
    // Routing of the PLL ready interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t pll_rdy_int1_en;
    // Routing of the reset done interrupt to INT1
    // 0x00: Disabled
    // 0x01: Enabled (default)
    uint8_t reset_done_int1_en;
    // Routing of the UI DRDY interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t ui_drdy_int1_en;
    // Routing of the FIFO threshold interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t fifo_ths_int1_en;
    // Routing of the FIFO full interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t fifo_full_int1_en;
    // Routing of the UI AGC ready interrupt to INT1
    // 0x00: Disabled (default)
    // 0x01: Enabled
    uint8_t ui_agc_rdy_int1_en;
} icm42688_reg_int_source0_t;

icm42688_reg_int_source0_t icm42688_reg_new_int_source0(void);
void icm42688_reg_set_int_source0(icm42688_reg_int_source0_t* int_source0);
void icm42688_reg_get_int_source0(icm42688_reg_int_source0_t* int_source0);

typedef struct {
    // This bit automatically sets to 1 when a UI FSYNC interrupt is generated
    // The bit clears to 0 after the register has been read
    uint8_t ui_fsync_int;
    // This bit automatically sets to 1 when a PLL Ready interrupt is generated
    // The bit clears to 0 after the register has been read
    uint8_t pll_rdy_int;
    // This bit automatically sets to 1 when software reset is complete
    // The bit clears to 0 after the register has been read
    uint8_t reset_done_int;
    // This bit automatically sets to 1 when a Data Ready interrupt is generated
    // The bit clears to 0 after the register has been read
    uint8_t data_rdy_int;
    // This bit automatically sets to 1 when the FIFO buffer reaches the threshold
    // The bit clears to 0 after the register has been read
    uint8_t fifo_ths_int;
    // This bit automatically sets to 1 when the FIFO buffer is full
    // The bit clears to 0 after the register has been read
    uint8_t fifo_full_int;
    // This bit automatically sets to 1 when an AGC Ready interrupt is generated
    // The bit clears to 0 after the register has been read
    uint8_t agc_rdy_int;
} icm42688_reg_int_status_t;

void icm42688_reg_get_int_status(icm42688_reg_int_status_t* int_status);

#define __ICM42688_REG_PWR_MGMT0_DEFAULT_VALUE 0x00

#define ICM42688_REG_PWR_MGMT0_TEMP_DIS_ENABLED 0x00
#define ICM42688_REG_PWR_MGMT0_TEMP_DIS_DISABLED 0x01

#define ICM42688_REG_PWR_MGMT0_IDLE_ENABLED 0x00
#define ICM42688_REG_PWR_MGMT0_IDLE_DISABLED 0x01

#define ICM42688_REG_PWR_MGMT0_GYRO_MODE_OFF 0x00
#define ICM42688_REG_PWR_MGMT0_GYRO_MODE_STANDBY 0x01
#define ICM42688_REG_PWR_MGMT0_GYRO_MODE_LOW_NOISE 0x03

#define ICM42688_REG_PWR_MGMT0_ACCEL_MODE_OFF 0x00
#define ICM42688_REG_PWR_MGMT0_ACCEL_MODE_LOW_POWER 0x02
#define ICM42688_REG_PWR_MGMT0_ACCEL_MODE_LOW_NOISE 0x03

typedef struct {
    // Temperature sensor enable / disable
    // 0x00: Temperature sensor is enabled (default)
    // 0x01: Temperature sensor is disabled
    uint8_t temp_dis;
    // 0x00: the RC oscillator is powered on even if Accel and Gyro are powered off (default)
    // 0x01: when Accel and Gyro are powered off, the chip will go to OFF state, since the RC oscillator will also be powered off
    uint8_t idle;
    // Gyroscope needs to be kept ON for a minimum of 45ms. When transitioning from OFF to any of the other modes, do not issue any register writes for 200μs
    // 0x00: Turns gyroscope off (default)
    // 0x01: Places gyroscope in Standby Mode
    // 0x03: Places gyroscope in Low Noise Mode
    uint8_t gyro_mode;
    // When transitioning from OFF to any of the other modes, do not issue any register writes for 200μs
    // 0x00: Turns accelerometer off (default)
    // 0x01: Turns accelerometer off
    // 0x02: Places accelerometer in Low Power (LP) Mode
    // 0x03: Places accelerometer in Low Noise (LN) Mode
    uint8_t accel_mode;
} icm42688_reg_pwr_mgmt0_t;

icm42688_reg_pwr_mgmt0_t icm42688_reg_new_pwr_mgmt0(void);
void icm42688_reg_set_pwr_mgmt0(icm42688_reg_pwr_mgmt0_t* pwr_mgmt0);
void icm42688_reg_get_pwr_mgmt0(icm42688_reg_pwr_mgmt0_t* pwr_mgmt0);

typedef struct {
    // Lower byte of temperature data
    uint8_t temp_data_l;
    // Upper byte of temperature data
    uint8_t temp_data_h;
} icm42688_reg_temp_data_t;

void icm42688_reg_get_temp_data(icm42688_reg_temp_data_t* temp_data);

typedef struct {
    // Device ID, read-only
    // 0x47: ICM-42688
    uint8_t dev_id;
} icm42688_reg_who_am_i_t;

void icm42688_reg_get_who_am_i(icm42688_reg_who_am_i_t* who_am_i);
