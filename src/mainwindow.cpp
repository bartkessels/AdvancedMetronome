#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>

#include "metronome.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    metronome(new Metronome(this))
{
    ui->setupUi(this);

    // Connect signals
    connect(metronome, &Metronome::measureEnded,
            this, &MainWindow::on_metronomeMeasureCompleted);

    // Setup vertical / horizontal layouts
    ui->hLayout_currentFile->setAlignment(Qt::AlignLeft);
    ui->hLayout_currentPlayingMeasure->setAlignment(Qt::AlignLeft);
    ui->vLayout_information->setAlignment(Qt::AlignTop);
    ui->vLayout_measures->setAlignment(Qt::AlignTop);

    // Start with empty state
    clearWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// =============================================================================
// Metronome

/**
 * @brief MainWindow::startMetronome
 * @param preMetronomeTicks wheter or not there should be pre-metronome ticks
 *
 * Start the metronome and check if pre-metronome ticks should be
 * added to the metronome; the default pre-metronome ticks have a
 * time-signature of 1/1
 *
 * If there shouldn't be pre-metronome ticks this method will delegate
 * the loading of a measure to another method
 *
 */
void MainWindow::startMetronome(bool preMetronomeTicks)
{
    currentPlayingMeasure = DEFAULT_CURRENT_PLAYING_MEASURE;

    if (preMetronomeTicks) {
        int beatsPerMinute = ui->spn_preMetronomeBeatsPerMinute->value();
        int numberOfRepeats = ui->spn_preMetronomeNumberOfTicks->value();

        Measure *preMetronome = new Measure();
        preMetronome->setBeatsPerMinute(beatsPerMinute);
        preMetronome->setNumberOfRepeats(numberOfRepeats);
        preMetronome->setNumeratorIndex(PRE_METRONOME_TIME_SIGNATURE_NUMERATOR_INDEX);
        preMetronome->setDenominatorIndex(PRE_METRONOME_TIME_SIGNATURE_DENOMINATOR_INDEX);

        metronome->setMeasure(preMetronome);
    } else {
        playNextMeasure();
    }

    metronome->start();
}

// =============================================================================
// Measure

/**
 * @brief MainWindow::nextMetronomeMeasure
 *
 * If a measure is completed check if another measure is
 * waiting to be played, if so update the measure in the
 * metronome object and continue, if there aren't any more
 * measures stop the metronome
 *
 */
void MainWindow::playNextMeasure()
{
    currentPlayingMeasure++;
    if (currentPlayingMeasure < ui->vLayout_measures->count()) {

        QWidget *measureWidget = ui->vLayout_measures->itemAt(currentPlayingMeasure)->widget();
        Measure *measure = dynamic_cast<Measure*>(measureWidget);

        if (measure != NULL) {
            metronome->setMeasure(measure);
        }
    } else {
        metronome->stop();
    }

    setCurrentPlayingMeasure();
}

void MainWindow::setCurrentPlayingMeasure()
{
    QString title = tr("(none)");

    if (currentPlayingMeasure < ui->vLayout_measures->count()) {

        QWidget *measureWidget = ui->vLayout_measures->itemAt(currentPlayingMeasure)->widget();
        Measure *measure = dynamic_cast<Measure*>(measureWidget);

        title = measure->getTitle();
    }

    ui->lbl_currentPlayingMeasure->setText(title);
}

// =============================================================================
// Metronome slots

/**
 * @brief MainWindow::on_metronomeMeasureCompleted
 *
 * If the metronome notifies that a measure is completed
 * delegate a check for a new measure to another
 * method
 *
 */
void MainWindow::on_metronomeMeasureCompleted()
{
    playNextMeasure();
}

// =============================================================================
// JSON

/**
 * @brief MainWindow::getAsJson
 * @return a jsonDocument representation of the entered data
 *
 * Get all the data the user has entered into the application and
 * all the measures the user has added
 *
 */
QJsonDocument MainWindow::getAsJson()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QString songTitle = ui->le_songTitle->text();
    bool preMetronomeEnabled = ui->cb_usePreMetronomeTicks->isChecked();
    int preMetronomeBeatsPerMinute = ui->spn_preMetronomeBeatsPerMinute->value();
    int preMetronomeNumberOfTicks= ui->spn_preMetronomeNumberOfTicks->value();
    QJsonArray jsonArrayMeasures;

    // Iterate over measures
    for (int i = 0; i < ui->vLayout_measures->count(); i++) {
        QWidget *measureWidget = ui->vLayout_measures->itemAt(i)->widget();
        Measure *measure = dynamic_cast<Measure*>(measureWidget);
        jsonArrayMeasures.insert(i, measure->getAsJsonObject());
    }

    jsonObject.insert(JSON_KEY_SONG_TITLE, songTitle);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_ENABLED, preMetronomeEnabled);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_BPM, preMetronomeBeatsPerMinute);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_TICKS, preMetronomeNumberOfTicks);
    jsonObject.insert(JSON_KEY_MEASURES, jsonArrayMeasures);
    jsonDocument.setObject(jsonObject);

    return jsonDocument;
}

