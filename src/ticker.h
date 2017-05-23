#include <stdint.h>

#ifndef TICKER_H
#define TICKER_H

// TickerManager ------------------------------------------------------------------------

typedef uint32_t (*NowHandler)();

struct TickerManager 
{
    NowHandler _now;
    struct Ticker *_tickers;
    uint8_t _tickers_len;
};

uint8_t ticker_manager_init(struct TickerManager*, NowHandler, struct Ticker*, uint8_t);

void ticker_manager_exec(struct TickerManager*);

// --------------------------------------------------------------------------------------

// Ticker -------------------------------------------------------------------------------

typedef void (*TickHandler)();

struct Ticker
{
    TickHandler _on_tick;
    uint32_t _interval;
    uint32_t _last_tick;
};

uint8_t ticker_init(struct Ticker*, TickHandler, uint32_t);

// --------------------------------------------------------------------------------------

#endif