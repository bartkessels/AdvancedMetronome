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

/**
 * @brief Measure::getBpm
 * @return beats per minute for the measure
 */
int Measure::getBpm()
{
    return ui->spn_beatsPerMinute->value();
}

/**
 * @brief Measure::getRepetitions
 * @return total repetitions for the measure
 */
int Measure::getRepetitions()
{
    return ui->spn_numberOfRepeats->value();
}

/**
 * @brief Measure::getTimeSignature
 * @return the time signature for the measure
 *
 * Calculate the time signature from the user entered
 * numerator and denominator
 *
 */
int Measure::getTimeSignature()
{
    int numerator = getNumerator();
    int denominator = getDenominator();

    if (numerator <= 0) {
        return DEFAULT_TIME_SIGNATURE;
    }

    return (numerator / denominator) * denominator;
}

/**
 * @brief Measure::getNumerator
 * @return the value of the numerator spinner
 */
int Measure::getNumerator()
{
    return ui->cbox_timeSignatureNumerator->currentText().toInt();
}

/**
 * @brief Measure::getNumeratorIndex
 * @return the index of the numerator spinner
 */
int Measure::getNumeratorIndex()
{
    return ui->cbox_timeSignatureNumerator->currentIndex();
}

/**
 * @brief Measure::getDenominator
 * @return the value of the denominator spinner
 */
int Measure::getDenominator()
{
    return ui->cbox_timeSignatureDenominator->currentText().toInt();
}

/**
 * @brief Measure::getDenominatorIndex
 * @return the index of the denominator spinner
 */
int Measure::getDenominatorIndex()
{
    return ui->cbox_timeSignatureDenominator->currentIndex();
}

/**
 * @brief Measure::getTitle
 * @return the title for the measure
 */
QString Measure::getTitle()
{
    return ui->le_title->text();
}

// =============================================================================
// Setter

/**
 * @brief Measure::setBpm
 * @param beatsPerMinute the beats per minute for the measure
 *
 * Set the beats per minute for the measure
 *
 */
void Measure::setBpm(int beatsPerMinute)
{
    int minBeatsPerMinute = ui->spn_beatsPerMinute->minimum();
    int maxBeatsPerMinute = ui->spn_beatsPerMinute->maximum();

    if (beatsPerMinute >= minBeatsPerMinute && beatsPerMinute <= maxBeatsPerMinute) {
        ui->spn_beatsPerMinute->setValue(beatsPerMinute);
    }
}

/**
 * @brief Measure::setRepetitions
 * @param repetitions the total repetitions for the measure
 *
 * Set the total repetitions for the measure
 *
 */
void Measure::setRepetitions(int repetitions)
{
    int minRepetitions= ui->spn_numberOfRepeats->minimum();
    int maxRepetitions = ui->spn_numberOfRepeats->maximum();

    if (repetitions >= minRepetitions && repetitions <= maxRepetitions) {
        ui->spn_numberOfRepeats->setValue(repetitions);
    }
}

/**
 * @brief Measure::setTimeSignatureIndex
 * @param numeratorIndex index of the numerator spinner
 * @param denominatorIndex index of the denominator spinner
 *
 * Set the time signature based on the indices for the
 * numerator and denominator spinners
 *
 */
void Measure::setTimeSignatureIndex(int numeratorIndex, int denominatorIndex)
{
    ui->cbox_timeSignatureNumerator->setCurrentIndex(numeratorIndex);
    ui->cbox_timeSignatureDenominator->setCurrentIndex(denominatorIndex);
}

/**
 * @brief Measure::setTitle
 * @param title the title for the measure
 *
 * Set the title for the measure
 *
 */
void Measure::setTitle(QString title)
{
    ui->le_title->setText(title);
}

// =============================================================================
// Json

/**
 * @brief Measure::getJsonObject
 * @return json representation of the measure
 *
 * Put all user fillable fields into a json object
 *
 */
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

/**
 * @brief Measure::loadFromJson
 * @param jsonObject the json object that needs to be loaded
 *
 * Load all the json values into the corresponding user
 * fillable fields
 *
 */
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
