//-----------------------------------------------------------------------------
/** @file libpentobi_gui/SameHeightLayout.h
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifndef LIBPENTOBI_GUI_SAME_HEIGHT_LAYOUT_H
#define LIBPENTOBI_GUI_SAME_HEIGHT_LAYOUT_H

// Needed in the header because moc_*.cxx does not include config.h
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QLayout>

//-----------------------------------------------------------------------------

/** Layout that assigns exactly the same height to all items.
    Needed for the box containing the piece selectors, because QBoxLayout
    and QGridLayout do not always assign the exact same height to all items
    if the height is not a multiple of the number of items. */
class SameHeightLayout
    : public QLayout
{
    Q_OBJECT

public:
    explicit SameHeightLayout(QWidget* parent = nullptr);

    ~SameHeightLayout();

    void addItem(QLayoutItem* item) override;

    QSize sizeHint() const override;

    QSize minimumSize() const override;

    int count() const override;

    QLayoutItem* itemAt(int i) const override;

    QLayoutItem* takeAt(int i) override;

    void setGeometry(const QRect& rect) override;

private:
    QList<QLayoutItem*> m_list;

    int getSpacing() const;
};

//-----------------------------------------------------------------------------

#endif // LIBPENTOBI_GUI_SAME_HEIGHT_LAYOUT_H
