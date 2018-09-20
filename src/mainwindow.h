#pragma once

#include <QMainWindow>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>

#include <QDebug>

#include "measure.h"
#include "metronome.h"
#include "merge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

#define JSON_KEY_SONG_TITLE "song_title"
#define JSON_KEY_PRE_METRONOME_ENABLED "pre_metronome_enabled"
#define JSON_KEY_PRE_METRONOME_BPM "pre_metronome_bpm"
#define JSON_KEY_PRE_METRONOME_TICKS "pre_metronome_number_of_ticks"
#define JSON_KEY_MEASURES "measures"

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QJsonObject *getAsJson();

private slots:
    // Measure move
    void on_moveMeasureUp(Measure *measure);
    void on_moveMeasureDown(Measure *measure);

    // File action menu
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();

    // Measure action menu
    void on_actionAdd_Measure_triggered();

private:
    Ui::MainWindow *ui;
    QString lastSavedFile;
    Metronome* metronome;
};
