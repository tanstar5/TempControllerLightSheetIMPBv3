#include "communicatorqml.h"
#include <QSerialPort>
#include <QThread>
#include <QTimer>

#include <QSerialPortInfo>
#include <QDebug>



QSerialPort *seriall;
QSerialPort *serial;
QTimer *autoTimer;
QTimer *autoTimer561;
QTimer *autoTimer491;
QTimer *autoTimerProtocol;
QTimer *autoTimerInterval;

communicatorQml::communicatorQml(QObject *parent)
    : QObject{parent}
{
    autoTimer = new QTimer(this);
    autoTimer->setInterval(1000);
    autoTimer->setSingleShot(false);
    connect(autoTimer, SIGNAL(timeout()), this, SLOT(readSerial()));

    autoTimer561 = new QTimer(this);
    //autoTimer561->setInterval(2000);
    autoTimer561->setSingleShot(true);
    connect(autoTimer561, SIGNAL(timeout()), this, SLOT(offL561()));

    autoTimer491 = new QTimer(this);
    //autoTimer561->setInterval(2000);
    autoTimer491->setSingleShot(true);
    connect(autoTimer491, SIGNAL(timeout()), this, SLOT(offL491()));

    autoTimerProtocol = new QTimer(this);
    autoTimer561->setInterval(10000);
    autoTimerProtocol->setSingleShot(false);
    connect(autoTimerProtocol, SIGNAL(timeout()), this, SLOT(switchonL561()));

    autoTimerInterval = new QTimer(this);
    autoTimerInterval->setSingleShot(true);

    //connect(autoTimerProtocol, SIGNAL(timeout()), this, SLOT(offL491()));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
            qDebug() << "Serial Number: " << info.serialNumber();
            qDebug() << "System Location: " << info.systemLocation();
            printf("\n\n");
        }

    seriall = new QSerialPort(this);
   // serial2->
    seriall->setPortName("COM7");
    seriall->setBaudRate(QSerialPort::Baud19200);
    seriall->setDataBits(QSerialPort::Data8);
    seriall->setParity(QSerialPort::NoParity);
    seriall->setStopBits(QSerialPort::OneStop);
    seriall->setFlowControl(QSerialPort::NoFlowControl);
    //serial2->open(QIODevice::ReadWrite);

    serial = new QSerialPort(this);
    serial->setPortName(Value3());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}


int communicatorQml::Value1()
{
    return val1;
}

int communicatorQml::Value2()
{
    return val2;
}

QString communicatorQml::Value3()
{
    return val3;
}

int communicatorQml::getValue1(){
    return val1;
}

int communicatorQml::getValue2(){
    return val2;
}

QString communicatorQml::getValue3(){
    return val3;
}

QString communicatorQml::AotfCom()
{
    return aotfCom_val;
}

QString communicatorQml::getAotfCom()
{
    return aotfCom_val;
}

bool communicatorQml::Laser561()
{
    return laser561_val;
}

bool communicatorQml::getLaser561()
{
    return laser561_val;
}

bool communicatorQml::Laser491()
{
    return laser491_val;
}

bool communicatorQml::getLaser491()
{
    return laser491_val;
}

void communicatorQml::setValue1(int value){
    val1 = value;
    emit Value1Changed();
}

void communicatorQml::setValue2(int value){
    val2 = value;
    emit Value2Changed();
}

void communicatorQml::setValue3(QString value){
    val3 = value;
    emit Value3Changed();
    printf("com port changed to \n");
    if (serial){
        serial->close();
        serial = new QSerialPort();
    }

    serial->setPortName(Value3());

}

void communicatorQml::setAotfCom(QString value)
{
    aotfCom_val = value;
    emit AotfComChanged();
    printf("Aotf com channel changed\n");
    if (seriall){
        seriall->close();
        seriall = new QSerialPort(this);
        seriall->setBaudRate(QSerialPort::Baud19200);
        seriall->setDataBits(QSerialPort::Data8);
        seriall->setParity(QSerialPort::NoParity);
        seriall->setStopBits(QSerialPort::OneStop);
        seriall->setFlowControl(QSerialPort::NoFlowControl);
    }
    qDebug() << "current port" << value;
    seriall->setPortName(AotfCom());
    qDebug() << "current port" << seriall->portName();


}

