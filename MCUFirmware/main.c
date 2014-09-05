/*
* MCUFirmware.c
*
* Created: 27.08.2014 18:47:15
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#define F_CPU 16000000
#define BAUD_RATE ((unsigned int)103)

#define byte unsigned char

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "commands.h"
#include "ATMega2560.h"

void InitializePins(void);
void StartedBlink(void);
inline void LedCommand(void);
inline void SensorCommand(void);
inline void DriveCommand(void);

int main(void)
{
    InitializePins();
    InitializePWM();
    InitializeSerialPort();
    StartedBlink();
    
    sei();
    
    while (1)
    {
    }
}

void InitializePins(void)
{
    LED1_DDR |= (1 << LED1_PIN);
    LED2_DDR |= (1 << LED2_PIN);
    LED3_DDR |= (1 << LED3_PIN);
    LED4_DDR |= (1 << LED4_PIN);
    LED5_DDR |= (1 << LED5_PIN);
    
    SENSOR1_DDR &= ~(1 << SENSOR1_PIN);
    SENSOR2_DDR &= ~(1 << SENSOR2_PIN);
    SENSOR3_DDR &= ~(1 << SENSOR3_PIN);
    SENSOR4_DDR &= ~(1 << SENSOR4_PIN);
    SENSOR5_DDR &= ~(1 << SENSOR5_PIN);
    
    M2_DIRECTION_DDR |= (1 << M2_DIRECTION_PIN);
    M1_DIRECTION_DDR |= (1 << M1_DIRECTION_PIN);
    M2_SPEED_DDR |= (1 << M2_SPEED_PIN);
    M1_SPEED_DDR |= (1 << M1_SPEED_PIN);
}

void StartedBlink(void)
{
    for (int i = 0; i < 3; ++i)
    {
        LED1_PORT |= (1 << LED1_PIN);
        LED2_PORT |= (1 << LED2_PIN);
        LED3_PORT |= (1 << LED3_PIN);
        LED4_PORT |= (1 << LED4_PIN);
        LED5_PORT |= (1 << LED5_PIN);
        _delay_ms(350);
        LED1_PORT &= ~(1 << LED1_PIN);
        LED2_PORT &= ~(1 << LED2_PIN);
        LED3_PORT &= ~(1 << LED3_PIN);
        LED4_PORT &= ~(1 << LED4_PIN);
        LED5_PORT &= ~(1 << LED5_PIN);
        _delay_ms(200);
    }
}

inline void LedCommand(void)
{
    byte arg = RecieveSerialByte();
    
    byte address = arg >> 1;
    if (address > 4)
    {
        return;
    }
    
    byte val = arg & 1;
    switch(address)
    {
        case 0:
        {
            if (val)
            {
                LED1_PORT |= (1 << LED1_PIN);
            }
            else
            {
                LED1_PORT &= ~(1 << LED1_PIN);
            }
            
            break;
        }
        
        case 1:
        {
            if (val)
            {
                LED2_PORT |= (1 << LED2_PIN);
            }
            else
            {
                LED2_PORT &= ~(1 << LED2_PIN);
            }
            
            break;
        }
        
        case 2:
        {
            if (val)
            {
                LED3_PORT |= (1 << LED3_PIN);
            }
            else
            {
                LED3_PORT &= ~(1 << LED3_PIN);
            }
            
            break;
        }
        
        case 3:
        {
            if (val)
            {
                LED4_PORT |= (1 << LED4_PIN);
            }
            else
            {
                LED4_PORT &= ~(1 << LED4_PIN);
            }
            
            break;
        }
        
        case 4:
        {
            if (val)
            {
                LED5_PORT |= (1 << LED5_PIN);
            }
            else
            {
                LED5_PORT &= ~(1 << LED5_PIN);
            }
            
            break;
        }
    }
}

inline void SensorCommand(void)
{
    byte arg = RecieveSerialByte();
    if (arg > 4)
    {
        return;
    }
    
    byte val = 0;
    switch (arg)
    {
        case 0:
        {
            val = SENSOR1_PORT & (1 << SENSOR1_PIN);
            break;
        }
        
        case 1:
        {
            val = SENSOR2_PORT & (1 << SENSOR2_PIN);
            break;
        }
        
        case 2:
        {
            val = SENSOR3_PORT & (1 << SENSOR3_PIN);
            break;
        }
        
        case 3:
        {
            val = SENSOR4_PORT & (1 << SENSOR4_PIN);
            break;
        }
        
        case 4:
        {
            val = SENSOR5_PORT & (1 << SENSOR5_PIN);
            break;
        }
    }
    
    SendSerialByte(!!val);
}

inline void DriveCommand(void)
{
    byte arg = RecieveSerialByte();
    
    byte motorsSpeed = arg & 0b11111100;
    byte M1Direction = arg & 0b00000010;
    byte M2Direction = arg & 0b00000001;
    
    if (M1Direction)
    {
        M1_DIRECTION_PORT |= (1 << M1_DIRECTION_PIN);
    }
    else
    {
        M1_DIRECTION_PORT &= ~(1 << M1_DIRECTION_PIN);
    }
    
    if (M2Direction)
    {
        M2_DIRECTION_PORT |= (1 << M2_DIRECTION_PIN);
    }
    else
    {
        M2_DIRECTION_PORT &= ~(1 << M2_DIRECTION_PIN);
    }
    
    if (!motorsSpeed)
    {
        M1_SPEED_VALUE = 0;
        M2_SPEED_VALUE = 0;
    }
    else
    {
        M1_SPEED_VALUE = 255 - 63 + motorsSpeed;
        M2_SPEED_VALUE = 255 - 63 + motorsSpeed;
    }
}

ISR (SERIAL_INTERRUPT)
{
    byte val = RecieveSerialByte();
    switch (val)
    {
        case LED_COMMAND:
        {
            LedCommand();
            break;
        }
        
        case SENSOR_COMMAND:
        {
            SensorCommand();
            break;
        }
        
        case DRIVE_COMMAND:
        {
            DriveCommand();
            break;
        }
    }
}
