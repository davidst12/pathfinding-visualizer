#pragma once

#include <SFML/Graphics.hpp>

class SelectionText : public sf::Drawable {
public:
    inline SelectionText(std::string title, std::vector<std::string> option_names, const sf::Font& font, bool allow_multiple_selection = false) {
        multiple_selection_allowed = allow_multiple_selection;
        option_names.insert(option_names.begin(), title);
        if(allow_multiple_selection) option_names.push_back("<<Continue>>");
        options_count = option_names.size() - 1;  // Exclude title from options count
        cursor_index = 1;

        for(size_t i = 0; i < option_names.size(); ++i) {
            sf::Text text(font, option_names[i], 24);
            if(cursor_index == i) text.setFillColor(sf::Color::Yellow);
            else text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
            if(i == 0) {
                text.setPosition({400.0f, 200.0f + i * 30.0f});
            } else {
                text.setPosition({400.0f, 220.0f + i * 30.0f});
            }
            texts.push_back(text);
        }
    }

    inline int moveUp() {
        if(cursor_index > 1) {
            cursor_index -= 1;
        } else return cursor_index;

        for (size_t i = 1; i <= options_count; ++i) {
            if (i == cursor_index) {
                texts[i].setFillColor(sf::Color::Yellow);
            } else {
                texts[i].setFillColor(sf::Color::White);
            }
        }
        return cursor_index;
    }

    inline int moveDown() {
        if(cursor_index < options_count) {
            cursor_index += 1;
        } else return cursor_index;

        for (size_t i = 1; i <= options_count; ++i) {
            if (i == cursor_index) {
                texts[i].setFillColor(sf::Color::Yellow);
            } else {
                texts[i].setFillColor(sf::Color::White);
            }
        }
        return cursor_index;
    }

    // Return TRUE if user's pressed <Continue>, FALSE otherwise
    inline bool pressedEnter() {
        if(!multiple_selection_allowed) {
            oprions_selected.clear();
            oprions_selected.emplace(cursor_index);
            return true;
        } else {
            if (cursor_index == options_count) {   // Cursor is on "Continue"
                return !oprions_selected.empty();  // True if at least one option is selected, False otherwise
            }
            if(oprions_selected.contains(cursor_index)) {
                oprions_selected.erase(cursor_index);
            } else {
                oprions_selected.emplace(cursor_index);
            }
            for (size_t i = 1; i <= options_count; ++i) {
                if (oprions_selected.contains(i)) {
                    texts[i].setStyle(sf::Text::Underlined | sf::Text::Bold);
                } else {
                    texts[i].setStyle(sf::Text::Bold);
                }
            }
        }
        return false;
    }

    inline std::set<int> getSelectedOptions() const {
        return oprions_selected;
    }

    inline int getSelectedOption() const {
        return cursor_index;
    }

    // El truco para el .draw() único
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (const auto& text : texts) {
            target.draw(text, states);
        }
    }

private:
    std::vector<sf::Text> texts;
    int options_count = 0;
    bool multiple_selection_allowed;
    int cursor_index = 1;
    std::set<int> oprions_selected = {};
};
