#include "scroll_bar.hpp"

template <>
ps::ScrollBar<ps::Orientation::Vertical>::ScrollBar(std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                                                    std::unique_ptr<psapi::sfm::Sprite> hover_button,
                                                    std::unique_ptr<psapi::sfm::Sprite> press_button,
                                                    std::unique_ptr<psapi::sfm::Sprite> release_button,
                                                    ps::Scrollable *scrollable_object,
                                                    double          scroll_ratio,
                                                    const vec2i    &bar_position,
                                                    const vec2u    &bar_size,
                                                    const wid_t    &id                                      )
:
    background_     (std::move(background_sprite)),
    hover_button_   (std::move(hover_button)),
    press_button_   (std::move(press_button)),
    release_button_ (std::move(release_button))
{
    pos_    = bar_position;
    size_   = bar_size;
    id_     = id;

    static std::unique_ptr<psapi::sfm::Texture> slider_texture = {};
    slider_texture->loadFromFile(VERTICAL_SLIDER_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> slider_sprite = {};
    slider_sprite->setTexture(slider_texture.get());

    vec2u slider_size = vec2u{16u, (unsigned int)(scroll_ratio * size_.y)};

    std::unique_ptr<Slider<Orientation::Vertical>> slider = std::make_unique<Slider<Orientation::Vertical>>(std::move(slider_sprite),
                                                                                                            pos_ + vec2i{0, 16},
                                                                                                            slider_size,
                                                                                                            vec2i{0, 1},
                                                                                                            pos_ + vec2i{0, 16},
                                                                                                            size_,
                                                                                                            this, 
                                                                                                            scrollable_object);

    static std::unique_ptr<psapi::sfm::Texture> up_move_texture = {};
    up_move_texture->loadFromFile(UP_MOVE_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> up_move_sprite = {};
    up_move_sprite->setTexture(up_move_texture.get());

    std::unique_ptr<MoveButton<Orientation::Vertical>> up_move_button = std::make_unique<MoveButton<Orientation::Vertical>>(std::move(up_move_sprite),
                                                                                                                            pos_,
                                                                                                                            vec2u{16, 16},
                                                                                                                            vec2i{0, 1},
                                                                                                                            this,
                                                                                                                            slider.get());
    
    static std::unique_ptr<psapi::sfm::Texture> down_move_texture = {};
    down_move_texture->loadFromFile(DOWN_MOVE_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> down_move_sprite = {};
    down_move_sprite->setTexture(down_move_texture.get());

    std::unique_ptr<MoveButton<Orientation::Vertical>> down_move_button = std::make_unique<MoveButton<Orientation::Vertical>>(  std::move(down_move_sprite),
                                                                                                                                pos_ + vec2i{size_.x - 16, size_.y - 16},
                                                                                                                                vec2u{16, 16},
                                                                                                                                vec2i{0, -1},
                                                                                                                                this,
                                                                                                                                slider.get());

    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(down_move_button))));
    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(up_move_button))));
    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(slider))));

}

template <>
ps::ScrollBar<ps::Orientation::Horizontal>::ScrollBar(std::unique_ptr<psapi::sfm::Sprite> background_sprite, 
                                                    std::unique_ptr<psapi::sfm::Sprite> hover_button,
                                                    std::unique_ptr<psapi::sfm::Sprite> press_button,
                                                    std::unique_ptr<psapi::sfm::Sprite> release_button,
                                                    ps::Scrollable *scrollable_object,
                                                    double          scroll_ratio,
                                                    const vec2i    &bar_position,
                                                    const vec2u    &bar_size,
                                                    const wid_t    &id                                      )
:
    background_     (std::move(background_sprite)),
    hover_button_   (std::move(hover_button)),
    press_button_   (std::move(press_button)),
    release_button_ (std::move(release_button))
{
    pos_    = bar_position;
    size_   = bar_size;
    id_     = id;

    static std::unique_ptr<psapi::sfm::Texture> slider_texture = {};
    slider_texture->loadFromFile(HORIZONTAL_SCROLL_BAR_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> slider_sprite = {};
    slider_sprite->setTexture(slider_texture.get());

    vec2u slider_size = vec2u{(unsigned int)(scroll_ratio * size_.x), 16u};

    std::unique_ptr<Slider<Orientation::Horizontal>> slider = std::make_unique<Slider<Orientation::Horizontal>>(std::move(slider_sprite),
                                                                                                                pos_ + vec2i{16, -16},
                                                                                                                slider_size,
                                                                                                                vec2i{1, 0},
                                                                                                                pos_ + vec2i{16, -16},
                                                                                                                size_,
                                                                                                                this, 
                                                                                                                scrollable_object);

    static std::unique_ptr<psapi::sfm::Texture> left_move_texture = {};
    left_move_texture->loadFromFile(LEFT_MOVE_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> left_move_sprite = {};
    left_move_sprite->setTexture(left_move_texture.get());

    std::unique_ptr<MoveButton<Orientation::Vertical>> left_move_button = std::make_unique<MoveButton<Orientation::Vertical>>(  std::move(left_move_sprite),
                                                                                                                                pos_,
                                                                                                                                vec2u{16, 16},
                                                                                                                                vec2i{-1, 0},
                                                                                                                                this,
                                                                                                                                slider.get());
    
    static std::unique_ptr<psapi::sfm::Texture> right_move_texture = {};
    right_move_texture->loadFromFile(RIGHT_MOVE_BUTTON_TEXTURE);

    std::unique_ptr<psapi::sfm::Sprite> right_move_sprite = {};
    right_move_sprite->setTexture(right_move_texture.get());

    std::unique_ptr<MoveButton<Orientation::Vertical>> right_move_button = std::make_unique<MoveButton<Orientation::Vertical>>( std::move(right_move_sprite),
                                                                                                                                pos_ + vec2i{size_.x - 16, -16},
                                                                                                                                vec2u{16, 16},
                                                                                                                                vec2i{1, 0},
                                                                                                                                this,
                                                                                                                                slider.get());

    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(right_move_button))));
    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(left_move_button))));
    (static_cast<AWindowVector*>(this))->addWindow(std::move(static_cast<std::unique_ptr<AWindow>>(std::move(slider))));

}
