#include <iostream>

{% if cookiecutter.add_boost == 'y' -%}
#include <boost/algorithm/string.hpp>
{% endif %}
{% if cookiecutter.add_sfml == 'y' -%}
#include <SFML/Graphics.hpp>
{% endif %}

int main(int argc, char** argv)
{
    std::cout << "Hello, world!" << std::endl;

    {% if cookiecutter.add_boost == 'y' -%}
    const std::string hello_boost = "Hello";
    std::cout << boost::algorithm::to_upper_copy(hello_boost) << std::endl;
    {% endif %}
    {% if cookiecutter.add_sfml == 'y' -%}
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML example");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
    {% endif %}

    return 0;
}
