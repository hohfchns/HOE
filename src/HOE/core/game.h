#pragma once
#include "enums.h"
#include "render_component.h"
#include "collision_component.h"
#include "SDL.h"
#include "camera.h"
#include <vector>

// Singleton class
class Game
{
public:
    static Game& GetInstance() {
        static Game instance;

        return instance;
    }

    int getScreenWidth () { return m_ScreenWidth; }
    int getScreenHeight () { return m_ScreenHeight; }

    void initalize(int screenWidth, int screenHeight) { m_ScreenWidth = screenWidth; m_ScreenHeight = screenHeight; }

    std::vector<Component*> m_ReadyComponents;
    std::vector<Component*> m_UpdateComponents;
    std::vector<RenderComponent*> m_RenderComponents;
    std::vector<CollisionComponent*> m_CollisionComponents;

    std::vector<Component*> GetComponents() { return m_Components; }
    void AddComponent(Component* component) { m_Components.push_back(component); }
    void AddRenderComponent(RenderComponent* component);
    void AddCollisionComponent(CollisionComponent* component);
    void AddComponentCallback(Component* component, CallbackType type);
    void RemoveComponent(Component* component, CallbackType type);
    void RemoveRenderComponent(Component* component);
    void RemoveCollisionComponent(Component* component);

    void InitComponents() { for (Component* component : m_Components) { component->Init(); } }
    void ReadyComponents() { for (Component* component : m_ReadyComponents ) { component->Ready(); } }
    void UpdateComponents(double deltaTime) { for ( Component* component : m_UpdateComponents ) { component->Update(deltaTime); } }
    void PhysicsUpdateComponents(double deltaTime) { for ( Component* component : m_UpdateComponents ) { component->PhysicsUpdate(deltaTime); } }
    void DrawComponents(SDL_Renderer** renderer) { for (RenderComponent* component : m_RenderComponents) { component->Draw(renderer, m_MainCamera); } }

    SDL_Renderer** m_CurRenderer = NULL;

    Camera* m_MainCamera;

private:
    Game() {} ;

    bool ComponentInVector(Component* component, std::vector<Component*> vector);

    int m_ScreenWidth;
    int m_ScreenHeight;

    std::vector<Component*> m_Components;

public:
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};