#pragma once

#include <QWidget>
#include <QString>
#include <QJsonObject>

#include <QDebug>

#include "imeasure.h"

namespace Ui {
class Measure;
}

class Measure : public QWidget, public IMeasure
{
    Q_OBJECT
    Q_INTERFACES(IMeasure)

public:
    explicit Measure(QWidget *parent = nullptr);
    explicit Measure(QJsonObject jsonObject, QWidget *parent = nullptr);
    ~Measure();

    // Getters
    int getBpm();
    int getRepetitions();
    int getTimeSignature();
    int getNumerator();
    int getNumeratorIndex();
    int getDenominator();
    int getDenominatorIndex();
    QString getTitle();

    // Setters
    void setBpm(int bpm);
    void setRepetitions(int repetitions);
    void setTimeSignatureIndex(int numeratorIndex, int denominatorIndex);
    void setTitle(QString title);

    // JSON
    QJsonObject getJsonObject();
    void loadFromJson(QJsonObject jsonObject);

signals:
    void notifyMoveUp(IMeasure *measure);
    void notifyMoveDown(IMeasure *measure);
    void notifyDelete(IMeasure *measure);

private slots:
    void on_btn_moveUp_clicked();
    void on_btn_moveDown_clicked();
    void on_btn_delete_clicked();

private:
    Ui::Measure *ui;

    // Time signatures
    const int DEFAULT_TIME_SIGNATURE = 4;

    // JSON keys
    const char* JSON_KEY_TITLE = "measure_title";
    const char* JSON_KEY_BPM = "beats_per_minute";
    const char* JSON_KEY_REPEATS = "number_of_repeats";
    const char* JSON_KEY_NUMERATOR = "numerator";
    const char* JSON_KEY_DENOMINATOR = "denominator";
};
