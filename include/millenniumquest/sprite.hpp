#pragma once
#include <raylib.h>

namespace mquest{
    struct SpriteSheets{
        unsigned int sheet_rows, sheet_columns;
    };
    
    class Sprite{
        protected:
        Texture2D sprite_texture;
        Rectangle spriteframe_rect;
        Vector2 m_velocity, m_position;
        bool on_ground;
        private:
        const SpriteSheets sprite_sheets;
        unsigned int frame_counter, current_frame, frame_count;
        const int frame_speed;
        public:
        Sprite(Texture2D texture, Vector2 position,
            SpriteSheets &&sheets,
            unsigned int &&frame_count=5U,
            int &&frame_speed=8) : 
            sprite_texture{texture}, m_position{position},
            frame_speed{frame_speed}, frame_counter{0U}, current_frame{0U}, frame_count{frame_count},
            on_ground{true}, m_velocity{0,0}, sprite_sheets{sheets}
        {}
        bool &ground() noexcept { return on_ground; }
        Rectangle &frame_rect() noexcept { return spriteframe_rect; }
        Vector2 &position() noexcept { return m_position; }
        Vector2 &velocity() noexcept { return m_velocity; }

        void update(float &delta, const unsigned int &&fps=60){
            this->frame_counter++;
            if(this->frame_counter >= (fps/this->frame_speed)){
                this->frame_counter = 0;
                this->current_frame = (this->current_frame + 1) % frame_count;
            }
            int frame_width = this->sprite_texture.width / this->sprite_sheets.sheet_columns;
            int frame_height = this->sprite_texture.height / this->sprite_sheets.sheet_rows;
            this->spriteframe_rect.x = (this->current_frame % this->sprite_sheets.sheet_columns) * frame_width;
            this->spriteframe_rect.y = (this->current_frame / this->sprite_sheets.sheet_columns) * frame_height;
            this->spriteframe_rect.width = frame_width;
            this->spriteframe_rect.height = frame_height;

            this->m_velocity.y += 400 * delta;
            this->m_position.y += this->m_velocity.y * delta;
        }
        void draw_sprite(Color color=WHITE){
            DrawTextureRec(this->sprite_texture, this->spriteframe_rect, this->m_position, color);
        }
        void unload_sprite(){
            UnloadTexture(this->sprite_texture);
        }
    };
};