#include "settingsdlg.h"
#include "ui_settingsdlg.h"
#include "trdialog.h"

#include <QSettings>
#include <QUrl>
#include <QMessageBox>

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg),
    m_trDlg(new TrDialog(this))
{
    ui->setupUi(this);

    QSettings s;
    ui->feedUrl->setText(s.value("feed").toString());
    ui->interval->setValue(s.value("refreshInterval", 1).toInt());
    ui->itemCount->setValue(s.value("itemCount", 10).toInt());
    foreach (TrBackend backend, backends()) {
        ui->listWidget->addItem(backend["host"].toString());
    }

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

    emit settingsUpdated();
}

QList<TrBackend> SettingsDlg::backends()
{
    QList<TrBackend> backends;
    QSettings s;
    foreach (QVariant b, s.value("backends").toList()) {
        backends << b.toMap();
    }
    return backends;
}

void SettingsDlg::setBackends(QList<TrBackend> backends)
{
    QSettings s;
    QList<QVariant> variant;
    foreach(TrBackend b, backends) {
        variant << QVariant::fromValue(b);
    }
    s.setValue("backends", variant);
}

void SettingsDlg::on_addbtn_clicked()
{
    m_trDlg->reset();
    if (m_trDlg->exec() != QDialog::Accepted)
        return;

    QList<TrBackend> trBackends = backends();
    TrBackend backend = m_trDlg->getBackend();
    trBackends << backend;

    setBackends(trBackends);

    ui->listWidget->addItem(backend["host"].toString());
}

void SettingsDlg::on_editBtn_clicked()
{
    if (ui->listWidget->selectedItems().size() == 0) {
        QMessageBox::warning(this, "Error", "No server selected");
        return;
    }

    int current = ui->listWidget->currentRow();

    QList<TrBackend> trBackends = backends();
    m_trDlg->loadBackend(trBackends[current]);

    if (m_trDlg->exec() != QDialog::Accepted)
        return;

    trBackends[current] = m_trDlg->getBackend();
    setBackends(trBackends);
}

void SettingsDlg::on_deleteBtn_clicked()
{
    if (ui->listWidget->selectedItems().size() == 0) {
        QMessageBox::warning(this, "Error", "No server selected");
        return;
    }

    int current = ui->listWidget->currentRow();
    QList<TrBackend> trBackends = backends();
    trBackends.takeAt(current);
    setBackends(trBackends);
    ui->listWidget->takeItem(current);
}
