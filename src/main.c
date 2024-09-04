#define F_CPU 16000000UL  // Set the clock frequency to 16 MHz

#include <avr/io.h>
#include <util/delay.h>

void uart_init(unsigned int baud)
{
    unsigned int ubrr = F_CPU / 16 / baud - 1; // Calculate baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);      // Set high byte of baud rate
    UBRR0L = (unsigned char)ubrr;             // Set low byte of baud rate
    UCSR0B = (1 << TXEN0);                    // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, 1 stop bit
}

void uart_transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)));       // Wait for empty transmit buffer
    UDR0 = data;                            // Put data into buffer, sends the data
}

void uart_print(const char* str)
{
    while (*str)
    {
        uart_transmit(*str++);               // Send each character in the string
    }
}

int main(void)
{
    uart_init(9600);                        // Initialize UART with 9600 baud rate

    while (1)
    {
        uart_print("Hello\r\n");             // Send "Hello" over UART
        _delay_ms(1000);                    // Delay for 1 second
    }
}
