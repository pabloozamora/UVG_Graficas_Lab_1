#include "framebuffer.h"

void render() {
    // Limpiar el framebuffer con el color de fondo
    Color clearColor(0, 0, 0);  // Negro
    clear(clearColor);

    // Dibujar polígono
    
    renderBuffer();
}

int main() {
    render();

    return 0;
}
