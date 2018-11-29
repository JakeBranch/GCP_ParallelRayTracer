#include <iostream>

#include <SDL.h>

#include <memory>
#include <list>

#include "Camera.h"
#include "Ray.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Window.h"
#include "RayTracer.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();
    std::shared_ptr<Window> window = std::make_shared<Window>();
    std::shared_ptr<RayTracer> rayTracer = std::make_shared<RayTracer>();
    
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(200, 200 , 0), 100, glm::vec3(0,0,1));
    rayTracer->addSphere(sphere1);

    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(400, 400 , 0), 100, glm::vec3(0,0,1));
    rayTracer->addSphere(sphere2);

    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(200, 400, 0), 100, glm::vec3(0,0,1));
    rayTracer->addSphere(sphere3);

    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(glm::vec3(400, 200, 0), 100, glm::vec3(0,0,1));
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
            for(int y = 0; y < 800; y++)
            {
                
                for(int x = 0; x < 600; x++)
                {
                    Ray ray = camera->createRay(glm::vec3(x, y, 0));

                    glm::vec3 color = rayTracer->traceRay(ray);

                    color.x *= 255;
                    color.y *= 255;
                    color.z *= 255;

                    window->drawPixel(x, y, color);
                }

            }

            window->display();
            finished = true;
        }
    }

    window->cleanUp();

    return 0;
}