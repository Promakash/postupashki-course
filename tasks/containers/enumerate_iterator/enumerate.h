template<typename It>
class EnumerateIt {
};

template<typename It>
class Enumerate {
public:
    Enumerate(It begin, It end);

    EnumerateIt<It> begin();

    EnumerateIt<It> end();
};