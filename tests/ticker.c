#include <minunit.h>
#include <ticker.h>


// Default implementations --------------------------------------------

void on_tick_default() {}

uint32_t now_default()
{
    return 1234;
} 

struct Ticker *tickers_empty[] = {};

// --------------------------------------------------------------------

// ticker_manager_init ------------------------------------------------

MU_TEST(test_ticker_manager_init_ticker_manager_null)
{
    uint8_t res = ticker_manager_init(NULL, now_default, tickers_empty, 0);
    if (res != 1)
    {
        mu_fail("Failed to null check ticker manager");
    }
}

MU_TEST(test_ticker_manager_init_now_handler_null)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, NULL, tickers_empty, 0);
    if (res != 1)
    {
        mu_fail("Failed to null check now handler");
    }
}

MU_TEST(test_ticker_manager_init_tickers_null)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, now_default, NULL, 0);
    if (res != 1)
    {
        mu_fail("Failed to null check tickers");
    }
}

MU_TEST(test_ticker_manager_init_correct)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, now_default, tickers_empty, 1);
    if (res != 0)
    {
        mu_fail("Failed to initialize ticker manager");
        return;
    }

    if (ticker_manager._now != now_default)
    {
      mu_fail("Failed to set now handler");
      return;
    }

    if (ticker_manager._tickers != tickers_empty)
    {
      mu_fail("Failed to set tickers");
      return;
    }

    if (ticker_manager._tickers_len != 1)
    {
      mu_fail("Failed to set tickers_len");
      return;
    }
}

// --------------------------------------------------------------------

// ticker_manager_exec ------------------------------------------------

uint32_t test_ticker_manager_exec_now_fn()
{
  return 1000;
}

uint8_t test_ticker_manager_exec_on_ticker_counter = 0;
void test_ticker_manager_exec_on_tick()
{
  test_ticker_manager_exec_on_ticker_counter++;
}

MU_TEST(test_ticker_manager_exec)
{
  struct TickerManager ticker_manager;

  struct Ticker ticker_one, ticker_two, ticker_three;
  struct Ticker *tickers[] = { &ticker_one, &ticker_two, &ticker_three };

  if (ticker_init(&ticker_one, test_ticker_manager_exec_on_tick, 1000) != 0)
  {
    mu_fail("Failed to init ticker");
    return;
  }

  if (ticker_init(&ticker_two, test_ticker_manager_exec_on_tick, 1000) != 0)
  {
    mu_fail("Failed to init ticker");
    return;
  }

  if (ticker_init(&ticker_three, test_ticker_manager_exec_on_tick, 1000) != 0)
  {
    mu_fail("Failed to init ticker");
    return;
  }

  if (ticker_manager_init(&ticker_manager, test_ticker_manager_exec_now_fn, tickers, 3) != 0)
  {
    mu_fail("Failed to init ticker manager");
    return;
  }

  ticker_manager_exec(&ticker_manager);

  if (test_ticker_manager_exec_on_ticker_counter != 3)
  {
    mu_fail("Failed to call all three tickers");
    return;
  }

  if (ticker_one._last_tick != 1000 ||
      ticker_one._last_tick != 1000 ||
      ticker_one._last_tick != 1000)
  {
    mu_fail("Failed to set last tick on tickers");
    return;
  }

  ticker_manager_exec(&ticker_manager);

  if (test_ticker_manager_exec_on_ticker_counter != 3)
  {
    mu_fail("Called tickers to many times");
    return;
  }
}

// --------------------------------------------------------------------

// ticker_init --------------------------------------------------------

MU_TEST(test_ticker_init_ticker_null)
{
  uint8_t res = ticker_init(NULL, on_tick_default, 1000);
  if (res != 1)
  {
    mu_fail("Failed to null check ticker");
    return;
  }
}

MU_TEST(test_ticker_init_ticker_handler_null)
{
  struct Ticker ticker;
  uint8_t res = ticker_init(&ticker, NULL, 1000);
  if (res != 1)
  {
    mu_fail("Failed to null check ticker handler");
    return;
  }
}

MU_TEST(test_ticker_init_correct)
{
  struct Ticker ticker;
  uint8_t res = ticker_init(&ticker, on_tick_default, 1000);
  if (res != 0)
  {
    mu_fail("Failed to initialize ticker");
    return;
  }

  if (ticker._on_tick != on_tick_default)
  {
    mu_fail("Failed to set ticker handler");
    return;
  }

  if (ticker._interval != 1000)
  {
    mu_fail("Failed to set interval");
    return;
  }

  if (ticker._last_tick != 0)
  {
    mu_fail("Failed to set last tick to 0");
    return;
  }
}

// --------------------------------------------------------------------

MU_TEST_SUITE(test_suite_ticker)
{
  MU_RUN_TEST(test_ticker_manager_init_ticker_manager_null);
  MU_RUN_TEST(test_ticker_manager_init_now_handler_null);
  MU_RUN_TEST(test_ticker_manager_init_tickers_null);
  MU_RUN_TEST(test_ticker_manager_init_correct);
  MU_RUN_TEST(test_ticker_manager_exec);
  MU_RUN_TEST(test_ticker_init_ticker_handler_null);
  MU_RUN_TEST(test_ticker_init_ticker_null);
  MU_RUN_TEST(test_ticker_init_correct);
}

int main()
{
  MU_RUN_SUITE(test_suite_ticker);
  MU_REPORT();
  return 0;
}
