#ifndef  GRAPHICS_TEXT_HPP
#define  GRAPHICS_TEXT_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class Font : public AFont
        {
        public:
             Font() = default;
            ~Font() = default;

            virtual bool loadFromFile(const std::string& filename) override;

        private:
            sf::Font font_;

            friend class Text;
        };

        class Text : public AText
        {
        public:
             Text() = default;
            ~Text() = default;

            virtual void draw(ARenderWindow *window)          override;
            virtual void setString(const std::string& string) override;
            virtual void setFont(const AFont* font)           override;
            virtual void setCharacterSize(unsigned int size)  override;
            virtual void setStyle(uint32_t style)             override;
            virtual void setFillColor(const Color* color)     override;
            virtual void setOutlineColor(const Color* color)  override;
            virtual void setOutlineThickness(float thickness) override;

        private:
            sf::Text text_;
        };  

    } //sfm
    
} //psapi

#endif //GRAPHICS_TEXT_HPP