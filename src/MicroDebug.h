#ifndef __MICRO_DEBUG_H
#define __MICRO_DEBUG_H

// #define ENABLE_DEBUG
// #define DEBUG_PORT Serial

#define TEXTIFY(A) #A
#define ESCAPEQUOTE(A) TEXTIFY(A)

#ifdef ARDUINO

#ifndef DEBUG_USE_PRINT_P
#if defined(ESP8266)
#define DEBUG_USE_PRINT_P 1
#else
#define DEBUG_USE_PRINT_P 0
#endif
#endif

#ifdef ENABLE_DEBUG

// Use os_printf, works but also outputs additional dubug if not using Serial
//#define DEBUG_BEGIN(speed)  DEBUG_PORT.begin(speed);
// DEBUG_PORT.setDebugOutput(true) #define DBUGF(format, ...)
// os_printf(PSTR(format "\n"), ##__VA_ARGS__)

#define DEBUG_BEGIN(speed) DEBUG_PORT.begin(speed)

#if DEBUG_USE_PRINT_P
// Serial.printf_P needs Git version of Arduino Core
#define DBUGF(format, ...) DEBUG_PORT.printf_P(PSTR(format "\n"), ##__VA_ARGS__)
#else
#define DBUGF(format, ...) DEBUG_PORT.printf(format "\n", ##__VA_ARGS__)
#endif

#define DBUG(...) DEBUG_PORT.print(__VA_ARGS__)
#define DBUGLN(...) DEBUG_PORT.println(__VA_ARGS__)
#define DBUGVAR(x, ...)                                                        \
  do {                                                                         \
    DEBUG_PORT.print(F(ESCAPEQUOTE(x) " = "));                                    \
    DEBUG_PORT.println(x, ##__VA_ARGS__);                                      \
  } while (false)

#else

#define DEBUG_BEGIN(speed) DEBUG_PORT.begin(speed)
#define DBUGF(...)
#define DBUG(...)
#define DBUGLN(...)
#define DBUGVAR(...)

#endif // DEBUG

#ifdef DEBUG_SERIAL1
#error DEBUG_SERIAL1 defiend, please use -DDEBUG_PORT=Serial1 instead
#endif

#ifndef DEBUG_PORT
#define DEBUG_PORT Serial
#endif
#define DEBUG DEBUG_PORT

#else

#define DEBUG_BEGIN(speed) 

#ifdef ENABLE_DEBUG

#define DBUGF(format, ...) printf(format "\n", ##__VA_ARGS__)
#define DBUG(...)
#define DBUGLN(...)
#define DBUGVAR(...)

#else

#define DBUGF(...)
#define DBUG(...)
#define DBUGLN(...)
#define DBUGVAR(...)

#endif // DEBUG


#endif

#endif // __MICRO_DEBUG_H
 