/**
 * @brief MainWindow::loadFromJson
 * @param jsonDocument the jsonDocument with all values
 *
 * Set values from json to the fields the user can edit,
 * this method also iterates over the measures array but
 * does not set the values for each measure
 *
 */
void MainWindow::loadFromJson(QString filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Opening File"), tr("The selected file does not exist"));
        return;
    }

    QString fileContents = QString(file.readAll());
    QJsonDocument document = QJsonDocument::fromJson(fileContents.toUtf8());
    file.flush();
    file.close();

    // Invalid JSON
    if (document.isNull() || !document.isObject()) {
        QMessageBox::warning(this, tr("Opening File"), tr("The selected file is not a valid Advanced Metronone file"));
        return;
    }

    clearWindow();
    setCurrentFile(filePath);

    QJsonObject jsonObject = document.object();
    QString songTitle = jsonObject.value(JSON_KEY_SONG_TITLE).toString();
    bool preMetronomeEnabled = jsonObject.value(JSON_KEY_PRE_METRONOME_ENABLED).toBool();
    int preMetronomeBeatsPerMinute = jsonObject.value(JSON_KEY_PRE_METRONOME_BPM).toInt();
    int preMetronomeNumberOfTicks = jsonObject.value(JSON_KEY_PRE_METRONOME_TICKS).toInt();
    QJsonArray jsonArrayMeasures = jsonObject.value(JSON_KEY_MEASURES).toArray();

    for (int i = 0; i < jsonArrayMeasures.count(); i++) {
        QJsonObject jsonMeasure = jsonArrayMeasures.at(i).toObject();
        addMeasure(new Measure(jsonMeasure, this));
    }

    ui->le_songTitle->setText(songTitle);
    ui->cb_usePreMetronomeTicks->setChecked(preMetronomeEnabled);
    ui->spn_preMetronomeBeatsPerMinute->setValue(preMetronomeBeatsPerMinute);
    ui->spn_preMetronomeNumberOfTicks->setValue(preMetronomeNumberOfTicks);
}

// =============================================================================
// Window

/**
 * @brief MainWindow::addMeasure
 * @param measure the measure to add
 *
 * Add a measure to the measures list and connect all the required
 * signals for the up/down buttons
 *
 */
void MainWindow::addMeasure(Measure *measure)
{
    connect(measure, &Measure::moveMeasureUp, this, &MainWindow::on_moveMeasureUp);
    connect(measure, &Measure::moveMeasureDown, this, &MainWindow::on_moveMeasureDown);

    ui->vLayout_measures->addWidget(measure);
}

/**
 * @brief MainWindow::setCurrentFile
 * @param currentFile the file that is being edited
 *
 * Update the member variable and UI to make sure
 * the location of the currently edited file is
 * being saved
 *
 */
void MainWindow::setCurrentFile(QString currentFile)
{
    ui->lbl_currentFile->setText(currentFile);
    lastSavedFile = currentFile;
}

/**
 * @brief MainWindow::clearWindow
 *
 * Set all song elements to their default values and remove
 * all measures
 *
 */
void MainWindow::clearWindow()
{
    // Clear song
    ui->le_songTitle->clear();
    ui->cb_usePreMetronomeTicks->setChecked(DEFAULT_PRE_METRONOME_ENABLED);
    ui->spn_preMetronomeBeatsPerMinute->setValue(DEFAULT_PRE_METRONOME_BPM);
    ui->spn_preMetronomeNumberOfTicks->setValue(DEFAULT_PRE_METRONOME_TICKS);

    // Clear measures
    for (int i = 0; i < ui->vLayout_measures->count(); i++) {
        ui->vLayout_measures->itemAt(i)->widget()->deleteLater();
    }

    // Clear file
    lastSavedFile.clear();
    ui->lbl_currentFile->setText(tr("(none)"));
}

// =============================================================================
// Measure move

/**
 * @brief MainWindow::on_moveMeasureUp
 * @param measure the measure that needs to be moved up
 *
 * Move the measure that is being given one position up
 * if the measure isn't already at the top
 *
 */
void MainWindow::on_moveMeasureUp(Measure *measure)
{
    int currentIndex = ui->vLayout_measures->indexOf(measure);
    int previousIndex = currentIndex - 1;

    if (previousIndex >= 0) {
        QWidget *measureWidget = ui->vLayout_measures->itemAt(previousIndex)->widget();
        Measure *previousMeasure = dynamic_cast<Measure*>(measureWidget);

        // Switch the measures
        if (previousMeasure != NULL) {
            ui->vLayout_measures->insertWidget(previousIndex, measure);
            ui->vLayout_measures->insertWidget(currentIndex, previousMeasure);
        }
    }
}

/**
 * @brief MainWindow::on_moveMeasureDown
 * @param measure the measure that needs to be moved down
 *
 * Move the measure that is being given one position down
 * if the measure isn't already at the bottom
 *
 */
