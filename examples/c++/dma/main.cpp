#include <iostream>
#include <memory>

#include <freequant/strategy/Strategy.h>
#include <freequant/indicators/Indicator.h>
#include <freequant/indicators/MA.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/providers/fix/FixMarketDataProvider.h>
#include <freequant//providers/ctp/CtpMarketDataProvider.h>
#include <freequant/trade/TradeProvider.h>
#include <freequant/providers/ctp/CtpTradeProvider.h>

using namespace std;

class DmaStrategy : public FreeQuant::Strategy {
private:
    boost::shared_ptr<FreeQuant::MarketDataProvider> _mdProvider;
    boost::shared_ptr<FreeQuant::TradeProvider> _tradeProvider;
    FreeQuant::MA ma;
public:
    void onInit() {
        setRunningMode(Strategy::Live);
//        string connection = "protocal=tcp;host=180.168.212.79;port=31213;userid=40022870;password=141537;brokerid=4000";
        string connection = "protocal=tcp;host=asp-sim2-front1.financial-trading-platform.com;port=26213;userid=352240;password=888888;brokerid=2030";

        _mdProvider.reset(new FreeQuant::CtpMarketDataProvider(connection));
//        _mdProvider.reset(new FreeQuant::FixMarketDataProvider("senderid=ME;targetid=FQMarketDataServer;host=127.0.0.1;port=7711;username=simuser;password=simuser"));
        _tradeProvider.reset(new FreeQuant::CtpTradeProvider(connection));

        vector<string> symbols;
        symbols.push_back("IF1302");
        symbols.push_back("GOOG");
        addSymbols(symbols);

        chooseMarketProvider("CTP");
        chooseTradeProvider("CTP");

        setMarketDataProvider(_mdProvider.get());
        setTradeProvider(_tradeProvider.get());

        addIndicator(&ma);
    }
    void onStart() {
        std::cout << "strategy start..." << std::endl;


    }

    void onStop() {
        std::cout << "strategy exit..." << std::endl;
    }

    void onBar(const FreeQuant::Bar& bar) {
        cout << "bar: "<< bar << endl;
    }

    void onTick(const FreeQuant::Tick& tick) {
        cout << "tick: "<< tick << endl;
    }

    void onDestroy() {
        std::cout << "strategy destroy..." << std::endl;
    }
};

int main() {
    DmaStrategy strategy;
    strategy.init();
    strategy.start();
    while (strategy.running()) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
    strategy.destroy();
}

