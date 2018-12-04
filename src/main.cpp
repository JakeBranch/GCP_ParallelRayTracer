#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>

#include <memory>
#include <list>
#include <omp.h>

#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Window.h"
#include "RayTracer.h"

int main(int argc, char *argv[])
{
    int num;
    std::cin >> num;

    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Window> window = std::make_shared<Window>();
    std::shared_ptr<RayTracer> rayTracer = std::make_shared<RayTracer>();
    
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(200, 200 , 100), 100, glm::vec3(0,0,0.75f));
    rayTracer->addSphere(sphere1);

    std::shared_ptr<Sphere> sphere9 = std::make_shared<Sphere>(glm::vec3(200, 200 , 500), 100, glm::vec3(1,0,0));
    rayTracer->addSphere(sphere9);

    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(400, 400 , 100), 100, glm::vec3(0,0,0.75f));
    rayTracer->addSphere(sphere2);

    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(200, 400, 100), 100, glm::vec3(0.75f,0,0));
    rayTracer->addSphere(sphere3);

    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(glm::vec3(400, 200, 100), 100, glm::vec3(0.75f,0,0));
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

            // #pragma omp parallel for
            for(int y = 0; y < 800; y++)
            {
                
                for(int x = 0; x < 600; x++)
                {
                    Ray ray = camera->createRay(glm::vec3(x, y, 0));

                    glm::vec3 color = glm::vec3(0.1f,0.1f,0.1f);

                    rayTracer->reset();
                    rayTracer->traceRay(ray, color);

                    color.x *= 255;
                    color.y *= 255;
                    color.z *= 255;
                    
                    // #pragma omp critical
                    {
                        window->drawPixel(x, y, glm::clamp(color, glm::vec3(0,0,0), glm::vec3(255,255,255)));
                    }
                }

            }

            window->display();
            finished = true;
        }
    }

    window->cleanUp();

    return 0;
}