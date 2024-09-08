#pragma once

template<typename T>
struct Vec2 {
    T x, y;
    // 向量加法
    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }
    // 向量减法
    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }
    // 点积
    T operator*(const Vec2& other) const {
        return x * other.x + y * other.y;
    }
    // 标量乘法
    Vec2 operator*(T scalar) const {
        return {x * scalar, y * scalar};
    }
    // 标量除法
    Vec2 operator/(T scalar) const {
        return {x / scalar, y / scalar};
    }
    // 比较
    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
};

template<typename T>
struct Vec3 {
    T x, y, z;
    // 向量加法
    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    // 向量减法
    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    // 标量乘法
    Vec3 operator*(T scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    // 标量除法
    Vec3 operator/(T scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }
    // 点积
    T operator*(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    // 叉积
    Vec3 cross(const Vec3& other) const {
        return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        };
    }
};

template<typename T>
struct Vec4 {
    T x, y, z, w;
    // 向量加法
    Vec4 operator+(const Vec4& other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }
    // 向量减法
    Vec4 operator-(const Vec4& other) const {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }
    // 标量乘法
    Vec4 operator*(T scalar) const {
        return {x * scalar, y * scalar, z * scalar, w * scalar};
    }
    // 标量除法
    Vec4 operator/(T scalar) const {
        return {x / scalar, y / scalar, z / scalar, w / scalar};
    }
    // 点积
    T operator*(const Vec4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
};
