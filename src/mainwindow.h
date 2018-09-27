#pragma once

#include <QMainWindow>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

#include <QDebug>

#include "measure.h"
#include "metronome.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

// URI's
#define URI_GITHUB "https://github.com/bartkessels/AdvancedMetronome"

// File extension
#define FILE_EXT_PATTERN "(*.metgs)"
#define FILE_EXT ".metgs"

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // File
    bool openFile(QString filePath);
    bool saveFile(QString filePath);

private:

    // JSON
    QJsonDocument getJsonDocument();
    bool loadFromJson(QJsonDocument jsonDocument);

    // Window
    void clearWindow();
    void swapMeasures(int widgetOne, int widgetTwo);

private slots:

    // Metronome
    void on_metronomeTick(int totalRepetitions, int currentRepetition);
    void on_metronomeAddMeasure(IMeasure *measure);
    void on_metronomeChangeMeasure(IMeasure *measure);
    void on_metronomeStop();

    // Measure
    void on_measureMoveUp(IMeasure *measure);
    void on_measureMoveDown(IMeasure *measure);

    // File action menu
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();

    // Metronome action menu
    void on_actionPlay_triggered();
    void on_actionStop_triggered();

    // Measure action menu
    void on_actionAdd_Measure_triggered();

    // Help action menu
    void on_actionAbout_Advanced_Metronome_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionView_on_GitHub_triggered();

private:
    Ui::MainWindow *ui;
    QString lastSavedFile;
    IMetronome *metronome;

    // JSON keys
    const char* JSON_KEY_TITLE = "song_title";
    const char* JSON_KEY_PRE_METRONOME_ENABLED = "pre_metronome_enabled";
    const char* JSON_KEY_PRE_METRONOME_BPM = "pre_metronome_bpm";
    const char* JSON_KEY_PRE_METRONOME_TICKS = "pre_metronome_number_of_ticks";
    const char* JSON_KEY_MEASURES = "measures";

    // Default values
    const bool DEFAULT_PRE_METRONOME_ENABLED = true;
    const int DEFAULT_PRE_METRONOME_BPM = 120;
    const int DEFAULT_PRE_METRONOME_TICKS = 4;
    const QString DEFAULT_NONE_VALUE = tr("(none)");
    const int DEFAULT_REPETITIONS_UNTIL_NEXT_MEASURE = 0;
};
