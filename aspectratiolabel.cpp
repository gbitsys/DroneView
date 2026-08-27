#include "aspectratiolabel.h"

AspectRatioLabel::AspectRatioLabel(QWidget *parent) : QLabel(parent) {
    setAlignment(Qt::AlignCenter);
    setMinimumSize(1, 1);
}

void AspectRatioLabel::setPixmap(const QPixmap &pixmap) {
    m_originalPixmap = pixmap;
    updatePixmap();
}

void AspectRatioLabel::resizeEvent(QResizeEvent *event) {
    updatePixmap();
    QLabel::resizeEvent(event);
}

void AspectRatioLabel::updatePixmap() {
    if (!m_originalPixmap.isNull()) {
        QPixmap scaledPixmap = m_originalPixmap.scaled(
            size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );
        QLabel::setPixmap(scaledPixmap);
    }
}