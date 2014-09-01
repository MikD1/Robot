/*
 * ATMega32u4.h
 *
 * Created: 29.08.2014 19:23:16
 * Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
 */

#ifndef ATMEGA32U4_H_
#define ATMEGA32U4_H_

void InitializePWM(void);
void InitializeSerialPort(void);
inline unsigned char RecieveSerialByte(void);
inline void SendSerialByte(unsigned char data);

#define SERIAL_INTERRUPT USART1_RX_vect

// GPIO 13
#define LED1_DDR DDRC
#define LED1_PORT PORTC
#define LED1_PIN PORTC7
// GPIO 12
#define LED2_DDR DDRD
#define LED2_PORT PORTD
#define LED2_PIN PORTD6
// GPIO 11
#define LED3_DDR DDRB
#define LED3_PORT PORTB
#define LED3_PIN PORTB7
// GPIO 10
#define LED4_DDR DDRB
#define LED4_PORT PORTB
#define LED4_PIN PORTB6
// GPIO 9
#define LED5_DDR DDRB
#define LED5_PORT PORTB
#define LED5_PIN PORTB5

// GPIO A0
#define SENSOR1_DDR DDRF
#define SENSOR1_PORT PORTF
#define SENSOR1_PIN PORTF7
// GPIO A1
#define SENSOR2_DDR DDRF
#define SENSOR2_PORT PORTF
#define SENSOR2_PIN PORTF6
// GPIO A2
#define SENSOR3_DDR DDRF
#define SENSOR3_PORT PORTF
#define SENSOR3_PIN PORTF5
// GPIO A3
#define SENSOR4_DDR DDRF
#define SENSOR4_PORT PORTF
#define SENSOR4_PIN PORTF4
// GPIO A4
#define SENSOR5_DDR DDRF
#define SENSOR5_PORT PORTF
#define SENSOR5_PIN PORTF1

// GPIO 4
#define RIGHT_MOTOR_DIRECTION_DDR DDRD
#define RIGHT_MOTOR_DIRECTION_PORT PORTD
#define RIGHT_MOTOR_DIRECTION_PIN PIND4
// GPIO 7
#define LEFT_MOTOR_DIRECTION_DDR DDRE
#define LEFT_MOTOR_DIRECTION_PORT PORTE
#define LEFT_MOTOR_DIRECTION_PIN PINE6
// GPIO 5
#define RIGHT_MOTOR_SPEED_DDR DDRC
#define RIGHT_MOTOR_SPEED_PORT PORTC
#define RIGHT_MOTOR_SPEED_PIN PINC6
// GPIO 6
#define LEFT_MOTOR_SPEED_DDR DDRD
#define LEFT_MOTOR_SPEED_PORT PORTD
#define LEFT_MOTOR_SPEED_PIN PIND7
// -------
#define RIGHT_MOTOR_SPEED_VALUE OCR3A
#define LEFT_MOTOR_SPEED_VALUE OCR4D

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
    TCCR3B |= (1 << CS40);
    
    TCCR4C |= (1 << COM4D1);
    TCCR4C &= ~(1 << COM4D0);
    TCCR4C |= (1 << PWM4D);
    TCCR4D &= ~(1 << WGM41);
    TCCR4D |= (1 << WGM40);
    TCCR4B &= ~(1 << CS43);
    TCCR4B &= ~(1 << CS42);
    TCCR4B &= ~(1 << CS41);
    TCCR4B |= (1 << CS40);
}

void InitializeSerialPort(void)
{
    UBRR1H = (byte)(BAUD_RATE >> 8);
    UBRR1L = (byte)BAUD_RATE;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
}

inline unsigned char RecieveSerialByte(void)
{
    while (!(UCSR1A & (1 << RXC1)))
    {
    }

    return UDR1;
}

inline void SendSerialByte(unsigned char data)
{
    while (!(UCSR1A & ( 1 << UDRE1)))
    {
    }
    
    UDR1 = data;
}

#endif /* ATMEGA32U4_H_ */
