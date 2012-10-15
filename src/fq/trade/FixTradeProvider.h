#ifndef FQ_TRADE_FIXTRADEPROVIDER_H
#define FQ_TRADE_FIXTRADEPROVIDER_H

#include <quickfix/Application.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionID.h>

#include <fq/trade/TradeProvider.h>
#include <fq/strategy/Order.h>

namespace FreeQuant { namespace Trade {

class HistoricalDataRequest;

class FixTradeProvider : public TradeProvider, private FIX::Application, private FIX::MessageCracker {
public:
    FixTradeProvider();
    virtual ~FixTradeProvider();
    void connect();
    void disconnect();
    bool isConnected() const;
    std::string name() const { return "FIX"; }

    std::vector<std::string> availableExchanges() const;
    std::vector<std::string> availableInstruments() const;
    void logon();
    void onLogon();
    void logout();
    void onLogout();
    void onError() {}
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);

    void sendOrder(FreeQuant::Strategy::Order&);
    void cancelOrder(FreeQuant::Strategy::Order&);
    void replaceOrder(FreeQuant::Strategy::Order&);

    void openOrders() const;

    void requestHistoricalData(HistoricalDataRequest& request);
    void cancelHistoricalData(HistoricalDataRequest& request);

private:
    void onCreate(const FIX::SessionID&);
    void onLogon(const FIX::SessionID&);
    void onLogout(const FIX::SessionID&);
    void toAdmin(FIX::Message&, const FIX::SessionID&);
    void toApp(FIX::Message&, const FIX::SessionID&)
        throw(FIX::DoNotSend);
    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);
    void fromApp( const FIX::Message&, const FIX::SessionID& )
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    void onMessage(const FIX44::MarketDataRequestReject&, const FIX::SessionID&);
    void onMessage(const FIX44::MarketDataIncrementalRefresh&, const FIX::SessionID&);
    void onMessage(const FIX44::MarketDataSnapshotFullRefresh&, const FIX::SessionID&);
    void onMessage(const FIX44::ExecutionReport&, const FIX::SessionID&);
    void onMessage(const FIX44::SecurityList&, const FIX::SessionID&);
    void onMessage(const FIX44::OrderCancelReject&, const FIX::SessionID&);

    FIX::SessionSettings *m_settings;
    FIX::FileStoreFactory *m_storeFactory;
    FIX::SocketInitiator *m_initiator;
    FIX::SessionID *m_sessionId;

    std::string senderCompId;
    std::string targetCompId;
};

}}
#endif // FQ_TRADE_FIXTRADEPROVIDER_H