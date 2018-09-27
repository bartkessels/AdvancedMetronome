#pragma once

#include <QWidget>
#include <QString>
#include <QJsonObject>

class IMeasure
{

public:
    virtual ~IMeasure() {}

    // Getters
    virtual int getBpm() = 0;
    virtual int getRepetitions() = 0;
    virtual int getTimeSignature() = 0;
    virtual int getNumerator() = 0;
    virtual int getNumeratorIndex() = 0;
    virtual int getDenominator() = 0;
    virtual int getDenominatorIndex() = 0;
    virtual QString getTitle() = 0;

    // Setters
    virtual void setBpm(int bpm) = 0;
    virtual void setRepetitions(int repetitions) = 0;
    virtual void setTimeSignatureIndex(int numeratorIndex, int denominatorIndex) = 0;
    virtual void setTitle(QString title) = 0;

    // JSON
    virtual QJsonObject getJsonObject() = 0;
    virtual void loadFromJson(QJsonObject jsonObject) = 0;

    // Signals
    virtual void notifyMoveUp(IMeasure *measure) = 0;
    virtual void notifyMoveDown(IMeasure *measure) = 0;
    virtual void notifyDelete(IMeasure *measure) = 0;
};

Q_DECLARE_INTERFACE(IMeasure, "IMeasure")
