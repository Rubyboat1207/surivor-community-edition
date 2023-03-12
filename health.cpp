
class Health: public PsudoComponent {
    public:
        double maxHP;
        double health;
        Health() {
            
        }
        ~Health() {}

        virtual void Damage(int damage);
        virtual void Damage();
        virtual void Heal();
        virtual void Heal(int hp);
        virtual void OnDeath();
};

void Health::Damage() {
    Damage(1);
}
void Health::Damage(int damage) {
    if(damage < 0) {
        Heal(-damage);
        return;
    }
    health -= damage;
    if(health <= 0) {
        health = 0;
        OnDeath();
    }
}
void Health::Heal() {
    Heal(1);
}
void Health::Heal(int hp) {
    if(hp < 0) {
        Damage(-hp);
        return;
    }
    health += hp;
    if(health > maxHP) {
        health = maxHP;
    }
}
void Health::OnDeath() {
    
}