# ticker

Micro lib for invoking functions for every N number of T, where for T is time in milliseconds.
Written with the intent of being used in the run loop of Arduinos.

Example

```c
#include <ticker.h>

// NowHandler, in this case getting time as you would on an Arduino 
uint32_t now()
{
  return millis();
}

// A TickerHandler, called every interval
void on_tick()
{
  // Do something
}

int main()
{
  struct Ticker ticker;
  if (ticker_init(&ticker, on_tick, 1000) != 0)
  {
    return 1; // Failed to initialize ticker
  }

  struct Ticker *tickers[] = { &ticker };
  struct TickerManager ticker_manager;

  if (ticker_manager_init(&ticker_manager, now, tickers, 1) != 0)
  {
    return 1; // Failed to initialize ticker manager
  }

  // Use execute to make the manager loop through the tickers and check their interval against the current time.
  ticker_manager_exec(&ticker_manager);

  return 0;
}
```

