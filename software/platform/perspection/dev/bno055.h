#ifndef BNO055_H_
#define BNO055_H_

#include <stdbool.h>
#include <stdint.h>

#define BNO055_ADDR 0x28
#define BNO055_ID 0xA0

/* Page id register definition */
#define BNO055_PAGE_ID_ADDR                   0X07

/* PAGE0 REGISTER DEFINITION START*/
#define BNO055_CHIP_ID_ADDR                   0x00
#define BNO055_ACCEL_REV_ID_ADDR              0x01
#define BNO055_MAG_REV_ID_ADDR                0x02
#define BNO055_GYRO_REV_ID_ADDR               0x03
#define BNO055_SW_REV_ID_LSB_ADDR             0x04
#define BNO055_SW_REV_ID_MSB_ADDR             0x05
#define BNO055_BL_REV_ID_ADDR                 0X06

/* Accel data register */
#define BNO055_ACCEL_DATA_X_LSB_ADDR          0X08
#define BNO055_ACCEL_DATA_X_MSB_ADDR          0X09
#define BNO055_ACCEL_DATA_Y_LSB_ADDR          0X0A
#define BNO055_ACCEL_DATA_Y_MSB_ADDR          0X0B
#define BNO055_ACCEL_DATA_Z_LSB_ADDR          0X0C
#define BNO055_ACCEL_DATA_Z_MSB_ADDR          0X0D

/* Mag data register */
#define BNO055_MAG_DATA_X_LSB_ADDR            0X0E
#define BNO055_MAG_DATA_X_MSB_ADDR            0X0F
#define BNO055_MAG_DATA_Y_LSB_ADDR            0X10
#define BNO055_MAG_DATA_Y_MSB_ADDR            0X11
#define BNO055_MAG_DATA_Z_LSB_ADDR            0X12
#define BNO055_MAG_DATA_Z_MSB_ADDR            0X13

/* Gyro data registers */
#define BNO055_GYRO_DATA_X_LSB_ADDR           0X14
#define BNO055_GYRO_DATA_X_MSB_ADDR           0X15
#define BNO055_GYRO_DATA_Y_LSB_ADDR           0X16
#define BNO055_GYRO_DATA_Y_MSB_ADDR           0X17
#define BNO055_GYRO_DATA_Z_LSB_ADDR           0X18
#define BNO055_GYRO_DATA_Z_MSB_ADDR           0X19

/* Euler data registers */
#define BNO055_EULER_H_LSB_ADDR               0X1A
#define BNO055_EULER_H_MSB_ADDR               0X1B
#define BNO055_EULER_R_LSB_ADDR               0X1C
#define BNO055_EULER_R_MSB_ADDR               0X1D
#define BNO055_EULER_P_LSB_ADDR               0X1E
#define BNO055_EULER_P_MSB_ADDR               0X1F

/* Quaternion data registers */
#define BNO055_QUATERNION_DATA_W_LSB_ADDR     0X20
#define BNO055_QUATERNION_DATA_W_MSB_ADDR     0X21
#define BNO055_QUATERNION_DATA_X_LSB_ADDR     0X22
#define BNO055_QUATERNION_DATA_X_MSB_ADDR     0X23
#define BNO055_QUATERNION_DATA_Y_LSB_ADDR     0X24
#define BNO055_QUATERNION_DATA_Y_MSB_ADDR     0X25
#define BNO055_QUATERNION_DATA_Z_LSB_ADDR     0X26
#define BNO055_QUATERNION_DATA_Z_MSB_ADDR     0X27

/* Linear acceleration data registers */
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR   0X28
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR   0X29
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR   0X2A
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR   0X2B
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR   0X2C
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR   0X2D

/* Gravity data registers */
#define BNO055_GRAVITY_DATA_X_LSB_ADDR        0X2E
#define BNO055_GRAVITY_DATA_X_MSB_ADDR        0X2F
#define BNO055_GRAVITY_DATA_Y_LSB_ADDR        0X30
#define BNO055_GRAVITY_DATA_Y_MSB_ADDR        0X31
#define BNO055_GRAVITY_DATA_Z_LSB_ADDR        0X32
#define BNO055_GRAVITY_DATA_Z_MSB_ADDR        0X33

/* Temperature data register */
#define BNO055_TEMP_ADDR                      0X34

/* Status registers */
#define BNO055_CALIB_STAT_ADDR                0X35
#define BNO055_SELFTEST_RESULT_ADDR           0X36
#define BNO055_INTR_STAT_ADDR                 0X37

#define BNO055_SYS_CLK_STAT_ADDR              0X38
#define BNO055_SYS_STAT_ADDR                  0X39
#define BNO055_SYS_ERR_ADDR                   0X3A

/* Unit selection register */
#define BNO055_UNIT_SEL_ADDR                  0X3B
#define BNO055_DATA_SELECT_ADDR               0X3C

