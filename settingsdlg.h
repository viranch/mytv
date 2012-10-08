#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDlg(QWidget *parent = 0);
    ~SettingsDlg();

signals:
    void settingsUpdated();
    
private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void saveSettings();

private:
    Ui::SettingsDlg *ui;
};

#endif // SETTINGSDLG_H