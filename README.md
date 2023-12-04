<p align="center">
<img src="./assets/logo.png" width="100" height="100" /> 
</p>

# Джеджалик

Швидкий компілятор Мавки для вебу.

```c++
#include "jejalyk.cpp"

int main() {
    const auto result = compile("друк(\"Привіт від Івана!\")");
    if (result->parser_error) {
        std::cout << result->parser_error->message << std::endl;
    } else if (result->error) {
        std::cout << result->error->message << std::endl;
    } else {
        std::cout << result->result << std::endl;
    }
    return 0;
}
```