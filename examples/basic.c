#include "rilib.h"

int main() {
    riWindow* window = ri_createWindow("window", RI_RECT(200, 200, 800, 600), riWindowCenter);
    riWindow_vsync(window, 1); 

    riAudio_play("output.mp3");
    riRect player = RI_RECT(20, 20, 200, 200);

    riImage image = ri_loadImage("../logo.jpg");

    while (riWindow_shouldClose(window) == RI_FALSE) {
        while (riWindow_checkEvent(window)) {
            if (window->event.type == ri_keyReleased) {
                if (window->event.key == ri_return)
                    riAudio_play("sonc.mp3");
            }
        }
        
        if (ri_isPressed(window, ri_up))
            player.y -= 5;
        if (ri_isPressed(window, ri_down))
            player.y += 5;
        if (ri_isPressed(window, ri_right))
            player.x += 5;
        if (ri_isPressed(window, ri_left))
            player.x -= 5;

        riWindow_clear(window, RI_RGB(125, 0, 125));
        
        i32 size = window->r.h / 2;
        ri_drawImage(image, RI_RECT((window->r.w / 2) - (size / 2), (window->r.h / 2) - (size / 2), 
                                    size, size));

        ri_drawRect(player, RI_RGB(255, 0, 0));
        riWindow_draw(window);
    }

    riWindow_close(window);
}
