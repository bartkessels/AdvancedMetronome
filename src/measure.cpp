#include "measure.h"
#include "ui_measure.h"

Measure::Measure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Measure)
{
    ui->setupUi(this);

    ui->vLayout_buttons->setAlignment(Qt::AlignTop);
}

Measure::Measure(QJsonObject jsonObject, QWidget *parent):
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

int Measure::getTimeSignature()
{
    int numerator = getNumerator();
    int denominator = getDenominator();

    if (numerator <= 0) {
        return DEFAULT_TIME_SIGNATURE;
    }

    return (numerator / denominator) * denominator;
}

int Measure::getNumerator()
{
    return ui->cbox_timeSignatureNumerator->currentText().toInt();
}

int Measure::getDenominator()
{
    return ui->cbox_timeSignatureDenominator->currentText().toInt();
}

int Measure::getNumeratorIndex()
{
    return ui->cbox_timeSignatureNumerator->currentIndex();
}

int Measure::getDenominatorIndex()
{
    return ui->cbox_timeSignatureDenominator->currentIndex();
}

QJsonObject Measure::getAsJsonObject()
{
    QString measureTitle = getTitle();
    int beatsPerMinute = getBeatsPerMinute();
    int numberOfRepeats = getNumberOfRepeats();
    int numeratorIndex = getNumeratorIndex();
    int denominatorIndex = getDenominatorIndex();
    QJsonObject jsonObject;

    jsonObject.insert(JSON_KEY_MEASURE_TITLE, measureTitle);
    jsonObject.insert(JSON_KEY_MEASURE_BPM, beatsPerMinute);
    jsonObject.insert(JSON_KEY_MEASURE_REPEATS, numberOfRepeats);
    jsonObject.insert(JSON_KEY_MEASURE_NUMERATOR, numeratorIndex);
    jsonObject.insert(JSON_KEY_MEASURE_DENOMINATOR, denominatorIndex);

    return jsonObject;
}

void Measure::loadFromJsonObject(QJsonObject jsonObject)
{
    QString measureTitle = jsonObject.value(JSON_KEY_MEASURE_TITLE).toString();
    int beatsPerMinute = jsonObject.value(JSON_KEY_MEASURE_BPM).toInt();
    int numberOfRepeats = jsonObject.value(JSON_KEY_MEASURE_REPEATS).toInt();
    int numeratorIndex = jsonObject.value(JSON_KEY_MEASURE_NUMERATOR).toInt();
    int denominatorIndex = jsonObject.value(JSON_KEY_MEASURE_DENOMINATOR).toInt();

    setTitle(measureTitle);
    setBeatsPerMinute(beatsPerMinute);
    setNumberOfRepeats(numberOfRepeats);
    setNumeratorIndex(numeratorIndex);
    setDenominatorIndex(denominatorIndex);
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

void Measure::setNumeratorIndex(int numeratorIndex)
{
    ui->cbox_timeSignatureNumerator->setCurrentIndex(numeratorIndex);
}

void Measure::setDenominatorIndex(int denominatorIndex)
{
    ui->cbox_timeSignatureDenominator->setCurrentIndex(denominatorIndex);
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
