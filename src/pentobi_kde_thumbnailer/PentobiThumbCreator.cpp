//-----------------------------------------------------------------------------
/** @file pentobi_kde_thumbnailer/PentobiThumbCreator.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#include "PentobiThumbCreator.h"

#include <QImage>
#include "libpentobi_thumbnail/CreateThumbnail.h"

//-----------------------------------------------------------------------------

extern "C" {

Q_DECL_EXPORT ThumbCreator* new_creator() { return new PentobiThumbCreator; }

}

//-----------------------------------------------------------------------------

PentobiThumbCreator::PentobiThumbCreator(QObject* parent)
    : QObject(parent)
{
}

PentobiThumbCreator::~PentobiThumbCreator() = default;

bool PentobiThumbCreator::create(const QString& path, int width, int height,
                                 QImage& image)
{
    image = QImage(width, height, QImage::Format_ARGB32);
    if (image.isNull())
        return false;
    image.fill(Qt::transparent);
    return createThumbnail(path, width, height, image);
}

//-----------------------------------------------------------------------------
