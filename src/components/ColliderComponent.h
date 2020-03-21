#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>

#include "../AssetManager.h"
#include "../Components/TransformComponent.h"
#include "../EntityManager.h"
#include "../Game.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
  public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent* transform;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
        this->colliderTag = colliderTag;
        this->collider    = {x, y, width, height};
        texture           = Game::assetManager->GetTexture(std::string("collision-texture"));
    }

    void Initialize() override {
        if (owner->HasComponent<TransformComponent>()) {
            transform            = owner->GetComponent<TransformComponent>();
            sourceRectangle      = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override {
        collider.x             = static_cast<int>(transform->position.x);
        collider.y             = static_cast<int>(transform->position.y);
        collider.w             = transform->width * transform->scale;
        collider.h             = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
    }

    void Render() override {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }
};

#endif
