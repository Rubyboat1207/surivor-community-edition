Vector2 cameraPosition = Vector2(0,0);

class Renderer: public PsudoComponent {
    public:
        RubyImage* sharedSprite;

        Transform* transform = nullptr;

        Renderer() {};
        ~Renderer() {};

        virtual void Update();
        virtual void Start();
        void Render(Vector2 screenspacePosition);
};

void Renderer::Start() {
    if(transform == nullptr) {
        transform = gameObject->GetComponent<Transform>();
        return;
    }
}

void Renderer::Update() {
    Vector2 spritePose = cameraPosition - transform->position;
    Render(spritePose);
}

void Renderer::Render(Vector2 screenspacePosition) {
    sharedSprite->setX(screenspacePosition.x);
    sharedSprite->setY(screenspacePosition.y);
    sharedSprite->blit(screenSurface);
}

class MultispriteRenderer : public PsudoComponent {
    public:
        RubySpriteSheet* sharedSprite;

        Transform* transform = nullptr;

        MultispriteRenderer() {};
        ~MultispriteRenderer() {};

        virtual void Update();
        virtual void Start();
        virtual void ComponentAdded(PsudoComponent* comp) { printf("test\n"); }
};

void MultispriteRenderer::Start() {
    if(transform == nullptr) {
        transform = gameObject->GetComponent<Transform>();
        return;
    }
}

void MultispriteRenderer::Update() {
    Vector2 spritePose = cameraPosition - transform->position;
    sharedSprite->setX(spritePose.x);
    sharedSprite->setY(spritePose.y);
    sharedSprite->blit();
}

// void MultispriteRenderer::ComponentAdded(PsudoComponent* comp) {
//     printf("hehehe\n");
//     printf("%s", comp->isOf<Transform>() ? "yes" : "no");
//     if(comp->isOf<Transform>()) {
//         transform = (Transform*) comp;
//     }
// }

class TextRenderer: public Renderer {
    public:
    RubySpriteSheet* spriteSheet;
    string backingText;
    virtual void Update();
    TextRenderer(RubySpriteSheet* sharedSpriteSheet);
};

TextRenderer::TextRenderer(RubySpriteSheet* sharedSpriteSheet) {
    this->sharedSprite = sharedSpriteSheet->src;
}

void TextRenderer::Update() {
    for(int i = 0; i < backingText.size(); i++) {
        char c = backingText.at(i);
        spriteSheet->col = c - 31;
        Vector2 spritePose = Vector2(cameraPosition.x - transform->position.x, cameraPosition.y - transform->position.y);
        sharedSprite->setX(spritePose.x + (spriteSheet->rowWidth * i));
        sharedSprite->setY(spritePose.y);
        sharedSprite->blit(screenSurface);
    }
}