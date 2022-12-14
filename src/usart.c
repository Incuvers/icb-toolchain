#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

/**
 * @brief ISR for usart rx complete
 * 
 */
ISR(USART0_RX_vect) {
  cli();
  unsigned char value;
  // echo character back
  value = UDR0;
  UDR0 = value;
  sei();
}

void usart_init(void){
  /* Load upper 8-bits into the high byte of the UBRR register
      Default frame format is 8 data bits, no parity, 1 stop bit
      to change use UCSRC, see AVR datasheet */ 
  cli();
  // Enable receiver and transmitter and receive complete interrupt 
  UCSR0B = (1<<TXEN1)|(1<<RXEN1)|(0<<UCSZ12)|(1<<RXCIE1);//|(1<<TXCIE1);
  //8-bit data, 1 stop bit, Aynchronous USART, no parity	
  UCSR0C = (1<<UCSZ11)|(1<<UCSZ10)|(0<<USBS1)|(0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10);
  UBRR0H = (uint8_t) (BAUD_PRESCALE >> 8); 
  UBRR0L = (uint8_t) (BAUD_PRESCALE);// Load lower 8-bits into the low byte of the UBRR register
  sei();
}
