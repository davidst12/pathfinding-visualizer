#pragma once

#include <SFML/Graphics.hpp>

class OptionsMenuText : public sf::Drawable {
private:
    std::vector<sf::Text> piezas;
    bool multiple_selection_allowed;

public:
    inline OptionsMenuText(std::vector<std::string> str, const sf::Font& font, bool allow_multiple_selection = false) {
        multiple_selection_allowed = allow_multiple_selection;
        for(size_t i = 0; i < str.size(); ++i) {
            sf::Text text(font, str[i], 24);
            if(i == 0) {
                text.setFillColor(sf::Color::White);
                text.setStyle(sf::Text::Bold);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
                text.setPosition({400.0f, 200.0f + i * 30.0f});
            } else {
                text.setFillColor(sf::Color::White);
                text.setStyle(sf::Text::Bold);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
                text.setPosition({400.0f, 220.0f + i * 30.0f});
            }
            piezas.push_back(text);
        }
    }

    inline void newSelectedPiece(int index) {
        for (size_t i = 0; i < piezas.size(); ++i) {
            if (i == index) {
                piezas[i].setFillColor(sf::Color::Yellow);
            } else {
                piezas[i].setFillColor(sf::Color::White);
            }
        }
    }

    inline void newPeressedPiece(int index) {
        for (size_t i = 0; i < piezas.size(); ++i) {
            if (i == index) {
                piezas[i].getStyle() == (sf::Text::Underlined | sf::Text::Bold) ? piezas[i].setStyle(sf::Text::Bold) : piezas[i].setStyle(sf::Text::Underlined | sf::Text::Bold);
            }
        }
    }

    // El truco para el .draw() único
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (const auto& texto : piezas) {
            target.draw(texto, states);
        }
    }
};