#include <stdlib.h>
#include <stdint.h>
#include "ticker.h"

// TickerManager ------------------------------------------------------------------------

uint8_t ticker_manager_init(struct TickerManager *ticker_manager, NowHandler now_handler, struct Ticker **tickers, uint8_t tickers_len)
{
    if (ticker_manager == NULL || now_handler == NULL || tickers == NULL)
    {
        return 1;
    }

    ticker_manager->_tickers = tickers;
    ticker_manager->_tickers_len = tickers_len;
    ticker_manager->_now = now_handler;

    return 0;
}

void ticker_manager_exec(struct TickerManager *ticker_manager)
{
    for (uint8_t i = 0; i < ticker_manager->_tickers_len; i++)
    {
        struct Ticker *ticker = ticker_manager->_tickers[i];
        uint32_t now = ticker_manager->_now();

        if ((ticker->_last_tick - now) >= ticker->_interval)
        {
            ticker->_last_tick = now;
            ticker->_on_tick();
        }
    }
}

// --------------------------------------------------------------------------------------

// Ticker -------------------------------------------------------------------------------

uint8_t ticker_init(struct Ticker *ticker, TickHandler on_tick, uint32_t interval)
{
    if (ticker == NULL || on_tick == NULL)
    {
        return 1;
    }

    ticker->_on_tick = on_tick;
    ticker->_interval = interval;
    ticker->_last_tick = 0;

    return 0;
}

// --------------------------------------------------------------------------------------
