#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "include/iobserver.h"
#include "include/topinodocument.h"
#include "include/imageanalysisview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IObserver {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void modelHasChanged() final;    

  private slots:
    void onNew();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onImportImage();
    void onExportImage();
    void onQuit();

    void onAboutQt();
    void onAboutTopino();

    void onViewHasChanged();

  private:
    Ui::MainWindow *ui;

    QLabel zoomlabel;

    TopinoDocument document;
    ImageAnalysisView view;
};

#endif // MAINWINDOW_H