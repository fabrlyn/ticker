// Default implementations --------------------------------------------

uint32_t now_default()
{
    return 1234;
} 

struct Ticker tickers_empty[] = {};

// --------------------------------------------------------------------

// ticker_manager_init ------------------------------------------------

MU_TEST(test_ticker_manager_init_ticker_manager_null)
{
    uint8_t res = ticker_manager_init(NULL, now_deafult, tickers_empty);
    if (res != 1)
    {
        mu_fail("Failed to null check ticker manager");
    }
}

MU_TEST(test_ticker_manager_init_now_handler_null)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, NULL, tickers);
    if (res != 1)
    {
        mu_fail("Failed to null check now handler");
    }
}

MU_TEST(test_ticker_manager_init_tickers_null)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, now_default, NULL);
    if (res != 1)
    {
        mu_fail("Failed to null check tickers");
    }
}

MU_TEST(test_ticker_manager_init_correct)
{
    struct TickerManager ticker_manager;
    uint8_t res = ticker_manager_init(&ticker_manager, now_deafult, ticker_empty);
    if (res != 0)
    {
        mu_fail("Failed to initialize ticker manager");
    }
}

// --------------------------------------------------------------------

// ticker_manager_exec ------------------------------------------------

MU_TEST(test_ticker_manager_exec)
{

}

// --------------------------------------------------------------------

// ticker_init --------------------------------------------------------

MU_TEST(test_ticker_init_ticker_null)
{

}

MU_TEST(test_ticker_init_ticker_handler_null)
{

}

// --------------------------------------------------------------------