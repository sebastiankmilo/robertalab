//NEPO definitions for calliope
// Display brightness is in interval of 0..255
// To scale that to 0..9 we use the following multipliers:
#define _SET_BRIGHTNESS_MULTIPLIER 28.34
#define _GET_BRIGHTNESS_MULTIPLIER 0.0353
// Light sensor returns values in interval 0..255
// To scale them to 0..100 we use this multiplier:
#define _GET_LIGHTLEVEL_MULTIPLIER 0.3922
#define _ITERATION_SLEEP_TIMEOUT 1

// math constants used in math blocks. Avoids inclusion of <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.718281828459045
#endif

#ifndef M_GOLDEN_RATIO
#define M_GOLDEN_RATIO 1.61803398875
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 0.707106781187
#endif

#ifndef M_INFINITY
#define M_INFINITY 0x7f800000
#endif

#include <list>

template <typename T>
T _getListElementByIndex(std::list<T> &list, unsigned index) {
    auto iterator = list.begin();
    advance(iterator, index);
    return (*iterator);
}

template <typename T>
T _getAndRemoveListElementByIndex(std::list<T> &list, unsigned index) {
    auto iterator = list.begin();
    advance(iterator, index);
    T value = (*iterator);
    list.erase(iterator);
    return value;
}

template <typename T>
void _removeListElementByIndex(std::list<T> &list, unsigned index) {
    _getAndRemoveListElementByIndex(list, index);
}

/*
* The only known situation where the cast of P to T would be needed is for int to double
* in other cases T and P will be the same type. If only one template parameter is used
* then the match void setListElementByIndex(std::list<double>, int, int) would not be possible
*/

template <typename T, typename P>
void _setListElementByIndex(std::list<T> &list, unsigned index, P value) {
    if (index < list.size()) {
        auto iterator = list.begin();
        advance(iterator, index);
        (*iterator) = (T) (value);
    } else {
        list.push_back((T) (value));
    }
}

template <typename T, typename P>
void _insertListElementBeforeIndex(std::list<T> &list, unsigned index, P value) {
    auto iterator = list.begin();
    advance(iterator, index);
    list.insert(iterator, (T) (value));
}

template <typename T, typename P>
int _getFirstOccuranceOfElement(std::list<T> &list, P value) {
    int i = 0;
    auto iterator = list.begin();
    for(i = 0, iterator = list.begin(); iterator != list.end(); ++iterator, ++i) {
      if ((P) (*iterator) == value) {
        return i;
      }
    }
    if ((P) (*iterator) != value) {
      return -1;
    }
}

template <typename T, typename P>
int _getLastOccuranceOfElement(std::list<T> &list, P value) {
    int i = 0;
    auto iterator = list.rbegin();
    for(i = 0, iterator = list.rbegin(); iterator != list.rend(); ++iterator, ++i) {
      if ((P) (*iterator) == value) {
        return i;
      }
    }
    if ((P) (*iterator) != value) {
      return -1;
    }
}
