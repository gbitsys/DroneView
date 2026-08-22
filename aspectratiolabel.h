/*
Class made to keep the aspect ratio of an image (QLabel)

*/


#ifndef ASPECTRATIOLABEL_H
#define ASPECTRATIOLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioLabel : public QLabel {
    Q_OBJECT
public:
    explicit AspectRatioLabel(QWidget *parent = nullptr);

    // Κάνουμε override την setPixmap για να αποθηκεύουμε την αρχική εικόνα
    void setPixmap(const QPixmap &pixmap);

protected:
    // Το event που καλείται όταν αλλάζει μέγεθος το παράθυρο/container
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap m_originalPixmap;
    void updatePixmap();
};

#endif // ASPECTRATIOLABEL_H
