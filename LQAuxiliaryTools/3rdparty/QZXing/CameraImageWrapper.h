#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QImage>
#include <QString>
#include <zxing/zxing/LuminanceSource.h>

using namespace zxing;

class CameraImageWrapper : public LuminanceSource
{
public:
    CameraImageWrapper();
    CameraImageWrapper(const QImage& sourceImage);
    CameraImageWrapper(CameraImageWrapper& otherInstance);
    ~CameraImageWrapper();

    static CameraImageWrapper* Factory(const QImage& image, int maxWidth=-1, int maxHeight=-1, bool smoothTransformation=false);
    
    int getWidth() const;
    int getHeight() const;
    
    bool isSmoothTransformationEnabled;

    unsigned char getPixel(int x, int y) const;
    unsigned char* copyMatrix() const;
    
    QImage grayScaleImage(QImage::Format f);
    QImage getOriginalImage();

    // Callers take ownership of the returned memory and must call delete [] on it themselves.
    ArrayRef<char> getRow(int y, ArrayRef<char> row) const;
    ArrayRef<char> getMatrix() const;

    bool setImage(QString fileName, int maxWidth, int maxHeight);
    bool setImage(QImage newImage, int maxWidth, int maxHeight);
    void scale(int maxWidth, int maxHeight);
    QImage scale_s(const QImage &image, int maxWidth, int maxHeight, bool smoothTransformation);
private:
    QImage image;
    unsigned char* pRow;
    unsigned char* pMatrix;
};

#endif //CAMERAIMAGE_H
