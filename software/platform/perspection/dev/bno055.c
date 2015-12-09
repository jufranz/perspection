#include "bno055.h"
#include "i2c.h"
#include "clock.h"


#ifdef BNO055_DELAY
#define delay(x) clock_delay_usec(1000*x)
#else
#define delay(x)
#endif


uint8_t bno055_read8(uint8_t reg) {
  i2c_single_send(BNO055_ADDR, reg);
  static uint8_t recv_buf;
  i2c_single_receive(BNO055_ADDR, &recv_buf);
  return recv_buf;
}

void bno055_write8(uint8_t reg, uint8_t val) {
  static uint8_t send_buf[2];
  send_buf[0] = reg;
  send_buf[1] = val;
  i2c_burst_send(BNO055_ADDR, send_buf, 2);
}

void read_len(uint8_t reg, uint8_t *buffer, uint8_t len)
{
  i2c_single_send(BNO055_ADDR, reg);
  i2c_burst_receive(BNO055_ADDR, buffer, len);
}

uint8_t bno055_get_id() {
  return bno055_read8(BNO055_CHIP_ID_ADDR);
}

bool bno055_init(void) {
  //intialize i2c (ports/pins usually found in board.h for platform)
  i2c_init(I2C_SDA_PORT, I2C_SDA_PIN, I2C_SCL_PORT, I2C_SCL_PIN, I2C_SCL_FAST_BUS_SPEED);
  /* Make sure we have the right device */
  bno055_write8(BNO055_PAGE_ID_ADDR, 0);
  uint8_t id = bno055_read8(BNO055_CHIP_ID_ADDR);
  if(id != BNO055_ID)
  {
    clock_delay_usec(0xFFFF); // hold on for boot
    id = bno055_read8(BNO055_CHIP_ID_ADDR);
    if(id != BNO055_ID) {
      return false;  // still not? ok bail
    }
  }

  /* Switch to config mode (just in case since this is the default) */
  bno055_set_mode(BNO055_OPERATION_MODE_CONFIG);

  /* Reset */
//  bno055_write8(BNO055_SYS_TRIGGER_ADDR, 0x20);
//  while (bno055_read8(BNO055_CHIP_ID_ADDR) != BNO055_ID)
//  {
//    clock_delay_usec(1000);
//  }
//  delay(50);

  /* Set to normal power mode */
  bno055_write8(BNO055_PWR_MODE_ADDR, BNO055_POWER_MODE_NORMAL);
  delay(10);

  bno055_write8(BNO055_PAGE_ID_ADDR, 0);
  bno055_write8(BNO055_SYS_TRIGGER_ADDR, 0x0);
  delay(10);

  return true;
}

static bno055_opmode_t _mode = BNO055_OPERATION_MODE_NDOF; //default val?
void bno055_set_mode(bno055_opmode_t mode) {
  _mode = mode;
  bno055_write8(BNO055_OPR_MODE_ADDR, mode);
  delay(30);
}

void bno055_set_xtal(bool use_xtal) {
  bno055_opmode_t modeback = _mode;
  /* Switch to config mode (just in case since this is the default) */
  bno055_set_mode(BNO055_OPERATION_MODE_CONFIG);
  delay(25);
  bno055_write8(BNO055_PAGE_ID_ADDR, 0);
  if (use_xtal) {
    bno055_write8(BNO055_SYS_TRIGGER_ADDR, 0x80);
  } else {
    bno055_write8(BNO055_SYS_TRIGGER_ADDR, 0x00);
  }
  delay(10);
  /* Set the requested operating mode (see section 3.3) */
  bno055_set_mode(modeback);
  delay(20);
}

void bno055_set_units(uint8_t units) {
  bno055_write8(BNO055_UNIT_SEL_ADDR, units);
}

uint8_t bno055_get_status(void) {
  //necessary???
  //bno055_write8(BNO055_PAGE_ID_ADDR, 0);
  return bno055_read8(BNO055_SYS_STAT_ADDR);
}

uint8_t bno055_get_selftest_result(void) {
    return bno055_read8(BNO055_SELFTEST_RESULT_ADDR);
}

