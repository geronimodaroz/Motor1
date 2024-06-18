#include <SDL.h>
#include <iostream>


/*int main() {
    std::cout << "Hello, World!" << std::endl;  // Imprime "Hello, World!" seguido de un salto de línea
    std::cout << std::flush;  // Fuerza el vaciado del búfer
    return 0;
}*/

int main(int argc, char** argv)
{
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Log("Hello, World!");


    SDL_Window* window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Obtener dimensiones de la ventana
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Calcular las dimensiones de la superficie
    int surfaceWidth = 200;
    int surfaceHeight = 150;

    // Calcular las coordenadas para centrar la superficie en la ventana
    int surfaceX = (windowWidth - surfaceWidth) / 2;
    int surfaceY = (windowHeight - surfaceHeight) / 2;

    // Crear una superficie
    SDL_Surface* surface = SDL_CreateRGBSurface(0, surfaceWidth, surfaceHeight, 32, 0, 0, 0, 0);
    if (!surface) {
        std::cerr << "Error al crear la superficie: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }

        // Ejemplo de dibujo en la superficie
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0)); // Rellena la superficie de rojo

        // Convertir la superficie en textura
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Limpiar el renderizador y renderizar la textura en el centro de la ventana
        SDL_RenderClear(renderer);
        SDL_Rect destRect = { surfaceX, surfaceY, surfaceWidth, surfaceHeight };
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_RenderPresent(renderer);

        // Liberar la textura creada
        SDL_DestroyTexture(texture);
    }

    // Liberar la superficie y otros recursos
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
