#ifndef POINT_VORTEX_ICOPYABLE_H
#define POINT_VORTEX_ICOPYABLE_H


namespace utils {
    class ICopyable {
    public:
        [[nodiscard]] virtual ICopyable* copy() const = 0;
    };
}



#endif //POINT_VORTEX_ICOPYABLE_H
