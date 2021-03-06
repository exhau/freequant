#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <freequant/marketdata/CtpMarketDataProvider.h>
#include <freequant/trade/FixTradeProvider.h>
#include <freequant/trade/CtpTradeProvider.h>
#include <freequant/trade/TwsTradeProvider.h>
#include <freequant/strategy/Order.h>
#include <freequant/marketdata/Trade.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    int tr = 1;
    switch(tr){
    case 1: {
        string connection = "protocal=tcp;host=asp-sim2-front1.financial-trading-platform.com;port=26205;userid=352240;password=888888;brokerid=2030";
        trade_provider.reset(new FreeQuant::CtpTradeProvider(connection));
        break;
    }
    case 2:
        trade_provider.reset(new FreeQuant::FixTradeProvider("config.fix"));
        break;
    case 3:
    default:
        trade_provider.reset(new FreeQuant::TwsTradeProvider("host=127.0.0.1"));
        break;
    }

//    std::string connection = "protocal=tcp;host=27.115.78.154;port=31213;userid=40022870;password=141537;brokerid=8000";
//    _md_provider.reset(new FreeQuant::CtpMarketDataProvider(connection));
//    _md_provider->connect(true);
//    vector<string> symbols;
//    symbols.push_back("IF1212");
//    _md_provider->subscribe(symbols);
}

MainWindow::~MainWindow() {}

void MainWindow::onOpenOrders() {
    trade_provider->openOrders();
}

void MainWindow::onFetchOrders() {
    FreeQuant::DateTime dt;
    trade_provider->fetchOrders("IF1212", dt, dt);
}

void MainWindow::onFetchTrades() {
    FreeQuant::DateTime dt;
    trade_provider->fetchTrades("IF1212", dt, dt);
}

void MainWindow::onFetchPositions() {
    trade_provider->updatePosition("IF1212");
}

void MainWindow::onQueryExchanges() {
    trade_provider->availableExchanges();
}

void MainWindow::onQueryInstruments() {
    trade_provider->availableInstruments();
}

void MainWindow::onQueryInvestor() {
    trade_provider->updateAccount();
}

void MainWindow::onCancelOrder() {
    FreeQuant::Order order;
    trade_provider->cancelOrder(order);
}

void MainWindow::onReplaceOrder() {
    FreeQuant::Order order;
    trade_provider->replaceOrder(order);
}

void MainWindow::onPlaceOrder() {
//    CommonDialog dialog(this, CommonDialog::OrderDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant>& params = dialog.params();
//        OrderId id =  params.value("id").toInt();
//        Order order = params.value("order").value<Order>();
//        Contract contract = params.value("contract").value<Contract>();
//        m_client->placeOrder(id, contract, order);
//    }
    FreeQuant::Order order("IF1212", FreeQuant::Order::Market, FreeQuant::Order::Buy, 120.0, 1);
    trade_provider->sendOrder(order);
}

//void MainWindow::onReqOpenOrders() {
//    m_client->reqOpenOrders();
//}

//void MainWindow::onReqAllOpenOrders() {
//    m_client->reqAllOpenOrders();
//}

//void MainWindow::onReqAutoOpenOrders() {
//     m_client->reqAutoOpenOrders(true);
//}

//void MainWindow::onReqAccountUpdate() {

//}

void MainWindow::onClear() {
//    ui->responseTextEdit->clear();
//    ui->dataTextEdit->clear();
//    ui->errorsTextEdit->clear();
}

void MainWindow::onConnect() {
//    string connection = "protocal=tcp;host=asp-sim2-front1.financial-trading-platform.com;port=26205;userid=352240;password=888888;brokerid=2030";
    std::string connection = "protocal=tcp;host=180.168.212.79;port=31205;userid=40022870;password=141537;brokerid=8000";

    trade_provider->connect(connection, true);
//    md_provider->connect();
//    trade_provider->connect();
//    client.connect("",7496, 0);
//    CommonDialog dialog(this, CommonDialog::ConnectionDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant> params = dialog.params();

//        QString ip = params.value("ip").toString();
//        unsigned int port = params.value("port").toUInt();
//        int clientId = params.value("clientId").toInt();
//        QString message = QString("Connecting to Tws using clientId %1 ...").arg(clientId);
//        ui->responseTextEdit->append(message);

//        bool success = m_client->eConnect(ip.toAscii(), port, clientId);
//        if (success) {
//            QString message = QString("Connected to Tws server version %1 at %2.").arg(m_client->serverVersion()).arg(m_client->TwsConnectionTime().c_str());
//            ui->responseTextEdit->append(message);
//        }
//    }
}

void MainWindow::onDisconnect() {
//    md_provider->disconnect();
    trade_provider->disconnect();
}

void MainWindow::onCancelMktData() {
    vector<string> symbols;
    symbols.push_back("IF1210");
    symbols.push_back("cu0909");
//    md_provider->unsubscribe(symbols);
//    trade_provider->unsubscribe(symbols);
}

void MainWindow::onReqMktData() {
    vector<string> symbols;
    symbols.push_back("IF1210");
    symbols.push_back("GOOG");
//    trade_provider->subscribe(symbols);
//    int ret = api->SubscribeMarketData(&instruments[0], instruments.size());
//    cerr << "--->>> Subscribe MarketData " << ((ret == 0) ? "success" : "failed") << endl;

//    CommonDialog dialog(this, CommonDialog::OrderDialog);
//    if (dialog.exec() == QDialog::Accepted) {
//        QMap<QString, QVariant>& params = dialog.params();
//        TickerId id = params.value("id").toInt();;
//        Contract contract = params.value("contract").value<Contract>();
//        std::string genericTicks = params.value("genericTicks").toString().toStdString();
//        bool snapshot = params.value("snapshot").toBool();
//        m_client->reqMktData(id, contract, genericTicks, snapshot);
//    }

//    trade_provider->subscribe(symbols);
 }

//void MainWindow::onExtord() {
//    CommonDialog dialog(this, CommonDialog::OrderAttributesDialog);
//    dialog.exec();
//}

//void MainWindow::onReqIds() {
//    m_client->reqIds(20);
//}

//void MainWindow::onReqContractDetails() {

//}

//void MainWindow::onFinancialAdvisor() {
//    faGroupsXML = faProfilesXML = faAliasesXML = "";
//    faError = false;
//    m_client->requestFA(GROUPS);
//    m_client->requestFA(PROFILES);
//    m_client->requestFA(ALIASES);
//}

//void MainWindow::onReqAccts() {
//    m_client->reqManagedAccts();
//}
