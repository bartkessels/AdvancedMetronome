#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>

#include "metronome.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->vLayout_information->setAlignment(Qt::AlignTop);
    ui->vLayout_measures->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QJsonObject *MainWindow::getAsJson()
{
    QJsonObject *jsonObject = new QJsonObject();
    QString songTitle = ui->le_songTitle->text();
    bool preMetronomeEnabled = ui->cb_usePreMetronomeTicks->isChecked();
    int preMetronomeBeatsPerMinute = ui->spn_preMetronomeBeatsPerMinute->value();
    int preMetronomeNumberOfTicks= ui->spn_preMetronomeNumberOfTicks->value();
    QJsonArray *jsonArrayMeasures = new QJsonArray();

    // Iterate over measures
    for (int i = 0; i < ui->vLayout_measures->count(); i++) {
        QWidget *measureWidget = ui->vLayout_measures->itemAt(i)->widget();
        Measure* measure = dynamic_cast<Measure*>(measureWidget);

        if (measure != NULL) {
            jsonArrayMeasures->insert(i, *measure->getAsJsonObject());
        }
    }

    jsonObject->insert(JSON_KEY_SONG_TITLE, songTitle);
    jsonObject->insert(JSON_KEY_PRE_METRONOME_ENABLED, preMetronomeEnabled);
    jsonObject->insert(JSON_KEY_PRE_METRONOME_BPM, preMetronomeBeatsPerMinute);
    jsonObject->insert(JSON_KEY_PRE_METRONOME_TICKS, preMetronomeNumberOfTicks);
    jsonObject->insert(JSON_KEY_MEASURES, *jsonArrayMeasures);

    return jsonObject;
}

// =============================================================================
// Measure move
void MainWindow::on_moveMeasureUp(Measure *measure)
{
    int currentIndex = ui->vLayout_measures->indexOf(measure);
    int previousIndex = currentIndex - 1;

    if (previousIndex >= 0) {
        Measure *previousMeasure = dynamic_cast<Measure*>(
                    ui->vLayout_measures->itemAt(previousIndex)->widget());

        // Switch the measures
        if (previousMeasure != NULL) {
            ui->vLayout_measures->insertWidget(previousIndex, measure);
            ui->vLayout_measures->insertWidget(currentIndex, previousMeasure);
        }
    }
}

void MainWindow::on_moveMeasureDown(Measure *measure)
{
    int currentIndex = ui->vLayout_measures->indexOf(measure);
    int nextIndex = currentIndex + 1;

    if (nextIndex < ui->vLayout_measures->count()) {
        Measure *nextMeasure = dynamic_cast<Measure*>(
                    ui->vLayout_measures->itemAt(nextIndex)->widget());

        // Switch the measures
        if (nextMeasure != NULL) {
            ui->vLayout_measures->insertWidget(currentIndex, nextMeasure);
            ui->vLayout_measures->insertWidget(nextIndex, measure);
        }
    }
}

// =============================================================================
// File action menu

void MainWindow::on_actionSave_triggered()
{

    if (lastSavedFile.length() <= 0) {
        on_actionSave_As_triggered();
        return;
    }

    QFile file(lastSavedFile);

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QJsonObject *jsonObject = getAsJson();
        QJsonDocument document(*jsonObject);

        file.write(document.toJson());
        file.flush();
        file.close();

        delete jsonObject;
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QFileDialog saveFileDialog(this, tr("Save Advanced Metronome Song"));
    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveFileDialog.setNameFilter(tr("Advanced Metronome Song") + "(*.ams)");
    saveFileDialog.setDefaultSuffix(".ams");
    saveFileDialog.exec();

    if (saveFileDialog.selectedFiles().length() > 0) {
        lastSavedFile = saveFileDialog.selectedFiles().first();
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    // Open
}

// =============================================================================
// Metronome action menu

// =============================================================================
// Measure action menu

void MainWindow::on_actionAdd_Measure_triggered()
{
    // Add
    Measure *measure = new Measure(this);
    connect(measure, &Measure::moveMeasureUp, this, &MainWindow::on_moveMeasureUp);
    connect(measure, &Measure::moveMeasureDown, this, &MainWindow::on_moveMeasureDown);

    ui->vLayout_measures->addWidget(measure);
}
