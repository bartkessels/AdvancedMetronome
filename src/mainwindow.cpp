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
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyTick(int,int)), this, SLOT(on_metronomeTick(int,int)));
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyAddMeasure(IMeasure*)), this, SLOT(on_metronomeAddMeasure(IMeasure*)));
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyChangeMeasure(IMeasure*)), this, SLOT(on_metronomeChangeMeasure(IMeasure*)));
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyStop()), this, SLOT(on_metronomeStop()));
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyMeasureMoveUp(IMeasure*)), this, SLOT(on_measureMoveUp(IMeasure*)));
    connect(dynamic_cast<QObject*>(metronome), SIGNAL(notifyMeasureMoveDown(IMeasure*)), this, SLOT(on_measureMoveDown(IMeasure*)));

    // Setup vertical / horizontal layouts
    ui->hLayout_currentFile->setAlignment(Qt::AlignLeft);
    ui->hLayout_currentPlayingMeasure->setAlignment(Qt::AlignLeft);
    ui->hLayout_repeitionsUntilNextMeasure->setAlignment(Qt::AlignLeft);
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
// File

bool MainWindow::openFile(QString filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Opening File"), tr("The selected file does not exist"));
        return false;
    }

    QString fileContents = QString(file.readAll());
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileContents.toUtf8());
    file.flush();
    file.close();

    bool fileOpened = loadFromJson(jsonDocument);

    if (!fileOpened) {
        QMessageBox::warning(this, tr("Opening File"), tr("The selected file is not a valid Advanced Metronome file"));
        return false;
    }

    lastSavedFile = filePath;
    ui->lbl_currentFile->setText(lastSavedFile);

    return true;
}

bool MainWindow::saveFile(QString filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QJsonDocument document = getJsonDocument();

        file.write(document.toJson());
        file.flush();
        file.close();

        return true;
    }

    return false;
}


// =============================================================================
// JSON

bool MainWindow::loadFromJson(QJsonDocument jsonDocument)
{
    // Invalid JSON
    if (jsonDocument.isNull() || !jsonDocument.isObject()) {
        return false;
    }

    clearWindow();

    QJsonObject jsonObject = jsonDocument.object();
    QString songTitle = jsonObject.value(JSON_KEY_TITLE).toString();
    bool preMetronomeEnabled = jsonObject.value(JSON_KEY_PRE_METRONOME_ENABLED).toBool();
    int preMetronomeBeatsPerMinute = jsonObject.value(JSON_KEY_PRE_METRONOME_BPM).toInt();
    int preMetronomeNumberOfTicks = jsonObject.value(JSON_KEY_PRE_METRONOME_TICKS).toInt();
    QJsonArray jsonArrayMeasures = jsonObject.value(JSON_KEY_MEASURES).toArray();
    metronome->loadMeasuresFromJson(jsonArrayMeasures);

    ui->le_songTitle->setText(songTitle);
    ui->cb_usePreMetronomeTicks->setChecked(preMetronomeEnabled);
    ui->spn_preMetronomeBeatsPerMinute->setValue(preMetronomeBeatsPerMinute);
    ui->spn_preMetronomeNumberOfTicks->setValue(preMetronomeNumberOfTicks);

    return true;
}

QJsonDocument MainWindow::getJsonDocument()
{
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QString songTitle = ui->le_songTitle->text();
    bool preMetronomeEnabled = ui->cb_usePreMetronomeTicks->isChecked();
    int preMetronomeBeatsPerMinute = ui->spn_preMetronomeBeatsPerMinute->value();
    int preMetronomeNumberOfTicks= ui->spn_preMetronomeNumberOfTicks->value();
    QJsonArray jsonArrayMeasures = metronome->getMeasuresAsJson();

    jsonObject.insert(JSON_KEY_TITLE, songTitle);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_ENABLED, preMetronomeEnabled);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_BPM, preMetronomeBeatsPerMinute);
    jsonObject.insert(JSON_KEY_PRE_METRONOME_TICKS, preMetronomeNumberOfTicks);
    jsonObject.insert(JSON_KEY_MEASURES, jsonArrayMeasures);
    jsonDocument.setObject(jsonObject);

    return jsonDocument;
}

// =============================================================================
// Window

