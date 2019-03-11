#ifndef POLYFITLABEL_H
#define POLYFITLABEL_H
#include <QLabel>

class PolyfitLabel : public QLabel
{

    Q_OBJECT
public:
    explicit PolyfitLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit PolyfitLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    ~PolyfitLabel() override;

    void updateData(float* data, int size);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    float       *mpPointData;
    int         mPointSize;
};

#endif // POLYFITLABEL_H
