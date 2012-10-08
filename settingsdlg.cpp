#include "settingsdlg.h"
#include "ui_settingsdlg.h"

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::on_addButton_clicked()
{
    ui->feedsList->addItem(ui->newFeed->text());
}

void SettingsDlg::on_deleteButton_clicked()
{
    foreach(QListWidgetItem *feed, ui->feedsList->selectedItems()) {
        ui->feedsList->takeItem(ui->feedsList->row(feed));
    }
}
