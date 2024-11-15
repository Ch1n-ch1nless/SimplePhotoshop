/*
#ifndef  VIEW_SCROLL_BAR_HPP
#define  VIEW_SCROLL_BAR_HPP

#include "window.hpp"
#include "scrollable.hpp"
#include "../Standard/api_bar.hpp"

namespace ps
{
    enum class ScrollType : int
    {
        Vertical,
        Horizontal
    };


/*============================< Slider interface >============================*/
/*
    template <ScrollType type>
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
*/
/*==========================< Slider implementation >=========================*/
/*
    template <ScrollType type>
    Slider<type>::Slider(std::unique_ptr<psapi::sfm::Sprite> sprite,
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

    template<ScrollType type>
    void Slider<type>::move(float offsetX, float offsetY)
    {
        object_->scroll(offsetX, offsetY);

        last_mouse_pos_ += vec2i{(int)offsetX, (int)offsetY};
        pos_            += vec2i{(int)offsetX, (int)offsetY};

        pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + (int)scroll_bar_size_.x, pos_.x));
        pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + (int)scroll_bar_size_.y, pos_.y));
    }

    template<ScrollType type>
    void Slider<type>::move(const vec2f &offset)
    {
        object_->scroll(offset);

        last_mouse_pos_ += vec2i{(int)offset.x, (int)offset.y};
        pos_            += vec2i{(int)offset.x, (int)offset.y};

        pos_.x = std::max(top_left_pos_.x, std::min(top_left_pos_.x + (int)scroll_bar_size_.x, pos_.x));
        pos_.y = std::max(top_left_pos_.y, std::min(top_left_pos_.y + (int)scroll_bar_size_.y, pos_.y));
    }

    template <ScrollType type>
    void Slider<type>::draw(IRenderWindow* render_window)
    {
        sprite_->setPosition(static_cast<float>(pos_.x), 
                            static_cast<float>(pos_.y) );

        sprite_->draw(render_window);
    }

    template <ScrollType type>
    bool Slider<type>::update(const IRenderWindow* render_window, const Event& event)
    {
        if (!is_active_) return;

        vec2i new_mouse_position = psapi::sfm::Mouse::getPosition(render_window);

        if (pos_.x <= new_mouse_position.x && new_mouse_position.x <= (pos_.x + size_.x) &&
            pos_.y <= new_mouse_position.y && new_mouse_position.y <= (pos_.y + size_.y)   )
        {
            if (event.type == psapi::sfm::Event::MouseMoved)
            {
                ps::vec2i offset = new_mouse_position - last_mouse_pos_;
                
                offset.x = offset.x * ((direction_.x == 0) ? 0 : 1);
                offset.y = offset.y * ((direction_.y == 0) ? 0 : 1);

                move(offset);
            }
            else if (event.type == psapi::sfm::Event::MouseButtonPressed)
            {
                last_mouse_pos_ = new_mouse_position;
            }
        }
    }

    template <ScrollType type>
    void Slider<type>::setState(State state)
    {
        state_ = state;
    }

    template <ScrollType type>
    psapi::IBarButton::State Slider<type>::getState() const
    {
        return state_;
    } 
*/
/*============================================================================*/

/*==========================< MoveButton interface >==========================*/
/*
    template <ScrollType type>
    class MoveButton : public psapi::IBarButton, public AWindow
    {
    public:
        MoveButton( std::unique_ptr<psapi::sfm::Sprite> sprite,
                    const vec2i                         &position,
                    const vec2u                         &size,
                    const vec2i                         &direction,
                    const IWindow*                      scroll_bar,  
                    Slider<type>*                       slider      );


        virtual ~MoveButton() = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual void setState(State state) override;
        virtual State getState() const override; 

    private:
        std::unique_ptr<psapi::sfm::Sprite> sprite_;
        vec2i                               direction_;
        Slider<type>*                       slider_;
        State state_;
    };
*/
/*========================< MoveButton implementation >=======================*/
/*
    template <ScrollType type>
    MoveButton<type>::MoveButton(std::unique_ptr<psapi::sfm::Sprite> sprite,
                                const vec2i                         &position,
                                const vec2u                         &size,
                                const vec2i                         &direction,
                                const IWindow*                      scroll_bar,  
                                Slider<type>*                       slider     )
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

    template <ScrollType type>
    void MoveButton<type>::draw(IRenderWindow* render_window)
    {
        sprite_->setPosition(pos_);
        sprite_->draw(render_window);
    }

    template <ScrollType type>
    bool MoveButton<type>::update(const IRenderWindow* render_window,
                                const Event          &event        )
    {
        if (!is_active_) return false;

        vec2i new_mouse_position = psapi::sfm::Mouse::getPosition(render_window);

        new_mouse_position -= pos;

        if (0 <= new_mouse_position.x && new_mouse_position.x <= size_.x &&
            0 <= new_mouse_position.y && new_mouse_position.y <= size.y     )
        {
            if (event.type == Event::MouseButtonPressed)
            {
                slider_->move((float)direction.x, (float)direction.y);
                return true;
            }
        }

        return false;
    }

    template <ScrollType type>
    void MoveButton<type>::setState(State state)
    {
        state_ = state;
    }

    template <ScrollType type>
    psapi::IBarButton::State MoveButton<type>::getState() const
    {
        return state_;
    } 
*/
/*============================================================================*/

/*===========================< ScrollBar interface >==========================*/
/*
    template <ScrollType type>
    class ScrollBar : public psapi::IBar, public AWindowVector
    {
    public:
        ScrollBar(  std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                    std::unique_ptr<psapi::sfm::Sprite> hover_button,
                    std::unique_ptr<psapi::sfm::Sprite> press_button,
                    std::unique_ptr<psapi::sfm::Sprite> release_button,
                    const vec2i    &bar_position,
                    const vec2u    &bar_size,
                    const wid_t    &id                                    );

        virtual ~ScrollBar() override = default;

        virtual void draw(IRenderWindow* render_window) override;
        virtual bool update(const IRenderWindow* render_window, const Event& event) override;

        virtual psapi::ChildInfo getNextChildInfo() const override;
        virtual void finishButtonDraw(IRenderWindow* renderWindow, const psapi::IBarButton* button) const override;

    private:
        void drawChildren(IRenderWindow* render_window) override;
        bool updateChildren(const IRenderWindow* render_window, const Event& event) override;
        void handleDoubleAction();
        
        std::unique_ptr<psapi::sfm::Sprite> background_;
        std::unique_ptr<psapi::sfm::Sprite> hover_button_;
        std::unique_ptr<psapi::sfm::Sprite> press_button_;
        std::unique_ptr<psapi::sfm::Sprite> release_button_;

    };
*/
/*========================< ScrollBar implementation >========================*/
/*
    template<ScrollType type>
    ScrollBar<type>::ScrollBar( std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                                std::unique_ptr<psapi::sfm::Sprite> hover_button,
                                std::unique_ptr<psapi::sfm::Sprite> press_button,
                                std::unique_ptr<psapi::sfm::Sprite> release_button,
                                const vec2i    &bar_position,
                                const vec2u    &bar_size,
                                const wid_t    &id                                      )
    :
        background_     (std::move(background)),
        hover_button_   (std::move(hover_button)),
        press_button_   (std::move(press_button)),
        release_button_ (std::move(release_button))
    {
        pos_    = bar_position;
        size_   = bar_size;
        id_     = id;

        
    }
*/
/*============================================================================*/
//}

//#endif //VIEW_SCROLL_BAR_HPP