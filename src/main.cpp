#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>

#include <memory>
#include <list>
#include <omp.h>
#include <thread>
#include <mutex>
#include <vector>

#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Window.h"
#include "RayTracer.h"

std::mutex mutex;

void traceRays(int startY, int endY, int startX, int endX, std::shared_ptr<Camera> camera, std::shared_ptr<RayTracer> rayTracer, std::shared_ptr<Window> window);

int main(int argc, char *argv[])
{
    int num;
    std::cin >> num;

    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Window> window = std::make_shared<Window>();
    std::shared_ptr<RayTracer> rayTracer = std::make_shared<RayTracer>();
    
    std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(200, 200 , 100), 100, glm::vec3(0,0,0.75f));
    rayTracer->addSphere(sphere1);

    // std::shared_ptr<Sphere> sphere9 = std::make_shared<Sphere>(glm::vec3(200, 200 , 500), 100, glm::vec3(1,0,0));
    // rayTracer->addSphere(sphere9);

    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(400, 400 , 100), 100, glm::vec3(0,0,0.75f));
    rayTracer->addSphere(sphere2);

    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(glm::vec3(200, 400, 100), 100, glm::vec3(0.75f,0,0));
    rayTracer->addSphere(sphere3);

    std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(glm::vec3(400, 200, 100), 100, glm::vec3(0.75f,0,0));
    rayTracer->addSphere(sphere4);

    bool running = true;
    bool finished = false;

    std::vector<std::thread> threads;

    int stepY = 200;
    int startY = 0;
    int endY = stepY;

    int stepX = 150;
    int startX = 0;
    int endX = stepX;

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
            for(int i = 0; i < 16; i++)
            {
                if(i != 0)
                {
                    if(i % 4 == 0)
                    {
                        startY += stepY;
                        endY += stepY;

                        startX = 0;
                        endX = stepX;
                    }
                    else
                    {
                        startX += stepX;
                        endX += stepX;
                    }
                }

                threads.push_back(std::thread(traceRays, startY, endY, startX, endX, camera, rayTracer, window));
            }

            for(std::vector<std::thread>::size_type i = 0; i != threads.size(); i++)
            {
                threads[i].join();
            }

            window->display();
            finished = true;
        }
    }

    window->cleanUp();

    return 0;
}

void traceRays(int startY, int endY, int startX, int endX, std::shared_ptr<Camera> camera, std::shared_ptr<RayTracer> rayTracer, std::shared_ptr<Window> window)
{
    for(int y = startY; y < endY; y++)
    {
        
        for(int x = startX; x < endX; x++)
        {
            Ray ray = camera->createRay(glm::vec3(x, y, 0));

            glm::vec3 color = glm::vec3(0.1f,0.1f,0.1f);

            rayTracer->reset();
            rayTracer->traceRay(ray, color);

            color.x *= 255;
            color.y *= 255;
            color.z *= 255;
            
            mutex.lock();
                window->drawPixel(x, y, glm::clamp(color, glm::vec3(0,0,0), glm::vec3(255,255,255)));
            mutex.unlock();
        }

    }
}