#ifndef  GRAPHICS_TEXT_HPP
#define  GRAPHICS_TEXT_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class Font final : public IFont
        {
        public:
             Font();
            ~Font() final = default;

            virtual bool loadFromFile(const std::string& filename) override;

            static std::unique_ptr<IFont> create();

        private:
            sf::Font font_;

            friend class Text;
        };

        class Text final : public IText
        {
        public:
             Text();
            ~Text() final = default;

            virtual IntRect getGlobalBounds() const override;
            virtual void draw(IRenderWindow *window)    const override;
            virtual void setString(const std::string& string) override;
            virtual void setFont(const IFont* font)           override;
            virtual void setCharacterSize(unsigned int size)  override;
            virtual void setStyle(uint32_t style)             override;
            virtual void setPos(const vec2f &pos)             override;
            virtual void setSize(const vec2f &size)           override;
            virtual void setFillColor(const Color* color)     override;
            virtual void setOutlineColor(const Color* color)  override;
            virtual void setOutlineThickness(float thickness) override;

            static std::unique_ptr<IText> create();

        private:
            sf::Text text_;
        };  

    } //sfm
    
} //psapi

#endif //GRAPHICS_TEXT_HPP