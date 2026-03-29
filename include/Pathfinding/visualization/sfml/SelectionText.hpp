#pragma once

#include <SFML/Graphics.hpp>

class SelectionText : public sf::Drawable {
   public:
    inline SelectionText(std::string title, std::vector<std::string> option_names,
                         const sf::Font& font, bool allow_multiple_selection = false) {
        m_multiple_selection_allowed = allow_multiple_selection;
        option_names.insert(option_names.begin(), title);
        if (allow_multiple_selection) option_names.push_back("<<Continue>>");
        m_options_count = option_names.size() - 1;  // Exclude title from options count
        m_cursor_index = 1;

        for (size_t i = 0; i < option_names.size(); ++i) {
            sf::Text text(font, option_names[i], 24);
            if (m_cursor_index == i)
                text.setFillColor(sf::Color::Yellow);
            else
                text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
            if (i == 0) {
                text.setPosition({400.0f, 200.0f + i * 30.0f});
            } else {
                text.setPosition({400.0f, 220.0f + i * 30.0f});
            }
            m_texts.push_back(text);
        }
    }

    inline int moveUp() {
        if (m_cursor_index > 1) {
            m_cursor_index -= 1;
        } else {
            return m_cursor_index;
        }

        for (size_t i = 1; i <= m_options_count; ++i) {
            if (i == m_cursor_index) {
                m_texts[i].setFillColor(sf::Color::Yellow);
            } else {
                m_texts[i].setFillColor(sf::Color::White);
            }
        }
        return m_cursor_index;
    }

    inline int moveDown() {
        if (m_cursor_index < m_options_count) {
            m_cursor_index += 1;
        } else
            return m_cursor_index;

        for (size_t i = 1; i <= m_options_count; ++i) {
            if (i == m_cursor_index) {
                m_texts[i].setFillColor(sf::Color::Yellow);
            } else {
                m_texts[i].setFillColor(sf::Color::White);
            }
        }
        return m_cursor_index;
    }

    // Return TRUE if user's pressed <Continue>, FALSE otherwise
    inline bool pressedEnter() {
        if (!m_multiple_selection_allowed) {
            m_options_selected.clear();
            m_options_selected.emplace(m_cursor_index);
            return true;
        } else {
            if (m_cursor_index == m_options_count) {  // Cursor is on "Continue"
                return !m_options_selected
                            .empty();  // True if at least one option is selected, False otherwise
            }
            if (m_options_selected.count(m_cursor_index)) {
                m_options_selected.erase(m_cursor_index);
            } else {
                m_options_selected.emplace(m_cursor_index);
            }
            for (size_t i = 1; i <= m_options_count; ++i) {
                if (m_options_selected.count(i)) {
                    m_texts[i].setStyle(sf::Text::Underlined | sf::Text::Bold);
                } else {
                    m_texts[i].setStyle(sf::Text::Bold);
                }
            }
        }
        return false;
    }

    inline std::set<int> getSelectedOptions() const {
        return m_options_selected;
    }

    inline int getSelectedOption() const {
        return m_cursor_index;
    }

    // El truco para el .draw() único
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (const auto& text : m_texts) {
            target.draw(text, states);
        }
    }

   private:
    std::vector<sf::Text> m_texts;
    int m_options_count = 0;
    bool m_multiple_selection_allowed;
    int m_cursor_index = 1;
    std::set<int> m_options_selected = {};
};