/* Mode registers */
#define BNO055_OPR_MODE_ADDR                  0X3D
#define BNO055_PWR_MODE_ADDR                  0X3E

#define BNO055_SYS_TRIGGER_ADDR               0X3F
#define BNO055_TEMP_SOURCE_ADDR               0X40

/* Axis remap registers */
#define BNO055_AXIS_MAP_CONFIG_ADDR           0X41
#define BNO055_AXIS_MAP_SIGN_ADDR             0X42

/* SIC registers */
#define BNO055_SIC_MATRIX_0_LSB_ADDR          0X43
#define BNO055_SIC_MATRIX_0_MSB_ADDR          0X44
#define BNO055_SIC_MATRIX_1_LSB_ADDR          0X45
#define BNO055_SIC_MATRIX_1_MSB_ADDR          0X46
#define BNO055_SIC_MATRIX_2_LSB_ADDR          0X47
#define BNO055_SIC_MATRIX_2_MSB_ADDR          0X48
#define BNO055_SIC_MATRIX_3_LSB_ADDR          0X49
#define BNO055_SIC_MATRIX_3_MSB_ADDR          0X4A
#define BNO055_SIC_MATRIX_4_LSB_ADDR          0X4B
#define BNO055_SIC_MATRIX_4_MSB_ADDR          0X4C
#define BNO055_SIC_MATRIX_5_LSB_ADDR          0X4D
#define BNO055_SIC_MATRIX_5_MSB_ADDR          0X4E
#define BNO055_SIC_MATRIX_6_LSB_ADDR          0X4F
#define BNO055_SIC_MATRIX_6_MSB_ADDR          0X50
#define BNO055_SIC_MATRIX_7_LSB_ADDR          0X51
#define BNO055_SIC_MATRIX_7_MSB_ADDR          0X52
#define BNO055_SIC_MATRIX_8_LSB_ADDR          0X53
#define BNO055_SIC_MATRIX_8_MSB_ADDR          0X54

/* Accelerometer Offset registers */
#define BNO055_ACCEL_OFFSET_X_LSB_ADDR        0X55
#define BNO055_ACCEL_OFFSET_X_MSB_ADDR        0X56
#define BNO055_ACCEL_OFFSET_Y_LSB_ADDR        0X57
#define BNO055_ACCEL_OFFSET_Y_MSB_ADDR        0X58
#define BNO055_ACCEL_OFFSET_Z_LSB_ADDR        0X59
#define BNO055_ACCEL_OFFSET_Z_MSB_ADDR        0X5A

/* Magnetometer Offset registers */
#define BNO055_MAG_OFFSET_X_LSB_ADDR          0X5B
#define BNO055_MAG_OFFSET_X_MSB_ADDR          0X5C
#define BNO055_MAG_OFFSET_Y_LSB_ADDR          0X5D
#define BNO055_MAG_OFFSET_Y_MSB_ADDR          0X5E
#define BNO055_MAG_OFFSET_Z_LSB_ADDR          0X5F
#define BNO055_MAG_OFFSET_Z_MSB_ADDR          0X60

/* Gyroscope Offset register s*/
#define BNO055_GYRO_OFFSET_X_LSB_ADDR         0X61
#define BNO055_GYRO_OFFSET_X_MSB_ADDR         0X62
#define BNO055_GYRO_OFFSET_Y_LSB_ADDR         0X63
#define BNO055_GYRO_OFFSET_Y_MSB_ADDR         0X64
#define BNO055_GYRO_OFFSET_Z_LSB_ADDR         0X65
#define BNO055_GYRO_OFFSET_Z_MSB_ADDR         0X66

/* Radius registers */
#define BNO055_ACCEL_RADIUS_LSB_ADDR          0X67
#define BNO055_ACCEL_RADIUS_MSB_ADDR          0X68
#define BNO055_MAG_RADIUS_LSB_ADDR            0X69
#define BNO055_MAG_RADIUS_MSB_ADDR            0X6A

/* Unit Selection */
#define BNO055_UNITS_ACC_MS2        (0<<0)
#define BNO055_UNITS_ACC_MG         (1<<0)
#define BNO055_UNITS_ANG_RATE_DPS   (0<<1)
#define BNO055_UNITS_ANG_RATE_RPS   (1<<1)
#define BNO055_UNITS_ANG_DEG        (0<<2)
#define BNO055_UNITS_ANG_RAD        (1<<2)
#define BNO055_UNITS_TEMP_C         (0<<4)
#define BNO055_UNITS_TEMP_F         (1<<4)

