#ifndef GSTVIDEOWIDGET_H
#define GSTVIDEOWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QImage>

class GstVideoWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    explicit GstVideoWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

public slots:
    void updateFrame(const QImage &image) {
        currentFrame = image;
        update(); // calling paintGL()
    }

protected:
    void paintGL() override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::black); // filling background with black color
        // in case of different aspect ratio there is no distortion in the image (letterboxing)

        if (!currentFrame.isNull()) {
            QImage scaledImage = currentFrame.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // Qt::KeepAspectRatio scaling while keeping ratio
            // Qt::SmoothTransformation anti-aliasing
            int x = (width() - scaledImage.width()) / 2; // for centering the image at x axis
            int y = (height() - scaledImage.height()) / 2; // for centering the image at y axis
            painter.drawImage(x, y, scaledImage);
        }
    }

private:
    QImage currentFrame;
};

#endif // GSTVIDEOWIDGET_H