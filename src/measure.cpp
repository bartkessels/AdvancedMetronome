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
    loadFromJson(jsonObject);
}

Measure::~Measure()
{
    delete ui;
}

// =============================================================================
// Getters

int Measure::getBpm()
{
    return ui->spn_beatsPerMinute->value();
}

int Measure::getRepetitions()
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

int Measure::getNumeratorIndex()
{
    return ui->cbox_timeSignatureNumerator->currentIndex();
}

int Measure::getDenominator()
{
    return ui->cbox_timeSignatureDenominator->currentText().toInt();
}

int Measure::getDenominatorIndex()
{
    return ui->cbox_timeSignatureDenominator->currentIndex();
}

QString Measure::getTitle()
{
    return ui->le_title->text();
}

// =============================================================================
// Setter

void Measure::setBpm(int beatsPerMinute)
{
    int minBeatsPerMinute = ui->spn_beatsPerMinute->minimum();
    int maxBeatsPerMinute = ui->spn_beatsPerMinute->maximum();

    if (beatsPerMinute >= minBeatsPerMinute && beatsPerMinute <= maxBeatsPerMinute) {
        ui->spn_beatsPerMinute->setValue(beatsPerMinute);
    }
}

void Measure::setRepetitions(int repetitions)
{
    int minRepetitions= ui->spn_numberOfRepeats->minimum();
    int maxRepetitions = ui->spn_numberOfRepeats->maximum();

    if (repetitions >= minRepetitions && maxRepetitions <= repetitions) {
        ui->spn_numberOfRepeats->setValue(repetitions);
    }
}

void Measure::setTimeSignatureIndex(int numeratorIndex, int denominatorIndex)
{
    ui->cbox_timeSignatureNumerator->setCurrentIndex(numeratorIndex);
    ui->cbox_timeSignatureDenominator->setCurrentIndex(denominatorIndex);
}

void Measure::setTitle(QString title)
{
    ui->le_title->setText(title);
}

// =============================================================================
// Json

QJsonObject Measure::getJsonObject()
{
    QString title = getTitle();
    int bpm = getBpm();
    int repetitions = getRepetitions();
    int numeratorIndex = getNumeratorIndex();
    int denominatorIndex = getDenominatorIndex();
    QJsonObject jsonObject;

    jsonObject.insert(JSON_KEY_TITLE, title);
    jsonObject.insert(JSON_KEY_BPM, bpm);
    jsonObject.insert(JSON_KEY_REPEATS, repetitions);
    jsonObject.insert(JSON_KEY_NUMERATOR, numeratorIndex);
    jsonObject.insert(JSON_KEY_DENOMINATOR, denominatorIndex);

    return jsonObject;
}

void Measure::loadFromJson(QJsonObject jsonObject)
{
    QString title = jsonObject.value(JSON_KEY_TITLE).toString();
    int bpm = jsonObject.value(JSON_KEY_BPM).toInt();
    int repetitions = jsonObject.value(JSON_KEY_REPEATS).toInt();
    int numeratorIndex = jsonObject.value(JSON_KEY_NUMERATOR).toInt();
    int denominatorIndex = jsonObject.value(JSON_KEY_DENOMINATOR).toInt();

    setTitle(title);
    setBpm(bpm);
    setRepetitions(repetitions);
    setTimeSignatureIndex(numeratorIndex, denominatorIndex);
}

// =============================================================================
// Slots

/**
 * @brief Measure::on_btn_moveUp_clicked
 *
 * Notify the listeners that the measure is
 * supposed to be moved up
 *
 */
void Measure::on_btn_moveUp_clicked()
{
    emit notifyMoveUp(this);
}

/**
 * @brief Measure::on_btn_moveDown_clicked
 *
 * Notify the listeners that the measure is
 * supposed to be moved down
 *
 */
void Measure::on_btn_moveDown_clicked()
{
    emit notifyMoveDown(this);
}

/**
 * @brief Measure::on_btn_delete_clicked
 *
 * Delete the current object
 *
 */
void Measure::on_btn_delete_clicked()
{
    this->deleteLater();
}
