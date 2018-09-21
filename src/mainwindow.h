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

// Pre metronome
#define PRE_METRONOME_TIME_SIGNATURE_NUMERATOR_INDEX 0
#define PRE_METRONOME_TIME_SIGNATURE_DENOMINATOR_INDEX 0

// JSON Keys
#define JSON_KEY_SONG_TITLE "song_title"
#define JSON_KEY_PRE_METRONOME_ENABLED "pre_metronome_enabled"
#define JSON_KEY_PRE_METRONOME_BPM "pre_metronome_bpm"
#define JSON_KEY_PRE_METRONOME_TICKS "pre_metronome_number_of_ticks"
#define JSON_KEY_MEASURES "measures"

// Default values
#define DEFAULT_PRE_METRONOME_ENABLED true
#define DEFAULT_PRE_METRONOME_BPM 120
#define DEFAULT_PRE_METRONOME_TICKS 4
#define DEFAULT_CURRENT_PLAYING_MEASURE -1

// File extension
#define FILE_EXT_PATTERN "(*.metgs)"
#define FILE_EXT ".metgs"

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // JSON
    QJsonDocument getAsJson();
    void loadFromJson(QJsonDocument jsonObject);

    // Window
    void addMeasure(Measure *measure);
    void setCurrentFile(QString currentFile);
    void clearWindow();

    // Metronome
    void startMetronome(bool preMetronomeTicks);

private slots:
    // Metronome
    void on_metronomeMeasureCompleted();

    // Measure move
    void on_moveMeasureUp(Measure *measure);
    void on_moveMeasureDown(Measure *measure);

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

    void on_actionAbout_Advanced_Metronome_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionView_on_GitHub_triggered();

private:
    Ui::MainWindow *ui;
    QString lastSavedFile;
    Metronome* metronome;
    int currentPlayingMeasure = DEFAULT_CURRENT_PLAYING_MEASURE;
};
