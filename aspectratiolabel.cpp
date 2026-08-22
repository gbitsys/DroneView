#include "aspectratiolabel.h"

AspectRatioLabel::AspectRatioLabel(QWidget *parent) : QLabel(parent) {
    // Κεντράρισμα της εικόνας μέσα στο διαθέσιμο χώρο
    setAlignment(Qt::AlignCenter);

    // ΠΟΛΥ ΣΗΜΑΝΤΙΚΟ: Επιτρέπει στο layout να μικρύνει το label
    // κάτω από τις αρχικές διαστάσεις της εικόνας
    setMinimumSize(1, 1);
}

void AspectRatioLabel::setPixmap(const QPixmap &pixmap) {
    m_originalPixmap = pixmap;
    updatePixmap();
}

void AspectRatioLabel::resizeEvent(QResizeEvent *event) {
    updatePixmap();
    QLabel::resizeEvent(event); // Καλούμε τη βασική υλοποίηση
}

void AspectRatioLabel::updatePixmap() {
    if (!m_originalPixmap.isNull()) {
        // Υπολογισμός νέας εικόνας με διατήρηση αναλογιών (KeepAspectRatio)
        // και ομαλή μετατροπή (SmoothTransformation)
        QPixmap scaledPixmap = m_originalPixmap.scaled(
            size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );

        // Καλούμε την setPixmap της μητρικής κλάσης για να την εμφανίσουμε
        QLabel::setPixmap(scaledPixmap);
    }
}