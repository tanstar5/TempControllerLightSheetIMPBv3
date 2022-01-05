#ifndef COMMUNICATORQML_H
#define COMMUNICATORQML_H
#include <QObject>

class communicatorQml:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int Value1 READ getValue1() WRITE setValue1() NOTIFY Value1Changed());
    Q_PROPERTY(int Value2 READ getValue2() WRITE setValue2() NOTIFY Value2Changed());
    Q_PROPERTY(QString Value3 READ getValue3() WRITE setValue3() NOTIFY Value3Changed());

    Q_PROPERTY(QString AotfCom READ getAotfCom() WRITE setAotfCom() NOTIFY AotfComChanged());
    Q_PROPERTY(bool Laser561 READ getLaser561() WRITE onL561() NOTIFY statusChangedLaser561());
    Q_PROPERTY(bool Laser491 READ getLaser491() WRITE onL491() NOTIFY statusChangedLaser491());


public:
    explicit communicatorQml(QObject *parent = nullptr);
    int Value1();
    int getValue1();
    //void setValue1(int value);

    int Value2();
    int getValue2();
    //void setValue2(int value);

    QString Value3();
    QString getValue3();
    //void setValue3(int value);

    QString AotfCom();
    QString getAotfCom();

    bool Laser561();
    bool getLaser561();
    //void setValue3(int value);

    bool Laser491();
    bool getLaser491();


signals:
    void Value1Changed();
    void Value2Changed();
    void Value3Changed();    
    void StartReadAgain();

    void statusChangedLaser561();
    void onLaser561();
    void offLaser561();

    void statusChangedLaser491();
    void onLaser491();
    void offLaser491();

    void AotfComChanged();


public slots:
    void setValue1(int value);
    void setValue2(int value);
    void setValue3(QString value);

    void setAotfCom(QString value);

    void dial1Set(int value);
    void readSerial();
    void contiSerial(bool value);
    void dial1c2set();

    void switchonL491();
    void onL491(bool l_on);
    void offL491();

    void switchonL561();
    void onL561(bool l_on);
    void offL561();

    void update_L491activetime(int val);
    void update_L561activetime(int val);

    void startProtocol(bool val);
    void setGlobaltimeProtocol(int val);
    void setIntervaltimeProtocol(int val);

private:
    int val1 = 0;
    int val2 = 0;
    QString val3 = "com6";

    QString aotfCom_val = "com7";
    bool laser561_val = false;
    bool laser491_val = false;

    int laser561_pow = 0;
    int laser491_pow = 0;

    int laser561_active = 2000;
    int laser491_active = 2000;

    int protocolIntervalTime = 2000;
    int protocolGlobalTime = 6500;
};

#endif // COMMUNICATORQML_H
