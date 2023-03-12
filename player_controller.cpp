
class PlayerController: public PsudoComponent {
    public:
        Transform* transform;
        Vector2* offset = nullptr;
        double speed = 0.3;
        PlayerController() {
            
        }
        ~PlayerController() {}

        virtual void Update();
        virtual void Start();
};

void PlayerController::Start() {
    transform = gameObject->GetComponent<Transform>();
    offset = new Vector2(
        WIDTH / 2 - gameObject->GetComponent<Renderer>()->sharedSprite->surface->w / 2,
        HEIGHT / 2 - gameObject->GetComponent<Renderer>()->sharedSprite->surface->h / 2
    );
    cameraPosition = transform->position;
}

void PlayerController::Update() {
    // printf("update\n");
    
    Vector2 vec = Vector2(
		(keys[SDL_SCANCODE_A]) - (keys[SDL_SCANCODE_D]),
		(keys[SDL_SCANCODE_W]) - (keys[SDL_SCANCODE_S])
	) * deltaTime * speed;
    
    transform->position += vec;
    auto calcpos = transform->position + offset;
    auto pid = calcP(0.003, &(cameraPosition), &calcpos);
    // pid.print();
    cameraPosition = pid;
}