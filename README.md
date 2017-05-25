# ticker

Micro lib for invoking functions for every N number of T, where for example N is the interval and T is time;
Written with the intent of being used in the run loop of Arduinos.

Example

```c
#include <ticker.h>

// NowHandler, in this case getting time as you would on an Arduino 
uint32_t now()
{
  return millis();
}

// A TickerHandler, called for every interval
void on_tick()
{
  // Do something
}

int main()
{
  struct Ticker ticker;

  if (ticker_init(&ticker, on_tick, 1000) != 0)
  {
    // Failed to initialize ticker
    return 1;
  }

  struct Ticker *tickers[] = { &ticker };
  struct TickerManager ticker_manager;

  if (ticker_manager_init(&ticker_manager, now, tickers, 1) != 0)
  {
    // Failed to initialize ticker manager
    return 1;
  }

  // Use execute to make the manager loop through the tickers and check their interval against the current time.
  ticker_manager_exec(&ticker_manager);

  return 0;
}
```

