#ifndef  VIEW_SCROLL_BAR_HPP
#define  VIEW_SCROLL_BAR_HPP

#include "window.hpp"
#include "scrollable.hpp"
#include "../Standard/api_bar.hpp"

namespace ps
{
    enum class Orientation : int
    {
        Vertical,
        Horizontal
    };

    const char* const VERTICAL_SLIDER_TEXTURE       = "pictures/vertical_slider.png";
    const char* const HORIZONTAL_SLIDER_TEXTURE     = "pictures/horizontal_slider.png";
    const char* const UP_MOVE_BUTTON_TEXTURE        = "pictures/up_move_button.png";
    const char* const DOWN_MOVE_BUTTON_TEXTURE      = "pictures/down_move_button.png";
    const char* const LEFT_MOVE_BUTTON_TEXTURE      = "pictures/left_move_button.png";
    const char* const RIGHT_MOVE_BUTTON_TEXTURE     = "pictures/right_move_button.png";
    const char* const VERTICAL_SCROLL_BAR_TEXTURE   = "pictures/vertical_scroll_bar.png";
    const char* const HORIZONTAL_SCROLL_BAR_TEXTURE = "pictures/horizontal_scroll_bar.png";

    const ps::vec2u MOVE_BUTTON_SIZE = ps::vec2u{16, 16};

/*============================< Slider interface >============================*/

    template <Orientation orientation>
    class Slider : public psapi::IBarButton, public AWindow
    {
    public:
        Slider( std::unique_ptr<psapi::sfm::Sprite> sprite,
                const vec2i                         &position,
                const vec2u                         &size,
                const vec2i                         &direction,
                const vec2i                         &top_left_position,
                const vec2u                         &scroll_bar_size,
                const IWindow*                      scroll_bar,  
                Scrollable*                         object              );
        
        virtual ~Slider() override = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual wid_t getId() const override;
        
        virtual       IWindow* getWindowById(wid_t id)       override;
        virtual const IWindow* getWindowById(wid_t id) const override;

        virtual vec2i getPos()  const override;
        virtual vec2u getSize() const override;

        virtual void setParent(const IWindow* parent) override;

        virtual void forceActivate() override;
        virtual void forceDeactivate() override;

        virtual bool isActive() const override;

        virtual bool isWindowContainer() const override;

        virtual void setState(State state) override;
        virtual State getState() const override; 

        void move(float offsetX, float offsetY);
        void move(const vec2f &offset);

    private:
        std::unique_ptr<psapi::sfm::Sprite> sprite_;
        ps::vec2i                           direction_;
        ps::vec2i                           top_left_pos_;
        ps::vec2u                           scroll_bar_size_;
        ps::vec2i                           last_mouse_pos_;
        Scrollable*                         object_;
        State                               state_;

    };

/*==========================< Slider implementation >=========================*/

    template <Orientation orientation>
    Slider<orientation>::Slider(std::unique_ptr<psapi::sfm::Sprite> sprite,
                        const vec2i                         &position,
                        const vec2u                         &size,
                        const vec2i                         &direction,
                        const vec2i                         &top_left_corner_position,
                        const vec2u                         &scroll_bar_size,
                        const IWindow*                      scroll_bar,  
                        Scrollable*                         object     )
    :
        sprite_         (std::move(sprite)),
        direction_      (direction),
        top_left_pos_   (top_left_corner_position),
        scroll_bar_size_(scroll_bar_size),
        object_         (object),
        state_          (psapi::IBarButton::State::Normal)
    {
        parent_     = scroll_bar;
        pos_        = position;
        size_       = size;
        is_active_  = true;

        last_mouse_pos_ = pos_;

        vec2u picture_size = sprite->getSize();
        sprite_->setScale(static_cast<float>(size_.x) / static_cast<float>(picture_size.x),
                        static_cast<float>(size_.y) / static_cast<float>(picture_size.y) );
    }