typedef enum {
  /* Operation mode settings*/
  BNO055_OPERATION_MODE_CONFIG        = 0X00,
  BNO055_OPERATION_MODE_ACCONLY       = 0X01,
  BNO055_OPERATION_MODE_MAGONLY       = 0X02,
  BNO055_OPERATION_MODE_GYRONLY       = 0X03,
  BNO055_OPERATION_MODE_ACCMAG        = 0X04,
  BNO055_OPERATION_MODE_ACCGYRO       = 0X05,
  BNO055_OPERATION_MODE_MAGGYRO       = 0X06,
  BNO055_OPERATION_MODE_AMG           = 0X07,
  BNO055_OPERATION_MODE_IMUPLUS       = 0X08,
  BNO055_OPERATION_MODE_COMPASS       = 0X09,
  BNO055_OPERATION_MODE_M4G           = 0X0A,
  BNO055_OPERATION_MODE_NDOF_FMC_OFF  = 0X0B,
  BNO055_OPERATION_MODE_NDOF          = 0X0C
} bno055_opmode_t;

//typedef enum {
//  BNO055_SYSTEM_STATUS_IDLE                    = 0x00,
//  BNO055_SYSTEM_STATUS_ERROR                   = 0x01,
//  BNO055_SYSTEM_STATUS_INITIALIZING_PARAMETERS = 0x02,
//  BNO055_SYSTEM_STATUS_SYSTEM_INITIALIZATION   = 0x03,
//  BNO055_SYSTEM_STATUS_EXECUTING_SELFTEST      = 0x04,
//  BNO055_SYSTEM_STATUS_SENSOR_FUSION_RUNNING   = 0x05,
//  BNO055_SYSTEM_STATUS_RUNNING_NO_FUSION       = 0x06
//} bno055_system_status_t;

typedef enum {
  BNO055_POWER_MODE_NORMAL            = 0X00,
  BNO055_POWER_MODE_LOWPOWER          = 0X01,
  BNO055_POWER_MODE_SUSPEND           = 0X02
} bno055_powermode_t;

typedef enum {
  BNO055_ACC_VECTOR   = BNO055_ACCEL_DATA_X_LSB_ADDR,
  BNO055_MAG_VECTOR   = BNO055_MAG_DATA_X_LSB_ADDR,
  BNO055_GYRO_VECTOR  = BNO055_GYRO_DATA_X_LSB_ADDR,
  BNO055_EULER_VECTOR = BNO055_EULER_H_LSB_ADDR,
  BNO055_LIA_VECTOR   = BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR,
  BNO055_GRAV_VECTOR  = BNO055_GRAVITY_DATA_X_LSB_ADDR
} bno055_vector_type_t;

#define BNO055_SYSTEM_CAL_MASK (0x3 << 6)
#define BNO055_GYRO_CAL_MASK (0x3 << 4)
#define BNO055_ACCEL_CAL_MASK (0x3 << 2)
#define BNO055_MAG_CAL_MASK (0x3 << 0)

typedef struct {
  bool system_cal;
  bool gyro_cal;
  bool accel_cal;
  bool mag_cal;
} bno055_calibration_t;

typedef struct {
  int16_t x;
  int16_t y;
  int16_t z;
} bno055_vector_t;

typedef struct {
  int16_t w;
  int16_t x;
  int16_t y;
  int16_t z;
} bno055_quat_t;

typedef struct
{
  uint16_t accel_offset_x;
  uint16_t accel_offset_y;
  uint16_t accel_offset_z;
  uint16_t gyro_offset_x;
  uint16_t gyro_offset_y;
  uint16_t gyro_offset_z;
  uint16_t mag_offset_x;
  uint16_t mag_offset_y;
  uint16_t mag_offset_z;

  uint16_t accel_radius;
  uint16_t mag_radius;
} bno055_offsets_t;
  
#define BNO055_XAXIS 0
#define BNO055_YAXIS 1
#define BNO055_ZAXIS 2
#define BNO055_POSITIVE 0
#define BNO055_NEGATIVE 1

bool bno055_init(void);
void bno055_set_mode(bno055_opmode_t mode);
void bno055_set_xtal(bool use_xtal);
void bno055_set_units(uint8_t units);
uint8_t bno055_get_id();
uint8_t bno055_get_status(void);
uint8_t bno055_get_error(void);
uint8_t bno055_get_selftest_result(void);
bno055_calibration_t bno055_get_calibration(void);
bool bno055_is_calibrated(void);
bno055_vector_t bno055_get_vector(bno055_vector_type_t type);
bno055_quat_t bno055_get_quat(void);
int8_t bno055_get_temp(void);
bno055_offsets_t bno055_get_sensor_offsets(void);
void bno055_set_sensor_offsets(bno055_offsets_t offsets);
uint8_t bno055_read8(uint8_t reg);
void bno055_write8(uint8_t reg, uint8_t val);
//set_axis_mapping(remapped x, remapped y, remapped z)
void bno055_set_axis_map_config(uint8_t x, uint8_t y, uint8_t z);
void bno055_set_axis_map_sign(bool x, bool y, bool z);

#endif
