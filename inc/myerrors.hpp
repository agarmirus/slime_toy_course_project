#include <exception>
#include <string>

using namespace std;

class BaseError: public std::exception
{};

class TextureFileIOError: public BaseError
{};
