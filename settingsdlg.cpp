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
    ui->feedUrl->setText(s.value("feed").toString());
    ui->interval->setValue(s.value("refreshInterval", 1).toInt());
    ui->itemCount->setValue(s.value("itemCount", 10).toInt());
    ui->searchSuffix->setText(s.value("searchSuffix").toString());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::saveSettings()
{
    QSettings s;
    s.setValue("feed", ui->feedUrl->text());
    s.setValue("refreshInterval", ui->interval->value());
    s.setValue("itemCount", ui->itemCount->value());
    s.setValue("searchSuffix", ui->searchSuffix->text());

    emit settingsUpdated();
}
