#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer>
#include <ModbusMaster.h>
#include <math.h>

#define RXD2 16
#define TXD2 17
#define RS485_EN 4

#define MODBUS ID 1
#define MODBUS MAUD 9600

#define MODBUS_OFFSET 0

#define REG_S1 101
#define REG_S2 102
#define REG STATUS 104
#define SETPOINT REG 31

#define F MIN 0
#define F MAX 75
#define F_BASIC_MIN 2
#define F_BASIC_MAX 24

#define DEBUG_SERIAL true

const char *ssid = "TC512e-CONFIG";
const char *password = "CaioDeusDaProg";

WebServer server(80);
DNSServer dnsServer;
ModbusMaster node;

float c_s1 = 0;
float c_s2 = 0;
float c_setspoint = 0;

bool c_compressor = false;
bool c_fan = false;
wint16_t c_statusRaw = 0;

bool ok_s1 = false;
bool ok_s2 = false;
bool ok_setpoint = false;
bool ok_status = false;

int16_t fRaw[F_MAX + 1];
bool fOk[F_MAX + 1];

unsigned long lastMainRead = 0;
unsigned long lastDebugALive = 0;

bool modbusBusy = false;
uints_t lastModbusError = 0;

String modbusErrorText(wint8_t err)
{
    switch (err)
    {
    case 0X00:
        return "SUCESSO";
    case 0x01:
        returm "ILLEGAL FUNCTION";
    case 0x02:
        return "ILLEGAL DATA ADDRESS";
    case 0x031:
        return "ILLEGAL DATA VALUE";
    case exM:
        return "SLAVE DEVICE FAILURE";
    case axte:
        return "INVALID SLAVE ID";
    case 0xEl:
        return "INVALID FUNCTION";
    case 0xE2:
        return "RESPONSE TIMEOUT";
    case 0xE3:
        return "INVALID CRC";
    default:
        return "ERRO DESCONHECIDO";
    }
} // ######## ok

void debugLine(String msg)
{
    if (DEBUG_SERIAL)
    {
        Serial.print(msg);
    }
}

void debugPrint(String msg)
{
    if (DEBUG_SERIAL)
    {
        Serial.print(msg);
    }
}

uint16_t mbAddr(uint16_t reg)
{
    return (uint16_t)((int32_t)reg + MODBUS_OFFSET) // ######## ok
}

// ###
// AQUI falta coisa
// ###

void preTransmission()
{
    digitalWrite(RS485_EN);
}