    template<Orientation orientation>
    void Slider<orientation>::move(float offsetX, float offsetY)
    {
        object_->scroll(offsetX, offsetY);

        last_mouse_pos_ += vec2i{(int)offsetX, (int)offsetY};
        pos_            += vec2i{(int)offsetX, (int)offsetY};

        ps::vec2i max_deviation = {(int)scroll_bar_size_.x - (int)size_.x,
                                   (int)scroll_bar_size_.y - (int)size_.y};

        pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + max_deviation.x, pos_.x));
        pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + max_deviation.y, pos_.y));

        last_mouse_pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + max_deviation.x, last_mouse_pos_.x));
        last_mouse_pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + max_deviation.y, last_mouse_pos_.y));
    }

    template<Orientation orientation>
    void Slider<orientation>::move(const vec2f &offset)
    {
        object_->scroll(offset);

        last_mouse_pos_ += vec2i{(int)offset.x, (int)offset.y};
        pos_            += vec2i{(int)offset.x, (int)offset.y};

        ps::vec2i max_deviation = {(int)scroll_bar_size_.x - (int)size_.x,
                                   (int)scroll_bar_size_.y - (int)size_.y};

        pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + max_deviation.x, pos_.x));
        pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + max_deviation.y, pos_.y));

        last_mouse_pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + max_deviation.x, last_mouse_pos_.x));
        last_mouse_pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + max_deviation.y, last_mouse_pos_.y));
    }

    template <Orientation orientation>
    void Slider<orientation>::draw(IRenderWindow* render_window)
    {
        sprite_->setPosition(static_cast<float>(pos_.x), 
                             static_cast<float>(pos_.y) );

        sprite_->draw(render_window);
    }

    template <Orientation orientation>
    bool Slider<orientation>::update(const IRenderWindow* render_window, const Event& event)
    {
        if (!is_active_) return;

        vec2i new_mouse_position = psapi::sfm::Mouse::getPosition(render_window);

        if (pos_.x <= new_mouse_position.x && new_mouse_position.x <= (pos_.x + size_.x) &&
            pos_.y <= new_mouse_position.y && new_mouse_position.y <= (pos_.y + size_.y)   )
        {
            if (event.orientation == psapi::sfm::Event::MouseMoved)
            {
                ps::vec2i offset = new_mouse_position - last_mouse_pos_;
                
                offset.x = offset.x * direction_.x;
                offset.y = offset.y * direction_.y;

                move(offset);
            }
            else if (event.orientation == psapi::sfm::Event::MouseButtonPressed)
            {
                last_mouse_pos_ = new_mouse_position;
            }
        }
    }

    template <Orientation orientation>
    void Slider<orientation>::setState(State state)
    {
        state_ = state;
    }

    template <Orientation orientation>
    psapi::IBarButton::State Slider<orientation>::getState() const
    {
        return state_;
    }

/*============================================================================*/

/*==========================< MoveButton interface >==========================*/

    template <Orientation orientation>
    class MoveButton : public psapi::IBarButton, public AWindow
    {
    public:
        MoveButton( std::unique_ptr<psapi::sfm::Sprite> sprite,
                    const vec2i                         &position,
                    const vec2u                         &size,
                    const vec2i                         &direction,
                    const IWindow*                      scroll_bar,  
                    Slider<orientation>*                slider      );


        virtual ~MoveButton() = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual void setState(State state) override;
        virtual State getState() const override; 

    private:
        std::unique_ptr<psapi::sfm::Sprite> sprite_;
        vec2i                               direction_;
        Slider<orientation>*                       slider_;
        State state_;
    };

/*========================< MoveButton implementation >=======================*/

    template <Orientation orientation>
    MoveButton<orientation>::MoveButton(std::unique_ptr<psapi::sfm::Sprite> sprite,
                                const vec2i                                 &position,
                                const vec2u                                 &size,
                                const vec2i                                 &direction,
                                const IWindow*                              scroll_bar,  
                                Slider<orientation>*                        slider     )
    :
        sprite_     (std::move(sprite)),
        direction_  (direction),
        slider_     (slider)
    {
        pos_        = position;
        size_       = size;
        parent_     = scroll_bar;
        is_active_  = true;

        vec2u picture_size = sprite->getSize();
        sprite->setScale(static_cast<float>(size_.x) / static_cast<float>(picture_size.x),
                         static_cast<float>(size_.y) / static_cast<float>(picture_size.y) );
    }

    template <Orientation orientation>
    void MoveButton<orientation>::draw(IRenderWindow* render_window)
    {
        sprite_->setPosition(pos_);
        sprite_->draw(render_window);
    }

    template <Orientation orientation>
    bool MoveButton<orientation>::update(const IRenderWindow* render_window,
                                const Event          &event        )
    {
        if (!is_active_) return false;

        vec2i new_mouse_position = psapi::sfm::Mouse::getPosition(render_window);

        new_mouse_position -= pos;

        if (0 <= new_mouse_position.x && new_mouse_position.x <= size_.x &&
            0 <= new_mouse_position.y && new_mouse_position.y <= size.y     )
        {
            if (event.orientation == Event::MouseButtonPressed)
            {
                slider_->move((float)direction.x, (float)direction.y);
                return true;
            }
        }

        return false;
    }

    template <Orientation orientation>
    void MoveButton<orientation>::setState(State state)
    {
        state_ = state;
    }

    template <Orientation orientation>
    psapi::IBarButton::State MoveButton<orientation>::getState() const
    {
        return state_;
    } 

