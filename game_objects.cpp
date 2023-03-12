class PsudoComponent;
class GameObject;
#include <type_traits>

class PsudoComponent {
    public:
        GameObject* gameObject;

        virtual void Update();
        virtual void Start();
        virtual void ComponentAdded(PsudoComponent* comp) {}
        template<class T>
        bool isOf();
        // template<class T>
        // PsudoComponent GetComponent(T componentType) { return gameObject->GetComponent(componentType); };
};

void PsudoComponent::Update() {

}

void PsudoComponent::Start() {

}

template<class T>
bool PsudoComponent::isOf() {
    T* result = dynamic_cast<T*>(this);
    if (result != nullptr) {
        return true;
    }
    return false;
}

std::vector<GameObject*> activeGameObjects;
class GameObject {
    bool active;
public:
    std::vector<PsudoComponent*> components;
    int activeid;
    template<class T>
    T* GetComponent();
    void Update();
    void Start();

    void AddComponent(PsudoComponent* component);
    GameObject() {
        printf("added\n");
        activeid = activeGameObjects.size();
        activeGameObjects.push_back(this);
    }
    ~GameObject() {
        for(int i = 0; i < components.size(); i++) {
            delete components[i];
        }
    }
    void setActive(bool active);
};
template<class T>
T* GameObject::GetComponent() {
    try {
        for (PsudoComponent* component : components) {
            T* result = dynamic_cast<T*>(component);
            if (result != nullptr) {
                return result;
            }
            // if(component->isOf<T>()) {
            //     return dynamic_cast<T*>(component);
            // }
        }
        return nullptr;
    }
    catch(...) {
        return nullptr;
    }
}

/**
 * @brief Adds component to a game object, and transfers ownership to the gameobject.
 * 
 * This now means that the game object's update function now calls the update function of the component.
 * The newly registered component will now have their component added function called for each currently present components.
 * Any pre-existing components will also be notified of this addition.
 * 
 * @param component Component instance to be added
 * @return ** void 
 */
void GameObject::AddComponent(PsudoComponent* component) {
    component->gameObject = this;
    for(PsudoComponent* comp: components) {
        comp->ComponentAdded(component);
        component->ComponentAdded(comp);
    }
    components.push_back(component);
    // printf("start\n");
    component->Start();
}
void GameObject::setActive(bool active) {
    if(this->active != active) {
        if(!active) {
            printf("deactivated\n");
            activeGameObjects.erase(activeGameObjects.begin() + activeid);
            activeid = -1;
        }
        if(active) {
            activeid = activeGameObjects.size();
            activeGameObjects.push_back(this);
        }
    }
    this->active = active;
}

void GameObject::Update() {
    // printf("GO updating\n");
    for(int i = 0; i < components.size(); i++) {
        // printf("c update\n");
        components[i]->Update();
    }
}