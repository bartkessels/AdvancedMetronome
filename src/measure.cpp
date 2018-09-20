#include "measure.h"
#include "ui_measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Measure)
{
    ui->setupUi(this);
}

Measure::Measure(QJsonObject *jsonObject, QWidget *parent):
    Measure(parent)
{
    loadFromJsonObject(jsonObject);
}

Measure::~Measure()
{
    delete ui;
}

QString Measure::getTitle()
{
    return ui->le_title->text();
}

int Measure::getBeatsPerMinute()
{
    return ui->spn_beatsPerMinute->value();
}

int Measure::getNumberOfRepeats()
{
    return ui->spn_numberOfRepeats->value();
}

QJsonObject *Measure::getAsJsonObject()
{
    QString measureTitle = getTitle();
    int beatsPerMinute = getBeatsPerMinute();
    int numberOfRepeats = getNumberOfRepeats();
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_KEY_MEASURE_TITLE, measureTitle);
    jsonObject->insert(JSON_KEY_MEASURE_BPM, beatsPerMinute);
    jsonObject->insert(JSON_KEY_MEASURE_REPEATS, numberOfRepeats);

    return jsonObject;
}

void Measure::loadFromJsonObject(QJsonObject *jsonObject)
{
    QString measureTitle = jsonObject->value(JSON_KEY_MEASURE_TITLE).toString();
    int beatsPerMinute = jsonObject->value(JSON_KEY_MEASURE_BPM).toInt();
    int numberOfRepeats = jsonObject->value(JSON_KEY_MEASURE_REPEATS).toInt();

    setTitle(measureTitle);
    setBeatsPerMinute(beatsPerMinute);
    setNumberOfRepeats(numberOfRepeats);
}

void Measure::setTitle(QString title)
{
    ui->le_title->setText(title);
}

void Measure::setBeatsPerMinute(int beatsPerMinute)
{
    int minBeatsPerMinute = ui->spn_beatsPerMinute->minimum();
    int maxBeatsPerMinute = ui->spn_beatsPerMinute->maximum();

    if (beatsPerMinute >= minBeatsPerMinute && beatsPerMinute <= maxBeatsPerMinute) {
        ui->spn_beatsPerMinute->setValue(beatsPerMinute);
    }
}

void Measure::setNumberOfRepeats(int numberOfRepeats)
{
    int minNumberOfRepeats = ui->spn_numberOfRepeats->minimum();
    int maxNumberOfRepeats = ui->spn_numberOfRepeats->maximum();

    if (numberOfRepeats >= minNumberOfRepeats && numberOfRepeats <= maxNumberOfRepeats) {
        ui->spn_numberOfRepeats->setValue(numberOfRepeats);
    }
}

void Measure::on_measureTopMost()
{
    ui->btn_moveUp->setEnabled(false);
}

void Measure::on_measureBottomMost()
{
    ui->btn_moveDown->setEnabled(false);
}

void Measure::on_locationChanged()
{
    ui->btn_moveUp->setEnabled(true);
    ui->btn_moveDown->setEnabled(true);
}

void Measure::on_btn_moveUp_clicked()
{
    emit moveMeasureUp(this);
}

void Measure::on_btn_moveDown_clicked()
{
    emit moveMeasureDown(this);
}

void Measure::on_btn_delete_clicked()
{
    this->deleteLater();
}
