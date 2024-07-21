#ifndef VECTOR2D_HH
#define VECTOR2D_HH

class Vector2D{

    public:

        Vector2D(float x, float y);
        Vector2D(const Vector2D& other);
        Vector2D& operator=(const Vector2D& other);
        bool operator!=(const Vector2D& other) const;
        bool operator==(const Vector2D& other) const;
        ~Vector2D() = default;

        static bool lexographycal_sort(const Vector2D& v1, const Vector2D& v2);

        float m_x;
        float m_y;



};

#endif