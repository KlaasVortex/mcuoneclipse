/*
 * SHT31.c
 *
 *  Created on: 08.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_SHT31_C_
#define SOURCES_SHT31_C_


#include "Platform.h"
#if PL_CONFIG_HAS_SHT31
#include "GI2C1.h"
#include "WAIT1.h"

#define SHT31_I2C_ADDR  (0x44) /* default I2C address with ADDR pin pulled LOW (default on Adafruit board) */
//#define SHT31_I2C_ADDR  (0x45) /* I2C address with ADDR pin pulled HIGH: pull ADR pin to VIN */

#define SHT31_DEFAULT_ADDR           0x44
#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10
#define SHT31_MEAS_HIGHREP         0x2400
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416
#define SHT31_READSTATUS           0xF32D
#define SHT31_CLEARSTATUS          0x3041
#define SHT31_SOFTRESET            0x30A2
#define SHT31_HEATEREN             0x306D
#define SHT31_HEATERDIS            0x3066

/* status bits of the Status register (0xF32D) */
#define SHT31_STATUS_ALERT_PENDING      (1<<15) /* 0: no pending alert, 1: at least one pending alert */
#define SHT31_STATUS_HEATER_ON          (1<<13) /* 0: heater OFF, 1: heater ON */
#define SHT31_STATUS_RH_TRACKING_ALERT  (1<<11) /* 0: no RH tracking alert, 1: alert */
#define SHT31_STATUS_T_TRACKING_ALERT   (1<<10) /* 0: no T tracking alert, 1: alert */
#define SHT31_STATUS_SYSTEM_RESET       (1<<4)  /* 0: no reset detected sincd last clear status register command, 1: reset detected (hard reset, soft reset or supply fail */
#define SHT31_STATUS_CMD_STATUS         (1<<1)  /* 0: last command executed successfully; 1: last command not processed, it was either invalid, failed the internal command checksum */
#define SHT31_STATUS_WRITE_CRC_STATUS   (1<<0)  /* 0: checksum of last write transfer was correct, 1: checksum of last write transfer failed */

#define SHT31_CRC8_POLYNOMIAL  0x31    /* Seed for CRC polynomial */
#define SHT31_CRC8_INIT        0xFF    /* Init value for CRC */

uint8_t SHT31_GenerateCRC(uint8_t *data, uint8_t datalen) {
  /* calculates 8-Bit checksum with given polynomial */
  uint8_t crc = SHT31_CRC8_INIT;
  uint8_t b;
  uint8_t i;

  for (i=0; i<datalen; i++) {
    crc ^= data[i];
    for (b=0; b<8; b++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ SHT31_CRC8_POLYNOMIAL;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

uint8_t SHT31_WriteCommand(uint16_t cmd) {
  uint8_t buf[2];

  buf[0] = cmd>>8;
  buf[1] = cmd&0xff;
  return GI2C1_WriteAddress(SHT31_I2C_ADDR, buf, sizeof(buf), NULL, 0);
}

uint8_t SHT31_ReadStatus(uint16_t *status) {
  uint8_t res;
  uint8_t cmd[2];
  uint8_t stat[3];
  uint8_t crc;

  cmd[0] = SHT31_READSTATUS>>8;
  cmd[1] = SHT31_READSTATUS&0xff;
  res = GI2C1_ReadAddress(SHT31_I2C_ADDR, cmd, sizeof(cmd), stat, sizeof(stat));
  if (res!=ERR_OK) {
    *status = 0;
    return res;
  }
  crc = SHT31_GenerateCRC(stat, 2);
  if (crc!=stat[2]) {
    return ERR_CRC; /* wrong CRC */
  }
  *status = (stat[0]<<8)+stat[1]; /* ignore CRC */
  return res;
}


uint8_t SHT31_Heater(bool on) {
  return SHT31_WriteCommand(on?SHT31_HEATEREN:SHT31_HEATERDIS);
}

uint8_t SHT31_Reset(void) {
  return SHT31_WriteCommand(SHT31_SOFTRESET);
}

#if 1
uint8_t SHT31_ReadTempHum(float *temperature, float *humidity) {
  double stemp, shum;
  uint16_t ST, SRH;
  uint8_t readbuffer[6];
  uint8_t i, res;
  uint8_t cmd[2];

  cmd[0] = SHT31_MEAS_HIGHREP>>8;
  cmd[1] = SHT31_MEAS_HIGHREP&0xff;
  res = GI2C1_ReadAddressWait(SHT31_I2C_ADDR, cmd, sizeof(cmd), 500, readbuffer, sizeof(readbuffer));
  if (res!=ERR_OK) {
    return res;
  }
  ST = (readbuffer[0]<<8)|readbuffer[1];
  if (readbuffer[2] != SHT31_GenerateCRC(readbuffer, 2)) {
    return ERR_CRC;
  }

  SRH = (readbuffer[3])|readbuffer[4];
  if (readbuffer[5] != SHT31_GenerateCRC(readbuffer+3, 2)) {
    return ERR_CRC;
  }

  stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;
  *temperature = stemp;

  shum = SRH;
  shum *= 100;
  shum /= 0xFFFF;
  *humidity = shum;

  return ERR_OK;
}
#endif

void SHT31_Init(void) {
  uint16_t status;
  uint8_t res;
  float temp, hum;

  res = SHT31_ReadStatus(&status);
  res = SHT31_ReadTempHum(&temp, &hum);
}

#endif /* PL_CONFIG_HAS_SHT31 */

#endif /* SOURCES_SHT31_C_ */
