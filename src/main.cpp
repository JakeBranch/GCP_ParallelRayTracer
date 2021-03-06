#include <iostream>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <time.h>

#include <SDL.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Window.h"
#include "RayTracer.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Window> window = std::make_shared<Window>();
    std::shared_ptr<RayTracer> rayTracer = std::make_shared<RayTracer>();

    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(3.0f, 0 , -20), 2, glm::vec3(0.75f,0,0.75f));
    rayTracer->addSphere(sphere1);

    std::shared_ptr<Sphere> sphere9 = std::make_shared<Sphere>(glm::vec3(2.5f, 5.0f , -15), 1, glm::vec3(1,0,0));
    rayTracer->addSphere(sphere9);
  
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(-3.0f, 0, -20), 2, glm::vec3(0,0.75f,0.75f));
    rayTracer->addSphere(sphere2);

    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(0, -3.0f, -20), 2, glm::vec3(0.75f,0.75f,0));
    rayTracer->addSphere(sphere3);

    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(glm::vec3(0, 3.0f, -20), 2, glm::vec3(0.75f,0.75f,0.75f));
    rayTracer->addSphere(sphere4);

    bool running = true;
    bool finished = false;

	while (running)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

        if(!finished)
        {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            for(int y = 0; y < 800; y++)
            {
                
                for(int x = 0; x < 600; x++)
                {
                        Ray ray = camera->createRay(glm::vec3(x, y, 0));

                        glm::vec3 color = glm::vec3(0.1f,0.1f,0.1f);

                        rayTracer->traceRay(ray, color);

                        color.x *= 255;
                        color.y *= 255;
                        color.z *= 255;
                        
            
                        window->drawPixel(x, y, glm::clamp(color, glm::vec3(0,0,0), glm::vec3(255,255,255)));
                }

            }

            window->display();
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            finished = true;

            std::chrono::duration<double> executionTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            std::cout << "Time taken: " << executionTime.count() << std::endl;
        }
    }

    window->cleanUp();

    return 0;
}
