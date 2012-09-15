//-----------------------------------------------------------------------------
/** @file libpentobi_gui/InitialRatingDialog.cpp */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "InitialRatingDialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

//-----------------------------------------------------------------------------

InitialRatingDialog::InitialRatingDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Initial Rating"));
    // Disable '?' button in title bar on Windows, we don't have
    // context help
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    QLabel* label =
        new QLabel(tr("You have not yet played rated games in this game"
                      " variant. Estimate your playing strength to"
                      " initialize your rating."));
    label->setWordWrap(true);
    layout->addWidget(label);
    QHBoxLayout* sliderBoxLayout = new QHBoxLayout();
    layout->addLayout(sliderBoxLayout);
    sliderBoxLayout->addWidget(new QLabel(tr("Beginner")));
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setMinimum(1000);
    m_slider->setMaximum(2000);
    m_slider->setSingleStep(10);
    m_slider->setPageStep(100);
    sliderBoxLayout->addWidget(m_slider);
    sliderBoxLayout->addWidget(new QLabel(tr("Expert")));
    m_ratingLabel = new QLabel();
    layout->addWidget(m_ratingLabel);
    setRating(1000);
    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(setRating(int)));
    QDialogButtonBox* buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void InitialRatingDialog::setRating(int rating)
{
    m_rating = rating;
    m_ratingLabel->setText(tr("Your initial rating: %1").arg(rating));
}

//-----------------------------------------------------------------------------
