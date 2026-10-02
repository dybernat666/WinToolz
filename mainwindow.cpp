#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <windows.h>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void check_registry(MainWindow *self);

void MainWindow::on_reestr_check_clicked()
{
    check_registry(this);
}

void check_registry(MainWindow *self) {
    DWORD ValueCount;
    HKEY hKey;
    RegOpenKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_READ,&hKey);
    // первый параметр радотает с реестром текущего пользователя
    // второй путь к разделу , третий это доп флаги (не используются)
    // четвертый тут все понятно, пятый это куда винда будет результат класть ну запишет дескриптор раздела открытого
    RegQueryInfoKeyW(
        hKey,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &ValueCount,
        nullptr,
        nullptr,
        nullptr,
        nullptr);
    for (DWORD i = 0; i < ValueCount; i++) {
        wchar_t val[256]; // каждый раз заново создаём разммер для имени
        DWORD charito = 256; // сбрасываем размер буфера для некст записи
        RegEnumValueW(
            hKey,
            i,
            val,
            &charito,
            nullptr,
            nullptr,
            nullptr,
            nullptr);
        QString name = QString::fromWCharArray(val); // переводим сишную строку в QString, чтобы можно было склеивать текст
        QMessageBox::information(self,"result", "в реестре найдено: " + name);
        // val это буфер куда виндоус запишет имя и значение,
        // charito размер буфера
        // i- индекс текушего значения
        // nullptr тк остальные данные нам не нужны
    }
    RegCloseKey(hKey); // закрываем один раз, после цикла, а не на каждой итерации
}
void MainWindow::on_startup_clicked()
{
    QProcess process; // создаем процесс чтобы запустить питон как бы снаружи

    process.start("python", QStringList() << "code.py"); // гоним питон файл, он должен лежать рядом с exe и тд

    if (!process.waitForStarted()) { // если питон вообще не запустился (нет в path например)
        QMessageBox::information(this, "error", "питон не запустился, проверь путь и тд");
        return;
    }

    process.waitForFinished(); // ждем пока скрипт доделает свое дело

    QString output = process.readAllStandardOutput(); // забираем все что он напринтил

    QMessageBox::information(this, "result", output); // просто показываем все одним окном, крч
}


void MainWindow::on_check2_clicked()
{
    QMessageBox::information(this,"vlo","just press win + s and type task scheduler(планировщик заданий) ");
}

