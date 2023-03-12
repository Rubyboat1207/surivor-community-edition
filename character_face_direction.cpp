
class CharacterFaceDirection: public PsudoComponent {
    public:
        bool FlipSprite;
        Transform* transform;
        Vector2 oldPosition = Vector2(0,0);


        CharacterFaceDirection() {
            
        }
        ~CharacterFaceDirection() {}

        virtual void Update();
        virtual void Start();
};

void CharacterFaceDirection::Start() {
    transform = gameObject->GetComponent<Transform>();
}

void CharacterFaceDirection::Update() {
    // I'd assume this is managed for me due to scoping and the fact these arent pointers.
    Vector2 position = Vector2(transform->position.x, transform->position.y);
    
    

    oldPosition = position;
}