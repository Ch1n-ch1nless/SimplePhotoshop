#ifndef  GRAPHICS_RENDER_WINDOW_HPP
#define  GRAPHICS_RENDER_WINDOW_HPP

#include "../Standard/api_sfm.hpp"

#include <SFML/Graphics.hpp>

namespace psapi
{
    namespace sfm
    {
        class Text;
        class Sprite;
        class Image;
        class PixelsArray;
        class RectangleShape;
        class EllipseShape;

        class RenderWindow final : public IRenderWindow
        {
        public:
             RenderWindow(unsigned int width, unsigned int height, const std::string& window_title);
            ~RenderWindow() final = default;

            virtual bool isOpen () const override;
            virtual void clear  ()       override;
            virtual void display()       override;
            virtual void close  ()       override;

            virtual vec2u getSize() const override;

            virtual bool pollEvent(Event& event) override;

            virtual void draw(Drawable *target) override;

            virtual void setFps(float fps) override;
            virtual float getFps() const override;

            static std::unique_ptr<IRenderWindow> create(unsigned int width, unsigned int height, const std::string& name);

        private:
            sf::RenderWindow window_;
            vec2u            size_;

            friend class Text;
            friend class Sprite;
            friend class Image;
            friend class PixelsArray;
            friend class RectangleShape;
            friend class EllipseShape;

            friend vec2i Mouse::getPosition(const IRenderWindow* window);
        };

    } //sfm

} //psapi

#endif //GRAPHICS_RENDER_WINDOW_HPP