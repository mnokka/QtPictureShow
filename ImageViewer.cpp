#include "ImageViewer.h"
#include <QDir>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent), currentIndex(0)
{
    setWindowTitle("Image Viewer MPN 2025");

    resize(800, 600);

    // Initialize QLabel for displaying images
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->resize(800, 600);

    imageLabel->setText(StartupMessage);
    QFont font("Arial", 30, QFont::Bold);
    imageLabel->setFont(font);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::darkRed);  // Asetetaan teksti vihreäksi
    imageLabel->setPalette(palette);

    imageLabel->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, Qt::darkGray);  // Vaihda taustaväri tummanharmaaksi
    imageLabel->setPalette(palette);

    loadImagesFromDirectory("../..");  // QtCreatorrunning inside Build directory. Check when package created!

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ImageViewer::showNextImage);
    timer->start(5000); // ms
}

void ImageViewer::showNextImage()
{
    if (!imagePaths.isEmpty()) {
        // Load and display the next image
        QImage image(imagePaths[currentIndex]);
        imageLabel->setPixmap(QPixmap::fromImage(image).scaled(imageLabel->size(), Qt::KeepAspectRatio));

        QFileInfo fileInfo(imagePaths[currentIndex]);
        setWindowTitle("Image Viewer MPN 2025 - " + fileInfo.fileName());

        // Update index to show the next image
        currentIndex = (currentIndex + 1) % imagePaths.size();
    }
}

void ImageViewer::loadImagesFromDirectory(const QString &dirPath)
{
    QDir dir(dirPath);
    dir.setNameFilters(QStringList() << "*.jpg" << "*.png" << "*.bmp");
    dir.setFilter(QDir::Files);

    imagePaths = dir.entryList();
    for (int i = 0; i < imagePaths.size(); ++i) {
        imagePaths[i] = dir.absoluteFilePath(imagePaths[i]);
        qDebug() << "Found image:" << imagePaths[i];
    }

    if (imagePaths.isEmpty()) {
        StartupMessage="No pictures found. I can't show anything!!";
        imageLabel->setText(StartupMessage);
        qDebug() << "No images found in the directory!";
        QMessageBox::warning(this, "No Images Found", "No images found in the directory! Please add images and try again.");

    }
}
