class Vector2 {
public:
    Vector2(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double x;
    double y;
    Vector2 operator+(Vector2 vec) {
        return Vector2(vec.x + x, y + vec.y);
    }
    Vector2 operator+(Vector2* vec) {
        return Vector2(vec->x + x, y + vec->y);
    }
    void operator+=(Vector2 vec) {
        x += vec.x;
        y += vec.y;
    }
    Vector2 operator-() {
        return Vector2(-x, -y);
    }
    Vector2 operator-(Vector2 vec) {
        return Vector2(x - vec.x, y - vec.y);
    }
    Vector2 operator*(double mult) {
        return Vector2(x * mult, y * mult);
    }
    Vector2 normalize() {
        double maximum = std::max(x, y);
        // x = 90
        // y = 15

        //max = 90
        //min = 15

        // (90 - 15) / 90 : 0.8
        // : 0.0
        return Vector2(x / maximum, y / maximum);
    }
    void print();
};

void Vector2::print() {
    printf(" %f,%f\n", x, y);
}


double calcP(double p, double cur, double setpoint) {
    double err = setpoint - cur;
    return cur + (p * err) * deltaTime;
}

Vector2 calcP(double p, Vector2* cur, Vector2* setpoint) {
    return Vector2(calcP(p, cur->x, setpoint->x), calcP(p, cur->y, setpoint->y));
}