uint8_t bno055_get_error(void) {
    return bno055_read8(BNO055_SYS_ERR_ADDR);
}

bno055_calibration_t bno055_get_calibration(void) {
  bno055_calibration_t result;
  uint8_t cal_data = bno055_read8(BNO055_CALIB_STAT_ADDR);
  result.system_cal = ((BNO055_SYSTEM_CAL_MASK & cal_data) == BNO055_SYSTEM_CAL_MASK);
  result.gyro_cal = ((BNO055_GYRO_CAL_MASK & cal_data) == BNO055_GYRO_CAL_MASK);
  result.accel_cal = ((BNO055_ACCEL_CAL_MASK & cal_data) == BNO055_ACCEL_CAL_MASK);
  result.mag_cal = ((BNO055_MAG_CAL_MASK & cal_data) == BNO055_MAG_CAL_MASK);
  return result;
}
  
bool bno055_is_calibrated(void) {
  bno055_calibration_t result = bno055_get_calibration();
  return (result.system_cal &&
          result.gyro_cal &&
          result.accel_cal &&
          result.mag_cal);
}
bno055_vector_t bno055_get_vector(bno055_vector_type_t type) {
  bno055_vector_t result;
  uint8_t buffer[6];
  uint8_t i;
  for(i = 0; i < 6; i++) buffer[i] = 0;
  result.x = 0;
  result.y = 0;
  result.z = 0;

  /* Read vector data (6 bytes) */
  read_len(type, buffer, 6);

  result.z = ((int16_t)buffer[0]) | (((int16_t)buffer[1]) << 8);
  result.x = ((int16_t)buffer[2]) | (((int16_t)buffer[3]) << 8);
  result.y = ((int16_t)buffer[4]) | (((int16_t)buffer[5]) << 8);
  return result;
}

bno055_quat_t bno055_get_quat(void) {
  bno055_quat_t result;
  uint8_t buffer[8];
  uint8_t i;
  for(i = 0; i < 8; i++) buffer[i] = 0;
  result.w = 0;
  result.x = 0;
  result.y = 0;
  result.z = 0;

  /* Read vector data (6 bytes) */
  read_len(BNO055_QUATERNION_DATA_W_LSB_ADDR, buffer, 8);

  result.w = ((int16_t)buffer[0]) | (((int16_t)buffer[1]) << 8);
  result.x = ((int16_t)buffer[2]) | (((int16_t)buffer[3]) << 8);
  result.y = ((int16_t)buffer[4]) | (((int16_t)buffer[5]) << 8);
  result.z = ((int16_t)buffer[6]) | (((int16_t)buffer[7]) << 8);
  return result;
}

int8_t bno055_get_temp(void) {
    return (int8_t)(bno055_read8(BNO055_TEMP_ADDR));
}

bno055_offsets_t bno055_get_sensor_offsets(void) {
  bno055_offsets_t result;
  result.accel_offset_x = 0;
  result.accel_offset_y = 0;
  result.accel_offset_z = 0;
  result.gyro_offset_x = 0;
  result.gyro_offset_y = 0;
  result.gyro_offset_z = 0;
  result.mag_offset_x = 0;
  result.mag_offset_y = 0;
  result.mag_offset_z = 0;
  result.accel_radius = 0;
  result.mag_radius = 0;
  //XXX TODO
  return result;
}

void bno055_set_sensor_offsets(bno055_offsets_t offsets) {
  //XXX TODO
}

void bno055_set_axis_map_config(uint8_t x, uint8_t y, uint8_t z){
  uint8_t val = 0;
  val |= (z & 0x03) << 4;
  val |= (y & 0x03) << 2;
  val |= (x & 0x03);

  bno055_write8(BNO055_AXIS_MAP_CONFIG_ADDR, val);
}

void bno055_set_axis_map_sign(bool x, bool y, bool z){
  uint8_t val = 0;
  val |= (uint8_t)x << 2;
  val |= (uint8_t)y << 1;
  val |= (uint8_t)z;
  
  bno055_write8(BNO055_AXIS_MAP_SIGN_ADDR, val);
}
