#include "framebuffer.h"

void render() {
    // Limpiar el framebuffer con el color de fondo
    Color clearColor(0, 0, 0);  // Negro
    clear(clearColor);

    // Colores
    Color white(255, 255, 255);
    Color yellow(255, 255, 0);
    Color blue(0, 0, 255);
    Color green(0, 255, 0);
    Color red(255, 0, 0);

    // Definir polígonos
    std::vector<Vertex2> polygon1 = {
        {165, 380}, {185, 360}, {180, 330}, {207, 345}, {233, 330}, {230, 360}, {250, 380}, {220, 385}, {205, 410}, {193, 383}
    };

    std::vector<Vertex2> polygon2 = {
        {321, 335}, {288, 286}, {339, 251}, {374, 302}
    };

    std::vector<Vertex2> polygon3 = {
        {377, 249}, {411, 197}, {436, 249}
    };

    std::vector<Vertex2> polygon4 = {
        {413, 177}, {448, 159}, {502, 88}, {553, 53}, {535, 36}, {676, 37}, {660, 52},
        {750, 145}, {761, 179}, {672, 192}, {659, 214}, {615, 214}, {632, 230}, {580, 230},
        {597, 215}, {552, 214}, {517, 144}, {466, 180}
    };

    std::vector<Vertex2> polygon5 = {
        {682, 175}, {708, 120}, {735, 148}, {739, 170}
    };

    // Dibujar polígonos
    drawPolygon(polygon1, yellow, white);
    
    drawPolygon(polygon2, blue, white);

    renderBuffer();
}

int main() {
    render();

    return 0;
}
