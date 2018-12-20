
#include "essentialQtso/essentialQt.hpp"
#include "baseClassQtso/baseClassQt.hpp"
#include "cryptoQtso/hashQt.hpp"
//#include "signalso/signal.hpp"

#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QCommandLineParser>
//#include <QThread>

namespace
{

}

int main(int argc, char *argv[])
{
    //MACRO_signalHandler

    QCoreApplication app(argc, argv);
    QString errorStr;
    QCoreApplication::setApplicationName("hasherQt");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("hasherQt is a program to generate hash values");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("input/s", "Filename/s or string/s to hash");

    parser.addOption({"i", R"(file or string)", "Input type", "file"});
    parser.addOption({"o", R"(decimal, hexadecimal or base64)", "Output type", "decimal"});
    parser.addOption({"a", R"(crc32c, xxhash, SHA256, Whirlpool)", "Hash type", "xxhash"});

    //Process the actual command line arguments given by the user
    parser.process(app);

    while (errorStr.isEmpty())
    {
        const QStringList parsedPositionalArgs(parser.positionalArguments());
        if (parsedPositionalArgs.size() < 1)
        {

            eines::baseClassQt_c::appendError_f(errorStr, "No input to hash provided");
            eines::baseClassQt_c::appendError_f(errorStr, parser.helpText());
            break;
        }

        QString inputStr(parsedPositionalArgs.at(0));
        if (inputStr.isEmpty())
        {
            eines::baseClassQt_c::appendError_f(errorStr, "Input is empty");
        }

        eines::hasher_c::inputType_ec inputType;
        QString inputTypeStr;
        if (parser.isSet("i"))
        {
            while (true)
            {
                if (parser.value("i") == "file")
                {
                    inputTypeStr = "file";
                    inputType = eines::hasher_c::inputType_ec::file;
                    break;
                }
                if (parser.value("i") == "string")
                {
                    inputTypeStr = "string";
                    inputType = eines::hasher_c::inputType_ec::string;
                    break;
                }
                eines::baseClassQt_c::appendError_f(errorStr, "Wrong input type value");
                break;
            }
        }
        else
        {
            inputTypeStr = "file";
            inputType = eines::hasher_c::inputType_ec::file;
            //eines::baseClassQt_c::appendError_f(errorStr, "Input type option, -i, not set");
        }

        eines::hasher_c::outputType_ec outputType;
        if (parser.isSet("o"))
        {
            while (true)
            {
//                if (parser.value("o") == "unsigned64bitInteger")
//                {
//                    outputType = eines::hasher_c::outputType_ec::unsigned64bitInteger;
//                    break;
//                }
                if (parser.value("o") == "decimal")
                {
                    outputType = eines::hasher_c::outputType_ec::decimalString;
                    break;
                }
                if (parser.value("o") == "hexadecimal")
                {
                    outputType = eines::hasher_c::outputType_ec::hexadecimalString;
                    break;
                }
                if (parser.value("o") == "base64")
                {
                    outputType = eines::hasher_c::outputType_ec::base64String;
                    break;
                }
                eines::baseClassQt_c::appendError_f(errorStr, "Wrong output type value");
                break;
            }
        }
        else
        {
            outputType = eines::hasher_c::outputType_ec::decimalString;
            //eines::baseClassQt_c::appendError_f(errorStr, "Output type option, -o, not set");
        }

        eines::hasher_c::hashType_ec hashType;
        if (parser.isSet("a"))
        {
            while (true)
            {
                if (parser.value("a") == "crc32c")
                {
                    hashType = eines::hasher_c::hashType_ec::crc32c;
                    break;
                }
                if (parser.value("a") == "xxhash")
                {
                    hashType = eines::hasher_c::hashType_ec::XXHASH64;
                    break;
                }
                if (parser.value("a") == "SHA256")
                {
                    hashType = eines::hasher_c::hashType_ec::SHA256;
                    break;
                }
                if (parser.value("a") == "Whirlpool")
                {
                    hashType = eines::hasher_c::hashType_ec::whirlpool;
                    break;
                }
                eines::baseClassQt_c::appendError_f(errorStr, "Wrong hash type value");
                break;
            }
        }
        else
        {
            hashType = eines::hasher_c::hashType_ec::XXHASH64;
            //eines::baseClassQt_c::appendError_f(errorStr, "Hash type option, -h, not set");
        }

        if (not errorStr.isEmpty())
        {
            break;
        }

        for (const QString& inputStr_ite_con : parsedPositionalArgs)
        {
            qtOutRef_ext() << "\nInput (" << inputTypeStr << "): " <<inputStr_ite_con << "\n";
            eines::hasher_c hasherObj(inputType, inputStr_ite_con, outputType, hashType);
            hasherObj.generateHash_f();
            if (hasherObj.anyError_f())
            {
                qtOutRef_ext() << hasherObj.getError_f();
            }
            else
            {
//                if (hasherObj.hashNumberResultSet_f())
//                {
//                    qtOutRef_ext() << "Hash number: " << hasherObj.hashNumberResult_f() << "\n";
//                }
                if (hasherObj.hashStringResultSet_f())
                {
                    qtOutRef_ext() << "Hash string: " << QString::fromStdString(hasherObj.hashStringResult_f()) << "\n";
                }
            }
        }
        break;
    }

    //is this even necessary?
    //QTimer::singleShot(0, &app, SLOT(quit()));

    //app.exec(); //run the application

    if (not errorStr.isEmpty())
    {
        qtOutRef_ext() << "Errors:\n" << errorStr << "\n";
        return EXIT_FAILURE;
    }

//    {
//        qtOutRef_ext() << "\nPress control+C or send a SIGTERM to exit" << endl;
//        while (eines::signal::isRunning_f())
//        {
//            QThread::sleep(1);
//        }
//    }
}
