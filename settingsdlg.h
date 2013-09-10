#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>
#include "trbackend.h"

namespace Ui {
class SettingsDlg;
}

class TrDialog;

class SettingsDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDlg(QWidget *parent = 0);
    ~SettingsDlg();

    QList<TrBackend> backends();

signals:
    void settingsUpdated();
    
private slots:
    void reload();
    void saveSettings();
    void on_addbtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();

private:
    Ui::SettingsDlg *ui;
    TrDialog *m_trDlg;

    void setBackends(QList<TrBackend> backends);
};

#endif // SETTINGSDLG_H