void communicatorQml::dial1Set(int value){
    setValue1(value);
    setValue2(Value1());
    printf("Dial value changed val1=%d, val2=%d \n",val1,val2);
}

void communicatorQml::readSerial()
{
    serial->open(QIODevice::ReadWrite);
    int data_out = Value1();
    QByteArray data_in;
    printf("writing to serial %d\n",data_out);
    serial->write( (char *) &data_out, sizeof (data_out) );
    if (serial->waitForReadyRead(400)){
        data_in = serial->readAll();
        setValue2((unsigned char)data_in[0]);
        printf("Data read from serial: %d\n",(unsigned char)data_in[0]);
    }

}

void communicatorQml::contiSerial(bool value)
{

    if (value){
        autoTimer->stop();
    }else{
        autoTimer->start();
    }


}

void communicatorQml::dial1c2set()
{
    int value = val1;
    setValue2(value);
    printf("info received val1=%d, val2=%d \n",val1,val2);
}

void communicatorQml::switchonL491()
{
    onL491(true);
}

void communicatorQml::onL491(bool l_on)
{
    if (l_on){
        laser491_val = true;
        // write the code for serial to switch laser on
        seriall->clearError();
        seriall->open(QIODevice::ReadWrite);
        qDebug() << "Error Name : " << seriall->error();
        qDebug() << "Selecting AOTF Channel";
        //printf("sending on command \n");

        char data_channel[] = {'X','2',13};
        seriall->write( (char *) &data_channel, sizeof (data_channel) );
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        char data_cr[] = {13};
        seriall->waitForBytesWritten(400);
        seriall->write( (char *) &data_cr, sizeof (data_cr) );

        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        qDebug() << "Selected AOTF Channel";
        qDebug() << "Switching on selected Channel";

        char data_on_off[] = {'O','1',13};
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        seriall->write( (char *) &data_on_off, sizeof (data_on_off) );
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }

        //char data_cr[] = {13};
        seriall->write( (char *) &data_cr, sizeof (data_cr) );
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        qDebug() << "Switched on selected Channel";
        seriall->close();

        //printf("Laser 561 switched on \n");
        emit onLaser491();
        emit statusChangedLaser491();
        autoTimer491->setInterval(laser491_active);
        autoTimer491->start();

    }else{
        laser491_val = false;
    }

}



