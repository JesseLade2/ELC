#pragma once
#include "ELC.h"
#include "font8x8.hpp"
#include <vector>
#include <memory>
#include <functional>

namespace ELC {
    class Widget {
    public:
        Rectangle rect;
        virtual ~Widget() = default;
        virtual void Update() {}
        virtual void Draw() {}
        virtual void OnChar(int key) {}
        virtual void OnKeyDown(int key) {}
    };

    class Button : public Widget {
    public:
        std::string text;
        std::function<void()> onClick;
        Button(Vec2 pos, Vec2 size, std::string txt) : text(txt) {
            rect = {pos.x, pos.y, size.x, size.y};
        }
        void Update() override;
        void Draw() override;
    };

    class TextBox : public Widget {
    public:
        std::string text, placeholder;
        bool focused = false;
        TextBox(Vec2 pos, Vec2 size, std::string place) : placeholder(place) {
            rect = {pos.x, pos.y, size.x, size.y};
        }
        void Update() override;
        void Draw() override;
        void OnChar(int key) override;
        void OnKeyDown(int key) override;
    };

    class Gui {
    public:
        std::vector<std::shared_ptr<Widget>> widgets;
        void Update();
        void Draw();
        template<typename T, typename... Args>
        T& emplace_back(Args... args) {
            widgets.emplace_back(std::make_shared<T>(args...));
            return *static_cast<T*>(widgets.back().get());
        }
    };
}