void MainWindow::on_moveMeasureDown(Measure *measure)
{
    int currentIndex = ui->vLayout_measures->indexOf(measure);
    int nextIndex = currentIndex + 1;

    if (nextIndex < ui->vLayout_measures->count()) {
        QWidget *measureWidget = ui->vLayout_measures->itemAt(nextIndex)->widget();
        Measure *nextMeasure = dynamic_cast<Measure*>(measureWidget);

        // Switch the measures
        if (nextMeasure != NULL) {
            ui->vLayout_measures->insertWidget(currentIndex, nextMeasure);
            ui->vLayout_measures->insertWidget(nextIndex, measure);
        }
    }
}

// =============================================================================
// File action menu

/**
 * @brief MainWindow::on_actionNew_triggered
 *
 * This method displays a dialog to the user if a file is being
 * edited, if the user still wants to continue creating a new file
 * then the actual clearing of the window is being delegated to another
 * method
 *
 */
void MainWindow::on_actionNew_triggered()
{
    // Check if a file is opened
    if (lastSavedFile != NULL && lastSavedFile.length() > 0) {
        int reply = QMessageBox::question(this, "Create new song", tr("It looks like you have a file opened, are you sure you want to create a new song?"), QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            clearWindow();
        }
    }
}

/**
 * @brief MainWindow::on_actionSave_triggered
 *
 * This method checks if a file is already being
 * edited, if that's the case then it delegates
 * the writing of the file to another method,
 * if there isn't a file being edited is calls
 * the method that always shows a save file dialog
 *
 */
void MainWindow::on_actionSave_triggered()
{
    if (lastSavedFile.length() <= 0) {
        on_actionSave_As_triggered();
        return;
    }

    QFile file(lastSavedFile);

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QJsonDocument document = getAsJson();

        file.write(document.toJson());
        file.flush();
        file.close();
    }
}

/**
 * @brief MainWindow::on_actionSave_As_triggered
 *
 * This method always displays a save file dialog,
 * the actual writing of the file is delegated
 * to another method
 *
 */
void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog saveFileDialog(this, tr("Save Advanced Metronome Song"));
    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveFileDialog.setNameFilter(tr("Advanced Metronome Song") + FILE_EXT_PATTERN);
    saveFileDialog.setDefaultSuffix(FILE_EXT);
    int result = saveFileDialog.exec();

    if (result == QMessageBox::Accepted &&
            saveFileDialog.selectedFiles().length() > 0) {
        setCurrentFile(saveFileDialog.selectedFiles().first());
        on_actionSave_triggered();
    }
}

/**
 * @brief MainWindow::on_actionOpen_triggered
 *
 * This method displays the open file dialog
 * and delegates the opening/reading of the
 * file to another method
 *
 */
void MainWindow::on_actionOpen_triggered()
{
    // Open
    QFileDialog openFileDialog(this, tr("Open Advanced Metronome Song"));
    openFileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openFileDialog.setNameFilter(tr("Advanced Metronome Song") + FILE_EXT_PATTERN);
    int result = openFileDialog.exec();

    if (result == QMessageBox::Accepted &&
            openFileDialog.selectedFiles().length() > 0) {
        QString selectedFile = openFileDialog.selectedFiles().first();
        loadFromJson(selectedFile);
    }
}

// =============================================================================
// Metronome action menu

/**
 * @brief MainWindow::on_actionPlay_triggered
 *
 * Delegate the starting of the metronome to another
 * method while passing in wheter or not the pre-metronome
 * should be used
 *
 */
void MainWindow::on_actionPlay_triggered()
{
    bool usePreMetronome = ui->cb_usePreMetronomeTicks->isChecked();
    startMetronome(usePreMetronome);
}

/**
 * @brief MainWindow::on_actionStop_triggered
 *
 * Stop the metronome
 *
 */
void MainWindow::on_actionStop_triggered()
{
    metronome->stop();
}

// =============================================================================
// Measure action menu

/**
 * @brief MainWindow::on_actionAdd_Measure_triggered
 *
 * Delegate the creation and adding of a new measure object
 * to another method
 *
 */
void MainWindow::on_actionAdd_Measure_triggered()
{
    addMeasure(new Measure(this));
}

// =============================================================================
// Help action menu

/**
 * @brief MainWindow::on_actionAbout_Advanced_Metronome_triggered
 *
 * Show about dialog for Advanced Metronome
 *
 */
void MainWindow::on_actionAbout_Advanced_Metronome_triggered()
{
    QMessageBox::about(this, tr("About Advanced Metronome"), tr("Advanced Metronome is created for musicians who want to practice songs which "
                                                                "have multiple speeds and/or time-durations. 'Cause regular metronomes only "
                                                                "allow one constant tempo Advanced Metronome steps in to solve this problem.\n\n"
                                                                "Advanced Metronome also gives you the ability to save and share your songs "
                                                                "with others so this application will suit many bands in their song-writing "
                                                                "process."));
}

/**
 * @brief MainWindow::on_actionAbout_Qt_triggered
 *
 * Show about dialog for Qt
 *
 */
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

/**
 * @brief MainWindow::on_actionView_on_GitHub_triggered
 *
 * Open the github page
 *
 */
void MainWindow::on_actionView_on_GitHub_triggered()
{
    QDesktopServices::openUrl(QUrl(URI_GITHUB));
}
