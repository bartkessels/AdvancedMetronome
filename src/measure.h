#pragma once

#include <QWidget>
#include <QString>
#include <QJsonObject>

#include <QDebug>

namespace Ui {
class Measure;
}

class Measure : public QWidget
{
    Q_OBJECT

#define JSON_KEY_MEASURE_TITLE "measure_title"
#define JSON_KEY_MEASURE_BPM "beats_per_minute"
#define JSON_KEY_MEASURE_REPEATS "number_of_repeats"
#define JSON_KEY_MEASURE_NUMERATOR "numerator"
#define JSON_KEY_MEASURE_DENOMINATOR "denominator"

#define DEFAULT_TIME_SIGNATURE 4

public:
    explicit Measure(QWidget *parent = nullptr);
    explicit Measure(QJsonObject jsonObject, QWidget *parent = nullptr);
    ~Measure();

    QString getTitle();
    int getBeatsPerMinute();
    int getNumberOfRepeats();
    int getTimeSignature();
    int getNumerator();
    int getDenominator();
    int getNumeratorIndex();
    int getDenominatorIndex();
    QJsonObject getAsJsonObject();

    void setTitle(QString title);
    void setBeatsPerMinute(int beatsPerMinute);
    void setNumberOfRepeats(int numberOfRepeats);
    void setNumeratorIndex(int numeratorIndex);
    void setDenominatorIndex(int denominatorIndex);
    void loadFromJsonObject(QJsonObject jsonObject);

signals:
    void moveMeasureUp(Measure *measure);
    void moveMeasureDown(Measure *measure);

private slots:
    void on_btn_moveUp_clicked();
    void on_btn_moveDown_clicked();
    void on_btn_delete_clicked();

private:
    Ui::Measure *ui;
};