void communicatorQml::offL491()
{
    // write the code for serial to switch laser off
    seriall->open(QIODevice::ReadWrite);

    qDebug() << "Selecting AOTF Channel";
    //printf("sending on command \n");

    char data_channel[] = {'X','2',13};
    seriall->write( (char *) &data_channel, sizeof (data_channel) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    char data_cr[] = {13};
    seriall->write( (char *) &data_cr, sizeof (data_cr) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    qDebug() << "Selected AOTF Channel";

    qDebug() << "Switching off selected Channel";
    char data_on_off[] = {'O','0',13};
    seriall->write( (char *) &data_on_off, sizeof (data_on_off) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    //char data_cr[] = {13};
    seriall->write( (char *) &data_cr, sizeof (data_cr) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    qDebug() << "Switched off selected Channel";
    //seriall->close();

    seriall->close();
    onL491(false);
    printf("Laser 491 switched off \n");
    emit offLaser491();
    emit statusChangedLaser491();
    //autoTimer2->start();
}

void communicatorQml::switchonL561()
{
    onL561(true);
}

void communicatorQml::onL561(bool l_on)
{
    if (l_on){
        laser561_val = true;
        // write the code for serial to switch laser on
        seriall->clearError();
        seriall->open(QIODevice::ReadWrite);
        qDebug() << "Error Name : " << seriall->error();
        qDebug() << "Selecting AOTF Channel";
        //printf("sending on command \n");

        char data_channel[] = {'X','1',13};
        seriall->write( (char *) &data_channel, sizeof (data_channel) ); //********
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        char data_cr[] = {13};
        seriall->waitForBytesWritten(400);
        seriall->write( (char *) &data_cr, sizeof (data_cr) ); //********
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        qDebug() << "Selected AOTF Channel";

        qDebug() << "Switching on selected Channel";



        char data_on_off[] = {'O','1',13};
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        seriall->write( (char *) &data_on_off, sizeof (data_on_off) ); //********
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        //char data_cr[] = {13};
        seriall->write( (char *) &data_cr, sizeof (data_cr) );
        seriall->waitForBytesWritten(400);
        if (seriall->waitForReadyRead(400)){
            QByteArray data_in = seriall->readAll();
            //setValue2((unsigned char)data_in[0]);
            qDebug() << "current port name:"<<seriall->portName();
            qDebug() << "Received Signal : " << data_in;
        }
        qDebug() << "Switched on selected Channel";
        seriall->close();

        //printf("Laser 561 switched on \n");
        emit onLaser561();
        emit statusChangedLaser561();
        autoTimer561->setInterval(laser561_active);
        autoTimer561->start();

    }else{
        laser561_val = false;
    }


}

void communicatorQml::offL561()
{
    // write the code for serial to switch laser off
    seriall->open(QIODevice::ReadWrite);

    qDebug() << "Selecting AOTF Channel";
    //printf("sending on command \n");

    char data_channel[] = {'X','1',13};
    seriall->write( (char *) &data_channel, sizeof (data_channel) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    char data_cr[] = {13};
    seriall->write( (char *) &data_cr, sizeof (data_cr) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    qDebug() << "Selected AOTF Channel";

    qDebug() << "Switching off selected Channel";



    char data_on_off[] = {'O','0',13};
    seriall->write( (char *) &data_on_off, sizeof (data_on_off) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    //char data_cr[] = {13};
    seriall->write( (char *) &data_cr, sizeof (data_cr) );
    if (seriall->waitForReadyRead(400)){
        QByteArray data_in = seriall->readAll();
        //setValue2((unsigned char)data_in[0]);
        qDebug() << "current port name:"<<seriall->portName();
        qDebug() << "Received Signal : " << data_in;
    }
    qDebug() << "Switched off selected Channel";
    seriall->close();

    //seriall->close();
    onL561(false);
    printf("Laser 561 switched off \n");
    emit offLaser561();
    emit statusChangedLaser561();
    //autoTimer2->start();

}

void communicatorQml::update_L491activetime(int val)
{
    laser491_active = val;
    qDebug()<<"491 Exposure time changed to:"<<val<<"millisecs" ;
}

void communicatorQml::update_L561activetime(int val)
{
    laser561_active = val;
    qDebug()<<"561 Exposure time changed to:"<<val<<"millisecs" ;
}

void communicatorQml::startProtocol(bool val)
{
    if (val){
        onL561(true);
        autoTimerInterval->setInterval(protocolIntervalTime);
        connect(this, SIGNAL(offLaser561()),autoTimerInterval,SLOT(start()));
        connect(autoTimerInterval, SIGNAL(timeout()), this, SLOT(switchonL491()));

        //autoTimerInterval ->start();

        autoTimerProtocol->setSingleShot(false);
        autoTimerProtocol->setInterval(protocolGlobalTime);
        connect(this, SIGNAL(offLaser491()),autoTimerProtocol,SLOT(start()));
        connect(autoTimerProtocol, SIGNAL(timeout()), this, SLOT(switchonL561()));

        //autoTimerProtocol ->start();

    }else{
        disconnect(autoTimerInterval, SIGNAL(timeout()), this, SLOT(switchonL491()));
        autoTimerProtocol->setSingleShot(true);
        disconnect(autoTimerProtocol, SIGNAL(timeout()), this, SLOT(switchonL561()));
        disconnect(autoTimerInterval, SIGNAL(timeout()), this, SLOT(switchonL491()));
        disconnect(this, SIGNAL(offLaser491()),autoTimerProtocol,SLOT(start()));
    }

}

void communicatorQml::setGlobaltimeProtocol(int value)
{
    protocolGlobalTime = value*1000;
}

void communicatorQml::setIntervaltimeProtocol(int val)
{
    protocolIntervalTime = val*1000;
}