/*============================================================================*/

/*===========================< ScrollBar interface >==========================*/

    template <Orientation orientation>
    class ScrollBar : public psapi::IBar, public AWindowVector
    {
    public:
        ScrollBar(  std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                    std::unique_ptr<psapi::sfm::Sprite> hover_button,
                    std::unique_ptr<psapi::sfm::Sprite> press_button,
                    std::unique_ptr<psapi::sfm::Sprite> release_button,
                    ps::Scrollable *scrollable_object,
                    double          scroll_ratio,
                    const vec2i    &bar_position,
                    const vec2u    &bar_size,
                    const wid_t    &id                                    ) = delete;

        virtual ~ScrollBar() override = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual psapi::ChildInfo getNextChildInfo() const override;
        virtual void finishButtonDraw(IRenderWindow* renderWindow, const psapi::IBarButton* button) const override;

        static std::unique_ptr<ScrollBar<orientation>> create();

    private:
        void drawChildren(IRenderWindow* render_window) override;
        bool updateChildren(const IRenderWindow* render_window, const Event& event) override;
        void handleDoubleAction();
        
        std::unique_ptr<psapi::sfm::Sprite> background_;
        std::unique_ptr<psapi::sfm::Sprite> hover_button_;
        std::unique_ptr<psapi::sfm::Sprite> press_button_;
        std::unique_ptr<psapi::sfm::Sprite> release_button_;

    };

/*========================< ScrollBar implementation >========================*/

    template <Orientation orientation>
    void ScrollBar<orientation>::draw(IRenderWindow* render_window)
    {
        background_->draw(render_window);

        drawChildren(render_window);
    }

    template <Orientation orientation>
    bool update(const IRenderWindow* render_window, const Event& event)
    {
        if (!is_active_)
        {
            return false;
        }

        return updateChildren(render_window, event);
    }

    template <Orientation orientation>
    psapi::ChildInfo ScrollBar<orientation>::getNextChildInfo() const
    {
        return psapi::ChildInfo{};
    }

    template <Orientation orientation>
    void ScrollBar<orientation>::finishButtonDraw(IRenderWindow* renderWindow, const psapi::IBarButton* button) const
    {
        return;
    }

    template <Orientation orientation>
    void ScrollBar<orientation>::drawChildren(IRenderWindow* render_window)
    {
        for (auto &window : windows_)
        {
            window->draw(render_window);
        }
    }

    template <Orientation orientation>
    bool ScrollBar<orientation>::updateChildren(const IRenderWindow* render_window, const Event& event)
    {
        bool result = false;

        for (auto &window : windows_)
        {
            result |= window->update(render_window, event);
        }

        handleDoubleAction();

        return result;
    }

    template <Orientation orientation>
    void ScrollBar<orientation>::handleDoubleAction()
    {
        ssize_t last_active = last_active_button_;

        int n_active_buttons = 0;
        ssize_t new_active = -1;

        for (size_t i = 0; i < windows_.size(); i++)
        {
            psapi::IBarButton* ptr = static_cast<psapi::IBarButton*>(windows_[i].get());

            if (ptr->getState() == psapi::IBarButton::State::Released)
            {
                n_active_buttons++; 
                new_active = static_cast<ssize_t>(i);
            }
        }

        if (n_active_buttons > 1) 
        {
            psapi::IBarButton* ptr = static_cast<psapi::IBarButton*>(windows_[(size_t)last_active].get());
            ptr->setState(psapi::IBarButton::State::Normal);
        }
        else if (n_active_buttons == 1) 
        {
            last_active_button_ = new_active;
        }
    }

    template <Orientation orientation>
    std::unique_ptr<ScrollBar<orientation>> ScrollBar<orientation>::create()
    {
        static std::unique_ptr<psapi::sfm::Texture> background_texture = {};
        
        if (orientation == Orientation::Vertical)
        {
            background_texture->loadFromFile(VERTICAL_SCROLL_BAR_TEXTURE);
        }
        else
        {
            background_texture->loadFromFile(HORIZONTAL_SCROLL_BAR_TEXTURE);
        }

        static std::unique_ptr<psapi::sfm::Texture> press_button_texture = {};
        // press_button_texture->loadFromFile();
        // 
    }

/*============================================================================*/
}

#endif //VIEW_SCROLL_BAR_HPP