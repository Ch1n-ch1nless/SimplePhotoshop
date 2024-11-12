#ifndef  GRAPHICS_SHAPE_HPP
#define  GRAPHICS_SHAPE_HPP

#include "render_window.hpp"

namespace psapi
{
    namespace sfm
    {
        class EllipseShape : public IEllipseShape
        {
        public:
            EllipseShape(unsigned int width, unsigned int height);
            EllipseShape(const vec2u &size);
            EllipseShape(unsigned int radius);

            void draw(IRenderWindow *window) const override;

            void setTexture(const ITexture *texture) override;
            void setFillColor(const Color &color) override;
            void setPosition(const vec2i &pos) override;
            void setPosition(const vec2f &pos) override;
            void setPosition(const vec2d &pos) override;
            void setScale(const vec2f &scale) override;
            void setSize(const vec2u &size) override;
            void setRotation(float angle) override;
            void setOutlineColor(const Color &color) override;
            void setOutlineThickness(float thickness) override;

            float getRotation() const override;
            vec2f getScale() const override;
            vec2f getPosition() const override;
            const Color &getFillColor() const override;
            vec2u getSize() const override;
            float getOutlineThickness() const override;
            const Color &getOutlineColor() const override;
            const IImage *getImage() const override;

            void move(const vec2f &offset) override;

        private:
            sf::CircleShape shape_;
        };

        class RectangleShape : public IRectangleShape
        {
        public:
            RectangleShape(unsigned int width, unsigned int height);
            RectangleShape(const vec2u &size);

            ~RectangleShape() override = default;

            void draw(IRenderWindow *window) const override;

            void setTexture(const ITexture *texture) override;
            void setFillColor(const Color &color) override;
            void setPosition(const vec2i &pos) override;
            void setPosition(const vec2f &pos) override;
            void setPosition(const vec2d &pos) override;
            void setScale(const vec2f &scale) override;
            void setSize(const vec2u &size) override;
            void setRotation(float angle) override;
            void setOutlineColor(const Color &color) override;
            void setOutlineThickness(float thickness) override;

            float getRotation() const override;
            vec2f getScale() const override;
            vec2f getPosition() const override;
            const Color &getFillColor() const override;
            vec2u getSize() const override;
            float getOutlineThickness() const override;
            const Color &getOutlineColor() const override;
            const IImage *getImage() const override;

            void move(const vec2f &offset) override;

        private:
            sf::RectangleShape shape_;
        };

    } //sfm

} //psapi

#endif //GRAPHICS_SHAPE_HPP