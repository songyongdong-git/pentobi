//-----------------------------------------------------------------------------
/** @file pentobi/RatingDialog.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "RatingDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include "Util.h"

//-----------------------------------------------------------------------------

QLabel* createSelectableLabel()
{
    auto label = new QLabel;
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    return label;
}

//-----------------------------------------------------------------------------

RatingDialog::RatingDialog(QWidget* parent, RatingHistory& history)
    : QDialog(parent),
      m_history(history)
{
    setWindowTitle(tr("Rating"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    auto layout = new QVBoxLayout;
    setLayout(layout);
    auto formLayout = new QFormLayout;
    layout->addLayout(formLayout);
    formLayout->setLabelAlignment(Qt::AlignLeft);
    auto box = new QHBoxLayout;
    m_labelRating = createSelectableLabel();
    box->addWidget(m_labelRating);
    box->addStretch();
    formLayout->addRow(tr("Your rating:"), box);
    m_labelVariant = createSelectableLabel();
    formLayout->addRow(tr("Game variant:"), m_labelVariant);
    m_labelNuGames = createSelectableLabel();
    formLayout->addRow(tr("Rated games:"), m_labelNuGames);
    m_labelBestRating = createSelectableLabel();
    formLayout->addRow(tr("Best previous rating:"), m_labelBestRating);
    layout->addSpacing(layout->margin());
    layout->addWidget(new QLabel(tr("Recent development:")));
    m_graph = new RatingGraph;
    layout->addWidget(m_graph, 1);
    layout->addSpacing(layout->margin());
    layout->addWidget(new QLabel(tr("Recent games:")));
    m_list = new RatedGamesList;
    layout->addWidget(m_list, 1);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    layout->addWidget(buttonBox);
    m_clearButton =
        buttonBox->addButton(tr("&Clear"), QDialogButtonBox::ActionRole);
    buttonBox->button(QDialogButtonBox::Close)->setDefault(true);
    buttonBox->button(QDialogButtonBox::Close)->setAutoDefault(true);
    buttonBox->button(QDialogButtonBox::Close)->setFocus();
    updateContent();
    connect(buttonBox, &QDialogButtonBox::rejected, this, &RatingDialog::reject);
    connect(buttonBox, &QDialogButtonBox::clicked, this, &RatingDialog::buttonClicked);
    connect(m_list, &RatedGamesList::openRatedGame, this, &RatingDialog::activateGame);
}

void RatingDialog::activateGame(unsigned n)
{
    emit openRecentFile(m_history.getFile(n));
}

void RatingDialog::buttonClicked(QAbstractButton* button)
{
    if (button != static_cast<QAbstractButton*>(m_clearButton))
        return;
    QMessageBox msgBox(QMessageBox::Warning, "",
                       tr("Clear rating and delete rating history?"),
                       QMessageBox::Cancel, this);
    Util::setNoTitle(msgBox);
    auto clearButton =
        msgBox.addButton(tr("Clear rating"), QMessageBox::DestructiveRole);
    msgBox.setDefaultButton(clearButton);
    msgBox.exec();
    if (msgBox.clickedButton() != clearButton)
        return;
    m_history.clear();
    updateContent();
}

void RatingDialog::updateContent()
{
    auto variant = m_history.getVariant();
    unsigned nuGames = m_history.getNuGames();
    Rating rating = m_history.getRating();
    Rating bestRating = m_history.getBestRating();
    if (nuGames == 0)
        rating = Rating(0);
    QString variantStr;
    switch (variant)
    {
    case Variant::classic:
        variantStr = tr("Classic (4 players)");
        break;
    case Variant::classic_2:
        variantStr = tr("Classic (2 players)");
        break;
    case Variant::classic_3:
        variantStr = tr("Classic (3 players)");
        break;
    case Variant::duo:
        variantStr = tr("Duo");
        break;
    case Variant::trigon:
        variantStr = tr("Trigon (4 players)");
        break;
    case Variant::trigon_2:
        variantStr = tr("Trigon (2 players)");
        break;
    case Variant::trigon_3:
        variantStr = tr("Trigon (3 players)");
        break;
    case Variant::junior:
        variantStr = tr("Junior");
        break;
    case Variant::nexos:
        variantStr = tr("Nexos (4 players)");
        break;
    case Variant::nexos_2:
        variantStr = tr("Nexos (2 players)");
        break;
    case Variant::callisto:
        variantStr = tr("Callisto (4 players)");
        break;
    case Variant::callisto_2:
        variantStr = tr("Callisto (2 players, 2 colors)");
        break;
    case Variant::callisto_2_4:
        variantStr = tr("Callisto (2 players, 4 colors)");
        break;
    case Variant::callisto_3:
        variantStr = tr("Callisto (3 players)");
        break;
    case Variant::gembloq:
        variantStr = tr("GembloQ (4 players)");
        break;
    case Variant::gembloq_2:
        variantStr = tr("GembloQ (2 players, 2 colors)");
        break;
    case Variant::gembloq_2_4:
        variantStr = tr("GembloQ (2 players, 4 colors)");
        break;
    case Variant::gembloq_3:
        variantStr = tr("GembloQ (3 players)");
        break;
    }
    m_labelVariant->setText(variantStr);
        m_labelNuGames->setText(QString::number(nuGames));
    if (nuGames == 0)
    {
        m_labelRating->setText("<b>--");
        m_labelBestRating->setText("--");
    }
    else
    {
        m_labelRating->setText(QString("<b>%1").arg(rating.to_int()));
        m_labelBestRating->setNum(bestRating.to_int());
    }
    m_graph->updateContent(m_history);
    m_list->updateContent(variant, m_history);
    m_clearButton->setEnabled(nuGames > 0);
}

//-----------------------------------------------------------------------------
