#include "settingsdlg.h"
#include "ui_settingsdlg.h"

#include <QSettings>
#include <QUrl>

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);

    QSettings s;
    QList<QVariant> urls = s.value("feeds").toList();
    foreach(QVariant feed, urls) {
        ui->feedsList->addItem(feed.toUrl().toString());
    }
    ui->interval->setValue(s.value("refreshInterval", 1).toInt());
    ui->itemCount->setValue(s.value("itemCount", 10).toInt());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::on_addButton_clicked()
{
    QUrl url(ui->newFeed->text());
    ui->feedsList->addItem(ui->newFeed->text());
    ui->newFeed->clear();
}

void SettingsDlg::on_deleteButton_clicked()
{
    foreach(QListWidgetItem *feed, ui->feedsList->selectedItems()) {
        ui->feedsList->takeItem(ui->feedsList->row(feed));
    }
}

void SettingsDlg::saveSettings()
{
    QList<QVariant> urls;
    for(int i=0; i<ui->feedsList->count(); i++) {
        urls << QUrl(ui->feedsList->item(i)->text());
    }

    QSettings s;
    s.setValue("feeds", urls);
    s.setValue("refreshInterval", ui->interval->value());
    s.setValue("itemCount", ui->itemCount->value());

    emit settingsUpdated();
}
