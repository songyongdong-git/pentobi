//-----------------------------------------------------------------------------
/** @file libpentobi_gui/GameInfoDialog.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "GameInfoDialog.h"

#include <QDialogButtonBox>
#include <QTextCodec>
#include "LineEdit.h"
#include "libpentobi_gui/Util.h"

using libpentobi_base::Variant;

//-----------------------------------------------------------------------------

GameInfoDialog::GameInfoDialog(QWidget* parent, Game& game,
                               QTextCodec*& textCodec)
    : QDialog(parent),
      m_game(game),
      m_textCodec(textCodec)
{
    setWindowTitle(tr("Game Info"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    auto layout = new QVBoxLayout;
    setLayout(layout);
    m_formLayout = new QFormLayout;
    layout->addLayout(m_formLayout);
    auto variant = game.get_variant();
    auto nuColors = get_nu_colors(variant);
    auto nuPlayers = get_nu_players(variant);
    if (variant == Variant::duo)
    {
        m_playerBlue = createPlayerName(tr("Player &Purple:"), Color(0));
        m_playerGreen = createPlayerName(tr("Player &Orange:"), Color(1));
    }
    else if (variant == Variant::junior)
    {
        m_playerBlue = createPlayerName(tr("Player &Green:"), Color(0));
        m_playerGreen = createPlayerName(tr("Player &Orange:"), Color(1));
    }
    else if (nuColors == 2)
    {
        m_playerBlue = createPlayerName(tr("Player &Blue:"), Color(0));
        m_playerGreen = createPlayerName(tr("Player &Green:"), Color(1));
    }
    else if (nuPlayers == 2)
    {
        m_playerBlueRed = createPlayerName(tr("Player &Blue/Red:"), Color(0));
        m_playerYellowGreen =
            createPlayerName(tr("Player &Yellow/Green:"), Color(1));
    }
    else
    {
        m_playerBlue = createPlayerName(tr("Player &Blue:"), Color(0));
        m_playerYellow = createPlayerName(tr("Player &Yellow:"), Color(1));
        m_playerRed = createPlayerName(tr("Player &Red:"), Color(2));
        if (nuPlayers == 4)
            m_playerGreen = createPlayerName(tr("Player &Green:"), Color(3));
    }
    m_date = createLine(tr("&Date:"), m_game.get_date());
    m_time = createLine(tr("&Time limits:"), m_game.get_time());
    m_event = createLine(tr("&Event:"), m_game.get_event());
    m_round = createLine(tr("R&ound:"), m_game.get_round());
    auto buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);
    // We assume that the user wants to edit the game info if it is still empty
    // and that he only wants to display it if not empty. Therefore, we leave
    // the focus at the first text field if it is empty and put it on the
    // button box otherwise.
    if (nuColors == 4 && nuPlayers == 2)
    {
        if (! m_playerBlueRed->text().isEmpty())
            buttonBox->setFocus();
    }
    else if (! m_playerBlue->text().isEmpty())
        buttonBox->setFocus();
    connect(buttonBox, &QDialogButtonBox::accepted,
            this, &GameInfoDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected,
            this, &GameInfoDialog::reject);
}

GameInfoDialog::~GameInfoDialog() = default;

void GameInfoDialog::accept()
{
    auto variant = m_game.get_variant();
    auto nuColors = get_nu_colors(variant);
    auto nuPlayers = get_nu_players(variant);
    string value;
    if (nuColors == 2)
    {
        if (acceptLine(m_playerBlue, value))
            m_game.set_player_name(Color(0), value);
        if (acceptLine(m_playerGreen, value))
            m_game.set_player_name(Color(1), value);
    }
    else if (nuPlayers == 2)
    {
        if (acceptLine(m_playerBlueRed, value))
            m_game.set_player_name(Color(0), value);
        if (acceptLine(m_playerYellowGreen, value))
            m_game.set_player_name(Color(1), value);
    }
    else
    {
        if (acceptLine(m_playerBlue, value))
            m_game.set_player_name(Color(0), value);
        if (acceptLine(m_playerYellow, value))
            m_game.set_player_name(Color(1), value);
        if (acceptLine(m_playerRed, value))
            m_game.set_player_name(Color(2), value);
        if (nuPlayers == 4)
            if (acceptLine(m_playerGreen, value))
                m_game.set_player_name(Color(3), value);
    }
    if (acceptLine(m_date, value))
        m_game.set_date(value);
    if (acceptLine(m_time, value))
        m_game.set_time(value);
    if (acceptLine(m_event, value))
        m_game.set_event(value);
    if (acceptLine(m_round, value))
        m_game.set_round(value);
    QDialog::accept();
}

bool GameInfoDialog::acceptLine(QLineEdit* lineEdit, string& value)
{
    if (! lineEdit->isModified())
        return false;
    QString text = lineEdit->text();
    value = m_textCodec->fromUnicode(text).constData();
    return true;
}

QLineEdit* GameInfoDialog::createLine(const QString& label, const string& text)
{
    auto lineEdit = new LineEdit(this, 30);
    if (! text.empty())
    {
        lineEdit->setText(m_textCodec->toUnicode(text.c_str()));
        lineEdit->setCursorPosition(0);
    }
    m_formLayout->addRow(label, lineEdit);
    return lineEdit;
}

QLineEdit* GameInfoDialog::createPlayerName(const QString& label, Color c)
{
    return createLine(label, m_game.get_player_name(c));
}

//-----------------------------------------------------------------------------
