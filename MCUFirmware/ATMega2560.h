/*
* ATMega2560.h
*
* Created: 27.08.2014 18:47:15
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#ifndef ATMEGA2560_H_
#define ATMEGA2560_H_

void InitializePWM(void);
void InitializeSerialPort(void);
inline unsigned char RecieveSerialByte(void);
inline void SendSerialByte(unsigned char data);

#define SERIAL_INTERRUPT USART0_RX_vect

// GPIO 52
#define LED1_DDR _SFR_IO8(0x04)
#define LED1_PORT _SFR_IO8(0x05)
#define LED1_PIN 1
// GPIO 53
#define LED2_DDR _SFR_IO8(0x04)
#define LED2_PORT _SFR_IO8(0x05)
#define LED2_PIN 0
// GPIO 50
#define LED3_DDR _SFR_IO8(0x04)
#define LED3_PORT _SFR_IO8(0x05)
#define LED3_PIN 3
// GPIO 51
#define LED4_DDR _SFR_IO8(0x04)
#define LED4_PORT _SFR_IO8(0x05)
#define LED4_PIN 2
// GPIO 48
#define LED5_DDR _SFR_MEM8(0x10A)
#define LED5_PORT _SFR_MEM8(0x10B)
#define LED5_PIN 1

// GPIO 38
#define SENSOR1_DDR _SFR_IO8(0x0A)
#define SENSOR1_PORT _SFR_IO8(0x09)
#define SENSOR1_PIN 7
// GPIO 39
#define SENSOR2_DDR _SFR_IO8(0x13)
#define SENSOR2_PORT _SFR_IO8(0x12)
#define SENSOR2_PIN 2
// GPIO 36
#define SENSOR3_DDR _SFR_IO8(0x07)
#define SENSOR3_PORT _SFR_IO8(0x06)
#define SENSOR3_PIN 1
// GPIO 37
#define SENSOR4_DDR _SFR_IO8(0x07)
#define SENSOR4_PORT _SFR_IO8(0x06)
#define SENSOR4_PIN 0
// GPIO 34
#define SENSOR5_DDR _SFR_IO8(0x07)
#define SENSOR5_PORT _SFR_IO8(0x06)
#define SENSOR5_PIN 3

// GPIO 1
#define RIGHT_MOTOR_DIRECTION_DDR DDRG
#define RIGHT_MOTOR_DIRECTION_PORT PORTG
#define RIGHT_MOTOR_DIRECTION_PIN PINE5
// GPIO 16
#define LEFT_MOTOR_DIRECTION_DDR DDRH
#define LEFT_MOTOR_DIRECTION_PORT PORTH
#define LEFT_MOTOR_DIRECTION_PIN PINH4
// GPIO 5
#define RIGHT_MOTOR_SPEED_DDR DDRE
#define RIGHT_MOTOR_SPEED_PORT PORTE
#define RIGHT_MOTOR_SPEED_PIN PINE3
// GPIO 15
#define LEFT_MOTOR_SPEED_DDR DDRH
#define LEFT_MOTOR_SPEED_PORT PORTH
#define LEFT_MOTOR_SPEED_PIN PINH3
// -------
#define RIGHT_MOTOR_SPEED_VALUE OCR3A
#define LEFT_MOTOR_SPEED_VALUE OCR4A

void InitializePWM(void)
{
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);
    TCCR3A &= ~(1 << WGM31);
    TCCR3A |= (1 << WGM30);
    TCCR3B &= ~(1 << WGM33);
    TCCR3B &= ~(1 << WGM32);
    TCCR3B &= ~(1 << CS32);
    TCCR3B &= ~(1 << CS31);
    TCCR3B |= (1 << CS30);
    
    TCCR4A |= (1 << COM4A1);
    TCCR4A &= ~(1 << COM4A0);
    TCCR4A &= ~(1 << WGM41);
    TCCR4A |= (1 << WGM40);
    TCCR4B &= ~(1 << WGM43);
    TCCR4B &= ~(1 << WGM42);
    TCCR4B &= ~(1 << CS42);
    TCCR4B &= ~(1 << CS41);
    TCCR4B |= (1 << CS40);
}

void InitializeSerialPort(void)
{
    UBRR0H = (byte)(BAUD_RATE >> 8);
    UBRR0L = (byte)BAUD_RATE;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

inline unsigned char RecieveSerialByte(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return UDR0;
}

inline void SendSerialByte(unsigned char data)
{
    while (!(UCSR0A & ( 1 << UDRE0)))
    {
    }
    
    UDR0 = data;
}


#endif /* ATMEGA2560_H_ */