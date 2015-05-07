/*
WellyNet (Formerly SoftwareSerialWithHalfDuplex based on SoftwareSerial) - 
Multi-instance software serial with half duplex library for Arduino/Wiring

This library is designed to implement a half duplex, addressed communications
protocol called WellyNet, designed as an exercise in network protocol development
and prototyping for the FabAcademy 2015 class from FabLab Wgtn.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef WellyNet_h
#define WellyNet_h

#include <inttypes.h>
#include <Stream.h>

/******************************************************************************
* Definitions
******************************************************************************/

#define _SS_MAX_RX_BUFF 64 // RX buffer size
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class WellyNet : public Stream
{
private:
  // per object data
  uint8_t _receivePin;
  uint8_t _receiveBitMask;
  volatile uint8_t *_receivePortRegister;

  uint8_t _transmitPin;
  uint8_t _transmitBitMask;
  volatile uint8_t *_transmitPortRegister;

/*
  uint8_t _dndPin;
  uint8_t _dndBitMask;
  volatile uint8_t *_dndPortRegister;
  */
  uint16_t _rx_delay_centering;
  uint16_t _rx_delay_intrabit;
  uint16_t _rx_delay_stopbit;
  uint16_t _tx_delay;

  uint16_t _buffer_overflow:1;
  uint16_t _inverse_logic:1;

  uint8_t _address;
  

  // static data
  static char _receive_buffer[_SS_MAX_RX_BUFF]; 
  static volatile uint8_t _receive_buffer_tail;
  static volatile uint8_t _receive_buffer_head;
  static WellyNet *active_object;

  // private methods
  void recv();
  uint8_t rx_pin_read();
  void tx_pin_write(uint8_t pin_state);
  void setTX(uint8_t transmitPin);
  void setRX(uint8_t receivePin);
  void setDND(uint8_t dndPin);

  // private static method for timing
  static inline void tunedDelay(uint16_t delay);

public:
  // public methods
  WellyNet(uint8_t commsPin, uint8_t address, bool inverse_logic = false);
  ~WellyNet();
  void begin(long speed);
  bool listen();
  void end();
  bool isListening() { return this == active_object; }
  bool overflow() { bool ret = _buffer_overflow; _buffer_overflow = false; return ret; }
  int peek();
  int getPacket(int command[]);
  int checksumCalc(int command[]);

  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();
  
  using Print::write;

  // public only for easy access by interrupt handlers
  static inline void handle_interrupt();
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif
