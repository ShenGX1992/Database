#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QDesktopWidget> // get screen size
#include <QThread>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_updateChange_clicked();

    void on_pushButton_undo_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_displayAll_clicked();

    void on_pushButton_IDup_clicked();

    void on_pushButton_IDdown_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_addContent_clicked();

    void on_pushButton_Exit_clicked();

    void ui_button_pressed();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
