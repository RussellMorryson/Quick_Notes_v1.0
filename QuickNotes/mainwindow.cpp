#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <string>

#include <iconvlite.h>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);    
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_saveButton_clicked() {
    if (ui->lineName->text() != QString::fromStdString("")) {

        QString qname = ui->lineName->text();
        QString qnote = ui->editNote->toPlainText();

        std::string name = qname.toStdString().data();
        std::string note = qnote.toStdString().data();

        QString qsavePath = QFileDialog::getExistingDirectory(this, "Выбор места сохранения", "C:\\");
        std::string savePath = qsavePath.toStdString().data();

        std::fstream file;
        std::string fname = savePath + "/" + name + ".txt";
        std::string ffname = utf2cp(fname);

        file.open(ffname, std::ios::app);

        if (file.is_open()) {
            file << note;
            file.close();
            QMessageBox::information(this, "Сохранено!", "Сохранение выполнено успешно!");

            ui->lineName->clear();
            ui->editNote->clear();

        } else {
            QMessageBox::warning(this, "Ошибка!", "Сохранение не выполнено!");
        }
    } else {
        QMessageBox::warning(this, "Ошибка!", "Введите название документа!");
    }
}
