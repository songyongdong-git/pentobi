//-----------------------------------------------------------------------------
/** @file pentobi_qml/Main.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QApplication>
#include <QCommandLineParser>
#include <QMessageBox>
#include <QTranslator>
#include <QtQml>
#include <QtWebView/QtWebView>
#include "AnalyzeGameModel.h"
#include "GameModel.h"
#include "HelpFileExtractor.h"
#include "PlayerModel.h"
#include "RatingModel.h"
#include "libboardgame_util/Log.h"

using libboardgame_util::RandomGenerator;

//-----------------------------------------------------------------------------

namespace {

#ifdef Q_OS_ANDROID
void initAndroid()
{
    // Disable sidebars in QtQuick.Dialogs.FileDialog, the dialog is not
    // very usable on smartphones otherwise
    QSettings settings;
    settings.setValue("QQControlsFileDialog/sidebarVisible", false);
}
#endif

}

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    libboardgame_util::LogInitializer log_initializer;
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Pentobi");
    app.setApplicationName("Pentobi");
#ifdef VERSION
    app.setApplicationVersion(VERSION);
#endif
#ifdef Q_OS_ANDROID
    initAndroid();
#endif
    qmlRegisterType<AnalyzeGameModel>("pentobi", 1, 0, "AnalyzeGameModel");
    qmlRegisterType<GameModel>("pentobi", 1, 0, "GameModel");
    qmlRegisterType<HelpFileExtractor>("pentobi", 1, 0, "HelpFileExtractor");
    qmlRegisterType<PlayerModel>("pentobi", 1, 0, "PlayerModel");
    qmlRegisterType<RatingModel>("pentobi", 1, 0, "RatingModel");
    qmlRegisterInterface<AnalyzeGameElement>("AnalyzeGameElement");
    qmlRegisterInterface<GameMove>("GameModelMove");
    qmlRegisterInterface<PieceModel>("PieceModel");
    QString locale = QLocale::system().name();
    QTranslator translatorPentobi;
    translatorPentobi.load("qml_" + locale, ":qml/i18n");
    app.installTranslator(&translatorPentobi);
    // The translation of standard buttons in QtQuick.Dialogs.MessageDialog
    // is broken on Android (last tested with Qt 5.6; QTBUG-43353), so we
    // created our own file, which contains the translations we need.
    QTranslator translatorQt;
    translatorQt.load("replace_qtbase_" + locale, ":qml/i18n");
    app.installTranslator(&translatorQt);
    QCommandLineParser parser;
    QCommandLineOption optionNoBook("nobook");
    parser.addOption(optionNoBook);
    QCommandLineOption optionNoDelay("nodelay");
    parser.addOption(optionNoDelay);
    QCommandLineOption optionSeed("seed", "Set random seed to <n>.", "n");
    parser.addOption(optionSeed);
    QCommandLineOption optionThreads("threads", "Use <n> threads (0=auto).",
                                     "n");
    parser.addOption(optionThreads);
#if ! LIBBOARDGAME_DISABLE_LOG
    QCommandLineOption optionVerbose("verbose");
    parser.addOption(optionVerbose);
#endif
    parser.process(app);
    try
    {
#if ! LIBBOARDGAME_DISABLE_LOG
        if (! parser.isSet(optionVerbose))
            libboardgame_util::disable_logging();
#endif
        if (parser.isSet(optionNoBook))
            PlayerModel::noBook = true;
        if (parser.isSet(optionNoDelay))
            PlayerModel::noDelay = true;
        bool ok;
        if (parser.isSet(optionSeed))
        {
            auto seed = parser.value(optionSeed).toUInt(&ok);
            if (! ok)
                throw runtime_error("--seed must be a positive number");
            RandomGenerator::set_global_seed(seed);
        }
        if (parser.isSet(optionThreads))
        {
            auto nuThreads = parser.value(optionThreads).toUInt(&ok);
            if (! ok)
                throw runtime_error("--threads must be a positive number");
            PlayerModel::nuThreads = nuThreads;
        }
        QQmlApplicationEngine engine(QUrl("qrc:///qml/Main.qml"));
        QtWebView::initialize();
        return app.exec();
    }
    catch (const bad_alloc&)
    {
        // bad_alloc is an expected error because the player requires a larger
        // amount of memory.
        QMessageBox::critical(nullptr, app.translate("main", "Pentobi"),
                              app.translate("main", "Not enough memory."));
        return 1;
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}

//-----------------------------------------------------------------------------
