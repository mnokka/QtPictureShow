#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QStringList>

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);

private slots:
    void showNextImage();

private:
    QLabel *imageLabel;           // QLabel for displaying images
    QTimer *timer;                // Timer for showing the next image
    QStringList imagePaths;       // List of image paths
    int currentIndex;             // Current index of the displayed image

    // Function to load images from a directory
    void loadImagesFromDirectory(const QString &dirPath);

    QString StartupMessage = "Stay tuned,cat pictures are loading";
    int x=600;
    int y =600;

};

#endif // IMAGEVIEWER_H
