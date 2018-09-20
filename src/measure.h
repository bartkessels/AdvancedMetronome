#pragma once

#include <QWidget>
#include <QString>
#include <QJsonObject>

namespace Ui {
class Measure;
}

class Measure : public QWidget
{
    Q_OBJECT

#define JSON_KEY_MEASURE_TITLE "measure_title"
#define JSON_KEY_MEASURE_BPM "beats_per_minute"
#define JSON_KEY_MEASURE_REPEATS "number_of_repeats"

public:
    explicit Measure(QWidget *parent = nullptr);
    explicit Measure(QJsonObject *jsonObject, QWidget *parent = nullptr);
    ~Measure();

    QString getTitle();
    int getBeatsPerMinute();
    int getNumberOfRepeats();
    QJsonObject *getAsJsonObject();

    void setTitle(QString title);
    void setBeatsPerMinute(int beatsPerMinute);
    void setNumberOfRepeats(int numberOfRepeats);
    void loadFromJsonObject(QJsonObject *jsonObject);

signals:
    void moveMeasureUp(Measure *measure);
    void moveMeasureDown(Measure *measure);

public slots:
    void on_measureTopMost();
    void on_measureBottomMost();
    void on_locationChanged();

private slots:
    void on_btn_moveUp_clicked();
    void on_btn_moveDown_clicked();
    void on_btn_delete_clicked();

private:
    Ui::Measure *ui;
};