void MainWindow::clearWindow()
{
    // Clear song
    ui->le_songTitle->clear();
    ui->cb_usePreMetronomeTicks->setChecked(DEFAULT_PRE_METRONOME_ENABLED);
    ui->spn_preMetronomeBeatsPerMinute->setValue(DEFAULT_PRE_METRONOME_BPM);
    ui->spn_preMetronomeNumberOfTicks->setValue(DEFAULT_PRE_METRONOME_TICKS);

    // Delete metronome
    metronome->deleteMeasures();

    // Clear file
    lastSavedFile.clear();
    ui->lbl_currentFile->setText(DEFAULT_NONE_VALUE);
    ui->lbl_currentPlayingMeasure->setText(DEFAULT_NONE_VALUE);
}

// =============================================================================
// Slots

void MainWindow::on_metronomeTick(int totalRepetitions, int currentRepetition)
{
    qInfo() << "on_metronomeTick";

    if (currentRepetition > totalRepetitions) {
        return;
    }

    int repetitionsLeft = totalRepetitions - currentRepetition;

    ui->lbl_repetitionsUntilNextMeasure->setText(
                QString::number(repetitionsLeft));

}

void MainWindow::on_metronomeAddMeasure(IMeasure *measure)
{
    if (measure != NULL) {
        ui->vLayout_measures->addWidget(dynamic_cast<QWidget*>(measure));
    }
}

/**
 * @brief MainWindow::on_metronomeChangeMeasure
 * @param newMeasure the measure that is being played right now
 *
 * Display the title of the currently playing measure on the
 * screen
 *
 */
void MainWindow::on_metronomeChangeMeasure(IMeasure *newMeasure)
{

    if (newMeasure == NULL) {
        ui->lbl_currentPlayingMeasure->setText(DEFAULT_NONE_VALUE);
        return;
    }

    ui->lbl_currentPlayingMeasure->setText(newMeasure->getTitle());
}

void MainWindow::on_metronomeStop()
{
    qInfo() << "on_metronomeStop";

    ui->lbl_currentPlayingMeasure->setText(DEFAULT_NONE_VALUE);
    ui->lbl_repetitionsUntilNextMeasure->setText(
                QString::number(DEFAULT_REPETITIONS_UNTIL_NEXT_MEASURE));
}

void MainWindow::on_measureMoveUp(IMeasure *measure)
{
    QWidget *currentWidget = dynamic_cast<QWidget*>(measure);

    if (currentWidget == NULL) {
        qInfo() << "Current widget is NULL";
        return;
    }

    int totalWidgets = ui->vLayout_measures->count();
    int currentIndex = ui->vLayout_measures->indexOf(currentWidget);
    int nextIndex = currentIndex + 1;

    if (nextIndex < totalWidgets) {
        QWidget *nextWidget= ui->vLayout_measures->itemAt(nextIndex)->widget();

        // Switch the measures
        if (nextWidget != NULL) {
            ui->vLayout_measures->insertWidget(currentIndex, nextWidget);
            ui->vLayout_measures->insertWidget(nextIndex, currentWidget);
        }
    }
}

void MainWindow::on_measureMoveDown(IMeasure *measure)
{

    QWidget *currentWidget = dynamic_cast<QWidget*>(measure);

    if (currentWidget == NULL) {
        qInfo() << "Current widget is NULL";
        return;
    }

    int currentIndex = ui->vLayout_measures->indexOf(currentWidget);
    int previousIndex = currentIndex - 1;

    if (previousIndex >= 0) {
        QWidget *previousWidget = ui->vLayout_measures->itemAt(previousIndex)->widget();

        // Switch the measures
        if (previousWidget != NULL) {
            ui->vLayout_measures->insertWidget(previousIndex, currentWidget);
            ui->vLayout_measures->insertWidget(currentIndex, previousWidget);
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

    openFile(lastSavedFile);
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
        saveFile(saveFileDialog.selectedFiles().first());
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
        openFile(openFileDialog.selectedFiles().first());
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
    int preMetronomeBpm = ui->spn_preMetronomeBeatsPerMinute->value();
    int preMetronomeTicks = ui->spn_preMetronomeNumberOfTicks->value();

    metronome->setupPreMetronome(preMetronomeBpm, preMetronomeTicks);
    metronome->start(usePreMetronome);
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
    metronome->addMeasure();
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
