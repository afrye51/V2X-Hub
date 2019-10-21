/**
 * Pedestrian Webservice
 * Webservice registers pedestrian request for going through intersection
 *
 * The version of the OpenAPI document: 0.1.9
 * 
 *
 * NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */


#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QHostAddress>
#include <QRegExp>
#include <QStringList>
#include <QSharedPointer>
#include <QObject>
#ifdef __linux__
#include <signal.h>
#include <unistd.h>
#endif
#include <qhttpengine/server.h>
#include "OAIApiRouter.h"

#ifdef __linux__
void catchUnixSignals(QList<int> quitSignals) {
    auto handler = [](int sig) -> void {
        // blocking and not aysnc-signal-safe func are valid
        qDebug() << "\nquit the application by signal " << sig;
        QCoreApplication::quit();
    };

    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask    = blocking_mask;
    sa.sa_flags   = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}
#endif

int main(int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
#ifdef __linux__
    QList<int> sigs({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    catchUnixSignals(sigs);
#endif
    // Build the command-line options
    QCommandLineParser parser;
    QCommandLineOption addressOption(
        QStringList() << "a" << "address",
        "address to bind to",
        "address",
        "0.0.0.0"
    );
    parser.addOption(addressOption);
    QCommandLineOption portOption(
        QStringList() << "p" << "port",
        "port to listen on",
        "port",
        "8080"
    );
    parser.addOption(portOption);
    parser.addHelpOption();

    // Parse the options that were provided
    parser.process(a);

    // Obtain the values
    QHostAddress address = QHostAddress(parser.value(addressOption));
    quint16 port = static_cast<quint16>(parser.value(portOption).toInt());

    QSharedPointer<OpenAPI::OAIApiRequestHandler> handler(new OpenAPI::OAIApiRequestHandler());
    auto router = QSharedPointer<OpenAPI::OAIApiRouter>::create();
    router->setUpRoutes();
    QObject::connect(handler.data(), &OpenAPI::OAIApiRequestHandler::requestReceived, [&](QHttpEngine::Socket *socket) {
        router->processRequest(socket);
    });

    QHttpEngine::Server server(handler.data());
    qDebug() << "Serving on " << address.toString() << ":" << port;
    // Attempt to listen on the specified port
    if (!server.listen(address, port)) {
        qCritical("Unable to listen on the specified port.");
        return 1;
    }

    return a.exec();
}
